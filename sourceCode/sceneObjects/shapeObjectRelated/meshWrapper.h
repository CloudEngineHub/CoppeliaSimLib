#pragma once

#include <colorObject.h>
#include <ser.h>
#include <simMath/3Vector.h>
#include <simMath/7Vector.h>
#include <dynMaterialObject.h>

// ----------------------------------------------------------------------------------------------
// flags: bit0: not writable, bit1: not readable, bit2: removable
#define DEFINE_PROPERTIES                                                                                                                                                                                   \
    FUNCX(propMeshWrap_mass, "mass", sim_propertytype_float, 0, "Mass", "")                                                                                                                                 \
    FUNCX(propMeshWrap_com, "centerOfMass", sim_propertytype_vector3, 0, "Center of mass", "Center of mass, relative to the shape's reference frame")                                                       \
    FUNCX(propMeshWrap_inertia, "inertia", sim_propertytype_floatarray, 0, "Inertia tensor", "Inertia tensor, relative to the shape's reference frame")                                                     \
    FUNCX(propMeshWrap_pmi, "principalMomentOfInertia", sim_propertytype_floatarray, sim_propertyinfo_notwritable, "Principal moment of inertia", "Principal moment of inertia, relative to pmiQuaternion") \
    FUNCX(propMeshWrap_pmiQuaternion, "pmiQuaternion", sim_propertytype_quaternion, sim_propertyinfo_notwritable, "Quaternion of the principal moment of inertia", "Quaternion of the principal moment of inertia, relative to the shape's reference frame")

#define FUNCX(name, str, v1, v2, t1, t2) const SProperty name = {str, v1, v2, t1, t2};
DEFINE_PROPERTIES
#undef FUNCX
#define FUNCX(name, str, v1, v2, t1, t2) name,
const std::vector<SProperty> allProps_meshWrap = {DEFINE_PROPERTIES};
#undef FUNCX
#undef DEFINE_PROPERTIES
// ----------------------------------------------------------------------------------------------

class CViewableBase;
class CShape;
class CMesh;
class CSceneObject;

class CMeshWrapper
{
  public:
    CMeshWrapper();
    virtual ~CMeshWrapper();

    void addItem(CMeshWrapper* m);
    void detachItems();

    virtual void prepareVerticesIndicesNormalsAndEdgesForSerialization();
    virtual void performSceneObjectLoadingMapping(const std::map<int, int>* map);
    virtual void performTextureObjectLoadingMapping(const std::map<int, int>* map, int opType);
    void performDynMaterialObjectLoadingMapping(const std::map<int, int>* map);
    virtual void announceSceneObjectWillBeErased(const CSceneObject* object);
    virtual void setTextureDependencies(int shapeID);
    virtual bool getContainsTransparentComponents() const;
    virtual void displayGhost(const C7Vector& cumulIFrameTr, CShape* geomData, int displayAttrib, bool originalColors,
                              bool backfaceCulling, double transparency, const float* newColors);
    virtual void display(const C7Vector& cumulIFrameTr, CShape* geomData, int displayAttrib,
                         CColorObject* collisionColor, int dynObjFlag_forVisualization, int transparencyHandling,
                         bool multishapeEditSelected);
    virtual void display_extRenderer(const C7Vector& cumulIFrameTr, CShape* geomData, int displayAttrib,
                                     const C7Vector& tr, int shapeHandle, int& componentIndex);
    virtual void display_colorCoded(const C7Vector& cumulIFrameTr, CShape* geomData, int objectId, int displayAttrib);
    virtual CMeshWrapper* copyYourself();
    virtual void scale(double isoVal);
    virtual void setPurePrimitiveType(int theType, double xOrDiameter, double y, double zOrHeight);
    virtual int getPurePrimitiveType() const;
    virtual bool isMesh() const;
    virtual bool isPure() const;
    virtual bool isConvex() const;
    virtual void takeVisualAttributesFrom(CMesh* origin);
    virtual int countTriangles() const;
    virtual void getCumulativeMeshes(const C7Vector& parentCumulTr, std::vector<double>& vertices,
                                     std::vector<int>* indices, std::vector<double>* normals);
    virtual void getCumulativeMeshes(const C7Vector& parentCumulTr, const CMeshWrapper* wrapper,
                                     std::vector<double>& vertices, std::vector<int>* indices,
                                     std::vector<double>* normals);
    virtual void setColor(int colorComponent, const float* rgbData); // cumulative
    virtual void setColor(const CShape* shape, int& elementIndex, const char* colorName, int colorComponent,
                          const float* rgbData, int& rgbDataOffset);
    virtual bool getColor(const char* colorName, int colorComponent, float* rgbData, int& rgbDataOffset) const;
    virtual void getAllMeshComponentsCumulative(const C7Vector& parentCumulTr, std::vector<CMesh*>& shapeComponentList,
                                                std::vector<C7Vector>* OptParentCumulTrList = nullptr);
    virtual CMesh* getMeshComponentAtIndex(const C7Vector& parentCumulTr, int& index,
                                           C7Vector* optParentCumulTrOut = nullptr);
    virtual int getComponentCount() const;
    virtual bool serialize(CSer& ar, const char* shapeName, const C7Vector& parentCumulIFrame, bool rootLevel);
    virtual void flipFaces();
    virtual double getShadingAngle() const;
    virtual void setCulling(bool c);
    virtual void setVisibleEdges(bool v);
    virtual void setShadingAngle(double angle);
    virtual double getEdgeThresholdAngle() const;
    virtual void setEdgeThresholdAngle(double angle);
    virtual void setHideEdgeBorders_OLD(bool v);
    virtual bool getHideEdgeBorders_OLD() const;
    virtual int getTextureCount() const;
    virtual bool hasTextureThatUsesFixedTextureCoordinates() const;
    virtual void removeAllTextures();
    virtual void getColorStrings(std::string& colorStrings, bool onlyNamed) const;
    virtual CMesh* getFirstMesh();
    virtual CMesh* getMeshFromUid(long long int meshUid, const C7Vector& parentCumulTr, C7Vector& shapeRelTr);

    void addSpecializedObjectEventData(int parentObjectHandle, CCbor* ev);
    int setFloatProperty_wrapper(const char* pName, double pState);
    int getFloatProperty_wrapper(const char* pName, double& pState) const;
    int setVector3Property_wrapper(const char* pName, const C3Vector& pState);
    int getVector3Property_wrapper(const char* pName, C3Vector& pState) const;
    int setQuaternionProperty_wrapper(const char* pName, const C4Vector& pState);
    int getQuaternionProperty_wrapper(const char* pName, C4Vector& pState) const;
    int setFloatArrayProperty_wrapper(const char* pName, const double* v, int vL);
    int getFloatArrayProperty_wrapper(const char* pName, std::vector<double>& pState) const;
    int getPropertyName_wrapper(int& index, std::string& pName) const;
    static int getPropertyName_static_wrapper(int& index, std::string& pName);
    int getPropertyInfo_wrapper(const char* pName, int& info, std::string& infoTxt) const;
    static int getPropertyInfo_static_wrapper(const char* pName, int& info, std::string& infoTxt);

    void copyAttributesTo(CMeshWrapper* target);
    void copyWrapperData(CMeshWrapper* target);
    void scaleMassAndInertia(double s);
    void setMass(double m);
    double getMass() const;
    void setName(std::string newName);
    std::string getName() const;

    int getDynMaterialId_old() const;
    void setDynMaterialId_old(int id);
    // ---------------------

    C7Vector getDiagonalInertiaInfo(C3Vector& diagMasslessI) const;
    C7Vector getBB(C3Vector* optBBSize) const;
    virtual void setBBFrame(const C7Vector& bbFrame);
    virtual bool reorientBB(const C4Vector* rot);
    bool getShapeRelIFrame(const C7Vector& parentCumulTr, const CMeshWrapper* wrapper, C7Vector& shapeRelIFrame) const;
    bool getShapeRelBB(const C7Vector& parentCumulTr, const CMeshWrapper* wrapper, C7Vector& shapeRelBB,
                       C3Vector* optBBSize) const;
    C3Vector getCOM() const;
    C7Vector getIFrame() const;
    void setIFrame(const C7Vector& iframe);
    void setCOM(const C3Vector& com);
    C3X3Matrix getInertia() const;
    void setInertia(const C3X3Matrix& im, int modifItemRow = -1, int modifItemCol = -1);
    C3Vector getPMI() const;
    void setPMI(const C3Vector& pmi);
    std::string getInertiaErrorString() const;
    void setInertiaAndComputePMI(const C3X3Matrix& inertia, bool forcePMICalc = false);

    static bool getPMIFromInertia(const C3X3Matrix& tensor, C4Vector& rotation, C3Vector& principalMoments);
    static C3X3Matrix getInertiaFromPMI(const C3Vector& principalMoments, const C7Vector& newFrame);
    static C3X3Matrix getInertiaInNewFrame(const C4Vector& oldFrame, const C3X3Matrix& oldMatrix,
                                           const C4Vector& newFrame);
    static std::string getInertiaErrorString(const C3X3Matrix& matrix);

    std::vector<CMeshWrapper*> childList;

  protected:
    void _commonInit();
    void _computeInertiaFromComposingInertias();
    std::string _name;
    double _mass;

    C7Vector _iFrame;      // Inertia ref. frame, relative to parent _iFrame. Identity if root
    C3Vector _com;         // Center of mass, relative to _iFrame
    C3X3Matrix _iMatrix;   // Mass-less inertia matrix, expressed in the _iFrame
    C3Vector _pmi;         // Principal moment of inertia (calculated from _iMatrix), expressed in the _iFrame
    C4Vector _pmiRotFrame; // Frame of the principal moment of inertia (calculated from _iMatrix), expressed in the _iFrame
    C7Vector _bbFrame;     // Ref. frame of the bounding box and vertices, relative to _iFrame
    C3Vector _bbSize;      // Size of the bounding box, relative to _iFrame

    int _parentObjectHandle;

    int _dynMaterialId_old;
    bool _convex_OLD;
};
