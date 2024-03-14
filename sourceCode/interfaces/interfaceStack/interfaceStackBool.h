#pragma once

#include <interfaceStackObject.h>

class CInterfaceStackBool : public CInterfaceStackObject
{
  public:
    CInterfaceStackBool(bool theValue);
    virtual ~CInterfaceStackBool();

    CInterfaceStackObject *copyYourself() const;
    void printContent(int spaces, std::string &buffer) const;
    std::string getObjectData() const;
    void addCborObjectData(CCbor *cborObj) const;
    unsigned int createFromData(const char *data, unsigned char version);
    static bool checkCreateFromData(const char *data, unsigned int &w, unsigned int l, unsigned char version);

    bool getValue() const;

  protected:
    bool _value;
};
