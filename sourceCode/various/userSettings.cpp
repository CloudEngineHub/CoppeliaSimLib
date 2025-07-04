#include <confReaderAndWriter.h>
#include <simInternal.h>
#include <userSettings.h>
#include <global.h>
#include <tt.h>
#include <vVarious.h>
#include <app.h>
#include <simFlavor.h>
#ifdef SIM_WITH_GUI
#include <vDialog.h>
#include <guiApp.h>
#endif

#define USER_SETTINGS_FILENAME "usrset.txt"

#define _USR_ANTIALIASING "antialiasing"
#define _USR_DISPLAY_WORLD_REF "displayWorldRef"
#define _USR_USE_GLFINISH "useGlFinish"
#define _USR_USE_GLFINISH_VISION_SENSORS "useGlFinish_visionSensors"
#define _USR_OGL_COMPATIBILITY_TWEAK_1 "oglCompatibilityTweak1"

#define _USR_STEREO_DIST "stereoDist"
#define _USR_VSYNC "vsync"
#define _USR_IDENTICAL_VERTICES_TOLERANCE "identicalVertexTolerance"
#define _USR_DYNAMIC_ACTIVITY_RANGE "dynamicActivityRange"
#define _USR_FREE_SERVER_PORT_START "freeServerPortStart"
#define _USR_FREE_SERVER_PORT_RANGE "freeServerPortRange"
#define _USR_GUI_FONT_SIZE_WIN "guiFontSize_Win"
#define _USR_GUI_FONT_SIZE_MAC "guiFontSize_Mac"
#define _USR_GUI_FONT_SIZE_LINUX "guiFontSize_Linux"
#define _USR_TRANSLATION_STEP_SIZE "objectTranslationStepSize"
#define _USR_ROTATION_STEP_SIZE "objectRotationStepSize"
#define _USR_COMPRESS_FILES "compressFiles"
#define _USR_TRIANGLE_COUNT_IN_OBB "triCountInOBB"
#define _USR_UNDO_REDO_ENABLED "undoRedoEnabled"
#define _USR_UNDO_REDO_PARTIAL_WITH_CAMERAS "undoRedoOnlyPartialWithCameras"
#define _USR_UNDO_REDO_LEVEL_COUNT "undoRedoLevelCount"
#define _USR_RUN_CUSTOMIZATION_SCRIPTS "runCustomizationScripts"
#define _USR_RUN_ADDONS "runAddOns"

#define _USR_TEST1 "test1"
#define _USR_MAC_CHILD_DIALOG_TYPE "macChildDialogType"
#define _USR_DESKTOP_RECORDING_INDEX "desktopRecordingIndex"
#define _USR_DESKTOP_RECORDING_WIDTH "desktopRecordingWidth"
#define _USR_EXTERNAL_SCRIPT_EDITOR "externalScriptEditor"
#define _USR_XML_EXPORT_SPLIT_SIZE "xmlExportSplitSize"
#define _USR_XML_EXPORT_KNOWN_FORMATS "xmlExportKnownFormats"

#define _USR_IDLE_FPS "idleFps"
#define _USR_UNDO_REDO_MAX_BUFFER_SIZE "undoRedoMaxBufferSize"
#define _USR_ALWAYS_SHOW_CONSOLE "alwaysShowConsole"
#define _USR_VERBOSITY "verbosity"
#define _USR_STATUSBAR_VERBOSITY "statusbarVerbosity"
#define _USR_DIALOG_VERBOSITY "dialogVerbosity"
#define _USR_LOG_FILTER "logFilter"
#define _USR_TIMESTAMP "timeStamp"
#define _USR_UNDECORATED_STATUSBAR_MSGS "undecoratedStatusbarMessages"
#define _USR_CONSOLE_MSGS_TO_FILE "consoleMsgsToFile"
#define _USR_CONSOLE_MSGS_FILE "consoleMsgsFile"
#define _USR_FORCE_BUG_FIX_REL_30002 "forceBugFix_rel30002"
#define _USR_STATUSBAR_INITIALLY_VISIBLE "statusbarInitiallyVisible"
#define _USR_MODELBROWSER_INITIALLY_VISIBLE "modelBrowserInitiallyVisible"
#define _USR_SCENEHIERARCHY_INITIALLY_VISIBLE "sceneHierarchyInitiallyVisible"
#define _USR_SCENEHIERARCHY_HIDDEN_DURING_SIMULATION "sceneHierarchyHiddenDuringSimulation"
#define _USR_AUTO_SAVE_DELAY "autoSaveDelay"
#define _USR_TIME_FOR_UNDO_REDO_TOO_LONG_WARNING "timeInMsForUndoRedoTooLongWarning"
#define _USR_MIDDLE_MOUSE_BUTTON_SWITCHES_MODES "middleMouseButtonSwitchesModes"
#define _USR_NAVIGATION_BACKWARD_COMPATIBILITY_MODE "navigationBackwardCompatibility"
#define _USR_COLOR_ADJUST_BACK_COMPATIBILITY "colorAdjust_backCompatibility"
#define _USR_SPECIFIC_GPU_TWEAK "specificGpuTweak"
#define _USR_DISABLED_OPENGL_BASED_CUSTOM_UI "disableOpenGlBasedCustomUi"
#define _USR_DISABLE_VISIBLE_EDGES "disableVisibleEdges"
#define _USR_SHOW_old_DLGS "showOldDlgs"
#define _USR_ENABLE_OLD_RENDERABLE "enableOldRenderableBehaviour"
#define _USR_BUGFIX1 "bugFix1"
#define _USR_READDELAY "readDelay"
#define _USR_WRITEDELAY "writeDelay"
#define _USR_USEBUFFERS "useBuffers"
#define _USR_SCRIPTCONVERSION "scriptConversion"
#define _USR_NOTIFY_DEPRECATED "notifyDeprecated"
#define _USR_ENABLE_old_MIRROR_OBJECTS "enableOldMirrorObjects"
#define _USR_ALLOW_old_EDU_RELEASE "allowOldEduRelease"
#define _USR_THREADED_SCRIPTS_GRACE_TIME "threadedScriptsStoppingGraceTime"

#define _USR_ABORT_SCRIPT_EXECUTION_BUTTON "abortScriptExecutionButton"
#define _USR_INIT_WINDOW_SIZE "initWindowSize"
#define _USR_INIT_WINDOW_POS "initWindowPos"
#define _USR_DARK_MODE "darkMode"
#define _USR_RENDERING_SURFACE_VERTICAL_SHIFT "renderingSurfaceVShift"
#define _USR_RENDERING_SURFACE_VERTICAL_RESIZE "renderingSurfaceVResize"
#define _USR_ADDITIONAL_LUA_PATH "additionalLuaPath"
#define _USR_ADDITIONAL_PYTHON_PATH "additionalPythonPath"
#define _USR_DEFAULT_PYTHON "defaultPython"
#define _USR_EXEC_UNSAFE "execUnsafe"
#define _USR_EXEC_UNSAFE_EXT "execUnsafeExt"

#define _USR_DIRECTORY_FOR_SCENES "defaultDirectoryForScenes"
#define _USR_DIRECTORY_FOR_MODELS "defaultDirectoryForModels"
#define _USR_DIRECTORY_FOR_IMPORTEXPORT "defaultDirectoryForImportExport"
#define _USR_DIRECTORY_FOR_MISC "defaultDirectoryForMiscFiles"

#define _USR_OFFSCREEN_CONTEXT_TYPE "offscreenContextType"
#define _USR_FBO_TYPE "fboType"
#define _USR_FORCE_FBO_VIA_EXT "forceFboViaExt"
#define _USR_VBO_OPERATION "vboOperation"
#define _USR_VBO_PERSISTENCE_IN_MS "vboPersistenceInMs"
#define _USR_HIGH_RES_DISPLAY "highResDisplay"
#define _USR_GUESSED_SCALING_FOR_2X_OPENGL "guessedDisplayScalingThresholdFor2xOpenGl"
#define _USR_OGL_SCALING "oglScaling"
#define _USR_GUI_SCALING "guiScaling"
#define _USR_NO_EDGES_WHEN_MOUSE_DOWN "noEdgesWhenMouseDownInCameraView"
#define _USR_NO_TEXTURES_WHEN_MOUSE_DOWN "noTexturesWhenMouseDownInCameraView"
#define _USR_NO_CUSTOM_UIS_WHEN_MOUSE_DOWN "noCustomUisWhenMouseDownInCameraView"
#define _USR_HIERARCHY_REFRESH_CNT "hierarchyRefreshCnt"

#define _USR_CODE_COLOR_BACKGROUND "codeColor_background"
#define _USR_CODE_COLOR_SELECTION "codeColor_selection"
#define _USR_CODE_COLOR_COMMENT "codeColor_comment"
#define _USR_CODE_COLOR_NUMBER "codeColor_number"
#define _USR_CODE_COLOR_STRING "codeColor_string"
#define _USR_CODE_COLOR_CHARACTER "codeColor_character"
#define _USR_CODE_COLOR_OPERATOR "codeColor_operator"
#define _USR_CODE_COLOR_PREPROCESSOR "codeColor_preprocessor"
#define _USR_CODE_COLOR_IDENTIFIER "codeColor_identifier"
#define _USR_CODE_COLOR_WORD "codeColor_word"
#define _USR_CODE_COLOR_WORD2 "codeColor_word2"
#define _USR_CODE_COLOR_WORD3 "codeColor_word3"
#define _USR_CODE_COLOR_WORD4 "codeColor_word4"

#define _USR_FILE_DIALOGS_NATIVE "fileDialogs"
#define _USR_MOUSE_WHEEL_ZOOM_FACTOR "mouseWheelZoomFactor"
#define _USR_PREFERRED_SANDBOX_LANG "preferredSandboxLang"

#define _USR_DO_NOT_WRITE_PERSISTENT_DATA "doNotWritePersistentData"
#define _USR_DO_NOT_SHOW_UPDATE_CHECK_MESSAGE "doNotShowUpdateCheckMessage"
#define _USR_DO_NOT_SHOW_PROGRESS_BARS "doNotShowProgressBars"
#define _USR_SUPPRESS_STARTUP_DIALOG "suppressStartupDialogs"
#define _USR_SUPPRESS_XML_OVERWRITE_MSG "suppressXmlOverwriteMsg"
#define _USR_ALLOW_SETTINGS_WRITE "allowSettingsWrite"
#define _USR_NO_VERSION_CHECK "noVersionCheck"

#define _USR_SCRIPT_EDITOR_FONT "scriptEditorFont"
#define _USR_SCRIPT_EDITOR_FONT_SIZE "scriptEditorFontSize"
#define _USR_SCRIPT_EDITOR_BOLDFONT "scriptEditorBoldFont"

#define _USR_CONNECTION_ADDRESS "conParam1"
#define _USR_CONNECTION_PORT "conParam2"

#define _USR_LICENSE_LITE "license_lite"
#define _USR_LICENSE_EDU "license_edu"
#define _USR_LICENSE_PRO "license_pro"
#define _USR_LICENSE "license"
#define _USR_LICENSE_ENDPOINT "licenseEndpoint"
#define _USR_FLOAT_LICENSE_ENABLED "floatingLicenseEnabled"
#define _USR_FLOAT_LICENSE_SERVER_ADDRESS "floatingLicenseServer"
#define _USR_FLOAT_LICENSE_SERVER_PORT "floatingLicensePort"
#define _USR_KEEP_DONGLE_OPEN "keepDongleOpen"

#define _USR_MEM "mem"

CUserSettings::CUserSettings()
{
    // Debugging section:
    // *****************************
    alwaysShowConsole = false;
    _overrideConsoleVerbosity = "default";
    _overrideStatusbarVerbosity = "default";
    _overrideDialogVerbosity = "default";
    _consoleLogFilter = "";
    undecoratedStatusbarMessages = false;
    timeStamp = false;

    // Rendering section:
    // *****************************
    _idleFps = 8;
    _idleFps_session = -1;
    offscreenContextType = -1; // default type
    fboType = -1;              // default type
    forceFboViaExt = false;    // default
    vboOperation = -1;         // default
    vboPersistenceInMs = 5000; // default
    oglCompatibilityTweak1 = false;
    useGlFinish = false;
    useGlFinish_visionSensors = false;
    vsync = 0;
    stereoDist = 0.0; // default, no stereo!

    // Visual section:
    // *****************************
    darkMode = false;
    initWindowSize[0] = 0; // fullscreen
    initWindowSize[1] = 0;
    initWindowPos[0] = 0;
    initWindowPos[1] = 0;
    renderingSurfaceVShift = 0;
    renderingSurfaceVResize = 0;
    scriptEditorFont = "";     // default
    scriptEditorFontSize = -1; // default
    scriptEditorBoldFont = false;

    displayWorldReference = true;
    antiAliasing = false;
    guiFontSize_Win = 13;   // 11-14 ok
    guiFontSize_Mac = -1;   // 10-13 ok
    guiFontSize_Linux = 13; // 11-14 ok, default is quite large
    statusbarInitiallyVisible = CSimFlavor::getBoolVal(10);
    modelBrowserInitiallyVisible = true;
    sceneHierarchyInitiallyVisible = true;
    sceneHierarchyHiddenDuringSimulation = false;

    highResDisplay = -1;
    guessedDisplayScalingThresholdFor2xOpenGl = 150;
    oglScaling = 1;
    guiScaling = 1.0;
    noEdgesWhenMouseDownInCameraView = false;
    noTexturesWhenMouseDownInCameraView = false;
    noCustomUisWhenMouseDownInCameraView = true;
    hierarchyRefreshCnt = 6;

    _setIntVector3(codeColor_background, 205, 205, 205);
    _setIntVector3(codeColor_selection, 128, 128, 255);
    _setIntVector3(codeColor_comment, 0, 140, 0);
    _setIntVector3(codeColor_number, 220, 0, 220);
    _setIntVector3(codeColor_string, 48, 149, 186);
    _setIntVector3(codeColor_character, 48, 149, 186);
    _setIntVector3(codeColor_operator, 0, 0, 0);
    _setIntVector3(codeColor_preprocessor, 0, 128, 128);
    _setIntVector3(codeColor_identifier, 64, 64, 64);
    _setIntVector3(codeColor_word, 50, 50, 215);
    _setIntVector3(codeColor_word2, 152, 0, 0);
    _setIntVector3(codeColor_word3, 220, 80, 20);
    _setIntVector3(codeColor_word4, 152, 64, 0);

    // Directories section:
    // *****************************
    defaultDirectoryForScenes = "";
    defaultDirectoryForModels = "";
    defaultDirectoryForImportExport = "";
    defaultDirectoryForMiscFiles = "";

    // Serialization section:
    // *****************************
    autoSaveDelay = 2; // 2 minutes for an auto-save by default. set to 0 for no auto-save
    doNotWritePersistentData = false;
    compressFiles = true;
    fileDialogs = -1; // default
    allowSettingsWrite = true;

    // Undo/redo section:
    // *****************************
    _undoRedoEnabled = true;
    _undoRedoOnlyPartialWithCameras = true;
    undoRedoLevelCount = 16;
    undoRedoMaxBufferSize = 80000000;
    timeInMsForUndoRedoTooLongWarning = 200;

    // Messaging section:
    // *****************************
    doNotShowUpdateCheckMessage = false;
    doNotShowProgressBars = false;
    suppressStartupDialogs = false;
    suppressXmlOverwriteMsg = false;
    noVersionCheck = 0;

    // Compatibility section:
    // *****************************
    middleMouseButtonSwitchesModes = false; // set to false on 28/9/2014
    navigationBackwardCompatibility = false;
    colorAdjust_backCompatibility = 1.0; // default
    specificGpuTweak = false;            // default
    disableOpenGlBasedCustomUi = false;
    disableVisibleEdges = false;
    showOldDlgs = false;
    enableOldRenderableBehaviour = false;
    enableOldMirrorObjects = false;
    allowOldEduRelease = -1;
    threadedScriptsStoppingGraceTime = 0;
    bugFix1 = 1000;
    readDelay = -500;
    writeDelay = 1000;
    useBuffers = true;
    scriptConversion = 0;
    notifyDeprecated = 1;

    // Various section:
    // *****************************
    preferredSandboxLang = "";  // same as "lua" actually
    mouseWheelZoomFactor = 1.0; // default
    dynamicActivityRange = 1000.0;
    _translationStepSize = 0.025;
    _rotationStepSize = 5.0 * degToRad;
    freeServerPortStart = 20000;
    _nextfreeServerPortToUse = freeServerPortStart;
    freeServerPortRange = 2000;
    _abortScriptExecutionButton = 3;
    triCountInOBB = 8; // gave best results in 2009/07/21
    identicalVertexTolerance = 0.000001;
    runCustomizationScripts = true;
    runAddOns = true;

    test1 = false;
    macChildDialogType = -1; // default
    additionalLuaPath = "";
    additionalPythonPath = "";
    defaultPython = "";
    execUnsafe = true;
    execUnsafeExt = false;

    desktopRecordingIndex = 0;
    desktopRecordingWidth = -1;
    externalScriptEditor = "";
    xmlExportSplitSize = 0;
    xmlExportKnownFormats = true;

    forceBugFix_rel30002 = false;

    license_lite = "";
    license_edu = "";
    license_pro = "";
    license = "";
    licenseEndpoint = "";
    floatingLicenseEnabled = false;
    floatingLicenseServer = "127.0.0.1";
    floatingLicensePort = 20249;
    keepDongleOpen = false;

    loadUserSettings();
}

CUserSettings::~CUserSettings()
{
}

void CUserSettings::setTranslationStepSize(double s)
{
    double sc = 1.0;
    if ((s >= 0.0075) && (s < 0.075))
        sc = 10.0;
    if (s >= 0.075)
        sc = 100.0;
    if (s < 0.0015 * sc)
        s = 0.001 * sc;
    else
    {
        if (s < 0.00375 * sc)
        {
            if (sc < 2.0)
                s = 0.002 * sc;
            else
                s = 0.0025 * sc;
        }
        else
            s = 0.005 * sc;
    }
    _translationStepSize = s;
}
double CUserSettings::getTranslationStepSize()
{
    return (_translationStepSize);
}

void CUserSettings::setRotationStepSize(double s)
{
    if (s < 1.5 * degToRad)
        s = 1.0 * degToRad;
    else
    {
        if (s < 3.5 * degToRad)
            s = 2.0 * degToRad;
        else
        {
            if (s < 7.5 * degToRad)
                s = 5.0 * degToRad;
            else
            {
                if (s < 12.5 * degToRad)
                    s = 10.0 * degToRad;
                else
                {
                    if (s < 22.5 * degToRad)
                        s = 15.0 * degToRad;
                    else
                    {
                        if (s < 37.5 * degToRad)
                            s = 30.0 * degToRad;
                        else
                            s = 45.0 * degToRad;
                    }
                }
            }
        }
    }
    _rotationStepSize = s;
}

double CUserSettings::getRotationStepSize()
{
    return (_rotationStepSize);
}

void CUserSettings::setUndoRedoEnabled(bool isEnabled)
{
    _undoRedoEnabled = isEnabled;
    if (App::currentWorld->undoBufferContainer != nullptr)
        App::currentWorld->undoBufferContainer->emptySceneProcedure();
}

bool CUserSettings::getUndoRedoEnabled()
{
    return (_undoRedoEnabled);
}

bool CUserSettings::getUndoRedoOnlyPartialWithCameras()
{
    return (_undoRedoOnlyPartialWithCameras);
}

int CUserSettings::getIdleFps()
{
    if (_idleFps_session >= 0)
        return (_idleFps_session);
    return (_idleFps);
}

void CUserSettings::setIdleFps(int fps)
{
    _idleFps = tt::getLimitedInt(0, 25, fps);
}

void CUserSettings::setIdleFps_session(int fps)
{
    if (fps != _idleFps_session)
    {
        _idleFps_session = fps;
        if ((App::worldContainer != nullptr) && App::worldContainer->getEventsEnabled())
        {
            const char* cmd = propApp_idleFps.name;
            CCbor* ev = App::worldContainer->createObjectChangedEvent(sim_handle_app, cmd, true);
            ev->appendKeyInt(cmd, _idleFps_session);
            App::worldContainer->pushEvent();
        }
    }
}

int CUserSettings::getAbortScriptExecutionTiming()
{
    return (_abortScriptExecutionButton);
}

int CUserSettings::getNextFreeServerPortToUse()
{
    return (_nextfreeServerPortToUse);
}

void CUserSettings::setNextFreeServerPortToUse(int p)
{
    _nextfreeServerPortToUse = p;
}

void CUserSettings::_setIntVector3(int v[3], int a, int b, int c)
{
    v[0] = a;
    v[1] = b;
    v[2] = c;
}

void CUserSettings::saveUserSettings(bool outputMsgs /*=true*/)
{
    if (allowSettingsWrite)
    {
        CConfReaderAndWriter c;

        c.addRandomLine("// Debugging");
        c.addRandomLine("// =================================================");
        c.addBoolean(_USR_ALWAYS_SHOW_CONSOLE, alwaysShowConsole, "");
        c.addString(
            _USR_VERBOSITY, _overrideConsoleVerbosity,
            "to override console verbosity setting, use any of: default (do not override), none, errors, warnings, "
            "loadinfos, scripterrors, scriptwarnings, msgs, infos, debug, trace, tracelua or traceall");
        c.addString(
            _USR_STATUSBAR_VERBOSITY, _overrideStatusbarVerbosity,
            "to override statusbar verbosity setting, use any of: default (do not override), none, errors, warnings, "
            "loadinfos, scripterrors, scriptwarnings, msgs, infos, debug, trace, tracelua or traceall");
        c.addString(_USR_DIALOG_VERBOSITY, _overrideDialogVerbosity,
                    "to override dialog verbosity setting, use any of: default (do not override), none, errors, "
                    "warnings, questions or infos");
        c.addBoolean(_USR_TIMESTAMP, timeStamp, "");
        c.addString(_USR_LOG_FILTER, _consoleLogFilter,
                    "leave empty for no filter. Filter format: txta1&txta2&...&txtaN|txtb1&txtb2&...&txtbN|...");
        c.addBoolean(_USR_UNDECORATED_STATUSBAR_MSGS, undecoratedStatusbarMessages, "");
        c.addBoolean(_USR_CONSOLE_MSGS_TO_FILE, App::getConsoleMsgToFile(),
                     "if true, console messages are sent to consoleMsgsFile");
        c.addString(_USR_CONSOLE_MSGS_FILE, App::getConsoleMsgFile(), "defaults to debugLog.txt");
        c.addRandomLine("");
        c.addRandomLine("");

        c.addRandomLine("// Rendering");
        c.addRandomLine("// =================================================");
        c.addInteger(_USR_IDLE_FPS, _idleFps, "");
        c.addInteger(_USR_OFFSCREEN_CONTEXT_TYPE, offscreenContextType,
                     "recommended to keep -1 (-1=default, 0=Qt offscreen, 1=QGLWidget/QOpenGLWidget visible, "
                     "2=QGLWidget/QOpenGLWidget invisible).");
        c.addInteger(_USR_FBO_TYPE, fboType,
                     "recommended to keep -1 (-1=default, 0=native, 1=QOpenGLFramebufferObject).");
        // c.addBoolean(_USR_FORCE_FBO_VIA_EXT,forceFboViaExt,"recommended to keep false.");
        c.addInteger(_USR_VBO_OPERATION, vboOperation,
                     "recommended to keep -1 (-1=default, 0=always off, 1=on when available).");
        // c.addInteger(_USR_VBO_PERSISTENCE_IN_MS,vboPersistenceInMs,"recommended to keep 5000.");
        // c.addBoolean(_USR_OGL_COMPATIBILITY_TWEAK_1,oglCompatibilityTweak1,"recommended to keep false since it causes
        // small memory leaks."); c.addBoolean(_USR_USE_GLFINISH,useGlFinish,"recommended to keep false. Graphic card
        // dependent."); c.addBoolean(_USR_USE_GLFINISH_VISION_SENSORS,useGlFinish_visionSensors,"recommended to keep
        // false. Graphic card dependent."); c.addInteger(_USR_VSYNC,vsync,"recommended to keep at 0. Graphic card
        // dependent."); c.addFloat(_USR_STEREO_DIST,stereoDist,"0=no stereo, otherwise the intra occular distance
        // (0.0635 for the human eyes).");
        c.addInteger(_USR_HIGH_RES_DISPLAY, highResDisplay,
                     "-1=none, 1=special, 2=enabled, 3=enable oglScaling and guiScaling below.");
        c.addInteger(_USR_GUESSED_SCALING_FOR_2X_OPENGL, guessedDisplayScalingThresholdFor2xOpenGl, "200=default");
        c.addInteger(_USR_OGL_SCALING, oglScaling, "1=default. No effect if highResDisplay!=3 above.");
        c.addFloat(_USR_GUI_SCALING, guiScaling, "1.0=default. No effect if highResDisplay!=3 above.");
        // c.addBoolean(_USR_NO_EDGES_WHEN_MOUSE_DOWN,noEdgesWhenMouseDownInCameraView,"if true, rendering is faster
        // during mouse/view interaction");
        // c.addBoolean(_USR_NO_TEXTURES_WHEN_MOUSE_DOWN,noTexturesWhenMouseDownInCameraView,"if true, rendering is
        // faster during mouse/view interaction");
        // c.addBoolean(_USR_NO_CUSTOM_UIS_WHEN_MOUSE_DOWN,noCustomUisWhenMouseDownInCameraView,"if true, rendering is
        // faster during mouse/view interaction");
        c.addInteger(_USR_HIERARCHY_REFRESH_CNT, hierarchyRefreshCnt, "");

        c.addRandomLine("");
        c.addRandomLine("");

        c.addRandomLine("// Visual");
        c.addRandomLine("// =================================================");
        c.addIntVector2(_USR_INIT_WINDOW_SIZE, initWindowSize, "0,0 for fullscreen");
        c.addIntVector2(_USR_INIT_WINDOW_POS, initWindowPos, "");
        c.addBoolean(_USR_DARK_MODE, darkMode, "");
        // c.addInteger(_USR_RENDERING_SURFACE_VERTICAL_SHIFT,renderingSurfaceVShift,"");
        // c.addInteger(_USR_RENDERING_SURFACE_VERTICAL_RESIZE,renderingSurfaceVResize,"");
        c.addBoolean(_USR_DISPLAY_WORLD_REF, displayWorldReference, "");
        // c.addBoolean(_USR_ANTIALIASING,antiAliasing,"");
        c.addInteger(_USR_GUI_FONT_SIZE_WIN, guiFontSize_Win, "-1=default");
        c.addInteger(_USR_GUI_FONT_SIZE_MAC, guiFontSize_Mac, "-1=default");
        c.addInteger(_USR_GUI_FONT_SIZE_LINUX, guiFontSize_Linux, "-1=default");
        c.addBoolean(_USR_STATUSBAR_INITIALLY_VISIBLE, statusbarInitiallyVisible, "");
        c.addBoolean(_USR_MODELBROWSER_INITIALLY_VISIBLE, modelBrowserInitiallyVisible, "");
        c.addBoolean(_USR_SCENEHIERARCHY_INITIALLY_VISIBLE, sceneHierarchyInitiallyVisible, "");
        c.addBoolean(_USR_SCENEHIERARCHY_HIDDEN_DURING_SIMULATION, sceneHierarchyHiddenDuringSimulation, "");
        c.addString(_USR_SCRIPT_EDITOR_FONT, scriptEditorFont,
                    "empty=default. e.g. \"Courier New\", \"DejaVu Sans Mono\", \"Consolas\", \"Ubuntu Mono\", etc.");
        c.addBoolean(_USR_SCRIPT_EDITOR_BOLDFONT, scriptEditorBoldFont, "");
        c.addInteger(_USR_SCRIPT_EDITOR_FONT_SIZE, scriptEditorFontSize, "-1=default.");

        c.addIntVector3(_USR_CODE_COLOR_BACKGROUND, codeColor_background, "");
        c.addIntVector3(_USR_CODE_COLOR_SELECTION, codeColor_selection, "");
        c.addIntVector3(_USR_CODE_COLOR_COMMENT, codeColor_comment, "");
        c.addIntVector3(_USR_CODE_COLOR_NUMBER, codeColor_number, "");
        c.addIntVector3(_USR_CODE_COLOR_STRING, codeColor_string, "");
        c.addIntVector3(_USR_CODE_COLOR_CHARACTER, codeColor_character, "");
        c.addIntVector3(_USR_CODE_COLOR_OPERATOR, codeColor_operator, "");
        c.addIntVector3(_USR_CODE_COLOR_PREPROCESSOR, codeColor_preprocessor, "");
        c.addIntVector3(_USR_CODE_COLOR_IDENTIFIER, codeColor_identifier, "");
        c.addIntVector3(_USR_CODE_COLOR_WORD, codeColor_word, "");
        c.addIntVector3(_USR_CODE_COLOR_WORD2, codeColor_word2, "");
        c.addIntVector3(_USR_CODE_COLOR_WORD3, codeColor_word3, "");
        c.addIntVector3(_USR_CODE_COLOR_WORD4, codeColor_word4, "");

        c.addRandomLine("");
        c.addRandomLine("");

        c.addRandomLine("// Directories");
        c.addRandomLine("// =================================================");
        c.addString(_USR_DIRECTORY_FOR_SCENES, defaultDirectoryForScenes,
                    "absolute path, e.g. d:/myScenes (or leave empty for default path)");
        c.addString(_USR_DIRECTORY_FOR_MODELS, defaultDirectoryForModels,
                    "absolute path, e.g. d:/myModels (or leave empty for default path)");
        c.addString(_USR_DIRECTORY_FOR_IMPORTEXPORT, defaultDirectoryForImportExport,
                    "absolute path, e.g. d:/myCadFiles (or leave empty for default path)");
        c.addString(_USR_DIRECTORY_FOR_MISC, defaultDirectoryForMiscFiles,
                    "absolute path, e.g. d:/myMiscFiles (or leave empty for default path)");

        c.addRandomLine("");
        c.addRandomLine("");

        c.addRandomLine("// Serialization");
        c.addRandomLine("// =================================================");
        c.addInteger(_USR_AUTO_SAVE_DELAY, autoSaveDelay, "in minutes. 0 to disable.");
        c.addBoolean(_USR_DO_NOT_WRITE_PERSISTENT_DATA, doNotWritePersistentData, "");
        // c.addBoolean(_USR_COMPRESS_FILES,compressFiles,"");
        // c.addInteger(_USR_FILE_DIALOGS_NATIVE,fileDialogs,"recommended to keep -1 (-1=default, 0=native dialogs, 1=Qt
        // dialogs).");
        c.addBoolean(_USR_ALLOW_SETTINGS_WRITE, allowSettingsWrite, "");

        c.addRandomLine("");
        c.addRandomLine("");

        c.addRandomLine("// Undo/Redo");
        c.addRandomLine("// =================================================");
        c.addBoolean(_USR_UNDO_REDO_ENABLED, _undoRedoEnabled, "");
        c.addBoolean(_USR_UNDO_REDO_PARTIAL_WITH_CAMERAS, _undoRedoOnlyPartialWithCameras, "");
        c.addInteger(_USR_UNDO_REDO_LEVEL_COUNT, undoRedoLevelCount, "");
        c.addInteger(_USR_UNDO_REDO_MAX_BUFFER_SIZE, undoRedoMaxBufferSize, "");
        c.addInteger(_USR_TIME_FOR_UNDO_REDO_TOO_LONG_WARNING, timeInMsForUndoRedoTooLongWarning, "");
        c.addRandomLine("");
        c.addRandomLine("");

        c.addRandomLine("// Messaging");
        c.addRandomLine("// =================================================");
        c.addBoolean(_USR_DO_NOT_SHOW_UPDATE_CHECK_MESSAGE, doNotShowUpdateCheckMessage, "");
        c.addBoolean(_USR_DO_NOT_SHOW_PROGRESS_BARS, doNotShowProgressBars, "");
        c.addBoolean(_USR_SUPPRESS_STARTUP_DIALOG, suppressStartupDialogs, "");
        c.addBoolean(_USR_SUPPRESS_XML_OVERWRITE_MSG, suppressXmlOverwriteMsg, "");

        c.addRandomLine("");
        c.addRandomLine("");

        c.addRandomLine("// Compatibility");
        c.addRandomLine("// =================================================");
        // c.addBoolean(_USR_MIDDLE_MOUSE_BUTTON_SWITCHES_MODES,middleMouseButtonSwitchesModes,"has only an effect if
        // navigationBackwardCompatibility is true.");
        // c.addBoolean(_USR_NAVIGATION_BACKWARD_COMPATIBILITY_MODE,navigationBackwardCompatibility,"recommended to keep
        // false."); c.addFloat(_USR_COLOR_ADJUST_BACK_COMPATIBILITY,colorAdjust_backCompatibility,"recommended to
        // keep 1.0"); c.addBoolean(_USR_SPECIFIC_GPU_TWEAK,specificGpuTweak,"");
        // c.addBoolean(_USR_DISABLED_OPENGL_BASED_CUSTOM_UI, disableOpenGlBasedCustomUi, "");
        // c.addBoolean(_USR_DISABLE_VISIBLE_EDGES, disableVisibleEdges, "");

        c.addBoolean(_USR_SHOW_old_DLGS, showOldDlgs, "");
        // c.addBoolean(_USR_ENABLE_OLD_RENDERABLE,enableOldRenderableBehaviour,"");
        // c.addBoolean(_USR_ENABLE_old_MIRROR_OBJECTS,enableOldMirrorObjects,"");
        // c.addInteger(_USR_THREADED_SCRIPTS_GRACE_TIME,threadedScriptsStoppingGraceTime,"");
        c.addInteger(_USR_READDELAY, readDelay, "");
        c.addInteger(_USR_WRITEDELAY, writeDelay, "");
        c.addBoolean(_USR_USEBUFFERS, useBuffers, "");
        c.addInteger(_USR_SCRIPTCONVERSION, scriptConversion, "-1: convert to old scripts, 1: convert to new script objects");
        c.addInteger(_USR_NOTIFY_DEPRECATED, notifyDeprecated, "0: no notification, 1: simple notification, 2: exhaustive notification");

        c.addRandomLine("");
        c.addRandomLine("");

        c.addRandomLine("// Various");
        c.addRandomLine("// =================================================");

        c.addString(_USR_PREFERRED_SANDBOX_LANG, preferredSandboxLang, "python, lua or bareLua");
        c.addFloat(_USR_MOUSE_WHEEL_ZOOM_FACTOR, mouseWheelZoomFactor, "");
        c.addFloat(_USR_DYNAMIC_ACTIVITY_RANGE, dynamicActivityRange, "");
        c.addFloat(_USR_TRANSLATION_STEP_SIZE, _translationStepSize, "");
        c.addFloat(_USR_ROTATION_STEP_SIZE, _rotationStepSize * radToDeg, "");
        // c.addInteger(_USR_FREE_SERVER_PORT_START,freeServerPortStart,"");
        // c.addInteger(_USR_FREE_SERVER_PORT_RANGE,freeServerPortRange,"");
        c.addInteger(_USR_ABORT_SCRIPT_EXECUTION_BUTTON, _abortScriptExecutionButton, "in seconds. Zero to disable.");
        c.addInteger(_USR_TRIANGLE_COUNT_IN_OBB, triCountInOBB, "");
        c.addFloat(_USR_IDENTICAL_VERTICES_TOLERANCE, identicalVertexTolerance, "");
        c.addBoolean(_USR_RUN_CUSTOMIZATION_SCRIPTS, runCustomizationScripts, "");
        c.addBoolean(_USR_RUN_ADDONS, runAddOns, "");

        // c.addBoolean(_USR_TEST1,test1,"recommended to keep false.");
        // c.addInteger(_USR_MAC_CHILD_DIALOG_TYPE,macChildDialogType,"-1=default.");
        c.addString(_USR_ADDITIONAL_LUA_PATH, additionalLuaPath, "e.g. d:/myLuaRoutines");
        c.addString(_USR_ADDITIONAL_PYTHON_PATH, additionalPythonPath, "e.g. d:/myPythonRoutines");
        c.addString(_USR_DEFAULT_PYTHON, defaultPython, "e.g. c:/Python38/python.exe");
        c.addBoolean(_USR_EXEC_UNSAFE, execUnsafe, "");
        c.addBoolean(_USR_EXEC_UNSAFE_EXT, execUnsafeExt,
                     "same as above, but for code triggered externally. Recommended to keep false.");
        // c.addInteger(_USR_DESKTOP_RECORDING_INDEX,desktopRecordingIndex,"");
        // c.addInteger(_USR_DESKTOP_RECORDING_WIDTH,desktopRecordingWidth,"-1=default.");
        c.addString(_USR_EXTERNAL_SCRIPT_EDITOR, externalScriptEditor, "");
        c.addInteger(_USR_XML_EXPORT_SPLIT_SIZE, xmlExportSplitSize, "0=generate a single file.");
        c.addBoolean(_USR_XML_EXPORT_KNOWN_FORMATS, xmlExportKnownFormats,
                     "true=if several files are generated, mesh and image files are saved under known formats.");

        c.addRandomLine("");
        c.addRandomLine("");

        c.addRandomLine("// License");
        c.addRandomLine("// =================================================");
#ifdef IS_LITE
        license_lite = license;
#endif
#ifdef IS_EDU
        license_edu = license;
#endif
#ifdef IS_PRO
        license_pro = license;
#endif
        c.addString(_USR_LICENSE_LITE, license_lite, "");
        c.addString(_USR_LICENSE_EDU, license_edu, "");
        c.addString(_USR_LICENSE_PRO, license_pro, "");
        // only for backcompatibility      c.addString(_USR_LICENSE, license, "");
        if (licenseEndpoint.size() > 0)
            c.addString(_USR_LICENSE_ENDPOINT, licenseEndpoint, "");
        if (keepDongleOpen)
            c.addBoolean(_USR_KEEP_DONGLE_OPEN, keepDongleOpen, "");
        if (floatingLicenseEnabled)
        {
            c.addBoolean(_USR_FLOAT_LICENSE_ENABLED, floatingLicenseEnabled, "");
            c.addString(_USR_FLOAT_LICENSE_SERVER_ADDRESS, floatingLicenseServer, "");
            c.addInteger(_USR_FLOAT_LICENSE_SERVER_PORT, floatingLicensePort, "");
        }

        if (mem.size() != 0)
        {
            c.addRandomLine("");
            c.addRandomLine("");

            c.addRandomLine("// Other");
            c.addRandomLine("// =================================================");
            c.addString(_USR_MEM, mem, "");
        }

        std::string file(CFolderSystem::getUserSettingsPath());
        file += "/";
        file += USER_SETTINGS_FILENAME;
        c.writeConfiguration(file.c_str());
        if (outputMsgs)
        {
            std::string txt("wrote user settings to ");
            txt += file;
            App::logMsg(sim_verbosity_scriptinfos, txt.c_str());
        }
    }
}

void CUserSettings::loadUserSettings()
{
    CConfReaderAndWriter c;
    std::string file(CFolderSystem::getUserSettingsPath());
    file += "/";
    file += USER_SETTINGS_FILENAME;
    if (!c.readConfiguration(file.c_str(), "settings"))
        saveUserSettings();

    // Debugging section:
    // *****************************
    c.getBoolean(_USR_ALWAYS_SHOW_CONSOLE, alwaysShowConsole);
    c.getString(_USR_VERBOSITY, _overrideConsoleVerbosity);
    if (_overrideConsoleVerbosity.compare("default") != 0)
    {
        int l = App::getVerbosityLevelFromString(_overrideConsoleVerbosity.c_str());
        if (l >= sim_verbosity_none)
        {
            App::setConsoleVerbosity(l);
            App::logMsg(sim_verbosity_warnings, "console verbosity overridden to '%s' via usrset.txt.",
                        _overrideConsoleVerbosity.c_str());
        }
        else
            App::logMsg(sim_verbosity_errors, "unrecognized verbosity value in usrset.txt: %s.",
                        _overrideConsoleVerbosity.c_str());
    }
    c.getString(_USR_STATUSBAR_VERBOSITY, _overrideStatusbarVerbosity);
    if (_overrideStatusbarVerbosity.compare("default") != 0)
    {
        int l = App::getVerbosityLevelFromString(_overrideStatusbarVerbosity.c_str());
        if (l >= sim_verbosity_none)
        {
            App::setStatusbarVerbosity(l);
            App::logMsg(sim_verbosity_warnings, "statusbar verbosity overridden to '%s' via usrset.txt.",
                        _overrideStatusbarVerbosity.c_str());
        }
        else
            App::logMsg(sim_verbosity_errors, "unrecognized verbosity value in usrset.txt: %s.",
                        _overrideStatusbarVerbosity.c_str());
    }
    c.getString(_USR_LOG_FILTER, _consoleLogFilter);
    App::setConsoleLogFilter(_consoleLogFilter.c_str());

    c.getString(_USR_DIALOG_VERBOSITY, _overrideDialogVerbosity);
    if (_overrideDialogVerbosity.compare("default") != 0)
    {
        int l = App::getVerbosityLevelFromString(_overrideDialogVerbosity.c_str());
        if (l >= sim_verbosity_none)
        {
            App::setDlgVerbosity(l);
            App::logMsg(sim_verbosity_warnings, "dialog verbosity overridden to '%s' via usrset.txt.",
                        _overrideDialogVerbosity.c_str());
        }
        else
            App::logMsg(sim_verbosity_errors, "unrecognized verbosity value in usrset.txt: %s.",
                        _overrideDialogVerbosity.c_str());
    }
    c.getBoolean(_USR_TIMESTAMP, timeStamp);
    c.getBoolean(_USR_UNDECORATED_STATUSBAR_MSGS, undecoratedStatusbarMessages);
    bool dummyBool = false;
    if (c.getBoolean(_USR_CONSOLE_MSGS_TO_FILE, dummyBool))
        App::setConsoleMsgToFile(dummyBool);
    std::string debugFile;
    if (c.getString(_USR_CONSOLE_MSGS_FILE, debugFile))
        App::setConsoleMsgFile(debugFile.c_str());

    // Rendering section:
    // *****************************
    c.getInteger(_USR_IDLE_FPS, _idleFps);
    setIdleFps(_idleFps);
    c.getInteger(_USR_OFFSCREEN_CONTEXT_TYPE, offscreenContextType);
    c.getInteger(_USR_FBO_TYPE, fboType);
    c.getBoolean(_USR_FORCE_FBO_VIA_EXT, forceFboViaExt);
    c.getInteger(_USR_VBO_OPERATION, vboOperation);
#ifdef USES_QGLWIDGET
#else
    offscreenContextType = 0;
    fboType = 1;
#endif
    c.getInteger(_USR_VBO_PERSISTENCE_IN_MS, vboPersistenceInMs);
    c.getBoolean(_USR_OGL_COMPATIBILITY_TWEAK_1, oglCompatibilityTweak1);
    c.getBoolean(_USR_USE_GLFINISH, useGlFinish);
    c.getBoolean(_USR_USE_GLFINISH_VISION_SENSORS, useGlFinish_visionSensors);
    c.getInteger(_USR_VSYNC, vsync);
    c.getFloat(_USR_STEREO_DIST, stereoDist);
    c.getInteger(_USR_HIGH_RES_DISPLAY, highResDisplay);
    c.getInteger(_USR_GUESSED_SCALING_FOR_2X_OPENGL, guessedDisplayScalingThresholdFor2xOpenGl);
    c.getInteger(_USR_OGL_SCALING, oglScaling);
    c.getFloat(_USR_GUI_SCALING, guiScaling);
    c.getBoolean(_USR_NO_EDGES_WHEN_MOUSE_DOWN, noEdgesWhenMouseDownInCameraView);
    c.getBoolean(_USR_NO_TEXTURES_WHEN_MOUSE_DOWN, noTexturesWhenMouseDownInCameraView);
    c.getBoolean(_USR_NO_CUSTOM_UIS_WHEN_MOUSE_DOWN, noCustomUisWhenMouseDownInCameraView);
    c.getInteger(_USR_HIERARCHY_REFRESH_CNT, hierarchyRefreshCnt);
#ifdef USES_QGLWIDGET
#else
    hierarchyRefreshCnt = 0;
#endif

    // Visual section:
    // *****************************
    c.getIntVector2(_USR_INIT_WINDOW_SIZE, initWindowSize);
    c.getIntVector2(_USR_INIT_WINDOW_POS, initWindowPos);
    c.getBoolean(_USR_DARK_MODE, darkMode);
    c.getInteger(_USR_RENDERING_SURFACE_VERTICAL_SHIFT, renderingSurfaceVShift);
    c.getInteger(_USR_RENDERING_SURFACE_VERTICAL_RESIZE, renderingSurfaceVResize);
    c.getBoolean(_USR_DISPLAY_WORLD_REF, displayWorldReference);
    c.getBoolean(_USR_ANTIALIASING, antiAliasing);
    c.getInteger(_USR_GUI_FONT_SIZE_WIN, guiFontSize_Win);
    c.getInteger(_USR_GUI_FONT_SIZE_MAC, guiFontSize_Mac);
    c.getInteger(_USR_GUI_FONT_SIZE_LINUX, guiFontSize_Linux);
    c.getBoolean(_USR_STATUSBAR_INITIALLY_VISIBLE, statusbarInitiallyVisible);
    c.getBoolean(_USR_MODELBROWSER_INITIALLY_VISIBLE, modelBrowserInitiallyVisible);
#ifdef SIM_WITH_GUI
    // OLDMODELBROWSER COglSurface::_browserEnabled=modelBrowserInitiallyVisible;
    GuiApp::setBrowserEnabled(modelBrowserInitiallyVisible);
#endif
    c.getBoolean(_USR_SCENEHIERARCHY_INITIALLY_VISIBLE, sceneHierarchyInitiallyVisible);
#ifdef SIM_WITH_GUI
    App::setHierarchyEnabled(sceneHierarchyInitiallyVisible);
#endif
    c.getBoolean(_USR_SCENEHIERARCHY_HIDDEN_DURING_SIMULATION, sceneHierarchyHiddenDuringSimulation);

    c.getString(_USR_SCRIPT_EDITOR_FONT, scriptEditorFont);

    c.getBoolean(_USR_SCRIPT_EDITOR_BOLDFONT, scriptEditorBoldFont);
    c.getInteger(_USR_SCRIPT_EDITOR_FONT_SIZE, scriptEditorFontSize);

    c.getIntVector3(_USR_CODE_COLOR_BACKGROUND, codeColor_background);
    c.getIntVector3(_USR_CODE_COLOR_SELECTION, codeColor_selection);
    c.getIntVector3(_USR_CODE_COLOR_COMMENT, codeColor_comment);
    c.getIntVector3(_USR_CODE_COLOR_NUMBER, codeColor_number);
    c.getIntVector3(_USR_CODE_COLOR_STRING, codeColor_string);
    c.getIntVector3(_USR_CODE_COLOR_CHARACTER, codeColor_character);
    c.getIntVector3(_USR_CODE_COLOR_OPERATOR, codeColor_operator);
    c.getIntVector3(_USR_CODE_COLOR_PREPROCESSOR, codeColor_preprocessor);
    c.getIntVector3(_USR_CODE_COLOR_IDENTIFIER, codeColor_identifier);
    c.getIntVector3(_USR_CODE_COLOR_WORD, codeColor_word);
    c.getIntVector3(_USR_CODE_COLOR_WORD2, codeColor_word2);
    c.getIntVector3(_USR_CODE_COLOR_WORD3, codeColor_word3);
    c.getIntVector3(_USR_CODE_COLOR_WORD4, codeColor_word4);

    // Directories section:
    // *****************************
    c.getString(_USR_DIRECTORY_FOR_SCENES, defaultDirectoryForScenes);
    c.getString(_USR_DIRECTORY_FOR_MODELS, defaultDirectoryForModels);
    c.getString(_USR_DIRECTORY_FOR_IMPORTEXPORT, defaultDirectoryForImportExport);
    c.getString(_USR_DIRECTORY_FOR_MISC, defaultDirectoryForMiscFiles);

    // Serialization section:
    // *****************************
    c.getInteger(_USR_AUTO_SAVE_DELAY, autoSaveDelay);
    c.getBoolean(_USR_DO_NOT_WRITE_PERSISTENT_DATA, doNotWritePersistentData);
    c.getBoolean(_USR_COMPRESS_FILES, compressFiles);
    c.getInteger(_USR_FILE_DIALOGS_NATIVE, fileDialogs);
    c.getBoolean(_USR_ALLOW_SETTINGS_WRITE, allowSettingsWrite);

    // Undo/redo section:
    // *****************************
    c.getBoolean(_USR_UNDO_REDO_ENABLED, _undoRedoEnabled);
    c.getBoolean(_USR_UNDO_REDO_PARTIAL_WITH_CAMERAS, _undoRedoOnlyPartialWithCameras);
    c.getInteger(_USR_UNDO_REDO_LEVEL_COUNT, undoRedoLevelCount);
    undoRedoLevelCount = tt::getLimitedInt(3, 50, undoRedoLevelCount);
    c.getInteger(_USR_UNDO_REDO_MAX_BUFFER_SIZE, undoRedoMaxBufferSize);
    undoRedoMaxBufferSize = tt::getLimitedInt(2000000, 800000000, undoRedoMaxBufferSize);
    c.getInteger(_USR_TIME_FOR_UNDO_REDO_TOO_LONG_WARNING, timeInMsForUndoRedoTooLongWarning);

    // Messaging section:
    // *****************************
    c.getBoolean(_USR_DO_NOT_SHOW_UPDATE_CHECK_MESSAGE, doNotShowUpdateCheckMessage);
    c.getBoolean(_USR_DO_NOT_SHOW_PROGRESS_BARS, doNotShowProgressBars);
    c.getBoolean(_USR_SUPPRESS_STARTUP_DIALOG, suppressStartupDialogs);
    c.getBoolean(_USR_SUPPRESS_XML_OVERWRITE_MSG, suppressXmlOverwriteMsg);
    c.getInteger(_USR_NO_VERSION_CHECK, noVersionCheck);

    // Compatibility section:
    // *****************************
    c.getBoolean(_USR_MIDDLE_MOUSE_BUTTON_SWITCHES_MODES, middleMouseButtonSwitchesModes);
    c.getBoolean(_USR_NAVIGATION_BACKWARD_COMPATIBILITY_MODE, navigationBackwardCompatibility);
    c.getFloat(_USR_COLOR_ADJUST_BACK_COMPATIBILITY, colorAdjust_backCompatibility);
    c.getBoolean(_USR_SPECIFIC_GPU_TWEAK, specificGpuTweak);
    c.getBoolean(_USR_DISABLED_OPENGL_BASED_CUSTOM_UI, disableOpenGlBasedCustomUi);
    c.getBoolean(_USR_DISABLE_VISIBLE_EDGES, disableVisibleEdges);
    c.getBoolean(_USR_SHOW_old_DLGS, showOldDlgs);
    c.getBoolean(_USR_ENABLE_OLD_RENDERABLE, enableOldRenderableBehaviour);
    c.getBoolean(_USR_ENABLE_old_MIRROR_OBJECTS, enableOldMirrorObjects);
    c.getInteger(_USR_ALLOW_old_EDU_RELEASE, allowOldEduRelease);
    c.getInteger(_USR_THREADED_SCRIPTS_GRACE_TIME, threadedScriptsStoppingGraceTime);
    c.getInteger(_USR_BUGFIX1, bugFix1);
    c.getInteger(_USR_READDELAY, readDelay);
    c.getInteger(_USR_WRITEDELAY, writeDelay);
    c.getBoolean(_USR_USEBUFFERS, useBuffers);
    c.getInteger(_USR_SCRIPTCONVERSION, scriptConversion);
    c.getInteger(_USR_NOTIFY_DEPRECATED, notifyDeprecated);

    // Various section:
    // *****************************
    c.getString(_USR_PREFERRED_SANDBOX_LANG, preferredSandboxLang);
    std::string lang;
    if (App::getAppNamedParam("preferredSandboxLang", lang))
        preferredSandboxLang = lang;

    c.getFloat(_USR_MOUSE_WHEEL_ZOOM_FACTOR, mouseWheelZoomFactor);
    c.getFloat(_USR_DYNAMIC_ACTIVITY_RANGE, dynamicActivityRange);
    if (c.getFloat(_USR_TRANSLATION_STEP_SIZE, _translationStepSize))
        setTranslationStepSize(_translationStepSize);
    if (c.getFloat(_USR_ROTATION_STEP_SIZE, _rotationStepSize))
        setRotationStepSize(_rotationStepSize * degToRad);
    c.getInteger(_USR_FREE_SERVER_PORT_START, freeServerPortStart);
    _nextfreeServerPortToUse = freeServerPortStart;
    c.getInteger(_USR_FREE_SERVER_PORT_RANGE, freeServerPortRange);
    c.getInteger(_USR_ABORT_SCRIPT_EXECUTION_BUTTON, _abortScriptExecutionButton);
    c.getInteger(_USR_TRIANGLE_COUNT_IN_OBB, triCountInOBB);
    c.getFloat(_USR_IDENTICAL_VERTICES_TOLERANCE, identicalVertexTolerance);
    c.getBoolean(_USR_RUN_CUSTOMIZATION_SCRIPTS, runCustomizationScripts);
    c.getBoolean(_USR_RUN_ADDONS, runAddOns);

    c.getBoolean(_USR_TEST1, test1);
    c.getInteger(_USR_MAC_CHILD_DIALOG_TYPE, macChildDialogType);
#ifdef SIM_WITH_GUI
#ifdef MAC_SIM
    if (macChildDialogType <= 0)
    { // Qt::Tool
        VDialog::dialogStyle = QT_MODELESS_DLG_STYLE;
    }
    else
    { // Qt::Dialog
        VDialog::dialogStyle = Qt::Dialog;
    }
#else
    VDialog::dialogStyle = QT_MODELESS_DLG_STYLE;
#endif
#endif
    c.getString(_USR_ADDITIONAL_LUA_PATH, additionalLuaPath);
    c.getString(_USR_ADDITIONAL_PYTHON_PATH, additionalPythonPath);
    c.getString(_USR_DEFAULT_PYTHON, defaultPython);
    c.getBoolean(_USR_EXEC_UNSAFE, execUnsafe);
    c.getBoolean(_USR_EXEC_UNSAFE_EXT, execUnsafeExt);
    c.getInteger(_USR_DESKTOP_RECORDING_INDEX, desktopRecordingIndex);
    c.getInteger(_USR_DESKTOP_RECORDING_WIDTH, desktopRecordingWidth);
    c.getBoolean(_USR_FORCE_BUG_FIX_REL_30002, forceBugFix_rel30002);
    c.getString(_USR_EXTERNAL_SCRIPT_EDITOR, externalScriptEditor);
    c.getInteger(_USR_XML_EXPORT_SPLIT_SIZE, xmlExportSplitSize);
    c.getBoolean(_USR_XML_EXPORT_KNOWN_FORMATS, xmlExportKnownFormats);

    // License section:
    // *****************************
    c.getString(_USR_LICENSE_LITE, license_lite);
    c.getString(_USR_LICENSE_EDU, license_edu);
    c.getString(_USR_LICENSE_PRO, license_pro);
    c.getString(_USR_LICENSE, license);
#ifdef IS_LITE
    if (license_lite != "")
        license = license_lite;
    license_lite = license;
#endif
#ifdef IS_EDU
    if (license_edu != "")
        license = license_edu;
    license_edu = license;
#endif
#ifdef IS_PRO
    if (license_pro != "")
        license = license_pro;
    license_pro = license;
#endif
    std::string npLicense;
    if (App::getAppNamedParam("license", npLicense))
        license = npLicense;
    c.getString(_USR_LICENSE_ENDPOINT, licenseEndpoint);
    c.getBoolean(_USR_KEEP_DONGLE_OPEN, keepDongleOpen);
    c.getBoolean(_USR_FLOAT_LICENSE_ENABLED, floatingLicenseEnabled);
    c.getString(_USR_FLOAT_LICENSE_SERVER_ADDRESS, floatingLicenseServer);
    c.getInteger(_USR_FLOAT_LICENSE_SERVER_PORT, floatingLicensePort);

    // Other section:
    // *****************************
    c.getString(_USR_MEM, mem);

    std::string tmp("user settings file is ");
    tmp += file;
    App::logMsg(sim_verbosity_loadinfos | sim_verbosity_onlyterminal, tmp.c_str());
}
