#include <customData_old.h>
#include <base64.h>
#include <utils.h>
#include <tt.h>

CCustomData_old::CCustomData_old()
{
}

CCustomData_old::~CCustomData_old()
{ // beware, the current world could be nullptr
    removeAllData();
}

void CCustomData_old::serializeData(CSer& ar, const char* objectName, int scriptHandle)
{
    if (ar.isBinary())
    {
        if (ar.isStoring())
        { // Storing
            for (unsigned int i = 0; i < dat.size(); i++)
            {
                ar.storeDataName("Dat");
                ar << head[i];
                ar << len[i];
                for (int j = 0; j < len[i]; j++)
                    ar << dat[i][j];
                ar.flush();
            }
            ar.storeDataName(SER_END_OF_OBJECT);
        }
        else
        { // Loading
            removeAllData();
            int byteQuantity;
            std::string theName = "";
            while (theName.compare(SER_END_OF_OBJECT) != 0)
            {
                theName = ar.readDataName();
                if (theName.compare(SER_END_OF_OBJECT) != 0)
                {
                    bool noHit = true;
                    if (theName == "Dat")
                    {
                        noHit = false;
                        ar >> byteQuantity;
                        int e;
                        int l;
                        ar >> e;
                        ar >> l;
                        char* dd = new char[l];
                        for (int i = 0; i < l; i++)
                            ar >> dd[i];
                        dat.push_back(dd);
                        len.push_back(l);
                        head.push_back(e);
                    }
                    if (noHit)
                        ar.loadUnknownData();
                }
            }
        }
    }
    else
    {
        if (ar.isStoring())
        {
            int totSize = 0;
            for (size_t i = 0; i < dat.size(); i++)
                totSize += len[i];
            if (ar.xmlSaveDataInline(totSize))
            {
                for (size_t i = 0; i < dat.size(); i++)
                {
                    ar.xmlPushNewNode("data");
                    ar.xmlAddNode_int("header", head[i]);
                    ar.xmlAddNode_int("length", len[i]);
                    if (len[i] > 0)
                    {
                        std::string str(base64_encode((unsigned char*)&dat[i][0], len[i]));
                        ar.xmlAddNode_string("data_base64Coded", str.c_str());
                    }
                    ar.xmlPopNode();
                }
            }
            else
            {
                CSer* serObj = nullptr;
                if (objectName != nullptr)
                    serObj = ar.xmlAddNode_binFile("file", (std::string("objectCustomData_") + objectName).c_str());
                else
                {
                    if (scriptHandle != -1)
                        serObj = ar.xmlAddNode_binFile(
                            "file",
                            (std::string("scriptCustomData_") + utils::getIntString(false, scriptHandle)).c_str());
                    else
                        serObj = ar.xmlAddNode_binFile("file", "sceneCustomData");
                }
                serObj[0] << int(dat.size());
                for (size_t i = 0; i < dat.size(); i++)
                {
                    serObj[0] << head[i];
                    serObj[0] << len[i];
                    for (int j = 0; j < len[i]; j++)
                        serObj[0] << dat[i][j];
                }
                serObj->flush();
                serObj->writeClose();
                delete serObj;
            }
        }
        else
        {
            CSer* serObj = ar.xmlGetNode_binFile("file", false);
            if (serObj == nullptr)
            {
                if (ar.xmlPushChildNode("data", false))
                {
                    while (true)
                    {
                        int header, l;
                        ar.xmlGetNode_int("header", header);
                        ar.xmlGetNode_int("length", l);
                        std::string data;
                        if (l > 0)
                        {
                            ar.xmlGetNode_string("data_base64Coded", data);
                            data = base64_decode(data);
                            setData(header, &data[0], l);
                        }
                        else
                            setData(header, nullptr, l);
                        if (!ar.xmlPushSiblingNode("data", false))
                            break;
                    }
                    ar.xmlPopNode();
                }
            }
            else
            {
                int s;
                serObj[0] >> s;
                for (size_t i = 0; i < size_t(s); i++)
                {
                    int e;
                    int l;
                    serObj[0] >> e;
                    serObj[0] >> l;
                    char* dd = new char[l];
                    for (int i = 0; i < l; i++)
                        serObj[0] >> dd[i];
                    dat.push_back(dd);
                    len.push_back(l);
                    head.push_back(e);
                }
                serObj->readClose();
                delete serObj;
            }
        }
    }
}

void CCustomData_old::initNewFormat(CCustomData& newObj, bool objectData) const
{
    for (size_t i = 0; i < head.size(); i++)
    {
        int h = head[i];
        int l = len[i];
        char* c = dat[i];
        if (h == 356248756)
        {
            std::vector<char> buff(c, c + l);
            std::vector<std::string> tags;
            _extractCustomDataTagsFromBuffer(buff, tags);
            for (size_t j = 0; j < tags.size(); j++)
            {
                std::string data;
                _extractCustomDataFromBuffer(buff, tags[j].c_str(), data);
                if (data.size() > 0)
                    newObj.setData(tags[j].c_str(), data.c_str(), data.size(), false);
            }
        }
        else
        {
            std::string tag;
            if (objectData)
                tag = "_oldObjectCustomData_";
            else
                tag = "_oldSceneCustomData_";
            tag += std::to_string(h);
            tag += "_";
            newObj.setData(tag.c_str(), c, size_t(l), false);
        }
    }
}

CCustomData_old* CCustomData_old::copyYourself()
{
    CCustomData_old* retVal = new CCustomData_old();
    for (unsigned int i = 0; i < dat.size(); i++)
    {
        char* d = new char[len[i]];
        retVal->dat.push_back(d);
        retVal->len.push_back(len[i]);
        retVal->head.push_back(head[i]);
        for (int j = 0; j < len[i]; j++)
            d[j] = dat[i][j];
    }
    return (retVal);
}

void CCustomData_old::setData(int header, const char* data, int datLen)
{
    removeData(header);
    if ((data == nullptr) || (datLen == 0)) // Following 2 lines since 2010/03/04
        return;
    char* newData = new char[datLen];
    for (int i = 0; i < datLen; i++)
        newData[i] = data[i];
    dat.push_back(newData);
    len.push_back(datLen);
    head.push_back(header);
}

int CCustomData_old::getDataLength(int header)
{
    if (header == -1)
    { // new since 19/09/2011
        // Here we want the length of the arry that contains all the header numbers
        return ((int)head.size() * sizeof(int));
    }
    else
    {
        for (unsigned int i = 0; i < dat.size(); i++)
        {
            if (head[i] == header)
                return (len[i]);
        }
    }
    return (0);
}

void CCustomData_old::getData(int header, char* data) const
{
    if (header == -1)
    { // new since 19/09/2011
        // Here we want the arry that contains all the header numbers
        for (unsigned int i = 0; i < head.size(); i++)
            ((int*)data)[i] = head[i];
    }
    else
    {
        for (unsigned int i = 0; i < dat.size(); i++)
        {
            if (head[i] == header)
            {
                for (int j = 0; j < len[i]; j++)
                    data[j] = dat[i][j];
                break;
            }
        }
    }
}

bool CCustomData_old::getHeader(int index, int& header) const
{
    if (index >= int(head.size()))
        return (false);
    header = head[index];
    return (true);
}

void CCustomData_old::removeData(int header)
{
    for (unsigned int i = 0; i < dat.size(); i++)
    {
        if (head[i] == header)
        {
            delete[] dat[i];
            dat.erase(dat.begin() + i);
            len.erase(len.begin() + i);
            head.erase(head.begin() + i);
            break;
        }
    }
}

void CCustomData_old::removeAllData()
{
    for (unsigned int i = 0; i < dat.size(); i++)
        delete[] dat[i];
    dat.clear();
    len.clear();
    head.clear();
}

void CCustomData_old::_extractCustomDataFromBuffer(std::vector<char>& buffer, const char* dataName,
                                                   std::string& extractedData)
{
    extractedData.clear();
    int off = 0;
    while (off + 8 < int(buffer.size()))
    {
        int sizeIncr = ((int*)((&buffer[0]) + off))[0];
        int nameLength = ((int*)((&buffer[0]) + off))[1];
        std::string datName(((&buffer[0]) + off) + 4 + 4);
        if (datName.compare(dataName) == 0)
        { // ok, we have the correct data here
            int datLength = sizeIncr - 4 - 4 - nameLength;
            extractedData.resize(datLength);
            for (int i = 0; i < datLength; i++)
                extractedData[i] = buffer[off + 4 + 4 + nameLength + i];
            buffer.erase(buffer.begin() + off, buffer.begin() + off + sizeIncr);
            return;
        }
        // continue searching
        off += sizeIncr;
    }
}

void CCustomData_old::_extractCustomDataTagsFromBuffer(std::vector<char>& buffer, std::vector<std::string>& tags)
{
    int off = 0;
    while (off + 8 < int(buffer.size()))
    {
        int sizeIncr = ((int*)((&buffer[0]) + off))[0];
        // int nameLength=((int*)((&buffer[0])+off))[1];
        std::string datName(((&buffer[0]) + off) + 4 + 4);
        tags.push_back(datName);
        off += sizeIncr;
    }
}
