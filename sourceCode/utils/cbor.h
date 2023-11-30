#pragma once

#include <vector>
#include <string>
#include <map>
#include <simLib/simTypes.h>

struct SEventInf
{
    size_t pos;
    std::string eventId;
};

class CCbor
{
  public:
    CCbor(const std::string *initBuff = nullptr, int options = 0);
    virtual ~CCbor();

    void swapWithEmptyBuffer(std::vector<unsigned char> *emptyBuff);
    bool isText(const char *v, size_t l);

    void appendInt(long long int v);
    void appendUCharArray(const unsigned char *v, size_t cnt);
    void appendIntArray(const int *v, size_t cnt);
    void appendIntArray(const long long int *v, size_t cnt);
    void appendFloat(float v);
    void appendFloatArray(const float *v, size_t cnt);
    void appendDouble(double v);
    void appendDoubleArray(const double *v, size_t cnt);
    void appendNull();
    void appendBool(bool v);
    void appendBuff(const unsigned char *v, size_t l);
    void appendString(const char *v, int l = -1);

    void appendKeyInt(const char *key, long long int v);
    void appendKeyUCharArray(const char *key, const unsigned char *v, size_t cnt);
    void appendKeyIntArray(const char *key, const int *v, size_t cnt);
    void appendKeyIntArray(const char *key, const long long int *v, size_t cnt);
    void appendKeyFloat(const char *key, float v);
    void appendKeyFloatArray(const char *key, const float *v, size_t cnt);
    void appendKeyDouble(const char *key, double v);
    void appendKeyDoubleArray(const char *key, const double *v, size_t cnt);
    void appendKeyNull(const char *key);
    void appendKeyBool(const char *key, bool v);
    void appendKeyBuff(const char *key, const unsigned char *v, size_t l);
    void appendKeyString(const char *key, const char *v, int l = -1);

    void openArray();
    void openKeyArray(const char *key);
    void openMap();
    void openKeyMap(const char *key);
    void closeArrayOrMap();

    void appendLuaString(const std::string &v);
    void appendRaw(const unsigned char *v, size_t l);

    void createEvent(const char *event, const char *fieldName, const char *objType, long long int uid, int handle,
                     bool mergeable, bool openDataField = true);
    void pushEvent();
    long long int finalizeEvents(long long int nextSeq, bool seqChanges);
    size_t getEventCnt() const;
    size_t getEventDepth() const;

    void clear();

    std::string getBuff() const;
    const unsigned char *getBuff(size_t &l) const;

  protected:
    void _appendItemTypeAndLength(unsigned char t, long long int l);
    void _adjustEventSeq(size_t pos, long long int endSeq);

    std::vector<unsigned char> _buff;
    int _options; // bit0: treat doubles as float

    size_t _eventDepth; // nb of array/map closes needed
    bool _eventOpen;    // true when not yet pushed
    size_t _discardableEventCnt;
    std::vector<SEventInf> _eventInfos;
    std::map<std::string, size_t> _mergeableEventIds;
};
