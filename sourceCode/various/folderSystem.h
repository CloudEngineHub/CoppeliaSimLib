#pragma once

#include <QTemporaryDir>

class CFolderSystem
{
  public:
    CFolderSystem();
    virtual ~CFolderSystem();

    static std::string getPathFromFull(const char* full); // no final backslash or slash is returned
    static std::string getNameFromFull(const char* full);
    static std::string getUserSettingsPath();

    std::string getExecutablePath() const;
    std::string getAddOnPath() const;
    std::string getInterpretersRootPath() const;
    std::string getAutoSavedScenesPath() const;
    std::string getAutoSavedScenesContainingPath() const;
    std::string getSystemPath() const;
    std::string getResourcesPath() const;
    std::string getScenesDefaultPath() const;
    std::string getModelsDefaultPath() const;

    std::string getScenesPath() const;
    void setScenesPath(const char* path);
    std::string getModelsPath() const;
    void setModelsPath(const char* path);
    std::string getImportExportPath() const;
    void setImportExportPath(const char* path);
    std::string getTexturesPath() const;
    void setTexturesPath(const char* path);
    std::string getVideosPath() const;
    void setVideosPath(const char* path);
    std::string getOtherFilesPath() const;
    void setOtherFilesPath(const char* path);
    // std::string getAppDataPath() const;
    std::string getTempDataPath() const;
    std::string getSceneTempDataPath() const;
    std::string getLuaPath() const;
    std::string getPythonPath() const;
    std::string getMujocoPath() const;

  private:
    QTemporaryDir* _tempDir;
    std::string _executablePath;
    std::string _systemPath;
    std::string _addOnPath;
    std::string _resourcesPath;
    std::string _scenesPath;
    std::string _modelsPath;
    std::string _importExportPath;
    std::string _texturesPath;
    std::string _videosPath;
    std::string _otherFilesPath;
    std::string _appDataPath;
    std::string _tempDataPath;
    std::string _scenesDefaultPath;
    std::string _modelsDefaultPath;
    std::string _mujocoPath;
    std::string _autoSavedScenesContainingPath;
    std::string _autoSavedScenesDir;
};
