#pragma once

#include "vThread.h"
#include "ser.h"
#ifdef SIM_WITH_GUI
#include "vMenubar.h"
#endif

class CSimulation
{
public:
    CSimulation();
    virtual ~CSimulation();
    void simulationAboutToStart();
    void simulationEnded();
    void setUpDefaultValues();
    bool startOrResumeSimulation();
    bool stopSimulation();
    bool pauseSimulation();
    bool isSimulationRunning() const;
    bool isSimulationPaused() const;
    bool isSimulationStopped() const;
    void advanceSimulationByOneStep();
    void setIsRealTimeSimulation(bool realTime);
    bool getIsRealTimeSimulation() const;
    void serialize(CSer& ar);

    float getSimulationTime() const;
    float getSimulationTime_real() const;
    void setResetSceneAtSimulationEnd(bool r);
    bool getResetSceneAtSimulationEnd() const;
    void setRemoveNewObjectsAtSimulationEnd(bool r);
    bool getRemoveNewObjectsAtSimulationEnd() const;

    void incrementStopRequestCounter();
    int getStopRequestCounter() const;
    bool didStopRequestCounterChangeSinceSimulationStart() const;

    void pushGenesisEvents() const;


    bool canGoSlower() const;
    bool canGoFaster() const;
    bool getSettingsAreDefault() const;

    void setSpeedModifierCount(int sm);
    int getSpeedModifierCount() const;

    void setTimeStep(float dt);
    float getTimeStep() const;

    void setPassesPerRendering(int n);
    int getPassesPerRendering() const;

    void setRealTimeCoeff(double coeff);
    double getRealTimeCoeff() const;

    bool getDynamicContentVisualizationOnly() const;
    void setDynamicContentVisualizationOnly(bool dynOnly);

    void adjustRealTimeTimer(float deltaTime);

    void setFullscreenAtSimulationStart(bool f);
    bool getFullscreenAtSimulationStart() const;


    bool isRealTimeCalculationStepNeeded() const;

    void setSimulationState(int state);

    bool processCommand(int commandID);
    bool getInfo(std::string& txtLeft,std::string& txtRight,int& index) const;

    void setPauseAtError(bool br);
    bool getPauseAtError() const;
    void pauseOnErrorRequested();
    void setPauseTime(float time);
    float getPauseTime() const;
    bool getPauseAtSpecificTime() const;
    void setPauseAtSpecificTime(bool e);
    int getSimulationState() const;

#ifdef SIM_WITH_GUI
    bool showAndHandleEmergencyStopButton(bool showState,const char* scriptName);
    void keyPress(int key);
    void addMenu(VMenu* menu);
#endif

private:
    float _getNewTimeStep(int newSpeedModifierCount) const;
    bool _goFasterOrSlower(int action);
    void _setSimulationTime(float t);
    void _clearSimulationTimeHistory();
    void _addToSimulationTimeHistory(float simTime,float simTimeReal);
    bool _getSimulationTimeHistoryDurations(float& simTime,float& simTimeReal) const;

    double _getSpeedModifier_forRealTimeCoefficient() const;

    bool _resetSimulationAtEnd;
    bool _removeNewObjectsAtSimulationEnd;

    bool _fullscreenAtSimulationStart;

    float _simulationTime;
    float simulationTime_real;
    float simulationTime_real_noCatchUp;

    int simulationTime_real_lastInMs;
    float _realTimeCorrection;

    int _simulationStepCount;

    int _disableWarningsFlags;

    int _simulationPassesPerRendering;
    float _simulationTimeStep;
    int _speedModifierCount;
    int _desiredFasterOrSlowerSpeed;


    int timeInMsWhenStopWasPressed;

    bool _realTimeSimulation;
    double _realTimeCoefficient;

    float _simulationTimeToPause;
    bool _pauseAtSpecificTime;
    bool _pauseAtError;
    bool _pauseOnErrorRequested;
    bool _hierarchyWasEnabledBeforeSimulation;


    int _simulationState;
    bool _requestToStop; // Indicates a passage from paused to stop (but through running!). Check the simulation state diagram!!
    bool _requestToPause; // added on 2010/01/13 (simPauseSimulation didn't work in the first simulation pass)

    // Following is needed to determine if we are really in real-time mode
    std::vector<float> simulationTime_history;
    std::vector<float> simulationTime_real_history;

    bool _initialValuesInitialized;
    float _initialSimulationTimeStep;
    bool _initialPauseAtSpecificTime;
    bool _dynamicContentVisualizationOnly;

    int _stopRequestCounter;
    int _stopRequestCounterAtSimulationStart;
};
