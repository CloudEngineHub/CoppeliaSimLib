#pragma once

#include <sceneObject.h>
#include <mesh.h>
#include <dummy.h>

// ----------------------------------------------------------------------------------------------
// flags: bit0: not writable, bit1: not readable, bit2: removable
#define DEFINE_PROPERTIES \
    FUNCX(propShape_meshes,                  "meshes",                                   sim_propertytype_intvector, 1) \
    FUNCX(propShape_applyCulling,            "applyCulling",                             sim_propertytype_bool, 2) \
    FUNCX(propShape_applyShadingAngle,       "applyShadingAngle",                        sim_propertytype_float, 2) \
    FUNCX(propShape_applyShowEdges,          "applyShowEdges",                           sim_propertytype_bool, 2) \
    FUNCX(propShape_flipFaces,               "flipFaces",                                sim_propertytype_bool, 2) \
    FUNCX(propShape_respondableMask,         "respondableMask",                          sim_propertytype_int, 0) \
    FUNCX(propShape_startInDynSleepMode,     "startInDynSleepMode",                      sim_propertytype_bool, 0) \
    FUNCX(propShape_dynamic,                 "dynamic",                                  sim_propertytype_bool, 0) \
    FUNCX(propShape_kinematic,               "kinematic",                                sim_propertytype_bool, 0) \
    FUNCX(propShape_respondable,             "respondable",                              sim_propertytype_bool, 0) \
    FUNCX(propShape_setToDynamicWithParent,  "setToDynamicWithParent",                   sim_propertytype_bool, 0) \
    FUNCX(propShape_initLinearVelocity,      "initLinearVelocity",                       sim_propertytype_vector3, 0) \
    FUNCX(propShape_initAngularVelocity,     "initAngularVelocity",                      sim_propertytype_vector3, 0) \
    FUNCX(propShape_dynLinearVelocity,       "dynLinearVelocity",                        sim_propertytype_vector3, 1) \
    FUNCX(propShape_dynAngularVelocity,     "dynAngularVelocity",                       sim_propertytype_vector3, 1) \

#define FUNCX(name, str, v1, v2) const SProperty name = {str, v1, v2};
DEFINE_PROPERTIES
#undef FUNCX
#define FUNCX(name, str, v1, v2) name,
const std::vector<SProperty> allProps_shape = { DEFINE_PROPERTIES };
#undef FUNCX
#undef DEFINE_PROPERTIES
// ----------------------------------------------------------------------------------------------

class CShape : public CSceneObject
{
  public:
    CShape();
    CShape(const std::vector<double> &allHeights, int xSize, int ySize, double dx, double minH, double maxH); // heightfield
    CShape(const C7Vector &transformation, const std::vector<double> &vertices, const std::vector<int> &indices,
           const std::vector<double> *optNormals, const std::vector<float> *optTexCoords, int options); // mesh
    virtual ~CShape();

    void replaceMesh(CMeshWrapper *newMesh, bool keepMeshAttributes);
    CMeshWrapper *detachMesh();
    bool computeMassAndInertia(double density);

    void invertFrontBack();

    int getMeshModificationCounter();
    CMeshWrapper *getMesh() const;
    CMesh *getSingleMesh() const;
    CMesh* getMeshFromUid(int meshUid, const C7Vector& parentCumulTr, C7Vector& shapeRelTr) const;


    void *_meshCalculationStructure;
    int _meshModificationCounter;

    // Following functions are inherited from CSceneObject
    void addSpecializedObjectEventData(CCbor *ev);
    CSceneObject *copyYourself();
    void copyAttributesTo(CShape *target);
    void removeSceneDependencies();
    void scaleObject(double scalingFactor);
    bool scaleObjectNonIsometrically(double x, double y, double z);
    void serialize(CSer &ar);
    void announceObjectWillBeErased(const CSceneObject *object, bool copyBuffer);
    void announceCollectionWillBeErased(int groupID, bool copyBuffer);
    void announceCollisionWillBeErased(int collisionID, bool copyBuffer);
    void announceDistanceWillBeErased(int distanceID, bool copyBuffer);
    void announceIkObjectWillBeErased(int ikGroupID, bool copyBuffer);
    void performObjectLoadingMapping(const std::map<int, int> *map, bool loadingAmodel);
    void performCollectionLoadingMapping(const std::map<int, int> *map, bool loadingAmodel);
    void performCollisionLoadingMapping(const std::map<int, int> *map, bool loadingAmodel);
    void performDistanceLoadingMapping(const std::map<int, int> *map, bool loadingAmodel);
    void performIkLoadingMapping(const std::map<int, int> *map, bool loadingAmodel);
    void performTextureObjectLoadingMapping(const std::map<int, int> *map);
    void performDynMaterialObjectLoadingMapping(const std::map<int, int> *map);
    void simulationAboutToStart();
    void simulationEnded();
    void initializeInitialValues(bool simulationAlreadyRunning);
    void computeBoundingBox();
    std::string getObjectTypeInfo() const;
    std::string getObjectTypeInfoExtended() const;
    bool isPotentiallyCollidable() const;
    bool isPotentiallyMeasurable() const;
    bool isPotentiallyDetectable() const;
    bool isPotentiallyRenderable() const;
    void setIsInScene(bool s);

    int setBoolProperty(const char* pName, bool pState);
    int getBoolProperty(const char* pName, bool& pState) const;
    int setIntProperty(const char* pName, int pState);
    int getIntProperty(const char* pName, int& pState) const;
    int setFloatProperty(const char* pName, double pState);
    int getFloatProperty(const char* pName, double& pState) const;
    int setStringProperty(const char* pName, const char* pState);
    int getStringProperty(const char* pName, std::string& pState) const;
    int setVector3Property(const char* pName, const C3Vector& pState);
    int getVector3Property(const char* pName, C3Vector& pState) const;
    int setVectorProperty(const char* pName, const double* v, int vL);
    int getVectorProperty(const char* pName, std::vector<double>& pState) const;
    int setIntVectorProperty(const char* pName, const int* v, int vL);
    int getIntVectorProperty(const char* pName, std::vector<int>& pState) const;
    int getPropertyName(int& index, std::string& pName, std::string& appartenance) const;
    static int getPropertyName_static(int& index, std::string& pName, std::string& appartenance);
    int getPropertyInfo(const char* pName, int& info) const;
    static int getPropertyInfo_static(const char* pName, int& info);


    // Various
    void commonInit();
    int getComponentCount() const;
    bool getCulling() const;
    void setCulling(bool culState);
    bool getVisibleEdges() const;
    void setVisibleEdges(bool v);
    double getShadingAngle() const;
    void setShadingAngle(double a);
    void setRespondableSuspendCount(int cnt);
    void decrementRespondableSuspendCount();

    bool getHideEdgeBorders_OLD() const;
    void setHideEdgeBorders_OLD(bool v);
    int getEdgeWidth_DEPRECATED() const;
    void setEdgeWidth_DEPRECATED(int w);
    bool getShapeWireframe_OLD() const;
    void setShapeWireframe_OLD(bool w);
    CDynMaterialObject *getDynMaterial();
    void setDynMaterial(CDynMaterialObject *mat);

    void display_extRenderer(CViewableBase *renderingObject, int displayAttrib);

    // Overridden from CSceneObject:
    bool setParent(CSceneObject *newParent);

    void prepareVerticesIndicesNormalsAndEdgesForSerialization();

    bool getStartInDynamicSleeping() const;
    void setStartInDynamicSleeping(bool sleeping);
    bool getStatic() const;
    void setStatic(bool sta);
    bool getDynKinematic() const;
    void setDynKinematic(bool kin);

    C3Vector getInitialDynamicLinearVelocity();
    void setInitialDynamicLinearVelocity(const C3Vector &vel);
    C3Vector getInitialDynamicAngularVelocity();
    void setInitialDynamicAngularVelocity(const C3Vector &vel);
    bool isCompound() const;
    void setColor(const char *colorName, int colorComponent, float r, float g, float b);
    void setColor(const char *colorName, int colorComponent, const float *rgbData);
    bool getColor(const char *colorName, int colorComponent, float *rgbData);
    void setRespondable(bool r);
    bool getRespondable();
    void setRespondableMask(int m);
    int getRespondableMask();

    bool getSetAutomaticallyToNonStaticIfGetsParent();
    void setSetAutomaticallyToNonStaticIfGetsParent(bool autoNonStatic);

    void setDynamicVelocity(const C3Vector &linearV, const C3Vector &angularV);
    C3Vector getDynamicLinearVelocity();
    C3Vector getDynamicAngularVelocity();
    void addAdditionalForceAndTorque(const C3Vector &f, const C3Vector &t);
    void clearAdditionalForce();
    void clearAdditionalTorque();
    void clearAdditionalForceAndTorque();
    C3Vector getAdditionalForce();
    C3Vector getAdditionalTorque();

    CSceneObject *getLastParentForLocalGlobalRespondable();
    void clearLastParentForLocalGlobalRespondable();


    // Distance measurement functions
    bool getShapeShapeDistance_IfSmaller(CShape *it, double &dist, double ray[7], int buffer[2]);
    bool getDistanceToDummy_IfSmaller(CDummy *it, double &dist, double ray[7], int &buffer);

    // Collision detection functions
    bool isMeshCalculationStructureInitialized();
    void initializeMeshCalculationStructureIfNeeded();
    void removeMeshCalculationStructure();
    bool doesShapeCollideWithShape(CShape *collidee, std::vector<double> *intersections);

    bool relocateFrame(const char *mode, const C7Vector *tr = nullptr);
    bool alignBB(const char *mode, const C7Vector *tr = nullptr);
    C7Vector getCumulCenteredMeshFrame() const;

    void setInsideAndOutsideFacesSameColor_DEPRECATED(bool s);
    bool getInsideAndOutsideFacesSameColor_DEPRECATED();

    void actualizeContainsTransparentComponent();
    bool getContainsTransparentComponent();

    void setRigidBodyWasAlreadyPutToSleepOnce(bool s);
    bool getRigidBodyWasAlreadyPutToSleepOnce();

  protected:
    CMeshWrapper *_mesh;
    void _serializeMesh(CSer &ar);

    int _respondableMask;
    CSceneObject *_lastParentForLocalGlobalRespondable;

    // Variables which need to be serialized
    bool _startInDynamicSleeping;
    bool _shapeIsDynamicallyStatic;
    bool _shapeIsDynamicallyKinematic; // for static shapes that move (used by e.g. Mujoco)
    bool _shapeIsDynamicallyRespondable;
    bool _containsTransparentComponents; // to be able to order shapes according to transparency
    bool _setAutomaticallyToNonStaticIfGetsParent;
    C3Vector _initialDynamicLinearVelocity;
    C3Vector _initialDynamicAngularVelocity;
    CDynMaterialObject *_dynMaterial;

    // other variables:
    C3Vector _dynamicLinearVelocity;
    C3Vector _dynamicAngularVelocity;
    C3Vector _additionalForce;
    C3Vector _additionalTorque;
    int _respondableSuspendCount;
    std::vector<int> _meshIds; // for mesh delete events

    bool _rigidBodyWasAlreadyPutToSleepOnce;

    C3Vector _initialInitialDynamicLinearVelocity;
    C3Vector _initialInitialDynamicAngularVelocity;

#ifdef SIM_WITH_GUI
  public:
    void display(CViewableBase *renderingObject, int displayAttrib);
    void displayInertia(CViewableBase *renderingObject, double size, bool persp);
    void displayFrames(CViewableBase *renderingObject, double size, bool persp);
#endif
};
