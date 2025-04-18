#pragma once

#include <string>

// FULLY STATIC CLASS
class CSimFlavor
{
  public:
    static int ver();
    static void getAboutStr(std::string& title, std::string& txt);
    static int handleReadOpenFile(int f, char* b);
    static void run(int w);
    static int getIntVal(int w);
    static int getIntVal_2int(int w, int v1, int v2);
    static int getIntVal_str(int w, const char* str);
    static bool getBoolVal(int w);
    static bool getBoolVal_str(int w, const char* str);
    static std::string getStringVal(int w);
    static std::string getStringVal_int(int w, int v);
};
