#include <simInternal.h>
#include <undoBufferCont.h>
#include <vDateTime.h>
#include <app.h>
#include <simStrings.h>
#ifdef SIM_WITH_GUI
#include <guiApp.h>
#endif

CUndoBufferCont::CUndoBufferCont()
{
    _commonInit();
}

CUndoBufferCont::~CUndoBufferCont()
{ // beware, the current world could be nullptr
    for (size_t i = 0; i < _buffers.size(); i++)
        delete _buffers[i];
    undoBufferArrays.clearAll();
}

int CUndoBufferCont::getNextBufferId()
{
    return (_nextBufferId);
}

void CUndoBufferCont::emptySceneProcedure()
{
    _commonInit();
}

void CUndoBufferCont::_commonInit()
{
    _currentStateIndex = -1;
    for (int i = 0; i < int(_buffers.size()); i++)
        delete _buffers[i];
    _buffers.clear();
    undoBufferArrays.clearAll();
    _announceChangeStartCalled = false;
    _announceChangeGradualCalledTime = -1;
    _sceneSaveMightBeNeeded = false;
    _undoPointSavingOrRestoringUnderWay = false;
    _inUndoRoutineNow = false;
    _nextBufferId = 0;
}

bool CUndoBufferCont::isUndoSavingOrRestoringUnderWay()
{
    TRACE_INTERNAL;
    return (_undoPointSavingOrRestoringUnderWay);
}

bool CUndoBufferCont::isSceneSaveMaybeNeededFlagSet()
{
    bool codeEditorChange = false;
#ifdef SIM_WITH_GUI
    codeEditorChange = ((GuiApp::mainWindow != nullptr) &&
                        GuiApp::mainWindow->codeEditorContainer->hasSomethingBeenModifiedInCurrentScene());
#endif
    return (_sceneSaveMightBeNeeded || codeEditorChange);
}

void CUndoBufferCont::clearSceneSaveMaybeNeededFlag()
{
    _sceneSaveMightBeNeeded = false;
}

bool CUndoBufferCont::announceChange()
{
    TRACE_INTERNAL;
    if (!_inUndoRoutineNow)
    {
        bool retVal = memorizeState();
        _announceChangeGradualCalledTime = -1;
        return (retVal);
    }
    return (false);
}

void CUndoBufferCont::announceChangeStart()
{
    TRACE_INTERNAL;
    if (!_inUndoRoutineNow)
        _announceChangeStartCalled = true;
}

void CUndoBufferCont::announceChangeEnd()
{
    TRACE_INTERNAL;
    if (!_inUndoRoutineNow)
    {
        if (_announceChangeStartCalled)
        {
            memorizeState();
            _announceChangeGradualCalledTime = -1;
        }
        _announceChangeStartCalled = false;
    }
}

void CUndoBufferCont::announceChangeGradual()
{
    TRACE_INTERNAL;
    if (!_inUndoRoutineNow)
    {
        if (_announceChangeGradualCalledTime == -1)
            _announceChangeGradualCalledTime = (int)VDateTime::getTimeInMs();
    }
}

void CUndoBufferCont::memorizeStateIfNeeded()
{
    TRACE_INTERNAL;
    if (!_inUndoRoutineNow)
    {
        if (_announceChangeGradualCalledTime == -1)
            return;
        if (VDateTime::getTimeDiffInMs(_announceChangeGradualCalledTime) > 5000)
        {
            memorizeState();
            _announceChangeGradualCalledTime = -1;
        }
    }
}

void CUndoBufferCont::emptyRedoBuffer()
{
    TRACE_INTERNAL;
    while (int(_buffers.size()) > _currentStateIndex + 1)
    {
        undoBufferArrays.removeDependenciesFromUndoBufferId(_buffers[_buffers.size() - 1]->getBufferId());
        delete _buffers[_buffers.size() - 1];
        _buffers.pop_back();
#ifdef SIM_WITH_GUI
        GuiApp::setToolbarRefreshFlag();
#endif
    }
}

bool CUndoBufferCont::memorizeState()
{
    TRACE_INTERNAL;
#ifdef SIM_WITH_GUI
    if (_inUndoRoutineNow)
        return (false);
    if (!App::currentWorld->simulation->isSimulationStopped())
        return (false);
    if (GuiApp::mainWindow == nullptr)
        return (false); // we are in headless mode

    // If we arrived here, we might have something to save:

    if (!_isGoodToMemorizeUndoOrRedo())
    {                                   // we cannot memorize anything now...
        _sceneSaveMightBeNeeded = true; // actually we don't know if this is really the case, but since we are not
                                        // authorized to check right now, this is safer!
        return (false);
    }

    bool retVal = true; // means the scene changed.. we modify this variable accordingly later down

    static int tooLongExecutionCount = 0;
    int startTime = (int)VDateTime::getTimeInMs();

    if (GuiApp::mainWindow != nullptr)
        GuiApp::mainWindow->codeEditorContainer->saveOrCopyOperationAboutToHappen();

    std::vector<char> newBuff;
    CSer serObj(newBuff, CSer::filetype_csim_bin_scene_buff);
    serObj.disableCountingModeExceptForExceptions();

    serObj.writeOpenBinary(false); // we don't wanna compression
    _undoPointSavingOrRestoringUnderWay = true;
    CUndoBufferCameras* cameraBuffers = new CUndoBufferCameras();
    cameraBuffers->storeCameras();
    App::currentWorld->saveScene(serObj, false); // This takes the 90% of time of the whole routine
    cameraBuffers->releaseCameras();
    _undoPointSavingOrRestoringUnderWay = false;
    serObj.writeClose();

    CUndoBuffer* it = new CUndoBuffer(newBuff, _nextBufferId++, cameraBuffers);
    if (_currentStateIndex == -1)
    { // first buffer, we just add it
        _buffers.push_back(it);
        _currentStateIndex = 0;
    }
    else
    { // We check with previous buffer:
        std::vector<char> prevBuff;
        _getFullBuffer(_currentStateIndex, prevBuff);
        if (it->finalize(prevBuff))
        { // different from previous, we remove forward buffers and add this one:
            while (int(_buffers.size()) > _currentStateIndex + 1)
            {
                undoBufferArrays.removeDependenciesFromUndoBufferId(_buffers[_buffers.size() - 1]->getBufferId());
                delete _buffers[_buffers.size() - 1];
                _buffers.pop_back();
            }
            _buffers.push_back(it);
            _currentStateIndex++;
        }
        else
        {
            undoBufferArrays.removeDependenciesFromUndoBufferId(it->getBufferId());
            delete it; // same as previous, we delete it
            retVal = false;
        }
    }

    std::vector<char> fullBuff;
    while ((_getUsedMemory() + undoBufferArrays.getMemorySizeInBytes() > App::userSettings->undoRedoMaxBufferSize) ||
           (int(_buffers.size()) > App::userSettings->undoRedoLevelCount))
    { // We have to remove a few states at the beginning
        if (int(_buffers.size()) < 3)
            break; // at least 3 states!
        _getFullBuffer(1, fullBuff);
        CUndoBuffer* it = _buffers[1];
        it->updateWithFullBuffer(fullBuff);
        undoBufferArrays.removeDependenciesFromUndoBufferId(_buffers[0]->getBufferId());
        delete _buffers[0];
        _buffers.erase(_buffers.begin());
        _currentStateIndex--;
    }
    if (VDateTime::getTimeDiffInMs(startTime) > App::userSettings->timeInMsForUndoRedoTooLongWarning)
        tooLongExecutionCount++;
    else
        tooLongExecutionCount = 0;

    if (tooLongExecutionCount >= 5)
    {
        static bool displayedMessage = false;
        if (!displayedMessage)
        {
            std::string tmp(
                "It seems that the undo/redo functionality takes too long to execute and slows down CoppeliaSim. You "
                "might have a large scene loaded. Do you wish to disable the undo/redo functionality for current "
                "session? (in future, you can disable the undo/redo functionality manually in the user settings "
                "dialog, or you can change the threshold level for this warning in ");
            tmp += App::folders->getUserSettingsPath() + "/usrset.txt";
            if (VMESSAGEBOX_REPLY_YES == GuiApp::uiThread->messageBox_warning(GuiApp::mainWindow, "Undo / redo",
                                                                              tmp.c_str(), VMESSAGEBOX_YES_NO,
                                                                              VMESSAGEBOX_REPLY_NO))
                App::userSettings->setUndoRedoEnabled(false);
            displayedMessage = true;
        }
        tooLongExecutionCount = 0;
    }

    GuiApp::setToolbarRefreshFlag();

    _sceneSaveMightBeNeeded = _sceneSaveMightBeNeeded || retVal;
    return (retVal);
#else
    return (false);
#endif
}

bool CUndoBufferCont::_isGoodToMemorizeUndoOrRedo()
{
    TRACE_INTERNAL;
#ifdef SIM_WITH_GUI
    if (!App::currentWorld->simulation->isSimulationStopped())
        return (false);
    if (GuiApp::mainWindow == nullptr)
        return (false);
    if (GuiApp::getEditModeType() != NO_EDIT_MODE)
        return (false);
    if (GuiApp::mainWindow->oglSurface->isPageSelectionActive())
        return (false);
    if (GuiApp::mainWindow->oglSurface->isViewSelectionActive())
        return (false);
    if (!App::userSettings->getUndoRedoEnabled())
        return (false);
    return (true);
#else
    return (false);
#endif
}

bool CUndoBufferCont::canUndo()
{
    TRACE_INTERNAL;
#ifdef SIM_WITH_GUI
    if (GuiApp::mainWindow == nullptr)
        return (false); // we are in headless mode
    if (!_isGoodToMemorizeUndoOrRedo())
        return (false);
    return (_currentStateIndex > 0);
#else
    return (false);
#endif
}

bool CUndoBufferCont::canRedo()
{
    TRACE_INTERNAL;
#ifdef SIM_WITH_GUI
    if (GuiApp::mainWindow == nullptr)
        return (false); // we are in headless mode
    if (!_isGoodToMemorizeUndoOrRedo())
        return (false);
    return (_currentStateIndex <= (int(_buffers.size()) - 2));
#else
    return (false);
#endif
}

void CUndoBufferCont::undo()
{
    TRACE_INTERNAL;
#ifdef SIM_WITH_GUI
    if (_inUndoRoutineNow)
        return;
    if (GuiApp::mainWindow == nullptr)
        return; // we are in headless mode

    if (GuiApp::mainWindow->codeEditorContainer->areSceneEditorsOpen())
    {
        GuiApp::uiThread->messageBox_information(GuiApp::mainWindow, IDSN_UNDO_REDO,
                                                 IDS_UNDO_REDO_WITH_OPEN_SCRIPT_EDITOR_MESSAGE, VMESSAGEBOX_OKELI,
                                                 VMESSAGEBOX_REPLY_OK);
        return;
    }
    _inUndoRoutineNow = true;
    // 1. We memorize this position: NOOOOOOO!!! Can cause subtle errors!!
    if (_announceChangeGradualCalledTime != -1)
    {
        //  memorizeState();
        _announceChangeGradualCalledTime = -1;
    }
    if (_currentStateIndex < 1)
    {
        _inUndoRoutineNow = false;
        return; // nothing to undo
    }

    // 2. We go back:
    _currentStateIndex--;
    std::vector<char> theBuff;
    CUndoBufferCameras* cameraBuffers = _getFullBuffer(_currentStateIndex, theBuff);
    // 3. Load the buffer:

    App::worldContainer->pluginContainer->sendEventCallbackMessageToAllPlugins(sim_message_eventcallback_abouttoundo);

    _rememberSelectionState();
    cameraBuffers->preRestoreCameras();

    App::currentWorld->sceneObjects->deselectObjects();
    App::currentWorld->simulation->stopSimulation(); // should be anyway stopped!
    std::string scenePath(App::currentWorld->environment->getScenePathAndName());
    App::currentWorld->clearScene(false);

    CSer serObj(theBuff, CSer::filetype_csim_bin_scene_buff);
    serObj.readOpenBinary(0, false);
    _undoPointSavingOrRestoringUnderWay = true;

    App::currentWorld->loadScene(serObj, true);
    App::currentWorld->environment->setScenePathAndName(scenePath.c_str());
    cameraBuffers->restoreCameras();

    _undoPointSavingOrRestoringUnderWay = false;
    serObj.readClose();
    if (GuiApp::mainWindow != nullptr)
        GuiApp::mainWindow->refreshDimensions(); // this is important so that the new pages and views are set to the
                                                 // correct dimensions

    // 4. We select previously selected objects:
    _restoreSelectionState();

    _inUndoRoutineNow = false;

    App::worldContainer->pluginContainer->sendEventCallbackMessageToAllPlugins(sim_message_eventcallback_undoperformed);
    App::worldContainer->setModificationFlag(16); // undo called

    // 5. Dialog refresh:
    GuiApp::setFullDialogRefreshFlag();
    GuiApp::setToolbarRefreshFlag();
#endif
}

void CUndoBufferCont::redo()
{
    TRACE_INTERNAL;
#ifdef SIM_WITH_GUI
    if (_currentStateIndex > (int(_buffers.size()) - 2))
        return; // nothing to redo
    if (GuiApp::mainWindow == nullptr)
        return; // we are in headless mode
    if (GuiApp::mainWindow->codeEditorContainer->areSceneEditorsOpen())
    {
        GuiApp::uiThread->messageBox_information(GuiApp::mainWindow, IDSN_UNDO_REDO,
                                                 IDS_UNDO_REDO_WITH_OPEN_SCRIPT_EDITOR_MESSAGE, VMESSAGEBOX_OKELI,
                                                 VMESSAGEBOX_REPLY_OK);
        return;
    }
    // 2. We go forward:
    _currentStateIndex++;
    std::vector<char> theBuff;
    CUndoBufferCameras* cameraBuffers = _getFullBuffer(_currentStateIndex, theBuff);

    // 3. Load the buffer:

    App::worldContainer->pluginContainer->sendEventCallbackMessageToAllPlugins(sim_message_eventcallback_abouttoredo);

    _rememberSelectionState();
    cameraBuffers->preRestoreCameras();

    App::currentWorld->sceneObjects->deselectObjects();
    App::currentWorld->simulation->stopSimulation(); // should be anyway stopped!
    App::currentWorld->clearScene(false);

    CSer serObj(theBuff, CSer::filetype_csim_bin_scene_buff);
    serObj.readOpenBinary(0, false);
    _undoPointSavingOrRestoringUnderWay = true;

    App::currentWorld->loadScene(serObj, true);
    cameraBuffers->restoreCameras();

    _undoPointSavingOrRestoringUnderWay = false;
    serObj.readClose();
    if (GuiApp::mainWindow != nullptr)
        GuiApp::mainWindow->refreshDimensions(); // this is important so that the new pages and views are set to the
                                                 // correct dimensions

    // 4. We select previously selected objects:
    _restoreSelectionState();

    App::worldContainer->pluginContainer->sendEventCallbackMessageToAllPlugins(sim_message_eventcallback_redoperformed);
    App::worldContainer->setModificationFlag(32); // redo called

    // 5. Dialog refresh:
    GuiApp::setFullDialogRefreshFlag();
    GuiApp::setToolbarRefreshFlag();
#endif
}

CUndoBufferCameras* CUndoBufferCont::_getFullBuffer(int index, std::vector<char>& fullBuff)
{
    TRACE_INTERNAL;
    if ((index >= int(_buffers.size())) || (index < 0))
    {
        fullBuff.clear();
        return (nullptr);
    }
    CUndoBufferCameras* retVal = nullptr;
    if (index == 0)
    { // the first one
        retVal = _buffers[index]->getCameraBuffers();
        _buffers[index]->getRestored(nullptr, fullBuff);
    }
    else
    {
        std::vector<char> prevBuff;
        _getFullBuffer(index - 1, prevBuff);
        retVal = _buffers[index]->getCameraBuffers();
        _buffers[index]->getRestored(&prevBuff, fullBuff);
    }
    return (retVal);
}

int CUndoBufferCont::_getUsedMemory()
{
    TRACE_INTERNAL;
    int retVal = 0;
    for (size_t i = 0; i < _buffers.size(); i++)
        retVal += int(_buffers[i]->buffer.size());
    return (retVal);
}

void CUndoBufferCont::_rememberSelectionState()
{
    TRACE_INTERNAL;
    _selectionState.clear();
    std::vector<CSceneObject*> sel;
    App::currentWorld->sceneObjects->getSelectedObjects(sel);
    for (size_t i = 0; i < sel.size(); i++)
        _selectionState.push_back(sel[i]->getObjectAlias_fullPath());
}

void CUndoBufferCont::_restoreSelectionState()
{
    TRACE_INTERNAL;
    for (size_t i = 0; i < _selectionState.size(); i++)
    {
        CSceneObject* obj = App::currentWorld->sceneObjects->getObjectFromPath(nullptr, _selectionState[i].c_str(), -1);
        if (obj != nullptr)
            App::currentWorld->sceneObjects->addObjectToSelection(obj->getObjectHandle());
    }
    _selectionState.clear();
}
