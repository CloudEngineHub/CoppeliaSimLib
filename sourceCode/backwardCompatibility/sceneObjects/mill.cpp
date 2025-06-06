#include <simInternal.h>
#include <mill.h>
#include <tt.h>
#include <vDateTime.h>
#include <utils.h>
#include <app.h>
#ifdef SIM_WITH_GUI
#include <millRendering.h>
#endif

CMill::CMill(int theType)
{
    commonInit();
    setMillType(theType);
    computeBoundingBox();
}

CMill::CMill()
{ // needed by the serialization routine only!
    commonInit();
}

CMill::~CMill()
{
    delete convexVolume;
}

std::string CMill::getObjectTypeInfo() const
{
    return "mill";
}

std::string CMill::getObjectTypeInfoExtended() const
{
    if (_millType == sim_mill_pyramid_subtype)
        return ("mill (pyramid)");
    if (_millType == sim_mill_cylinder_subtype)
        return ("mill (cylinder)");
    if (_millType == sim_mill_disc_subtype)
        return ("mill (disc)");
    return ("mill (cone)");
}

bool CMill::isPotentiallyCollidable() const
{
    return (false);
}
bool CMill::isPotentiallyMeasurable() const
{
    return (false);
}
bool CMill::isPotentiallyDetectable() const
{
    return (false);
}
bool CMill::isPotentiallyRenderable() const
{
    return (false);
}

void CMill::commonInit()
{
    convexVolume = new CConvexVolume();
    _explicitHandling = false;
    _objectType = sim_sceneobject_mill;
    _size = 0.01;
    _localObjectSpecialProperty = 0;
    _millableObject = -1;
    _millDataValid = false;
    _calcTimeInMs = 0;
    _milledSurface = 0.0;
    _milledVolume = 0.0;
    _milledObjectCount = 0;

    _objectMovementPreferredAxes = 0x013;

    passiveVolumeColor.setDefaultValues();
    passiveVolumeColor.setColor(0.0f, 0.5f, 0.9f, sim_colorcomponent_ambient_diffuse);
    activeVolumeColor.setDefaultValues();
    activeVolumeColor.setColor(1.0f, 0.1f, 0.1f, sim_colorcomponent_ambient_diffuse);
    _visibilityLayer = MILL_LAYER;
    _objectAlias = getObjectTypeInfo();
    _objectName_old = getObjectTypeInfo();
    _objectAltName_old = tt::getObjectAltNameFromObjectName(_objectName_old.c_str());
}

void CMill::setExplicitHandling(bool setExplicit)
{
    _explicitHandling = setExplicit;
}

bool CMill::getExplicitHandling() const
{
    return (_explicitHandling);
}

int CMill::getMillableObject() const
{
    return (_millableObject);
}

void CMill::setMillableObject(int objectID)
{
    _millableObject = objectID;
}

void CMill::removeSceneDependencies()
{
    CSceneObject::removeSceneDependencies();
    _millableObject = -1;
}

void CMill::addSpecializedObjectEventData(CCbor* ev)
{
#if SIM_EVENT_PROTOCOL_VERSION == 2
    ev->openKeyMap(getObjectTypeInfo().c_str());
    ev->closeArrayOrMap(); // mill
#endif
}

CSceneObject* CMill::copyYourself()
{
    CMill* newMill = (CMill*)CSceneObject::copyYourself();

    newMill->_millableObject = _millableObject;
    newMill->_milledSurface = _milledSurface;
    newMill->_milledVolume = _milledVolume;
    newMill->_milledObjectCount = _milledObjectCount;
    newMill->_millDataValid = false;
    newMill->_size = _size;
    newMill->_explicitHandling = _explicitHandling;
    newMill->_millType = _millType;

    delete newMill->convexVolume;
    newMill->convexVolume = convexVolume->copyYourself();

    // Colors:
    passiveVolumeColor.copyYourselfInto(&newMill->passiveVolumeColor);
    activeVolumeColor.copyYourselfInto(&newMill->activeVolumeColor);

    newMill->_initialValuesInitialized = _initialValuesInitialized;
    newMill->_initialExplicitHandling = _initialExplicitHandling;

    return (newMill);
}

void CMill::announceObjectWillBeErased(const CSceneObject* object, bool copyBuffer)
{ // copyBuffer is false by default (if true, we are 'talking' to objects
    // in the copyBuffer)
    CSceneObject::announceObjectWillBeErased(object, copyBuffer);
    if (_millableObject == object->getObjectHandle())
        _millableObject = -1;
}

void CMill::announceCollectionWillBeErased(int groupID, bool copyBuffer)
{ // copyBuffer is false by default (if true, we are 'talking' to objects
    // in the copyBuffer)
    CSceneObject::announceCollectionWillBeErased(groupID, copyBuffer);
    if (_millableObject == groupID)
        _millableObject = -1;
}
void CMill::announceCollisionWillBeErased(int collisionID, bool copyBuffer)
{ // copyBuffer is false by default (if true, we are 'talking' to objects
    // in the copyBuffer)
    CSceneObject::announceCollisionWillBeErased(collisionID, copyBuffer);
}
void CMill::announceDistanceWillBeErased(int distanceID, bool copyBuffer)
{ // copyBuffer is false by default (if true, we are 'talking' to objects
    // in the copyBuffer)
    CSceneObject::announceDistanceWillBeErased(distanceID, copyBuffer);
}
void CMill::announceIkObjectWillBeErased(int ikGroupID, bool copyBuffer)
{ // copyBuffer is false by default (if true, we are 'talking' to objects
    // in the copyBuffer)
    CSceneObject::announceIkObjectWillBeErased(ikGroupID, copyBuffer);
}

void CMill::performObjectLoadingMapping(const std::map<int, int>* map, int opType)
{
    CSceneObject::performObjectLoadingMapping(map, opType);
    if (_millableObject <= SIM_IDEND_SCENEOBJECT)
        _millableObject = CWorld::getLoadingMapping(map, _millableObject);
}
void CMill::performCollectionLoadingMapping(const std::map<int, int>* map, int opType)
{
    CSceneObject::performCollectionLoadingMapping(map, opType);
    if (_millableObject > SIM_IDEND_SCENEOBJECT)
        _millableObject = CWorld::getLoadingMapping(map, _millableObject);
}
void CMill::performCollisionLoadingMapping(const std::map<int, int>* map, int opType)
{
    CSceneObject::performCollisionLoadingMapping(map, opType);
}
void CMill::performDistanceLoadingMapping(const std::map<int, int>* map, int opType)
{
    CSceneObject::performDistanceLoadingMapping(map, opType);
}
void CMill::performIkLoadingMapping(const std::map<int, int>* map, int opType)
{
    CSceneObject::performIkLoadingMapping(map, opType);
}

void CMill::performTextureObjectLoadingMapping(const std::map<int, int>* map, int opType)
{
    CSceneObject::performTextureObjectLoadingMapping(map, opType);
}

void CMill::performDynMaterialObjectLoadingMapping(const std::map<int, int>* map)
{
    CSceneObject::performDynMaterialObjectLoadingMapping(map);
}

void CMill::initializeInitialValues(bool simulationAlreadyRunning)
{ // is called at simulation start, but also after object(s) have been copied into a scene!
    CSceneObject::initializeInitialValues(simulationAlreadyRunning);
    _initialExplicitHandling = _explicitHandling;
}

void CMill::simulationAboutToStart()
{
    initializeInitialValues(false);
    CSceneObject::simulationAboutToStart();
}

void CMill::simulationEnded()
{ // Remember, this is not guaranteed to be run! (the object can be copied during simulation, and pasted after it
    // ended). For thoses situations there is the initializeInitialValues routine!
    if (_initialValuesInitialized)
    {
        if ((getCumulativeModelProperty() & sim_modelproperty_not_reset) == 0)
        {
            _explicitHandling = _initialExplicitHandling;
        }
    }
    CSceneObject::simulationEnded();
}

void CMill::serialize(CSer& ar)
{
    CSceneObject::serialize(ar);
    if (ar.isBinary())
    {
        if (ar.isStoring())
        { // Storing
            ar.storeDataName("Snt");
            ar << _millType;
            ar.flush();

            ar.storeDataName("Vod");
            ar.setCountingMode();
            convexVolume->serialize(ar);
            if (ar.setWritingMode())
                convexVolume->serialize(ar);

            ar.storeDataName("_ns");
            ar << _size;
            ar.flush();

            ar.storeDataName("Pra");
            unsigned char nothing = 0;
            // 12/12/2011 SIM_SET_CLEAR_BIT(nothing,0,_millAllCuttable);
            // free since 13/7/2016 SIM_SET_CLEAR_BIT(nothing,1,_showMillBase_DEPRECATED);
            SIM_SET_CLEAR_BIT(nothing, 2, _explicitHandling);
            ar << nothing;
            ar.flush();

            ar.storeDataName("Cl1");
            ar.setCountingMode();
            passiveVolumeColor.serialize(ar, 0);
            if (ar.setWritingMode())
                passiveVolumeColor.serialize(ar, 0);

            ar.storeDataName("Cl2");
            ar.setCountingMode();
            activeVolumeColor.serialize(ar, 0);
            if (ar.setWritingMode())
                activeVolumeColor.serialize(ar, 0);

            ar.storeDataName("Sox");
            ar << _millableObject;
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
                    if (theName.compare("Snt") == 0)
                    {
                        noHit = false;
                        ar >> byteQuantity;
                        ar >> _millType;
                    }
                    if (theName.compare("Vod") == 0)
                    {
                        noHit = false;
                        ar >> byteQuantity;
                        if (convexVolume != nullptr)
                            delete convexVolume;
                        convexVolume = new CConvexVolume();
                        convexVolume->serialize(ar);
                    }
                    if (theName.compare("Sns") == 0)
                    { // for backward comp. (flt->dbl)
                        noHit = false;
                        ar >> byteQuantity;
                        float bla;
                        ar >> bla;
                        _size = (double)bla;
                    }

                    if (theName.compare("_ns") == 0)
                    {
                        noHit = false;
                        ar >> byteQuantity;
                        ar >> _size;
                    }

                    if (theName.compare("Sox") == 0)
                    {
                        noHit = false;
                        ar >> byteQuantity;
                        ar >> _millableObject;
                    }
                    if (theName == "Pra")
                    {
                        noHit = false;
                        ar >> byteQuantity;
                        unsigned char nothing;
                        ar >> nothing;
                        // free since 13/7/2016 _showMillBase_DEPRECATED=SIM_IS_BIT_SET(nothing,1);
                        _explicitHandling = SIM_IS_BIT_SET(nothing, 2);
                    }
                    if (theName.compare("Cl1") == 0)
                    {
                        noHit = false;
                        ar >> byteQuantity;
                        passiveVolumeColor.serialize(ar, 0);
                    }
                    if (theName.compare("Cl2") == 0)
                    {
                        noHit = false;
                        ar >> byteQuantity;
                        activeVolumeColor.serialize(ar, 0);
                    }
                    if (noHit)
                        ar.loadUnknownData();
                }
            }
            if (ar.getSerializationVersionThatWroteThisFile() < 17)
            { // on 29/08/2013 we corrected all default lights. So we need to correct for that change:
                utils::scaleColorUp_(passiveVolumeColor.getColorsPtr());
                utils::scaleColorUp_(activeVolumeColor.getColorsPtr());
            }
            computeBoundingBox();
        }
    }
    else
    {
        if (ar.isStoring())
        {
            ar.xmlAddNode_enum("type", _millType, sim_mill_pyramid_subtype, "pyramid", sim_mill_cylinder_subtype,
                               "cylinder", sim_mill_disc_subtype, "disc", sim_mill_cone_subtype, "cone");

            ar.xmlAddNode_float("size", _size);

            ar.xmlAddNode_int("millableEntity", _millableObject);

            ar.xmlPushNewNode("switches");
            ar.xmlAddNode_bool("explicitHandling", _explicitHandling);
            ar.xmlPopNode();

            ar.xmlPushNewNode("colors");
            ar.xmlPushNewNode("passive");
            passiveVolumeColor.serialize(ar, 0);
            ar.xmlPopNode();
            ar.xmlPushNewNode("active");
            activeVolumeColor.serialize(ar, 0);
            ar.xmlPopNode();
            ar.xmlPopNode();

            ar.xmlPushNewNode("volume");
            convexVolume->serialize(ar);
            ar.xmlPopNode();
        }
        else
        {
            ar.xmlGetNode_enum("type", _millType, true, "pyramid", sim_mill_pyramid_subtype, "cylinder",
                               sim_mill_cylinder_subtype, "disc", sim_mill_disc_subtype, "cone", sim_mill_cone_subtype);

            ar.xmlGetNode_float("size", _size);

            ar.xmlGetNode_int("millableEntity", _millableObject);

            if (ar.xmlPushChildNode("switches"))
            {
                ar.xmlGetNode_bool("explicitHandling", _explicitHandling);
                ar.xmlPopNode();
            }

            if (ar.xmlPushChildNode("colors"))
            {
                if (ar.xmlPushChildNode("passive"))
                {
                    passiveVolumeColor.serialize(ar, 0);
                    ar.xmlPopNode();
                }
                if (ar.xmlPushChildNode("active"))
                {
                    activeVolumeColor.serialize(ar, 0);
                    ar.xmlPopNode();
                }
                ar.xmlPopNode();
            }

            if (ar.xmlPushChildNode("volume"))
            {
                if (convexVolume != nullptr)
                    delete convexVolume;
                convexVolume = new CConvexVolume();
                convexVolume->serialize(ar);
                ar.xmlPopNode();
            }
            computeBoundingBox();
        }
    }
}

bool CMill::getMillingVolumeBoundingBox(C3Vector& minV, C3Vector& maxV) const
{
    return (convexVolume->getVolumeBoundingBox(minV, maxV));
}

void CMill::computeBoundingBox()
{
    C3Vector minV, maxV;
    getMillingVolumeBoundingBox(minV, maxV);
    C3Vector m(_size * 0.25, _size * 0.25, _size * 0.25); // mill base
    C3Vector n(-_size * 0.25, -_size * 0.25, -_size * 0.25);
    minV.keepMin(n);
    maxV.keepMax(m);
    C7Vector fr;
    fr.Q.setIdentity();
    fr.X = (minV + maxV) * 0.5;
    _setBB(fr, (maxV - minV) * 0.5);
}

void CMill::resetMill(bool exceptExplicitHandling)
{
    if ((!exceptExplicitHandling) || (!getExplicitHandling()))
    {
        _millDataValid = false;
        _calcTimeInMs = 0;
    }
}

int CMill::handleMill(bool exceptExplicitHandling, double& milledSurface, double& milledVolume,
                      bool justForInitialization)
{
    if (exceptExplicitHandling && getExplicitHandling())
        return (0); // We don't want to handle those
    _millDataValid = false;
    _calcTimeInMs = 0;
    if (!App::currentWorld->mainSettings_old->millsEnabled)
        return (0);
    if (!App::worldContainer->pluginContainer->isGeomPluginAvailable())
        return (0);

    int stTime = (int)VDateTime::getTimeInMs();

    // For now:
    int cutObjectHandle = -1;
    milledSurface = 0.0;
    milledVolume = 0.0;
    _milledObjectCount =
        0; // CCuttingRoutine::cutEntity(getObjectHandle(),_millableObject,cutObjectHandle,milledSurface,milledVolume,justForInitialization,false);
    _milledSurface = milledSurface;
    _milledVolume = milledVolume;
    _calcTimeInMs = VDateTime::getTimeDiffInMs(stTime);
    _millDataValid = true;
    return (_milledObjectCount);
}

double CMill::getCalculationTime() const
{
    return (double(_calcTimeInMs) * 0.001);
}

bool CMill::getMillDataIsValid() const
{
    return (_millDataValid);
}

CColorObject* CMill::getColor(bool getActiveColor)
{
    if (getActiveColor)
        return (&activeVolumeColor);
    return (&passiveVolumeColor);
}

void CMill::setSize(double newSize)
{
    tt::limitValue(0.0001, 10.0, newSize);
    _size = newSize;
}
double CMill::getSize() const
{
    return (_size);
}

bool CMill::getMilledSurface(double& surf) const
{
    if (!_millDataValid)
        return (false);
    surf = _milledSurface;
    return (true);
}

bool CMill::getMilledVolume(double& vol) const
{
    if (!_millDataValid)
        return (false);
    vol = _milledVolume;
    return (true);
}

bool CMill::getMilledCount(int& milledCount) const
{
    if (!_millDataValid)
        return (false);
    milledCount = _milledObjectCount;
    return (true);
}

void CMill::scaleObject(double scalingFactor)
{
    _size *= scalingFactor;
    convexVolume->scaleVolume(scalingFactor);

    CSceneObject::scaleObject(scalingFactor);
}

void CMill::setMillType(int theType)
{
    _millType = theType;
    if (theType == sim_mill_cylinder_subtype)
        convexVolume->setVolumeType(CYLINDER_TYPE_CONVEX_VOLUME, _objectType, _size);
    if (theType == sim_mill_disc_subtype)
        convexVolume->setVolumeType(DISC_TYPE_CONVEX_VOLUME, _objectType, _size);
    if (theType == sim_mill_pyramid_subtype)
        convexVolume->setVolumeType(PYRAMID_TYPE_CONVEX_VOLUME, _objectType, _size);
    if (theType == sim_mill_cone_subtype)
        convexVolume->setVolumeType(CONE_TYPE_CONVEX_VOLUME, _objectType, _size);
}
int CMill::getMillType() const
{
    return (_millType);
}

#ifdef SIM_WITH_GUI
void CMill::display(CViewableBase* renderingObject, int displayAttrib)
{
    displayMill(this, renderingObject, displayAttrib);
}
#endif
