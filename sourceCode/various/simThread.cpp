#include <simThread.h>
#include <vThread.h>
#include <app.h>
#include <fileOperations.h>
#include <simStringTable.h>
#include <tt.h>
#include <vDateTime.h>
#include <proxSensorRoutine.h>
#include <sceneObjectOperations.h>
#include <fileOperations.h>
#include <addOperations.h>
#include <utils.h>
#include <vVarious.h>
#include <mesh.h>
#include <graphingRoutines_old.h>
#include <simStringTable_openGl.h>
#include <simFlavor.h>
#ifdef SIM_WITH_GUI
#include <toolBarCommand.h>
#include <engineProperties.h>
#include <guiApp.h>
#endif

CSimThread::CSimThread()
{
}

CSimThread::~CSimThread()
{
}

void CSimThread::executeMessages()
{
#ifdef SIM_WITH_GUI
    if (_renderRequired() && (GuiApp::mainWindow != nullptr))
    { // we always enter here, unless we skip display frames during simulation. In idle mode, _renderRequired will sleep
        // appropriately
        if (App::currentWorld->simulation->isSimulationStopped())
        {
            for (size_t i = 0; i < App::currentWorld->sceneObjects->getObjectCount(sim_sceneobject_camera); i++)
            {
                CCamera* it = App::currentWorld->sceneObjects->getCameraFromIndex(i);
                it->handleCameraTracking();
            }
        }
        // OLD:
        if (App::currentWorld->simulation->isSimulationStopped())
        {
            for (size_t i = 0; i < App::currentWorld->sceneObjects->getObjectCount(sim_sceneobject_path); i++)
            {
                CPath_old* it = App::currentWorld->sceneObjects->getPathFromIndex(i);
                it->resetPath();
            }
        }

        App::worldContainer->pluginContainer->sendEventCallbackMessageToAllPlugins_old(
            sim_message_eventcallback_beforerendering);
        SIM_THREAD_INDICATE_UI_THREAD_CAN_DO_ANYTHING;
        GuiApp::uiThread->renderScene(); // will render via the UI thread
    }
#endif

    handleExtCalls();
}

void CSimThread::handleExtCalls()
{
#ifdef SIM_WITH_GUI
    CSimAndUiThreadSync::simThread_allowUiThreadToWrite();
    while (true)
    {
        _eventLoop.processEvents();
        if (CSimAndUiThreadSync::simThread_forbidUiThreadToWrite(false))
            break;
    }
#else
    _eventLoop.processEvents();
#endif
    _handleSimulationThreadCommands(); // Handle delayed SIM commands
}

void CSimThread::appendSimulationThreadCommand(SSimulationThreadCommand cmd, double executionDelay /*=0.0*/)
{ // CALLED FROM ANY THREAD
    cmd.sceneUniqueId = App::currentWorld->environment->getSceneUniqueID();
    cmd.execTime = VDateTime::getTime() + executionDelay;
#ifdef SIM_WITH_GUI
    _mutex.lock("CSimThread::appendSimulationThreadCommand");
    _simulationThreadCommands.push_back(cmd);
    _mutex.unlock();
#else
    _simulationThreadCommands.push_back(cmd);
#endif
}

void CSimThread::_handleSimulationThreadCommands()
{ // CALLED ONLY FROM THE MAIN SIMULATION THREAD
    IF_C_API_SIM_OR_UI_THREAD_CAN_WRITE_DATA
    {
        int i = 0;
        while (i < _simulationThreadCommands.size())
        {
            SSimulationThreadCommand cmd = _simulationThreadCommands[i];
            if (cmd.execTime <= VDateTime::getTime())
            {
#ifdef SIM_WITH_GUI
                _mutex.lock("CSimThread::_handleSimulationThreadCommands");
                _simulationThreadCommands.erase(_simulationThreadCommands.begin() + i);
                _mutex.unlock();
#else
                _simulationThreadCommands.erase(_simulationThreadCommands.begin() + i);
#endif
                _executeSimulationThreadCommand(cmd);
            }
            else
                i++;
        }
    }
}

void CSimThread::_executeSimulationThreadCommand(SSimulationThreadCommand cmd)
{
    TRACE_INTERNAL;

    if (cmd.cmdId == FINAL_EXIT_REQUEST_CMD)
        App::postExitRequest();

    if (cmd.cmdId == EXIT_REQUEST_CMD)
    {
        cmd.cmdId = FINAL_EXIT_REQUEST_CMD;
        appendSimulationThreadCommand(cmd);
    }

    if (cmd.cmdId == AUTO_SAVE_SCENE_CMD)
        _handleAutoSaveSceneCommand(cmd);

    if (cmd.cmdId == MEMORIZE_UNDO_STATE_IF_NEEDED_CMD)
    {
        App::currentWorld->undoBufferContainer->memorizeStateIfNeeded();
        App::appendSimulationThreadCommand(cmd, 0.2);
    }

    if (cmd.cmdId == CHKLICM_CMD)
    {
        std::string v = CSimFlavor::getStringVal(19);
        if (v.size() > 0)
        {
            if (v[v.size() - 1] != ' ')
                App::logMsg(sim_verbosity_errors, v.c_str());
            else
            {
                App::logMsg(sim_verbosity_errors, v.c_str());
#ifdef SIM_WITH_GUI
                if (GuiApp::canShowDialogs())
                    GuiApp::uiThread->messageBox_critical(GuiApp::mainWindow, CSimFlavor::getStringVal(20).c_str(), v.c_str(), VMESSAGEBOX_OKELI, VMESSAGEBOX_REPLY_OK);
#endif
            }
        }
        App::appendSimulationThreadCommand(cmd, double(CSimFlavor::getIntVal(4)));
    }

#ifdef SIM_WITH_GUI
    if (cmd.cmdId == REFRESH_DIALOGS_CMD)
    { // like a timer actually
        SUIThreadCommand cmdIn;
        SUIThreadCommand cmdOut;
        cmdIn.cmdId = REFRESH_DIALOGS_UITHREADCMD;
        {
            // Following instruction very important in the function below tries to lock resources (or a plugin it
            // calls!):
            SIM_THREAD_INDICATE_UI_THREAD_CAN_DO_ANYTHING;
            GuiApp::uiThread->executeCommandViaUiThread(&cmdIn, &cmdOut);
        }
        appendSimulationThreadCommand(cmd, 0.3);
    }
#endif

    if (cmd.sceneUniqueId != App::currentWorld->environment->getSceneUniqueID())
        return;

#ifdef SIM_WITH_GUI
    if (cmd.cmdId == PLUS_HVUD_CMD)
    {
        SUIThreadCommand cmdIn;
        SUIThreadCommand cmdOut;
        cmdIn.cmdId = UDC_UITHREADCMD;
        {
            // Following instruction very important in the function below tries to lock resources (or a plugin it
            // calls!):
            SIM_THREAD_INDICATE_UI_THREAD_CAN_DO_ANYTHING;
            GuiApp::uiThread->executeCommandViaUiThread(&cmdIn, &cmdOut);
        }
    }
    if (cmd.cmdId == PLUS_RG_CMD)
    {
        {
            SUIThreadCommand cmdIn;
            SUIThreadCommand cmdOut;
            cmdIn.cmdId = RG_UITHREADCMD;
            SIM_THREAD_INDICATE_UI_THREAD_CAN_DO_ANYTHING;
            GuiApp::uiThread->executeCommandViaUiThread(&cmdIn, &cmdOut);
        }
        int dl = CSimFlavor::getIntVal(5);
        if (dl > 0)
            appendSimulationThreadCommand(cmd, double(dl));
    }
    if (cmd.cmdId == PLUS_LR_CMD)
    {
        CSimFlavor::run(6);
    }
    if (cmd.cmdId == SET_SHAPE_TRANSPARENCY_CMD)
    {
        CShape* shape = App::currentWorld->sceneObjects->getShapeFromHandle(cmd.intParams[0]);
        if (shape != nullptr)
        {
            if (!shape->isCompound())
            {
                shape->getSingleMesh()->color.setTranslucid(cmd.boolParams[0]);
                shape->getSingleMesh()->color.setOpacity(cmd.doubleParams[0]);
                App::undoRedo_sceneChanged("");
            }
        }
    }
    if (cmd.cmdId == MAKE_OBJECT_CHILD_OF_CMD)
    {
        CSceneObject* child = App::currentWorld->sceneObjects->getObjectFromHandle(cmd.intParams[0]);
        CSceneObject* parent = App::currentWorld->sceneObjects->getObjectFromHandle(cmd.intParams[1]);
        if (child != nullptr)
        {
            App::currentWorld->sceneObjects->setObjectParent(child, parent, true);
            App::undoRedo_sceneChanged(""); // **************** UNDO THINGY ****************
        }
    }

    if ((cmd.cmdId > SCENE_OBJECT_OPERATION_START_SOOCMD) && (cmd.cmdId < SCENE_OBJECT_OPERATION_END_SOOCMD))
        CSceneObjectOperations::processCommand(cmd.cmdId);

    if ((cmd.cmdId >= UI_MODULE_MENU_CMDS_START) && (cmd.cmdId <= UI_MODULE_MENU_CMDS_END))
        App::worldContainer->addOnScriptContainer->processCommand(cmd.cmdId);

    if ((cmd.cmdId > PAGE_CONT_FUNCTIONS_START_PCCMD) && (cmd.cmdId < PAGE_CONT_FUNCTIONS_END_PCCMD))
        App::currentWorld->pageContainer->processCommand(cmd.cmdId, cmd.intParams[0]);

    if ((cmd.cmdId > FILE_OPERATION_START_FOCMD) && (cmd.cmdId < FILE_OPERATION_END_FOCMD))
        CFileOperations::processCommand(cmd);

    if ((cmd.cmdId > SIMULATION_COMMANDS_START_SCCMD) && (cmd.cmdId < SIMULATION_COMMANDS_END_SCCMD))
        App::currentWorld->simulation->processCommand(cmd.cmdId);

    if (cmd.cmdId == SET_SHAPE_SHADING_ANGLE_CMD)
    {
        CShape* shape = App::currentWorld->sceneObjects->getShapeFromHandle(cmd.intParams[0]);
        if ((shape != nullptr) && shape->getMesh()->isMesh())
            shape->getSingleMesh()->setShadingAngle(cmd.doubleParams[0]);
    }
    if (cmd.cmdId == SET_SHAPE_EDGE_ANGLE_CMD)
    {
        CShape* shape = App::currentWorld->sceneObjects->getShapeFromHandle(cmd.intParams[0]);
        if ((shape != nullptr) && shape->getMesh()->isMesh())
            shape->getSingleMesh()->setEdgeThresholdAngle(cmd.doubleParams[0]);
    }

    if (cmd.cmdId == TOGGLE_EXPAND_COLLAPSE_HIERARCHY_OBJECT_CMD)
    {
        CSceneObject* obj = App::currentWorld->sceneObjects->getObjectFromHandle(cmd.intParams[0]);
        if (obj != nullptr)
        {
            obj->setObjectProperty(obj->getObjectProperty() ^ sim_objectproperty_collapsed);
            App::undoRedo_sceneChanged("");
        }
    }
    if (cmd.cmdId == ADD_OR_REMOVE_TO_FROM_OBJECT_SELECTION_CMD)
    {
        for (size_t i = 0; i < cmd.intParams.size(); i++)
        {
            CSceneObject* obj = App::currentWorld->sceneObjects->getObjectFromHandle(cmd.intParams[i]);
            if (obj != nullptr)
            {
                if (cmd.boolParams[i])
                    App::currentWorld->sceneObjects->addObjectToSelection(cmd.intParams[i]);
                else
                    App::currentWorld->sceneObjects->removeObjectFromSelection(cmd.intParams[i]);
                App::undoRedo_sceneChanged("");
            }
        }
    }
    if (cmd.cmdId == CLICK_RAY_INTERSECTION_CMD_OLD)
        _handleClickRayIntersection_old(cmd);

    if (cmd.cmdId == SWAP_VIEWS_CMD)
    {
        CSPage* p = App::currentWorld->pageContainer->getPage(cmd.intParams[0]);
        if (p != nullptr)
        {
            p->swapViews(size_t(cmd.intParams[1]), size_t(cmd.intParams[2]), cmd.boolParams[0]);
            App::undoRedo_sceneChanged(""); // **************** UNDO THINGY ****************
        }
    }

    if (cmd.cmdId == CALL_MODULE_ENTRY_CMD)
    {
        CScriptObject* script = App::worldContainer->getScriptObjectFromHandle(cmd.intParams[0]);
        if (script != nullptr)
        {
            CInterfaceStack* inStack = App::worldContainer->interfaceStackContainer->createStack();
            inStack->pushTableOntoStack();
            inStack->pushTextOntoStack("handle");
            inStack->pushInt32OntoStack(cmd.intParams[1]);
            inStack->insertDataIntoStackTable();
            script->systemCallScript(sim_syscb_moduleentry, inStack, nullptr);
            App::worldContainer->interfaceStackContainer->destroyStack(inStack);
            int data[4] = {cmd.intParams[1], 0, 0, 0};
            App::worldContainer->pluginContainer->sendEventCallbackMessageToAllPlugins(
                sim_message_eventcallback_moduleentry, data);
        }
    }

    if (cmd.cmdId == CALL_USER_CONFIG_CALLBACK_CMD)
    { // cmd.intParams[0] is an object handle
        CScriptObject* script = App::currentWorld->sceneObjects->getScriptObjectFromHandle(cmd.intParams[0]);
        if (script == nullptr)
            script = App::currentWorld->sceneObjects->embeddedScriptContainer->getScriptFromObjectAttachedTo(sim_scripttype_customization, cmd.intParams[0]);
        if ((script != nullptr) && (script->hasSystemFunctionOrHook(sim_syscb_userconfig)))
        { // we have a user config callback
            script->systemCallScript(sim_syscb_userconfig, nullptr, nullptr);
        }
        else
        {
            SUIThreadCommand cmdIn;
            SUIThreadCommand cmdOut;
            cmdIn.cmdId = OPEN_MODAL_SCRIPT_SIMULATION_PARAMETERS_UITHREADCMD;
            cmdIn.intParams.push_back(cmd.intParams[0]);
            // Make sure we have a script param object:
            CSceneObject* object = App::currentWorld->sceneObjects->getObjectFromHandle(cmd.intParams[0]);
            if (object->getUserScriptParameterObject() == nullptr)
                object->setUserScriptParameterObject(new CUserParameters());
            {
                // Following instruction very important in the function below tries to lock resources (or a plugin it
                // calls!):
                SIM_THREAD_INDICATE_UI_THREAD_CAN_DO_ANYTHING;
                GuiApp::uiThread->executeCommandViaUiThread(&cmdIn, &cmdOut);
            }
        }
    }
    if (cmd.cmdId == OPEN_SCRIPT_EDITOR_CMD)
    {
        if ((GuiApp::getEditModeType() == NO_EDIT_MODE) && (GuiApp::mainWindow != nullptr))
        {
            CScriptObject* it = App::currentWorld->getScriptObjectFromHandle(cmd.intParams[0]);
            if (it != nullptr)
            {
                if (it->getScriptType() == sim_scripttype_customization)
                    GuiApp::mainWindow->codeEditorContainer->openCustomizationScript(cmd.intParams[0]);
                else
                    GuiApp::mainWindow->codeEditorContainer->openSimulationScript(cmd.intParams[0]);
            }
        }
    }

    if (cmd.cmdId == OPEN_MODAL_MODEL_PROPERTIES_CMD)
    {
        if (GuiApp::getEditModeType() == NO_EDIT_MODE)
        {
            SUIThreadCommand cmdIn;
            SUIThreadCommand cmdOut;
            cmdIn.cmdId = OPEN_MODAL_MODEL_PROPERTIES_UITHREADCMD;
            cmdIn.intParams.push_back(cmd.intParams[0]);
            {
                // Following instruction very important in the function below tries to lock resources (or a plugin it
                // calls!):
                SIM_THREAD_INDICATE_UI_THREAD_CAN_DO_ANYTHING;
                GuiApp::uiThread->executeCommandViaUiThread(&cmdIn, &cmdOut);
            }
            App::undoRedo_sceneChanged(""); // **************** UNDO THINGY ****************
            GuiApp::setFullDialogRefreshFlag();
        }
    }

    if (cmd.cmdId == CLOSE_FLOATING_VIEW_CMD)
    {
        CSPage* page =
            App::currentWorld->pageContainer->getPage(App::currentWorld->pageContainer->getActivePageIndex());
        if (page != nullptr)
        {
            CSView* theFloatingView = page->getView(size_t(cmd.intParams[0]));
            if (theFloatingView != nullptr)
            {
                if (theFloatingView->getCanBeClosed())
                {
                    page->removeFloatingView(size_t(cmd.intParams[0]));
                    App::undoRedo_sceneChanged("");
                }
            }
        }
    }

    if (cmd.cmdId == REMOVE_CURRENT_PAGE_CMD)
    {
        App::currentWorld->pageContainer->removePage(App::currentWorld->pageContainer->getActivePageIndex());
        App::logMsg(sim_verbosity_msgs, IDSNS_REMOVED_VIEW);
        App::undoRedo_sceneChanged("");
    }

    // Edit mode commands:
    if ((GuiApp::mainWindow != nullptr) && (cmd.cmdId > EDIT_MODE_COMMANDS_START_EMCMD) &&
        (cmd.cmdId < EDIT_MODE_COMMANDS_END_EMCMD))
    {
        CSceneObject* additionalSceneObject = nullptr;
        if (cmd.cmdId == PATH_EDIT_MODE_OLD_APPEND_NEW_PATH_POINT_FROM_CAMERA_EMCMD)
        {
            additionalSceneObject = (CSceneObject*)cmd.objectParams[0];
            if (additionalSceneObject != nullptr)
            { // make sure that object is still valid:
                if (!App::currentWorld->sceneObjects->doesObjectExist(additionalSceneObject))
                    additionalSceneObject = nullptr;
            }
        }
        GuiApp::mainWindow->editModeContainer->processCommand(cmd.cmdId, additionalSceneObject);
    }

    if (cmd.cmdId == DISPLAY_MESSAGE_CMD)
    {
        if (GuiApp::mainWindow != nullptr)
        {
            if (cmd.intParams[0] == sim_msgbox_type_info)
                GuiApp::uiThread->messageBox_information(GuiApp::mainWindow, cmd.stringParams[0].c_str(),
                                                         cmd.stringParams[1].c_str(), VMESSAGEBOX_OKELI,
                                                         VMESSAGEBOX_REPLY_OK);
            if (cmd.intParams[0] == sim_msgbox_type_warning)
                GuiApp::uiThread->messageBox_warning(GuiApp::mainWindow, cmd.stringParams[0].c_str(),
                                                     cmd.stringParams[1].c_str(), VMESSAGEBOX_OKELI,
                                                     VMESSAGEBOX_REPLY_OK);
            if (cmd.intParams[0] == sim_msgbox_type_critical)
                GuiApp::uiThread->messageBox_critical(GuiApp::mainWindow, cmd.stringParams[0].c_str(),
                                                      cmd.stringParams[1].c_str(), VMESSAGEBOX_OKELI,
                                                      VMESSAGEBOX_REPLY_OK);
        }
    }

    if ((cmd.cmdId > ADD_COMMANDS_START_ACCMD) && (cmd.cmdId < ADD_COMMANDS_END_ACCMD))
    {
        CSView* subview = nullptr;
        if (cmd.objectParams.size() > 0)
        {
            subview = (CSView*)cmd.objectParams[0];
            if (subview != nullptr)
            { // make sure that object is still valid:
                CSPage* page =
                    App::currentWorld->pageContainer->getPage(App::currentWorld->pageContainer->getActivePageIndex());
                if (!page->isViewValid(subview))
                    subview = nullptr;
            }
        }
        CAddOperations::processCommand(cmd.cmdId, subview);
    }

    if (cmd.cmdId == CAMERA_SHIFT_TO_FRAME_SELECTION_CMD)
        CToolBarCommand::processCommand(cmd.cmdId);
    if (cmd.cmdId == CAMERA_SHIFT_NAVIGATION_CMD)
        CToolBarCommand::processCommand(cmd.cmdId);
    if (cmd.cmdId == CAMERA_ROTATE_NAVIGATION_CMD)
        CToolBarCommand::processCommand(cmd.cmdId);
    if (cmd.cmdId == CAMERA_ZOOM_NAVIGATION_CMD)
        CToolBarCommand::processCommand(cmd.cmdId);
    if (cmd.cmdId == CAMERA_ANGLE_NAVIGATION_CMD)
        CToolBarCommand::processCommand(cmd.cmdId);
    if (cmd.cmdId == OBJECT_SHIFT_NAVIGATION_CMD)
        CToolBarCommand::processCommand(cmd.cmdId);
    if (cmd.cmdId == OBJECT_ROTATE_NAVIGATION_CMD)
        CToolBarCommand::processCommand(cmd.cmdId);
    if (cmd.cmdId == PAGE_SELECTOR_CMD)
        CToolBarCommand::processCommand(cmd.cmdId);
    if (cmd.cmdId == OBJECT_SELECTION_SELECTION_CMD)
        CToolBarCommand::processCommand(cmd.cmdId);
    if (cmd.cmdId == PATH_POINT_CREATION_MODE_CMD)
        CToolBarCommand::processCommand(cmd.cmdId);
    if (cmd.cmdId == CLEAR_SELECTION_SELECTION_CMD)
        CToolBarCommand::processCommand(cmd.cmdId);
    if ((cmd.cmdId >= VIEW_1_CMD) && (cmd.cmdId <= VIEW_8_CMD))
        CToolBarCommand::processCommand(cmd.cmdId);

    if (GuiApp::mainWindow != nullptr)
    {
        if ((cmd.cmdId == EXPAND_HIERARCHY_CMD) || (cmd.cmdId == COLLAPSE_HIERARCHY_CMD))
            GuiApp::mainWindow->oglSurface->hierarchy->processCommand(cmd.cmdId);
        if ((cmd.cmdId == EXPAND_SELECTED_HIERARCHY_CMD) || (cmd.cmdId == COLLAPSE_SELECTED_HIERARCHY_CMD))
            GuiApp::mainWindow->oglSurface->hierarchy->processCommand(cmd.cmdId);
        if ((cmd.cmdId >= HIERARCHY_COLORING_NONE_CMD) && (cmd.cmdId <= HIERARCHY_COLORING_BLUE_CMD))
            GuiApp::mainWindow->oglSurface->hierarchy->processCommand(cmd.cmdId);
        if ((cmd.cmdId == MOVE_UP_HIERARCHY_CMD) || (cmd.cmdId == MOVE_DOWN_HIERARCHY_CMD))
            GuiApp::mainWindow->oglSurface->hierarchy->processCommand(cmd.cmdId);
    }

    if (cmd.cmdId == DISPLAY_WARNING_IF_DEBUGGING_CMD)
    {
        if ((App::getConsoleVerbosity() >= sim_verbosity_trace) && (!App::userSettings->suppressStartupDialogs))
            GuiApp::uiThread->messageBox_information(
                GuiApp::mainWindow, "Tracing", "Tracing is turned on: this might lead to drastic performance loss.",
                VMESSAGEBOX_OKELI, VMESSAGEBOX_REPLY_OK);
    }

    if (cmd.cmdId == RESTART_SCRIPT_CMD)
    {
        CScriptObject* it = App::worldContainer->getScriptObjectFromHandle(cmd.intParams[0]);
        if ((it != nullptr) && it->resetScript())
        {
            std::string msg(it->getDescriptiveName());
            msg += " was reset.";
            App::logMsg(sim_verbosity_msgs, msg.c_str());
        }
    }

    if ((cmd.cmdId > VIEW_FUNCTIONS_START_VFCMD) && (cmd.cmdId < VIEW_FUNCTIONS_END_VFCMD))
    {
        CSPage* page =
            App::currentWorld->pageContainer->getPage(App::currentWorld->pageContainer->getActivePageIndex());
        if (page != nullptr)
        {
            CSView* view = page->getView(size_t(cmd.intParams[0]));
            if (view != nullptr)
                view->processCommand(cmd.cmdId, cmd.intParams[0]);
        }
    }

    if ((cmd.cmdId > VIEW_SELECTOR_START_VSCMD) && (cmd.cmdId < VIEW_SELECTOR_END_VSCMD))
        GuiApp::mainWindow->oglSurface->viewSelector->processCommand(cmd.cmdId, cmd.intParams[0]);

    if (cmd.cmdId == MODEL_BROWSER_DRAG_AND_DROP_CMD)
    {
        std::string infoStr;
        std::string errorStr;
        if (CFileOperations::loadModel(cmd.stringParams[0].c_str(), false, false, nullptr, false, false, &infoStr, &errorStr))
        {
            GuiApp::setRebuildHierarchyFlag();
            if (infoStr.size() > 0)
                App::logMsg(sim_verbosity_msgs, infoStr.c_str());
            App::logMsg(sim_verbosity_msgs, IDSNS_MODEL_LOADED);
            if (App::currentWorld->sceneObjects->getSelectionCount() == 1)
            { // we could have several model bases (in the old fileformat)
                CSceneObject* obj = App::currentWorld->sceneObjects->getLastSelectionObject();
                if (obj != nullptr)
                {
                    if (cmd.intParams[0] >= 0)
                    {
                        CSceneObject* parent(App::currentWorld->sceneObjects->getObjectFromHandle(cmd.intParams[0]));
                        if (parent != nullptr)
                        {
                            if (!App::assemble(parent->getObjectHandle(), obj->getObjectHandle(), false, false))
                            { // failed to assemble. We just parent it and set its local pose to zero
                                App::currentWorld->sceneObjects->setObjectParent(obj, parent, true);
                                obj->setLocalTransformation(C7Vector::identityTransformation);
                            }
                            parent->setObjectProperty((parent->getObjectProperty() | sim_objectproperty_collapsed) - sim_objectproperty_collapsed);
                        }
                    }
                    else
                    {
                        C7Vector tr(obj->getFullLocalTransformation());
                        double ss = obj->getObjectMovementStepSize(0);
                        if (ss == 0.0)
                            ss = App::userSettings->getTranslationStepSize();
                        double x = cmd.doubleParams[0] - fmod(cmd.doubleParams[0], ss);
                        double y = cmd.doubleParams[1] - fmod(cmd.doubleParams[1], ss);
                        tr.X(0) += x;
                        tr.X(1) += y;
                        obj->setLocalTransformation(tr);
                    }
                }
            }
            GuiApp::mainWindow->openglWidget->clearModelDragAndDropInfo();
            App::undoRedo_sceneChanged("");
        }
        else
        {
            if (infoStr.size() > 0)
                App::logMsg(sim_verbosity_msgs, infoStr.c_str());
            App::logMsg(sim_verbosity_errors, errorStr.c_str());
        }
    }

    if (cmd.cmdId == DISPLAY_VARIOUS_WARNING_MESSAGES_DURING_SIMULATION_CMD)
    {
        if ((!App::currentWorld->simulation->isSimulationStopped()) && GuiApp::canShowDialogs())
        {
            App::currentWorld->dynamicsContainer->displayWarningsIfNeeded();
            App::appendSimulationThreadCommand(cmd, 0.5);
        }
    }

    if (cmd.cmdId == DRAGENTER_GUITRIGGEREDCMD)
    {
        CInterfaceStack* stack = App::worldContainer->interfaceStackContainer->createStack();
        stack->pushTableOntoStack();
        stack->insertKeyTextIntoStackTable("id", "dragEnterEvent");
        stack->pushTextOntoStack("data");
        stack->pushTableOntoStack();
        stack->insertKeyTextIntoStackTable("mimeText", cmd.stringParams[0].c_str());
        stack->insertDataIntoStackTable();
        stack->pushInt32OntoStack(-1, false);
        App::worldContainer->broadcastMsg(stack, -1, 0);
        App::worldContainer->interfaceStackContainer->destroyStack(stack);
    }
    if (cmd.cmdId == DRAGLEAVE_GUITRIGGEREDCMD)
    {
        CInterfaceStack* stack = App::worldContainer->interfaceStackContainer->createStack();
        stack->pushTableOntoStack();
        stack->insertKeyTextIntoStackTable("id", "dragLeaveEvent");
        stack->pushTextOntoStack("data");
        stack->pushTableOntoStack();
        stack->insertKeyTextIntoStackTable("mimeText", cmd.stringParams[0].c_str());
        stack->insertDataIntoStackTable();
        stack->pushInt32OntoStack(-1, false);
        App::worldContainer->broadcastMsg(stack, -1, 0);
        App::worldContainer->interfaceStackContainer->destroyStack(stack);
    }
    if (cmd.cmdId == DRAGDROP_GUITRIGGEREDCMD)
    {
        CInterfaceStack* stack = App::worldContainer->interfaceStackContainer->createStack();
        stack->pushTableOntoStack();
        stack->insertKeyTextIntoStackTable("id", "dragDropEvent");
        stack->pushTextOntoStack("data");
        stack->pushTableOntoStack();
        stack->insertKeyTextIntoStackTable("mimeText", cmd.stringParams[0].c_str());
        stack->insertDataIntoStackTable();
        stack->pushInt32OntoStack(-1, false);
        App::worldContainer->broadcastMsg(stack, -1, 0);
        App::worldContainer->interfaceStackContainer->destroyStack(stack);
    }

    if (cmd.cmdId == SELECT_RENDERER_CMD)
    {
        App::worldContainer->pluginContainer->selectExtRenderer(cmd.intParams[0]);
    }

    if (cmd.cmdId == SET_VIEW_ANGLE_CAMERAGUITRIGGEREDCMD)
    {
        CCamera* cam = App::currentWorld->sceneObjects->getCameraFromHandle(cmd.intParams[0]);
        if (cam != nullptr)
            cam->setViewAngle(cmd.doubleParams[0]);
    }
    if (cmd.cmdId == SET_ORTHO_VIEW_SIZE_CAMERAGUITRIGGEREDCMD)
    {
        CCamera* cam = App::currentWorld->sceneObjects->getCameraFromHandle(cmd.intParams[0]);
        if (cam != nullptr)
            cam->setOrthoViewSize(cmd.doubleParams[0]);
    }
    if (cmd.cmdId == SET_NEAR_CLIPPING_CAMERAGUITRIGGEREDCMD)
    {
        CCamera* cam = App::currentWorld->sceneObjects->getCameraFromHandle(cmd.intParams[0]);
        if (cam != nullptr)
        {
            double np, fp;
            cam->getClippingPlanes(np, fp);
            cam->setClippingPlanes(cmd.doubleParams[0], fp);
        }
    }
    if (cmd.cmdId == SET_FAR_CLIPPING_CAMERAGUITRIGGEREDCMD)
    {
        CCamera* cam = App::currentWorld->sceneObjects->getCameraFromHandle(cmd.intParams[0]);
        if (cam != nullptr)
        {
            double np, fp;
            cam->getClippingPlanes(np, fp);
            cam->setClippingPlanes(np, cmd.doubleParams[0]);
        }
    }
    if (cmd.cmdId == SET_TRACKED_OBJECT_CAMERAGUITRIGGEREDCMD)
    {
        CCamera* cam = App::currentWorld->sceneObjects->getCameraFromHandle(cmd.intParams[0]);
        if (cam != nullptr)
        {
            if (cmd.intParams[1] < 0)
                cam->setTrackedObjectHandle(-1);
            else
            {
                CSceneObject* obj = App::currentWorld->sceneObjects->getObjectFromHandle(cmd.intParams[1]);
                if (obj != nullptr)
                    cam->setTrackedObjectHandle(obj->getObjectHandle());
            }
        }
    }
    if (cmd.cmdId == TOGGLE_SHOWFOG_CAMERAGUITRIGGEREDCMD)
    {
        CCamera* cam = App::currentWorld->sceneObjects->getCameraFromHandle(cmd.intParams[0]);
        if (cam != nullptr)
            cam->setHideFog(!cam->getHideFog());
    }
    if (cmd.cmdId == TOGGLE_SHOWVOLUME_CAMERAGUITRIGGEREDCMD)
    {
        CCamera* cam = App::currentWorld->sceneObjects->getCameraFromHandle(cmd.intParams[0]);
        if (cam != nullptr)
            cam->setShowVolume(!cam->getShowVolume());
    }
    if (cmd.cmdId == TOGGLE_USEPARENTASMANIPPROXY_CAMERAGUITRIGGEREDCMD)
    {
        CCamera* cam = App::currentWorld->sceneObjects->getCameraFromHandle(cmd.intParams[0]);
        if (cam != nullptr)
            cam->setUseParentObjectAsManipulationProxy(!cam->getUseParentObjectAsManipulationProxy());
    }
    if (cmd.cmdId == TOGGLE_ALLOWTRANSLATION_CAMERAGUITRIGGEREDCMD)
    {
        CCamera* cam = App::currentWorld->sceneObjects->getCameraFromHandle(cmd.intParams[0]);
        if (cam != nullptr)
            cam->setAllowTranslation(!cam->getAllowTranslation());
    }
    if (cmd.cmdId == TOGGLE_ALLOWROTATION_CAMERAGUITRIGGEREDCMD)
    {
        CCamera* cam = App::currentWorld->sceneObjects->getCameraFromHandle(cmd.intParams[0]);
        if (cam != nullptr)
            cam->setAllowRotation(!cam->getAllowRotation());
    }
    if (cmd.cmdId == SET_SIZE_CAMERAGUITRIGGEREDCMD)
    {
        CCamera* cam = App::currentWorld->sceneObjects->getCameraFromHandle(cmd.intParams[0]);
        if (cam != nullptr)
            cam->setCameraSize(cmd.doubleParams[0]);
    }
    if (cmd.cmdId == TOGGLE_LOCALLIGHTS_CAMERAGUITRIGGEREDCMD)
    {
        CCamera* cam = App::currentWorld->sceneObjects->getCameraFromHandle(cmd.intParams[0]);
        if (cam != nullptr)
            cam->setUseLocalLights(!cam->getuseLocalLights());
    }
    if (cmd.cmdId == TOGGLE_ALLOWPICKING_CAMERAGUITRIGGEREDCMD)
    {
        CCamera* cam = App::currentWorld->sceneObjects->getCameraFromHandle(cmd.intParams[0]);
        if (cam != nullptr)
            cam->setAllowPicking(!cam->getAllowPicking());
    }
    if (cmd.cmdId == SET_RENDERMODE_CAMERAGUITRIGGEREDCMD)
    {
        CCamera* cam = App::currentWorld->sceneObjects->getCameraFromHandle(cmd.intParams[0]);
        if (cam != nullptr)
            cam->setRenderMode(cmd.intParams[1], cmd.boolParams[0], cmd.boolParams[1]);
    }
    if (cmd.cmdId == NEW_COLLECTION_COLLECTIONGUITRIGGEREDCMD)
    {
        CCollection* newGroup = new CCollection(-2);
        newGroup->setCollectionName(IDSOGL_COLLECTION, false);
        App::currentWorld->collections->addCollection(newGroup, false);
        // Now select the new collection in the UI. We need to post it so that it arrives after the dialog refresh!:
        SSimulationThreadCommand cmd2;
        cmd2.cmdId = CALL_DIALOG_FUNCTION_GUITRIGGEREDCMD;
        cmd2.intParams.push_back(COLLECTION_DLG);
        cmd2.intParams.push_back(0);
        cmd2.intParams.push_back(newGroup->getCollectionHandle());
        App::appendSimulationThreadCommand(cmd2);
    }
    if (cmd.cmdId == TOGGLE_OVERRIDE_COLLECTIONGUITRIGGEREDCMD)
    {
        CCollection* theGroup = App::currentWorld->collections->getObjectFromHandle(cmd.intParams[0]);
        if (theGroup != nullptr)
            theGroup->setOverridesObjectMainProperties(!theGroup->getOverridesObjectMainProperties());
    }
    if (cmd.cmdId == REMOVE_COLLECTION_COLLECTIONGUITRIGGEREDCMD)
    {
        App::currentWorld->collections->removeCollection(cmd.intParams[0]);
    }
    if (cmd.cmdId == REMOVE_COLLECTION_ITEM_COLLECTIONGUITRIGGEREDCMD)
    {
        CCollection* theGroup = App::currentWorld->collections->getObjectFromHandle(cmd.intParams[0]);
        if (theGroup != nullptr)
        {
            for (size_t i = 1; i < cmd.intParams.size(); i++)
                theGroup->removeCollectionElementFromHandle(cmd.intParams[i]);
            if (theGroup->getElementCount() == 0)
            { // The group is empty and we have to remove it
                App::currentWorld->collections->removeCollection(theGroup->getCollectionHandle());
            }
        }
    }
    if (cmd.cmdId == RENAME_COLLECTION_COLLECTIONGUITRIGGEREDCMD)
    {
        CCollection* it = App::currentWorld->collections->getObjectFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setCollectionName(cmd.stringParams[0].c_str(), true);
    }
    if (cmd.cmdId == ADD_COLLECTION_ITEM_EVERYTHING_COLLECTIONGUITRIGGEREDCMD)
    {
        CCollection* it = App::currentWorld->collections->getObjectFromHandle(cmd.intParams[0]);
        if (it != nullptr)
        {
            CCollectionElement* grEl = new CCollectionElement(-1, sim_collectionelement_all, true);
            it->addCollectionElement(grEl);
        }
    }
    if (cmd.cmdId == ADD_COLLECTION_ITEM_LOOS_COLLECTIONGUITRIGGEREDCMD)
    {
        CCollection* it = App::currentWorld->collections->getObjectFromHandle(cmd.intParams[0]);
        bool additive = cmd.boolParams[0];
        if (it != nullptr)
        {
            for (size_t i = 1; i < cmd.intParams.size(); i++)
            {
                CSceneObject* obj = App::currentWorld->sceneObjects->getObjectFromHandle(cmd.intParams[i]);
                if (obj != nullptr)
                {
                    CCollectionElement* grEl =
                        new CCollectionElement(obj->getObjectHandle(), sim_collectionelement_loose, additive);
                    it->addCollectionElement(grEl);
                }
            }
        }
    }
    if (cmd.cmdId == ADD_COLLECTION_ITEM_FROMBASE_COLLECTIONGUITRIGGEREDCMD)
    {
        CCollection* it = App::currentWorld->collections->getObjectFromHandle(cmd.intParams[0]);
        bool additive = cmd.boolParams[0];
        bool baseInclusive = cmd.boolParams[1];
        if (it != nullptr)
        {
            CSceneObject* lastSel = App::currentWorld->sceneObjects->getObjectFromHandle(cmd.intParams[1]);
            if (lastSel != nullptr)
            {
                int grpType = sim_collectionelement_frombaseincluded;
                if (!baseInclusive)
                    grpType = sim_collectionelement_frombaseexcluded;
                CCollectionElement* grEl = new CCollectionElement(lastSel->getObjectHandle(), grpType, additive);
                it->addCollectionElement(grEl);
            }
        }
    }
    if (cmd.cmdId == ADD_COLLECTION_ITEM_FROMTIP_COLLECTIONGUITRIGGEREDCMD)
    {
        CCollection* it = App::currentWorld->collections->getObjectFromHandle(cmd.intParams[0]);
        bool additive = cmd.boolParams[0];
        bool tipInclusive = cmd.boolParams[1];
        if (it != nullptr)
        {
            CSceneObject* lastSel = App::currentWorld->sceneObjects->getObjectFromHandle(cmd.intParams[1]);
            if (lastSel != nullptr)
            {
                int grpType = sim_collectionelement_fromtipincluded;
                if (!tipInclusive)
                    grpType = sim_collectionelement_fromtipexcluded;
                CCollectionElement* grEl = new CCollectionElement(lastSel->getObjectHandle(), grpType, additive);
                it->addCollectionElement(grEl);
            }
        }
    }

    if (cmd.cmdId == TOGGLE_EXPLICITHANDLING_VISIONSENSORGUITRIGGEREDCMD)
    {
        CVisionSensor* it = App::currentWorld->sceneObjects->getVisionSensorFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setExplicitHandling(!it->getExplicitHandling());
    }
    if (cmd.cmdId == TOGGLE_EXTERNALINPUT_VISIONSENSORGUITRIGGEREDCMD)
    {
        CVisionSensor* it = App::currentWorld->sceneObjects->getVisionSensorFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setUseExternalImage(!it->getUseExternalImage());
    }
    if (cmd.cmdId == TOGGLE_LOCALLIGHTS_VISIONSENSORGUITRIGGEREDCMD)
    {
        CVisionSensor* it = App::currentWorld->sceneObjects->getVisionSensorFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setUseLocalLights(!it->getuseLocalLights());
    }
    if (cmd.cmdId == TOGGLE_SHOWVOLUME_VISIONSENSORGUITRIGGEREDCMD)
    {
        CVisionSensor* it = App::currentWorld->sceneObjects->getVisionSensorFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setShowVolume(!it->getShowVolume());
    }
    if (cmd.cmdId == TOGGLE_SHOWFOG_VISIONSENSORGUITRIGGEREDCMD)
    {
        CVisionSensor* it = App::currentWorld->sceneObjects->getVisionSensorFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setHideFog(!it->getHideFog());
    }
    if (cmd.cmdId == SET_NEARCLIPPING_VISIONSENSORGUITRIGGEREDCMD)
    {
        CVisionSensor* it = App::currentWorld->sceneObjects->getVisionSensorFromHandle(cmd.intParams[0]);
        if (it != nullptr)
        {
            double np, fp;
            it->getClippingPlanes(np, fp);
            it->setClippingPlanes(cmd.doubleParams[0], fp);
        }
    }
    if (cmd.cmdId == SET_FARCLIPPING_VISIONSENSORGUITRIGGEREDCMD)
    {
        CVisionSensor* it = App::currentWorld->sceneObjects->getVisionSensorFromHandle(cmd.intParams[0]);
        if (it != nullptr)
        {
            double np, fp;
            it->getClippingPlanes(np, fp);
            it->setClippingPlanes(np, cmd.doubleParams[0]);
        }
    }
    if (cmd.cmdId == SET_PERSPECTANGLE_OR_ORTHOSIZE_VISIONSENSORGUITRIGGEREDCMD)
    {
        CVisionSensor* it = App::currentWorld->sceneObjects->getVisionSensorFromHandle(cmd.intParams[0]);
        if (it != nullptr)
        {
            if (it->getPerspective())
                it->setViewAngle(cmd.doubleParams[0]);
            else
                it->setOrthoViewSize(cmd.doubleParams[0]);
        }
    }
    if (cmd.cmdId == SET_RESOLUTION_VISIONSENSORGUITRIGGEREDCMD)
    {
        CVisionSensor* it = App::currentWorld->sceneObjects->getVisionSensorFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setResolution(&cmd.intParams[1]);
    }
    if (cmd.cmdId == SET_OBJECTSIZE_VISIONSENSORGUITRIGGEREDCMD)
    {
        CVisionSensor* it = App::currentWorld->sceneObjects->getVisionSensorFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setVisionSensorSize(cmd.doubleParams[0]);
    }
    if (cmd.cmdId == SET_DEFAULTIMGCOL_VISIONSENSORGUITRIGGEREDCMD)
    {
        CVisionSensor* it = App::currentWorld->sceneObjects->getVisionSensorFromHandle(cmd.intParams[0]);
        if (it != nullptr)
        {
            float w[3] = {(float)cmd.doubleParams[0], (float)cmd.doubleParams[1], (float)cmd.doubleParams[2]};
            it->setDefaultBufferValues(w);
            it->setUseEnvironmentBackgroundColor(cmd.boolParams[0]);
        }
    }
    if (cmd.cmdId == APPLY_MAINPROP_TO_SELECTION_VISIONSENSORGUITRIGGEREDCMD)
    {
        CVisionSensor* last = App::currentWorld->sceneObjects->getVisionSensorFromHandle(cmd.intParams[0]);
        if (last != nullptr)
        {
            int r[2];
            last->getResolution(r);
            float b[3];
            last->getDefaultBufferValues(b);
            for (size_t i = 1; i < cmd.intParams.size(); i++)
            {
                CVisionSensor* it = App::currentWorld->sceneObjects->getVisionSensorFromHandle(cmd.intParams[i]);
                if (it != nullptr)
                {
                    it->setRenderMode(last->getRenderMode());
                    it->setExplicitHandling(last->getExplicitHandling());
                    it->setUseExternalImage(last->getUseExternalImage());
                    it->setPerspective(last->getPerspective());
                    it->setHideFog(last->getHideFog());
                    it->setIgnoreRGBInfo(last->getIgnoreRGBInfo());
                    it->setIgnoreDepthInfo(last->getIgnoreDepthInfo());
                    it->setComputeImageBasicStats(last->getComputeImageBasicStats());
                    double np, fp;
                    last->getClippingPlanes(np, fp);
                    it->setClippingPlanes(np, fp);
                    it->setViewAngle(last->getViewAngle());
                    it->setOrthoViewSize(last->getOrthoViewSize());
                    it->setResolution(r);
                    it->setUseLocalLights(last->getuseLocalLights());
                    it->setUseEnvironmentBackgroundColor(last->getUseEnvironmentBackgroundColor());
                    it->setDefaultBufferValues(b);
                    it->setDetectableEntityHandle(last->getDetectableEntityHandle());
                }
            }
        }
    }
    if (cmd.cmdId == APPLY_VISUALPROP_TO_SELECTION_VISIONSENSORGUITRIGGEREDCMD)
    {
        CVisionSensor* last = App::currentWorld->sceneObjects->getVisionSensorFromHandle(cmd.intParams[0]);
        if (last != nullptr)
        {
            for (size_t i = 1; i < cmd.intParams.size(); i++)
            {
                CVisionSensor* it = App::currentWorld->sceneObjects->getVisionSensorFromHandle(cmd.intParams[i]);
                if (it != nullptr)
                {
                    last->getColor()->copyYourselfInto(it->getColor());
                    it->setVisionSensorSize(last->getVisionSensorSize());
                    it->setShowVolume(last->getShowVolume());
                }
            }
        }
    }
    if (cmd.cmdId == TOGGLE_IGNORERGB_VISIONSENSORGUITRIGGEREDCMD)
    {
        CVisionSensor* it = App::currentWorld->sceneObjects->getVisionSensorFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setIgnoreRGBInfo(!it->getIgnoreRGBInfo());
    }
    if (cmd.cmdId == TOGGLE_IGNOREDEPTH_VISIONSENSORGUITRIGGEREDCMD)
    {
        CVisionSensor* it = App::currentWorld->sceneObjects->getVisionSensorFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setIgnoreDepthInfo(!it->getIgnoreDepthInfo());
    }
    if (cmd.cmdId == TOGGLE_PACKET1BLANK_VISIONSENSORGUITRIGGEREDCMD)
    {
        CVisionSensor* it = App::currentWorld->sceneObjects->getVisionSensorFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setComputeImageBasicStats(!it->getComputeImageBasicStats());
    }
    if (cmd.cmdId == SET_RENDERMODE_VISIONSENSORGUITRIGGEREDCMD)
    {
        CVisionSensor* it = App::currentWorld->sceneObjects->getVisionSensorFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setRenderMode(cmd.intParams[1]);
    }

    if (cmd.cmdId == ADD_NEW_COLLISIONGUITRIGGEREDCMD)
    {
        int h = App::currentWorld->collisions_old->addNewObject(cmd.intParams[0], cmd.intParams[1], "");
        // Now select the new collection in the UI. We need to post it so that it arrives after the dialog refresh!:
        SSimulationThreadCommand cmd2;
        cmd2.cmdId = CALL_DIALOG_FUNCTION_GUITRIGGEREDCMD;
        cmd2.intParams.push_back(COLLISION_DLG);
        cmd2.intParams.push_back(0);
        cmd2.intParams.push_back(h);
        App::appendSimulationThreadCommand(cmd2);
    }
    if (cmd.cmdId == SET_OBJECTNAME_COLLISIONGUITRIGGEREDCMD)
    {
        CCollisionObject_old* it = App::currentWorld->collisions_old->getObjectFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setObjectName(cmd.stringParams[0].c_str(), true);
    }
    if (cmd.cmdId == DELETE_OBJECT_COLLISIONGUITRIGGEREDCMD)
    {
        CCollisionObject_old* it = App::currentWorld->collisions_old->getObjectFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            App::currentWorld->collisions_old->removeObject(it->getObjectHandle());
    }
    if (cmd.cmdId == TOGGLE_ENABLE_ALL_COLLISIONGUITRIGGEREDCMD)
    {
        App::currentWorld->mainSettings_old->collisionDetectionEnabled =
            !App::currentWorld->mainSettings_old->collisionDetectionEnabled;
    }
    if (cmd.cmdId == TOGGLE_EXPLICITHANDLING_COLLISIONGUITRIGGEREDCMD)
    {
        CCollisionObject_old* it = App::currentWorld->collisions_old->getObjectFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setExplicitHandling(!it->getExplicitHandling());
    }
    if (cmd.cmdId == TOGGLE_COLLIDERCOLORCHANGES_COLLISIONGUITRIGGEREDCMD)
    {
        CCollisionObject_old* it = App::currentWorld->collisions_old->getObjectFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setColliderChangesColor(!it->getColliderChangesColor());
    }
    if (cmd.cmdId == TOGGLE_COLLIDEECOLORCHANGES_COLLISIONGUITRIGGEREDCMD)
    {
        CCollisionObject_old* it = App::currentWorld->collisions_old->getObjectFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setCollideeChangesColor(!it->getCollideeChangesColor());
    }
    if (cmd.cmdId == TOGGLE_COLLISIONCONTOUR_COLLISIONGUITRIGGEREDCMD)
    {
        CCollisionObject_old* it = App::currentWorld->collisions_old->getObjectFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setExhaustiveDetection(!it->getExhaustiveDetection());
    }
    if (cmd.cmdId == SET_CONTOURWIDTH_COLLISIONGUITRIGGEREDCMD)
    {
        CCollisionObject_old* it = App::currentWorld->collisions_old->getObjectFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setContourWidth(cmd.intParams[1]);
    }

    if (cmd.cmdId == ADD_NEW_DISTANCEGUITRIGGEREDCMD)
    {
        int h = App::currentWorld->distances_old->addNewObject(cmd.intParams[0], cmd.intParams[1], "");
        // Now select the new collection in the UI. We need to post it so that it arrives after the dialog refresh!:
        SSimulationThreadCommand cmd2;
        cmd2.cmdId = CALL_DIALOG_FUNCTION_GUITRIGGEREDCMD;
        cmd2.intParams.push_back(DISTANCE_DLG);
        cmd2.intParams.push_back(0);
        cmd2.intParams.push_back(h);
        App::appendSimulationThreadCommand(cmd2);
    }
    if (cmd.cmdId == SET_OBJECTNAME_DISTANCEGUITRIGGEREDCMD)
    {
        CDistanceObject_old* it = App::currentWorld->distances_old->getObjectFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setObjectName(cmd.stringParams[0].c_str(), true);
    }
    if (cmd.cmdId == DELETE_OBJECT_DISTANCEGUITRIGGEREDCMD)
    {
        CDistanceObject_old* it = App::currentWorld->distances_old->getObjectFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            App::currentWorld->distances_old->removeObject(it->getObjectHandle());
    }
    if (cmd.cmdId == TOGGLE_ENABLE_ALL_DISTANCEGUITRIGGEREDCMD)
    {
        App::currentWorld->mainSettings_old->distanceCalculationEnabled =
            !App::currentWorld->mainSettings_old->distanceCalculationEnabled;
    }
    if (cmd.cmdId == TOGGLE_EXPLICITHANDLING_DISTANCEGUITRIGGEREDCMD)
    {
        CDistanceObject_old* it = App::currentWorld->distances_old->getObjectFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setExplicitHandling(!it->getExplicitHandling());
    }
    if (cmd.cmdId == TOGGLE_USETHRESHOLD_DISTANCEGUITRIGGEREDCMD)
    {
        CDistanceObject_old* it = App::currentWorld->distances_old->getObjectFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setThresholdEnabled(!it->getTreshholdEnabled());
    }
    if (cmd.cmdId == SET_THRESHOLD_DISTANCEGUITRIGGEREDCMD)
    {
        CDistanceObject_old* it = App::currentWorld->distances_old->getObjectFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setThreshold(cmd.doubleParams[0]);
    }
    if (cmd.cmdId == TOGGLE_SEGMENTDISPLAY_DISTANCEGUITRIGGEREDCMD)
    {
        CDistanceObject_old* it = App::currentWorld->distances_old->getObjectFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setDisplaySegment(!it->getDisplaySegment());
    }
    if (cmd.cmdId == SET_SEGMENTWIDTH_DISTANCEGUITRIGGEREDCMD)
    {
        CDistanceObject_old* it = App::currentWorld->distances_old->getObjectFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setSegmentWidth(cmd.doubleParams[0]);
    }

    if (cmd.cmdId == TOGGLE_SELECTABLE_COMMONPROPGUITRIGGEREDCMD)
    {
        CSceneObject* it = App::currentWorld->sceneObjects->getObjectFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setObjectProperty(it->getObjectProperty() ^ sim_objectproperty_selectable);
    }
    if (cmd.cmdId == TOGGLE_SELECTBASEOFMODEL_COMMONPROPGUITRIGGEREDCMD)
    {
        CSceneObject* it = App::currentWorld->sceneObjects->getObjectFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setObjectProperty(it->getObjectProperty() ^ sim_objectproperty_selectmodelbaseinstead);
    }
    if (cmd.cmdId == TOGGLE_DONGTSHOWINSIDEMODELSELECTION_COMMONPROPGUITRIGGEREDCMD)
    {
        CSceneObject* it = App::currentWorld->sceneObjects->getObjectFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setObjectProperty(it->getObjectProperty() ^ sim_objectproperty_dontshowasinsidemodel);
    }
    if (cmd.cmdId == TOGGLE_VIEWFITTINGIGNORED_COMMONPROPGUITRIGGEREDCMD)
    {
        CSceneObject* it = App::currentWorld->sceneObjects->getObjectFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setObjectProperty(it->getObjectProperty() ^ sim_objectproperty_ignoreviewfitting);
    }
    if (cmd.cmdId == APPLY_GENERALPROP_COMMONPROPGUITRIGGEREDCMD)
    {
        CSceneObject* last = App::currentWorld->sceneObjects->getObjectFromHandle(cmd.intParams[0]);
        if (last != nullptr)
        {
            int lastType = last->getObjectType();
            for (size_t i = 1; i < cmd.intParams.size(); i++)
            {
                CSceneObject* it = App::currentWorld->sceneObjects->getObjectFromHandle(cmd.intParams[i]);
                if (it != nullptr)
                {
                    int objPropToCopy = sim_objectproperty_selectable | sim_objectproperty_selectmodelbaseinstead |
                                        sim_objectproperty_dontshowasinsidemodel | sim_objectproperty_selectinvisible |
                                        sim_objectproperty_depthinvisible | sim_objectproperty_cannotdelete |
                                        sim_objectproperty_cannotdeleteduringsim;
                    it->setObjectProperty(((it->getObjectProperty() | objPropToCopy) - objPropToCopy) |
                                          (last->getObjectProperty() & objPropToCopy));
                    it->setSizeFactor(last->getSizeFactor());
                    if (it->getObjectType() == lastType)
                        it->setExtensionString(last->getExtensionString().c_str());
                }
            }
        }
    }
    if (cmd.cmdId == SET_CAMERAVISIBILITYLAYERS_COMMONPROPGUITRIGGEREDCMD)
    {
        CSceneObject* it = App::currentWorld->sceneObjects->getObjectFromHandle(cmd.intParams[0]);
        if (it != nullptr)
        {
            it->setVisibilityLayer(cmd.intParams[1]);
            // For backward compatibility: always renderable (now following the visibility layers as for cameras):
            if (it->isPotentiallyRenderable())
                it->setLocalObjectSpecialProperty(it->getLocalObjectSpecialProperty() |
                                                  sim_objectspecialproperty_renderable);
        }
    }
    if (cmd.cmdId == APPLY_VISIBILITYPROP_COMMONPROPGUITRIGGEREDCMD)
    {
        CSceneObject* last = App::currentWorld->sceneObjects->getObjectFromHandle(cmd.intParams[0]);
        if (last != nullptr)
        {
            for (size_t i = 1; i < cmd.intParams.size(); i++)
            {
                CSceneObject* it = App::currentWorld->sceneObjects->getObjectFromHandle(cmd.intParams[i]);
                if (it != nullptr)
                {
                    it->setVisibilityLayer(last->getVisibilityLayer());
                    it->setAuthorizedViewableObjects(last->getAuthorizedViewableObjects());
                }
            }
        }
    }
    if (cmd.cmdId == TOGGLE_MODELBASE_COMMONPROPGUITRIGGEREDCMD)
    {
        CSceneObject* it = App::currentWorld->sceneObjects->getObjectFromHandle(cmd.intParams[0]);
        if (it != nullptr)
        {
            it->setModelBase(!it->getModelBase());
            if (it->getModelBase())
                it->generateDnaString();
        }
    }
    if (cmd.cmdId == TOGGLE_COLLIDABLE_COMMONPROPGUITRIGGEREDCMD)
    {
        CSceneObject* it = App::currentWorld->sceneObjects->getObjectFromHandle(cmd.intParams[0]);
        if ((it != nullptr) && it->isPotentiallyCollidable())
            it->setLocalObjectSpecialProperty(it->getLocalObjectSpecialProperty() ^
                                              sim_objectspecialproperty_collidable);
    }
    if (cmd.cmdId == TOGGLE_MEASURABLE_COMMONPROPGUITRIGGEREDCMD)
    {
        CSceneObject* it = App::currentWorld->sceneObjects->getObjectFromHandle(cmd.intParams[0]);
        if ((it != nullptr) && it->isPotentiallyMeasurable())
            it->setLocalObjectSpecialProperty(it->getLocalObjectSpecialProperty() ^
                                              sim_objectspecialproperty_measurable);
    }
    if (cmd.cmdId == TOGGLE_RENDERABLE_COMMONPROPGUITRIGGEREDCMD)
    {
        CSceneObject* it = App::currentWorld->sceneObjects->getObjectFromHandle(cmd.intParams[0]);
        if ((it != nullptr) && it->isPotentiallyRenderable())
            it->setLocalObjectSpecialProperty(it->getLocalObjectSpecialProperty() ^
                                              sim_objectspecialproperty_renderable);
    }
    if (cmd.cmdId == TOGGLE_DETECTABLE_COMMONPROPGUITRIGGEREDCMD)
    {
        CSceneObject* it = App::currentWorld->sceneObjects->getObjectFromHandle(cmd.intParams[0]);
        if ((it != nullptr) && it->isPotentiallyDetectable())
        {
            int t = it->getLocalObjectSpecialProperty() & sim_objectspecialproperty_detectable;
            if (t == sim_objectspecialproperty_detectable)
            {
                t = it->getLocalObjectSpecialProperty() | sim_objectspecialproperty_detectable;
                t -= sim_objectspecialproperty_detectable;
            }
            else
                t = it->getLocalObjectSpecialProperty() | sim_objectspecialproperty_detectable;
            it->setLocalObjectSpecialProperty(t);
        }
    }
    if (cmd.cmdId == SET_DETECTABLEITEMS_COMMONPROPGUITRIGGEREDCMD)
    {
        CSceneObject* it = App::currentWorld->sceneObjects->getObjectFromHandle(cmd.intParams[0]);
        if ((it != nullptr) && it->isPotentiallyDetectable())
            it->setLocalObjectSpecialProperty(cmd.intParams[1]);
    }
    if (cmd.cmdId == APPLY_SPECIALPROP_COMMONPROPGUITRIGGEREDCMD)
    {
        CSceneObject* last = App::currentWorld->sceneObjects->getObjectFromHandle(cmd.intParams[0]);
        if (last != nullptr)
        {
            int settableBits = 0;
            if (last->isPotentiallyCollidable())
                settableBits |= sim_objectspecialproperty_collidable;
            if (last->isPotentiallyMeasurable())
                settableBits |= sim_objectspecialproperty_measurable;
            if (last->isPotentiallyDetectable())
                settableBits |= sim_objectspecialproperty_detectable;
            if (last->isPotentiallyRenderable())
                settableBits |= sim_objectspecialproperty_renderable;
            int stateOfSettableBits = last->getLocalObjectSpecialProperty() & settableBits;
            for (size_t i = 1; i < cmd.intParams.size(); i++)
            {
                CSceneObject* it = App::currentWorld->sceneObjects->getObjectFromHandle(cmd.intParams[i]);
                if (it != nullptr)
                {
                    int objProp =
                        ((it->getLocalObjectSpecialProperty() | settableBits) - settableBits) | stateOfSettableBits;
                    it->setLocalObjectSpecialProperty(objProp);
                }
            }
        }
    }
    if (cmd.cmdId == TOGGLE_SELECTINVISIBLE_COMMONPROPGUITRIGGEREDCMD)
    {
        CSceneObject* it = App::currentWorld->sceneObjects->getObjectFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setObjectProperty(it->getObjectProperty() ^ sim_objectproperty_selectinvisible);
    }
    if (cmd.cmdId == TOGGLE_DEPTHMAPIGNORED_COMMONPROPGUITRIGGEREDCMD)
    {
        CSceneObject* it = App::currentWorld->sceneObjects->getObjectFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setObjectProperty(it->getObjectProperty() ^ sim_objectproperty_depthinvisible);
    }
    if (cmd.cmdId == TOGGLE_CANNOTBEDELETED_COMMONPROPGUITRIGGEREDCMD)
    {
        CSceneObject* it = App::currentWorld->sceneObjects->getObjectFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setObjectProperty(it->getObjectProperty() ^ sim_objectproperty_cannotdelete);
    }
    if (cmd.cmdId == TOGGLE_CANNOTBEDELETEDDURINGSIMULATION_COMMONPROPGUITRIGGEREDCMD)
    {
        CSceneObject* it = App::currentWorld->sceneObjects->getObjectFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setObjectProperty(it->getObjectProperty() ^ sim_objectproperty_cannotdeleteduringsim);
    }
    if (cmd.cmdId == TOGGLE_HIDDENDURINGSIMULATION_COMMONPROPGUITRIGGEREDCMD)
    {
        CSceneObject* it = App::currentWorld->sceneObjects->getObjectFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setObjectProperty(it->getObjectProperty() ^ sim_objectproperty_hiddenforsimulation);
    }
    if (cmd.cmdId == TOGGLE_NOTMOVEABLE_COMMONPROPGUITRIGGEREDCMD)
    {
        CSceneObject* it = App::currentWorld->sceneObjects->getObjectFromHandle(cmd.intParams[0]);
        if (it != nullptr)
        {
            int p = it->getObjectMovementOptions();
            if ((p & 15) == 15)
                p -= 15;
            else
                p |= 15;
            it->setObjectMovementOptions(p);
        }
    }
    if (cmd.cmdId == SET_SELFCOLLISIONINDICATOR_COMMONPROPGUITRIGGEREDCMD)
    {
        CSceneObject* it = App::currentWorld->sceneObjects->getObjectFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setCollectionSelfCollisionIndicator(cmd.intParams[1]);
    }
    if (cmd.cmdId == SET_CANBESEENBY_COMMONPROPGUITRIGGEREDCMD)
    {
        CSceneObject* it = App::currentWorld->sceneObjects->getObjectFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setAuthorizedViewableObjects(cmd.intParams[1]);
    }
    if (cmd.cmdId == SET_EXTENSIONSTRING_COMMONPROPGUITRIGGEREDCMD)
    {
        CSceneObject* it = App::currentWorld->sceneObjects->getObjectFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setExtensionString(cmd.stringParams[0].c_str());
    }

    if (cmd.cmdId == SCALE_SCALINGGUITRIGGEREDCMD)
    {
        if (cmd.intParams.size() > 0)
        {
            CSceneObjectOperations::scaleObjects(cmd.intParams, cmd.doubleParams[0], !cmd.boolParams[0]);
            GuiApp::setFullDialogRefreshFlag();
        }
    }

    if (cmd.cmdId == SET_OVERRIDEPROPANDACKNOWLEDGMENT_MODELGUITRIGGEREDCMD)
    {
        CSceneObject* it = App::currentWorld->sceneObjects->getObjectFromHandle(cmd.intParams[0]);
        if (it != nullptr)
        {
            it->setModelProperty(cmd.intParams[1]);
            it->setModelAcknowledgement(cmd.stringParams[0].c_str());
        }
    }

    if (cmd.cmdId == SET_TIMESTEP_SIMULATIONGUITRIGGEREDCMD)
    {
        if (App::currentWorld->simulation->isSimulationStopped())
            App::currentWorld->simulation->setTimeStep(cmd.doubleParams[0]);
    }
    if (cmd.cmdId == SET_PPF_SIMULATIONGUITRIGGEREDCMD)
    {
        if (App::currentWorld->simulation->isSimulationStopped())
            App::currentWorld->simulation->setPassesPerRendering(cmd.intParams[0]);
    }
    if (cmd.cmdId == TOGGLE_REALTIME_SIMULATIONGUITRIGGEREDCMD)
    {
        if (App::currentWorld->simulation->isSimulationStopped())
            App::currentWorld->simulation->setIsRealTimeSimulation(
                !App::currentWorld->simulation->getIsRealTimeSimulation());
    }
    if (cmd.cmdId == SET_REALTIMEFACTOR_SIMULATIONGUITRIGGEREDCMD)
    {
        if (App::currentWorld->simulation->isSimulationStopped())
            App::currentWorld->simulation->setRealTimeCoeff(cmd.doubleParams[0]);
    }
    if (cmd.cmdId == TOGGLE_PAUSEATTIME_SIMULATIONGUITRIGGEREDCMD)
    {
        if (App::currentWorld->simulation->isSimulationStopped())
            App::currentWorld->simulation->setPauseAtSpecificTime(
                !App::currentWorld->simulation->getPauseAtSpecificTime());
    }
    if (cmd.cmdId == SET_PAUSETIME_SIMULATIONGUITRIGGEREDCMD)
    {
        if (App::currentWorld->simulation->isSimulationStopped())
            App::currentWorld->simulation->setPauseTime(cmd.doubleParams[0]);
    }
    if (cmd.cmdId == TOGGLE_PAUSEATERROR_SIMULATIONGUITRIGGEREDCMD)
    {
        if (App::currentWorld->simulation->isSimulationStopped())
            App::currentWorld->simulation->setPauseAtError(!App::currentWorld->simulation->getPauseAtError());
    }
    if (cmd.cmdId == TOGGLE_REMOVENEWOBJECTS_SIMULATIONGUITRIGGEREDCMD)
    {
        App::currentWorld->simulation->setRemoveNewObjectsAtSimulationEnd(
            !App::currentWorld->simulation->getRemoveNewObjectsAtSimulationEnd());
    }
    if (cmd.cmdId == TOGGLE_FULLSCREENATSTART_SIMULATIONGUITRIGGEREDCMD)
    {
        if (App::currentWorld->simulation->isSimulationStopped())
            App::currentWorld->simulation->setFullscreenAtSimulationStart(
                !App::currentWorld->simulation->getFullscreenAtSimulationStart());
    }
    if (cmd.cmdId == TOGGLE_DYNAMICS_DYNAMICSGUITRIGGEREDCMD)
    {
        App::currentWorld->dynamicsContainer->setDynamicsEnabled(
            !App::currentWorld->dynamicsContainer->getDynamicsEnabled());
        App::currentWorld->dynamicsContainer->removeWorld();
    }
    if (cmd.cmdId == SET_ENGINE_DYNAMICSGUITRIGGEREDCMD)
    {
        if (App::currentWorld->simulation->isSimulationStopped())
            App::currentWorld->dynamicsContainer->setDynamicEngineType(cmd.intParams[0], cmd.intParams[1]);
    }
    if (cmd.cmdId == TOGGLE_DISPLAYCONTACTS_DYNAMICSGUITRIGGEREDCMD)
    {
        App::currentWorld->dynamicsContainer->setDisplayContactPoints(
            !App::currentWorld->dynamicsContainer->getDisplayContactPoints());
    }
    if (cmd.cmdId == SET_GRAVITY_DYNAMICSGUITRIGGEREDCMD)
    {
        App::currentWorld->dynamicsContainer->setGravity(cmd.posParams[0]);
    }
    if (cmd.cmdId == SET_TIMESTEP_DYNAMICSGUITRIGGEREDCMD)
    {
        App::currentWorld->dynamicsContainer->setDesiredStepSize(cmd.doubleParams[0]);
    }
    if (cmd.cmdId == TOGGLE_EXPLICITHANDLING_PROXSENSORGUITRIGGEREDCMD)
    {
        CProxSensor* it = App::currentWorld->sceneObjects->getProximitySensorFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setExplicitHandling(!it->getExplicitHandling());
    }
    if (cmd.cmdId == SET_SENSORSUBTYPE_PROXSENSORGUITRIGGEREDCMD)
    {
        CProxSensor* it = App::currentWorld->sceneObjects->getProximitySensorFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setSensableType(cmd.intParams[1]);
    }
    if (cmd.cmdId == TOGGLE_SHOWVOLUME_PROXSENSORGUITRIGGEREDCMD)
    {
        CProxSensor* it = App::currentWorld->sceneObjects->getProximitySensorFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setShowVolume(!it->getShowVolume());
    }
    if (cmd.cmdId == SET_POINTSIZE_PROXSENSORGUITRIGGEREDCMD)
    {
        CProxSensor* it = App::currentWorld->sceneObjects->getProximitySensorFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setProxSensorSize(cmd.doubleParams[0]);
    }
    if (cmd.cmdId == APPLY_MAINPROP_PROXSENSORGUITRIGGEREDCMD)
    {
        CProxSensor* last = App::currentWorld->sceneObjects->getProximitySensorFromHandle(cmd.intParams[0]);
        if (last != nullptr)
        {
            for (size_t i = 1; i < cmd.intParams.size(); i++)
            {
                CProxSensor* it = App::currentWorld->sceneObjects->getProximitySensorFromHandle(cmd.intParams[i]);
                if (it != nullptr)
                {
                    it->setSensableType(last->getSensableType());
                    it->setExplicitHandling(last->getExplicitHandling());
                    if (last->getRandomizedDetection())
                    {
                        it->setRandomizedDetectionSampleCount(last->getRandomizedDetectionSampleCount());
                        it->setRandomizedDetectionCountForDetection(last->getRandomizedDetectionCountForDetection());
                    }
                    it->setFrontFaceDetection(last->getFrontFaceDetection());
                    it->setBackFaceDetection(last->getBackFaceDetection());
                    it->setExactMode(last->getExactMode());
                    it->setAllowedNormal(last->getAllowedNormal());
                    it->convexVolume->setSmallestDistanceAllowed(last->convexVolume->getSmallestDistanceAllowed());
                    it->setSensableObject(last->getSensableObject());
                }
            }
        }
    }
    if (cmd.cmdId == APPLY_VISUALPROP_PROXSENSORGUITRIGGEREDCMD)
    {
        CProxSensor* it = App::currentWorld->sceneObjects->getProximitySensorFromHandle(cmd.intParams[0]);
        if (it != nullptr)
        {
            for (size_t i = 1; i < cmd.intParams.size(); i++)
            {
                CProxSensor* it2 = App::currentWorld->sceneObjects->getProximitySensorFromHandle(cmd.intParams[i]);
                if (it2 != nullptr)
                {
                    if (it->getObjectHandle() != it2->getObjectHandle())
                    {
                        it->getColor(0)->copyYourselfInto(it2->getColor(0));
                        it->getColor(1)->copyYourselfInto(it2->getColor(1));
                        it2->setProxSensorSize(it->getProxSensorSize());
                        it2->setShowVolume(it->getShowVolume());
                    }
                }
            }
        }
    }
    if (cmd.cmdId == SET_DETECTIONPARAMS_PROXSENSORGUITRIGGEREDCMD)
    {
        CProxSensor* it = App::currentWorld->sceneObjects->getProximitySensorFromHandle(cmd.intParams[0]);
        if (it != nullptr)
        {
            it->setFrontFaceDetection(cmd.boolParams[0]);
            it->setBackFaceDetection(cmd.boolParams[1]);
            it->setExactMode(cmd.boolParams[2]);
            it->setAllowedNormal(cmd.doubleParams[0]);
            if (!cmd.boolParams[3])
                it->setAllowedNormal(0.0);
            it->convexVolume->setSmallestDistanceAllowed(cmd.doubleParams[1]);
            if (!cmd.boolParams[4])
                it->convexVolume->setSmallestDistanceAllowed(0.0);
            if (it->getRandomizedDetection())
            {
                it->setRandomizedDetectionSampleCount(cmd.intParams[1]);
                it->setRandomizedDetectionCountForDetection(cmd.intParams[2]);
            }
        }
    }

    if (cmd.cmdId == SET_OFFSET_DETECTIONVOLUMEGUITRIGGEREDCMD)
    {
        CProxSensor* prox = App::currentWorld->sceneObjects->getProximitySensorFromHandle(cmd.intParams[0]);
        CMill* mill = App::currentWorld->sceneObjects->getMillFromHandle(cmd.intParams[0]);
        if (prox != nullptr)
            prox->convexVolume->setOffset(cmd.doubleParams[0]);
        if (mill != nullptr)
            mill->convexVolume->setOffset(cmd.doubleParams[0]);
    }
    if (cmd.cmdId == SET_RADIUS_DETECTIONVOLUMEGUITRIGGEREDCMD)
    {
        CProxSensor* prox = App::currentWorld->sceneObjects->getProximitySensorFromHandle(cmd.intParams[0]);
        CMill* mill = App::currentWorld->sceneObjects->getMillFromHandle(cmd.intParams[0]);
        if (prox != nullptr)
            prox->convexVolume->setRadius(cmd.doubleParams[0]);
        if (mill != nullptr)
            mill->convexVolume->setRadius(cmd.doubleParams[0]);
    }
    if (cmd.cmdId == SET_RADIUSFAR_DETECTIONVOLUMEGUITRIGGEREDCMD)
    {
        CProxSensor* prox = App::currentWorld->sceneObjects->getProximitySensorFromHandle(cmd.intParams[0]);
        CMill* mill = App::currentWorld->sceneObjects->getMillFromHandle(cmd.intParams[0]);
        if (prox != nullptr)
            prox->convexVolume->setRadiusFar(cmd.doubleParams[0]);
        if (mill != nullptr)
            mill->convexVolume->setRadiusFar(cmd.doubleParams[0]);
    }
    if (cmd.cmdId == SET_RANGE_DETECTIONVOLUMEGUITRIGGEREDCMD)
    {
        CProxSensor* prox = App::currentWorld->sceneObjects->getProximitySensorFromHandle(cmd.intParams[0]);
        CMill* mill = App::currentWorld->sceneObjects->getMillFromHandle(cmd.intParams[0]);
        if (prox != nullptr)
            prox->convexVolume->setRange(cmd.doubleParams[0]);
        if (mill != nullptr)
            mill->convexVolume->setRange(cmd.doubleParams[0]);
    }
    if (cmd.cmdId == SET_XSIZE_DETECTIONVOLUMEGUITRIGGEREDCMD)
    {
        CProxSensor* prox = App::currentWorld->sceneObjects->getProximitySensorFromHandle(cmd.intParams[0]);
        CMill* mill = App::currentWorld->sceneObjects->getMillFromHandle(cmd.intParams[0]);
        if (prox != nullptr)
            prox->convexVolume->setXSize(cmd.doubleParams[0]);
        if (mill != nullptr)
            mill->convexVolume->setXSize(cmd.doubleParams[0]);
    }
    if (cmd.cmdId == SET_YSIZE_DETECTIONVOLUMEGUITRIGGEREDCMD)
    {
        CProxSensor* prox = App::currentWorld->sceneObjects->getProximitySensorFromHandle(cmd.intParams[0]);
        CMill* mill = App::currentWorld->sceneObjects->getMillFromHandle(cmd.intParams[0]);
        if (prox != nullptr)
            prox->convexVolume->setYSize(cmd.doubleParams[0]);
        if (mill != nullptr)
            mill->convexVolume->setYSize(cmd.doubleParams[0]);
    }
    if (cmd.cmdId == SET_XSIZEFAR_DETECTIONVOLUMEGUITRIGGEREDCMD)
    {
        CProxSensor* prox = App::currentWorld->sceneObjects->getProximitySensorFromHandle(cmd.intParams[0]);
        CMill* mill = App::currentWorld->sceneObjects->getMillFromHandle(cmd.intParams[0]);
        if (prox != nullptr)
            prox->convexVolume->setXSizeFar(cmd.doubleParams[0]);
        if (mill != nullptr)
            mill->convexVolume->setXSizeFar(cmd.doubleParams[0]);
    }
    if (cmd.cmdId == SET_YSIZEFAR_DETECTIONVOLUMEGUITRIGGEREDCMD)
    {
        CProxSensor* prox = App::currentWorld->sceneObjects->getProximitySensorFromHandle(cmd.intParams[0]);
        CMill* mill = App::currentWorld->sceneObjects->getMillFromHandle(cmd.intParams[0]);
        if (prox != nullptr)
            prox->convexVolume->setYSizeFar(cmd.doubleParams[0]);
        if (mill != nullptr)
            mill->convexVolume->setYSizeFar(cmd.doubleParams[0]);
    }
    if (cmd.cmdId == SET_ANGLE_DETECTIONVOLUMEGUITRIGGEREDCMD)
    {
        CProxSensor* prox = App::currentWorld->sceneObjects->getProximitySensorFromHandle(cmd.intParams[0]);
        CMill* mill = App::currentWorld->sceneObjects->getMillFromHandle(cmd.intParams[0]);
        if (prox != nullptr)
            prox->convexVolume->setAngle(cmd.doubleParams[0]);
        if (mill != nullptr)
            mill->convexVolume->setAngle(cmd.doubleParams[0]);
    }
    if (cmd.cmdId == SET_FACECOUNT_DETECTIONVOLUMEGUITRIGGEREDCMD)
    {
        CProxSensor* prox = App::currentWorld->sceneObjects->getProximitySensorFromHandle(cmd.intParams[0]);
        CMill* mill = App::currentWorld->sceneObjects->getMillFromHandle(cmd.intParams[0]);
        if (prox != nullptr)
            prox->convexVolume->setFaceNumber(cmd.intParams[1]);
        if (mill != nullptr)
            mill->convexVolume->setFaceNumber(cmd.intParams[1]);
    }
    if (cmd.cmdId == SET_FACECOUNTFAR_DETECTIONVOLUMEGUITRIGGEREDCMD)
    {
        CProxSensor* prox = App::currentWorld->sceneObjects->getProximitySensorFromHandle(cmd.intParams[0]);
        CMill* mill = App::currentWorld->sceneObjects->getMillFromHandle(cmd.intParams[0]);
        if (prox != nullptr)
            prox->convexVolume->setFaceNumberFar(cmd.intParams[1]);
        if (mill != nullptr)
            mill->convexVolume->setFaceNumberFar(cmd.intParams[1]);
    }
    if (cmd.cmdId == SET_SUBDIVISIONS_DETECTIONVOLUMEGUITRIGGEREDCMD)
    {
        CProxSensor* prox = App::currentWorld->sceneObjects->getProximitySensorFromHandle(cmd.intParams[0]);
        CMill* mill = App::currentWorld->sceneObjects->getMillFromHandle(cmd.intParams[0]);
        if (prox != nullptr)
            prox->convexVolume->setSubdivisions(cmd.intParams[1]);
        if (mill != nullptr)
            mill->convexVolume->setSubdivisions(cmd.intParams[1]);
    }
    if (cmd.cmdId == SET_SUBDIVISIONSFAR_DETECTIONVOLUMEGUITRIGGEREDCMD)
    {
        CProxSensor* prox = App::currentWorld->sceneObjects->getProximitySensorFromHandle(cmd.intParams[0]);
        CMill* mill = App::currentWorld->sceneObjects->getMillFromHandle(cmd.intParams[0]);
        if (prox != nullptr)
            prox->convexVolume->setSubdivisionsFar(cmd.intParams[1]);
        if (mill != nullptr)
            mill->convexVolume->setSubdivisionsFar(cmd.intParams[1]);
    }
    if (cmd.cmdId == SET_INSIDEGAP_DETECTIONVOLUMEGUITRIGGEREDCMD)
    {
        CProxSensor* prox = App::currentWorld->sceneObjects->getProximitySensorFromHandle(cmd.intParams[0]);
        CMill* mill = App::currentWorld->sceneObjects->getMillFromHandle(cmd.intParams[0]);
        if (prox != nullptr)
            prox->convexVolume->setInsideAngleThing(cmd.doubleParams[0]);
        if (mill != nullptr)
            mill->convexVolume->setInsideAngleThing(cmd.doubleParams[0]);
    }
    if (cmd.cmdId == APPLY_DETECTIONVOLUMEGUITRIGGEREDCMD)
    {
        CProxSensor* prox = App::currentWorld->sceneObjects->getProximitySensorFromHandle(cmd.intParams[0]);
        CMill* mill = App::currentWorld->sceneObjects->getMillFromHandle(cmd.intParams[0]);
        if (prox != nullptr)
        {
            for (size_t i = 1; i < cmd.intParams.size(); i++)
            {
                CProxSensor* it = App::currentWorld->sceneObjects->getProximitySensorFromHandle(cmd.intParams[i]);
                if ((it != nullptr) && (it->getSensorType() == prox->getSensorType()))
                {
                    double w = it->convexVolume->getSmallestDistanceAllowed();
                    it->convexVolume->disableVolumeComputation(true);
                    // Volume parameters:
                    it->setRandomizedDetection(false); // somehow needed for next to work always...??
                    it->setRandomizedDetection(prox->getRandomizedDetection());
                    it->convexVolume->setOffset(prox->convexVolume->getOffset());
                    it->convexVolume->setRange(prox->convexVolume->getRange());
                    it->convexVolume->setXSize(prox->convexVolume->getXSize());
                    it->convexVolume->setYSize(prox->convexVolume->getYSize());
                    it->convexVolume->setXSizeFar(prox->convexVolume->getXSizeFar());
                    it->convexVolume->setYSizeFar(prox->convexVolume->getYSizeFar());
                    it->convexVolume->setRadius(prox->convexVolume->getRadius());
                    it->convexVolume->setRadiusFar(prox->convexVolume->getRadiusFar());
                    it->convexVolume->setAngle(prox->convexVolume->getAngle());
                    it->convexVolume->setFaceNumber(prox->convexVolume->getFaceNumber());
                    it->convexVolume->setFaceNumberFar(prox->convexVolume->getFaceNumberFar());
                    it->convexVolume->setSubdivisions(prox->convexVolume->getSubdivisions());
                    it->convexVolume->setSubdivisionsFar(prox->convexVolume->getSubdivisionsFar());
                    it->convexVolume->setInsideAngleThing(prox->convexVolume->getInsideAngleThing());
                    // We have to recompute the planes:
                    it->convexVolume->disableVolumeComputation(false);
                    it->convexVolume->computeVolumes();
                    it->convexVolume->setSmallestDistanceAllowed(w);
                }
            }
        }
        if (mill != nullptr)
        {
            for (size_t i = 1; i < cmd.intParams.size(); i++)
            {
                CMill* it = App::currentWorld->sceneObjects->getMillFromHandle(cmd.intParams[i]);
                if (it != nullptr)
                {
                    it->convexVolume->disableVolumeComputation(true);
                    // Volume parameters:
                    it->setMillType(mill->getMillType());
                    it->convexVolume->setOffset(mill->convexVolume->getOffset());
                    it->convexVolume->setRange(mill->convexVolume->getRange());
                    it->convexVolume->setXSize(mill->convexVolume->getXSize());
                    it->convexVolume->setYSize(mill->convexVolume->getYSize());
                    it->convexVolume->setXSizeFar(mill->convexVolume->getXSizeFar());
                    it->convexVolume->setYSizeFar(mill->convexVolume->getYSizeFar());
                    it->convexVolume->setRadius(mill->convexVolume->getRadius());
                    it->convexVolume->setRadiusFar(mill->convexVolume->getRadiusFar());
                    it->convexVolume->setAngle(mill->convexVolume->getAngle());
                    it->convexVolume->setFaceNumber(mill->convexVolume->getFaceNumber());
                    it->convexVolume->setFaceNumberFar(mill->convexVolume->getFaceNumberFar());
                    it->convexVolume->setSubdivisionsFar(mill->convexVolume->getSubdivisionsFar());
                    // We have to recompute the planes:
                    it->convexVolume->disableVolumeComputation(false);
                    it->convexVolume->computeVolumes();
                }
            }
        }
    }

    if (cmd.cmdId == TOGGLE_ENABLEALL_MILLGUITRIGGEREDCMD)
    {
        App::currentWorld->mainSettings_old->millsEnabled = !App::currentWorld->mainSettings_old->millsEnabled;
    }
    if (cmd.cmdId == TOGGLE_EXPLICITHANDLING_MILLGUITRIGGEREDCMD)
    {
        CMill* it = App::currentWorld->sceneObjects->getMillFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setExplicitHandling(!it->getExplicitHandling());
    }
    if (cmd.cmdId == SET_SIZE_MILLGUITRIGGEREDCMD)
    {
        CMill* it = App::currentWorld->sceneObjects->getMillFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setSize(cmd.doubleParams[0]);
    }
    if (cmd.cmdId == SET_ENTITYTOCUT_MILLGUITRIGGEREDCMD)
    {
        CMill* it = App::currentWorld->sceneObjects->getMillFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setMillableObject(cmd.intParams[1]);
    }

    if (cmd.cmdId == TOGGLE_ENABLED_LIGHTGUITRIGGEREDCMD)
    {
        CLight* it = App::currentWorld->sceneObjects->getLightFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setLightActive(!it->getLightActive());
    }
    if (cmd.cmdId == TOGGLE_LIGHTISLOCAL_LIGHTGUITRIGGEREDCMD)
    {
        CLight* it = App::currentWorld->sceneObjects->getLightFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setLightIsLocal(!it->getLightIsLocal());
    }
    if (cmd.cmdId == SET_SIZE_LIGHTGUITRIGGEREDCMD)
    {
        CLight* it = App::currentWorld->sceneObjects->getLightFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setLightSize(cmd.doubleParams[0]);
    }
    if (cmd.cmdId == SET_SPOTCUTOFF_LIGHTGUITRIGGEREDCMD)
    {
        CLight* it = App::currentWorld->sceneObjects->getLightFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setSpotCutoffAngle(cmd.doubleParams[0]);
    }
    if (cmd.cmdId == SET_SPOTEXPONENT_LIGHTGUITRIGGEREDCMD)
    {
        CLight* it = App::currentWorld->sceneObjects->getLightFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setSpotExponent(cmd.intParams[1]);
    }
    if (cmd.cmdId == SET_CONSTATTENUATION_LIGHTGUITRIGGEREDCMD)
    {
        CLight* it = App::currentWorld->sceneObjects->getLightFromHandle(cmd.intParams[0]);
        if (it != nullptr)
        {
            double arr[3];
            it->getAttenuationFactors(arr);
            arr[0] = cmd.doubleParams[0];
            it->setAttenuationFactors(arr);
        }
    }
    if (cmd.cmdId == SET_LINATTENUATION_LIGHTGUITRIGGEREDCMD)
    {
        CLight* it = App::currentWorld->sceneObjects->getLightFromHandle(cmd.intParams[0]);
        if (it != nullptr)
        {
            double arr[3];
            it->getAttenuationFactors(arr);
            arr[1] = cmd.doubleParams[0];
            it->setAttenuationFactors(arr);
        }
    }
    if (cmd.cmdId == SET_QUADATTENUATION_LIGHTGUITRIGGEREDCMD)
    {
        CLight* it = App::currentWorld->sceneObjects->getLightFromHandle(cmd.intParams[0]);
        if (it != nullptr)
        {
            double arr[3];
            it->getAttenuationFactors(arr);
            arr[2] = cmd.doubleParams[0];
            it->setAttenuationFactors(arr);
        }
    }

    if (cmd.cmdId == SET_SIZE_SCRIPTGUITRIGGEREDCMD)
    {
        CScript* it = App::currentWorld->sceneObjects->getScriptFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setScriptSize(cmd.doubleParams[0]);
    }
    if (cmd.cmdId == APPLY_VISUALPROP_SCRIPTGUITRIGGEREDCMD)
    {
        CScript* it = App::currentWorld->sceneObjects->getScriptFromHandle(cmd.intParams[0]);
        if (it != nullptr)
        {
            for (size_t i = 1; i < cmd.intParams.size(); i++)
            {
                CScript* it2 = App::currentWorld->sceneObjects->getScriptFromHandle(cmd.intParams[i]);
                if (it2 != nullptr)
                {
                    it->getScriptColor()->copyYourselfInto(it2->getScriptColor());
                    it2->setScriptSize(it->getScriptSize());
                }
            }
        }
    }

    if (cmd.cmdId == SET_SIZE_DUMMYGUITRIGGEREDCMD)
    {
        CDummy* it = App::currentWorld->sceneObjects->getDummyFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setDummySize(cmd.doubleParams[0]);
    }
    if (cmd.cmdId == APPLY_VISUALPROP_DUMMYGUITRIGGEREDCMD)
    {
        CDummy* it = App::currentWorld->sceneObjects->getDummyFromHandle(cmd.intParams[0]);
        if (it != nullptr)
        {
            for (size_t i = 1; i < cmd.intParams.size(); i++)
            {
                CDummy* it2 = App::currentWorld->sceneObjects->getDummyFromHandle(cmd.intParams[i]);
                if (it2 != nullptr)
                {
                    it->getDummyColor()->copyYourselfInto(it2->getDummyColor());
                    it2->setDummySize(it->getDummySize());
                    it->copyEnginePropertiesTo(it2);
                }
            }
        }
    }
    if (cmd.cmdId == SET_LINKEDDUMMY_DUMMYGUITRIGGEREDCMD)
    {
        CDummy* it = App::currentWorld->sceneObjects->getDummyFromHandle(cmd.intParams[0]);
        if (it != nullptr)
        {
            CDummy* it2 = App::currentWorld->sceneObjects->getDummyFromHandle(cmd.intParams[1]);
            if (it2 != nullptr)
            {
                bool n = (it->getLinkedDummyHandle() == -1);
                it->setLinkedDummyHandle(it2->getObjectHandle(), true);

                int tp = it->getDummyType();
                if ((tp == sim_dummytype_default) || (tp == sim_dummytype_assembly))
                    it->setDummyType(sim_dummytype_dynloopclosure, true);
            }
            else
                it->setLinkedDummyHandle(-1, true);
        }
    }
    if (cmd.cmdId == SET_LINKTYPE_DUMMYGUITRIGGEREDCMD)
    {
        CDummy* it = App::currentWorld->sceneObjects->getDummyFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setDummyType(cmd.intParams[1], true);
    }
    if (cmd.cmdId == TOGGLE_FOLLOWORIENTATION_DUMMYGUITRIGGEREDCMD)
    {
        CDummy* it = App::currentWorld->sceneObjects->getDummyFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setAssignedToParentPathOrientation(!it->getAssignedToParentPathOrientation());
    }
    if (cmd.cmdId == TOGGLE_FOLLOWPOSITION_DUMMYGUITRIGGEREDCMD)
    {
        CDummy* it = App::currentWorld->sceneObjects->getDummyFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setAssignedToParentPath(!it->getAssignedToParentPath());
    }
    if (cmd.cmdId == SET_FREEORFIXEDONPATH_DUMMYGUITRIGGEREDCMD)
    {
        CDummy* it = App::currentWorld->sceneObjects->getDummyFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setFreeOnPathTrajectory(cmd.intParams[1] != 0);
    }
    if (cmd.cmdId == SET_OFFSET_DUMMYGUITRIGGEREDCMD)
    {
        CDummy* it = App::currentWorld->sceneObjects->getDummyFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setVirtualDistanceOffsetOnPath(cmd.doubleParams[0]);
    }
    if (cmd.cmdId == SET_COPYINCREMENT_DUMMYGUITRIGGEREDCMD)
    {
        CDummy* it = App::currentWorld->sceneObjects->getDummyFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setVirtualDistanceOffsetOnPath_variationWhenCopy(cmd.doubleParams[0]);
    }

    if (cmd.cmdId == TOGGLE_ENABLED_MIRRORGUITRIGGEREDCMD)
    {
        CMirror* it = App::currentWorld->sceneObjects->getMirrorFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setActive(!it->getActive());
    }
    if (cmd.cmdId == SET_WIDTH_MIRRORGUITRIGGEREDCMD)
    {
        CMirror* it = App::currentWorld->sceneObjects->getMirrorFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setMirrorWidth(cmd.doubleParams[0]);
    }
    if (cmd.cmdId == SET_HEIGHT_MIRRORGUITRIGGEREDCMD)
    {
        CMirror* it = App::currentWorld->sceneObjects->getMirrorFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setMirrorHeight(cmd.doubleParams[0]);
    }
    if (cmd.cmdId == SET_REFLECTANCE_MIRRORGUITRIGGEREDCMD)
    {
        CMirror* it = App::currentWorld->sceneObjects->getMirrorFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setReflectance(cmd.doubleParams[0]);
    }
    if (cmd.cmdId == SET_MIRRORFUNC_MIRRORGUITRIGGEREDCMD)
    {
        CMirror* it = App::currentWorld->sceneObjects->getMirrorFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setIsMirror(true);
    }
    if (cmd.cmdId == SET_CLIPPINGFUNC_MIRRORGUITRIGGEREDCMD)
    {
        CMirror* it = App::currentWorld->sceneObjects->getMirrorFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setIsMirror(false);
    }
    if (cmd.cmdId == SET_CLIPPINGENTITY_MIRRORGUITRIGGEREDCMD)
    {
        CMirror* it = App::currentWorld->sceneObjects->getMirrorFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setClippingObjectOrCollection(cmd.intParams[1]);
    }
    if (cmd.cmdId == TOGGLE_DISABLEALLCLIPPING_MIRRORGUITRIGGEREDCMD)
    {
        App::currentWorld->mainSettings_old->clippingPlanesDisabled =
            !App::currentWorld->mainSettings_old->clippingPlanesDisabled;
    }
    if (cmd.cmdId == TOGGLE_DISABLEALLMIRRORS_MIRRORGUITRIGGEREDCMD)
    {
        App::currentWorld->mainSettings_old->mirrorsDisabled = !App::currentWorld->mainSettings_old->mirrorsDisabled;
    }
    if (cmd.cmdId == TOGGLE_SAVECALCSTRUCT_ENVIRONMENTGUITRIGGEREDCMD)
    {
        App::currentWorld->environment->setSaveExistingCalculationStructures(
            !App::currentWorld->environment->getSaveExistingCalculationStructures());
    }
    if (cmd.cmdId == TOGGLE_SHAPETEXTURES_ENVIRONMENTGUITRIGGEREDCMD)
    {
        App::currentWorld->environment->setShapeTexturesEnabled(
            !App::currentWorld->environment->getShapeTexturesEnabled());
    }
    if (cmd.cmdId == TOGGLE_GLUITEXTURES_ENVIRONMENTGUITRIGGEREDCMD)
    {
        App::currentWorld->environment->set2DElementTexturesEnabled(
            !App::currentWorld->environment->get2DElementTexturesEnabled());
    }
    if (cmd.cmdId == TOGGLE_LOCKSCENE_ENVIRONMENTGUITRIGGEREDCMD)
    {
        App::currentWorld->environment->setRequestFinalSave(!App::currentWorld->environment->getRequestFinalSave());
    }
    if (cmd.cmdId == SET_ACKNOWLEDGMENT_ENVIRONMENTGUITRIGGEREDCMD)
    {
        App::currentWorld->environment->setAcknowledgement(cmd.stringParams[0].c_str());
    }
    if (cmd.cmdId == CLEANUP_OBJNAMES_ENVIRONMENTGUITRIGGEREDCMD)
    {
        if (App::currentWorld->simulation->isSimulationStopped())
            App::currentWorld->cleanupHashNames_allObjects(-1);
    }
    if (cmd.cmdId == CLEANUP_GHOSTS_ENVIRONMENTGUITRIGGEREDCMD)
    {
        App::currentWorld->ghostObjectCont_old->removeGhost(-1, -1);
    }
    if (cmd.cmdId == TOGGLE_ENABLED_FOGGUITRIGGEREDCMD)
    {
        App::currentWorld->environment->setFogEnabled(!App::currentWorld->environment->getFogEnabled());
    }
    if (cmd.cmdId == SET_TYPE_FOGGUITRIGGEREDCMD)
    {
        App::currentWorld->environment->setFogType(cmd.intParams[0]);
    }
    if (cmd.cmdId == SET_START_FOGGUITRIGGEREDCMD)
    {
        App::currentWorld->environment->setFogStart(cmd.doubleParams[0]);
    }
    if (cmd.cmdId == SET_END_FOGGUITRIGGEREDCMD)
    {
        App::currentWorld->environment->setFogEnd(cmd.doubleParams[0]);
    }
    if (cmd.cmdId == SET_DENSITY_FOGGUITRIGGEREDCMD)
    {
        App::currentWorld->environment->setFogDensity(cmd.doubleParams[0]);
    }

    if (cmd.cmdId == SET_ITEMRGB_COLORGUITRIGGEREDCMD)
    {
        float* col = GuiApp::getRGBPointerFromItem(cmd.intParams[0], cmd.intParams[1], cmd.intParams[2],
                                                   cmd.intParams[3], nullptr);
        if (col != nullptr)
        {
            col[0] = (float)cmd.doubleParams[0];
            col[1] = (float)cmd.doubleParams[1];
            col[2] = (float)cmd.doubleParams[2];
        }
    }

    if (cmd.cmdId == SET_SHININESS_MATERIALGUITRIGGEREDCMD)
    {
        int allowedParts = 0; // Bit-coded: 1=ambient/difuse, 2=diffuse(light only) 4=spec, 8=emiss., 16=aux channels,
                              // 32=pulsation, 64=shininess, 128=opacity, 256=colorName, 512=ext. string
        CColorObject* it = GuiApp::getVisualParamPointerFromItem(cmd.intParams[0], cmd.intParams[1], cmd.intParams[2],
                                                                 nullptr, &allowedParts);
        if ((it != nullptr) && (allowedParts & 64))
            it->setShininess(tt::getLimitedInt(0, 128, cmd.intParams[3]));
    }
    if (cmd.cmdId == TOGGLE_TRANSPARENCY_MATERIALGUITRIGGEREDCMD)
    {
        int allowedParts = 0; // Bit-coded: 1=ambient/difuse, 2=diffuse(light only) 4=spec, 8=emiss., 16=aux channels,
                              // 32=pulsation, 64=shininess, 128=opacity, 256=colorName, 512=ext. string
        CColorObject* it = GuiApp::getVisualParamPointerFromItem(cmd.intParams[0], cmd.intParams[1], cmd.intParams[2],
                                                                 nullptr, &allowedParts);
        CShape* shape = App::currentWorld->sceneObjects->getShapeFromHandle(cmd.intParams[1]);
        if ((it != nullptr) && (allowedParts & 128) && (shape != nullptr))
        {
            it->setTranslucid(!it->getTranslucid());
            shape->actualizeContainsTransparentComponent();
        }
    }
    if (cmd.cmdId == SET_TRANSPARENCYFACT_MATERIALGUITRIGGEREDCMD)
    {
        int allowedParts = 0; // Bit-coded: 1=ambient/difuse, 2=diffuse(light only) 4=spec, 8=emiss., 16=aux channels,
                              // 32=pulsation, 64=shininess, 128=opacity, 256=colorName, 512=ext. string
        CColorObject* it = GuiApp::getVisualParamPointerFromItem(cmd.intParams[0], cmd.intParams[1], cmd.intParams[2],
                                                                 nullptr, &allowedParts);
        if ((it != nullptr) && (allowedParts & 128))
            it->setOpacity(tt::getLimitedFloat(0.0, 1.0, cmd.doubleParams[0]));
    }
    if (cmd.cmdId == SET_NAME_MATERIALGUITRIGGEREDCMD)
    {
        int allowedParts = 0; // Bit-coded: 1=ambient/difuse, 2=diffuse(light only) 4=spec, 8=emiss., 16=aux channels,
                              // 32=pulsation, 64=shininess, 128=opacity, 256=colorName, 512=ext. string
        CColorObject* it = GuiApp::getVisualParamPointerFromItem(cmd.intParams[0], cmd.intParams[1], cmd.intParams[2],
                                                                 nullptr, &allowedParts);
        if ((it != nullptr) && (allowedParts & 256))
        {
            tt::removeIllegalCharacters(cmd.stringParams[0], false);
            it->setColorName(cmd.stringParams[0].c_str());
        }
    }
    if (cmd.cmdId == SET_EXTSTRING_MATERIALGUITRIGGEREDCMD)
    {
        int allowedParts = 0; // Bit-coded: 1=ambient/difuse, 2=diffuse(light only) 4=spec, 8=emiss., 16=aux channels,
                              // 32=pulsation, 64=shininess, 128=opacity, 256=colorName, 512=ext. string
        CColorObject* it = GuiApp::getVisualParamPointerFromItem(cmd.intParams[0], cmd.intParams[1], cmd.intParams[2],
                                                                 nullptr, &allowedParts);
        if ((it != nullptr) && (allowedParts & 512))
            it->setExtensionString(cmd.stringParams[0].c_str());
    }
    if (cmd.cmdId == SET_PULSATIONPARAMS_MATERIALGUITRIGGEREDCMD)
    {
        int allowedParts = 0; // Bit-coded: 1=ambient/difuse, 2=diffuse(light only) 4=spec, 8=emiss., 16=aux channels,
                              // 32=pulsation, 64=shininess, 128=opacity, 256=colorName, 512=ext. string
        CColorObject* it = GuiApp::getVisualParamPointerFromItem(cmd.intParams[0], cmd.intParams[1], cmd.intParams[2],
                                                                 nullptr, &allowedParts);
        if ((it != nullptr) && (allowedParts & 32))
        {
            it->setFlash(cmd.boolParams[0]);
            it->setUseSimulationTime(cmd.boolParams[1]);
            it->setFlashFrequency(cmd.doubleParams[0]);
            it->setFlashPhase(cmd.doubleParams[1]);
            it->setFlashRatio(cmd.doubleParams[2]);
        }
    }

    if (cmd.cmdId == SET_VOXELSIZE_OCTREEGUITRIGGEREDCMD)
    {
        COcTree* it = App::currentWorld->sceneObjects->getOctreeFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setCellSize(cmd.doubleParams[0]);
    }
    if (cmd.cmdId == TOGGLE_SHOWSTRUCTURE_OCTREEGUITRIGGEREDCMD)
    {
        COcTree* it = App::currentWorld->sceneObjects->getOctreeFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setShowOctree(!it->getShowOctree());
    }
    if (cmd.cmdId == TOGGLE_RANDOMCOLORS_OCTREEGUITRIGGEREDCMD)
    {
        COcTree* it = App::currentWorld->sceneObjects->getOctreeFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setUseRandomColors(!it->getUseRandomColors());
    }
    if (cmd.cmdId == TOGGLE_SHOWPOINTS_OCTREEGUITRIGGEREDCMD)
    {
        COcTree* it = App::currentWorld->sceneObjects->getOctreeFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setUsePointsInsteadOfCubes(!it->getUsePointsInsteadOfCubes());
    }
    if (cmd.cmdId == SET_POINTSIZE_OCTREEGUITRIGGEREDCMD)
    {
        COcTree* it = App::currentWorld->sceneObjects->getOctreeFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setPointSize(cmd.intParams[1]);
    }
    if (cmd.cmdId == CLEAR_OCTREEGUITRIGGEREDCMD)
    {
        COcTree* it = App::currentWorld->sceneObjects->getOctreeFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->clear();
    }
    if (cmd.cmdId == INSERT_SELECTEDVISIBLEOBJECTS_OCTREEGUITRIGGEREDCMD)
    {
        COcTree* it = App::currentWorld->sceneObjects->getLastSelectionOctree();
        App::currentWorld->sceneObjects->popLastSelection();
        std::vector<int> sel;
        App::currentWorld->sceneObjects->getSelectedObjectHandles(sel, -1, true, true);
        App::currentWorld->sceneObjects->deselectObjects();
        App::logMsg(sim_verbosity_msgs, "Inserting objects into OC tree...");
        it->insertObjects(sel);
        App::currentWorld->sceneObjects->addObjectToSelection(it->getObjectHandle());
        App::undoRedo_sceneChanged("");
        App::logMsg(sim_verbosity_msgs, "done.");
    }
    if (cmd.cmdId == SUBTRACT_SELECTEDVISIBLEOBJECTS_OCTREEGUITRIGGEREDCMD)
    {
        COcTree* it = App::currentWorld->sceneObjects->getLastSelectionOctree();
        App::currentWorld->sceneObjects->popLastSelection();
        std::vector<int> sel;
        App::currentWorld->sceneObjects->getSelectedObjectHandles(sel, -1, true, true);
        App::currentWorld->sceneObjects->deselectObjects();
        App::logMsg(sim_verbosity_msgs, "Subtracting objects from OC tree...");
        it->subtractObjects(sel);
        App::currentWorld->sceneObjects->addObjectToSelection(it->getObjectHandle());
        App::undoRedo_sceneChanged("");
        App::logMsg(sim_verbosity_msgs, "done.");
    }
    if (cmd.cmdId == TOGGLE_COLOREMISSIVE_OCTREEGUITRIGGEREDCMD)
    {
        COcTree* it = App::currentWorld->sceneObjects->getOctreeFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setColorIsEmissive(!it->getColorIsEmissive());
    }
    if (cmd.cmdId == SET_MAXVOXELSIZE_PTCLOUDGUITRIGGEREDCMD)
    {
        CPointCloud* it = App::currentWorld->sceneObjects->getPointCloudFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setCellSize(cmd.doubleParams[0]);
    }
    if (cmd.cmdId == TOGGLE_SHOWOCTREE_PTCLOUDGUITRIGGEREDCMD)
    {
        CPointCloud* it = App::currentWorld->sceneObjects->getPointCloudFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setShowOctree(!it->getShowOctree());
    }
    if (cmd.cmdId == TOGGLE_RANDOMCOLORS_PTCLOUDGUITRIGGEREDCMD)
    {
        CPointCloud* it = App::currentWorld->sceneObjects->getPointCloudFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setUseRandomColors(!it->getUseRandomColors());
    }
    if (cmd.cmdId == SET_PTSIZE_PTCLOUDGUITRIGGEREDCMD)
    {
        CPointCloud* it = App::currentWorld->sceneObjects->getPointCloudFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setPointSize(cmd.intParams[1]);
    }
    if (cmd.cmdId == CLEAR_PTCLOUDGUITRIGGEREDCMD)
    {
        CPointCloud* it = App::currentWorld->sceneObjects->getPointCloudFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->clear();
    }
    if (cmd.cmdId == INSERT_OBJECTS_PTCLOUDGUITRIGGEREDCMD)
    {
        CPointCloud* it = App::currentWorld->sceneObjects->getLastSelectionPointCloud();
        App::currentWorld->sceneObjects->popLastSelection();
        std::vector<int> sel;
        App::currentWorld->sceneObjects->getSelectedObjectHandles(sel, -1, true, true);
        App::currentWorld->sceneObjects->deselectObjects();
        App::logMsg(sim_verbosity_msgs, "Inserting objects into point cloud...");
        it->insertObjects(sel);
        App::currentWorld->sceneObjects->addObjectToSelection(it->getObjectHandle());
        App::undoRedo_sceneChanged("");
        App::logMsg(sim_verbosity_msgs, "done.");
    }
    if (cmd.cmdId == SET_MAXPTCNT_PTCLOUDGUITRIGGEREDCMD)
    {
        CPointCloud* it = App::currentWorld->sceneObjects->getPointCloudFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setMaxPointCountPerCell(cmd.intParams[1]);
    }
    if (cmd.cmdId == SET_BUILDRESOLUTION_PTCLOUDGUITRIGGEREDCMD)
    {
        CPointCloud* it = App::currentWorld->sceneObjects->getPointCloudFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setBuildResolution(cmd.doubleParams[0]);
    }
    if (cmd.cmdId == TOGGLE_USEOCTREE_PTCLOUDGUITRIGGEREDCMD)
    {
        CPointCloud* it = App::currentWorld->sceneObjects->getPointCloudFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setDoNotUseCalculationStructure(!it->getDoNotUseCalculationStructure());
    }
    if (cmd.cmdId == TOGGLE_EMISSIVECOLOR_PTCLOUDGUITRIGGEREDCMD)
    {
        CPointCloud* it = App::currentWorld->sceneObjects->getPointCloudFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setColorIsEmissive(!it->getColorIsEmissive());
    }
    if (cmd.cmdId == SET_DISPLAYRATIO_PTCLOUDGUITRIGGEREDCMD)
    {
        CPointCloud* it = App::currentWorld->sceneObjects->getPointCloudFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setPointDisplayRatio(cmd.doubleParams[0]);
    }
    if (cmd.cmdId == SUBTRACT_OBJECTS_PTCLOUDGUITRIGGEREDCMD)
    {
        CPointCloud* it = App::currentWorld->sceneObjects->getLastSelectionPointCloud();
        App::currentWorld->sceneObjects->popLastSelection();
        std::vector<int> sel;
        App::currentWorld->sceneObjects->getSelectedObjectHandles(sel, -1, true, true);
        App::currentWorld->sceneObjects->deselectObjects();
        App::logMsg(sim_verbosity_msgs, "Subtracting objects from point cloud...");
        it->subtractObjects(sel);
        App::currentWorld->sceneObjects->addObjectToSelection(it->getObjectHandle());
        App::undoRedo_sceneChanged("");
        App::logMsg(sim_verbosity_msgs, "done.");
    }
    if (cmd.cmdId == SET_SUBTRACTTOLERANCE_PTCLOUDGUITRIGGEREDCMD)
    {
        CPointCloud* it = App::currentWorld->sceneObjects->getPointCloudFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setRemovalDistanceTolerance(cmd.doubleParams[0]);
    }
    if (cmd.cmdId == SET_INSERTTOLERANCE_PTCLOUDGUITRIGGEREDCMD)
    {
        CPointCloud* it = App::currentWorld->sceneObjects->getPointCloudFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setInsertionDistanceTolerance(cmd.doubleParams[0]);
    }

    if (cmd.cmdId == SET_SIZE_FORCESENSORGUITRIGGEREDCMD)
    {
        CForceSensor* it = App::currentWorld->sceneObjects->getForceSensorFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setForceSensorSize(cmd.doubleParams[0]);
    }
    if (cmd.cmdId == APPLY_VISUALPROP_FORCESENSORGUITRIGGEREDCMD)
    {
        CForceSensor* it = App::currentWorld->sceneObjects->getForceSensorFromHandle(cmd.intParams[0]);
        if (it != nullptr)
        {
            for (size_t i = 1; i < cmd.intParams.size(); i++)
            {
                CForceSensor* it2 = App::currentWorld->sceneObjects->getForceSensorFromHandle(cmd.intParams[i]);
                if (it2 != nullptr)
                {
                    it->getColor(false)->copyYourselfInto(it2->getColor(false));
                    it->getColor(true)->copyYourselfInto(it2->getColor(true));
                    it2->setForceSensorSize(it->getForceSensorSize());
                }
            }
        }
    }
    if (cmd.cmdId == SET_SAMPLESIZE_FORCESENSORGUITRIGGEREDCMD)
    {
        CForceSensor* it = App::currentWorld->sceneObjects->getForceSensorFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setFilterSampleSize(cmd.intParams[1]);
    }
    if (cmd.cmdId == SET_AVERAGEVALUE_FORCESENSORGUITRIGGEREDCMD)
    {
        CForceSensor* it = App::currentWorld->sceneObjects->getForceSensorFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setFilterType(0);
    }
    if (cmd.cmdId == SET_MEDIANVALUE_FORCESENSORGUITRIGGEREDCMD)
    {
        CForceSensor* it = App::currentWorld->sceneObjects->getForceSensorFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setFilterType(1);
    }
    if (cmd.cmdId == APPLY_FILER_FORCESENSORGUITRIGGEREDCMD)
    {
        CForceSensor* it = App::currentWorld->sceneObjects->getForceSensorFromHandle(cmd.intParams[0]);
        if (it != nullptr)
        {
            for (size_t i = 1; i < cmd.intParams.size(); i++)
            {
                CForceSensor* it2 = App::currentWorld->sceneObjects->getForceSensorFromHandle(cmd.intParams[i]);
                if (it2 != nullptr)
                {
                    it2->setFilterSampleSize(it->getFilterSampleSize());
                    it2->setFilterType(it->getFilterType());
                }
            }
        }
    }
    if (cmd.cmdId == TOGGLE_FORCETHRESHOLDENABLE_FORCESENSORGUITRIGGEREDCMD)
    {
        CForceSensor* it = App::currentWorld->sceneObjects->getForceSensorFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setEnableForceThreshold(!it->getEnableForceThreshold());
    }
    if (cmd.cmdId == TOGGLE_TORQUETHRESHOLDENABLE_FORCESENSORGUITRIGGEREDCMD)
    {
        CForceSensor* it = App::currentWorld->sceneObjects->getForceSensorFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setEnableTorqueThreshold(!it->getEnableTorqueThreshold());
    }
    if (cmd.cmdId == SET_FORCETHRESHOLD_FORCESENSORGUITRIGGEREDCMD)
    {
        CForceSensor* it = App::currentWorld->sceneObjects->getForceSensorFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setForceThreshold(cmd.doubleParams[0]);
    }
    if (cmd.cmdId == SET_TORQUETHRESHOLD_FORCESENSORGUITRIGGEREDCMD)
    {
        CForceSensor* it = App::currentWorld->sceneObjects->getForceSensorFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setTorqueThreshold(cmd.doubleParams[0]);
    }
    if (cmd.cmdId == SET_CONSECTHRESHOLDVIOLATIONS_FORCESENSORGUITRIGGEREDCMD)
    {
        CForceSensor* it = App::currentWorld->sceneObjects->getForceSensorFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setConsecutiveViolationsToTrigger(cmd.intParams[1]);
    }
    if (cmd.cmdId == APPLY_BREAKING_FORCESENSORGUITRIGGEREDCMD)
    {
        CForceSensor* it = App::currentWorld->sceneObjects->getForceSensorFromHandle(cmd.intParams[0]);
        if (it != nullptr)
        {
            for (size_t i = 1; i < cmd.intParams.size(); i++)
            {
                CForceSensor* it2 = App::currentWorld->sceneObjects->getForceSensorFromHandle(cmd.intParams[i]);
                if (it2 != nullptr)
                {
                    it2->setEnableForceThreshold(it->getEnableForceThreshold());
                    it2->setEnableTorqueThreshold(it->getEnableTorqueThreshold());
                    it2->setForceThreshold(it->getForceThreshold());
                    it2->setTorqueThreshold(it->getTorqueThreshold());
                    it2->setConsecutiveViolationsToTrigger(
                        it->getConsecutiveViolationsToTrigger());
                }
            }
        }
    }
    if (cmd.cmdId == TOGGLE_BACKFACECULLING_SHAPEGUITRIGGEREDCMD)
    {
        CShape* it = App::currentWorld->sceneObjects->getShapeFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setCulling(!it->getCulling());
    }
    if (cmd.cmdId == TOGGLE_WIREFRAME_SHAPEGUITRIGGEREDCMD)
    {
        CShape* it = App::currentWorld->sceneObjects->getShapeFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setShapeWireframe_OLD(!it->getShapeWireframe_OLD());
    }
    if (cmd.cmdId == INVERT_FACES_SHAPEGUITRIGGEREDCMD)
    {
        CShape* it = App::currentWorld->sceneObjects->getShapeFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->invertFrontBack();
    }
    if (cmd.cmdId == TOGGLE_SHOWEDGES_SHAPEGUITRIGGEREDCMD)
    {
        CShape* it = App::currentWorld->sceneObjects->getShapeFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setVisibleEdges(!it->getVisibleEdges());
    }
    if (cmd.cmdId == SET_SHADINGANGLE_SHAPEGUITRIGGEREDCMD)
    {
        CShape* it = App::currentWorld->sceneObjects->getShapeFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setShadingAngle(cmd.doubleParams[0]);
    }
    if (cmd.cmdId == APPLY_OTHERPROP_SHAPEGUITRIGGEREDCMD)
    {
        CShape* last = App::currentWorld->sceneObjects->getShapeFromHandle(cmd.intParams[0]);
        if ((last != nullptr) && (!last->isCompound()))
        {
            for (size_t i = 1; i < cmd.intParams.size(); i++)
            {
                CShape* it = App::currentWorld->sceneObjects->getShapeFromHandle(cmd.intParams[i]);
                if ((it != nullptr) && (!it->isCompound()))
                {
                    it->getSingleMesh()->setVisibleEdges(last->getSingleMesh()->getVisibleEdges());
                    it->getSingleMesh()->setCulling(last->getSingleMesh()->getCulling());
                    it->getSingleMesh()->setInsideAndOutsideFacesSameColor_DEPRECATED(
                        last->getSingleMesh()->getInsideAndOutsideFacesSameColor_DEPRECATED());
                    it->getSingleMesh()->setEdgeWidth_DEPRECATED(last->getSingleMesh()->getEdgeWidth_DEPRECATED());
                    it->getSingleMesh()->setWireframe_OLD(last->getSingleMesh()->getWireframe_OLD());
                    it->getSingleMesh()->setShadingAngle(last->getSingleMesh()->getShadingAngle());
                    it->getSingleMesh()->setEdgeThresholdAngle(last->getSingleMesh()->getEdgeThresholdAngle());
                    it->getSingleMesh()->setHideEdgeBorders_OLD(last->getSingleMesh()->getHideEdgeBorders_OLD());
                    it->getSingleMesh()->setDisplayInverted_DEPRECATED(
                        last->getSingleMesh()->getDisplayInverted_DEPRECATED());
                }
            }
        }
    }
    if (cmd.cmdId == APPLY_VISUALPROP_SHAPEGUITRIGGEREDCMD)
    {
        CShape* last = App::currentWorld->sceneObjects->getShapeFromHandle(cmd.intParams[0]);
        if ((last != nullptr) && (!last->isCompound()))
        {
            for (size_t i = 1; i < cmd.intParams.size(); i++)
            {
                CShape* it = App::currentWorld->sceneObjects->getShapeFromHandle(cmd.intParams[i]);
                if ((it != nullptr) && (!it->isCompound()))
                {
                    last->getSingleMesh()->color.copyYourselfInto(&it->getSingleMesh()->color);
                    last->getSingleMesh()->insideColor_DEPRECATED.copyYourselfInto(
                        &it->getSingleMesh()->insideColor_DEPRECATED);
                    last->getSingleMesh()->edgeColor_DEPRECATED.copyYourselfInto(
                        &it->getSingleMesh()->edgeColor_DEPRECATED);
                    it->actualizeContainsTransparentComponent();
                }
            }
        }
    }
    if (cmd.cmdId == CLEAR_TEXTURES_SHAPEGUITRIGGEREDCMD)
    {
        for (size_t i = 0; i < cmd.intParams.size(); i++)
        {
            CShape* shape = App::currentWorld->sceneObjects->getShapeFromHandle(cmd.intParams[i]);
            if (shape != nullptr)
            {
                std::vector<CMesh*> components;
                shape->getMesh()->getAllMeshComponentsCumulative(C7Vector::identityTransformation, components);
                for (size_t j = 0; j < components.size(); j++)
                {
                    CTextureProperty* tp = components[j]->getTextureProperty();
                    if (tp != nullptr)
                    {
                        App::currentWorld->textureContainer->announceGeneralObjectWillBeErased(shape->getObjectHandle(), -1);
                        delete tp;
                        components[j]->setTextureProperty(nullptr);
                    }
                }
            }
        }
    }
    if (cmd.cmdId == SET_QUICKTEXTURES_SHAPEGUITRIGGEREDCMD)
    {
        bool rgba = cmd.boolParams[0];
        int resX = cmd.intParams[cmd.intParams.size() - 2];
        int resY = cmd.intParams[cmd.intParams.size() - 1];
        std::string texName(cmd.stringParams[0]);
        int n = 3;
        if (rgba)
            n = 4;

        // 1. Remove existing textures:
        std::vector<CShape*> shapeList;
        for (size_t i = 0; i < cmd.intParams.size() - 2; i++)
        {
            CShape* shape = App::currentWorld->sceneObjects->getShapeFromHandle(cmd.intParams[i]);
            if (shape != nullptr)
            {
                shapeList.push_back(shape);
                std::vector<CMesh*> components;
                shape->getMesh()->getAllMeshComponentsCumulative(C7Vector::identityTransformation, components);
                for (size_t j = 0; j < components.size(); j++)
                {
                    CTextureProperty* tp = components[j]->getTextureProperty();
                    if (tp != nullptr)
                    {
                        App::currentWorld->textureContainer->announceGeneralObjectWillBeErased(shape->getObjectHandle(), -1);
                        delete tp;
                        components[j]->setTextureProperty(nullptr);
                    }
                }
            }
        }

        // 2. Load and apply the texture:
        if (shapeList.size() != 0)
        {
            CTextureObject* textureObj = new CTextureObject(resX, resY);
            textureObj->setImage(rgba, false, false, &cmd.uint8Params[0]); // keep false,false
            textureObj->setObjectName(texName.c_str());
            for (size_t i = 0; i < shapeList.size(); i++)
            {
                CShape* shape = shapeList[i];
                std::vector<CMesh*> components;
                shape->getMesh()->getAllMeshComponentsCumulative(C7Vector::identityTransformation, components);
                for (size_t j = 0; j < components.size(); j++)
                {
                    CMesh* geom = components[j];
                    textureObj->addDependentObject(shape->getObjectHandle(), geom->getUniqueID());
                }
            }

            int textureID = App::currentWorld->textureContainer->addObject(
                textureObj, false); // might erase the textureObj and return a similar object already present!!

            for (size_t i = 0; i < shapeList.size(); i++)
            {
                CShape* shape = shapeList[i];
                C3Vector bbhs(shape->getBBHSize());
                double s = std::max<double>(std::max<double>(bbhs(0), bbhs(1)), bbhs(2)) * 2.0;
                std::vector<CMesh*> components;
                shape->getMesh()->getAllMeshComponentsCumulative(C7Vector::identityTransformation, components);
                for (size_t j = 0; j < components.size(); j++)
                {
                    CMesh* geom = components[j];
                    CTextureProperty* tp = new CTextureProperty(textureID);
                    tp->setRepeatU(true);
                    tp->setRepeatV(true);
                    tp->setTextureMapMode(sim_texturemap_cube);
                    tp->setInterpolateColors(true);
                    tp->setApplyMode(0);
                    tp->setTextureScaling(s, s);
                    geom->setTextureProperty(tp);
                }
            }
        }
    }

    if (cmd.cmdId == APPLY_SIZE_GEOMETRYGUITRIGGEREDCMD)
    {
        CShape* it = App::currentWorld->sceneObjects->getShapeFromHandle(cmd.intParams[0]);
        if (it != nullptr)
        {
            C3Vector bbhalfSizes(it->getBBHSize());
            double xSizeOriginal = 2.0 * bbhalfSizes(0);
            double ySizeOriginal = 2.0 * bbhalfSizes(1);
            double zSizeOriginal = 2.0 * bbhalfSizes(2);
            double s[3] = {1.0, 1.0, 1.0}; // imagine we have a plane that has dims x*y*0! keep default at 1.0

            if (xSizeOriginal != 0.0)
                s[0] = cmd.doubleParams[0] / xSizeOriginal;
            if (ySizeOriginal != 0.0)
                s[1] = cmd.doubleParams[1] / ySizeOriginal;
            if (zSizeOriginal != 0.0)
                s[2] = cmd.doubleParams[2] / zSizeOriginal;
            it->scaleObjectNonIsometrically(s[0], s[1], s[2]);
        }
    }
    if (cmd.cmdId == APPLY_SCALING_GEOMETRYGUITRIGGEREDCMD)
    {
        CShape* it = App::currentWorld->sceneObjects->getShapeFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->scaleObjectNonIsometrically(cmd.doubleParams[0], cmd.doubleParams[1], cmd.doubleParams[2]);
    }
    if (cmd.cmdId == COMMAND_QUEUE_UITRIGGEREDCMD)
        App::currentWorld->outsideCommandQueue_old->addCommand(cmd.intParams[0], cmd.intParams[1], cmd.intParams[2], cmd.intParams[3], cmd.intParams[4], nullptr, 0);
    if (cmd.cmdId == TOGGLE_BOOLPROP_TEXTUREGUITRIGGEREDCMD)
    {
        CTextureProperty* it = GuiApp::getTexturePropertyPointerFromItem(
            cmd.intParams[0], cmd.intParams[1], cmd.intParams[2], nullptr, nullptr, nullptr, nullptr);
        if (it != nullptr)
        {
            if (cmd.intParams[3] == 0)
                it->setInterpolateColors(!it->getInterpolateColors());
            if (cmd.intParams[3] == 2)
                it->setRepeatU(!it->getRepeatU());
            if (cmd.intParams[3] == 3)
                it->setRepeatV(!it->getRepeatV());
        }
    }
    if (cmd.cmdId == SET_3DCONFIG_TEXTUREGUITRIGGEREDCMD)
    {
        CTextureProperty* it = GuiApp::getTexturePropertyPointerFromItem(
            cmd.intParams[0], cmd.intParams[1], cmd.intParams[2], nullptr, nullptr, nullptr, nullptr);
        if (it != nullptr)
        {
            C7Vector tr(it->getTextureRelativeConfig());
            if (cmd.intParams[3] < 3)
            { // position
                double newVal = tt::getLimitedFloat(-100.0, 100.0, cmd.doubleParams[0]);
                tr.X(cmd.intParams[3]) = newVal;
            }
            else
            { // orientation
                C3Vector euler(tr.Q.getEulerAngles());
                euler(cmd.intParams[3] - 3) = cmd.doubleParams[0];
                tr.Q.setEulerAngles(euler);
            }
            it->setTextureRelativeConfig(tr);
        }
    }
    if (cmd.cmdId == SET_SCALING_TEXTUREGUITRIGGEREDCMD)
    {
        CTextureProperty* it = GuiApp::getTexturePropertyPointerFromItem(
            cmd.intParams[0], cmd.intParams[1], cmd.intParams[2], nullptr, nullptr, nullptr, nullptr);
        if (it != nullptr)
        {
            double x, y;
            it->getTextureScaling(x, y);
            double newVal = cmd.doubleParams[0];
            if (newVal >= 0.0)
                newVal = tt::getLimitedFloat(0.001, 1000.0, newVal);
            else
                newVal = tt::getLimitedFloat(-1000.0, -0.001, newVal);
            if (cmd.intParams[3] == 0)
                it->setTextureScaling(newVal, y);
            else
                it->setTextureScaling(x, newVal);
        }
    }
    if (cmd.cmdId == SET_MAPPINGMODE_TEXTUREGUITRIGGEREDCMD)
    {
        CTextureProperty* it = GuiApp::getTexturePropertyPointerFromItem(
            cmd.intParams[0], cmd.intParams[1], cmd.intParams[2], nullptr, nullptr, nullptr, nullptr);
        if (it != nullptr)
        {
            bool usingFixedTextureCoordinates = it->getFixedCoordinates();
            int mode = cmd.intParams[3];
            int previousMode = it->getTextureMapMode();
            bool setOk = false;
            if ((mode == sim_texturemap_plane) && ((previousMode != mode) || usingFixedTextureCoordinates))
                setOk = true;
            if ((mode == sim_texturemap_cylinder) && (previousMode != mode))
                setOk = true;
            if ((mode == sim_texturemap_sphere) && (previousMode != mode))
                setOk = true;
            if ((mode == sim_texturemap_cube) && (previousMode != mode))
                setOk = true;
            if (setOk)
                it->setTextureMapMode(mode);
        }
    }
    if (cmd.cmdId == SET_APPLYMODE_TEXTUREGUITRIGGEREDCMD)
    {
        CTextureProperty* it = GuiApp::getTexturePropertyPointerFromItem(
            cmd.intParams[0], cmd.intParams[1], cmd.intParams[2], nullptr, nullptr, nullptr, nullptr);
        if (it != nullptr)
            it->setApplyMode(cmd.intParams[3]);
    }
    if (cmd.cmdId == LOAD_ANDAPPLY_TEXTUREGUITRIGGEREDCMD)
    {
        CMesh* geom = nullptr;
        bool valid = false;
        bool is3D = false;
        GuiApp::getTexturePropertyPointerFromItem(cmd.intParams[0], cmd.intParams[1], cmd.intParams[2], nullptr, &is3D,
                                                  &valid, &geom);
        if (valid)
        {
            int resX = cmd.intParams[3];
            int resY = cmd.intParams[4];
            int n = cmd.intParams[5];
            bool rgba = (n == 4);
            CTextureObject* textureObj = new CTextureObject(resX, resY);
            textureObj->setImage(rgba, false, false, &cmd.uint8Params[0]); // keep false,false
            textureObj->setObjectName(cmd.stringParams[0].c_str());
            if (geom != nullptr)
                textureObj->addDependentObject(cmd.intParams[1], geom->getUniqueID());
            else
            {
                if (cmd.intParams[0] == TEXTURE_ID_OPENGL_GUI_BACKGROUND)
                    textureObj->addDependentObject(cmd.intParams[1], 0); // 0 is for background texture on 2DElement
                if (cmd.intParams[0] == TEXTURE_ID_OPENGL_GUI_BUTTON)
                {
                    CButtonBlock* block = App::currentWorld->buttonBlockContainer_old->getBlockWithID(cmd.intParams[1]);
                    CSoftButton* butt = block->getButtonWithID(cmd.intParams[2]);
                    textureObj->addDependentObject(cmd.intParams[1], butt->getUniqueID()); // Unique ID starts exceptionnally at 1
                }
            }
            int textureID = App::currentWorld->textureContainer->addObject(
                textureObj, false); // might erase the textureObj and return a similar object already present!!
            CTextureProperty* tp = new CTextureProperty(textureID);
            if (geom != nullptr)
                geom->setTextureProperty(tp);
            else
            {
                tp->setApplyMode(1); // 13/1/2012
                CButtonBlock* block = App::currentWorld->buttonBlockContainer_old->getBlockWithID(cmd.intParams[1]);
                if (cmd.intParams[0] == TEXTURE_ID_OPENGL_GUI_BACKGROUND)
                    block->setTextureProperty(tp);
                if (cmd.intParams[0] == TEXTURE_ID_OPENGL_GUI_BUTTON)
                {
                    CSoftButton* butt = block->getButtonWithID(cmd.intParams[2]);
                    butt->setTextureProperty(tp);
                }
            }
        }
    }
    if (cmd.cmdId == SELECT_REMOVE_TEXTUREGUITRIGGEREDCMD)
    {
        CMesh* geom = nullptr;
        bool valid = false;
        bool is3D = false;
        int tObject = cmd.intParams[3];
        CTextureProperty* tp = GuiApp::getTexturePropertyPointerFromItem(
            cmd.intParams[0], cmd.intParams[1], cmd.intParams[2], nullptr, &is3D, &valid, &geom);
        if (valid)
        {
            if (geom != nullptr)
            {
                if (tp != nullptr)
                { // remove the texture
                    App::currentWorld->textureContainer->announceGeneralObjectWillBeErased(cmd.intParams[1], geom->getUniqueID());
                    delete tp;
                    geom->setTextureProperty(nullptr);
                }
                else
                { // add an existing texture
                    if (tObject != -1)
                    {
                        if (tObject > SIM_IDEND_SCENEOBJECT)
                        {
                            CTextureObject* to = App::currentWorld->textureContainer->getObject(tObject);
                            to->addDependentObject(cmd.intParams[1], geom->getUniqueID());
                            tp = new CTextureProperty(tObject);
                            geom->setTextureProperty(tp);
                            tp->setTextureObjectID(tObject);
                        }
                    }
                }
            }
            if (cmd.intParams[0] == TEXTURE_ID_OPENGL_GUI_BACKGROUND)
            {
                CButtonBlock* block = App::currentWorld->buttonBlockContainer_old->getBlockWithID(cmd.intParams[1]);
                if (tp != nullptr)
                { // remove the texture
                    App::currentWorld->textureContainer->announceGeneralObjectWillBeErased(cmd.intParams[1], 0);
                    delete tp;
                    block->setTextureProperty(nullptr);
                }
                else
                { // add an existing texture
                    if (tObject != -1)
                    {
                        if (tObject > SIM_IDEND_SCENEOBJECT)
                        {
                            CTextureObject* to = App::currentWorld->textureContainer->getObject(tObject);
                            to->addDependentObject(cmd.intParams[1], 0);
                        }
                        tp = new CTextureProperty(tObject);
                        tp->setApplyMode(1); // 13/1/2012
                        block->setTextureProperty(tp);
                    }
                }
            }
            if (cmd.intParams[0] == TEXTURE_ID_OPENGL_GUI_BUTTON)
            { // texture is linked to a 2DElement button
                CButtonBlock* block = App::currentWorld->buttonBlockContainer_old->getBlockWithID(cmd.intParams[1]);
                CSoftButton* button = block->getButtonWithID(cmd.intParams[2]);
                if (tp != nullptr)
                { // remove the texture
                    App::currentWorld->textureContainer->announceGeneralObjectWillBeErased(cmd.intParams[1], cmd.intParams[2]);
                    delete tp;
                    button->setTextureProperty(nullptr);
                }
                else
                { // add an existing texture
                    if (tObject != -1)
                    {
                        if (tObject > SIM_IDEND_SCENEOBJECT)
                        {
                            CTextureObject* to = App::currentWorld->textureContainer->getObject(tObject);
                            to->addDependentObject(cmd.intParams[1], cmd.intParams[2]);
                        }
                        tp = new CTextureProperty(tObject);
                        tp->setApplyMode(1); // 13/1/2012
                        button->setTextureProperty(tp);
                    }
                }
            }
        }
    }

    if (cmd.cmdId == TOGGLE_BACKFACECULLING_MULTISHAPEEDITIONGUITRIGGEREDCMD)
    {
        CShape* it = App::currentWorld->sceneObjects->getShapeFromHandle(cmd.intParams[0]);
        if (it != nullptr)
        {
            std::vector<CMesh*> geoms;
            it->getMesh()->getAllMeshComponentsCumulative(C7Vector::identityTransformation, geoms);
            int index = cmd.intParams[1];
            if ((index >= 0) && (index < int(geoms.size())))
            {
                CMesh* geom = geoms[index];
                geom->setCulling(!geom->getCulling());
            }
        }
    }
    if (cmd.cmdId == TOGGLE_SHOWEDGES_MULTISHAPEEDITIONGUITRIGGEREDCMD)
    {
        CShape* it = App::currentWorld->sceneObjects->getShapeFromHandle(cmd.intParams[0]);
        if (it != nullptr)
        {
            std::vector<CMesh*> geoms;
            it->getMesh()->getAllMeshComponentsCumulative(C7Vector::identityTransformation, geoms);
            int index = cmd.intParams[1];
            if ((index >= 0) && (index < int(geoms.size())))
            {
                CMesh* geom = geoms[index];
                geom->setVisibleEdges(!geom->getVisibleEdges());
            }
        }
    }
    if (cmd.cmdId == SET_SHADINGANGLE_MULTISHAPEEDITIONGUITRIGGEREDCMD)
    {
        CShape* it = App::currentWorld->sceneObjects->getShapeFromHandle(cmd.intParams[0]);
        if (it != nullptr)
        {
            std::vector<CMesh*> geoms;
            it->getMesh()->getAllMeshComponentsCumulative(C7Vector::identityTransformation, geoms);
            int index = cmd.intParams[1];
            if ((index >= 0) && (index < int(geoms.size())))
            {
                CMesh* geom = geoms[index];
                geom->setShadingAngle(cmd.doubleParams[0]);
            }
        }
    }

    if (cmd.cmdId == TOGGLE_LAYER_LAYERGUITRIGGEREDCMD)
    {
        App::currentWorld->environment->setActiveLayers(App::currentWorld->environment->getActiveLayers() ^ cmd.intParams[0]);
    }
    if (cmd.cmdId == TOGGLE_SHOWDYNCONTENT_LAYERGUITRIGGEREDCMD)
    {
        App::currentWorld->simulation->setDynamicContentVisualizationOnly(
            !App::currentWorld->simulation->getDynamicContentVisualizationOnly());
    }

    if (cmd.cmdId == SET_ROLLEDUPSIZES_ROLLEDUPGUITRIGGEREDCMD)
    {
        CButtonBlock* it = App::currentWorld->buttonBlockContainer_old->getBlockWithID(cmd.intParams[0]);
        if (it != nullptr)
        {
            VPoint s;
            s.x = cmd.intParams[1];
            s.y = cmd.intParams[2];
            it->getRollupMin(s);
            s.x = cmd.intParams[3];
            s.y = cmd.intParams[4];
            it->getRollupMax(s);
        }
    }

    if (cmd.cmdId == SET_OFFFSET_JOINTDEPENDENCYGUITRIGGEREDCMD)
    {
        CJoint* it = App::currentWorld->sceneObjects->getJointFromHandle(cmd.intParams[0]);
        if (it != nullptr)
        {
            double off, mult;
            it->getDependencyParams(off, mult);
            it->setDependencyParams(cmd.doubleParams[0], mult);
        }
    }
    if (cmd.cmdId == SET_MULTFACT_JOINTDEPENDENCYGUITRIGGEREDCMD)
    {
        CJoint* it = App::currentWorld->sceneObjects->getJointFromHandle(cmd.intParams[0]);
        if (it != nullptr)
        {
            double off, mult;
            it->getDependencyParams(off, mult);
            it->setDependencyParams(off, cmd.doubleParams[0]);
        }
    }
    if (cmd.cmdId == SET_OTHERJOINT_JOINTDEPENDENCYGUITRIGGEREDCMD)
    {
        CJoint* it = App::currentWorld->sceneObjects->getJointFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setDependencyMasterJointHandle(cmd.intParams[1]);
    }

    if (cmd.cmdId == TOGGLE_CYCLIC_JOINTGUITRIGGEREDCMD)
    {
        CJoint* it = App::currentWorld->sceneObjects->getJointFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setIsCyclic(!it->getIsCyclic());
    }
    if (cmd.cmdId == SET_LEAD_JOINTGUITRIGGEREDCMD)
    {
        CJoint* it = App::currentWorld->sceneObjects->getJointFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setScrewLead(cmd.doubleParams[0]);
    }
    if (cmd.cmdId == SET_MINPOS_JOINTGUITRIGGEREDCMD)
    {
        CJoint* it = App::currentWorld->sceneObjects->getJointFromHandle(cmd.intParams[0]);
        if (it != nullptr)
        {
            double minP, maxP;
            it->getInterval(minP, maxP);
            it->setInterval(cmd.doubleParams[0], cmd.doubleParams[0] + maxP - minP);
        }
    }
    if (cmd.cmdId == SET_RANGE_JOINTGUITRIGGEREDCMD)
    {
        CJoint* it = App::currentWorld->sceneObjects->getJointFromHandle(cmd.intParams[0]);
        if (it != nullptr)
        {
            double minP, maxP;
            it->getInterval(minP, maxP);
            it->setInterval(minP, minP + cmd.doubleParams[0]);
        }
    }
    if (cmd.cmdId == SET_POS_JOINTGUITRIGGEREDCMD)
    {
        CJoint* it = App::currentWorld->sceneObjects->getJointFromHandle(cmd.intParams[0]);
        if (it != nullptr)
        {
            it->setPosition(cmd.doubleParams[0]);
            it->setTargetPosition(cmd.doubleParams[0]);
        }
    }
    if (cmd.cmdId == APPLY_CONFIGPARAMS_JOINTGUITRIGGEREDCMD)
    {
        CJoint* last = App::currentWorld->sceneObjects->getJointFromHandle(cmd.intParams[0]);
        if (last != nullptr)
        {
            for (size_t i = 1; i < cmd.intParams.size(); i++)
            {
                CJoint* it = App::currentWorld->sceneObjects->getJointFromHandle(cmd.intParams[i]);
                if ((it != nullptr) && (last->getJointType() == it->getJointType()))
                {
                    it->setIsCyclic(last->getIsCyclic());
                    double minV, maxV;
                    last->getInterval(minV, maxV);
                    it->setInterval(minV, maxV);
                    it->setPosition(last->getPosition());
                    it->setSphericalTransformation(last->getSphericalTransformation());
                    it->setScrewLead(last->getScrewLead());
                    it->setIKWeight_old(last->getIKWeight_old());
                    it->setMaxStepSize_old(last->getMaxStepSize_old());
                }
            }
        }
    }
    if (cmd.cmdId == SET_MODE_JOINTGUITRIGGEREDCMD)
    {
        CJoint* it = App::currentWorld->sceneObjects->getJointFromHandle(cmd.intParams[0]);
        if (it != nullptr)
        {
            if ((cmd.intParams[1] & sim_jointmode_hybrid_deprecated) != 0)
            {
                it->setJointMode(cmd.intParams[1] - sim_jointmode_hybrid_deprecated);
                it->setHybridFunctionality_old(true);
            }
            else
            {
                it->setJointMode(cmd.intParams[1]);
                it->setHybridFunctionality_old(false);
            }
        }
    }
    if (cmd.cmdId == APPLY_MODEPARAMS_JOINTGUITRIGGEREDCMD)
    {
        CJoint* last = App::currentWorld->sceneObjects->getJointFromHandle(cmd.intParams[0]);
        if (last != nullptr)
        {
            for (size_t i = 1; i < cmd.intParams.size(); i++)
            {
                CJoint* it = App::currentWorld->sceneObjects->getJointFromHandle(cmd.intParams[i]);
                if ((it != nullptr) && (last->getJointType() == it->getJointType()))
                {
                    it->setJointMode(last->getJointMode());
                    it->setHybridFunctionality_old(last->getHybridFunctionality_old());
                }
            }
        }
    }
    if (cmd.cmdId == APPLY_VISUALPARAMS_JOINTGUITRIGGEREDCMD)
    {
        CJoint* last = App::currentWorld->sceneObjects->getJointFromHandle(cmd.intParams[0]);
        if (last != nullptr)
        {
            for (size_t i = 1; i < cmd.intParams.size(); i++)
            {
                CJoint* it = App::currentWorld->sceneObjects->getJointFromHandle(cmd.intParams[i]);
                if ((it != nullptr) && (last->getJointType() == it->getJointType()))
                {
                    last->getColor(false)->copyYourselfInto(it->getColor(false));
                    last->getColor(true)->copyYourselfInto(it->getColor(true));
                    it->setSize(last->getLength(), last->getDiameter());
                }
            }
        }
    }
    if (cmd.cmdId == SET_LENGTH_JOINTGUITRIGGEREDCMD)
    {
        CJoint* it = App::currentWorld->sceneObjects->getJointFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setSize(cmd.doubleParams[0], 0.0);
    }
    if (cmd.cmdId == SET_DIAMETER_JOINTGUITRIGGEREDCMD)
    {
        CJoint* it = App::currentWorld->sceneObjects->getJointFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setSize(0.0, cmd.doubleParams[0]);
    }
    if (cmd.cmdId == SET_TARGETVELOCITY_JOINTDYNGUITRIGGEREDCMD)
    {
        CJoint* it = App::currentWorld->sceneObjects->getJointFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setTargetVelocity(cmd.doubleParams[0]);
    }
    if (cmd.cmdId == SET_FORCE_JOINTDYNGUITRIGGEREDCMD)
    {
        CJoint* it = App::currentWorld->sceneObjects->getJointFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setTargetForce(cmd.doubleParams[0], true);
    }
    if (cmd.cmdId == SET_MAXFORCE_JOINTDYNGUITRIGGEREDCMD)
    {
        CJoint* it = App::currentWorld->sceneObjects->getJointFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setTargetForce(cmd.doubleParams[0], false);
    }
    if (cmd.cmdId == APPLY_PARAMS_JOINTDYNGUITRIGGEREDCMD)
    {
        CJoint* last = App::currentWorld->sceneObjects->getJointFromHandle(cmd.intParams[0]);
        if ((last != nullptr) && ((last->getJointMode() == sim_jointmode_dynamic) || last->getHybridFunctionality_old()))
        {
            for (size_t i = 1; i < cmd.intParams.size(); i++)
            {
                CJoint* it = App::currentWorld->sceneObjects->getJointFromHandle(cmd.intParams[i]);
                if ((it != nullptr) && (last->getJointType() == it->getJointType()))
                {
                    if ((it->getJointMode() == last->getJointMode()) || (last->getHybridFunctionality_old() && it->getHybridFunctionality_old()))
                    {
                        it->setDynCtrlMode(last->getDynCtrlMode());
                        it->setDynPosCtrlType(last->getDynPosCtrlType());
                        it->setTargetForce(last->getTargetForce(true), true);
                        it->setTargetVelocity(last->getTargetVelocity());
                        it->setMotorLock(last->getMotorLock());
                        it->setTargetPosition(last->getTargetPosition());
                        double maxVelAccelJerk[3];
                        last->getMaxVelAccelJerk(maxVelAccelJerk);
                        it->setMaxVelAccelJerk(maxVelAccelJerk);
                        double kp, cp;
                        last->getKc(kp, cp);
                        it->setKc(kp, cp);
                    }
                    last->copyEnginePropertiesTo(it);
                }
            }
        }
    }
    if (cmd.cmdId == SET_MOTIONPROFILEVALS_JOINTDYNGUITRIGGEREDCMD)
    {
        CJoint* it = App::currentWorld->sceneObjects->getJointFromHandle(cmd.intParams[0]);
        if (it != nullptr)
        {
            double maxVelAccelJerk[3];
            it->getMaxVelAccelJerk(maxVelAccelJerk);
            maxVelAccelJerk[cmd.intParams[1]] = cmd.doubleParams[0];
            it->setMaxVelAccelJerk(maxVelAccelJerk);
        }
    }
    if (cmd.cmdId == SET_TARGETPOSITION_JOINTDYNGUITRIGGEREDCMD)
    {
        CJoint* it = App::currentWorld->sceneObjects->getJointFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setTargetPosition(cmd.doubleParams[0]);
    }
    if (cmd.cmdId == SET_KCVALUES_JOINTDYNGUITRIGGEREDCMD)
    {
        CJoint* it = App::currentWorld->sceneObjects->getJointFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setKc(cmd.doubleParams[0], cmd.doubleParams[1]);
    }
    if (cmd.cmdId == SET_JOINTCTRLMODE_JOINTDYNGUITRIGGEREDCMD)
    {
        CJoint* it = App::currentWorld->sceneObjects->getJointFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setDynCtrlMode(cmd.intParams[1]);
    }
    if (cmd.cmdId == SET_JOINTPOSCTRLMODETOGGLE_JOINTDYNGUITRIGGEREDCMD)
    {
        CJoint* it = App::currentWorld->sceneObjects->getJointFromHandle(cmd.intParams[0]);
        if (it != nullptr)
        {
            if (it->getDynPosCtrlType() == 0)
                it->setDynPosCtrlType(1);
            else
                it->setDynPosCtrlType(0);
        }
    }
    if (cmd.cmdId == TOGGLE_JOINTVELCTRLMODETYPE_JOINTDYNGUITRIGGEREDCMD)
    {
        CJoint* it = App::currentWorld->sceneObjects->getJointFromHandle(cmd.intParams[0]);
        if (it != nullptr)
        {
            if (it->getDynVelCtrlType() == 0)
                it->setDynVelCtrlType(1);
            else
                it->setDynVelCtrlType(0);
        }
    }

    if (cmd.cmdId == TOGGLE_LOCKMOTOR_JOINTDYNGUITRIGGEREDCMD)
    {
        CJoint* it = App::currentWorld->sceneObjects->getJointFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setMotorLock(!it->getMotorLock());
    }
    if (cmd.cmdId == APPLY_ALLENGINEPARAMS_JOINTDYNGUITRIGGEREDCMD)
    {
        CJoint* it = App::currentWorld->sceneObjects->getJointFromHandle(cmd.intParams[0]);
        if (it != nullptr)
        {
            for (size_t i = 1; i < cmd.intParams.size(); i++)
            {
                CJoint* anotherJoint = App::currentWorld->sceneObjects->getJointFromHandle(cmd.intParams[i]);
                if (anotherJoint != nullptr)
                    it->copyEnginePropertiesTo(anotherJoint);
            }
        }
    }

    if (cmd.cmdId == SET_ATTRIBUTES_PATH_OLD_GUITRIGGEREDCMD)
    {
        CPath_old* it = App::currentWorld->sceneObjects->getPathFromHandle(cmd.intParams[0]);
        if ((it != nullptr) && (it->pathContainer != nullptr))
            it->pathContainer->setAttributes(cmd.intParams[1]);
    }
    if (cmd.cmdId == SET_LINESIZE_PATH_OLD_GUITRIGGEREDCMD)
    {
        CPath_old* it = App::currentWorld->sceneObjects->getPathFromHandle(cmd.intParams[0]);
        if ((it != nullptr) && (it->pathContainer != nullptr))
            it->pathContainer->setLineSize(cmd.intParams[1]);
    }
    if (cmd.cmdId == SET_CTRLPTSIZE_PATH_OLD_GUITRIGGEREDCMD)
    {
        CPath_old* it = App::currentWorld->sceneObjects->getPathFromHandle(cmd.intParams[0]);
        if ((it != nullptr) && (it->pathContainer != nullptr))
            it->pathContainer->setSquareSize(cmd.doubleParams[0]);
    }
    if (cmd.cmdId == SET_DISTANCEUNIT_PATH_OLD_GUITRIGGEREDCMD)
    {
        CPath_old* it = App::currentWorld->sceneObjects->getPathFromHandle(cmd.intParams[0]);
        if ((it != nullptr) && (it->pathContainer != nullptr))
            it->pathContainer->setPathLengthCalculationMethod(cmd.intParams[1]);
    }
    if (cmd.cmdId == COPY_TO_CLIPBOARD_PATH_OLD_GUITRIGGEREDCMD)
    {
        CPath_old* it = App::currentWorld->sceneObjects->getPathFromHandle(cmd.intParams[0]);
        if ((it != nullptr) && (it->pathContainer != nullptr))
        {
            it->pathContainer->copyPointsToClipboard();
            App::logMsg(sim_verbosity_scriptinfos, "Path points copied to status bar.");
        }
    }
    if (cmd.cmdId == CREATE_EQUIVALENT_PATH_OLD_GUITRIGGEREDCMD)
    {
        CPath_old* it = App::currentWorld->sceneObjects->getPathFromHandle(cmd.intParams[0]);
        if ((it != nullptr) && (it->pathContainer != nullptr))
        {
            it->pathContainer->createEquivalent(it->getObjectHandle());
            App::logMsg(sim_verbosity_scriptinfos, "Equivalent path object created.");
        }
    }
    if (cmd.cmdId == TOGGLE_SHAPINGENABLED_PATH_OLD_SHAPINGGUITRIGGEREDCMD)
    {
        CPath_old* it = App::currentWorld->sceneObjects->getPathFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setShapingEnabled(!it->getShapingEnabled());
    }
    if (cmd.cmdId == TOGGLE_FOLLOWORIENTATION_PATH_OLD_SHAPINGGUITRIGGEREDCMD)
    {
        CPath_old* it = App::currentWorld->sceneObjects->getPathFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setShapingFollowFullOrientation(!it->getShapingFollowFullOrientation());
    }
    if (cmd.cmdId == TOGGLE_CONVEXHULLS_PATH_OLD_SHAPINGGUITRIGGEREDCMD)
    {
        CPath_old* it = App::currentWorld->sceneObjects->getPathFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setShapingThroughConvexHull(!it->getShapingThroughConvexHull());
    }
    if (cmd.cmdId == TOGGLE_LASTCOORDLINKSTOFIRST_PATH_OLD_SHAPINGGUITRIGGEREDCMD)
    {
        CPath_old* it = App::currentWorld->sceneObjects->getPathFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setShapingSectionClosed(!it->getShapingSectionClosed());
    }
    if (cmd.cmdId == GENERATE_SHAPE_PATH_OLD_SHAPINGGUITRIGGEREDCMD)
    {
        CPath_old* it = App::currentWorld->sceneObjects->getPathFromHandle(cmd.intParams[0]);
        if (it != nullptr)
        {
            CShape* shape = it->getShape();
            if (shape != nullptr)
                App::currentWorld->sceneObjects->addObjectToScene(shape, false, true);
        }
    }
    if (cmd.cmdId == SET_ELEMENTMAXLENGTH_PATH_OLD_SHAPINGGUITRIGGEREDCMD)
    {
        CPath_old* it = App::currentWorld->sceneObjects->getPathFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setShapingElementMaxLength(cmd.doubleParams[0]);
    }
    if (cmd.cmdId == SET_TYPE_PATH_OLD_SHAPINGGUITRIGGEREDCMD)
    {
        CPath_old* it = App::currentWorld->sceneObjects->getPathFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setShapingType(cmd.intParams[1]);
    }
    if (cmd.cmdId == SET_SCALINGFACTOR_PATH_OLD_SHAPINGGUITRIGGEREDCMD)
    {
        CPath_old* it = App::currentWorld->sceneObjects->getPathFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setShapingScaling(cmd.doubleParams[0]);
    }
    if (cmd.cmdId == SET_COORDINATES_PATH_OLD_SHAPINGGUITRIGGEREDCMD)
    {
        CPath_old* it = App::currentWorld->sceneObjects->getPathFromHandle(cmd.intParams[0]);
        if (it != nullptr)
        {
            it->shapingCoordinates.assign(cmd.doubleParams.begin(), cmd.doubleParams.end());
            it->setShapingElementMaxLength(it->getShapingElementMaxLength()); // To trigger an actualization!
        }
    }

    if (cmd.cmdId == TOGGLE_STATIC_SHAPEDYNGUITRIGGEREDCMD)
    {
        CShape* it = App::currentWorld->sceneObjects->getShapeFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setStatic(!it->getStatic());
    }
    if (cmd.cmdId == TOGGLE_STARTINSLEEPMODE_SHAPEDYNGUITRIGGEREDCMD)
    {
        CShape* it = App::currentWorld->sceneObjects->getShapeFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setStartInDynamicSleeping(!it->getStartInDynamicSleeping());
    }
    if (cmd.cmdId == TOGGLE_RESPONDABLE_SHAPEDYNGUITRIGGEREDCMD)
    {
        CShape* it = App::currentWorld->sceneObjects->getShapeFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setRespondable(!it->getRespondable());
    }
    if (cmd.cmdId == SET_RESPONDABLEMASK_SHAPEDYNGUITRIGGEREDCMD)
    {
        CShape* it = App::currentWorld->sceneObjects->getShapeFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setRespondableMask(cmd.intParams[1]);
    }
    if (cmd.cmdId == SET_MASS_SHAPEDYNGUITRIGGEREDCMD)
    {
        CShape* it = App::currentWorld->sceneObjects->getShapeFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->getMesh()->setMass(cmd.doubleParams[0]);
    }
    if (cmd.cmdId == SET_INERTIAMATRIX_SHAPEDYNGUITRIGGEREDCMD)
    {
        CShape* it = App::currentWorld->sceneObjects->getShapeFromHandle(cmd.intParams[0]);
        if (it != nullptr)
        {
            C3X3Matrix m(it->getMesh()->getInertia());
            m(size_t(cmd.intParams[1]), size_t(cmd.intParams[2])) = cmd.doubleParams[0];
            if (!cmd.boolParams[0])
                m(size_t(cmd.intParams[1]), size_t(cmd.intParams[2])) /= it->getMesh()->getMass();
            it->getMesh()->setInertia(m, cmd.intParams[1], cmd.intParams[2]);
        }
    }
    if (cmd.cmdId == SET_COMMATRIX_SHAPEDYNGUITRIGGEREDCMD)
    {
        CShape* it = App::currentWorld->sceneObjects->getShapeFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->getMesh()->setCOM(cmd.posParams[0]);
    }
    if (cmd.cmdId == APPLY_DYNPARAMS_SHAPEDYNGUITRIGGEREDCMD)
    {
        CShape* last = App::currentWorld->sceneObjects->getShapeFromHandle(cmd.intParams[0]);
        if (last != nullptr)
        {
            bool lastIsHeightfield = (last->getMesh()->getPurePrimitiveType() == sim_primitiveshape_heightfield);
            for (size_t i = 1; i < cmd.intParams.size(); i++)
            {
                CShape* it = App::currentWorld->sceneObjects->getShapeFromHandle(cmd.intParams[i]);
                if (it != nullptr)
                {
                    bool itIsHeightfield = (it->getMesh()->getPurePrimitiveType() == sim_primitiveshape_heightfield);
                    if (lastIsHeightfield)
                    { // Heightfields cannot be non-static
                        if (!itIsHeightfield)
                            it->setStatic(true);
                    }
                    else
                    {
                        if (!itIsHeightfield)
                        {
                            it->setStatic(last->getStatic());
                            it->setStartInDynamicSleeping(last->getStartInDynamicSleeping());
                            it->setSetAutomaticallyToNonStaticIfGetsParent(
                                last->getSetAutomaticallyToNonStaticIfGetsParent());
                            it->getMesh()->setMass(last->getMesh()->getMass());
                            it->getMesh()->setInertia(last->getMesh()->getInertia());
                            it->getMesh()->setCOM(last->getMesh()->getCOM());
                        }
                    }
                }
            }
        }
    }
    if (cmd.cmdId == TOGGLE_SETTODYNAMICIFGETSPARENT_SHAPEDYNGUITRIGGEREDCMD)
    {
        CShape* it = App::currentWorld->sceneObjects->getShapeFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setSetAutomaticallyToNonStaticIfGetsParent(!it->getSetAutomaticallyToNonStaticIfGetsParent());
    }
    if (cmd.cmdId == APPLY_RESPONDABLEPARAMS_SHAPEDYNGUITRIGGEREDCMD)
    {
        CShape* last = App::currentWorld->sceneObjects->getShapeFromHandle(cmd.intParams[0]);
        if (last != nullptr)
        {
            for (size_t i = 1; i < cmd.intParams.size(); i++)
            {
                CShape* it = App::currentWorld->sceneObjects->getShapeFromHandle(cmd.intParams[i]);
                if (it != nullptr)
                {
                    it->setRespondable(last->getRespondable());
                    it->setDynMaterial(last->getDynMaterial()->copyYourself());
                    it->setRespondableMask(last->getRespondableMask());
                }
            }
        }
    }
    if (cmd.cmdId == SET_MATERIAL_SHAPEDYNGUITRIGGEREDCMD)
    {
        CEngineProperties prop;
        prop.editObjectProperties(cmd.intParams[0]);
    }
    if (cmd.cmdId == SET_ENGINEPARAMS_JOINTDYNGUITRIGGEREDCMD)
    {
        CEngineProperties prop;
        prop.editObjectProperties(cmd.intParams[0]);
    }
    if (cmd.cmdId == SET_ENGINEPARAMS_DUMMYGUITRIGGEREDCMD)
    {
        CEngineProperties prop;
        prop.editObjectProperties(cmd.intParams[0]);
    }
    if (cmd.cmdId == SET_ENGINEPARAMS_DYNAMICSGUITRIGGEREDCMD)
    {
        CEngineProperties prop;
        prop.editObjectProperties(-1);
    }
    if (cmd.cmdId == DELETE_SCRIPT_SCRIPTGUITRIGGEREDCMD)
    {
        int scriptID = cmd.intParams[0];
        CScriptObject* script = App::currentWorld->sceneObjects->embeddedScriptContainer->getScriptObjectFromHandle(scriptID);
        if (script != nullptr)
        {
            if (GuiApp::mainWindow != nullptr)
                GuiApp::mainWindow->codeEditorContainer->closeFromScriptUid(script->getScriptUid(), nullptr, true);
            App::currentWorld->sceneObjects->embeddedScriptContainer->removeScript(scriptID);
        }
    }
    if (cmd.cmdId == TOGGLE_ENABLED_SCRIPTGUITRIGGEREDCMD)
    {
        CScriptObject* it = App::currentWorld->getScriptObjectFromHandle(cmd.intParams[0]);
        if (it != nullptr)
        {
            if (it->getScriptType() == sim_scripttype_customization)
                it->resetScript();
            it->setScriptIsDisabled(!it->getScriptIsDisabled());
        }
    }
    if (cmd.cmdId == TOGGLE_RESETAFTERSIMERROR_SCRIPTGUITRIGGEREDCMD)
    {
        CScript* it = App::currentWorld->sceneObjects->getScriptFromHandle(cmd.intParams[0]);
        if ((it != nullptr) && (it->scriptObject != nullptr))
        {
            if (it->scriptObject->getScriptType() == sim_scripttype_customization)
                it->resetAfterSimError(!it->getResetAfterSimError());
        }
    }
    if (cmd.cmdId == PARENTPROXY_OFF_SCRIPTGUITRIGGEREDCMD)
    {
        CScriptObject* it = App::currentWorld->getScriptObjectFromHandle(cmd.intParams[0]);
        if (it != nullptr)
        {
            it->setParentIsProxy(false);
#ifdef SIM_WITH_GUI
            if (GuiApp::mainWindow != nullptr)
            {
                unsigned short res = GuiApp::uiThread->messageBox_question(
                    GuiApp::mainWindow, "Code conversion",
                    "CoppeliaSim can try to adjust the code automatically, by mainly performing a simple string replacement:\n\n"
                    "'.' and './' (and similar)    with    '..' and '../'\n"
                    "'conveyor_customization-2'    with    'models.conveyor_customization-3'\n"
                    "'efficientconveyor_customization-2'    with    'models.efficientconveyor_customization-3'\n"
                    "'conveyorSystem_customization-2'    with    'models.conveyorSystem_customization-3'\n"
                    "'path_customization'    with    'models.path_customization-2'\n"
                    "'graph_customization'    with    'models.graph_customization-2'\n\n"
                    "There might be other changes that are possibly required, and that will have to be handled manually. Also, all non-embedded code (i.e. external files) is not touched.\n"
                    "Do you want to proceed?",
                    VMESSAGEBOX_YES_NO, VMESSAGEBOX_REPLY_YES);
                if (res == VMESSAGEBOX_REPLY_YES)
                {
                    GuiApp::mainWindow->codeEditorContainer->closeFromScriptUid(it->getScriptUid(), nullptr, true);
                    it->replaceScriptText("'.'", "'..'");
                    it->replaceScriptText("'./", "'../");
                    it->replaceScriptText("\".\"", "\"..\"");
                    it->replaceScriptText("\"./", "\"../");
                    it->replaceScriptText("'conveyor_customization-2'", "'models.conveyor_customization-3'");
                    it->replaceScriptText("\"conveyor_customization-2\"", "\"models.conveyor_customization-3\"");
                    it->replaceScriptText("'efficientconveyor_customization-2'", "'models.efficientconveyor_customization-3'");
                    it->replaceScriptText("\"efficientconveyor_customization-2\"", "\"models.efficientconveyor_customization-3\"");
                    it->replaceScriptText("'conveyorSystem_customization-2'", "'models.conveyorSystem_customization-3'");
                    it->replaceScriptText("\"conveyorSystem_customization-2\"", "\"models.conveyorSystem_customization-3\"");
                    it->replaceScriptText("'path_customization'", "'models.path_customization-2'");
                    it->replaceScriptText("\"path_customization\"", "\"models.path_customization-2\"");
                    it->replaceScriptText("'graph_customization'", "'models.graph_customization-2'");
                    it->replaceScriptText("\"graph_customization\"", "\"models.graph_customization-2\"");
                }
            }
#endif
        }
    }
    if (cmd.cmdId == TOGGLE_EXECUTEONCE_SCRIPTGUITRIGGEREDCMD)
    {
        int scriptID = cmd.intParams[0];
        CScriptObject* it = App::currentWorld->sceneObjects->embeddedScriptContainer->getScriptObjectFromHandle(scriptID);
    }
    if (cmd.cmdId == SET_EXECORDER_SCRIPTGUITRIGGEREDCMD)
    {
        CSceneObject* it = App::currentWorld->sceneObjects->getObjectFromHandle(cmd.intParams[0]);
        if (it != nullptr)
        {
            if (it->getObjectType() == sim_sceneobject_script)
            {
                CScript* scr = (CScript*)it;
                scr->scriptObject->setScriptExecPriority(cmd.intParams[1]); // new script objects
            }
            else
                it->setScriptExecPriority_raw(cmd.intParams[1]); // old scripts
        }
    }
    if (cmd.cmdId == SET_ALL_SCRIPTSIMULPARAMETERGUITRIGGEREDCMD)
    {
        int objID = cmd.intParams[0];
        CSceneObject* it = App::currentWorld->sceneObjects->getObjectFromHandle(objID);
        if (it != nullptr)
        {
            CUserParameters* sp = it->getUserScriptParameterObject();
            sp->userParamEntries.clear();
            for (size_t i = 0; i < cmd.intParams.size() - 1; i++)
            {
                SUserParamEntry e;
                e.name = cmd.stringParams[3 * i + 0];
                e.unit = cmd.stringParams[3 * i + 1];
                e.value = cmd.stringParams[3 * i + 2];
                e.properties = cmd.intParams[1 + i];
                sp->userParamEntries.push_back(e);
            }
            if (sp->userParamEntries.size() == 0)
                it->setUserScriptParameterObject(nullptr);
        }
    }

    if (cmd.cmdId == TOGGLE_EXPLICITHANDLING_GRAPHGUITRIGGEREDCMD)
    {
        CGraph* it = App::currentWorld->sceneObjects->getGraphFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setExplicitHandling(!it->getExplicitHandling());
    }
    if (cmd.cmdId == TOGGLE_BUFFERCYCLIC_GRAPHGUITRIGGEREDCMD)
    {
        CGraph* it = App::currentWorld->sceneObjects->getGraphFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setCyclic(!it->getCyclic());
    }
    if (cmd.cmdId == TOGGLE_TIMEGRAPHVISIBLE_GRAPHGUITRIGGEREDCMD)
    {
        CGraph* it = App::currentWorld->sceneObjects->getGraphFromHandle(cmd.intParams[0]);
        if (it != nullptr)
        {
            CGraphData_old* grData = it->getGraphData(cmd.intParams[1]);
            if (grData != nullptr)
                grData->setVisible(!grData->getVisible());
        }
    }
    if (cmd.cmdId == TOGGLE_TIMEGRAPHSHOWLABEL_GRAPHGUITRIGGEREDCMD)
    {
        CGraph* it = App::currentWorld->sceneObjects->getGraphFromHandle(cmd.intParams[0]);
        if (it != nullptr)
        {
            CGraphData_old* grData = it->getGraphData(cmd.intParams[1]);
            if (grData != nullptr)
                grData->setLabel(!grData->getLabel());
        }
    }
    if (cmd.cmdId == TOGGLE_TIMEGRAPHLINKPOINTS_GRAPHGUITRIGGEREDCMD)
    {
        CGraph* it = App::currentWorld->sceneObjects->getGraphFromHandle(cmd.intParams[0]);
        if (it != nullptr)
        {
            CGraphData_old* grData = it->getGraphData(cmd.intParams[1]);
            if (grData != nullptr)
                grData->setLinkPoints(!grData->getLinkPoints());
        }
    }
    if (cmd.cmdId == INSERT_DATASTREAM_GRAPHGUITRIGGEREDCMD)
    {
        CGraph* it = App::currentWorld->sceneObjects->getGraphFromHandle(cmd.intParams[0]);
        if (it != nullptr)
        {
            int currentDataType = cmd.intParams[1];
            int index = cmd.intParams[2];
            int objID;
            CGraphingRoutines_old::loopThroughAllAndGetObjectsFromGraphCategory(index, currentDataType, objID);
            CGraphData_old* newGraphDat = new CGraphData_old(currentDataType, objID, -1);
            CGraph* it = App::currentWorld->sceneObjects->getLastSelectionGraph();
            int h = it->addNewGraphData(newGraphDat);
            // Now select the object in the UI. We need to post it so that it arrives after the dialog refresh!:
            SSimulationThreadCommand cmd2;
            cmd2.cmdId = CALL_DIALOG_FUNCTION_GUITRIGGEREDCMD;
            cmd2.intParams.push_back(GRAPH_DLG);
            cmd2.intParams.push_back(0);
            cmd2.intParams.push_back(h);
            App::appendSimulationThreadCommand(cmd2);
        }
    }
    if (cmd.cmdId == REMOVE_DATASTREAM_GRAPHGUITRIGGEREDCMD)
    {
        CGraph* it = App::currentWorld->sceneObjects->getGraphFromHandle(cmd.intParams[0]);
        if ((it != nullptr) && (cmd.intParams[1] != -1))
            it->removeGraphData(cmd.intParams[1]);
    }
    if (cmd.cmdId == RENAME_DATASTREAM_GRAPHGUITRIGGEREDCMD)
    {
        CGraph* it = App::currentWorld->sceneObjects->getGraphFromHandle(cmd.intParams[0]);
        if (it != nullptr)
        {
            std::string newName(cmd.stringParams[0]);
            CGraphData_old* grData = it->getGraphData(cmd.intParams[1]);
            if ((grData != nullptr) && (newName != ""))
            {
                if (grData->getName() != newName)
                {
                    tt::removeIllegalCharacters(newName, false);
                    if (it->getGraphData(newName) == nullptr)
                        grData->setName(newName);
                }
            }
        }
    }
    if (cmd.cmdId == SET_OBJECTSIZE_GRAPHGUITRIGGEREDCMD)
    {
        CGraph* it = App::currentWorld->sceneObjects->getGraphFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setGraphSize(cmd.doubleParams[0]);
    }
    if (cmd.cmdId == SET_BUFFERSIZE_GRAPHGUITRIGGEREDCMD)
    {
        CGraph* it = App::currentWorld->sceneObjects->getGraphFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setBufferSize(cmd.intParams[1]);
    }
    if (cmd.cmdId == REMOVE_ALLSTATICCURVES_GRAPHGUITRIGGEREDCMD)
    {
        CGraph* it = App::currentWorld->sceneObjects->getGraphFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->removeAllStatics();
    }
    if (cmd.cmdId == REMOVE_ALLCURVES_GRAPHGUITRIGGEREDCMD)
    {
        CGraph* it = App::currentWorld->sceneObjects->getGraphFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->removeAllStreamsAndCurves();
    }
    if (cmd.cmdId == SET_VALUERAWSTATE_GRAPHGUITRIGGEREDCMD)
    {
        CGraph* it = App::currentWorld->sceneObjects->getGraphFromHandle(cmd.intParams[0]);
        if (it != nullptr)
        {
            CGraphData_old* grData = it->getGraphData(cmd.intParams[1]);
            if (grData != nullptr)
                grData->setDerivativeIntegralAndCumulative(cmd.intParams[2]);
        }
    }
    if (cmd.cmdId == SET_VALUEMULTIPLIER_GRAPHGUITRIGGEREDCMD)
    {
        CGraph* it = App::currentWorld->sceneObjects->getGraphFromHandle(cmd.intParams[0]);
        if (it != nullptr)
        {
            CGraphData_old* grData = it->getGraphData(cmd.intParams[1]);
            if (grData != nullptr)
                grData->setZoomFactor(cmd.doubleParams[0]);
        }
    }
    if (cmd.cmdId == SET_VALUEOFFSET_GRAPHGUITRIGGEREDCMD)
    {
        CGraph* it = App::currentWorld->sceneObjects->getGraphFromHandle(cmd.intParams[0]);
        if (it != nullptr)
        {
            CGraphData_old* grData = it->getGraphData(cmd.intParams[1]);
            if (grData != nullptr)
                grData->setAddCoeff(cmd.doubleParams[0]);
        }
    }
    if (cmd.cmdId == SET_MOVINGAVERAGEPERIOD_GRAPHGUITRIGGEREDCMD)
    {
        CGraph* it = App::currentWorld->sceneObjects->getGraphFromHandle(cmd.intParams[0]);
        if (it != nullptr)
        {
            CGraphData_old* grData = it->getGraphData(cmd.intParams[1]);
            if (grData != nullptr)
                grData->setMovingAverageCount(cmd.intParams[2]);
        }
    }
    if (cmd.cmdId == DUPLICATE_TOSTATIC_GRAPHGUITRIGGEREDCMD)
    {
        CGraph* it = App::currentWorld->sceneObjects->getGraphFromHandle(cmd.intParams[0]);
        if (it != nullptr)
        {
            CGraphData_old* grData = it->getGraphData(cmd.intParams[1]);
            if ((grData != nullptr) && (grData->getDataLength() != 0))
            {
                it->makeCurveStatic(cmd.intParams[1], 0);
                GuiApp::uiThread->messageBox_information(GuiApp::mainWindow, IDSN_GRAPH_CURVE,
                                                         IDSN_CURVE_WAS_DUPLICATED_TO_STATIC, VMESSAGEBOX_OKELI,
                                                         VMESSAGEBOX_REPLY_OK);
            }
        }
    }

    if (cmd.cmdId == DELETE_CURVE_GRAPHCURVEGUITRIGGEREDCMD)
    {
        CGraph* it = App::currentWorld->sceneObjects->getGraphFromHandle(cmd.intParams[0]);
        if (it != nullptr)
        {
            int objID = cmd.intParams[1];
            if (objID != -1)
            {
                if (cmd.boolParams[0])
                    it->remove2DPartners(objID);
                else
                    it->remove3DPartners(objID);
            }
        }
    }
    if (cmd.cmdId == RENAME_CURVE_GRAPHCURVEGUITRIGGEREDCMD)
    {
        CGraph* it = App::currentWorld->sceneObjects->getGraphFromHandle(cmd.intParams[0]);
        if (it != nullptr)
        {
            int objID = cmd.intParams[1];
            if (objID != -1)
            {
                std::string newName(cmd.stringParams[0]);
                CGraphDataComb_old* grData;
                if (cmd.boolParams[0])
                    grData = it->getGraphData2D(objID);
                else
                    grData = it->getGraphData3D(objID);
                if ((grData != nullptr) && (newName != ""))
                {
                    if (grData->getName() != newName)
                    {
                        tt::removeIllegalCharacters(newName, false);
                        if (cmd.boolParams[0])
                        {
                            if (it->getGraphData2D(newName) == nullptr)
                                grData->setName(newName);
                        }
                        else
                        {
                            if (it->getGraphData3D(newName) == nullptr)
                                grData->setName(newName);
                        }
                    }
                }
            }
        }
    }
    if (cmd.cmdId == TOGGLE_VISIBLE_GRAPHCURVEGUITRIGGEREDCMD)
    {
        CGraph* it = App::currentWorld->sceneObjects->getGraphFromHandle(cmd.intParams[0]);
        if ((it != nullptr) && (cmd.intParams[1] != -1))
        {
            CGraphDataComb_old* grDataComb = nullptr;
            if (cmd.boolParams[0])
                grDataComb = it->getGraphData2D(cmd.intParams[1]);
            else
                grDataComb = it->getGraphData3D(cmd.intParams[1]);
            if (grDataComb != nullptr)
                grDataComb->setVisible(!grDataComb->getVisible());
        }
    }
    if (cmd.cmdId == TOGGLE_LABEL_GRAPHCURVEGUITRIGGEREDCMD)
    {
        CGraph* it = App::currentWorld->sceneObjects->getGraphFromHandle(cmd.intParams[0]);
        if ((it != nullptr) && (cmd.intParams[1] != -1))
        {
            CGraphDataComb_old* grDataComb = nullptr;
            if (cmd.boolParams[0])
                grDataComb = it->getGraphData2D(cmd.intParams[1]);
            else
                grDataComb = it->getGraphData3D(cmd.intParams[1]);
            if (grDataComb != nullptr)
                grDataComb->setLabel(!grDataComb->getLabel());
        }
    }
    if (cmd.cmdId == TOGGLE_LINKPTS_GRAPHCURVEGUITRIGGEREDCMD)
    {
        CGraph* it = App::currentWorld->sceneObjects->getGraphFromHandle(cmd.intParams[0]);
        if ((it != nullptr) && (cmd.intParams[1] != -1))
        {
            CGraphDataComb_old* grDataComb = nullptr;
            if (cmd.boolParams[0])
                grDataComb = it->getGraphData2D(cmd.intParams[1]);
            else
                grDataComb = it->getGraphData3D(cmd.intParams[1]);
            if (grDataComb != nullptr)
                grDataComb->setLinkPoints(!grDataComb->getLinkPoints());
        }
    }
    if (cmd.cmdId == TOGGLE_ONTOP_GRAPHCURVEGUITRIGGEREDCMD)
    {
        CGraph* it = App::currentWorld->sceneObjects->getGraphFromHandle(cmd.intParams[0]);
        if ((it != nullptr) && (cmd.intParams[1] != -1))
        {
            CGraphDataComb_old* grDataComb = nullptr;
            if (cmd.boolParams[0])
                grDataComb = it->getGraphData2D(cmd.intParams[1]);
            else
                grDataComb = it->getGraphData3D(cmd.intParams[1]);
            if (grDataComb != nullptr)
                grDataComb->setVisibleOnTopOfEverything(!grDataComb->getVisibleOnTopOfEverything());
        }
    }
    if (cmd.cmdId == SET_RELATIVETO_GRAPHCURVEGUITRIGGEREDCMD)
    {
        CGraph* it = App::currentWorld->sceneObjects->getGraphFromHandle(cmd.intParams[0]);
        if ((it != nullptr) && (cmd.intParams[1] != -1))
        {
            CGraphDataComb_old* grDataComb = it->getGraphData3D(cmd.intParams[1]);
            if (grDataComb != nullptr)
                grDataComb->setCurveRelativeToWorld(cmd.boolParams[0]);
        }
    }
    if (cmd.cmdId == SET_CURVEWIDTH_GRAPHCURVEGUITRIGGEREDCMD)
    {
        CGraph* it = App::currentWorld->sceneObjects->getGraphFromHandle(cmd.intParams[0]);
        if ((it != nullptr) && (cmd.intParams[1] != -1))
        {
            CGraphDataComb_old* grDataComb = it->getGraphData3D(cmd.intParams[1]);
            if (grDataComb != nullptr)
                grDataComb->set3DCurveWidth(double(cmd.intParams[2]));
        }
    }
    if (cmd.cmdId == DUPLICATE_TOSTATIC_GRAPHCURVEGUITRIGGEREDCMD)
    {
        CGraph* it = App::currentWorld->sceneObjects->getGraphFromHandle(cmd.intParams[0]);
        if ((it != nullptr) && (cmd.intParams[1] != -1))
        {
            CGraphDataComb_old* grDataComb = nullptr;
            int dim = 1;
            if (cmd.boolParams[0])
                grDataComb = it->getGraphData2D(cmd.intParams[1]);
            else
            {
                dim = 2;
                grDataComb = it->getGraphData3D(cmd.intParams[1]);
            }
            if (grDataComb != nullptr)
            {
                it->makeCurveStatic(cmd.intParams[1], dim);
                GuiApp::uiThread->messageBox_information(GuiApp::mainWindow, IDSN_GRAPH_CURVE,
                                                         IDSN_CURVE_WAS_DUPLICATED_TO_STATIC, VMESSAGEBOX_OKELI,
                                                         VMESSAGEBOX_REPLY_OK);
            }
        }
    }
    if (cmd.cmdId == ADD_NEWCURVE_GRAPHCURVEGUITRIGGEREDCMD)
    {
        CGraph* it = App::currentWorld->sceneObjects->getGraphFromHandle(cmd.intParams[0]);
        if (it != nullptr)
        {
            CGraphDataComb_old* theNew = new CGraphDataComb_old();
            theNew->data[0] = cmd.intParams[1];
            theNew->data[1] = cmd.intParams[2];
            if (!cmd.boolParams[0])
            {
                theNew->data[2] = cmd.intParams[3];
                it->add3DPartners(theNew);
            }
            else
                it->add2DPartners(theNew);
            // Now select the object in the UI. We need to post it so that it arrives after the dialog refresh!:
            SSimulationThreadCommand cmd2;
            cmd2.cmdId = CALL_DIALOG_FUNCTION_GUITRIGGEREDCMD;
            cmd2.intParams.push_back(GRAPH2DAND3DCURVES_DLG);
            cmd2.intParams.push_back(0);
            cmd2.intParams.push_back(theNew->getIdentifier());
            App::appendSimulationThreadCommand(cmd2);
        }
    }

    if (cmd.cmdId == SET_POSRELATIVETO_OBJECTMANIPGUITRIGGEREDCMD)
    {
        CSceneObject* it = App::currentWorld->sceneObjects->getObjectFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setObjectMovementRelativity(0, cmd.intParams[1]);
    }
    if (cmd.cmdId == SET_PERMISSIONS_OBJECTMANIPGUITRIGGEREDCMD)
    {
        CSceneObject* it = App::currentWorld->sceneObjects->getObjectFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setObjectMovementPreferredAxes(cmd.intParams[1]);
    }
    if (cmd.cmdId == SET_POSSTEPSIZE_OBJECTMANIPGUITRIGGEREDCMD)
    {
        CSceneObject* it = App::currentWorld->sceneObjects->getObjectFromHandle(cmd.intParams[0]);
        if (it != nullptr)
        {
            int a = it->getObjectMovementOptions();
            if (cmd.doubleParams[0] < 0.0)
            {
                if (App::currentWorld->simulation->isSimulationStopped())
                    a = a | 1;
                else
                    a = a | 2;
            }
            else
            {
                if (App::currentWorld->simulation->isSimulationStopped())
                    a = (a | 1) - 1;
                else
                    a = (a | 2) - 2;
                it->setObjectMovementStepSize(0, cmd.doubleParams[0]);
            }
            it->setObjectMovementOptions(a);
        }
    }
    if (cmd.cmdId == SET_ORSTEPSIZE_OBJECTMANIPGUITRIGGEREDCMD)
    {
        CSceneObject* it = App::currentWorld->sceneObjects->getObjectFromHandle(cmd.intParams[0]);
        if (it != nullptr)
        {
            int a = it->getObjectMovementOptions();
            if (cmd.doubleParams[0] < 0.0)
            {
                if (App::currentWorld->simulation->isSimulationStopped())
                    a = a | 4;
                else
                    a = a | 8;
            }
            else
            {
                if (App::currentWorld->simulation->isSimulationStopped())
                    a = (a | 4) - 4;
                else
                    a = (a | 8) - 8;
                it->setObjectMovementStepSize(1, cmd.doubleParams[0]);
            }
            it->setObjectMovementOptions(a);
        }
    }
    if (cmd.cmdId == SET_ORRELATIVETO_OBJECTMANIPGUITRIGGEREDCMD)
    {
        CSceneObject* it = App::currentWorld->sceneObjects->getObjectFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setObjectMovementRelativity(1, cmd.intParams[1]);
    }

    if (cmd.cmdId == SET_TRANSF_POSITIONTRANSLATIONGUITRIGGEREDCMD)
    {
        CSceneObject* it = App::currentWorld->sceneObjects->getObjectFromHandle(cmd.intParams[0]);
        if (it != nullptr)
        {
            if (cmd.intParams[1] == 0)
                it->setLocalTransformation(it->getFullParentCumulativeTransformation().getInverse() *
                                           cmd.transfParams[0]);
            else
                it->setLocalTransformation(cmd.transfParams[0]);
            if (!App::currentWorld->simulation->isSimulationStopped())
                CALL_C_API_CLEAR_ERRORS(simResetDynamicObject, it->getObjectHandle() | sim_handleflag_model); // so that we can also manipulate dynamic objects
        }
    }
    if (cmd.cmdId == APPLY_POS_POSITIONTRANSLATIONGUITRIGGEREDCMD)
    {
        CSceneObject* last = App::currentWorld->sceneObjects->getObjectFromHandle(cmd.intParams[0]);
        if (last != nullptr)
        {
            int coordMode = cmd.intParams[cmd.intParams.size() - 2];
            int mask = cmd.intParams[cmd.intParams.size() - 1];
            C7Vector tr;
            if (coordMode == 0)
                tr = last->getCumulativeTransformation();
            else
                tr = last->getLocalTransformation();
            for (size_t i = 1; i < cmd.intParams.size() - 2; i++)
            {
                CSceneObject* it = App::currentWorld->sceneObjects->getObjectFromHandle(cmd.intParams[i]);
                C7Vector trIt;
                if (coordMode == 0)
                    trIt = it->getCumulativeTransformation();
                else
                    trIt = it->getLocalTransformation();
                if (mask & 1)
                    trIt.X(0) = tr.X(0);
                if (mask & 2)
                    trIt.X(1) = tr.X(1);
                if (mask & 4)
                    trIt.X(2) = tr.X(2);
                if (coordMode == 0)
                    it->setLocalTransformation(it->getFullParentCumulativeTransformation().getInverse() * trIt);
                else
                    it->setLocalTransformation(trIt);
                if (!App::currentWorld->simulation->isSimulationStopped())
                    CALL_C_API_CLEAR_ERRORS(simResetDynamicObject, it->getObjectHandle() | sim_handleflag_model); // so that we can also manipulate dynamic objects
            }
        }
    }
    if (cmd.cmdId == TRANSLATESCALE_SELECTION_POSITIONTRANSLATIONGUITRIGGEREDCMD)
    {
        int transfMode = cmd.intParams[cmd.intParams.size() - 2];
        int t = cmd.intParams[cmd.intParams.size() - 1];
        double scalingValues[3];
        scalingValues[0] = cmd.doubleParams[0];
        scalingValues[1] = cmd.doubleParams[1];
        scalingValues[2] = cmd.doubleParams[2];
        double translationValues[3];
        translationValues[0] = cmd.doubleParams[3];
        translationValues[1] = cmd.doubleParams[4];
        translationValues[2] = cmd.doubleParams[5];
        // Prepare the object that will be translated/scaled, and all other objects in selection appropriately:
        // There is one master object that acts as the translation/scaling pivot. That object needs to be carefully
        // selected
        std::vector<CSceneObject*> allSelObj;
        for (size_t i = 0; i < cmd.intParams.size() - 2; i++)
        {
            CSceneObject* it = App::currentWorld->sceneObjects->getObjectFromHandle(cmd.intParams[i]);
            allSelObj.push_back(it);
        }
        std::vector<CSceneObject*> allSelObjects;
        std::map<CSceneObject*, bool> occ;
        CSceneObject* masterObj = nullptr;
        for (int i = int(allSelObj.size()) - 1; i >= 0; i--)
        {
            CSceneObject* it = allSelObj[i]->getLastParentInSelection(&allSelObj);
            if (it == nullptr)
                it = allSelObj[i];
            std::map<CSceneObject*, bool>::iterator it2 = occ.find(it);
            if (it2 == occ.end())
            {
                occ[it] = true;
                if (masterObj == nullptr)
                    masterObj = it;
                else
                    allSelObjects.push_back(it);
            }
        }
        if (masterObj != nullptr)
        {
            C7Vector oldTr(masterObj->getCumulativeTransformation());
            // Translate/Scale the master's position:
            C7Vector tr;
            if (transfMode == 0)
                tr = masterObj->getCumulativeTransformation();
            else
                tr = masterObj->getLocalTransformation();
            if (t == 2)
            {
                tr.X(0) = tr.X(0) * scalingValues[0];
                tr.X(1) = tr.X(1) * scalingValues[1];
                tr.X(2) = tr.X(2) * scalingValues[2];
            }
            else
            {
                C7Vector m;
                m.setIdentity();
                if (t == 1)
                    m.X.setData(translationValues);
                if (transfMode == 2)
                    tr = tr * m;
                else
                    tr = m * tr;
            }
            if (transfMode == 0)
                tr = masterObj->getFullParentCumulativeTransformation().getInverse() * tr;
            masterObj->setLocalTransformation(tr);
            if (!App::currentWorld->simulation->isSimulationStopped())
                CALL_C_API_CLEAR_ERRORS(simResetDynamicObject, masterObj->getObjectHandle() | sim_handleflag_model); // so that we can also manipulate dynamic objects

            // Now move the "slaves" appropriately:
            C7Vector newTr(masterObj->getCumulativeTransformation());
            C7Vector shift(newTr * oldTr.getInverse());
            for (size_t i = 0; i < allSelObjects.size(); i++)
            {
                CSceneObject* obj = allSelObjects[i];
                C7Vector oldLTr = obj->getLocalTransformation();
                C7Vector parentTr = obj->getFullParentCumulativeTransformation();
                obj->setLocalTransformation(parentTr.getInverse() * shift * parentTr * oldLTr);
                if (!App::currentWorld->simulation->isSimulationStopped())
                    CALL_C_API_CLEAR_ERRORS(simResetDynamicObject, obj->getObjectHandle() | sim_handleflag_model); // so that we can also manipulate dynamic objects
            }
        }
    }

    if (cmd.cmdId == APPLY_OR_ORIENTATIONROTATIONGUITRIGGEREDCMD)
    {
        CSceneObject* last = App::currentWorld->sceneObjects->getObjectFromHandle(cmd.intParams[0]);
        if (last != nullptr)
        {
            int coordMode = cmd.intParams[cmd.intParams.size() - 1];
            C7Vector tr;
            if (coordMode == 0)
                tr = last->getCumulativeTransformation();
            else
                tr = last->getLocalTransformation();
            for (size_t i = 1; i < cmd.intParams.size() - 1; i++)
            {
                CSceneObject* it = App::currentWorld->sceneObjects->getObjectFromHandle(cmd.intParams[i]);
                C7Vector trIt;
                if (coordMode == 0)
                    trIt = it->getCumulativeTransformation();
                else
                    trIt = it->getLocalTransformation();
                trIt.Q = tr.Q;
                if (coordMode == 0)
                    it->setLocalTransformation(it->getFullParentCumulativeTransformation().getInverse() * trIt);
                else
                    it->setLocalTransformation(trIt);
                if (!App::currentWorld->simulation->isSimulationStopped())
                    CALL_C_API_CLEAR_ERRORS(simResetDynamicObject, it->getObjectHandle() | sim_handleflag_model); // so that we can also manipulate dynamic objects
            }
        }
    }
    if (cmd.cmdId == ROTATE_SELECTION_ORIENTATIONROTATIONGUITRIGGEREDCMD)
    {
        int transfMode = cmd.intParams[cmd.intParams.size() - 1];
        double rotAngles[3];
        rotAngles[0] = cmd.doubleParams[0];
        rotAngles[1] = cmd.doubleParams[1];
        rotAngles[2] = cmd.doubleParams[2];
        // Prepare the object that will be rotated, and all other objects in selection appropriately:
        // There is one master object that acts as the rotation pivot. That object needs to be carefully selected
        std::vector<CSceneObject*> allSelObj;
        for (size_t i = 0; i < cmd.intParams.size() - 1; i++)
        {
            CSceneObject* it = App::currentWorld->sceneObjects->getObjectFromHandle(cmd.intParams[i]);
            allSelObj.push_back(it);
        }
        std::vector<CSceneObject*> allSelObjects;
        std::map<CSceneObject*, bool> occ;
        CSceneObject* masterObj = nullptr;
        for (int i = int(allSelObj.size()) - 1; i >= 0; i--)
        {
            CSceneObject* it = allSelObj[i]->getLastParentInSelection(&allSelObj);
            if (it == nullptr)
                it = allSelObj[i];
            std::map<CSceneObject*, bool>::iterator it2 = occ.find(it);
            if (it2 == occ.end())
            {
                occ[it] = true;
                if (masterObj == nullptr)
                    masterObj = it;
                else
                    allSelObjects.push_back(it);
            }
        }
        if (masterObj != nullptr)
        {
            C7Vector oldTr(masterObj->getCumulativeTransformation());
            // Rotate the master:
            C7Vector tr;
            if (transfMode == 0)
                tr = masterObj->getCumulativeTransformation();
            else
                tr = masterObj->getLocalTransformation();
            C7Vector m;
            m.setIdentity();
            m.Q.setEulerAngles(rotAngles[0], rotAngles[1], rotAngles[2]);
            if (transfMode == 2)
                tr = tr * m;
            else
                tr = m * tr;
            if (transfMode == 0)
                tr = masterObj->getFullParentCumulativeTransformation().getInverse() * tr;
            masterObj->setLocalTransformation(tr);
            if (!App::currentWorld->simulation->isSimulationStopped())
                CALL_C_API_CLEAR_ERRORS(simResetDynamicObject, masterObj->getObjectHandle() | sim_handleflag_model); // so that we can also manipulate dynamic objects

            // Now rotate the "slaves":
            C7Vector newTr(masterObj->getCumulativeTransformation());
            C7Vector shift(newTr * oldTr.getInverse());
            for (size_t i = 0; i < allSelObjects.size(); i++)
            {
                CSceneObject* obj = allSelObjects[i];
                C7Vector oldLTr = obj->getLocalTransformation();
                C7Vector parentTr = obj->getFullParentCumulativeTransformation();
                obj->setLocalTransformation(parentTr.getInverse() * shift * parentTr * oldLTr);
                if (!App::currentWorld->simulation->isSimulationStopped())
                    CALL_C_API_CLEAR_ERRORS(simResetDynamicObject, obj->getObjectHandle() | sim_handleflag_model); // so that we can also manipulate dynamic objects
            }
        }
    }

    if (cmd.cmdId == REMOVE_ELEMENT_IKELEMENTGUITRIGGEREDCMD)
    {
        CIkGroup_old* ikGroup = App::currentWorld->ikGroups_old->getObjectFromHandle(cmd.intParams[0]);
        if (ikGroup != nullptr)
        {
            CIkElement_old* it = ikGroup->getIkElementFromHandle(cmd.intParams[1]);
            if (it != nullptr)
                ikGroup->removeIkElement(cmd.intParams[1]);
        }
    }
    if (cmd.cmdId == ADD_ELEMENT_IKELEMENTGUITRIGGEREDCMD)
    {
        CIkGroup_old* ikGroup = App::currentWorld->ikGroups_old->getObjectFromHandle(cmd.intParams[0]);
        if (ikGroup != nullptr)
        {
            CDummy* it = App::currentWorld->sceneObjects->getDummyFromHandle(cmd.intParams[1]);
            if (it != nullptr)
            {
                CIkElement_old* newIkEl = new CIkElement_old(it->getObjectHandle());
                if (!ikGroup->addIkElement(newIkEl))
                    delete newIkEl;
                else
                {
                    // Now select the object in the UI. We need to post it so that it arrives after the dialog refresh!:
                    SSimulationThreadCommand cmd2;
                    cmd2.cmdId = CALL_DIALOG_FUNCTION_GUITRIGGEREDCMD;
                    cmd2.intParams.push_back(IKELEMENT_DLG);
                    cmd2.intParams.push_back(0);
                    cmd2.intParams.push_back(newIkEl->getObjectHandle());
                    App::appendSimulationThreadCommand(cmd2);
                }
            }
        }
    }
    if (cmd.cmdId == TOGGLE_ACTIVE_IKELEMENTGUITRIGGEREDCMD)
    {
        CIkGroup_old* ikGroup = App::currentWorld->ikGroups_old->getObjectFromHandle(cmd.intParams[0]);
        if (ikGroup != nullptr)
        {
            CIkElement_old* it = ikGroup->getIkElementFromHandle(cmd.intParams[1]);
            if (it != nullptr)
                it->setEnabled(!it->getEnabled());
        }
    }
    if (cmd.cmdId == SET_BASE_IKELEMENTGUITRIGGEREDCMD)
    {
        CIkGroup_old* ikGroup = App::currentWorld->ikGroups_old->getObjectFromHandle(cmd.intParams[0]);
        if (ikGroup != nullptr)
        {
            CIkElement_old* it = ikGroup->getIkElementFromHandle(cmd.intParams[1]);
            if (it != nullptr)
                it->setBase(cmd.intParams[2]);
        }
    }
    if (cmd.cmdId == TOGGLE_CONSTRAINT_IKELEMENTGUITRIGGEREDCMD)
    {
        CIkGroup_old* ikGroup = App::currentWorld->ikGroups_old->getObjectFromHandle(cmd.intParams[0]);
        if (ikGroup != nullptr)
        {
            CIkElement_old* it = ikGroup->getIkElementFromHandle(cmd.intParams[1]);
            if (it != nullptr)
            {
                int c = cmd.intParams[2];
                //                    if
                //                    ((c==sim_ik_x_constraint)||(c==sim_ik_y_constraint)||(c==sim_ik_z_constraint)||(c==sim_ik_gamma_constraint))
                it->setConstraints(it->getConstraints() ^ c);
                //                    if (c==sim_ik_alpha_beta_constraint)
                //                    {
                //                        it->setConstraints(it->getConstraints()^sim_ik_alpha_beta_constraint);
                //                        if
                //                        ((it->getConstraints()&(sim_ik_alpha_beta_constraint|sim_ik_gamma_constraint))==sim_ik_gamma_constraint)
                //                            it->setConstraints(it->getConstraints()^sim_ik_gamma_constraint); // gamma
                //                            constraint cannot be selected if alpha-beta constraint is not selected!
                //                    }
            }
        }
    }
    if (cmd.cmdId == SET_REFERENCEFRAME_IKELEMENTGUITRIGGEREDCMD)
    {
        CIkGroup_old* ikGroup = App::currentWorld->ikGroups_old->getObjectFromHandle(cmd.intParams[0]);
        if (ikGroup != nullptr)
        {
            CIkElement_old* it = ikGroup->getIkElementFromHandle(cmd.intParams[1]);
            if (it != nullptr)
                it->setAlternativeBaseForConstraints(cmd.intParams[2]);
        }
    }
    if (cmd.cmdId == SET_PRECISION_IKELEMENTGUITRIGGEREDCMD)
    {
        CIkGroup_old* ikGroup = App::currentWorld->ikGroups_old->getObjectFromHandle(cmd.intParams[0]);
        if (ikGroup != nullptr)
        {
            CIkElement_old* it = ikGroup->getIkElementFromHandle(cmd.intParams[1]);
            if (it != nullptr)
            {
                if (cmd.intParams[2] == 0)
                    it->setMinLinearPrecision(cmd.doubleParams[0]);
                else
                    it->setMinAngularPrecision(cmd.doubleParams[0]);
            }
        }
    }
    if (cmd.cmdId == SET_WEIGHT_IKELEMENTGUITRIGGEREDCMD)
    {
        CIkGroup_old* ikGroup = App::currentWorld->ikGroups_old->getObjectFromHandle(cmd.intParams[0]);
        if (ikGroup != nullptr)
        {
            CIkElement_old* it = ikGroup->getIkElementFromHandle(cmd.intParams[1]);
            if (it != nullptr)
            {
                if (cmd.intParams[2] == 0)
                    it->setPositionWeight(cmd.doubleParams[0]);
                else
                    it->setOrientationWeight(cmd.doubleParams[0]);
            }
        }
    }

    if (cmd.cmdId == TOGGLE_ALLENABLED_IKGROUPGUITRIGGEREDCMD)
    {
        App::currentWorld->mainSettings_old->ikCalculationEnabled = !App::currentWorld->mainSettings_old->ikCalculationEnabled;
    }
    if (cmd.cmdId == REMOVE_IKGROUP_IKGROUPGUITRIGGEREDCMD)
    {
        CIkGroup_old* it = App::currentWorld->ikGroups_old->getObjectFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            App::currentWorld->ikGroups_old->removeIkGroup(it->getObjectHandle());
    }
    if (cmd.cmdId == ADD_IKGROUP_IKGROUPGUITRIGGEREDCMD)
    {
        CIkGroup_old* newGroup = new CIkGroup_old();
        newGroup->setObjectName("IK_Group", false);
        App::currentWorld->ikGroups_old->addIkGroup(newGroup, false);
        // Now select the object in the UI. We need to post it so that it arrives after the dialog refresh!:
        SSimulationThreadCommand cmd2;
        cmd2.cmdId = CALL_DIALOG_FUNCTION_GUITRIGGEREDCMD;
        cmd2.intParams.push_back(IK_DLG);
        cmd2.intParams.push_back(0);
        cmd2.intParams.push_back(newGroup->getObjectHandle());
        App::appendSimulationThreadCommand(cmd2);
        // Following second refresh is needed so that the up/down buttons become enabled:
        App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
    }
    if (cmd.cmdId == RENAME_IKGROUP_IKGROUPGUITRIGGEREDCMD)
    {
        CIkGroup_old* it = App::currentWorld->ikGroups_old->getObjectFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setObjectName(cmd.stringParams[0].c_str(), true);
    }
    if (cmd.cmdId == SHIFT_IKGROUP_IKGROUPGUITRIGGEREDCMD)
    {
        CIkGroup_old* it = App::currentWorld->ikGroups_old->getObjectFromHandle(cmd.intParams[0]);
        bool up = cmd.intParams[1] != 0;
        if (it != nullptr)
        {
            App::currentWorld->ikGroups_old->shiftIkGroup(cmd.intParams[0], up);
            SSimulationThreadCommand cmd2;
            cmd2.cmdId = CALL_DIALOG_FUNCTION_GUITRIGGEREDCMD;
            cmd2.intParams.push_back(IK_DLG);
            cmd2.intParams.push_back(0);
            cmd2.intParams.push_back(it->getObjectHandle());
            App::appendSimulationThreadCommand(cmd2);
        }
    }
    if (cmd.cmdId == TOGGLE_EXPLICITHANDLING_IKGROUPGUITRIGGEREDCMD)
    {
        CIkGroup_old* it = App::currentWorld->ikGroups_old->getObjectFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setExplicitHandling(!it->getExplicitHandling());
    }
    if (cmd.cmdId == TOGGLE_ACTIVE_IKGROUPGUITRIGGEREDCMD)
    {
        CIkGroup_old* it = App::currentWorld->ikGroups_old->getObjectFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setEnabled(!it->getEnabled());
    }
    if (cmd.cmdId == TOGGLE_IGNOREMAXSTEPSIZES_IKGROUPGUITRIGGEREDCMD)
    {
        CIkGroup_old* it = App::currentWorld->ikGroups_old->getObjectFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setIgnoreMaxStepSizes(!it->getIgnoreMaxStepSizes());
    }
    if (cmd.cmdId == SET_CALCMETHOD_IKGROUPGUITRIGGEREDCMD)
    {
        CIkGroup_old* it = App::currentWorld->ikGroups_old->getObjectFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setCalculationMethod(cmd.intParams[1]);
    }
    if (cmd.cmdId == SET_DAMPING_IKGROUPGUITRIGGEREDCMD)
    {
        CIkGroup_old* it = App::currentWorld->ikGroups_old->getObjectFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setDampingFactor(cmd.doubleParams[0]);
    }
    if (cmd.cmdId == SET_ITERATIONS_IKGROUPGUITRIGGEREDCMD)
    {
        CIkGroup_old* it = App::currentWorld->ikGroups_old->getObjectFromHandle(cmd.intParams[0]);
        if (it != nullptr)
            it->setMaxIterations(cmd.intParams[1]);
    }
    if (cmd.cmdId == SET_CONDITIONALPARAMS_IKGROUPGUITRIGGEREDCMD)
    {
        CIkGroup_old* it = App::currentWorld->ikGroups_old->getObjectFromHandle(cmd.intParams[0]);
        if (it != nullptr)
        {
            CIkGroup_old* it2 = App::currentWorld->ikGroups_old->getObjectFromHandle(cmd.intParams[1]);
            int id = -1;
            if (it2 != nullptr)
                id = it2->getObjectHandle();
            it->setDoOnFailOrSuccessOf(id, true);
            it->setDoOnPerformed(cmd.intParams[2] < 2);
            it->setDoOnFail(cmd.intParams[2] == 0);
            it->setRestoreIfPositionNotReached(cmd.boolParams[0]);
            it->setRestoreIfOrientationNotReached(cmd.boolParams[1]);
        }
    }

    if (cmd.cmdId == SAVE_USERSETTINGSGUITRIGGEREDCMD)
        App::userSettings->saveUserSettings();
    if (cmd.cmdId == SET_TRANSLATIONSTEPSIZE_USERSETTINGSGUITRIGGEREDCMD)
    {
        App::userSettings->setTranslationStepSize(cmd.doubleParams[0]);
        App::userSettings->saveUserSettings();
    }
    if (cmd.cmdId == SET_ROTATIONSTEPSIZE_USERSETTINGSGUITRIGGEREDCMD)
    {
        App::userSettings->setRotationStepSize(cmd.doubleParams[0]);
        App::userSettings->saveUserSettings();
    }
    if (cmd.cmdId == TOGGLE_HIDEHIERARCHY_USERSETTINGSGUITRIGGEREDCMD)
    {
        App::userSettings->sceneHierarchyHiddenDuringSimulation =
            !App::userSettings->sceneHierarchyHiddenDuringSimulation;
        App::userSettings->saveUserSettings();
    }
    if (cmd.cmdId == TOGGLE_SHOWWORLDREF_USERSETTINGSGUITRIGGEREDCMD)
    {
        App::userSettings->displayWorldReference = !App::userSettings->displayWorldReference;
        App::userSettings->saveUserSettings();
    }
    if (cmd.cmdId == TOGGLE_UNDOREDO_USERSETTINGSGUITRIGGEREDCMD)
    {
        App::userSettings->setUndoRedoEnabled(!App::userSettings->getUndoRedoEnabled());
        App::userSettings->saveUserSettings();
    }
    if (cmd.cmdId == TOGGLE_HIDECONSOLE_USERSETTINGSGUITRIGGEREDCMD)
    {
        App::userSettings->alwaysShowConsole = !App::userSettings->alwaysShowConsole;
        GuiApp::setShowConsole(App::userSettings->alwaysShowConsole);
        App::userSettings->saveUserSettings();
    }
    if (cmd.cmdId == TOGGLE_AUTOSAVE_USERSETTINGSGUITRIGGEREDCMD)
    {
        if (App::userSettings->autoSaveDelay != 0)
            App::userSettings->autoSaveDelay = 0;
        else
            App::userSettings->autoSaveDelay = 2; // 2 minutes
        App::userSettings->saveUserSettings();
    }
    if (cmd.cmdId == SET_OPENGLSETTINGS_USERSETTINGSGUITRIGGEREDCMD)
    {
        App::userSettings->offscreenContextType = cmd.intParams[0];
        App::userSettings->fboType = cmd.intParams[1];
        App::userSettings->vboOperation = cmd.intParams[2];
        // cmd.intParams[3] not used
        App::userSettings->oglCompatibilityTweak1 = cmd.boolParams[0];
        App::userSettings->useGlFinish = cmd.boolParams[1];
        App::userSettings->useGlFinish_visionSensors = cmd.boolParams[2];
        App::userSettings->setIdleFps(cmd.intParams[4]);
        App::userSettings->forceFboViaExt = cmd.boolParams[3];
        App::userSettings->saveUserSettings();
    }

    if (cmd.cmdId == PATHEDIT_MAKEDUMMY_GUITRIGGEREDCMD)
    {
        CDummy* newDummy = new CDummy();
        newDummy->setObjectAlias_direct(cmd.stringParams[0].c_str());
        newDummy->setObjectName_direct_old(cmd.stringParams[0].c_str());
        newDummy->setObjectAltName_direct_old(
            tt::getObjectAltNameFromObjectName(newDummy->getObjectName_old().c_str()).c_str());
        newDummy->setDummySize(cmd.doubleParams[0]);
        App::currentWorld->sceneObjects->addObjectToScene(newDummy, false, true);
        newDummy->setLocalTransformation(cmd.transfParams[0]);
    }
    if (cmd.cmdId == SHAPEEDIT_MAKESHAPE_GUITRIGGEREDCMD)
    {
        App::logMsg(sim_verbosity_msgs, IDSNS_GENERATING_SHAPE);
        int toid = cmd.intParams[0];
        CShape* newShape;
        if (toid != -1)
            newShape = new CShape(C7Vector::identityTransformation, cmd.doubleVectorParams[0], cmd.intVectorParams[0],
                                  nullptr, &cmd.floatVectorParams[0], 0);
        else
            newShape = new CShape(C7Vector::identityTransformation, cmd.doubleVectorParams[0], cmd.intVectorParams[0],
                                  nullptr, nullptr, 0);
        newShape->setVisibleEdges(false);
        newShape->getSingleMesh()->setShadingAngle(0.0);
        newShape->getSingleMesh()->setEdgeThresholdAngle(0.0);
        newShape->setObjectAlias_direct("Extracted_shape");
        newShape->setObjectName_direct_old("Extracted_shape");
        newShape->setObjectAltName_direct_old(
            tt::getObjectAltNameFromObjectName(newShape->getObjectName_old().c_str()).c_str());
        App::currentWorld->sceneObjects->addObjectToScene(newShape, false, true);
        if (toid != -1)
        {
            CTextureObject* to = App::currentWorld->textureContainer->getObject(toid);
            if ((to != nullptr) && (newShape->getSingleMesh()->getTextureProperty() != nullptr))
            {
                to->addDependentObject(newShape->getObjectHandle(), newShape->getSingleMesh()->getUniqueID());
                newShape->getSingleMesh()->getTextureProperty()->setTextureObjectID(toid);
            }
        }
        App::logMsg(sim_verbosity_msgs, "done.");
        GuiApp::setFullDialogRefreshFlag();
    }
    if (cmd.cmdId == SHAPEEDIT_MAKEPRIMITIVE_GUITRIGGEREDCMD)
    {
        CShape* newShape = new CShape(C7Vector::identityTransformation, cmd.doubleVectorParams[0],
                                      cmd.intVectorParams[0], nullptr, nullptr, 0);
        newShape->alignBB("mesh");
        C3Vector size;
        C7Vector conf(newShape->getLocalTransformation() * newShape->getBB(&size));
        size *= 2.0;
        delete newShape;
        CShape* shape = nullptr;

        if (cmd.intParams[0] == 0)
        { // Cuboid
            App::logMsg(sim_verbosity_msgs, "Generating cuboid...");
            shape = CAddOperations::addPrimitive_withDialog(ADD_COMMANDS_ADD_PRIMITIVE_RECTANGLE_ACCMD, &size);
            if (shape != nullptr)
                shape->setLocalTransformation(conf);
        }

        if (cmd.intParams[0] == 1)
        { // sphere
            App::logMsg(sim_verbosity_msgs, "Generating sphere...");
            double mm = std::max<double>(std::max<double>(size(0), size(1)), size(2));
            size(0) = mm;
            size(1) = mm;
            size(2) = mm;
            shape = CAddOperations::addPrimitive_withDialog(ADD_COMMANDS_ADD_PRIMITIVE_SPHERE_ACCMD, &size);
            if (shape != nullptr)
                shape->setLocalTransformation(conf);
        }

        if (cmd.intParams[0] == 2)
        { // spheroid
            App::logMsg(sim_verbosity_msgs, "Generating spheroid...");
            shape = CAddOperations::addPrimitive_withDialog(ADD_COMMANDS_ADD_PRIMITIVE_SPHERE_ACCMD, &size);
            if (shape != nullptr)
                shape->setLocalTransformation(conf);
        }

        if (cmd.intParams[0] == 3)
        { // cylinder
            App::logMsg(sim_verbosity_msgs, "Generating cylinder...");
            C3Vector diff(fabs(size(0) - size(1)), fabs(size(0) - size(2)), fabs(size(1) - size(2)));
            int t = 2;
            if (std::min<double>(std::min<double>(diff(0), diff(1)), diff(2)) == diff(0))
                t = 0;
            if (std::min<double>(std::min<double>(diff(0), diff(1)), diff(2)) == diff(1))
                t = 1;
            if (t == 0)
            {
                C3Vector s(size);
                size(0) = (s(0) + s(1)) * 0.5;
                size(1) = (s(0) + s(1)) * 0.5;
                size(2) = s(2);
            }
            if (t == 1)
            {
                C3Vector s(size);
                size(0) = (s(0) + s(2)) * 0.5;
                size(1) = (s(0) + s(2)) * 0.5;
                size(2) = s(1);
            }
            if (t == 2)
            {
                C3Vector s(size);
                size(0) = (s(2) + s(1)) * 0.5;
                size(1) = (s(2) + s(1)) * 0.5;
                size(2) = s(0);
            }
            shape = CAddOperations::addPrimitive_withDialog(ADD_COMMANDS_ADD_PRIMITIVE_CYLINDER_ACCMD, &size);
            if (shape != nullptr)
            {
                C7Vector r;
                r.setIdentity();
                if (t == 1)
                    r.Q.setEulerAngles(C3Vector(piValD2, 0.0, 0.0));
                if (t == 2)
                    r.Q.setEulerAngles(C3Vector(0.0, piValD2, 0.0));
                shape->setLocalTransformation(conf * r);
            }
        }
        if (shape != nullptr)
            App::logMsg(sim_verbosity_msgs, "done.");
        else
            App::logMsg(sim_verbosity_msgs, "Operation aborted.");
        GuiApp::setFullDialogRefreshFlag();
    }

    if (cmd.cmdId == SWITCH_TOINSTANCEINDEX_GUITRIGGEREDCMD)
    {
        App::worldContainer->switchToWorld(cmd.intParams[0]);
    }
    if (cmd.cmdId == SET_ACTIVEPAGE_GUITRIGGEREDCMD)
    {
        App::currentWorld->pageContainer->setActivePage(cmd.intParams[0]);
    }
    if (cmd.cmdId == SET_MOUSEMODE_GUITRIGGEREDCMD)
    {
        GuiApp::setMouseMode(cmd.intParams[0]);
    }
    if (cmd.cmdId == SELECT_VIEW_GUITRIGGEREDCMD)
    {
        CSceneObject* it = App::currentWorld->sceneObjects->getObjectFromHandle(cmd.intParams[0]);
        if (it != nullptr)
        {
            CSPage* view = App::currentWorld->pageContainer->getPage(cmd.intParams[1]);
            if (view != nullptr)
            {
                CSView* subView = view->getView(size_t(cmd.intParams[2]));
                if (subView != nullptr)
                {
                    subView->setLinkedObjectID(it->getObjectHandle(), false);
                    subView->setTimeGraph(cmd.boolParams[0]);
                }
            }
        }
    }

    if (cmd.cmdId == SET_CURRENTDIRECTORY_GUITRIGGEREDCMD)
    {
        if (cmd.intParams[0] == DIRECTORY_ID_TEXTURE)
            App::folders->setTexturesPath(cmd.stringParams[0].c_str());
    }
    if (cmd.cmdId == SHOW_PROGRESSDLGGUITRIGGEREDCMD)
    {
        GuiApp::uiThread->showOrHideProgressBar(true, cmd.intParams[0], cmd.stringParams[0].c_str());
    }
    if (cmd.cmdId == HIDE_PROGRESSDLGGUITRIGGEREDCMD)
    {
        GuiApp::uiThread->showOrHideProgressBar(false);
    }
    if (cmd.cmdId == SET_THUMBNAIL_GUITRIGGEREDCMD)
    {
        App::currentWorld->environment->modelThumbnail_notSerializedHere.setUncompressedThumbnailImage(
            (char*)&cmd.uint8Params[0], true, false);
    }
    if (cmd.cmdId == SET_OBJECT_SELECTION_GUITRIGGEREDCMD)
    {
        App::currentWorld->sceneObjects->deselectObjects();
        for (size_t i = 0; i < cmd.intParams.size(); i++)
            App::currentWorld->sceneObjects->addObjectToSelection(cmd.intParams[i]);
    }
    if (cmd.cmdId == CLEAR_OBJECT_SELECTION_GUITRIGGEREDCMD)
    {
        App::currentWorld->sceneObjects->deselectObjects();
    }
    if (cmd.cmdId == ADD_OBJECTS_TO_SELECTION_GUITRIGGEREDCMD)
    {
        for (size_t i = 0; i < cmd.intParams.size(); i++)
            App::currentWorld->sceneObjects->addObjectToSelection(cmd.intParams[i]);
    }
    if (cmd.cmdId == INVERT_SELECTION_GUITRIGGEREDCMD)
    {
        for (size_t i = 0; i < App::currentWorld->sceneObjects->getObjectCount(); i++)
            App::currentWorld->sceneObjects->xorAddObjectToSelection(
                App::currentWorld->sceneObjects->getObjectFromIndex(i)->getObjectHandle());
    }
    if (cmd.cmdId == POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD)
    {
        App::currentWorld->undoBufferContainer->announceChange();
    }
    if (cmd.cmdId == FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD)
    { // delay later this call until the resources have been actualized on the UI SIDE!!
        GuiApp::setFullDialogRefreshFlag();
        SUIThreadCommand cmdIn;
        SUIThreadCommand cmdOut;
        cmdIn.cmdId = REFRESH_DIALOGS_UITHREADCMD;
        {
            // Following instruction very important in the function below tries to lock resources (or a plugin it
            // calls!):
            SIM_THREAD_INDICATE_UI_THREAD_CAN_DO_ANYTHING;
            GuiApp::executeUiThreadCommand(&cmdIn, &cmdOut);
        }
    }
    if (cmd.cmdId == CALL_DIALOG_FUNCTION_GUITRIGGEREDCMD)
    { // delay later this call until the resources have been actualized on the UI SIDE!!
        SUIThreadCommand cmdIn;
        SUIThreadCommand cmdOut;
        cmdIn.cmdId = CALL_DIALOG_FUNCTION_UITHREADCMD;
        cmdIn.intParams.push_back(cmd.intParams[0]);
        cmdIn.intParams.push_back(cmd.intParams[1]);
        cmdIn.intParams.push_back(cmd.intParams[2]);
        {
            // Following instruction very important in the function below tries to lock resources (or a plugin it
            // calls!):
            SIM_THREAD_INDICATE_UI_THREAD_CAN_DO_ANYTHING;
            GuiApp::executeUiThreadCommand(&cmdIn, &cmdOut);
        }
    }

    if (cmd.cmdId == FULLREFRESH_HIERARCHY_GUITRIGGEREDCMD)
    { // delay later this call until the resources have been actualized on the UI SIDE!!
        GuiApp::setRefreshHierarchyViewFlag();
    }
    if (cmd.cmdId == REFRESH_TOOLBARS_GUITRIGGEREDCMD)
    { // delay later this call until the resources have been actualized on the UI SIDE!!
        GuiApp::setToolbarRefreshFlag();
    }

    // UNDO/REDO:
    //        if (cmd.cmdId==999995)
    //            App::currentWorld->undoBufferContainer->emptyRedoBuffer();
    if (cmd.cmdId == 999996)
        App::currentWorld->undoBufferContainer->announceChangeGradual();
    if (cmd.cmdId == 999997)
        App::currentWorld->undoBufferContainer->announceChangeStart();
    if (cmd.cmdId == 999998)
        App::currentWorld->undoBufferContainer->announceChangeEnd();
    if (cmd.cmdId == 999999)
        App::currentWorld->undoBufferContainer->announceChange();
#endif
}

void CSimThread::_handleAutoSaveSceneCommand(SSimulationThreadCommand cmd)
{
    bool noEditMode = true;
#ifdef SIM_WITH_GUI
    noEditMode = (GuiApp::getEditModeType() == NO_EDIT_MODE);
#endif
    if (CSimFlavor::getBoolVal(16) && (App::userSettings->autoSaveDelay > 0) && (!App::currentWorld->environment->getSceneLocked()) && App::currentWorld->simulation->isSimulationStopped() && noEditMode)
    {
        // First repost a same command:
        App::appendSimulationThreadCommand(cmd, 1.0);
        if (VDateTime::getSecondsSince1970() > (App::currentWorld->environment->autoSaveLastSaveTimeInSecondsSince1970 +
                                                App::userSettings->autoSaveDelay * 60))
        {
            std::string savedLoc = App::currentWorld->environment->getScenePathAndName();
            std::string testScene = App::folders->getAutoSavedScenesPath() + "/";
            testScene += std::to_string(App::worldContainer->getCurrentWorldIndex() + 1) + "-" +
                         App::currentWorld->environment->getUniquePersistentIdString() + ".";
            testScene += SIM_SCENE_EXTENSION;
            CFileOperations::saveScene(testScene.c_str(), false, false, nullptr, nullptr, nullptr, true);
#ifdef SIM_WITH_GUI
            GuiApp::setRebuildHierarchyFlag(); // we might have saved under a different name, we need to reflect it
#endif
            App::currentWorld->environment->setScenePathAndName(savedLoc.c_str());
            App::currentWorld->environment->autoSaveLastSaveTimeInSecondsSince1970 = VDateTime::getSecondsSince1970();
        }
    }
    else
        App::appendSimulationThreadCommand(cmd, 1.0); // repost the same message a bit later
}

#ifdef SIM_WITH_GUI
void CSimThread::_handleClickRayIntersection_old(SSimulationThreadCommand cmd)
{
    double nearClipp = cmd.doubleParams[0];
    C7Vector transf = cmd.transfParams[0];
    bool mouseDown = cmd.boolParams[0];
    int cameraHandle = cmd.intParams[0];

    CCamera* cam = App::currentWorld->sceneObjects->getCameraFromHandle(cameraHandle);
    if (cam != nullptr)
    {
        std::vector<int> currentSelectionState(App::currentWorld->sceneObjects->getSelectedObjectHandlesPtr()[0]);
        C3Vector pt, triNormal;
        int obj = -1;

        bool allObjectsAlsoNonDetectable = false;
        if (GuiApp::mainWindow != nullptr)
        {
            if (mouseDown)
                allObjectsAlsoNonDetectable = (GuiApp::mainWindow->getProxSensorClickSelectDown() < 0);
            else
                allObjectsAlsoNonDetectable = (GuiApp::mainWindow->getProxSensorClickSelectUp() < 0);
        }

        int intParams[8] = {0, 0, 0, 0, 0, 0, 0, 0};
        double floatParams[15] = {nearClipp, 999999.9, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                  0.0, 0.0, 0.0, 0.0, 0.01, 0.0, 0.0};
        int psh = CALL_C_API_CLEAR_ERRORS(simCreateProximitySensor, sim_proximitysensor_ray, sim_objectspecialproperty_detectable, 0, intParams, floatParams, nullptr);
        CALL_C_API_CLEAR_ERRORS(simSetObjectPosition, psh, cameraHandle, transf.X.data);
        CALL_C_API_CLEAR_ERRORS(simSetObjectOrientation, psh, cameraHandle, transf.Q.getEulerAngles().data);
        int displayAttrib = sim_displayattribute_renderpass;
        if (App::currentWorld->simulation->getDynamicContentVisualizationOnly())
            displayAttrib |= sim_displayattribute_dynamiccontentonly;
        CProxSensor* prox = App::currentWorld->sceneObjects->getProximitySensorFromHandle(psh);
        double dist = DBL_MAX;
        bool ptValid = false;
        for (size_t i = 0; i < App::currentWorld->sceneObjects->getObjectCount(); i++)
        {
            CSceneObject* object = App::currentWorld->sceneObjects->getObjectFromIndex(i);
            if (object->getShouldObjectBeDisplayed(cameraHandle, displayAttrib) && object->isPotentiallyMeasurable())
            {
                int theObj;
                bool valid =
                    CProxSensorRoutine::detectEntity(psh, object->getObjectHandle(), true, false, 0.0, pt, dist, true,
                                                     true, theObj, 0.0, triNormal, allObjectsAlsoNonDetectable);
                ptValid = ptValid || valid;
                if (valid)
                    obj = theObj;
            }
        }
        C7Vector sensTr(prox->getFullCumulativeTransformation());
        pt *= sensTr;
        triNormal = sensTr.Q * triNormal;
        CALL_C_API_CLEAR_ERRORS(simRemoveObject, psh);

        // Now generate a script message:
        double ptdata[6] = {pt(0), pt(1), pt(2), triNormal(0), triNormal(1), triNormal(2)};
        int msg;
        if (mouseDown)
            msg = sim_message_prox_sensor_select_down;
        else
            msg = sim_message_prox_sensor_select_up;
        App::currentWorld->outsideCommandQueue_old->addCommand(msg, obj, 0, 0, 0, ptdata, 6);
        App::currentWorld->sceneObjects->setSelectedObjectHandles(currentSelectionState.data(), currentSelectionState.size());
    }
}

bool CSimThread::_renderRequired()
{
    static int lastRenderingTime = 0;
    static int frameCount = 1000;
    bool render = false;
    if (App::currentWorld->simulation->getSimulationState() & sim_simulation_advancing)
    {
        frameCount++;
        render = (frameCount >= App::currentWorld->simulation->getPassesPerRendering());
        if (render)
            frameCount = 0;
    }
    else
    {
        frameCount = 1000;
        render = true;
        if (App::userSettings->getIdleFps() > 0)
        { // When idleFps is 0, then we don't sleep (like when simulating)
            int sleepTime = (1000 / App::userSettings->getIdleFps()) - (VDateTime::getTimeDiffInMs(lastRenderingTime));
            const int minSleepTime = 20; // 4; From 4 to 20 on 8/7/2014 (to avoid saturation)
            int effectiveSleepTime = sleepTime;
            if ((GuiApp::mainWindow != nullptr) && (GuiApp::mainWindow->getMouseButtonState() & 13))
                effectiveSleepTime = minSleepTime;
            if (effectiveSleepTime < minSleepTime)
                effectiveSleepTime = minSleepTime;
            VThread::sleep(effectiveSleepTime);
        }
    }

    if (render)
        lastRenderingTime = (int)VDateTime::getTimeInMs();
    return (render);
}
#endif
