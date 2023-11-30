#pragma once

#include <colorObject.h>
#include <thumbnail.h>
#ifdef SIM_WITH_GUI
#include <vMenubar.h>
#endif

class CCamera;
class CViewableBase;

class CEnvironment
{
  public:
    CEnvironment();
    virtual ~CEnvironment();

    void setUpDefaultValues();

    void serialize(CSer &ar);
    void setAcknowledgement(const char *a);
    std::string getAcknowledgement() const;
    void setVisualizeWirelessEmitters(bool v);
    bool getVisualizeWirelessEmitters() const;
    void setVisualizeWirelessReceivers(bool v);
    bool getVisualizeWirelessReceivers() const;
    void setShapeTexturesEnabled(bool e);
    bool getShapeTexturesEnabled() const;

    void pushGenesisEvents() const;

    static int getNextSceneUniqueId();
    static void setShapeTexturesTemporarilyDisabled(bool d);
    static bool getShapeTexturesTemporarilyDisabled();
    static void setShapeEdgesTemporarilyDisabled(bool d);
    static bool getShapeEdgesTemporarilyDisabled();
    static void setCustomUisTemporarilyDisabled(bool d);
    static bool getCustomUisTemporarilyDisabled();

    void set2DElementTexturesEnabled(bool e);
    bool get2DElementTexturesEnabled() const;

    void setRequestFinalSave(bool finalSaveActivated);
    bool getRequestFinalSave() const;
    void setSceneLocked();
    bool getSceneLocked() const;
    void setCalculationMaxTriangleSize(double s);
    double getCalculationMaxTriangleSize() const;
    void setCalculationMinRelTriangleSize(double s);
    double getCalculationMinRelTriangleSize() const;
    void setSaveExistingCalculationStructures(bool s);
    bool getSaveExistingCalculationStructures() const;
    void setSaveExistingCalculationStructuresTemp(bool s);
    bool getSaveExistingCalculationStructuresTemp() const;

    int getSceneUniqueID() const;

    void setSceneCanBeDiscardedWhenNewSceneOpened(bool canBeDiscarded);
    bool getSceneCanBeDiscardedWhenNewSceneOpened() const;

    std::string getExtensionString() const;
    void setExtensionString(const char *str);

    void setFogEnabled(bool e);
    bool getFogEnabled() const;
    void setFogDensity(double d);
    double getFogDensity() const;
    void setFogStart(double s);
    double getFogStart() const;
    void setFogEnd(double e);
    double getFogEnd() const;
    void setFogType(double t);
    int getFogType() const;
    bool areNonAmbientLightsActive() const;
    void setNonAmbientLightsActive(bool a);
    void setActiveLayers(unsigned short l);
    unsigned short getActiveLayers() const;

    void generateNewUniquePersistentIdString();
    std::string getUniquePersistentIdString() const;
    bool getSceneIsClosingFlag() const;
    void setSceneIsClosingFlag(bool closing);

    quint64 autoSaveLastSaveTimeInSecondsSince1970;
    float fogBackgroundColor[3];
    float backGroundColor[3];
    float backGroundColorDown[3];
    float ambientLightColor[3];
    CColorObject wirelessEmissionVolumeColor;
    CColorObject wirelessReceptionVolumeColor;

    CThumbnail modelThumbnail_notSerializedHere;

  protected:
    unsigned short _activeLayers;

    bool _nonAmbientLightsAreActive;
    bool fogEnabled;
    double fogDensity;
    double fogStart;
    double fogEnd;
    int fogType; // 0=linear, 1=exp, 2=exp2

    std::string _acknowledgement;
    std::string _sceneUniquePersistentIdString;
    bool _visualizeWirelessEmitters;
    bool _visualizeWirelessReceivers;
    bool _requestFinalSave;
    bool _sceneIsLocked;
    bool _shapeTexturesEnabled;
    bool _2DElementTexturesEnabled;
    double _calculationMaxTriangleSize;
    double _calculationMinRelTriangleSize;
    bool _saveExistingCalculationStructures;
    bool _saveExistingCalculationStructuresTemp;
    bool _sceneCanBeDiscardedWhenNewSceneOpened;

    bool _sceneIsClosingFlag;
    std::string _extensionString;

    int _sceneUniqueID;

    static bool _shapeTexturesTemporarilyDisabled;
    static bool _shapeEdgesTemporarilyDisabled;
    static bool _customUisTemporarilyDisabled;

    static int _nextSceneUniqueID;

#ifdef SIM_WITH_GUI
  public:
    void setBackgroundColor(int viewSize[2]);
    void activateAmbientLight(bool a);
    void activateFogIfEnabled(CViewableBase *viewable, bool forDynamicContentOnly);
    void deactivateFog();
    void temporarilyDeactivateFog();
    void reactivateFogThatWasTemporarilyDisabled();
#endif
};
