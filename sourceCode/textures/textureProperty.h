#pragma once

#include <textureObject.h>
#include <ser.h>
#include <simMath/7Vector.h>

class CSceneObject;

class CTextureProperty
{
  public:
    CTextureProperty();
    CTextureProperty(int textureOrVisionSensorObjectID);
    virtual ~CTextureProperty();

    CTextureProperty* copyYourself();
    void serialize(CSer& ar);
    bool announceObjectWillBeErased(const CSceneObject* object);
    void performObjectLoadingMapping(const std::map<int, int>* map);
    void performTextureObjectLoadingMapping(const std::map<int, int>* map, int opType);
    void addTextureDependencies(long long int objID, long long int objSubID);
    void scaleObject(double scalingFactor);
    void setInterpolateColors(bool ic);
    bool getInterpolateColors();
    void setApplyMode(int dt);
    int getApplyMode();
    void transformTexturePose(const C7Vector& mCorrection);

    int getTextureObjectID() const;
    void setTextureObjectID(int id);
    CTextureObject* getTextureObject();
    std::vector<float>* getTextureCoordinates(int objectStateId, const std::vector<float>& vertices, const std::vector<int>& triangles);
    std::vector<float>* getFixedTextureCoordinates();
    C7Vector getTextureRelativeConfig();
    void setTextureRelativeConfig(const C7Vector& c);
    void getTextureScaling(double& x, double& y);
    void setTextureScaling(double x, double y);
    void setRepeatU(bool r);
    bool getRepeatU();
    void setRepeatV(bool r);
    bool getRepeatV();

    void setFixedCoordinates(const std::vector<float>* coords); // nullptr to remove them and have calculated coords
    bool getFixedCoordinates();

    void setTextureMapMode(int mode);
    int getTextureMapMode();

    void setStartedTextureObject(CTextureObject* it);
    CTextureObject* getStartedTextureObject();

  private:
    void _commonInit();
    CTextureObject* _startedTexture;

    // to copy and serialize:
    bool _interpolateColor;
    int _applyMode;
    bool _repeatU;
    bool _repeatV;
    int _textureOrVisionSensorObjectID;
    int _textureCoordinateMode;
    C7Vector _textureRelativeConfig;
    double _textureScalingX;
    double _textureScalingY;
    std::vector<float> _fixedTextureCoordinates;

    // do not copy nor serialize:
    int _objectStateId;
    std::vector<float> _calculatedTextureCoordinates;

#ifdef SIM_WITH_GUI
  public:
    int* getTexCoordBufferIdPointer();

  private:
    int _texCoordBufferId; // used for VBOs
#endif
};
