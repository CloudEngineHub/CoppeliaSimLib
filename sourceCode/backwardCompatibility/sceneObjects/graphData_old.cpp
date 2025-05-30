#include <simInternal.h>
#include <graphData_old.h>
#include <global.h>
#include <graph.h>
#include <tt.h>
#include <proximitySensor.h>
#include <jointObject.h>
#include <app.h>
#include <graphingRoutines_old.h>
#ifdef SIM_WITH_GUI
#include <oGL.h>
#endif

CGraphData_old::CGraphData_old()
{
    addCoeff = 0.0;
    zoomFactor = 1.0;
    _lifeID = -1;
    _movingAverageCount = 1; // no moving average!
    _derivativeIntegralAndCumulative = sim_stream_transf_raw;
}

CGraphData_old::CGraphData_old(int theDataType, int theDataObjectID, int theDataObjectAuxID)
{
    dataType = theDataType;
    dataObjectID = theDataObjectID;
    dataObjectAuxID = theDataObjectAuxID;
    linkPoints = true;
    label = true;
    visible = true;
    identifier = -1;
    _floatData.clear();
    _transformedFloatData.clear();
    _floatDataValidFlags.clear();
    _transformedFloatDataValidFlags.clear();
    ambientColor[0] = 1.0;
    ambientColor[1] = ambientColor[2] = 0.0;
    zoomFactor = 1.0;
    addCoeff = 0.0;
    _derivativeIntegralAndCumulative = sim_stream_transf_raw;
    _movingAverageCount = 1; // no moving average!
    name = "Data";
}

CGraphData_old::~CGraphData_old()
{
    _floatData.clear();
    _transformedFloatData.clear();
    _floatDataValidFlags.clear();
    _transformedFloatDataValidFlags.clear();
}

void CGraphData_old::setLabel(bool l)
{
    label = l;
}

void CGraphData_old::setMovingAverageCount(int c)
{
    c = tt::getLimitedInt(1, 200, c);
    _movingAverageCount = c;
}

int CGraphData_old::getMovingAverageCount() const
{
    return (_movingAverageCount);
}

void CGraphData_old::setDerivativeIntegralAndCumulative(int val)
{
    _derivativeIntegralAndCumulative = val;
    resetData((int)_floatData.size());
}

int CGraphData_old::getDerivativeIntegralAndCumulative() const
{
    return (_derivativeIntegralAndCumulative);
}

bool CGraphData_old::getLabel() const
{
    return (label);
}

bool CGraphData_old::getLinkPoints() const
{
    return (linkPoints);
}

int CGraphData_old::getIdentifier() const
{
    return (identifier);
}

int CGraphData_old::getDataType() const
{
    return (dataType);
}
int CGraphData_old::getDataObjectID() const
{
    return (dataObjectID);
}
int CGraphData_old::getDataObjectAuxID() const
{
    return (dataObjectAuxID);
}

double CGraphData_old::getZoomFactor() const
{
    return (zoomFactor);
}

double CGraphData_old::getAddCoeff() const
{
    return (addCoeff);
}

bool CGraphData_old::getVisible() const
{
    return (visible);
}

void CGraphData_old::setLinkPoints(bool l)
{
    linkPoints = l;
}
void CGraphData_old::setVisible(bool v)
{
    visible = v;
}

void CGraphData_old::setIdentifier(int newIdentifier)
{
    identifier = newIdentifier;
}
void CGraphData_old::setZoomFactor(double newZoomFactor)
{
    tt::limitValue(-100000000000.0, 100000000000.0, newZoomFactor);
    zoomFactor = newZoomFactor;
}
void CGraphData_old::setAddCoeff(double newCoeff)
{
    tt::limitValue(-100000000000.0, 100000000000.0, newCoeff);
    addCoeff = newCoeff;
}
void CGraphData_old::setDataObjectID(int newID)
{
    dataObjectID = newID;
}
void CGraphData_old::setDataObjectAuxID(int newID)
{
    dataObjectAuxID = newID;
}
void CGraphData_old::setName(std::string theName)
{
    name = theName;
}
std::string CGraphData_old::getName() const
{
    return (name);
}

void CGraphData_old::performObjectLoadingMapping(const std::map<int, int>* map)
{
    if ((dataType > GRAPH_SCENEOBJECT_START) && (dataType < GRAPH_SCENEOBJECT_END))
        dataObjectID = CWorld::getLoadingMapping(map, dataObjectID);
}
void CGraphData_old::performCollisionLoadingMapping(const std::map<int, int>* map)
{
    if ((dataType > GRAPH_COLLISION_START) && (dataType < GRAPH_COLLISION_END))
        dataObjectID = CWorld::getLoadingMapping(map, dataObjectID);
}
void CGraphData_old::performDistanceLoadingMapping(const std::map<int, int>* map)
{
    if ((dataType > GRAPH_DISTANCE_START) && (dataType < GRAPH_DISTANCE_END))
        dataObjectID = CWorld::getLoadingMapping(map, dataObjectID);
}
void CGraphData_old::performIkLoadingMapping(const std::map<int, int>* map)
{
    if ((dataType > GRAPH_IK_START) && (dataType < GRAPH_IK_END))
        dataObjectID = CWorld::getLoadingMapping(map, dataObjectID);
}

bool CGraphData_old::announceObjectWillBeErased(int objID, bool copyBuffer)
{ // This routine can be called for objCont-objects, but also for objects
    // in the copy-buffer!!
    // Return value true means this CGraphData_old object needs to be destroyed!
    if ((dataType > GRAPH_SCENEOBJECT_START) && (dataType < GRAPH_SCENEOBJECT_END))
    {
        if (dataObjectID == objID)
            return (true);
    }
    return (false);
}
bool CGraphData_old::announceCollisionWillBeErased(int collisionID, bool copyBuffer)
{ // This routine can be called for objCont-objects, but also for objects
    // in the copy-buffer!! So never make use of any
    // 'ct::objCont->getObject(id)'-call or similar
    // Return value true means this CGraphData_old object needs to be destroyed!
    if ((dataType > GRAPH_COLLISION_START) && (dataType < GRAPH_COLLISION_END))
    {
        if (dataObjectID == collisionID)
            return (true);
    }
    return (false);
}
bool CGraphData_old::announceDistanceWillBeErased(int distanceID, bool copyBuffer)
{ // This routine can be called for objCont-objects, but also for objects
    // in the copy-buffer!! So never make use of any
    // 'ct::objCont->getObject(id)'-call or similar
    // Return value true means this CGraphData_old object needs to be destroyed!
    if ((dataType > GRAPH_DISTANCE_START) && (dataType < GRAPH_DISTANCE_END))
    {
        if (dataObjectID == distanceID)
            return (true);
    }
    return (false);
}

bool CGraphData_old::announceIkObjectWillBeErased(int ikGroupID, bool copyBuffer)
{
    if ((dataType > GRAPH_IK_START) && (dataType < GRAPH_IK_END))
    {
        if (dataObjectID == ikGroupID)
            return (true);
    }
    return (false);
}

void CGraphData_old::setValueDirect(int absIndex, double theValue, bool firstValue, bool cyclic, double range,
                                    const std::vector<double>& times)
{
    _floatData[absIndex] = theValue;
    _floatDataValidFlags[absIndex / 8] |= (1 << (absIndex & 7)); // valid data
    if (firstValue)
    { // this is the very first point
        if (_derivativeIntegralAndCumulative == sim_stream_transf_raw)
        {
            _transformedFloatData[absIndex] = _floatData[absIndex];
            _transformedFloatDataValidFlags[absIndex / 8] |= (1 << (absIndex & 7)); // valid data
        }
        if (_derivativeIntegralAndCumulative == sim_stream_transf_derivative)
        { // invalid data
            _transformedFloatData[absIndex] = 0.0;
            _transformedFloatDataValidFlags[absIndex / 8] &= 255 - (1 << (absIndex & 7)); // invalid data
        }
        if (_derivativeIntegralAndCumulative == sim_stream_transf_integral)
        {
            _transformedFloatData[absIndex] = 0.0;
            _transformedFloatDataValidFlags[absIndex / 8] |= (1 << (absIndex & 7)); // valid data
        }
        if (_derivativeIntegralAndCumulative == sim_stream_transf_cumulative)
        {
            _transformedFloatData[absIndex] = _floatData[absIndex];
            _transformedFloatDataValidFlags[absIndex / 8] |= (1 << (absIndex & 7)); // valid data
        }
    }
    else
    { // this is not the first point
        // We get the index of previous data:
        int prevIndex = absIndex - 1;
        if (prevIndex < 0)
            prevIndex += (int)_floatData.size();
        double dt = (times[absIndex] - times[prevIndex]);
        if (_derivativeIntegralAndCumulative == sim_stream_transf_raw)
        {
            _transformedFloatData[absIndex] = _floatData[absIndex];
            _transformedFloatDataValidFlags[absIndex / 8] |= (1 << (absIndex & 7)); // valid data
        }
        if (_derivativeIntegralAndCumulative == sim_stream_transf_derivative)
        {
            if (dt == 0.0)
            { // invalid data
                _transformedFloatData[absIndex] = 0.0;
                _transformedFloatDataValidFlags[absIndex / 8] &= 255 - (1 << (absIndex & 7)); // invalid data
            }
            else
            {
                if ((_floatDataValidFlags[prevIndex / 8] & (1 << (prevIndex & 7))) != 0)
                { // previous data was valid
                    if (!cyclic)
                        _transformedFloatData[absIndex] = (_floatData[absIndex] - _floatData[prevIndex]) / dt;
                    else
                        _transformedFloatData[absIndex] =
                            (tt::getAngleMinusAlpha_range(_floatData[absIndex], _floatData[prevIndex], range)) / dt;
                    _transformedFloatDataValidFlags[absIndex / 8] |= (1 << (absIndex & 7)); // valid data
                }
                else
                { // previous data was invalid
                    _transformedFloatData[absIndex] = 0.0;
                    _transformedFloatDataValidFlags[absIndex / 8] &= 255 - (1 << (absIndex & 7)); // invalid data
                }
            }
        }
        if (_derivativeIntegralAndCumulative == sim_stream_transf_integral)
        {
            if ((_floatDataValidFlags[prevIndex / 8] & (1 << (prevIndex & 7))) != 0)
            { // previous data was valid
                if ((_transformedFloatDataValidFlags[prevIndex / 8] & (1 << (prevIndex & 7))) != 0)
                { // previous transformed data was valid
                    if (!cyclic)
                        _transformedFloatData[absIndex] = _transformedFloatData[prevIndex] +
                                                          (_floatData[prevIndex] + _floatData[absIndex]) * 0.5 * dt;
                    else
                        _transformedFloatData[absIndex] =
                            _transformedFloatData[prevIndex] +
                            (_floatData[prevIndex] +
                             tt::getAngleMinusAlpha_range(_floatData[absIndex], _floatData[prevIndex], range) * 0.5) *
                                dt;
                }
                else
                    _transformedFloatData[absIndex] = (_floatData[prevIndex] + _floatData[absIndex]) * 0.5 *
                                                      dt; // previous transformed data was invalid
            }
            else
                _transformedFloatData[absIndex] = 0.0;                              // previous data was invalid
            _transformedFloatDataValidFlags[absIndex / 8] |= (1 << (absIndex & 7)); // valid transformed data
        }
        if (_derivativeIntegralAndCumulative == sim_stream_transf_cumulative)
        {
            if ((_floatDataValidFlags[prevIndex / 8] & (1 << (prevIndex & 7))) != 0)
            { // previous data was valid
                if ((_transformedFloatDataValidFlags[prevIndex / 8] & (1 << (prevIndex & 7))) != 0)
                { // previous transformed data was valid
                    if (!cyclic)
                        _transformedFloatData[absIndex] = _transformedFloatData[prevIndex] + _floatData[absIndex];
                    else
                        _transformedFloatData[absIndex] =
                            _transformedFloatData[prevIndex] +
                            (_floatData[prevIndex] +
                             tt::getAngleMinusAlpha_range(_floatData[absIndex], _floatData[prevIndex], range));
                }
                else
                    _transformedFloatData[absIndex] =
                        _floatData[prevIndex] + _floatData[absIndex]; // previous transformed data was invalid
            }
            else
                _transformedFloatData[absIndex] = _floatData[absIndex];             // previous data was invalid
            _transformedFloatDataValidFlags[absIndex / 8] |= (1 << (absIndex & 7)); // valid transformed data
        }
    }
}

void CGraphData_old::setValue(const C7Vector* graphCTM, int absIndex, bool firstValue, bool cyclic, double range,
                              const std::vector<double>& times)
{
    bool dataIsOkay = false;
    double theValue;
    if (dataType == GRAPH_NOOBJECT_USER_DEFINED)
    {
        if (_userDataValid)
        {
            theValue = _userData;
            dataIsOkay = true;
        }
    }
    else
    {
        if (CGraphingRoutines_old::loopThroughAllAndGetDataValue(dataType, dataObjectID, theValue, graphCTM))
            dataIsOkay = true;
    }
    if (dataIsOkay)
        setValueDirect(absIndex, theValue, firstValue, cyclic, range, times);
    else
    {
        _floatData[absIndex] = 0.0;
        _transformedFloatData[absIndex] = 0.0;
        _floatDataValidFlags[absIndex / 8] &= 255 - (1 << (absIndex & 7));            // invalid data
        _transformedFloatDataValidFlags[absIndex / 8] &= 255 - (1 << (absIndex & 7)); // invalid data
    }
}

bool CGraphData_old::getValue(int absIndex, double& v) const
{
    if (getValueRaw(absIndex, v))
    {
        v = v * zoomFactor + addCoeff;
        return (true);
    }
    return (false); // invalid data
}

bool CGraphData_old::getValueRaw(int absIndex, double& v) const
{ // isValid can be null;
    v = _transformedFloatData[absIndex];
    return ((_transformedFloatDataValidFlags[absIndex / 8] & (1 << (absIndex & 7))) != 0);
}

void CGraphData_old::setUserData(double data)
{
    _userData = data;
    _userDataValid = true;
}

void CGraphData_old::clearUserData()
{
    _userDataValid = false;
}

int CGraphData_old::getDataLength()
{
    return (int(_floatData.size()));
}

void CGraphData_old::resetData(int bufferSize)
{
    _floatData.reserve(bufferSize);
    _floatData.clear();
    _transformedFloatData.reserve(bufferSize);
    _transformedFloatData.clear();
    _floatDataValidFlags.clear();
    _transformedFloatDataValidFlags.clear();
    // We fill it with the default value:
    for (int i = 0; i < bufferSize; i++)
    {
        _floatData.push_back(0.0);
        _transformedFloatData.push_back(0.0);
    }
    for (int i = 0; i < (bufferSize / 8) + 1; i++)
    {
        _floatDataValidFlags.push_back(0); // all data is invalid!
        _transformedFloatDataValidFlags.push_back(0);
    }
    clearUserData();
}

CGraphData_old* CGraphData_old::copyYourself()
{ // We copy everything, even the name and the identifier
    CGraphData_old* newObj = new CGraphData_old(dataType, dataObjectID, dataObjectAuxID);
    newObj->zoomFactor = zoomFactor;
    newObj->addCoeff = addCoeff;
    newObj->_movingAverageCount = _movingAverageCount;
    newObj->identifier = identifier;
    newObj->visible = visible;
    newObj->linkPoints = linkPoints;
    newObj->label = label;
    newObj->name = name;
    newObj->_derivativeIntegralAndCumulative = _derivativeIntegralAndCumulative;
    for (int i = 0; i < 3; i++)
        newObj->ambientColor[i] = ambientColor[i];
    newObj->_floatData.assign(_floatData.begin(), _floatData.end());
    newObj->_transformedFloatData.assign(_transformedFloatData.begin(), _transformedFloatData.end());
    newObj->_floatDataValidFlags.assign(_floatDataValidFlags.begin(), _floatDataValidFlags.end());
    newObj->_transformedFloatDataValidFlags.assign(_transformedFloatDataValidFlags.begin(),
                                                   _transformedFloatDataValidFlags.end());
    return (newObj);
}

void CGraphData_old::serialize(CSer& ar, void* it)
{
    CGraph* cg = (CGraph*)it;
    if (ar.isBinary())
    {
        if (ar.isStoring())
        { // Storing
            ar.storeDataName("Nme");
            ar << name;
            ar.flush();

            ar.storeDataName("Oid");
            ar << identifier;
            ar.flush();

            ar.storeDataName("Dt2");
            ar << dataType << dataObjectID << dataObjectAuxID;
            ar.flush();

            ar.storeDataName("Col");
            ar << ambientColor[0] << ambientColor[1] << ambientColor[2];
            ar.flush();

            ar.storeDataName("_ar");
            ar << zoomFactor << addCoeff;
            ar.flush();

            ar.storeDataName("Mac");
            ar << _movingAverageCount;
            ar.flush();

            ar.storeDataName("Dci");
            ar << _derivativeIntegralAndCumulative;
            ar.flush();

            ar.storeDataName("Pa2");
            unsigned char dummy = 0;
            dummy = dummy + 1 * visible;
            dummy = dummy + 2 * linkPoints;
            dummy = dummy + 4 * label;
            ar << dummy;
            ar.flush();

            ar.storeDataName("_t9"); // Should always come after nullValue
            for (int i = 0; i < cg->getNumberOfPoints(); i++)
            {
                int absIndex;
                cg->getAbsIndexOfPosition(i, absIndex);
                ar << _floatData[absIndex];
            }
            ar.flush();

            ar.storeDataName("_fd");
            for (int i = 0; i < cg->getNumberOfPoints(); i++)
            {
                int absIndex;
                cg->getAbsIndexOfPosition(i, absIndex);
                ar << _transformedFloatData[absIndex];
            }
            ar.flush();

            ar.storeDataName("Bla");
            for (int i = 0; i < cg->getNumberOfPoints(); i++)
            {
                int absIndex;
                cg->getAbsIndexOfPosition(i, absIndex);
                if ((_floatDataValidFlags[absIndex / 8] & (1 << (absIndex & 7))) != 0)
                    ar << (unsigned char)1;
                else
                    ar << (unsigned char)0;
            }
            ar.flush();

            ar.storeDataName("Bli");
            for (int i = 0; i < cg->getNumberOfPoints(); i++)
            {
                int absIndex;
                cg->getAbsIndexOfPosition(i, absIndex);
                if ((_transformedFloatDataValidFlags[absIndex / 8] & (1 << (absIndex & 7))) != 0)
                    ar << (unsigned char)1;
                else
                    ar << (unsigned char)0;
            }
            ar.flush();

            ar.storeDataName(SER_END_OF_OBJECT);
        }
        else
        { // Loading
            int byteQuantity;
            std::string theName = "";
            while (theName.compare(SER_END_OF_OBJECT) != 0)
            {
                theName = ar.readDataName();
                if (theName.compare(SER_END_OF_OBJECT) != 0)
                {
                    bool noHit = true;
                    if (theName.compare("Nme") == 0)
                    {
                        noHit = false;
                        ar >> byteQuantity;
                        ar >> name;
                    }
                    if (theName.compare("Oid") == 0)
                    {
                        noHit = false;
                        ar >> byteQuantity;
                        ar >> identifier;
                    }
                    if (theName.compare("Dt2") == 0)
                    {
                        noHit = false;
                        ar >> byteQuantity;
                        ar >> dataType >> dataObjectID >> dataObjectAuxID;
                    }
                    if (theName.compare("Col") == 0)
                    {
                        noHit = false;
                        ar >> byteQuantity;
                        for (size_t i = 0; i < 3; i++)
                            ar >> ambientColor[i];
                    }
                    if (theName.compare("Var") == 0)
                    { // for backward comp. (flt->dbl)
                        noHit = false;
                        float bla, bli, blo;
                        ar >> byteQuantity;
                        ar >> bla >> bli >> blo;
                        zoomFactor = (double)bla;
                        addCoeff = (double)blo;
                    }

                    if (theName.compare("_ar") == 0)
                    {
                        noHit = false;
                        ar >> byteQuantity;
                        ar >> zoomFactor >> addCoeff;
                    }

                    if (theName.compare("Mac") == 0)
                    {
                        noHit = false;
                        ar >> byteQuantity;
                        ar >> _movingAverageCount;
                    }
                    if (theName.compare("Dci") == 0)
                    {
                        noHit = false;
                        ar >> byteQuantity;
                        ar >> _derivativeIntegralAndCumulative;
                    }
                    if (theName.compare("Pa2") == 0)
                    {
                        noHit = false;
                        ar >> byteQuantity;
                        unsigned char dummy;
                        ar >> dummy;
                        visible = (dummy & 1) == 1;
                        linkPoints = (dummy & 2) == 2;
                        label = (dummy & 4) == 4;
                    }
                    if (theName.compare("Dt9") == 0)
                    { // for backward comp. (flt->dbl)
                        noHit = false;
                        ar >> byteQuantity;
                        _floatData.reserve(cg->getBufferSize());
                        _floatData.clear();
                        for (int i = 0; i < cg->getBufferSize(); i++)
                            _floatData.push_back(0.0);
                        for (int i = 0; i < byteQuantity / int(sizeof(float)); i++)
                        {
                            float dummy;
                            ar >> dummy;
                            _floatData[i] = (double)dummy;
                        }
                    }

                    if (theName.compare("_t9") == 0)
                    {
                        noHit = false;
                        ar >> byteQuantity;
                        _floatData.clear(); // could also have read "Dt9"
                        for (int i = 0; i < cg->getBufferSize(); i++)
                            _floatData.push_back(0.0);
                        for (int i = 0; i < byteQuantity / int(sizeof(double)); i++)
                        {
                            double dummy;
                            ar >> dummy;
                            _floatData[i] = dummy;
                        }
                    }

                    if (theName.compare("Ifd") == 0)
                    { // for backward comp. (flt->dbl)
                        noHit = false;
                        ar >> byteQuantity;
                        _transformedFloatData.clear();
                        for (int i = 0; i < cg->getBufferSize(); i++)
                            _transformedFloatData.push_back(0.0);
                        for (int i = 0; i < byteQuantity / int(sizeof(float)); i++)
                        {
                            float dummy;
                            ar >> dummy;
                            _transformedFloatData[i] = (double)dummy;
                        }
                    }

                    if (theName.compare("_fd") == 0)
                    {
                        noHit = false;
                        ar >> byteQuantity;
                        _transformedFloatData.clear(); // could also have read "Ifd"
                        for (int i = 0; i < cg->getBufferSize(); i++)
                            _transformedFloatData.push_back(0.0);
                        for (int i = 0; i < byteQuantity / int(sizeof(double)); i++)
                        {
                            double dummy;
                            ar >> dummy;
                            _transformedFloatData[i] = dummy;
                        }
                    }

                    if (theName.compare("Bla") == 0)
                    {
                        noHit = false;
                        ar >> byteQuantity;
                        _floatDataValidFlags.clear();
                        for (int i = 0; i < ((cg->getBufferSize() / 8) + 1); i++)
                            _floatDataValidFlags.push_back(0); // None valid!
                        for (int i = 0; i < byteQuantity; i++)
                        {
                            unsigned char dummy;
                            ar >> dummy;
                            if (dummy != 0)
                                _floatDataValidFlags[i / 8] |= (1 << (i & 7));
                        }
                    }
                    if (theName.compare("Bli") == 0)
                    {
                        noHit = false;
                        ar >> byteQuantity;
                        _transformedFloatDataValidFlags.clear();
                        for (int i = 0; i < ((cg->getBufferSize() / 8) + 1); i++)
                            _transformedFloatDataValidFlags.push_back(0);
                        for (int i = 0; i < byteQuantity; i++)
                        {
                            unsigned char dummy;
                            ar >> dummy;
                            if (dummy != 0)
                                _transformedFloatDataValidFlags[i / 8] |= (1 << (i & 7));
                        }
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
            ar.xmlAddNode_string("name", name.c_str());

            ar.xmlAddNode_int("id", identifier);

            ar.xmlAddNode_int("dataType", dataType);
            ar.xmlAddNode_int("dataObjectId", dataObjectID);
            ar.xmlAddNode_int("dataObjectAuxId", dataObjectAuxID);

            ar.xmlAddNode_floats("color", ambientColor, 3);

            ar.xmlPushNewNode("transformation");
            ar.xmlAddNode_enum("value", _derivativeIntegralAndCumulative, sim_stream_transf_raw, "original",
                               sim_stream_transf_derivative, "derivative", sim_stream_transf_integral, "integral",
                               sim_stream_transf_cumulative, "cumulative");
            ar.xmlAddNode_float("scaling", zoomFactor);
            ar.xmlAddNode_float("offset", addCoeff);
            ar.xmlAddNode_int("movingAveragePeriod", _movingAverageCount);
            ar.xmlPopNode();

            ar.xmlPushNewNode("switches");
            ar.xmlAddNode_bool("visible", visible);
            ar.xmlAddNode_bool("linkPoints", linkPoints);
            ar.xmlAddNode_bool("showLabel", label);
            ar.xmlPopNode();

            std::vector<double> tmp;
            for (int i = 0; i < cg->getNumberOfPoints(); i++)
            {
                int absIndex;
                cg->getAbsIndexOfPosition(i, absIndex);
                tmp.push_back(_floatData[absIndex]);
            }
            ar.xmlAddNode_floats("data", tmp);

            tmp.clear();
            for (int i = 0; i < cg->getNumberOfPoints(); i++)
            {
                int absIndex;
                cg->getAbsIndexOfPosition(i, absIndex);
                tmp.push_back(_transformedFloatData[absIndex]);
            }
            ar.xmlAddNode_floats("transformedData", tmp);

            std::vector<bool> tmp2;
            for (int i = 0; i < cg->getNumberOfPoints(); i++)
            {
                int absIndex;
                cg->getAbsIndexOfPosition(i, absIndex);
                tmp2.push_back(((_floatDataValidFlags[absIndex / 8] & (1 << (absIndex & 7))) != 0));
            }
            ar.xmlAddNode_bools("dataValidity", tmp2);

            tmp2.clear();
            for (int i = 0; i < cg->getNumberOfPoints(); i++)
            {
                int absIndex;
                cg->getAbsIndexOfPosition(i, absIndex);
                tmp2.push_back(((_transformedFloatDataValidFlags[absIndex / 8] & (1 << (absIndex & 7))) != 0));
            }
            ar.xmlAddNode_bools("transformedDataValidity", tmp2);
        }
        else
        {
            ar.xmlGetNode_string("name", name);
            ar.xmlGetNode_int("id", identifier);

            ar.xmlGetNode_int("dataType", dataType);
            ar.xmlGetNode_int("dataObjectId", dataObjectID);
            ar.xmlGetNode_int("dataObjectAuxId", dataObjectAuxID);

            ar.xmlGetNode_floats("color", ambientColor, 3);

            if (ar.xmlPushChildNode("transformation"))
            {
                ar.xmlGetNode_enum("value", _derivativeIntegralAndCumulative, true, "original", sim_stream_transf_raw,
                                   "derivative", sim_stream_transf_derivative, "integral", sim_stream_transf_integral,
                                   "cumulative", sim_stream_transf_cumulative);
                ar.xmlGetNode_float("scaling", zoomFactor);
                ar.xmlGetNode_float("offset", addCoeff);
                ar.xmlGetNode_int("movingAveragePeriod", _movingAverageCount);
                ar.xmlPopNode();
            }

            if (ar.xmlPushChildNode("switches"))
            {
                ar.xmlGetNode_bool("visible", visible);
                ar.xmlGetNode_bool("linkPoints", linkPoints);
                ar.xmlGetNode_bool("showLabel", label);
                ar.xmlPopNode();
            }

            ar.xmlGetNode_floats("data", _floatData);

            ar.xmlGetNode_floats("transformedData", _transformedFloatData);

            std::vector<bool> tmp;
            ar.xmlGetNode_bools("dataValidity", tmp);
            _floatDataValidFlags.clear();
            for (int i = 0; i < ((cg->getBufferSize() / 8) + 1); i++)
                _floatDataValidFlags.push_back(0); // None valid!
            for (size_t i = 0; i < tmp.size(); i++)
            {
                if (tmp[i])
                    _floatDataValidFlags[i / 8] |= (1 << (i & 7));
            }

            tmp.clear();
            ar.xmlGetNode_bools("transformedDataValidity", tmp);
            _transformedFloatDataValidFlags.clear();
            for (int i = 0; i < ((cg->getBufferSize() / 8) + 1); i++)
                _transformedFloatDataValidFlags.push_back(0); // None valid!
            for (size_t i = 0; i < tmp.size(); i++)
            {
                if (tmp[i])
                    _transformedFloatDataValidFlags[i / 8] |= (1 << (i & 7));
            }
        }
    }
}
