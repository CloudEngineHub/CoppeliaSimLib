#pragma once

#include <ser.h>
#include <cbor.h>
#include <simMath/3Vector.h>

#define PROXSENSOR_MAX_FACE_NUMBER 1024  // Maximum faces of a disk or cone-type sensor
#define PROXSENSOR_MAX_SUBDIVISIONS 1024 // Maximum subdivisions of a cone-type sensor

// ----------------------------------------------------------------------------------------------
// flags: bit0: not writable, bit1: not readable, bit2: removable
#define DEFINE_PROPERTIES \
    FUNCX(propVolume_closeThreshold,                    "closeThreshold",                       sim_propertytype_float,     0, "Close threshold", "Close threshold: if a detection occures below that threshold, it is not registered. 0.0 to disable") \
    FUNCX(propVolume_offset,                            "volume_offset",                        sim_propertytype_float,     0, "Offset", "Offset of detection volume") \
    FUNCX(propVolume_range,                             "volume_range",                         sim_propertytype_float,     0, "Range", "Range/depth of detection volume") \
    FUNCX(propVolume_xSize,                             "volume_xSize",                         sim_propertytype_floatarray,   0, "X-sizes", "X-size (near and far) for pyramid-type volumes") \
    FUNCX(propVolume_ySize,                             "volume_ySize",                         sim_propertytype_floatarray,   0, "Y-sizes", "Y-size (near and far) for pyramid-type volumes") \
    FUNCX(propVolume_radius,                            "volume_radius",                        sim_propertytype_floatarray,   0, "Radius", "Radius for cylinder-, disk- and cone-type volumes") \
    FUNCX(propVolume_angle,                             "volume_angle",                         sim_propertytype_floatarray,   0, "Angles", "Angle and inside gap for disk- and cone-type volumes") \
    FUNCX(propVolume_faces,                             "volume_faces",                         sim_propertytype_intarray,     0, "Faces", "Number of faces (near and far) for cylinder-, disk- and pyramid-type volumes") \
    FUNCX(propVolume_subdivisions,                      "volume_subdivisions",                  sim_propertytype_intarray,     0, "Subdivisions", "Number of subdivisions (near and far) for cone-type volumes") \
    FUNCX(propVolume_edges,                             "volume_edges",                         sim_propertytype_floatarray,    sim_propertyinfo_notwritable, "Volume edges", "List of segments (defined by pairs of end-point coordinates) visualizing the volume") \
    FUNCX(propVolume_closeEdges,                        "volume_closeEdges",                    sim_propertytype_floatarray,    sim_propertyinfo_notwritable, "Volume close edges", "List of segments (defined by pairs of end-point coordinates) visualizing the close threshold of the volume") \

#define FUNCX(name, str, v1, v2, t1, t2) const SProperty name = {str, v1, v2, t1, t2};
DEFINE_PROPERTIES
#undef FUNCX
#define FUNCX(name, str, v1, v2, t1, t2) name,
const std::vector<SProperty> allProps_volume = { DEFINE_PROPERTIES };
#undef FUNCX
#undef DEFINE_PROPERTIES
// ----------------------------------------------------------------------------------------------

enum
{ // IS SERIALIZED!!!!
    PYRAMID_TYPE_CONVEX_VOLUME = 0,
    CYLINDER_TYPE_CONVEX_VOLUME,
    DISC_TYPE_CONVEX_VOLUME,
    CONE_TYPE_CONVEX_VOLUME,
    RAY_TYPE_CONVEX_VOLUME,
};

class CConvexVolume
{
  public:
    CConvexVolume();
    virtual ~CConvexVolume();

    CConvexVolume *copyYourself();
    void scaleVolume(double scalingFactor);
    void serialize(CSer &ar);
    bool getVolumeBoundingBox(C3Vector &minV, C3Vector &maxV) const;
    void disableVolumeComputation(bool disableIt);

    void commonInit();
    C4X4Matrix getTheMatrix(const C3Vector &pt0, const C3Vector &pt1, const C3Vector &pt2, bool tri);
    void add3Values(std::vector<double> &vect, const C4X4Matrix &transf, double x, double y, double z);
    void addAPlane(std::vector<double> *volume, std::vector<double> *normals, double nL, const C4X4Matrix &m,
                   bool inside);
    void computeVolumeEdges(std::vector<double> &edges);
    void getCloseAndFarVolumeEdges(std::vector<double> &allEdges, double distance, std::vector<double> &closeEdges,
                                   std::vector<double> &farEdges);
    void removeEdgesNotInsideVolume(std::vector<double> &edges, std::vector<double> &planes, bool invertSides);
    void generateSphereEdges(std::vector<double> &edges, double radius);

    int setBoolProperty(const char* pName, bool pState);
    int getBoolProperty(const char* pName, bool& pState) const;
    int setIntProperty(const char* pName, int pState);
    int getIntProperty(const char* pName, int& pState) const;
    int setFloatProperty(const char* pName, double pState);
    int getFloatProperty(const char* pName, double& pState) const;
    int setIntArray2Property(const char* pName, const int* pState);
    int getIntArray2Property(const char* pName, int* pState) const;
    int setVector2Property(const char* pName, const double* pState);
    int getVector2Property(const char* pName, double* pState) const;
    int setColorProperty(const char* pName, const float* pState);
    int getColorProperty(const char* pName, float* pState) const;
    int setFloatArrayProperty(const char* pName, const double* v, int vL);
    int getFloatArrayProperty(const char* pName, std::vector<double>& pState) const;
    int setIntArrayProperty(const char* pName, const int* v, int vL);
    int getIntArrayProperty(const char* pName, std::vector<int>& pState) const;
    int getPropertyName(int& index, std::string& pName);
    static int getPropertyName_static(int& index, std::string& pName);
    int getPropertyInfo(const char* pName, int& info, std::string& infoTxt);
    static int getPropertyInfo_static(const char* pName, int& info, std::string& infoTxt);

    void computeVolumes();
    void sendEventData(CCbor *eev);
    void setParentObjHandleForEvents(int h);

    void setVolumeType(int theType, int objectTypeTheVolumeIsFor, double pointSize);
    int getVolumeType();
    void setOffset(double theOffset, bool recomputeVolume = true);
    double getOffset() const;
    void setRange(double theRange, bool recomputeVolume = true);
    double getRange() const;
    void setXSize(double theXSize, bool recomputeVolume = true);
    double getXSize() const;
    void setYSize(double theYSize, bool recomputeVolume = true);
    double getYSize() const;
    void setXSizeFar(double theXSizeFar, bool recomputeVolume = true);
    double getXSizeFar() const;
    void setYSizeFar(double theYSizeFar, bool recomputeVolume = true);
    double getYSizeFar() const;
    void setRadius(double theRadius, bool recomputeVolume = true);
    double getRadius() const;
    void setRadiusFar(double theRadiusFar, bool recomputeVolume = true);
    double getRadiusFar() const;
    void setAngle(double theAngle, bool recomputeVolume = true);
    double getAngle() const;
    void setInsideAngleThing(double theAngleThing, bool recomputeVolume = true);
    double getInsideAngleThing() const;
    void setFaceNumber(int theFaceNumber, bool recomputeVolume = true);
    int getFaceNumber() const;
    void setFaceNumberFar(int theFaceNumberFar, bool recomputeVolume = true);
    int getFaceNumberFar() const;
    void setSubdivisions(int theSubdivisions, bool recomputeVolume = true);
    int getSubdivisions() const;
    void setSubdivisionsFar(int theSubdivisionsFar, bool recomputeVolume = true);
    int getSubdivisionsFar() const;
    void setSmallestDistanceAllowed(double d, bool recomputeVolume = true);
    double getSmallestDistanceAllowed() const;
    void setDefaultVolumeParameters(int objectTypeTheVolumeIsFor, double pointSize);
    void solveInterferences();

    // Variables which need to be serialized & copied
    std::vector<double> planesInside; // Detection volume is formed by the inside volume minus the outside volume
    std::vector<double> planesOutside;
    std::vector<double> normalsInside;
    std::vector<double> normalsOutside;
    std::vector<double> volumeEdges;
    std::vector<double> nonDetectingVolumeEdges;

  protected:
    int _parentObjHandleForEvents;
    bool _volumeComputationTemporarilyDisabled;

    // Variables which need to be serialized & copied
    double _smallestDistanceAllowed; // 0.0 means disabled
    int _volumeType;
    double offset;
    double range;
    double xSize;
    double ySize;
    double xSizeFar;
    double ySizeFar;
    double radius;
    double radiusFar;
    double angle;
    double insideAngleThing;
    int faceNumber;
    int faceNumberFar;
    int subdivisions;
    int subdivisionsFar;
};
