#pragma once

#include <sceneObject.h>
#include <convexVolume.h>

// ----------------------------------------------------------------------------------------------
// flags: bit0: not writable, bit1: not readable, bit2: removable
#define DEFINE_PROPERTIES                                                                                                                                                                                              \
    FUNCX(propProximitySensor_size, "sensorPointSize", sim_propertytype_float, 0, "Sensor point size", "")                                                                                                             \
    FUNCX(propProximitySensor_frontFaceDetection, "frontFaceDetection", sim_propertytype_bool, 0, "Front face detection", "")                                                                                          \
    FUNCX(propProximitySensor_backFaceDetection, "backFaceDetection", sim_propertytype_bool, 0, "Back face detection", "")                                                                                             \
    FUNCX(propProximitySensor_exactMode, "exactMode", sim_propertytype_bool, 0, "Exact mode", "")                                                                                                                      \
    FUNCX(propProximitySensor_explicitHandling, "explicitHandling", sim_propertytype_bool, 0, "Explicit handling", "")                                                                                                 \
    FUNCX(propProximitySensor_showVolume, "showVolume", sim_propertytype_bool, 0, "Show volume", "")                                                                                                                   \
    FUNCX(propProximitySensor_randomizedDetection, "randomizedDetection", sim_propertytype_bool, sim_propertyinfo_notwritable, "Randomized detection", "")                                                             \
    FUNCX(propProximitySensor_sensorType, "sensorType", sim_propertytype_int, sim_propertyinfo_notwritable, "Type", "Sensor type")                                                                                     \
    FUNCX(propProximitySensor_detectedObjectHandle, "detectedObjectHandle", sim_propertytype_int, sim_propertyinfo_notwritable | sim_propertyinfo_modelhashexclude, "Detected object", "Detected scene object handle") \
    FUNCX(propProximitySensor_angleThreshold, "angleThreshold", sim_propertytype_float, 0, "Angle threshold", "Angle threshold, 0.0 to disable")                                                                       \
    FUNCX(propProximitySensor_detectedPoint, "detectedPoint", sim_propertytype_vector3, sim_propertyinfo_notwritable | sim_propertyinfo_modelhashexclude, "Detected point", "")                                        \
    FUNCX(propProximitySensor_detectedNormal, "detectedNormal", sim_propertytype_vector3, sim_propertyinfo_notwritable | sim_propertyinfo_modelhashexclude, "Detected normal", "Detected normal vector")

#define FUNCX(name, str, v1, v2, t1, t2) const SProperty name = {str, v1, v2, t1, t2};
DEFINE_PROPERTIES
#undef FUNCX
#define FUNCX(name, str, v1, v2, t1, t2) name,
const std::vector<SProperty> allProps_proximitySensor = {DEFINE_PROPERTIES};
#undef FUNCX
#undef DEFINE_PROPERTIES
// ----------------------------------------------------------------------------------------------

class CProxSensor : public CSceneObject
{
  public:
    CProxSensor();
    CProxSensor(int theType);
    virtual ~CProxSensor();

    // Following functions are inherited from CSceneObject
    void addSpecializedObjectEventData(CCbor* ev) override;
    CSceneObject* copyYourself() override;
    void removeSceneDependencies() override;
    void scaleObject(double scalingFactor) override;
    void serialize(CSer& ar) override;
    void announceObjectWillBeErased(const CSceneObject* object, bool copyBuffer) override;
    void announceCollectionWillBeErased(int groupID, bool copyBuffer) override;
    void announceCollisionWillBeErased(int collisionID, bool copyBuffer) override;
    void announceDistanceWillBeErased(int distanceID, bool copyBuffer) override;
    void announceIkObjectWillBeErased(int ikGroupID, bool copyBuffer) override;
    void performObjectLoadingMapping(const std::map<int, int>* map, int opType) override;
    void performCollectionLoadingMapping(const std::map<int, int>* map, int opType) override;
    void performCollisionLoadingMapping(const std::map<int, int>* map, int opType) override;
    void performDistanceLoadingMapping(const std::map<int, int>* map, int opType) override;
    void performIkLoadingMapping(const std::map<int, int>* map, int opType) override;
    void performTextureObjectLoadingMapping(const std::map<int, int>* map, int opType) override;
    void performDynMaterialObjectLoadingMapping(const std::map<int, int>* map) override;
    void simulationAboutToStart() override;
    void simulationEnded() override;
    void initializeInitialValues(bool simulationAlreadyRunning) override;
    void computeBoundingBox() override;
    void setIsInScene(bool s) override;
    bool isPotentiallyCollidable() const override;
    bool isPotentiallyMeasurable() const override;
    bool isPotentiallyDetectable() const override;
    bool isPotentiallyRenderable() const override;
    std::string getObjectTypeInfo() const override;
    std::string getObjectTypeInfoExtended() const override;

    int setBoolProperty(const char* pName, bool pState) override;
    int getBoolProperty(const char* pName, bool& pState) const override;
    int setIntProperty(const char* pName, int pState) override;
    int getIntProperty(const char* pName, int& pState) const override;
    int setFloatProperty(const char* pName, double pState) override;
    int getFloatProperty(const char* pName, double& pState) const override;
    int setIntArray2Property(const char* pName, const int* pState) override;
    int getIntArray2Property(const char* pName, int* pState) const override;
    int setVector2Property(const char* pName, const double* pState) override;
    int getVector2Property(const char* pName, double* pState) const override;
    int setVector3Property(const char* pName, const C3Vector& pState) override;
    int getVector3Property(const char* pName, C3Vector& pState) const override;
    int setColorProperty(const char* pName, const float* pState) override;
    int getColorProperty(const char* pName, float* pState) const override;
    int setFloatArrayProperty(const char* pName, const double* v, int vL) override;
    int getFloatArrayProperty(const char* pName, std::vector<double>& pState) const override;
    int setIntArrayProperty(const char* pName, const int* v, int vL) override;
    int getIntArrayProperty(const char* pName, std::vector<int>& pState) const override;
    int getPropertyName(int& index, std::string& pName, std::string& appartenance) const override;
    static int getPropertyName_static(int& index, std::string& pName, std::string& appartenance);
    int getPropertyInfo(const char* pName, int& info, std::string& infoTxt) const override;
    static int getPropertyInfo_static(const char* pName, int& info, std::string& infoTxt);

    // Various
    bool getSensingVolumeBoundingBox(C3Vector& minV, C3Vector& maxV) const;
    void getSensingVolumeOBB(C7Vector& tr, C3Vector& halfSizes);
    void setSensableObject(int objectID);
    int getSensableObject();

    bool handleSensor(bool exceptExplicitHandling, int& detectedObjectHandle, C3Vector& detectedNormalVector);
    void resetSensor(bool exceptExplicitHandling);
    int readSensor(C3Vector& detectPt, int& detectedObjectHandle, C3Vector& detectedNormalVector);

    void commonInit();
    bool getSensedData(C3Vector& pt);
    void setExactMode(bool closestObjMode);
    bool getExactMode();
    void setProxSensorSize(double newSize);
    double getProxSensorSize();

    void setAllowedNormal(double al);
    double getAllowedNormal() const;
    bool getFrontFaceDetection() const;
    bool getBackFaceDetection() const;
    void setFrontFaceDetection(bool faceOn);
    void setBackFaceDetection(bool faceOn);
    void setShowDetectionVolume(bool show);

    int getSensorType() const;

    void setExplicitHandling(bool setExplicit);
    bool getExplicitHandling() const;

    void setSensableType(int theType);
    int getSensableType() const;

    void setShowVolume(bool s);
    bool getShowVolume() const;

    void setHideDetectionRay(bool hide);
    bool getHideDetectionRay() const;

    void setRandomizedDetection(bool enable);
    bool getRandomizedDetection() const;
    void setRandomizedDetectionSampleCount(int c);
    int getRandomizedDetectionSampleCount() const;
    void setRandomizedDetectionCountForDetection(int c);
    int getRandomizedDetectionCountForDetection() const;

    void calculateFreshRandomizedRays();
    const std::vector<C3Vector>* getPointerToRandomizedRays() const;
    std::vector<double>* getPointerToRandomizedRayDetectionStates();

    double getCalculationTime() const;
    C3Vector getDetectedPoint() const;
    bool getIsDetectedPointValid() const;
    std::string getSensableObjectLoadAlias() const;
    std::string getSensableObjectLoadName_old() const;

    CColorObject* getColor(int index);

    std::vector<double> cutEdges; // Only used for sensor cutting debugging

    CConvexVolume* convexVolume;

  protected:
    void _setDetectedObjectAndInfo(int h, const C3Vector* detectedPt = nullptr, const C3Vector* detectedN = nullptr);
    // Variables which need to be serialized & copied
    CColorObject volumeColor;
    CColorObject detectionRayColor;
    double _angleThreshold; // 0.0 means no threshold
    double _proxSensorSize;
    bool _exactMode; // otherwise approximate (non-closest item mode)
    bool _frontFaceDetection;
    bool _backFaceDetection;
    bool _explicitHandling;
    bool _showVolume;
    int sensorType;
    C3Vector _detectedPoint;
    int _detectedObjectHandle;
    C3Vector _detectedNormalVector;
    int _calcTimeInMs;

    bool _randomizedDetection;
    int _randomizedDetectionSampleCount_deprecated;       // 1
    int _randomizedDetectionCountForDetection_deprecated; // 1
    int _sensableType_deprecated;                         // sim_objectspecialproperty_detectable_ultrasonic
    int _sensableObject_deprecated;                       // scene object handle or collection handle
    bool _hideDetectionRay_deprecated;

    std::vector<C3Vector> _randomizedVectors;
    std::vector<double> _randomizedVectorDetectionStates;

    bool _initialExplicitHandling;

    std::string _sensableObjectLoadAlias;
    std::string _sensableObjectLoadName_old;

#ifdef SIM_WITH_GUI
  public:
    void display(CViewableBase* renderingObject, int displayAttrib) override;
#endif
};
