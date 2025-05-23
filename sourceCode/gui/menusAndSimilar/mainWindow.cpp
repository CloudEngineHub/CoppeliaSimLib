#include <simInternal.h>
#include <mainWindow.h>
#include <oGL.h>
#include <simulation.h>
#include <oglSurface.h>
#include <sceneObjectOperations.h>
#include <fileOperations.h>
#include <imgLoaderSaver.h>
#include <toolBarCommand.h>
#include <addOperations.h>
#include <dlgCont.h>
#include <helpMenu.h>
#include <tt.h>
#include <app.h>
#include <auxLibVideo.h>
#include <vVarious.h>
#include <simStrings.h>
#include <vDateTime.h>
#include <vFileFinder.h>
#include <utils.h>
#include <rendering.h>
#include <vMessageBox.h>
#include <boost/lexical_cast.hpp>
#include <qdlgmessageandcheckbox.h>
#include <simFlavor.h>
#include <QMimeData>
#include <QDragEnterEvent>
#include <QUrl>
#include <QToolButton>
#include <QLabel>
#include <QWindow>
//#include <Qsci/qsciscintilla.h> // put this before glx.h
#ifdef LIN_SIM
#include <GL/glx.h>
// Following since those macros are defined by Qt and XLib:
#undef None
#undef KeyPress
#undef KeyRelease
#undef FocusIn
#undef FocusOut
#undef FontChange
#undef Expose
#endif
#ifdef SIM_WITH_GUI
#include <guiApp.h>
#endif

const int DEFAULT_MOUSE_MODE = sim_navigation_camerashift | sim_navigation_clickselection |
                               sim_navigation_ctrlselection | sim_navigation_shiftselection |
                               sim_navigation_camerazoomwheel | sim_navigation_camerarotaterightbutton;

CMainWindow::CMainWindow(int operationalUiParts)
    : QMainWindow()
{
    TRACE_INTERNAL;
    _operationalUiParts = operationalUiParts;
    _focusObject = FOCUS_ON_PAGE;
    _clientArea[0] = 1024;
    _clientArea[1] = 768;
    _toolbar1 = nullptr;
    _toolbar2 = nullptr;
    _menubar = nullptr;
    _fullscreen = false;
    _hasStereo = false;
    _stereoDistance = 0.0;
    _leftEye = true;
    _mouseMode = DEFAULT_MOUSE_MODE;
    _proxSensorClickSelectDown = 0;
    _proxSensorClickSelectUp = 0;
    _mouseWheelEventTime = 0;

    lastInstance = -1;
    timeCounter = (int)VDateTime::getTimeInMs();
    lastTimeRenderingStarted = (int)VDateTime::getTimeInMs();
    previousDisplayWasEnabled = 0;
    previousCursor = -1;

    _lightDialogRefreshFlag = false;
    _fullDialogRefreshFlag = false;
    _dialogRefreshDontPublishFlag = false;
    _toolbarRefreshFlag = false;

    _toolbarButtonObjectShiftEnabled = true;
    _toolbarButtonObjectRotateEnabled = true;
    _toolbarButtonHierarchyEnabled = true;
    _toolbarButtonBrowserEnabled = true;
    _toolbarButtonObjPropEnabled = true;
    _toolbarButtonCalcModulesEnabled_OLD = true;

    _toolbarButtonPlayEnabled = true;
    _toolbarButtonPauseEnabled = true;
    _toolbarButtonStopEnabled = true;

    editModeContainer = new CEditModeContainer();
    oglSurface = new COglSurface();
    codeEditorContainer = new CCodeEditorContainer();

    // the simulator instances were created before the main window was created,
    // so duplicate the correct instance count here:
    for (int i = 0; i < App::worldContainer->getWorldCount(); i++)
        newInstanceAboutToBeCreated();

    // Required for MacOS apparently:
    if ((App::userSettings->highResDisplay == 1) ||
        ((devicePixelRatio() > 1.2) && (App::userSettings->highResDisplay == -1)))
        GuiApp::sc = 2;

    dlgCont = new CDlgCont(this);

    simulationRecorder = new CSimRecorder(App::folders->getVideosPath().c_str());
    _mouseButtonsState = 0;
    _keyDownState = 0;
    _mouseRayValid = false;
    _mouseClickActionCounter_down = 0;
    _mouseClickActionCounter_up = 0;

    //  resize(1024,768);

    // setWindowTitle adds multiple app icons on Linux somehow..
#ifndef LIN_SIM
    setWindowTitle(CSimFlavor::getStringVal(2)
                       .c_str()); // somehow it is important for Linux. Even if this title gets later overwritten, Linux
                                  // keeps this text to display the app name when minimized
#endif

    // --- Browser ---
    modelListWidget = new CModelListWidget();
    modelListWidget->setMaximumWidth(170 * 4);
    modelListWidget->setMinimumWidth(180);

    modelFolderWidget = new CModelFolderWidget(modelListWidget, "Model browser", App::folders->getModelsPath().c_str(),
                                               CSimFlavor::getStringVal(15).c_str());

#ifdef MAC_SIM
    if (modelFolderWidget->hasError())
    {
        SSimulationThreadCommand cmd;
        cmd.cmdId = DISPLAY_MESSAGE_CMD;
        cmd.intParams.push_back(sim_msgbox_type_warning);
        cmd.stringParams.push_back("Model folder not found");
        cmd.stringParams.push_back(IDSNS_MAC_FILE_ATTRIBUTE_PROBLEM);
        App::appendSimulationThreadCommand(cmd, 5000);
    }
#endif

    _modelBrowser = new QSplitter(Qt::Vertical);
    _modelBrowser->addWidget(modelFolderWidget);
    _modelBrowser->addWidget(modelListWidget);
    if (!GuiApp::getBrowserEnabled())
        _modelBrowser->setVisible(
            false); // do not explicitely set to true (not nice artifacts during creation). Is true by default anyways
                    // -----------

    // --- OpenGl widget ---
    openglWidget = new COpenglWidget();
    if (App::userSettings->stereoDist > 0.0)
    {
        if (openglWidget->format().stereo())
        {
            App::logMsg(sim_verbosity_loadinfos | sim_verbosity_onlyterminal, "enabled stereo (OpenGL).");
            _hasStereo = true;
            setStereoDistance(App::userSettings->stereoDist);
        }
        else
            App::logMsg(sim_verbosity_errors, "could not enable stereo (OpenGL).");
    }
#ifdef LIN_SIM
    std::string msg("if CoppeliaSim crashes now, try to install libgl1-mesa-dev on your system:");
    msg += "\n    >sudo apt install libgl1-mesa-dev";
    App::logMsg(sim_verbosity_loadinfos | sim_verbosity_onlyterminal, msg.c_str());
#endif
    openglWidget->makeCurrent();
#ifdef USES_QGLWIDGET
    initGl_ifNeeded();
#endif
#ifdef LIN_SIM
    App::logMsg(sim_verbosity_infos, "...did not crash.");
#endif
    // -----------

    // --- ( openGl widget ) splitter ---
    _sceneHierarchySplitter = new QSplitter(Qt::Horizontal);
    _sceneHierarchySplitter->addWidget(openglWidget);
    // -----------

    // --- Tab widget ---
    tabBar = new QTabBar();
    int ind = tabBar->addTab(App::currentWorld->environment->getSceneNameForUi().c_str());
    tabBar->setTabVisible(ind, _operationalUiParts & sim_gui_menubar);

#ifdef MAC_SIM
    tabBar->setExpanding(true);
#else
    tabBar->setExpanding(false);
#endif

    tabBar->setDocumentMode(true);
    //    tabBar->setStyleSheet("QTabBar::tab { height: 20px;}");
    tabBar->setElideMode(Qt::ElideRight);
    // tabBar->setVisible(false);
    connect(tabBar, SIGNAL(currentChanged(int)), this, SLOT(tabBarIndexChanged(int)));
    // -----------

    // --- Tabbar + hierarchy + OpenGl
    QVBoxLayout* vlay = new QVBoxLayout();
    vlay->setObjectName("vlay");
    vlay->addWidget(tabBar);
    vlay->addWidget(_sceneHierarchySplitter);
    vlay->setSpacing(0);
    vlay->setStretchFactor(tabBar, 0);
    vlay->setStretchFactor(openglWidget, 1);
    vlay->setContentsMargins(0, 0, 0, 0);
    QWidget* tabHierarchyAndOpenGl = new QWidget();
    tabHierarchyAndOpenGl->setLayout(vlay);
    // -----------

    // --- Status bar ---
    statusBar = new CStatusBar();
    QTextDocument* doc = statusBar->document();
    QFont font = doc->defaultFont();
    font.setFamily("Courier New");
    doc->setDefaultFont(font);
    statusBar->setReadOnly(true);
    statusBar->setLineWrapMode(QPlainTextEdit::WidgetWidth);
    statusBar->setMaximumBlockCount(5000);
    statusBar->moveCursor(QTextCursor::End);
    statusBar->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    statusBar->setMinimumHeight(50);
    statusBar->setMaximumHeight(600);
    statusBar->setObjectName("statusBar");
    if ((GuiApp::operationalUIParts & sim_gui_statusbar) == 0)
        statusBar->setVisible(false); // do not explicitely set to true (not nice artifacts during creation). Is true by default anyways
    // ---------------

    // --- statusbar splitter ---
    _statusbarSplitter = new QSplitter(Qt::Vertical);
    _statusbarSplitter->addWidget(tabHierarchyAndOpenGl);
    _statusbarSplitter->addWidget(statusBar);
    _statusbarSplitter->setCollapsible(0, false);
    _statusbarSplitter->setCollapsible(1, true);
    _statusbarSplitter->setOpaqueResize(false);
    QList<int> splitSizes;
    if (App::userSettings->statusbarInitiallyVisible)
        splitSizes << 10000 << 360;
    else
        splitSizes << 10000 << 0;
    _statusbarSplitter->setSizes(splitSizes);
    connect(_statusbarSplitter, SIGNAL(splitterMoved(int, int)), this, SLOT(statusbarSplitterMoved(int, int)));
    // -----------------

    // --- Browser splitter ---
    _modelBrowserSplitter = new QSplitter(Qt::Horizontal);
    _modelBrowserSplitter->addWidget(_modelBrowser);
    _modelBrowserSplitter->addWidget(_statusbarSplitter);
    _modelBrowserSplitter->setCollapsible(0, false);
    _modelBrowserSplitter->setOpaqueResize(false);
    splitSizes.clear();
    splitSizes << 1 << 10000;
    _modelBrowserSplitter->setSizes(splitSizes);
    // -----------------

    setCentralWidget(_modelBrowserSplitter);

    _signalMapper = new QSignalMapper(this);
    connect(_signalMapper, SIGNAL(mapped(int)), this, SLOT(_simMessageHandler(int)));
    _popupSignalMapper = new QSignalMapper(this);
    connect(_popupSignalMapper, SIGNAL(mapped(int)), this, SLOT(_simPopupMessageHandler(int)));
    setAcceptDrops(true);
}

CMainWindow::~CMainWindow()
{
    TRACE_INTERNAL;
    removeDefaultMenuBar();
    disconnect(_popupSignalMapper);
    delete _popupSignalMapper;
    disconnect(_signalMapper);
    delete _signalMapper;
    delete simulationRecorder;
    delete dlgCont;

    ogl::freeOutlineFont();
    ogl::freeBitmapFonts();

    delete codeEditorContainer;
    delete oglSurface;
    delete editModeContainer;
}

void CMainWindow::setBrowserVisible(bool v)
{
    if (_modelBrowser != nullptr)
        _modelBrowser->setVisible(v);
}

void CMainWindow::initializeWindow()
{
    createDefaultMenuBar();
    _createDefaultToolBars();
    setWindowPosAndDim(App::userSettings->initWindowPos[0], App::userSettings->initWindowPos[1],
                       App::userSettings->initWindowSize[0], App::userSettings->initWindowSize[1]);
}

void CMainWindow::announceScriptStateWillBeErased(int scriptHandle, long long int scriptUid)
{
    if (codeEditorContainer != nullptr)
        codeEditorContainer->announceScriptStateWillBeErased(scriptHandle, scriptUid);
}

void CMainWindow::setProxSensorClickSelectDown(int v)
{
    _proxSensorClickSelectDown = v;
}

int CMainWindow::getProxSensorClickSelectDown()
{
    return (_proxSensorClickSelectDown);
}

void CMainWindow::setProxSensorClickSelectUp(int v)
{
    _proxSensorClickSelectUp = v;
}

int CMainWindow::getProxSensorClickSelectUp()
{
    return (_proxSensorClickSelectUp);
}

void CMainWindow::setMouseRay(const C3Vector* orig, const C3Vector* dir)
{
    _mouseRayValid = (orig != nullptr);
    if (_mouseRayValid)
    {
        _mouseRayOrigin = orig[0];
        _mouseRayDirection = dir[0];
    }
}

bool CMainWindow::getMouseRay(C3Vector& orig, C3Vector& dir)
{
    if (_mouseRayValid)
    {
        orig = _mouseRayOrigin;
        dir = _mouseRayDirection;
    }
    return (_mouseRayValid);
}

void CMainWindow::mouseClickAction(bool down)
{
    if (down)
        _mouseClickActionCounter_down++;
    else
        _mouseClickActionCounter_up++;
}

int CMainWindow::getMouseClickActionCounter(bool down)
{
    int retVal;
    if (down)
        retVal = _mouseClickActionCounter_down;
    else
        retVal = _mouseClickActionCounter_up;
    return (retVal);
}

bool CMainWindow::getObjectShiftToggleViaGuiEnabled()
{
    return (_toolbarButtonObjectShiftEnabled);
}

void CMainWindow::setObjectShiftToggleViaGuiEnabled(bool e)
{
    _toolbarButtonObjectShiftEnabled = e;
    _actualizetoolbarButtonState();
}

bool CMainWindow::getObjectRotateToggleViaGuiEnabled()
{
    return (_toolbarButtonObjectRotateEnabled);
}

void CMainWindow::setObjectRotateToggleViaGuiEnabled(bool e)
{
    _toolbarButtonObjectRotateEnabled = e;
    _actualizetoolbarButtonState();
}

void CMainWindow::setHierarchyToggleViaGuiEnabled(bool e)
{
    _toolbarButtonHierarchyEnabled = e;
    _actualizetoolbarButtonState();
}

bool CMainWindow::getHierarchyToggleViaGuiEnabled()
{
    return (_toolbarButtonHierarchyEnabled);
}

void CMainWindow::setBrowserToggleViaGuiEnabled(bool e)
{
    _toolbarButtonBrowserEnabled = e;
    _actualizetoolbarButtonState();
}

bool CMainWindow::getBrowserToggleViaGuiEnabled()
{
    return (_toolbarButtonBrowserEnabled);
}

void CMainWindow::setObjPropToggleViaGuiEnabled(bool e)
{
    _toolbarButtonObjPropEnabled = e;
    _actualizetoolbarButtonState();
}

bool CMainWindow::getObjPropToggleViaGuiEnabled()
{
    return (_toolbarButtonObjPropEnabled);
}

void CMainWindow::setCalcModulesToggleViaGuiEnabled_OLD(bool e)
{
    _toolbarButtonCalcModulesEnabled_OLD = e;
    _actualizetoolbarButtonState();
}

bool CMainWindow::getCalcModulesToggleViaGuiEnabled_OLD()
{
    return (_toolbarButtonCalcModulesEnabled_OLD);
}

void CMainWindow::setPlayViaGuiEnabled(bool e)
{
    _toolbarButtonPlayEnabled = e;
    _actualizetoolbarButtonState();
}

bool CMainWindow::getPlayViaGuiEnabled()
{
    return (_toolbarButtonPlayEnabled);
}

void CMainWindow::setPauseViaGuiEnabled(bool e)
{
    _toolbarButtonPauseEnabled = e;
    _actualizetoolbarButtonState();
}

bool CMainWindow::getPauseViaGuiEnabled()
{
    return (_toolbarButtonPauseEnabled);
}

void CMainWindow::setStopViaGuiEnabled(bool e)
{
    _toolbarButtonStopEnabled = e;
    _actualizetoolbarButtonState();
}

bool CMainWindow::getStopViaGuiEnabled()
{
    return (_toolbarButtonStopEnabled);
}

bool CMainWindow::isFullScreen()
{
    return (_fullscreen);
}

void CMainWindow::setFullScreen(bool f)
{
    if (_fullscreen != f)
    {
        if (VThread::isUiThread())
        { // we are in the UI thread. We execute the command now:
            if (f)
            {
                openglWidget->setParent(nullptr);
                openglWidget->showFullScreen();
                // Following is somehow needed. The generated resize event from showFullScreen provides previous window
                // size values..
                windowResizeEvent(openglWidget->size().width(), openglWidget->size().height());
            }
            else
            {
                openglWidget->showNormal();
                _sceneHierarchySplitter->insertWidget(1, openglWidget);
                windowResizeEvent(width(), height());
            }
        }
        else
        { // We are NOT in the UI thread. We execute the command via the UI thread:
            SUIThreadCommand cmdIn;
            SUIThreadCommand cmdOut;
            cmdIn.cmdId = MAIN_WINDOW_SET_FULLSCREEN_MWTHREADCMD;
            cmdIn.boolParams.push_back(f);
            GuiApp::uiThread->executeCommandViaUiThread(&cmdIn, &cmdOut);
        }
    }
    _fullscreen = f;
}

void CMainWindow::setFocusObject(int f)
{
    _focusObject = f;
}

bool CMainWindow::getHasStereo()
{
    return (_hasStereo);
}

void CMainWindow::setStereoDistance(double d)
{
    _stereoDistance = d;
}

double CMainWindow::getStereoDistance()
{
    return (_stereoDistance);
}

bool CMainWindow::getLeftEye()
{
    return (_leftEye);
}

int CMainWindow::getMouseButtonState()
{ // 1=left, 2=wheel activity, 4=right, 8=middle wheel down
    return (_mouseButtonsState);
}

void CMainWindow::setMouseButtonState(int state)
{ // 1=left, 2=wheel activity, 4=right, 8=middle wheel down
    _mouseButtonsState = state;
}

int CMainWindow::getKeyDownState()
{ // 1=ctrl, 2=shift, 4=up, 8=down, 16=left, 32=right
    return (_keyDownState);
}

void CMainWindow::setKeyDownState(int state)
{ // 1=ctrl, 2=shift, 4=up, 8=down, 16=left, 32=right
    _keyDownState = state;
}

QSignalMapper* CMainWindow::getPopupSignalMapper()
{
    return (_popupSignalMapper);
}

void CMainWindow::_setClientArea(int x, int y)
{
    _clientArea[0] = x;
    _clientArea[1] = y;
    simulationRecorder->setRecordingSizeChanged(x, y);
}

void CMainWindow::getClientArea(int& x, int& y) const
{
    x = _clientArea[0];
    y = _clientArea[1];
}

void CMainWindow::windowResizeEvent(int x, int y)
{
    _setClientArea(x, y);
    _recomputeClientSizeAndPos();
    // printf("Size: %i, %i\n",size().width(),size().height());
    // printf("Pos: %i, %i\n",pos().x(),pos().y());
    // renderScene();
}

void CMainWindow::setWindowPosAndDim(int px, int py, int sx, int sy)
{
    if ((sx == 0) && (sy == 0))
        showMaximized();
    else
    {
        showNormal();
        int frameWidth = 0;
        int frameHeight = 0;
        sx -= frameWidth;
        sy -= frameHeight;
        resize(sx, sy);
        move(px, py);
    }
}

void CMainWindow::refreshDimensions()
{
    _recomputeClientSizeAndPos();
}

void CMainWindow::callDialogFunction(const SUIThreadCommand* cmdIn, SUIThreadCommand* cmdOut)
{
    dlgCont->callDialogFunction(cmdIn, cmdOut);
}

void CMainWindow::refreshDialogs_uiThread()
{
    static std::string scenePath;
    std::string p(App::currentWorld->environment->getScenePathAndName());
    if (scenePath != p)
    {
        scenePath = p;
        setWindowFilePath(scenePath.c_str());
    }
    App::worldContainer->pluginContainer->sendEventCallbackMessageToAllPlugins_old(sim_message_eventcallback_guipass);

    // We refresh dialogs and the toolbar here:
    //----------------------------------------------------------------------------------
    if (App::worldContainer->getCurrentWorldIndex() != lastInstance)
    {
        GuiApp::setFullDialogRefreshFlag();
        GuiApp::setToolbarRefreshFlag();
        createDefaultMenuBar();
        lastInstance = App::worldContainer->getCurrentWorldIndex();
        refreshDimensions();
        // If the instance was switched, we close all material/color dialogs:
        dlgCont->visibleInstanceAboutToSwitch();
    }

    dlgCont->destroyWhatNeedsDestruction();

    if (_lightDialogRefreshFlag || _fullDialogRefreshFlag)
    {
        if (!_dialogRefreshDontPublishFlag)
        {
            int data[4] = {_fullDialogRefreshFlag ? 2 : 0, 0, 0, 0};
            App::worldContainer->pluginContainer->sendEventCallbackMessageToAllPlugins_old(
                sim_message_eventcallback_refreshdialogs, data);
        }
        _dialogRefreshDontPublishFlag = false;
        dlgCont->refresh();
        if (_fullDialogRefreshFlag)
            GuiApp::setRebuildHierarchyFlag();
        GuiApp::setRefreshHierarchyViewFlag();
        _lightDialogRefreshFlag = false;
        _fullDialogRefreshFlag = false;
    }

    if (_toolbarRefreshFlag)
        _actualizetoolbarButtonState();
    _toolbarRefreshFlag = false;
    //----------------------------------------------------------------------------------

#ifndef LIN_SIM
    // setWindowTitle somehow adds multiple app icons on Linux...
    int ct = (int)VDateTime::getTimeInMs();
    if ((VDateTime::getTimeDiffInMs(timeCounter) > 1000) ||
        ((VDateTime::getTimeDiffInMs(timeCounter) > 100) && (!App::getOpenGlDisplayEnabled())))
    { // Refresh the main window text every 1/4 seconds:
        timeCounter = ct;
        std::string title;
        if (App::getOpenGlDisplayEnabled())
        {
            title = (IDS____RENDERING__);
            title += boost::lexical_cast<std::string>(_renderingTimeInMs) + " ms";
        }
        else
        { // We display the simulation time instead:
            title = IDS____SIMULATION_TIME__;
            title += utils::getTimeString(false, App::currentWorld->simulation->getSimulationTime());
        }
        title += " (";
        title += utils::getDoubleString(false, _fps, 1, 2);
        title += " fps)";
        if (editModeContainer->getEditModeType() & TRIANGLE_EDIT_MODE)
            title += IDS____TRIANGLE_EDIT_MODE;
        else if (editModeContainer->getEditModeType() & VERTEX_EDIT_MODE)
            title += IDS____VERTEX_EDIT_MODE;
        else if (editModeContainer->getEditModeType() & EDGE_EDIT_MODE)
            title += IDS____EDGE_EDIT_MODE;
        else if (editModeContainer->getEditModeType() & PATH_EDIT_MODE_OLD)
            title += IDS____PATH_EDIT_MODE_OLD;

        if (editModeContainer->getEditModeType() == NO_EDIT_MODE)
        {
            if (App::currentWorld->simulation->isSimulationRunning())
                title += IDS____SIMULATION_RUNNING;
            else if (App::currentWorld->simulation->isSimulationPaused())
                title += IDS____SIMULATION_PAUSED;
            else
                title += IDS____SIMULATION_STOPPED;
        }

        if (App::currentWorld->environment->getScenePathAndName().compare("") == 0)
            title = std::string(IDS_NEW_FILE) + title;
        else
            title = App::currentWorld->environment->getSceneName() + title;
        title = CSimFlavor::getStringVal(2) + " - " + title;
        setWindowTitle(title.c_str());
    }
#endif

    if (VDateTime::getTimeDiffInMs(_mouseWheelEventTime) > 300)
        _mouseButtonsState &= 0xffff - 2; // We clear the mouse wheel event
}

void CMainWindow::updateOpenGl()
{
#ifdef USES_QGLWIDGET
    renderScene();
#else
    openglWidget->update();
    openglWidget->repaint();
#endif
}

void CMainWindow::renderScene()
{
    static int ins = false;
    if (!ins)
    {
        ins = true;
        TRACE_INTERNAL;
        IF_UI_EVENT_CAN_READ_DATA // needed when the render is triggered by a resize (i.e. the SIM thread could be
                                  // writing to resources)
        {
            App::worldContainer->calcInfo->clearRenderingTime();
            App::worldContainer->calcInfo->renderingStart();

            int startTime = (int)VDateTime::getTimeInMs();
            _fps = 1.0 / (double(VDateTime::getTimeDiffInMs(lastTimeRenderingStarted, startTime)) / 1000.0);
            lastTimeRenderingStarted = startTime;

            if (_fullDialogRefreshFlag)
                GuiApp::setRebuildHierarchyFlag();
            if (_lightDialogRefreshFlag)
                GuiApp::setRefreshHierarchyViewFlag();

            if (windowHandle()->isExposed())
            {
                if ((!App::getOpenGlDisplayEnabled()) && (App::currentWorld->simulation != nullptr) &&
                    (App::currentWorld->simulation->isSimulationStopped()))
                    App::setOpenGlDisplayEnabled(true);

                bool swapTheBuffers = false;
                if (App::getOpenGlDisplayEnabled())
                {
                    swapTheBuffers = true;
                    openglWidget->makeContextCurrent();

                    int mp[2] = {_mouseRenderingPos[0], _mouseRenderingPos[1]};

                    if (!_hasStereo)
                        oglSurface->render(_currentCursor, _mouseButtonsState, mp, nullptr);
                    else
                    {
                        _leftEye = true;
                        glDrawBuffer(GL_BACK_LEFT);
                        oglSurface->render(_currentCursor, _mouseButtonsState, mp, nullptr);
                        _leftEye = false;
                        glDrawBuffer(GL_BACK_RIGHT);
                        oglSurface->render(_currentCursor, _mouseButtonsState, mp, nullptr);
                    }

                    previousDisplayWasEnabled = 0;
                    if (App::userSettings->useGlFinish) // false by default!
                        glFinish();                     // Might be important later (synchronization problems)
                                                        // removed on 2009/12/09 upon recomendation of gamedev community
                    // re-put on 2010/01/11 because it slows down some graphic cards in a
                    // non-proportional way (e.g. 1 object=x ms, 5 objects=20x ms) re-removed again (by
                    // default) on 31/01/2013. Thanks a lot to Cedric Pradalier for pointing problems
                    // appearing with the NVidia drivers
                }
                else
                {
                    if (previousDisplayWasEnabled < 2)
                    { // clear the screen
                        // We draw a dark grey view:
                        swapTheBuffers = true;
                        openglWidget->makeContextCurrent();
                        glDisable(GL_SCISSOR_TEST);
                        glViewport(-2000, -2000, 4000, 4000);
                        glClearColor(0.0, 0.0, 0.0, 1.0);
                        glClear(GL_COLOR_BUFFER_BIT);
                        if (App::userSettings->useGlFinish) // false by default!
                            glFinish();                     // Might be important later (synchronization problems)
                                                            // removed on 2009/12/09 upon recomendation of gamedev community
                                                            // re-put on 2010/01/11 because it slows down some graphic cards in a
                                                            // non-proportional way (e.g. 1 object=x ms, 5 objects=20x ms) re-removed again
                                                            // (by default) on 31/01/2013. Thanks a lot to Cedric Pradalier for pointing
                                                            // problems appearing with the NVidia drivers
                    }
                    if (previousDisplayWasEnabled < 2)
                        previousDisplayWasEnabled++;
                }

                if (simulationRecorder->getIsRecording())
                    simulationRecorder->recordFrameIfNeeded(_clientArea[0], _clientArea[1], 0, 0);
                // GuiApp::uiThread->setFrameRendered();
                if (swapTheBuffers &&
                    (openglWidget != nullptr)) // condition added on 31/1/2012... might help because some VMWare
                                               // installations crash when disabling the rendering
                {
#ifdef USES_QGLWIDGET
                    openglWidget->swapBuffers();
                    openglWidget->doneCurrent();
#else
                    //              openglWidget->update();
                    //              openglWidget->repaint();
                    openglWidget->doneCurrent();
#endif
                }
                _renderingTimeInMs = VDateTime::getTimeDiffInMs(startTime);
            }
            App::worldContainer->calcInfo->renderingEnd();
        }
        ins = false;
    }
    GuiApp::uiThread->setFrameRendered();
}

void CMainWindow::createDefaultMenuBar()
{
    if (GuiApp::operationalUIParts & sim_gui_menubar)
    { // Default menu bar
        removeDefaultMenuBar();
        _menubar = new VMenubar();

        bool menuBarEnabled = true;
        if (oglSurface->isViewSelectionActive() || oglSurface->isPageSelectionActive())
            menuBarEnabled = false;

// Since Qt5, Mac MenuBars don't have separators anymore... this is a quick and dirty workaround:
#define DUMMY_SPACE_QMENUBAR_QT5 ""
#ifdef MAC_SIM
#undef DUMMY_SPACE_QMENUBAR_QT5
#define DUMMY_SPACE_QMENUBAR_QT5 "    "
#endif

        if (editModeContainer->getEditModeType() == NO_EDIT_MODE)
        {
            _fileSystemMenu = new VMenu();
            _menubar->appendMenuAndDetach(_fileSystemMenu, menuBarEnabled,
                                          (std::string(IDS_FILE_MENU_ITEM) + DUMMY_SPACE_QMENUBAR_QT5).c_str());
            connect(_fileSystemMenu->getQMenu(), SIGNAL(aboutToShow()), this, SLOT(_aboutToShowFileSystemMenu()));
        }

        if (editModeContainer->getEditModeType() != MULTISHAPE_EDIT_MODE)
        {
            _editSystemMenu = new VMenu();
            _menubar->appendMenuAndDetach(_editSystemMenu, menuBarEnabled,
                                          (std::string(IDS_EDIT_MENU_ITEM) + DUMMY_SPACE_QMENUBAR_QT5).c_str());
            connect(_editSystemMenu->getQMenu(), SIGNAL(aboutToShow()), this, SLOT(_aboutToShowEditSystemMenu()));
        }

        if (editModeContainer->getEditModeType() == NO_EDIT_MODE)
        {
            _addSystemMenu = new VMenu();
            _menubar->appendMenuAndDetach(_addSystemMenu, menuBarEnabled,
                                          (std::string(IDS_ADD_MENU_ITEM) + DUMMY_SPACE_QMENUBAR_QT5).c_str());
            connect(_addSystemMenu->getQMenu(), SIGNAL(aboutToShow()), this, SLOT(_aboutToShowAddSystemMenu()));
            _simulationSystemMenu = new VMenu();
            _menubar->appendMenuAndDetach(_simulationSystemMenu, menuBarEnabled,
                                          (std::string(IDS_SIMULATION_MENU_ITEM) + DUMMY_SPACE_QMENUBAR_QT5).c_str());
            connect(_simulationSystemMenu->getQMenu(), SIGNAL(aboutToShow()), this,
                    SLOT(_aboutToShowSimulationSystemMenu()));
        }

        if (editModeContainer->getEditModeType() == NO_EDIT_MODE)
        {
            _toolsSystemMenu = new VMenu();
            _menubar->appendMenuAndDetach(_toolsSystemMenu, menuBarEnabled,
                                          (std::string(IDS_TOOLS_MENU_ITEM) + DUMMY_SPACE_QMENUBAR_QT5).c_str());
            connect(_toolsSystemMenu->getQMenu(), SIGNAL(aboutToShow()), this, SLOT(_aboutToShowToolsSystemMenu()));

            if (App::worldContainer->moduleMenuItemContainer->getItemCount() != 0)
            { // Modules (plugins+add-ons)
                VMenu* m = new VMenu();
                App::worldContainer->moduleMenuItemContainer->_menuHandle = new VMenu();
                _menubar->appendMenuAndDetach(App::worldContainer->moduleMenuItemContainer->_menuHandle, menuBarEnabled,
                                              (std::string("Modules") + DUMMY_SPACE_QMENUBAR_QT5).c_str());
                connect(App::worldContainer->moduleMenuItemContainer->_menuHandle->getQMenu(), SIGNAL(aboutToShow()),
                        this, SLOT(_aboutToShowCustomMenu()));
            }
            {
                _instancesSystemMenu = new VMenu();
                _menubar->appendMenuAndDetach(
                    _instancesSystemMenu, menuBarEnabled,
                    (std::string(IDS_INSTANCES_MENU_ITEM) + DUMMY_SPACE_QMENUBAR_QT5).c_str());
                connect(_instancesSystemMenu->getQMenu(), SIGNAL(aboutToShow()), this,
                        SLOT(_aboutToShowInstancesSystemMenu()));
            }
        }

        if (editModeContainer->getEditModeType() == NO_EDIT_MODE)
        {
            _helpSystemMenu = new VMenu();
            _menubar->appendMenuAndDetach(_helpSystemMenu, menuBarEnabled,
                                          (std::string(IDS_HELP_MENU_ITEM) + DUMMY_SPACE_QMENUBAR_QT5).c_str());
            connect(_helpSystemMenu->getQMenu(), SIGNAL(aboutToShow()), this, SLOT(_aboutToShowHelpSystemMenu()));
        }
    }
    refreshDimensions();
}

void CMainWindow::removeDefaultMenuBar()
{
    if (_menubar != nullptr) // GuiApp::operationalUIParts&sim_gui_menubar)
    {
        delete _menubar;
        _menubar = nullptr;
        refreshDimensions();
    }
}

void CMainWindow::_createDefaultToolBars()
{
    if ((_toolbar1 == nullptr) && (GuiApp::operationalUIParts & sim_gui_toolbar1))
    {
        _toolbar1 = new QToolBar(tr("Navigation"));
        _toolbar1->setIconSize(QSize(28, 28));
        _toolbar1->setAllowedAreas(Qt::TopToolBarArea | Qt::BottomToolBarArea);
        addToolBar(Qt::TopToolBarArea, _toolbar1);
#ifdef MAC_SIM
        _toolbar1->setMovable(
            false); // 14/7/2013: since Qt5.1.0 the toolbar looks just plain white when undocked under MacOS
#endif

        _toolbarActionCameraShift =
            _toolbar1->addAction(QIcon(":/toolbarFiles/cameraShift.png"), tr(IDS_TOOLBAR_TOOLTIP_CAMERA_SHIFT));
        _toolbarActionCameraShift->setCheckable(true);
        connect(_toolbarActionCameraShift, SIGNAL(triggered()), _signalMapper, SLOT(map()));
        _signalMapper->setMapping(_toolbarActionCameraShift, CAMERA_SHIFT_NAVIGATION_CMD);

        _toolbarActionCameraRotate =
            _toolbar1->addAction(QIcon(":/toolbarFiles/cameraRotate.png"), tr(IDS_TOOLBAR_TOOLTIP_CAMERA_ROTATE));
        _toolbarActionCameraRotate->setCheckable(true);
        connect(_toolbarActionCameraRotate, SIGNAL(triggered()), _signalMapper, SLOT(map()));
        _signalMapper->setMapping(_toolbarActionCameraRotate, CAMERA_ROTATE_NAVIGATION_CMD);

        _toolbarActionCameraZoom =
            _toolbar1->addAction(QIcon(":/toolbarFiles/cameraZoom.png"), tr(IDS_TOOLBAR_TOOLTIP_CAMERA_ZOOM));
        _toolbarActionCameraZoom->setCheckable(true);
        connect(_toolbarActionCameraZoom, SIGNAL(triggered()), _signalMapper, SLOT(map()));
        _signalMapper->setMapping(_toolbarActionCameraZoom, CAMERA_ZOOM_NAVIGATION_CMD);

        if (CSimFlavor::getBoolVal(12))
        {
            _toolbarActionCameraAngle = _toolbar1->addAction(QIcon(":/toolbarFiles/cameraAngle.png"), tr(IDS_TOOLBAR_TOOLTIP_CAMERA_OPENING_ANGLE));
            _toolbarActionCameraAngle->setCheckable(true);
            connect(_toolbarActionCameraAngle, SIGNAL(triggered()), _signalMapper, SLOT(map()));
            _signalMapper->setMapping(_toolbarActionCameraAngle, CAMERA_ANGLE_NAVIGATION_CMD);
        }

        _toolbarActionCameraSizeToScreen = _toolbar1->addAction(QIcon(":/toolbarFiles/cameraResize.png"),
                                                                tr(IDS_TOOLBAR_TOOLTIP_CAMERA_FIT_TO_SCREEN));
        _toolbarActionCameraSizeToScreen->setCheckable(false);
        connect(_toolbarActionCameraSizeToScreen, SIGNAL(triggered()), _signalMapper, SLOT(map()));
        _signalMapper->setMapping(_toolbarActionCameraSizeToScreen, CAMERA_SHIFT_TO_FRAME_SELECTION_CMD);

        _toolbar1->addSeparator();

        _toolbarActionClickSelection =
            _toolbar1->addAction(QIcon(":/toolbarFiles/clickSelection.png"), tr(IDS_TOOLBAR_TOOLTIP_CLICK_SELECTION));
        _toolbarActionClickSelection->setCheckable(true);
        connect(_toolbarActionClickSelection, SIGNAL(triggered()), _signalMapper, SLOT(map()));
        _signalMapper->setMapping(_toolbarActionClickSelection, OBJECT_SELECTION_SELECTION_CMD);

        _toolbarActionObjectShift =
            _toolbar1->addAction(QIcon(":/toolbarFiles/objectShift.png"), tr(IDS_TOOLBAR_TOOLTIP_OBJECT_SHIFT));
        _toolbarActionObjectShift->setCheckable(true);
        connect(_toolbarActionObjectShift, SIGNAL(triggered()), _signalMapper, SLOT(map()));
        _signalMapper->setMapping(_toolbarActionObjectShift, OBJECT_SHIFT_NAVIGATION_CMD);

        _toolbarActionObjectRotate =
            _toolbar1->addAction(QIcon(":/toolbarFiles/objectRotate.png"), tr(IDS_TOOLBAR_TOOLTIP_OBJECT_ROTATE));
        _toolbarActionObjectRotate->setCheckable(true);
        connect(_toolbarActionObjectRotate, SIGNAL(triggered()), _signalMapper, SLOT(map()));
        _signalMapper->setMapping(_toolbarActionObjectRotate, OBJECT_ROTATE_NAVIGATION_CMD);

        _toolbar1->addSeparator();

        _toolbarActionAssemble =
            _toolbar1->addAction(QIcon(":/toolbarFiles/assemble.png"), tr("Assemble / Disassemble"));
        _toolbarActionAssemble->setCheckable(false);
        connect(_toolbarActionAssemble, SIGNAL(triggered()), _signalMapper, SLOT(map()));
        _signalMapper->setMapping(_toolbarActionAssemble, SCENE_OBJECT_OPERATION_ASSEMBLE_SOOCMD);

        if (CSimFlavor::getBoolVal(12))
        {
            _toolbarActionTransferDna = _toolbar1->addAction(QIcon(":/toolbarFiles/transferDna.png"), tr(IDSN_TRANSFER_DNA));
            _toolbarActionTransferDna->setCheckable(false);
            connect(_toolbarActionTransferDna, SIGNAL(triggered()), _signalMapper, SLOT(map()));
            _signalMapper->setMapping(_toolbarActionTransferDna, SCENE_OBJECT_OPERATION_TRANSFER_DNA_SOOCMD);
        }

        _toolbar1->addSeparator();

        _toolbarActionUndo = _toolbar1->addAction(QIcon(":/toolbarFiles/undo.png"), tr(IDSN_UNDO));
        _toolbarActionUndo->setCheckable(false);
        connect(_toolbarActionUndo, SIGNAL(triggered()), _signalMapper, SLOT(map()));
        _signalMapper->setMapping(_toolbarActionUndo, SCENE_OBJECT_OPERATION_UNDO_SOOCMD);

        _toolbarActionRedo = _toolbar1->addAction(QIcon(":/toolbarFiles/redo.png"), tr(IDSN_REDO));
        _toolbarActionRedo->setCheckable(false);
        connect(_toolbarActionRedo, SIGNAL(triggered()), _signalMapper, SLOT(map()));
        _signalMapper->setMapping(_toolbarActionRedo, SCENE_OBJECT_OPERATION_REDO_SOOCMD);
        _toolbar1->addSeparator();

        if (CSimFlavor::getBoolVal(12))
        {
            _toolbarActionDynamicContentVisualization = _toolbar1->addAction(QIcon(":/toolbarFiles/dynamics.png"), tr(IDS_TOOLBAR_TOOLTIP_VISUALIZE_DYNAMIC_CONTENT));
            _toolbarActionDynamicContentVisualization->setCheckable(true);
            connect(_toolbarActionDynamicContentVisualization, SIGNAL(triggered()), _signalMapper, SLOT(map()));
            _signalMapper->setMapping(_toolbarActionDynamicContentVisualization, SIMULATION_COMMANDS_TOGGLE_DYNAMIC_CONTENT_VISUALIZATION_SCCMD);
        }

        _engineSelectCombo = new QComboBox();

#ifdef WIN_SIM
        _engineSelectCombo->setMinimumWidth(90);
        _engineSelectCombo->setMaximumWidth(90);
        _engineSelectCombo->setMinimumHeight(24);
        _engineSelectCombo->setMaximumHeight(24);
#endif
#ifdef MAC_SIM
        _engineSelectCombo->setMinimumWidth(95);
        _engineSelectCombo->setMaximumWidth(95);
        _engineSelectCombo->setMinimumHeight(24);
        _engineSelectCombo->setMaximumHeight(24);
#endif
#ifdef LIN_SIM
        _engineSelectCombo->setMinimumWidth(90);
        _engineSelectCombo->setMaximumWidth(90);
        _engineSelectCombo->setMinimumHeight(24);
        _engineSelectCombo->setMaximumHeight(24);
#endif

        _engineSelectCombo->addItem(IDS_BULLET_2_78);
        _engineSelectCombo->addItem(IDS_BULLET_2_83);
        _engineSelectCombo->addItem(IDS_ODE);
        _engineSelectCombo->addItem(IDS_VORTEX);
        _engineSelectCombo->addItem(IDS_NEWTON);
        _engineSelectCombo->addItem(IDS_MUJOCO);
#ifdef HAS_DRAKE
        _engineSelectCombo->addItem(IDS_DRAKE);
#endif
        _engineSelectCombo->setToolTip(IDS_TOOLBAR_TOOLTIP_DYNAMICS_ENGINE);
        _toolbar1->addWidget(_engineSelectCombo);
        connect(_engineSelectCombo, SIGNAL(activated(int)), this, SLOT(_engineSelectedViaToolbar(int)));

        _toolbarActionStart =
            _toolbar1->addAction(QIcon(":/toolbarFiles/start.png"), tr(IDS_TOOLBAR_TOOLTIP_SIMULATION_START));
        _toolbarActionStart->setCheckable(true);
        connect(_toolbarActionStart, SIGNAL(triggered()), _signalMapper, SLOT(map()));
        _signalMapper->setMapping(_toolbarActionStart, SIMULATION_COMMANDS_START_RESUME_SIMULATION_REQUEST_SCCMD);

        _toolbarActionPause =
            _toolbar1->addAction(QIcon(":/toolbarFiles/pause.png"), tr(IDS_PAUSE_SIMULATION_MENU_ITEM));
        _toolbarActionPause->setCheckable(true);
        connect(_toolbarActionPause, SIGNAL(triggered()), _signalMapper, SLOT(map()));
        _signalMapper->setMapping(_toolbarActionPause, SIMULATION_COMMANDS_PAUSE_SIMULATION_REQUEST_SCCMD);

        _toolbarActionStop = _toolbar1->addAction(QIcon(":/toolbarFiles/stop.png"), tr(IDS_STOP_SIMULATION_MENU_ITEM));
        _toolbarActionStop->setCheckable(false);
        connect(_toolbarActionStop, SIGNAL(triggered()), _signalMapper, SLOT(map()));
        _signalMapper->setMapping(_toolbarActionStop, SIMULATION_COMMANDS_STOP_SIMULATION_REQUEST_SCCMD);

        _toolbarActionRealTime =
            _toolbar1->addAction(QIcon(":/toolbarFiles/realTime.png"), tr(IDS_TOOLBAR_TOOLTIP_REALTIMESIMULATION));
        _toolbarActionRealTime->setCheckable(true);
        connect(_toolbarActionRealTime, SIGNAL(triggered()), _signalMapper, SLOT(map()));
        _signalMapper->setMapping(_toolbarActionRealTime, SIMULATION_COMMANDS_TOGGLE_REAL_TIME_SIMULATION_SCCMD);

        _toolbarActionReduceSpeed =
            _toolbar1->addAction(QIcon(":/toolbarFiles/reduceSpeed.png"), tr(IDSN_SLOW_DOWN_SIMULATION));
        _toolbarActionReduceSpeed->setCheckable(false);
        connect(_toolbarActionReduceSpeed, SIGNAL(triggered()), _signalMapper, SLOT(map()));
        _signalMapper->setMapping(_toolbarActionReduceSpeed, SIMULATION_COMMANDS_SLOWER_SIMULATION_SCCMD);

        _toolbarActionIncreaseSpeed =
            _toolbar1->addAction(QIcon(":/toolbarFiles/increaseSpeed.png"), tr(IDSN_SPEED_UP_SIMULATION));
        _toolbarActionIncreaseSpeed->setCheckable(false);
        connect(_toolbarActionIncreaseSpeed, SIGNAL(triggered()), _signalMapper, SLOT(map()));
        _signalMapper->setMapping(_toolbarActionIncreaseSpeed, SIMULATION_COMMANDS_FASTER_SIMULATION_SCCMD);

        if (CSimFlavor::getBoolVal(12))
        {
            _toolbarActionToggleVisualization = _toolbar1->addAction(QIcon(":/toolbarFiles/toggleVisualization.png"), "Toggle visualization");
            _toolbarActionToggleVisualization->setCheckable(true);
            connect(_toolbarActionToggleVisualization, SIGNAL(triggered()), _signalMapper, SLOT(map()));
            _signalMapper->setMapping(_toolbarActionToggleVisualization, SIMULATION_COMMANDS_TOGGLE_VISUALIZATION_SCCMD);
            _toolbar1->addSeparator();

            _toolbarActionPageSelector = _toolbar1->addAction(QIcon(":/toolbarFiles/pageSelector.png"), tr(IDSN_PAGE_SELECTOR));
            _toolbarActionPageSelector->setCheckable(true);
            connect(_toolbarActionPageSelector, SIGNAL(triggered()), _signalMapper, SLOT(map()));
            _signalMapper->setMapping(_toolbarActionPageSelector, PAGE_SELECTOR_CMD);
        }

        QWidget* spacer = new QWidget();
        spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        _toolbar1->addWidget(spacer);

        _toolbarLabel = new QLabel(CSimFlavor::getStringVal(21).c_str());
        _toolbar1->addWidget(_toolbarLabel);

        spacer = new QWidget();
        spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        _toolbar1->addWidget(spacer);
    }
    if ((_toolbar2 == nullptr) && (GuiApp::operationalUIParts & sim_gui_toolbar2))
    {
        _toolbar2 = new QToolBar(tr("Tools"));
        _toolbar2->setIconSize(QSize(28, 28));
        _toolbar2->setAllowedAreas(Qt::LeftToolBarArea | Qt::RightToolBarArea);
        addToolBar(Qt::LeftToolBarArea, _toolbar2);
#ifdef MAC_SIM
        _toolbar2->setMovable(
            false); // 14/7/2013: since Qt5.1.0 the toolbar looks just plain white when undocked under MacOS
#endif

        if (CSimFlavor::getBoolVal(12))
        {
            _toolbarActionSimulationSettings = _toolbar2->addAction(QIcon(":/toolbarFiles/simulationSettings.png"), tr(IDSN_SIMULATION_SETTINGS));
            _toolbarActionSimulationSettings->setCheckable(true);
            connect(_toolbarActionSimulationSettings, SIGNAL(triggered()), _signalMapper, SLOT(map()));
            _signalMapper->setMapping(_toolbarActionSimulationSettings, TOGGLE_SIMULATION_DLG_CMD);
            _toolbar2->addSeparator();
        }

        if (CSimFlavor::getBoolVal(12))
        {
            _toolbarActionObjectProperties = _toolbar2->addAction(QIcon(":/toolbarFiles/commonProperties.png"),
                                                                  tr(IDSN_OBJECT_PROPERTIES_MENU_ITEM));
            _toolbarActionObjectProperties->setCheckable(true);
            connect(_toolbarActionObjectProperties, SIGNAL(triggered()), _signalMapper, SLOT(map()));
            _signalMapper->setMapping(_toolbarActionObjectProperties, TOGGLE_OBJECT_DLG_CMD);
        }

        if (App::userSettings->showOldDlgs && CSimFlavor::getBoolVal(12))
        {
            _toolbarActionCalculationModules_OLD =
                _toolbar2->addAction(QIcon(":/toolbarFiles/calcmods.png"), "Old dialogs");
            _toolbarActionCalculationModules_OLD->setCheckable(true);
            connect(_toolbarActionCalculationModules_OLD, SIGNAL(triggered()), _signalMapper, SLOT(map()));
            _signalMapper->setMapping(_toolbarActionCalculationModules_OLD, TOGGLE_CALCULATION_DLG_CMD_OLD);
            _toolbar2->addSeparator();
        }

        if (CSimFlavor::getBoolVal(12) && App::userSettings->showOldDlgs)
        {
            _toolbarActionCollections =
                _toolbar2->addAction(QIcon(":/toolbarFiles/collections.png"), tr(IDSN_COLLECTIONS));
            _toolbarActionCollections->setCheckable(true);
            connect(_toolbarActionCollections, SIGNAL(triggered()), _signalMapper, SLOT(map()));
            _signalMapper->setMapping(_toolbarActionCollections, TOGGLE_COLLECTION_DLG_CMD);
        }

        if (CSimFlavor::getBoolVal(12))
        {
            _toolbarActionShapeEdition =
                _toolbar2->addAction(QIcon(":/toolbarFiles/shapeEdition.png"), tr(IDS_SHAPE_EDITION_TOOLBAR_TIP));
            _toolbarActionShapeEdition->setCheckable(true);
            connect(_toolbarActionShapeEdition, SIGNAL(triggered()), _signalMapper, SLOT(map()));
            _signalMapper->setMapping(_toolbarActionShapeEdition, SHAPE_EDIT_MODE_TOGGLE_ON_OFF_EMCMD);
        }

        if (CSimFlavor::getBoolVal(12) && App::userSettings->showOldDlgs)
        {
            _toolbarActionPathEdition =
                _toolbar2->addAction(QIcon(":/toolbarFiles/pathEdition.png"), tr(IDS_PATH_EDITION_TOOLBAR_TIP));
            _toolbarActionPathEdition->setCheckable(true);
            connect(_toolbarActionPathEdition, SIGNAL(triggered()), _signalMapper, SLOT(map()));
            _signalMapper->setMapping(_toolbarActionPathEdition, PATH_EDIT_MODE_OLD_TOGGLE_ON_OFF_EMCMD);
            _toolbar2->addSeparator();
        }

        _toolbarActionModelBrowser = _toolbar2->addAction(QIcon(":/toolbarFiles/modelBrowser.png"), tr(IDSN_MODEL_BROWSER));
        _toolbarActionModelBrowser->setCheckable(true);
        connect(_toolbarActionModelBrowser, SIGNAL(triggered()), _signalMapper, SLOT(map()));
        _signalMapper->setMapping(_toolbarActionModelBrowser, TOGGLE_BROWSER_DLG_CMD);

        _toolbarActionSceneHierarchy = _toolbar2->addAction(QIcon(":/toolbarFiles/sceneHierarchy.png"), tr(IDSN_SCENE_HIERARCHY));
        _toolbarActionSceneHierarchy->setCheckable(true);
        connect(_toolbarActionSceneHierarchy, SIGNAL(triggered()), _signalMapper, SLOT(map()));
        _signalMapper->setMapping(_toolbarActionSceneHierarchy, TOGGLE_HIERARCHY_DLG_CMD);

        if (CSimFlavor::getBoolVal(12))
        {
            _toolbarActionLayers = _toolbar2->addAction(QIcon(":/toolbarFiles/layers.png"), tr(IDS_LAYERS));
            _toolbarActionLayers->setCheckable(true);
            connect(_toolbarActionLayers, SIGNAL(triggered()), _signalMapper, SLOT(map()));
            _signalMapper->setMapping(_toolbarActionLayers, TOGGLE_LAYERS_DLG_CMD);
        }

        _toolbarActionAviRecorder =
            _toolbar2->addAction(QIcon(":/toolbarFiles/aviRecorder.png"), tr(IDSN_AVI_RECORDER));
        _toolbarActionAviRecorder->setCheckable(true);
        connect(_toolbarActionAviRecorder, SIGNAL(triggered()), _signalMapper, SLOT(map()));
        _signalMapper->setMapping(_toolbarActionAviRecorder, TOGGLE_AVI_RECORDER_DLG_CMD);

        _toolbarActionUserSettings =
            _toolbar2->addAction(QIcon(":/toolbarFiles/userSettings.png"), tr(IDSN_USER_SETTINGS));
        _toolbarActionUserSettings->setCheckable(true);
        connect(_toolbarActionUserSettings, SIGNAL(triggered()), _signalMapper, SLOT(map()));
        _signalMapper->setMapping(_toolbarActionUserSettings, TOGGLE_SETTINGS_DLG_CMD);
    }
    refreshDimensions();
    GuiApp::setToolbarRefreshFlag();
}

bool CMainWindow::event(QEvent* event)
{
    if (event->type() == QEvent::Close)
    {
        App::setOpenGlDisplayEnabled(true); // We might be in fast simulation mode...
        CFileOperations::processCommand(FILE_OPERATION_EXIT_SIMULATOR_FOCMD);
        event->ignore();
        return (true);
    }
    return (QMainWindow::event(event));
}

void CMainWindow::dragEnterEvent(QDragEnterEvent* dEvent)
{
    if (dEvent->mimeData()->hasUrls())
    {
        _mimeText = dEvent->mimeData()->text().toStdString();
        SSimulationThreadCommand cmd;
        cmd.cmdId = DRAGENTER_GUITRIGGEREDCMD;
        cmd.stringParams.push_back(_mimeText);
        App::appendSimulationThreadCommand(cmd);
        dEvent->acceptProposedAction();
    }
}

void CMainWindow::dragLeaveEvent(QDragLeaveEvent* dEvent)
{
    if (_mimeText.size() != 0)
    {
        SSimulationThreadCommand cmd;
        cmd.cmdId = DRAGLEAVE_GUITRIGGEREDCMD;
        cmd.stringParams.push_back(_mimeText);
        App::appendSimulationThreadCommand(cmd);
        _mimeText.clear();
    }
}

void CMainWindow::dropEvent(QDropEvent* dEvent)
{
    if (_mimeText.size() != 0)
    {
        SSimulationThreadCommand cmd;
        cmd.cmdId = DRAGDROP_GUITRIGGEREDCMD;
        cmd.stringParams.push_back(_mimeText);
        App::appendSimulationThreadCommand(cmd);
        _mimeText.clear();
    }
}

void CMainWindow::onLeftMouseButtonDoubleClickTT(int xPos, int yPos)
{
    _mouseRenderingPos[0] = xPos;
    _mouseRenderingPos[1] = _clientArea[1] - yPos;
    int selectionStatus = NOSELECTION;
    int mm = getMouseMode();
    if ((getKeyDownState() & 2) && (mm & sim_navigation_shiftselection))
        selectionStatus = SHIFTSELECTION;
    else if ((getKeyDownState() & 1) && (mm & sim_navigation_ctrlselection))
        selectionStatus = CTRLSELECTION;
    if (App::getOpenGlDisplayEnabled())
        oglSurface->leftMouseButtonDoubleClick(_mouseRenderingPos[0], _mouseRenderingPos[1], selectionStatus);
    App::setOpenGlDisplayEnabled(true); // enable the display again
}

void CMainWindow::onLeftMouseButtonDownTT(int xPos, int yPos)
{ // keys: bit0: ctrl, bit1: shift
    _mouseRenderingPos[0] = xPos;
    _mouseRenderingPos[1] = _clientArea[1] - yPos;
    setMouseButtonState(getMouseButtonState() | 1);
    int mm = getMouseMode();
    int selectionStatus = NOSELECTION;
    if (((getKeyDownState() & 3) == 3) && (mm & sim_navigation_ctrlselection))
        selectionStatus = CTRLSELECTION;
    else if ((getKeyDownState() & 2) && (mm & sim_navigation_shiftselection))
        selectionStatus = SHIFTSELECTION;
    else if ((getKeyDownState() & 1) && (mm & sim_navigation_ctrlselection))
        selectionStatus = CTRLSELECTION;
    oglSurface->clearCaughtElements(0xffff - sim_left_button);
    if (App::getOpenGlDisplayEnabled())
        oglSurface->leftMouseButtonDown(_mouseRenderingPos[0], _mouseRenderingPos[1], selectionStatus);
    App::setOpenGlDisplayEnabled(true); // Enable the display again
    setCurrentCursor(oglSurface->getCursor(xPos, yPos));
}

void CMainWindow::onMiddleMouseButtonDownTT(int xPos, int yPos)
{
    _mouseRenderingPos[0] = xPos;
    _mouseRenderingPos[1] = _clientArea[1] - yPos;
    oglSurface->clearCaughtElements(0xffff - sim_middle_button);
    setMouseButtonState(getMouseButtonState() | 8);
    int upperMouseMode =
        ((getMouseMode() & 0xff00) | sim_navigation_clickselection) -
        sim_navigation_clickselection; // sim_navigation_clickselection because otherwise we have a problem (12/06/2011)
    if (getMouseMode() & sim_navigation_camerarotaterightbutton)
        setMouseMode(upperMouseMode | sim_navigation_camerarotate); // default
    else
        setMouseMode(upperMouseMode | sim_navigation_passive);

    if (App::getOpenGlDisplayEnabled())
        oglSurface->middleMouseButtonDown(_mouseRenderingPos[0], _mouseRenderingPos[1]);
    App::setOpenGlDisplayEnabled(true); // Enable the display again
}

void CMainWindow::onRightMouseButtonDownTT(int xPos, int yPos)
{
    setMouseButtonState(getMouseButtonState() | 4);
    _mouseRenderingPos[0] = xPos;
    _mouseRenderingPos[1] = _clientArea[1] - yPos;
    if (App::userSettings->navigationBackwardCompatibility)
        GuiApp::setLightDialogRefreshFlag();
    oglSurface->clearCaughtElements(0xffff - sim_right_button);
    if (App::getOpenGlDisplayEnabled())
        oglSurface->rightMouseButtonDown(_mouseRenderingPos[0], _mouseRenderingPos[1]);
    App::setOpenGlDisplayEnabled(true); // Enable the display again
}

void CMainWindow::onLeftMouseButtonUpTT(int xPos, int yPos)
{
    _mouseRenderingPos[0] = xPos;
    _mouseRenderingPos[1] = _clientArea[1] - yPos;
    GuiApp::setLightDialogRefreshFlag(); // to refresh dlgs when an object has been dragged for instance
    if (oglSurface->getCaughtElements() & sim_left_button)
        oglSurface->leftMouseButtonUp(_mouseRenderingPos[0], _mouseRenderingPos[1]);
    oglSurface->clearCaughtElements(0xffff - sim_left_button);
    setMouseButtonState(getMouseButtonState() & (0xffff - 1));
    setCurrentCursor(oglSurface->getCursor(xPos, yPos));
}

void CMainWindow::onMiddleMouseButtonUpTT(int xPos, int yPos)
{ // Middle mouse button up is exclusively reserved for rotation
    _mouseRenderingPos[0] = xPos;
    _mouseRenderingPos[1] = _clientArea[1] - yPos;
    if (oglSurface->getCaughtElements() & sim_middle_button)
        oglSurface->middleMouseButtonUp(_mouseRenderingPos[0], _mouseRenderingPos[1]);
    oglSurface->clearCaughtElements(0xffff - sim_middle_button);
}

void CMainWindow::onRightMouseButtonUpTT(int xPos, int yPos)
{ // Right mouse button up is exclusively reserved for pop-up menu
    _mouseRenderingPos[0] = xPos;
    _mouseRenderingPos[1] = _clientArea[1] - yPos;
    if (oglSurface->getCaughtElements() & sim_right_button)
    {
        QPoint glob(openglWidget->mapToGlobal(QPoint(xPos, yPos)));
        oglSurface->rightMouseButtonUp(_mouseRenderingPos[0], _mouseRenderingPos[1], glob.x(), glob.y(), this);
    }
    oglSurface->clearCaughtElements(0xffff - sim_right_button);
    setMouseButtonState(getMouseButtonState() & (0xffff - 4));
}

void CMainWindow::getMouseRenderingPos(int pos[2])
{
    pos[0] = _mouseRenderingPos[0];
    pos[1] = _mouseRenderingPos[1];
}

void CMainWindow::onWheelRotateTT(int delta, int xPos, int yPos)
{
    _mouseRenderingPos[0] = xPos;
    _mouseRenderingPos[1] = _clientArea[1] - yPos;
    setMouseButtonState(getMouseButtonState() | 2);
    if (getMouseMode() & sim_navigation_camerazoomwheel)
    {
        if (App::getOpenGlDisplayEnabled())
            oglSurface->mouseWheel(delta, _mouseRenderingPos[0], _mouseRenderingPos[1]);
    }
    _mouseWheelEventTime = (int)VDateTime::getTimeInMs();
}

void CMainWindow::onMouseMoveTT(int xPos, int yPos)
{
    _mouseRayValid = false;
    _mouseRenderingPos[0] = xPos;
    _mouseRenderingPos[1] = _clientArea[1] - yPos;
    int cur = -1;
    if (App::getOpenGlDisplayEnabled())
    {
        int bts = sim_right_button | sim_middle_button | sim_left_button;
        if (App::userSettings->navigationBackwardCompatibility)
            bts = sim_right_button | sim_left_button;

        oglSurface->mouseMove(_mouseRenderingPos[0], _mouseRenderingPos[1],
                              (oglSurface->getCaughtElements() & bts) == 0);
        cur = oglSurface->getCursor(_mouseRenderingPos[0], _mouseRenderingPos[1]);
    }
    if ((_mouseButtonsState & 1) == 0)
        setCurrentCursor(cur);
}

int CMainWindow::modelDragMoveEvent(int xPos, int yPos, C3Vector* desiredModelPosition)
{
    _mouseRenderingPos[0] = xPos;
    _mouseRenderingPos[1] = _clientArea[1] - yPos;
    if (App::getOpenGlDisplayEnabled())
    {
        int ret = oglSurface->modelDragMoveEvent(_mouseRenderingPos[0], _mouseRenderingPos[1], desiredModelPosition);
        return (ret);
    }
    return (-1); // We can drop the model at the default location
}

void CMainWindow::setCurrentCursor(int cur)
{
    if (cur != -1)
        _currentCursor = cur;
    else
        _currentCursor = sim_cursor_arrow;
    if (previousCursor != _currentCursor)
    {
        setCursor(Qt::PointingHandCursor);
        if (_currentCursor == sim_cursor_arrow)
            setCursor(Qt::ArrowCursor);
        if (_currentCursor == sim_cursor_finger)
            setCursor(Qt::PointingHandCursor);
        if (_currentCursor == sim_cursor_all_directions)
            setCursor(Qt::SizeAllCursor);
        if (_currentCursor == sim_cursor_horizontal_directions)
            setCursor(Qt::SizeHorCursor);
        if (_currentCursor == sim_cursor_vertical_directions)
            setCursor(Qt::SizeVerCursor);
        if (_currentCursor == sim_cursor_slash_directions)
            setCursor(Qt::SizeBDiagCursor);
        if (_currentCursor == sim_cursor_backslash_directions)
            setCursor(Qt::SizeFDiagCursor);
        if (_currentCursor == sim_cursor_open_hand)
            setCursor(Qt::OpenHandCursor);
        if (_currentCursor == sim_cursor_closed_hand)
            setCursor(Qt::ClosedHandCursor);
        if (_currentCursor == sim_cursor_cross)
            setCursor(Qt::CrossCursor);
        previousCursor = _currentCursor;
    }
}

void CMainWindow::simulationAboutToStart()
{
    tabBar->setEnabled(false);
    editModeContainer->simulationAboutToStart();
    // reset those:
    _proxSensorClickSelectDown = 0;
    _proxSensorClickSelectUp = 0;
}

void CMainWindow::simulationEnded()
{
    tabBar->setEnabled(true);
    editModeContainer->simulationEnded();
    _proxSensorClickSelectDown = 0;
    _proxSensorClickSelectUp = 0;
}

void CMainWindow::editModeAboutToStart()
{
    tabBar->setEnabled(false);
}

void CMainWindow::editModeEnded()
{
    tabBar->setEnabled(true);
}

void CMainWindow::_actualizetoolbarButtonState()
{ // This is only for the default toolbars
    bool allowFitToView = false;
    int pageIndex = App::currentWorld->pageContainer->getActivePageIndex();
    CSPage* page = App::currentWorld->pageContainer->getPage(pageIndex);
    if (page != nullptr)
    {
        int ind = page->getLastMouseDownViewIndex();
        if (ind == -1)
            ind = 0;
        CSView* view = page->getView(size_t(ind));
        if (view != nullptr)
        {
            CCamera* cam = App::currentWorld->sceneObjects->getCameraFromHandle(view->getLinkedObjectID());
            allowFitToView = (cam != nullptr);
        }
    }

    bool noEditMode = (editModeContainer->getEditModeType() == NO_EDIT_MODE);
    bool noUiNorMultishapeEditMode = (editModeContainer->getEditModeType() != MULTISHAPE_EDIT_MODE);
    bool noSelector = ((!oglSurface->isPageSelectionActive()) && (!oglSurface->isViewSelectionActive()));

    size_t selS = App::currentWorld->sceneObjects->getSelectionCount();
    bool disassembleEnabled = false;
    bool assembleEnabled = false;
    if (selS == 1)
        disassembleEnabled = GuiApp::canDisassemble(App::currentWorld->sceneObjects->getLastSelectionHandle());
    else if (selS == 2)
        assembleEnabled = GuiApp::canAssemble(App::currentWorld->sceneObjects->getLastSelectionHandle(),
                                              App::currentWorld->sceneObjects->getObjectHandleFromSelectionIndex(0));

    bool transferDnaAllowed = false;
    if ((selS == 1) && noSelector && (editModeContainer->getEditModeType() == NO_EDIT_MODE) &&
        App::currentWorld->simulation->isSimulationStopped())
    {
        CSceneObject* it = App::currentWorld->sceneObjects->getLastSelectionObject();
        if (it->getModelBase())
        {
            std::vector<CSceneObject*> toExplore;
            for (size_t i = 0; i < App::currentWorld->sceneObjects->getOrphanCount(); i++)
                toExplore.push_back(App::currentWorld->sceneObjects->getOrphanFromIndex(i));
            while (toExplore.size() > 0)
            {
                CSceneObject* obj = toExplore[0];
                toExplore.erase(toExplore.begin());
                if (obj != it)
                {
                    if (obj->getModelBase() && (obj->getDnaString().compare(it->getDnaString()) == 0))
                    {
                        transferDnaAllowed = true;
                        break;
                    }
                    else
                        toExplore.insert(toExplore.end(), obj->getChildren()->begin(), obj->getChildren()->end());
                }
            }
        }
    }

    if (_toolbar1 != nullptr)
    { // We enable/disable/check/uncheck some buttons:
        _toolbarActionCameraShift->setEnabled(noSelector);
        _toolbarActionCameraShift->setChecked((getMouseMode() & 0x00ff) == sim_navigation_camerashift);
        _toolbarActionCameraRotate->setEnabled(noSelector);
        _toolbarActionCameraRotate->setChecked((getMouseMode() & 0x00ff) == sim_navigation_camerarotate);
        _toolbarActionCameraZoom->setEnabled(noSelector);
        _toolbarActionCameraZoom->setChecked((getMouseMode() & 0x00ff) == sim_navigation_camerazoom);
        _toolbarActionCameraSizeToScreen->setEnabled(allowFitToView && noSelector);
        if (assembleEnabled)
            _toolbarActionAssemble->setIcon(QIcon(":/toolbarFiles/assemble.png"));
        else
            _toolbarActionAssemble->setIcon(QIcon(":/toolbarFiles/disassemble.png"));
        _toolbarActionAssemble->setEnabled(assembleEnabled || disassembleEnabled);
        _toolbarActionObjectShift->setEnabled(noUiNorMultishapeEditMode && noSelector && _toolbarButtonObjectShiftEnabled);
        _toolbarActionObjectShift->setChecked((getMouseMode() & 0x00ff) == sim_navigation_objectshift);
        bool rot = true;
        if (App::currentWorld->sceneObjects != nullptr)
            rot = editModeContainer->pathPointManipulation->getSelectedPathPointIndicesSize_nonEditMode() == 0;
        _toolbarActionObjectRotate->setEnabled(noUiNorMultishapeEditMode && rot && noSelector && _toolbarButtonObjectRotateEnabled);
        _toolbarActionObjectRotate->setChecked((getMouseMode() & 0x00ff) == sim_navigation_objectrotate);
        _toolbarActionClickSelection->setEnabled(noSelector);
        _toolbarActionClickSelection->setChecked((getMouseMode() & 0x0300) == sim_navigation_clickselection);
        _toolbarActionUndo->setEnabled(App::currentWorld->undoBufferContainer->canUndo() && noSelector);
        _toolbarActionRedo->setEnabled(App::currentWorld->undoBufferContainer->canRedo() && noSelector);
        _engineSelectCombo->setEnabled((editModeContainer->getEditModeType() == NO_EDIT_MODE) && App::currentWorld->simulation->isSimulationStopped() && App::currentWorld->dynamicsContainer->getDynamicsEnabled() && noSelector);
        int ver;
        int eng = App::currentWorld->dynamicsContainer->getDynamicEngineType(&ver);
        if ((eng == sim_physics_bullet) && (ver == 0))
            _engineSelectCombo->setCurrentIndex(0);
        if ((eng == sim_physics_bullet) && (ver == 283))
            _engineSelectCombo->setCurrentIndex(1);
        if (eng == sim_physics_ode)
            _engineSelectCombo->setCurrentIndex(2);
        if (eng == sim_physics_vortex)
            _engineSelectCombo->setCurrentIndex(3);
        if (eng == sim_physics_newton)
            _engineSelectCombo->setCurrentIndex(4);
        if (eng == sim_physics_mujoco)
            _engineSelectCombo->setCurrentIndex(5);
#ifdef HAS_DRAKE
        if (eng == sim_physics_drake)
            _engineSelectCombo->setCurrentIndex(6);
#endif
        _toolbarActionStart->setEnabled(_toolbarButtonPlayEnabled && (editModeContainer->getEditModeType() == NO_EDIT_MODE) && (!App::currentWorld->simulation->isSimulationRunning()) && noSelector);
        _toolbarActionStart->setChecked(App::currentWorld->simulation->isSimulationRunning());
        _toolbarActionPause->setEnabled(_toolbarButtonPauseEnabled && (editModeContainer->getEditModeType() == NO_EDIT_MODE) && App::currentWorld->simulation->isSimulationRunning() && noSelector);
        _toolbarActionPause->setChecked(App::currentWorld->simulation->isSimulationPaused());
        _toolbarActionStop->setEnabled(_toolbarButtonStopEnabled && (editModeContainer->getEditModeType() == NO_EDIT_MODE) && (!App::currentWorld->simulation->isSimulationStopped()) && noSelector);
        _toolbarActionRealTime->setEnabled((editModeContainer->getEditModeType() == NO_EDIT_MODE) && App::currentWorld->simulation->isSimulationStopped() && noSelector);
        _toolbarActionRealTime->setChecked(App::currentWorld->simulation->getIsRealTimeSimulation());
        _toolbarActionReduceSpeed->setEnabled(App::currentWorld->simulation->canGoSlower() && noSelector);
        _toolbarActionIncreaseSpeed->setEnabled(App::currentWorld->simulation->canGoFaster() && noSelector);
        _toolbarLabel->setText(CSimFlavor::getStringVal(21).c_str());
        if (CSimFlavor::getBoolVal(12))
        {
            _toolbarActionCameraAngle->setEnabled(noSelector);
            _toolbarActionCameraAngle->setChecked((getMouseMode() & 0x00ff) == sim_navigation_cameraangle);
            _toolbarActionTransferDna->setEnabled(transferDnaAllowed);
            _toolbarActionDynamicContentVisualization->setEnabled((!App::currentWorld->simulation->isSimulationStopped()) && noSelector);
            _toolbarActionDynamicContentVisualization->setChecked(App::currentWorld->simulation->getDynamicContentVisualizationOnly());
            _toolbarActionToggleVisualization->setEnabled(App::currentWorld->simulation->isSimulationRunning() && noSelector);
            _toolbarActionToggleVisualization->setChecked(!App::getOpenGlDisplayEnabled());
            _toolbarActionPageSelector->setEnabled((!oglSurface->isViewSelectionActive()));
            _toolbarActionPageSelector->setChecked(oglSurface->isPageSelectionActive());
        }
    }
    if (_toolbar2 != nullptr)
    { // We enable/disable/check/uncheck some buttons:
        if (CSimFlavor::getBoolVal(12))
        {
            _toolbarActionSimulationSettings->setEnabled(noEditMode && noSelector);
            _toolbarActionSimulationSettings->setChecked(dlgCont->isVisible(SIMULATION_DLG));
            _toolbarActionObjectProperties->setEnabled(_toolbarButtonObjPropEnabled && noEditMode && noSelector);
            _toolbarActionObjectProperties->setChecked(dlgCont->isVisible(OBJECT_DLG));
            _toolbarActionShapeEdition->setEnabled((noSelector && (selS == 1) &&
                                                    App::currentWorld->sceneObjects->isLastSelectionOfType(sim_sceneobject_shape) &&
                                                    App::currentWorld->simulation->isSimulationStopped() &&
                                                    (editModeContainer->getEditModeType() == NO_EDIT_MODE)) ||
                                                   (editModeContainer->getEditModeType() & SHAPE_EDIT_MODE) ||
                                                   (editModeContainer->getEditModeType() & MULTISHAPE_EDIT_MODE));
            _toolbarActionShapeEdition->setChecked(editModeContainer->getEditModeType() & SHAPE_EDIT_MODE);
            _toolbarActionLayers->setEnabled(true);
            _toolbarActionLayers->setChecked(dlgCont->isVisible(LAYERS_DLG));
            if (App::userSettings->showOldDlgs)
            {
                _toolbarActionCalculationModules_OLD->setEnabled(_toolbarButtonCalcModulesEnabled_OLD && noEditMode && noSelector);
                _toolbarActionCalculationModules_OLD->setChecked(dlgCont->isVisible(CALCULATION_DLG_OLD));
                _toolbarActionCollections->setEnabled(noEditMode && noSelector);
                _toolbarActionCollections->setChecked(dlgCont->isVisible(COLLECTION_DLG));
                _toolbarActionPathEdition->setEnabled((noSelector && (selS == 1) &&
                                                       App::currentWorld->sceneObjects->isLastSelectionOfType(sim_sceneobject_path) &&
                                                       App::currentWorld->simulation->isSimulationStopped() &&
                                                       (editModeContainer->getEditModeType() == NO_EDIT_MODE)) ||
                                                      (editModeContainer->getEditModeType() & PATH_EDIT_MODE_OLD));
                _toolbarActionPathEdition->setChecked(editModeContainer->getEditModeType() == PATH_EDIT_MODE_OLD);
            }
        }

        _toolbarActionModelBrowser->setEnabled(noEditMode && noSelector && _toolbarButtonBrowserEnabled);
        _toolbarActionModelBrowser->setChecked(dlgCont->isVisible(BROWSER_DLG));
        _toolbarActionSceneHierarchy->setEnabled(noEditMode && noSelector && _toolbarButtonHierarchyEnabled && ((!App::userSettings->sceneHierarchyHiddenDuringSimulation) || App::currentWorld->simulation->isSimulationStopped()));
        _toolbarActionSceneHierarchy->setChecked(dlgCont->isVisible(HIERARCHY_DLG));
        _toolbarActionAviRecorder->setEnabled(noEditMode && noSelector && (CAuxLibVideo::video_recorderGetEncoderString != nullptr));
        _toolbarActionAviRecorder->setChecked(dlgCont->isVisible(AVI_RECORDER_DLG));
        _toolbarActionUserSettings->setEnabled(noEditMode && noSelector);
        _toolbarActionUserSettings->setChecked(dlgCont->isVisible(SETTINGS_DLG));
    }
}

void CMainWindow::_recomputeClientSizeAndPos()
{
    if (windowHandle() && windowHandle()->isExposed() && (_clientArea[0] != 0) &&
        (_clientArea[1] !=
         0)) // Added the two last args to avoid a collaps of the hierarchy when switching to another app (2011/01/26)
        oglSurface->setSurfaceSizeAndPosition(_clientArea[0],
                                              _clientArea[1] + App::userSettings->renderingSurfaceVResize, 0,
                                              App::userSettings->renderingSurfaceVShift);
}

void CMainWindow::_engineSelectedViaToolbar(int index)
{
    if (index == 0)
        App::currentWorld->simulation->processCommand(SIMULATION_COMMANDS_TOGGLE_TO_BULLET_2_78_ENGINE_SCCMD);
    if (index == 1)
        App::currentWorld->simulation->processCommand(SIMULATION_COMMANDS_TOGGLE_TO_BULLET_2_83_ENGINE_SCCMD);
    if (index == 2)
        App::currentWorld->simulation->processCommand(SIMULATION_COMMANDS_TOGGLE_TO_ODE_ENGINE_SCCMD);
    if (index == 3)
        App::currentWorld->simulation->processCommand(SIMULATION_COMMANDS_TOGGLE_TO_VORTEX_ENGINE_SCCMD);
    if (index == 4)
        App::currentWorld->simulation->processCommand(SIMULATION_COMMANDS_TOGGLE_TO_NEWTON_ENGINE_SCCMD);
    if (index == 5)
        App::currentWorld->simulation->processCommand(SIMULATION_COMMANDS_TOGGLE_TO_MUJOCO_ENGINE_SCCMD);
    if (index == 6)
        App::currentWorld->simulation->processCommand(SIMULATION_COMMANDS_TOGGLE_TO_DRAKE_ENGINE_SCCMD);
}

void CMainWindow::_simPopupMessageHandler(int id)
{
    if (VMenubar::doNotExecuteCommandButMemorizeIt)
    {
        VMenubar::memorizedCommand = id;
        VMenubar::doNotExecuteCommandButMemorizeIt = false;
        return;
    }
    _simMessageHandler(id);
}

void CMainWindow::_simMessageHandler(int id)
{
    bool processed = false;
    processed = CToolBarCommand::processCommand(id);
    if (!processed)
        processed = CFileOperations::processCommand(id);
    if (!processed)
        processed = CSceneObjectOperations::processCommand(id);
    if (!processed)
        processed = editModeContainer->processCommand(id, nullptr);
    if (!processed)
        processed = CAddOperations::processCommand(id, nullptr);
    if (!processed)
        processed = App::currentWorld->simulation->processCommand(id);
    if (!processed)
        processed = dlgCont->processCommand(id);
    if (!processed)
        processed = CHelpMenu::processCommand(id);
    if (!processed)
        processed = App::worldContainer->processGuiCommand(id);
    if (!processed)
        processed = App::worldContainer->moduleMenuItemContainer->processCommand(id);
    GuiApp::setToolbarRefreshFlag();
}

void CMainWindow::_aboutToShowFileSystemMenu()
{
    _fileSystemMenu->clear();
    CFileOperations::addMenu(_fileSystemMenu);
}

void CMainWindow::_aboutToShowEditSystemMenu()
{
    _editSystemMenu->clear();
    if (editModeContainer->getEditModeType() == NO_EDIT_MODE)
        CSceneObjectOperations::addMenu(_editSystemMenu);
    else
        editModeContainer->addMenu(_editSystemMenu, nullptr);
}

void CMainWindow::_aboutToShowAddSystemMenu()
{
    _addSystemMenu->clear();
    CAddOperations::addMenu(_addSystemMenu, nullptr, false, -1);
}

void CMainWindow::_aboutToShowSimulationSystemMenu()
{
    _simulationSystemMenu->clear();
    App::currentWorld->simulation->addMenu(_simulationSystemMenu);
}

void CMainWindow::_aboutToShowToolsSystemMenu()
{
    _toolsSystemMenu->clear();
    dlgCont->addMenu(_toolsSystemMenu);
}

void CMainWindow::_aboutToShowHelpSystemMenu()
{
    _helpSystemMenu->clear();
    CHelpMenu::addMenu(_helpSystemMenu);
}

void CMainWindow::_aboutToShowInstancesSystemMenu()
{
    _instancesSystemMenu->clear();
    App::worldContainer->addMenu(_instancesSystemMenu);
}

void CMainWindow::_aboutToShowCustomMenu()
{
    App::worldContainer->moduleMenuItemContainer->_menuHandle->clear();
    App::worldContainer->moduleMenuItemContainer->addMenus(App::worldContainer->moduleMenuItemContainer->_menuHandle);
}

void CMainWindow::statusbarSplitterMoved(int pos, int index)
{
    if (_statusbarSplitter->sizes()[1] <= 60)
        statusBar->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    else
        statusBar->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
}

void CMainWindow::onKeyPress(SMouseOrKeyboardOrResizeEvent e)
{
    TRACE_INTERNAL;
    if (e.specialKey != -1)
        oglSurface->keyPress(e.specialKey, this);
    else
    {
        bool processed = false;
        if (e.key == Qt::Key_Control)
        {
            setKeyDownState(getKeyDownState() | 1);
            processed = true;
        }
        if (e.key == Qt::Key_Shift)
        {
            setKeyDownState(getKeyDownState() | 2);
            processed = true;
        }
        if (e.key == Qt::Key_Up)
        {
            setKeyDownState(getKeyDownState() | 4);
            if (App::getOpenGlDisplayEnabled())
                oglSurface->keyPress(UP_KEY, this);
            processed = true;
        }
        if (e.key == Qt::Key_Down)
        {
            setKeyDownState(getKeyDownState() | 8);
            if (App::getOpenGlDisplayEnabled())
                oglSurface->keyPress(DOWN_KEY, this);
            processed = true;
        }
        if (e.key == Qt::Key_Left)
        {
            setKeyDownState(getKeyDownState() | 16);
            if (App::getOpenGlDisplayEnabled())
                oglSurface->keyPress(LEFT_KEY, this);
            processed = true;
        }
        if (e.key == Qt::Key_Right)
        {
            setKeyDownState(getKeyDownState() | 32);
            if (App::getOpenGlDisplayEnabled())
                oglSurface->keyPress(RIGHT_KEY, this);
            processed = true;
        }
        if (e.key == Qt::Key_Delete)
        {
            if (App::getOpenGlDisplayEnabled())
                oglSurface->keyPress(DELETE_KEY, this);
            processed = true;
        }
        if (e.key == Qt::Key_Escape)
        {
            App::setOpenGlDisplayEnabled(true); // Esc enables the display again
            oglSurface->setFocusObject(FOCUS_ON_PAGE);
            setFocusObject(oglSurface->getFocusObject());
            oglSurface->keyPress(ESC_KEY, this);
            processed = true;
        }
        if (e.key == Qt::Key_Tab)
        {
            if (App::getOpenGlDisplayEnabled())
                oglSurface->keyPress(TAB_KEY, this);
            processed = true;
        }
        if ((e.key == Qt::Key_Enter) || (e.key == Qt::Key_Return))
        {
            if (App::getOpenGlDisplayEnabled())
                oglSurface->keyPress(ENTER_KEY, this);
            processed = true;
        }
        if (e.key == Qt::Key_Backspace)
        {
            if (App::getOpenGlDisplayEnabled())
                oglSurface->keyPress(BACKSPACE_KEY, this);
            processed = true;
        }
        if (getKeyDownState() & 1)
        { // Very specific to CoppeliaSim, except for ctrl+Q (which doesn't exist by default on Windows)
            if (e.key == 81)
            {
                oglSurface->keyPress(CTRL_Q_KEY, this);
                processed = true;
            }
            if (e.key == 32)
            {
                oglSurface->keyPress(CTRL_SPACE_KEY, this);
                processed = true;
            }
            if (e.key == 68)
            {
                oglSurface->keyPress(CTRL_D_KEY, this);
                processed = true;
            }
            if (e.key == 71)
            {
                oglSurface->keyPress(CTRL_G_KEY, this);
                processed = true;
            }
            if (e.key == 69)
            {
                oglSurface->keyPress(CTRL_E_KEY, this);
                processed = true;
            }
            if (e.key == 66)
            {
                CToolBarCommand::processCommand(CAMERA_SHIFT_TO_FRAME_SELECTION_CMD);
                processed = true;
            }
        }

        if (!processed)
        {
            QByteArray ba(e.unicodeText.toLatin1());
            if (ba.length() >= 1)
            {
                if (App::getOpenGlDisplayEnabled())
                    oglSurface->keyPress(int(ba.at(0)), this);
            }
        }
    }
}

void CMainWindow::onKeyRelease(SMouseOrKeyboardOrResizeEvent e)
{
    TRACE_INTERNAL;
    int key = e.key;
    if (key == Qt::Key_Control)
        setKeyDownState(getKeyDownState() & (0xffff - 1));
    if (key == Qt::Key_Shift)
        setKeyDownState(getKeyDownState() & (0xffff - 2));
    if (key == Qt::Key_Up)
        setKeyDownState(getKeyDownState() & (0xffff - 4));
    if (key == Qt::Key_Down)
        setKeyDownState(getKeyDownState() & (0xffff - 8));
    if (key == Qt::Key_Left)
        setKeyDownState(getKeyDownState() & (0xffff - 16));
    if (key == Qt::Key_Right)
        setKeyDownState(getKeyDownState() & (0xffff - 32));
}

void CMainWindow::setDefaultMouseMode()
{
    TRACE_INTERNAL;
    setMouseMode(DEFAULT_MOUSE_MODE);
}

int CMainWindow::getMouseMode()
{
    //    sim_navigation_clickselection
    return (_mouseMode);
}

void CMainWindow::setMouseMode(int mm)
{ // can be called by any thread
    TRACE_INTERNAL;
    if ((!oglSurface->isViewSelectionActive()) && (!oglSurface->isPageSelectionActive()))
    {
        _mouseMode = mm;
        int bla = mm & 0x00f;
        if ((bla == sim_navigation_objectshift) || (bla == sim_navigation_objectrotate))
        {
            openOrBringDlgToFront(TRANSLATION_ROTATION_DLG);
            activateMainWindow();
        }
        else
            closeDlg(TRANSLATION_ROTATION_DLG);

        GuiApp::setToolbarRefreshFlag();
        GuiApp::setFullDialogRefreshFlag();
    }
}

void CMainWindow::setLightDialogRefreshFlag()
{
    _lightDialogRefreshFlag = true;
    _toolbarRefreshFlag = true;
}

void CMainWindow::setFullDialogRefreshFlag()
{
    _fullDialogRefreshFlag = true;
    _toolbarRefreshFlag = true;
}

void CMainWindow::setDialogRefreshDontPublishFlag()
{
    _dialogRefreshDontPublishFlag = true;
}

void CMainWindow::setToolbarRefreshFlag()
{
    _toolbarRefreshFlag = true;
}

void CMainWindow::newInstanceAboutToBeCreated()
{
    TRACE_INTERNAL;
    if (codeEditorContainer != nullptr)
        codeEditorContainer->showOrHideAll(false);
}

void CMainWindow::newInstanceWasJustCreated()
{
    TRACE_INTERNAL;
    int ind = tabBar->addTab(App::currentWorld->environment->getSceneNameForUi().c_str());
    tabBar->setTabVisible(ind, _operationalUiParts & sim_gui_menubar);
    tabBar->setCurrentIndex(App::worldContainer->getCurrentWorldIndex());
}

void CMainWindow::instanceAboutToBeDestroyed(int currentInstanceIndex)
{
    TRACE_INTERNAL;
    codeEditorContainer->sceneClosed(App::currentWorld->environment->getSceneUniqueID());

    tabBar->removeTab(currentInstanceIndex);
}

void CMainWindow::instanceAboutToChange(int newInstanceIndex)
{
    TRACE_INTERNAL;
    if (codeEditorContainer != nullptr)
        codeEditorContainer->showOrHideAll(false);
}

void CMainWindow::instanceHasChanged(int newInstanceIndex)
{
    TRACE_INTERNAL;

    if (tabBar->currentIndex() != newInstanceIndex)
        tabBar->setCurrentIndex(newInstanceIndex);

    App::setOpenGlDisplayEnabled(true);
    if (codeEditorContainer != nullptr)
        codeEditorContainer->showOrHideAll(true);
}

void CMainWindow::newSceneNameWasSet(const char* name)
{
    tabBar->setTabText(tabBar->currentIndex(), name);
}

void CMainWindow::tabBarIndexChanged(int newIndex)
{
    App::worldContainer->processGuiCommand(SWITCH_TOINSTANCEWITHTHUMBNAILSAVEINDEX0_GUIGUICMD + newIndex);
}

void CMainWindow::_closeDialogTemporarilyIfOpened(int dlgID, std::vector<int>& vect)
{
    if (GuiApp::mainWindow->dlgCont->isVisible(dlgID))
    {
        GuiApp::mainWindow->dlgCont->close(dlgID);
        vect.push_back(dlgID);
    }
}

void CMainWindow::closeTemporarilyDialogsForPageSelector()
{
    if (VThread::isUiThread())
    { // we are in the UI thread. We execute the command now:
        if (codeEditorContainer != nullptr)
            codeEditorContainer->showOrHideAll(false);
        _closeDialogTemporarilyIfOpened(SETTINGS_DLG, _dialogsClosedTemporarily_pageSelector);
        _closeDialogTemporarilyIfOpened(SIMULATION_DLG, _dialogsClosedTemporarily_pageSelector);
        _closeDialogTemporarilyIfOpened(ENVIRONMENT_DLG, _dialogsClosedTemporarily_pageSelector);
        _closeDialogTemporarilyIfOpened(COLLECTION_DLG, _dialogsClosedTemporarily_pageSelector);
        _closeDialogTemporarilyIfOpened(OBJECT_DLG, _dialogsClosedTemporarily_pageSelector);
        _closeDialogTemporarilyIfOpened(CALCULATION_DLG_OLD, _dialogsClosedTemporarily_pageSelector);
        _closeDialogTemporarilyIfOpened(TRANSLATION_ROTATION_DLG, _dialogsClosedTemporarily_pageSelector);
        _closeDialogTemporarilyIfOpened(BROWSER_DLG, _dialogsClosedTemporarily_pageSelector);

        dlgCont->close(COLOR_DLG);
        dlgCont->close(LIGHTMATERIAL_DLG);
        dlgCont->close(MATERIAL_DLG);
        dlgCont->close(FOG_DLG);
        dlgCont->close(TEXTURE_DLG);
    }
    else
    { // We are NOT in the UI thread. We execute the command via the UI thread:
        SUIThreadCommand cmdIn;
        SUIThreadCommand cmdOut;
        cmdIn.cmdId = MAIN_WINDOW_PAGE_SELECTOR_DLG_CLOSE_MWUITHREADCMD;
        GuiApp::uiThread->executeCommandViaUiThread(&cmdIn, &cmdOut);
    }
}

void CMainWindow::reopenTemporarilyClosedDialogsForPageSelector()
{
    if (VThread::isUiThread())
    { // we are in the UI thread. We execute the command now:
        for (int i = 0; i < int(_dialogsClosedTemporarily_pageSelector.size()); i++)
            dlgCont->openOrBringToFront(_dialogsClosedTemporarily_pageSelector[i]);
        _dialogsClosedTemporarily_pageSelector.clear();
        if (codeEditorContainer != nullptr)
            codeEditorContainer->showOrHideAll(true);
    }
    else
    { // We are NOT in the UI thread. We execute the command via the UI thread:
        SUIThreadCommand cmdIn;
        SUIThreadCommand cmdOut;
        cmdIn.cmdId = MAIN_WINDOW_PAGE_SELECTOR_DLG_REOPEN_MWUITHREADCMD;
        GuiApp::uiThread->executeCommandViaUiThread(&cmdIn, &cmdOut);
    }
}

void CMainWindow::closeTemporarilyDialogsForViewSelector()
{
    if (VThread::isUiThread())
    { // we are in the UI thread. We execute the command now:
        if (codeEditorContainer != nullptr)
            codeEditorContainer->showOrHideAll(false);
        _closeDialogTemporarilyIfOpened(SETTINGS_DLG, _dialogsClosedTemporarily_viewSelector);
        _closeDialogTemporarilyIfOpened(SIMULATION_DLG, _dialogsClosedTemporarily_viewSelector);
        _closeDialogTemporarilyIfOpened(ENVIRONMENT_DLG, _dialogsClosedTemporarily_viewSelector);
        _closeDialogTemporarilyIfOpened(COLLECTION_DLG, _dialogsClosedTemporarily_viewSelector);
        _closeDialogTemporarilyIfOpened(OBJECT_DLG, _dialogsClosedTemporarily_viewSelector);
        _closeDialogTemporarilyIfOpened(CALCULATION_DLG_OLD, _dialogsClosedTemporarily_viewSelector);
        _closeDialogTemporarilyIfOpened(TRANSLATION_ROTATION_DLG, _dialogsClosedTemporarily_viewSelector);
        _closeDialogTemporarilyIfOpened(BROWSER_DLG, _dialogsClosedTemporarily_viewSelector);

        dlgCont->close(COLOR_DLG);
        dlgCont->close(LIGHTMATERIAL_DLG);
        dlgCont->close(MATERIAL_DLG);
        dlgCont->close(FOG_DLG);
        dlgCont->close(TEXTURE_DLG);
    }
    else
    { // We are NOT in the UI thread. We execute the command via the UI thread:
        SUIThreadCommand cmdIn;
        SUIThreadCommand cmdOut;
        cmdIn.cmdId = MAIN_WINDOW_VIEW_SELECTOR_DLG_CLOSE_MWUITHREADCMD;
        GuiApp::uiThread->executeCommandViaUiThread(&cmdIn, &cmdOut);
    }
}

void CMainWindow::reopenTemporarilyClosedDialogsForViewSelector()
{
    if (VThread::isUiThread())
    { // we are in the UI thread. We execute the command now:
        for (int i = 0; i < int(_dialogsClosedTemporarily_viewSelector.size()); i++)
            dlgCont->openOrBringToFront(_dialogsClosedTemporarily_viewSelector[i]);
        _dialogsClosedTemporarily_viewSelector.clear();
        if (codeEditorContainer != nullptr)
            codeEditorContainer->showOrHideAll(true);
    }
    else
    { // We are NOT in the UI thread. We execute the command via the UI thread:
        SUIThreadCommand cmdIn;
        SUIThreadCommand cmdOut;
        cmdIn.cmdId = MAIN_WINDOW_VIEW_SELECTOR_DLG_REOPEN_MWUITHREADCMD;
        GuiApp::uiThread->executeCommandViaUiThread(&cmdIn, &cmdOut);
    }
}

void CMainWindow::reopenTemporarilyClosedNonEditModeDialogs()
{
    if (VThread::isUiThread())
    { // we are in the UI thread. We execute the command now:
        for (int i = 0; i < int(_dialogsClosedTemporarily_editModes.size()); i++)
            dlgCont->openOrBringToFront(_dialogsClosedTemporarily_editModes[i]);
        _dialogsClosedTemporarily_editModes.clear();
        if (codeEditorContainer != nullptr)
            codeEditorContainer->showOrHideAll(true);
    }
    else
    { // We are NOT in the UI thread. We execute the command via the UI thread:
        SUIThreadCommand cmdIn;
        SUIThreadCommand cmdOut;
        cmdIn.cmdId = MAIN_WINDOW_NON_EDIT_MODE_DLG_REOPEN_MWUITHREADCMD;
        GuiApp::uiThread->executeCommandViaUiThread(&cmdIn, &cmdOut);
    }
}

void CMainWindow::closeTemporarilyNonEditModeDialogs()
{
    if (VThread::isUiThread())
    { // we are in the UI thread. We execute the command now:
        if (codeEditorContainer != nullptr)
            codeEditorContainer->showOrHideAll(false);
        _closeDialogTemporarilyIfOpened(SETTINGS_DLG, _dialogsClosedTemporarily_editModes);
        _closeDialogTemporarilyIfOpened(SIMULATION_DLG, _dialogsClosedTemporarily_editModes);
        _closeDialogTemporarilyIfOpened(ENVIRONMENT_DLG, _dialogsClosedTemporarily_editModes);
        _closeDialogTemporarilyIfOpened(COLLECTION_DLG, _dialogsClosedTemporarily_editModes);
        _closeDialogTemporarilyIfOpened(OBJECT_DLG, _dialogsClosedTemporarily_editModes);
        _closeDialogTemporarilyIfOpened(CALCULATION_DLG_OLD, _dialogsClosedTemporarily_editModes);
        _closeDialogTemporarilyIfOpened(BROWSER_DLG, _dialogsClosedTemporarily_editModes);

        dlgCont->close(COLOR_DLG);
        dlgCont->close(LIGHTMATERIAL_DLG);
        dlgCont->close(MATERIAL_DLG);
        dlgCont->close(FOG_DLG);
        dlgCont->close(TEXTURE_DLG);
    }
    else
    { // We are NOT in the UI thread. We execute the command via the UI thread:
        SUIThreadCommand cmdIn;
        SUIThreadCommand cmdOut;
        cmdIn.cmdId = MAIN_WINDOW_NON_EDIT_MODE_DLG_CLOSE_MWUITHREADCMD;
        GuiApp::uiThread->executeCommandViaUiThread(&cmdIn, &cmdOut);
    }
}

void CMainWindow::openOrBringDlgToFront(int dlgId)
{
    TRACE_INTERNAL;
    if (VThread::isUiThread())
    { // we are in the UI thread. We execute the command now:
        dlgCont->openOrBringToFront(dlgId);
    }
    else
    { // We are NOT in the UI thread. We execute the command via the UI thread:
        SUIThreadCommand cmdIn;
        SUIThreadCommand cmdOut;
        cmdIn.cmdId = MAIN_WINDOW_OPEN_DLG_OR_BRING_TO_FRONT_MWUITHREADCMD;
        cmdIn.intParams.push_back(dlgId);
        GuiApp::uiThread->executeCommandViaUiThread(&cmdIn, &cmdOut);
    }
}

void CMainWindow::closeDlg(int dlgId)
{
    TRACE_INTERNAL;
    if (VThread::isUiThread())
    { // we are in the UI thread. We execute the command now:
        dlgCont->close(dlgId);
    }
    else
    { // We are NOT in the UI thread. We execute the command via the UI thread:
        SUIThreadCommand cmdIn;
        SUIThreadCommand cmdOut;
        cmdIn.cmdId = MAIN_WINDOW_CLOSE_DLG_MWUITHREADCMD;
        cmdIn.intParams.push_back(dlgId);
        GuiApp::uiThread->executeCommandViaUiThread(&cmdIn, &cmdOut);
    }
}

void CMainWindow::activateMainWindow()
{
    TRACE_INTERNAL;
    if (VThread::isUiThread())
    { // we are in the UI thread. We execute the command now:
        activateWindow();
    }
    else
    { // We are NOT in the UI thread. We execute the command via the UI thread:
        SUIThreadCommand cmdIn;
        SUIThreadCommand cmdOut;
        cmdIn.cmdId = MAIN_WINDOW_ACTIVATE_MWUITHREADCMD;
        GuiApp::uiThread->executeCommandViaUiThread(&cmdIn, &cmdOut);
    }
}

void CMainWindow::executeCommand(SUIThreadCommand* cmdIn, SUIThreadCommand* cmdOut)
{
    if (cmdIn->cmdId == MAIN_WINDOW_NON_EDIT_MODE_DLG_CLOSE_MWUITHREADCMD)
        closeTemporarilyNonEditModeDialogs();
    if (cmdIn->cmdId == MAIN_WINDOW_NON_EDIT_MODE_DLG_REOPEN_MWUITHREADCMD)
        reopenTemporarilyClosedNonEditModeDialogs();
    if (cmdIn->cmdId == MAIN_WINDOW_VIEW_SELECTOR_DLG_CLOSE_MWUITHREADCMD)
        closeTemporarilyDialogsForViewSelector();
    if (cmdIn->cmdId == MAIN_WINDOW_VIEW_SELECTOR_DLG_REOPEN_MWUITHREADCMD)
        reopenTemporarilyClosedDialogsForViewSelector();
    if (cmdIn->cmdId == MAIN_WINDOW_PAGE_SELECTOR_DLG_CLOSE_MWUITHREADCMD)
        closeTemporarilyDialogsForPageSelector();
    if (cmdIn->cmdId == MAIN_WINDOW_PAGE_SELECTOR_DLG_REOPEN_MWUITHREADCMD)
        reopenTemporarilyClosedDialogsForPageSelector();
    if (cmdIn->cmdId == MAIN_WINDOW_SET_FULLSCREEN_MWTHREADCMD)
        setFullScreen(cmdIn->boolParams[0]);
    if (cmdIn->cmdId == MAIN_WINDOW_ACTIVATE_MWUITHREADCMD)
        activateMainWindow();
    if (cmdIn->cmdId == MAIN_WINDOW_CLOSE_DLG_MWUITHREADCMD)
        closeDlg(cmdIn->intParams[0]);
    if (cmdIn->cmdId == MAIN_WINDOW_OPEN_DLG_OR_BRING_TO_FRONT_MWUITHREADCMD)
        openOrBringDlgToFront(cmdIn->intParams[0]);
}
