#include <simInternal.h>
#include <folderSystem.h>
#include <vFile.h>
#include <global.h>
#include <vVarious.h>
#include <app.h>
#include <simFlavor.h>
#include <vFileFinder.h>
#include <vDateTime.h>
#include <utils.h>
#include <filesystem>
#ifndef __cpp_lib_filesystem // macOS 10.13 does not support XCode >=11 which is required for that
#include <ftw.h>
#include <unistd.h>
#endif
#include <QStandardPaths>

CFolderSystem::CFolderSystem()
{
    _executablePath = App::getApplicationDir();
#ifdef MAC_SIM
    _resourcesPath = _executablePath + "/../Resources";
    QDir ad(_resourcesPath.c_str());
    _resourcesPath = ad.absolutePath().toStdString();
#else
    _resourcesPath = _executablePath;
#endif
    _systemPath = _resourcesPath + "/system";
    _scenesPath = _resourcesPath + "/scenes";
    _modelsPath = _resourcesPath + "/models";
    _importExportPath = _resourcesPath + "/cadFiles";
    _addOnPath = _resourcesPath + "/addOns";
    _videosPath = _resourcesPath;
    _otherFilesPath = _resourcesPath;
    _scenesDefaultPath = _scenesPath;
    _modelsDefaultPath = _modelsPath;
    if (App::userSettings->defaultDirectoryForScenes.length() != 0)
        setScenesPath(App::userSettings->defaultDirectoryForScenes.c_str());
    if (App::userSettings->defaultDirectoryForModels.length() != 0)
        setModelsPath(App::userSettings->defaultDirectoryForModels.c_str());
    if (App::userSettings->defaultDirectoryForImportExport.length() != 0)
        setImportExportPath(App::userSettings->defaultDirectoryForImportExport.c_str());
    if (App::userSettings->defaultDirectoryForMiscFiles.length() != 0)
        setOtherFilesPath(App::userSettings->defaultDirectoryForMiscFiles.c_str());

    _tempDir = new QTemporaryDir();
    _tempDir->setAutoRemove(true);
    if (_tempDir->isValid())
        _tempDataPath = _tempDir->path().toStdString().c_str();
    if (_tempDataPath.size() == 0)
    {
        _tempDataPath = _executablePath + "/tmp";
        if (!VFile::doesFolderExist(_tempDataPath.c_str()))
            VFile::createFolder(_tempDataPath.c_str());
    }

    _mujocoPath = _tempDataPath + "/mujoco";
    if (!VFile::doesFolderExist(_mujocoPath.c_str()))
        VFile::createFolder(_mujocoPath.c_str());

    QString s(QStandardPaths::locate(QStandardPaths::AppDataLocation, "CoppeliaSim", QStandardPaths::LocateDirectory));
    if (s.length() == 0)
    {
        QString wl(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));
        QDir(wl).mkdir("CoppeliaSim");
    }
    /*
    _appDataPath=QStandardPaths::writableLocation(QStandardPaths::AppDataLocation).toStdString()+"/CoppeliaSim";

    if (_appDataPath.size()==0)
    {
        _appDataPath=_executablePath+"/app";
        if (!VFile::doesFolderExist(_appDataPath.c_str()))
            VFile::createFolder(_appDataPath.c_str());
    }
    */

    _autoSavedScenesContainingPath = getUserSettingsPath() + "/autoSavedScenes";
    if (!VFile::doesFolderExist(_autoSavedScenesContainingPath.c_str()))
        VFile::createFolder(_autoSavedScenesContainingPath.c_str());
    // First remove old folders:
    VFileFinder finder;
    finder.searchFolders(_autoSavedScenesContainingPath.c_str());
    int index = 0;
    SFileOrFolder* foundItem = finder.getFoundItem(index++);
    while (foundItem != nullptr)
    {
        if ((foundItem->name != ".") && (foundItem->name != "..") &&
            (foundItem->lastWriteTime + 3600 * 24 * 2 < VDateTime::getSecondsSince1970())) // 2 days
            std::filesystem::remove_all(foundItem->path.c_str());
        foundItem = finder.getFoundItem(index++);
    }
    // create a new folder:
    QDateTime now = QDateTime::currentDateTime();
    _autoSavedScenesDir = now.toString("yyyy-MM-dd-HH-mm-").toStdString();
    _autoSavedScenesDir += utils::generateUniqueAlphaNumericString();
    VFile::createFolder((_autoSavedScenesContainingPath + "/" + _autoSavedScenesDir).c_str());
}

#ifndef __cpp_lib_filesystem // macOS 10.13 does not support XCode >=11 which is required for that
int unlinkCb(const char* fpath, const struct stat* sb, int typeflag, struct FTW* ftwbuf)
{
    int rv = remove(fpath);
    return rv;
}

int rmrf(const char* path)
{
    return nftw(path, unlinkCb, 64, FTW_DEPTH | FTW_PHYS);
}
#endif

CFolderSystem::~CFolderSystem()
{
    if (_tempDir->isValid())
        delete _tempDir;
    _tempDataPath.clear();
    if (_tempDataPath.size() > 0)
    {
#ifdef __cpp_lib_filesystem // macOS 10.13 does not support XCode >=11 which is required for that
        try
        {
            std::filesystem::remove_all(_tempDataPath.c_str());
        }
        catch (std::filesystem::filesystem_error const& e)
        {
        }
#else
        rmrf(_tempDataPath.c_str());
#endif
    }
}

std::string CFolderSystem::getPathFromFull(const char* full)
{ // no final slash is returned
    return (VVarious::splitPath_path(full));
}

std::string CFolderSystem::getNameFromFull(const char* full)
{
    return (VVarious::splitPath_fileBase(full));
}

std::string CFolderSystem::getExecutablePath() const
{
    return (_executablePath);
}

std::string CFolderSystem::getAddOnPath() const
{
    return (_addOnPath);
}

std::string CFolderSystem::getInterpretersRootPath() const
{
    return (_resourcesPath);
}

std::string CFolderSystem::getSystemPath() const
{
    return (_systemPath);
}

std::string CFolderSystem::getAutoSavedScenesPath() const
{
    return (_autoSavedScenesContainingPath + "/" + _autoSavedScenesDir);
}

std::string CFolderSystem::getAutoSavedScenesContainingPath() const
{
    return (_autoSavedScenesContainingPath);
}

std::string CFolderSystem::getResourcesPath() const
{
    return (_resourcesPath);
}

std::string CFolderSystem::getScenesDefaultPath() const
{
    return (_scenesDefaultPath);
}

std::string CFolderSystem::getModelsDefaultPath() const
{
    return (_modelsDefaultPath);
}

std::string CFolderSystem::getScenesPath() const
{
    return (_scenesPath);
}

void CFolderSystem::setScenesPath(const char* path)
{
    std::string pp(path);
    VVarious::removePathFinalSlashOrBackslash(pp);
    bool diff = (_scenesPath != pp);
    if (diff)
    {
        _scenesPath = pp;
        if ((App::worldContainer != nullptr) && App::worldContainer->getEventsEnabled())
        {
            const char* cmd = propApp_sceneDir.name;
            CCbor* ev = App::worldContainer->createObjectChangedEvent(sim_handle_app, cmd, true);
            ev->appendKeyText(cmd, _scenesPath.c_str());
            App::worldContainer->pushEvent();
        }
    }
}

std::string CFolderSystem::getModelsPath() const
{
    return (_modelsPath);
}

void CFolderSystem::setModelsPath(const char* path)
{
    std::string pp(path);
    VVarious::removePathFinalSlashOrBackslash(pp);
    bool diff = (_modelsPath != pp);
    if (diff)
    {
        _modelsPath = pp;
        if ((App::worldContainer != nullptr) && App::worldContainer->getEventsEnabled())
        {
            const char* cmd = propApp_modelDir.name;
            CCbor* ev = App::worldContainer->createObjectChangedEvent(sim_handle_app, cmd, true);
            ev->appendKeyText(cmd, _modelsPath.c_str());
            App::worldContainer->pushEvent();
        }
    }
}

std::string CFolderSystem::getImportExportPath() const
{
    return (_importExportPath);
}

void CFolderSystem::setImportExportPath(const char* path)
{
    std::string pp(path);
    VVarious::removePathFinalSlashOrBackslash(pp);
    bool diff = (_importExportPath != pp);
    if (diff)
    {
        _importExportPath = pp;
        if ((App::worldContainer != nullptr) && App::worldContainer->getEventsEnabled())
        {
            const char* cmd = propApp_importExportDir.name;
            CCbor* ev = App::worldContainer->createObjectChangedEvent(sim_handle_app, cmd, true);
            ev->appendKeyText(cmd, _importExportPath.c_str());
            App::worldContainer->pushEvent();
        }
    }
}

std::string CFolderSystem::getTexturesPath() const
{
    return (_texturesPath);
}

std::string CFolderSystem::getLuaPath() const
{
    return (_resourcesPath + "/lua");
}

std::string CFolderSystem::getPythonPath() const
{
    return (_resourcesPath + "/python");
}

std::string CFolderSystem::getMujocoPath() const
{
    return (_mujocoPath);
}

std::string CFolderSystem::getUserSettingsPath()
{ // static since needed before construction
    static std::string userSettingsFolder;
    if (userSettingsFolder.size() == 0)
    {
        std::string usrSet("CoppeliaSim");
        char* ps = std::getenv("COPPELIASIM_USER_SETTINGS_FOLDER_SUFFIX");
        if (ps != nullptr)
            usrSet += ps;
        const char* home = std::getenv("HOME");
#ifdef WIN_SIM
        const char* appData = std::getenv("appdata");
        if (appData != nullptr)
            userSettingsFolder = std::string(appData) + "/" + usrSet;
#endif
#ifdef LIN_SIM
        const char* xdghome = std::getenv("XDG_CONFIG_HOME"); // takes precedence
        if ((xdghome != nullptr) && (strlen(xdghome) != 0))
            home = xdghome;
        if ((home != nullptr) && (strlen(home) != 0))
            userSettingsFolder = std::string(home) + "/." + usrSet;
#endif
#ifdef MAC_SIM
        if (home != nullptr)
            userSettingsFolder = std::string(home) + "/." + usrSet;
#endif
        if (userSettingsFolder.size() == 0)
        { // fallback
#ifdef MAC_SIM
            userSettingsFolder = App::getApplicationDir() + "/../Resources/system";
#else
            userSettingsFolder = App::getApplicationDir() + "/system";
#endif
        }
    }
    return (userSettingsFolder);
}

void CFolderSystem::setTexturesPath(const char* path)
{
    _texturesPath = path;
    VVarious::removePathFinalSlashOrBackslash(_texturesPath);
}

std::string CFolderSystem::getVideosPath() const
{
    return (_videosPath);
}

void CFolderSystem::setVideosPath(const char* path)
{
    _videosPath = path;
    VVarious::removePathFinalSlashOrBackslash(_videosPath);
}

std::string CFolderSystem::getOtherFilesPath() const
{
    return (_otherFilesPath);
}

void CFolderSystem::setOtherFilesPath(const char* path)
{
    _otherFilesPath = path;
    VVarious::removePathFinalSlashOrBackslash(_otherFilesPath);
}

/*
std::string CFolderSystem::getAppDataPath() const
{
    return(_appDataPath);
}
*/

std::string CFolderSystem::getTempDataPath() const
{
    return (_tempDataPath);
}

std::string CFolderSystem::getSceneTempDataPath() const
{
    std::string folder =
        _tempDataPath + "/sceneData" + std::to_string(App::currentWorld->environment->getSceneUniqueID());
    if (!VFile::doesFolderExist(folder.c_str()))
        VFile::createFolder(folder.c_str());
    return (folder);
}
