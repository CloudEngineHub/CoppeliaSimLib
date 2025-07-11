#include <simInternal.h>
#include <dlgCont.h>
#include <global.h>
#include <oglSurface.h>
#include <app.h>
#include <auxLibVideo.h>
#include <simStrings.h>
#include <qdlgobjectdialogcontainer.h>
#include <qdlgshapeeditioncontainer.h>
#include <sceneObjectOperations.h>
#include <qdlgopenglsettings.h>
#include <simFlavor.h>
#ifdef SIM_WITH_GUI
#include <guiApp.h>
#endif

CDlgCont::CDlgCont(QWidget* pWindow)
{
    _destroyingContainerNow = false;
    initialize(pWindow);
}

CDlgCont::~CDlgCont()
{
    killAllDialogs();
}

void CDlgCont::initialize(QWidget* pWindow)
{
    if (dialogs.size() != 0)
        return; // Already initialized!
    parentWindow = pWindow;

    dialogs.push_back(new CToolDlgWrapper(DETECTION_VOLUME_DLG, 0));
    dialogs.push_back(new CToolDlgWrapper(SHAPE_DYN_DLG, 0));
    dialogs.push_back(new CToolDlgWrapper(SHAPE_EDITION_DLG, 0));
    dialogs.push_back(new CToolDlgWrapper(OBJECT_DLG, 0));
    dialogs.push_back(new CToolDlgWrapper(CALCULATION_DLG_OLD, 0));
    dialogs.push_back(new CToolDlgWrapper(JOINT_DYN_DLG, 0));
    dialogs.push_back(new CToolDlgWrapper(TRANSLATION_ROTATION_DLG, 0));
    dialogs.push_back(new CToolDlgWrapper(PATH_EDITION_DLG, 0));
    dialogs.push_back(new CToolDlgWrapper(MULTISHAPE_EDITION_DLG, 0));
    dialogs.push_back(new CToolDlgWrapper(GENERAL_PROPERTIES_DLG, 0));
    dialogs.push_back(new CToolDlgWrapper(SHAPE_DLG, 0));
    dialogs.push_back(new CToolDlgWrapper(JOINT_DLG, 0));
    dialogs.push_back(new CToolDlgWrapper(CAMERA_DLG, 0));
    dialogs.push_back(new CToolDlgWrapper(LIGHT_DLG, 0));
    dialogs.push_back(new CToolDlgWrapper(MIRROR_DLG, 0));
    dialogs.push_back(new CToolDlgWrapper(PROXIMITY_SENSOR_DLG, 0));
    dialogs.push_back(new CToolDlgWrapper(VISION_SENSOR_DLG, 0));
    dialogs.push_back(new CToolDlgWrapper(MILL_DLG_OLD, 0));
    dialogs.push_back(new CToolDlgWrapper(FORCE_SENSOR_DLG, 0));
    dialogs.push_back(new CToolDlgWrapper(GRAPH_DLG, 0));
    dialogs.push_back(new CToolDlgWrapper(SETTINGS_DLG, 0));
    dialogs.push_back(new CToolDlgWrapper(COLLECTION_DLG, 0));
    dialogs.push_back(new CToolDlgWrapper(ENVIRONMENT_DLG, 0));
    dialogs.push_back(new CToolDlgWrapper(COLLISION_DLG, 0));
    dialogs.push_back(new CToolDlgWrapper(DISTANCE_DLG, 0));
    dialogs.push_back(new CToolDlgWrapper(IK_DLG, 0));
    dialogs.push_back(new CToolDlgWrapper(OLD_LUA_SCRIPT_DLG, 0));
    dialogs.push_back(new CToolDlgWrapper(DUMMY_DLG, 0));
    dialogs.push_back(new CToolDlgWrapper(SCRIPT_DLG, 0));
    dialogs.push_back(new CToolDlgWrapper(LAYERS_DLG, 0));
    dialogs.push_back(new CToolDlgWrapper(DYNAMICS_DLG, 0));
    dialogs.push_back(new CToolDlgWrapper(PATH_DLG, 0));
    dialogs.push_back(new CToolDlgWrapper(SIMULATION_DLG, 0));
    dialogs.push_back(new CToolDlgWrapper(FOG_DLG, 0));
    dialogs.push_back(new CToolDlgWrapper(MATERIAL_DLG, 0));
    dialogs.push_back(new CToolDlgWrapper(LIGHTMATERIAL_DLG, 0));
    dialogs.push_back(new CToolDlgWrapper(COLOR_DLG, 0));
    dialogs.push_back(new CToolDlgWrapper(TEXTURE_DLG, 0));
    dialogs.push_back(new CToolDlgWrapper(GEOMETRY_DLG, 0));
    dialogs.push_back(new CToolDlgWrapper(GRAPH2DAND3DCURVES_DLG, 0));
    dialogs.push_back(new CToolDlgWrapper(IKELEMENT_DLG, 0));
    dialogs.push_back(new CToolDlgWrapper(PATH_SHAPING_DLG, 0));
    dialogs.push_back(new CToolDlgWrapper(AVI_RECORDER_DLG, 0));
}

void CDlgCont::refresh()
{
    if (!_destroyingContainerNow)
    {
        for (size_t i = 0; i < dialogs.size(); i++)
            dialogs[i]->refresh();
    }
}

void CDlgCont::callDialogFunction(const SUIThreadCommand* cmdIn, SUIThreadCommand* cmdOut)
{
    if ((!_destroyingContainerNow) && (cmdIn != nullptr))
    {
        for (size_t i = 0; i < dialogs.size(); i++)
            dialogs[i]->dialogCallbackFunc(cmdIn, cmdOut);
    }
}

void CDlgCont::destroyWhatNeedsDestruction()
{
    if (!_destroyingContainerNow)
    {
        for (size_t i = 0; i < dialogs.size(); i++)
            dialogs[i]->destroyIfDestructionNeeded();
    }
}

void CDlgCont::visibleInstanceAboutToSwitch()
{
    if (!_destroyingContainerNow)
    {
        for (size_t i = 0; i < dialogs.size(); i++)
            dialogs[i]->visibleInstanceAboutToSwitch();
    }
}

void CDlgCont::showDialogsButDontOpenThem()
{
    if (!_destroyingContainerNow)
    {
        for (size_t i = 0; i < dialogs.size(); i++)
            dialogs[i]->showDialogButDontOpenIt();
    }
}

void CDlgCont::hideDialogsButDontCloseThem()
{
    if (!_destroyingContainerNow)
    {
        for (size_t i = 0; i < dialogs.size(); i++)
            dialogs[i]->hideDialogButDontCloseIt();
    }
}

bool CDlgCont::openOrBringToFront(int dlgID)
{
    if (!_destroyingContainerNow)
    {
        if (dlgID == HIERARCHY_DLG)
            App::setHierarchyEnabled(true);
        else if (dlgID == BROWSER_DLG)
            GuiApp::setBrowserEnabled(true);
        else
        { // Here we check if we can open the dialog: (check also "toggle" function!)
            if ((GuiApp::operationalUIParts & sim_gui_dialogs) == 0)
                return (false);
            if (CSimFlavor::getIntVal(2) == 0)
            {
                if ((dlgID != TRANSLATION_ROTATION_DLG) && (dlgID != SETTINGS_DLG) && (dlgID != AVI_RECORDER_DLG))
                    return false;
            }

            CToolDlgWrapper* it = _getDialogWrapper(dlgID);
            if (it != nullptr)
                it->setVisible(true, parentWindow);
        }
        GuiApp::setToolbarRefreshFlag();
        return (true);
    }
    return (false);
}

void CDlgCont::close(int dlgID)
{
    if (!_destroyingContainerNow)
    {
        if (dlgID == HIERARCHY_DLG)
            App::setHierarchyEnabled(false);
        else if (dlgID == BROWSER_DLG)
            GuiApp::setBrowserEnabled(false);
        else
        {
            CToolDlgWrapper* it = _getDialogWrapper(dlgID);
            if (it != nullptr)
                it->setVisible(false, parentWindow);
        }
        GuiApp::setToolbarRefreshFlag();
    }
}

bool CDlgCont::toggle(int dlgID)
{
    if (!_destroyingContainerNow)
    {
        if (dlgID == HIERARCHY_DLG)
            App::setHierarchyEnabled(!App::getHierarchyEnabled());
        else if (dlgID == BROWSER_DLG)
            GuiApp::setBrowserEnabled(!GuiApp::getBrowserEnabled());
        else
        {
            // Here we check if we can open the dialog: (check also "openOrBringToFront" function!)
            if ((GuiApp::operationalUIParts & sim_gui_dialogs) == 0)
                return (false);
            CToolDlgWrapper* it = _getDialogWrapper(dlgID);
            if (it != nullptr)
                it->setVisible(!it->getVisible(), parentWindow);
        }
        GuiApp::setToolbarRefreshFlag();
        return (true);
    }
    return (false);
}

CToolDlgWrapper* CDlgCont::_getDialogWrapper(int dlgID)
{
    if (!_destroyingContainerNow)
    {
        for (size_t i = 0; i < dialogs.size(); i++)
        {
            if (dialogs[i]->getDialogType() == dlgID)
                return (dialogs[i]);
        }
    }
    return (nullptr);
}

VDialog* CDlgCont::getDialog(int dlgID)
{
    if (!_destroyingContainerNow)
    {
        for (int i = 0; i < int(dialogs.size()); i++)
        {
            if (dialogs[i]->getDialogType() == dlgID)
                return (dialogs[i]->getDialog());
        }
    }
    return (nullptr);
}

bool CDlgCont::isVisible(int dlgID)
{
    if (!_destroyingContainerNow)
    {
        if (dlgID == HIERARCHY_DLG)
            return (App::getHierarchyEnabled());
        else if (dlgID == BROWSER_DLG)
            return (GuiApp::getBrowserEnabled());
        else
        {
            CToolDlgWrapper* it = _getDialogWrapper(dlgID);
            if (it != nullptr)
                return (it->getVisible());
        }
    }
    return (false);
}

void CDlgCont::killAllDialogs()
{
    _destroyingContainerNow = true;
    for (int i = 0; i < int(dialogs.size()); i++)
        delete dialogs[i];
    dialogs.clear();
}

void CDlgCont::getWindowPos(int dlgID, int pos[2], bool& visible)
{
    if (!_destroyingContainerNow)
    {
        if (dlgID == HIERARCHY_DLG)
        {
            pos[0] = GuiApp::mainWindow->oglSurface->getHierarchyWidth();
            pos[1] = 0;
            visible = App::getHierarchyEnabled();
        }
        else if (dlgID == BROWSER_DLG)
        {
        }
        else
        {
            CToolDlgWrapper* it = _getDialogWrapper(dlgID);
            if (it != nullptr)
            {
                it->getPosition(pos);
                visible = it->getVisible();
            }
        }
    }
}

void CDlgCont::setWindowPos(int dlgID, int pos[2], bool visible)
{
    if (!_destroyingContainerNow)
    {
        if (dlgID == HIERARCHY_DLG)
        {
            GuiApp::mainWindow->oglSurface->setHierarchyWidth(pos[0]);
            App::setHierarchyEnabled(visible);
        }
        else if (dlgID == BROWSER_DLG)
        {
        }
        else
        {
            CToolDlgWrapper* it = _getDialogWrapper(dlgID);
            if (it != nullptr)
            {
                it->setPosition(pos[0], pos[1]);
                it->setVisible(visible, parentWindow);
            }
        }
    }
}

void CDlgCont::keyPress(int key)
{
    if (key == CTRL_D_KEY)
        processCommand(OPEN_OBJECT_DLG_OBJECT_SPECIFIC_PART_CMD);
    if (key == CTRL_G_KEY)
        processCommand(OPEN_CALCULATION_DLG_CMD_OLD);
}

void CDlgCont::addMenu(VMenu* menu)
{
    bool noShapePathEditModeNoSelector = true;
    if ((GuiApp::getEditModeType() & SHAPE_EDIT_MODE) || (GuiApp::getEditModeType() == PATH_EDIT_MODE_OLD))
        noShapePathEditModeNoSelector = false;
    if (GuiApp::mainWindow->oglSurface->isPageSelectionActive())
        noShapePathEditModeNoSelector = false;

    if ((CSimFlavor::getIntVal(2) == -1) || (CSimFlavor::getIntVal(2) == 1) || (CSimFlavor::getIntVal(2) == 2))
    {
        menu->appendMenuItem(GuiApp::mainWindow->getObjPropToggleViaGuiEnabled() && noShapePathEditModeNoSelector, GuiApp::mainWindow->dlgCont->isVisible(OBJECT_DLG), TOGGLE_OBJECT_DLG_CMD, IDSN_OBJECT_PROPERTIES_MENU_ITEM, true);
        if (App::userSettings->showOldDlgs)
            menu->appendMenuItem(GuiApp::mainWindow->getCalcModulesToggleViaGuiEnabled_OLD() && noShapePathEditModeNoSelector, GuiApp::mainWindow->dlgCont->isVisible(CALCULATION_DLG_OLD), TOGGLE_CALCULATION_DLG_CMD_OLD, "Old dialogs", true);
        menu->appendMenuSeparator();

        if (App::userSettings->showOldDlgs)
            menu->appendMenuItem(noShapePathEditModeNoSelector, GuiApp::mainWindow->dlgCont->isVisible(COLLECTION_DLG), TOGGLE_COLLECTION_DLG_CMD, IDSN_COLLECTIONS, true);
        menu->appendMenuItem(noShapePathEditModeNoSelector, GuiApp::mainWindow->dlgCont->isVisible(ENVIRONMENT_DLG), TOGGLE_ENVIRONMENT_DLG_CMD, IDSN_ENVIRONMENT, true);
    }

    menu->appendMenuItem(noShapePathEditModeNoSelector && GuiApp::mainWindow->getBrowserToggleViaGuiEnabled(), GuiApp::getBrowserEnabled(), TOGGLE_BROWSER_DLG_CMD, IDSN_MODEL_BROWSER, true);
    menu->appendMenuItem(GuiApp::mainWindow->getHierarchyToggleViaGuiEnabled(), App::getHierarchyEnabled(), TOGGLE_HIERARCHY_DLG_CMD, IDSN_SCENE_HIERARCHY, true);

    if ((CSimFlavor::getIntVal(2) == -1) || (CSimFlavor::getIntVal(2) == 1) || (CSimFlavor::getIntVal(2) == 2))
    {
        menu->appendMenuItem(true, GuiApp::mainWindow->dlgCont->isVisible(LAYERS_DLG), TOGGLE_LAYERS_DLG_CMD, IDS_LAYERS, true);
    }

    menu->appendMenuItem(CAuxLibVideo::video_recorderGetEncoderString != nullptr, GuiApp::mainWindow->dlgCont->isVisible(AVI_RECORDER_DLG), TOGGLE_AVI_RECORDER_DLG_CMD, IDSN_AVI_RECORDER, true);
    menu->appendMenuItem(noShapePathEditModeNoSelector, GuiApp::mainWindow->dlgCont->isVisible(SETTINGS_DLG), TOGGLE_SETTINGS_DLG_CMD, IDSN_USER_SETTINGS, true);

    if ((CSimFlavor::getIntVal(2) == -1) || (CSimFlavor::getIntVal(2) == 1) || (CSimFlavor::getIntVal(2) == 2))
    {
        menu->appendMenuSeparator();
        menu->appendMenuItem(true, GuiApp::getShowInertias(), TOGGLE_SHOW_INERTIA_DLG_CMD, "Visualize inertias", true);
        int v = 0;
        CALL_C_API_CLEAR_ERRORS(simGetIntProperty, sim_handle_app, "signal.simIK.debug_world", &v);
        CApiErrors::getAndClearLastError();
        menu->appendMenuItem(true, v & 1, TOGGLE_SHOW_IKWORLDS_DLG_CMD, "Visualize IK worlds", true);
        menu->appendMenuItem(true, v & 2, TOGGLE_SHOW_IKWORLDJACOBIANS_DLG_CMD, "Display IK world Jacobians", true);
    }
}

bool CDlgCont::processCommand(int commandID)
{ // Return value is true if the command belonged to dlg menu and was executed

    if (!VThread::isUiThread())
    { // we are NOT in the UI thread.
        // We execute the other commands via the UI thread:
        SUIThreadCommand cmdIn;
        SUIThreadCommand cmdOut;
        cmdIn.cmdId = OPEN_OR_CLOSE_UITHREADCMD;
        cmdIn.intParams.push_back(commandID);
        GuiApp::uiThread->executeCommandViaUiThread(&cmdIn, &cmdOut);
    }
    else
    { // We are in the UI thread.
        if (commandID == OPEN_MULTISHAPE_EDITION_DLG_CMD)
        {
            openOrBringToFront(MULTISHAPE_EDITION_DLG);
            return (true);
        }
        if (commandID == CLOSE_MULTISHAPE_EDITION_DLG_CMD)
        {
            close(MULTISHAPE_EDITION_DLG);
            return (true);
        }
        if (commandID == OPEN_GRAPH_DLG_CMD)
        {
            openOrBringToFront(GRAPH_DLG);
            return (true);
        }
        if (commandID == OPEN_CAMERA_DLG_CMD)
        {
            openOrBringToFront(CAMERA_DLG);
            return (true);
        }
        if (commandID == OPEN_LIGHT_DLG_CMD)
        {
            openOrBringToFront(LIGHT_DLG);
            return (true);
        }
        if (commandID == OPEN_MIRROR_DLG_CMD)
        {
            openOrBringToFront(MIRROR_DLG);
            return (true);
        }
        if (commandID == OPEN_SHAPE_DLG_CMD)
        {
            openOrBringToFront(SHAPE_DLG);
            return (true);
        }
        if (commandID == OPEN_PROXIMITY_SENSOR_DLG_CMD)
        {
            openOrBringToFront(PROXIMITY_SENSOR_DLG);
            return (true);
        }
        if (commandID == OPEN_VISION_SENSOR_DLG_CMD)
        {
            openOrBringToFront(VISION_SENSOR_DLG);
            return (true);
        }
        if (commandID == OPEN_MILL_DLG_CMD)
        {
            openOrBringToFront(MILL_DLG_OLD);
            return (true);
        }
        if (commandID == OPEN_OBJECT_DLG_CMD)
        {
            openOrBringToFront(OBJECT_DLG);
            return (true);
        }
        if (commandID == OPEN_SHAPE_EDITION_DLG_CMD)
        {
            openOrBringToFront(SHAPE_EDITION_DLG);
            return (true);
        }
        if (commandID == CLOSE_SHAPE_EDITION_DLG_CMD)
        {
            close(SHAPE_EDITION_DLG);
            return (true);
        }
        if (commandID == OPEN_PATH_EDITION_DLG_CMD)
        {
            openOrBringToFront(PATH_EDITION_DLG);
            return (true);
        }
        if (commandID == CLOSE_PATH_EDITION_DLG_CMD)
        {
            close(PATH_EDITION_DLG);
            return (true);
        }
        if (commandID == OPEN_OBJECT_DLG_OBJECT_SPECIFIC_PART_CMD)
        {
            if (GuiApp::getEditModeType() == NO_EDIT_MODE)
            {
                openOrBringToFront(OBJECT_DLG);
                VDialog* dlg = getDialog(OBJECT_DLG);
                if (dlg != nullptr)
                {
                    ((CQDlgObjectDialogContainer*)dlg)->desiredPage = 0;
                    ((CQDlgObjectDialogContainer*)dlg)->refresh();
                }
            }
            return (true);
        }
        if ((commandID == OPEN_SHAPE_EDIT_MODE_TRIANGLE_PART_CMD) ||
            (commandID == OPEN_SHAPE_EDIT_MODE_VERTEX_PART_CMD) || (commandID == OPEN_SHAPE_EDIT_MODE_EDGE_PART_CMD))
        {
            openOrBringToFront(SHAPE_EDITION_DLG);
            VDialog* dlg = getDialog(SHAPE_EDITION_DLG);
            if (dlg != nullptr)
            {
                if (commandID == OPEN_SHAPE_EDIT_MODE_TRIANGLE_PART_CMD)
                    ((CQDlgShapeEditionContainer*)dlg)->desiredPage = 0;
                if (commandID == OPEN_SHAPE_EDIT_MODE_VERTEX_PART_CMD)
                    ((CQDlgShapeEditionContainer*)dlg)->desiredPage = 1;
                if (commandID == OPEN_SHAPE_EDIT_MODE_EDGE_PART_CMD)
                    ((CQDlgShapeEditionContainer*)dlg)->desiredPage = 2;
                ((CQDlgShapeEditionContainer*)dlg)->refresh();
            }
            return (true);
        }
        if (commandID == OPEN_FORCE_SENSOR_DLG_CMD)
        {
            openOrBringToFront(FORCE_SENSOR_DLG);
            return (true);
        }
        if (commandID == OPEN_DUMMY_DLG_CMD)
        {
            openOrBringToFront(DUMMY_DLG);
            return (true);
        }
        if (commandID == OPEN_SCRIPT_DLG_CMD)
        {
            openOrBringToFront(SCRIPT_DLG);
            return (true);
        }
        if (commandID == OPEN_JOINT_DLG_CMD)
        {
            openOrBringToFront(JOINT_DLG);
            return (true);
        }
        if (commandID == OPEN_PATH_DLG_CMD)
        {
            openOrBringToFront(PATH_DLG);
            return (true);
        }
        if (commandID == OPEN_ENVIRONMENT_DLG_CMD)
        {
            openOrBringToFront(ENVIRONMENT_DLG);
            return (true);
        }
        if (commandID == OPEN_FOG_DLG_CMD)
        {
            openOrBringToFront(FOG_DLG);
            return (true);
        }
        if (commandID == TOGGLE_GENERAL_PROPERTIES_DLG_CMD)
        {
            toggle(GENERAL_PROPERTIES_DLG);
            return (true);
        }
        if (commandID == TOGGLE_GRAPH_DLG_CMD)
        {
            toggle(GRAPH_DLG);
            return (true);
        }
        if (commandID == TOGGLE_COLLECTION_DLG_CMD)
        {
            toggle(COLLECTION_DLG);
            return (true);
        }
        if (commandID == TOGGLE_CAMERA_DLG_CMD)
        {
            toggle(CAMERA_DLG);
            return (true);
        }
        if (commandID == TOGGLE_LIGHT_DLG_CMD)
        {
            toggle(LIGHT_DLG);
            return (true);
        }
        if (commandID == TOGGLE_MIRROR_DLG_CMD)
        {
            toggle(MIRROR_DLG);
            return (true);
        }
        if (commandID == TOGGLE_COLLISION_DLG_CMD)
        {
            toggle(COLLISION_DLG);
            return (true);
        }
        if (commandID == TOGGLE_SHAPE_DLG_CMD)
        {
            toggle(SHAPE_DLG);
            return (true);
        }
        if (commandID == TOGGLE_PROXIMITY_SENSOR_DLG_CMD)
        {
            toggle(PROXIMITY_SENSOR_DLG);
            return (true);
        }
        if (commandID == TOGGLE_VISION_SENSOR_DLG_CMD)
        {
            toggle(VISION_SENSOR_DLG);
            return (true);
        }
        if (commandID == TOGGLE_MILL_DLG_CMD)
        {
            toggle(MILL_DLG_OLD);
            return (true);
        }
        if (commandID == TOGGLE_FORCE_SENSOR_DLG_CMD)
        {
            toggle(FORCE_SENSOR_DLG);
            return (true);
        }
        if (commandID == TOGGLE_OLD_LUA_SCRIPT_DLG_CMD)
        {
            toggle(OLD_LUA_SCRIPT_DLG);
            return (true);
        }
        if (commandID == TOGGLE_SETTINGS_DLG_CMD)
        {
            toggle(SETTINGS_DLG);
            return (true);
        }
        if (commandID == TOGGLE_DUMMY_DLG_CMD)
        {
            toggle(DUMMY_DLG);
            return (true);
        }
        if (commandID == TOGGLE_SCRIPT_DLG_CMD)
        {
            toggle(SCRIPT_DLG);
            return (true);
        }
        if (commandID == TOGGLE_DISTANCE_DLG_CMD)
        {
            toggle(DISTANCE_DLG);
            return (true);
        }
        if (commandID == TOGGLE_JOINT_DLG_CMD)
        {
            toggle(JOINT_DLG);
            return (true);
        }
        if (commandID == TOGGLE_ENVIRONMENT_DLG_CMD)
        {
            toggle(ENVIRONMENT_DLG);
            return (true);
        }
        if (commandID == TOGGLE_IK_DLG_CMD)
        {
            toggle(IK_DLG);
            return (true);
        }
        if (commandID == TOGGLE_DYNAMICS_DLG_CMD)
        {
            toggle(DYNAMICS_DLG);
            return (true);
        }
        if (commandID == TOGGLE_SIMULATION_DLG_CMD)
        {
            toggle(SIMULATION_DLG);
            return (true);
        }
        if (commandID == TOGGLE_AVI_RECORDER_DLG_CMD)
        {
            toggle(AVI_RECORDER_DLG);
            return (true);
        }
        if (commandID == TOGGLE_HIERARCHY_DLG_CMD)
        {
            toggle(HIERARCHY_DLG);
            return (true);
        }
        if (commandID == OPEN_HIERARCHY_DLG_CMD)
        {
            openOrBringToFront(HIERARCHY_DLG);
            return (true);
        }
        if (commandID == CLOSE_HIERARCHY_DLG_CMD)
        {
            close(HIERARCHY_DLG);
            return (true);
        }
        if (commandID == TOGGLE_BROWSER_DLG_CMD)
        {
            toggle(BROWSER_DLG);
            return (true);
        }
        if (commandID == TOGGLE_LAYERS_DLG_CMD)
        {
            toggle(LAYERS_DLG);
            return (true);
        }
        if (commandID == TOGGLE_DYNAMICS_DLG_CMD)
        {
            toggle(DYNAMICS_DLG);
            return (true);
        }
        if (commandID == TOGGLE_PATH_DLG_CMD)
        {
            toggle(PATH_DLG);
            return (true);
        }
        if (commandID == TOGGLE_OBJECT_DLG_CMD)
        {
            toggle(OBJECT_DLG);
            return (true);
        }
        if (commandID == TOGGLE_CALCULATION_DLG_CMD_OLD)
        {
            toggle(CALCULATION_DLG_OLD);
            return (true);
        }
        if (commandID == OPEN_CALCULATION_DLG_CMD_OLD)
        {
            if (GuiApp::getEditModeType() == NO_EDIT_MODE)
                openOrBringToFront(CALCULATION_DLG_OLD);
            return (true);
        }
        if (commandID == TOGGLE_SHOW_INERTIA_DLG_CMD)
        {
            GuiApp::setShowInertias(!GuiApp::getShowInertias());
            if (GuiApp::getShowInertias())
                App::logMsg(sim_verbosity_msgs, "Visualizing inertias");
            else
                App::logMsg(sim_verbosity_msgs, "Hiding inertias");
            return (true);
        }
        if (commandID == TOGGLE_SHOW_IKWORLDS_DLG_CMD)
        {
            int v = 0;
            CALL_C_API_CLEAR_ERRORS(simGetIntProperty, sim_handle_app, "signal.simIK.debug_world", &v);
            if (v & 1)
            {
                v = v - 1;
                App::logMsg(sim_verbosity_msgs, "Hiding IK worlds");
            }
            else
            {
                v = v | 1;
                App::logMsg(sim_verbosity_msgs, "Visualizing IK worlds");
            }
            CALL_C_API_CLEAR_ERRORS(simSetIntProperty, sim_handle_app, "signal.simIK.debug_world", v);
            return (true);
        }
        if (commandID == TOGGLE_SHOW_IKWORLDJACOBIANS_DLG_CMD)
        {
            int v = 0;
            CALL_C_API_CLEAR_ERRORS(simGetIntProperty, sim_handle_app, "signal.simIK.debug_world", &v);
            if (v & 2)
            {
                v = v - 2;
                App::logMsg(sim_verbosity_msgs, "Hiding IK world Jacobians");
            }
            else
            {
                v = v | 2;
                App::logMsg(sim_verbosity_msgs, "Displaying IK world Jacobians");
            }
            CALL_C_API_CLEAR_ERRORS(simSetIntProperty, sim_handle_app, "signal.simIK.debug_world", v);
            return (true);
        }
    }
    return (false);
}
