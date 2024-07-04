#pragma once

#include <vArchive.h>
#include <vMutex.h>

class CPersistentDataContainer
{
  public:
    CPersistentDataContainer();
    CPersistentDataContainer(const char *filename, const char *customFolder = nullptr);
    virtual ~CPersistentDataContainer();

    int removeAllData();

    void initializeWithDataFromFile();

    void clearData(const char *dataName, bool toFile);
    void writeData(const char *dataName, const std::string &value, bool toFile, bool allowEmptyString);
    bool readData(const char *dataName, std::string &value);
    int hasData(const char* dataName, bool checkAllTypes, int* dataSize = nullptr);
    bool getPropertyName(int& index, std::string& pName);
    int getAllDataNames(std::vector<std::string> &names);

  protected:
    void _writeData(const char *dataName, const std::string &value, bool allowEmptyString);
    int _getDataIndex(const char *dataName);

    void _readFromFile(std::vector<std::string> &dataNames, std::vector<std::string> &dataValues);
    void _writeToFile(std::vector<std::string> &dataNames, std::vector<std::string> &dataValues);
    void _serialize(VArchive &ar, std::vector<std::string> &dataNames, std::vector<std::string> &dataValues);

    std::string _filename;
    std::string _customFolder;
    std::vector<std::string> _dataNames;
    std::vector<std::string> _dataValues;
    VMutex _eventMutex;
};
