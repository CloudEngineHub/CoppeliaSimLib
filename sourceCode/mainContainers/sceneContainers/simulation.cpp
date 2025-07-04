#include <simInternal.h>
#include <simulation.h>
#include <graph.h>
#include <tt.h>
#include <utils.h>
#include <graphingRoutines_old.h>
#include <app.h>
#include <simStrings.h>
#include <vDateTime.h>
#include <persistentDataContainer.h>
#include <simFlavor.h>
#ifdef SIM_WITH_GUI
#include <guiApp.h>
#endif

CSimulation::CSimulation()
{
    _stopRequestCounter = 0;
    setUpDefaultValues();
}

CSimulation::~CSimulation()
{ // beware, the current world could be nullptr
    setUpDefaultValues();
}

void CSimulation::setUpDefaultValues()
{
    _dynamicContentVisualizationOnly = false;
    _simulationState = sim_simulation_stopped;
    _simulationTime = 0.0;

    simulationTime_real = 0.0;
    simulationTime_real_noCatchUp = 0.0;
    _clearSimulationTimeHistory();

    _simulationTimeStep = 0.05;
    _simulationPassesPerRendering = 1;
    _desiredFasterOrSlowerSpeed = 0;
    _realTimeCoefficient = 1.0;
    _simulationStepCount = 0;
    _simulationTimeToPause = 10.0;
    _pauseAtSpecificTime = false;
    _pauseAtError = true;
    _hierarchyWasEnabledBeforeSimulation = false;
    _initialValuesInitialized = false;
    _removeNewObjectsAtSimulationEnd = true;
    _realTimeSimulation = false;
    _fullscreenAtSimulationStart = false;
    _speedModifierCount = 0;
    _requestToStop = false;
}

int CSimulation::getSpeedModifierCount() const
{
    return (_speedModifierCount);
}

void CSimulation::setSpeedModifierCount(int sm)
{
    while (sm != _speedModifierCount)
    {
        if (sm > _speedModifierCount)
        {
            if (!_goFasterOrSlower(1))
                break;
        }
        else
        {
            if (!_goFasterOrSlower(-1))
                break;
        }
    }
}

double CSimulation::_getSpeedModifier_forRealTimeCoefficient() const
{
    double retVal = 1.0;
    if (!isSimulationStopped())
    {
        if (_speedModifierCount >= 0)
            retVal = pow(2.0, double(_speedModifierCount));
        else
            retVal = _simulationTimeStep / _initialSimulationTimeStep;
    }
    return (retVal);
}

void CSimulation::setFullscreenAtSimulationStart(bool f)
{
    _fullscreenAtSimulationStart = f;
}

bool CSimulation::getFullscreenAtSimulationStart() const
{
    return (_fullscreenAtSimulationStart);
}

void CSimulation::setRemoveNewObjectsAtSimulationEnd(bool r)
{
    bool diff = (_removeNewObjectsAtSimulationEnd != r);
    if (diff)
    {
        _removeNewObjectsAtSimulationEnd = r;
        if (App::worldContainer->getEventsEnabled())
        {
            CCbor* ev = App::worldContainer->createObjectChangedEvent(sim_handle_scene, propSim_removeNewObjectsAtEnd.name, true);
            ev->appendKeyBool(propSim_removeNewObjectsAtEnd.name, _removeNewObjectsAtSimulationEnd);
            App::worldContainer->pushEvent();
        }
    }
}

bool CSimulation::getRemoveNewObjectsAtSimulationEnd() const
{
    return (_removeNewObjectsAtSimulationEnd);
}

void CSimulation::simulationAboutToStart()
{ // careful here: this is called by this through App::wc->simulationAboutToStart!!
    _initialValuesInitialized = true;
    _initialPauseAtSpecificTime = _pauseAtSpecificTime;
    _speedModifierCount = 0;
    _initialSimulationTimeStep = _simulationTimeStep;
    _dynamicContentVisualizationOnly = false;
    _desiredFasterOrSlowerSpeed = 0;
    _stopRequestCounterAtSimulationStart = _stopRequestCounter;
#ifdef SIM_WITH_GUI
    if ((GuiApp::mainWindow != nullptr) && App::userSettings->sceneHierarchyHiddenDuringSimulation)
    {
        _hierarchyWasEnabledBeforeSimulation = App::getHierarchyEnabled();
        GuiApp::mainWindow->dlgCont->processCommand(CLOSE_HIERARCHY_DLG_CMD);
    }
#endif
    if ((!App::currentWorld->dynamicsContainer->getSettingsAreDefault()) || (!getSettingsAreDefault()))
        App::logMsg(sim_verbosity_scriptwarnings,
                    "Detected non-default settings (time steps and/or dyn. engine global settings).");
}

void CSimulation::simulationEnded()
{ // careful here: this is called by this through App::wc->simulationEnded!!
    TRACE_INTERNAL;

#ifdef SIM_WITH_GUI
    showAndHandleEmergencyStopButton(false, "");
#endif
    _dynamicContentVisualizationOnly = false;
#ifdef SIM_WITH_GUI
    if (GuiApp::mainWindow != nullptr)
        GuiApp::mainWindow->simulationRecorder->stopRecording(false);
#endif
    if (_initialValuesInitialized)
    {
        setPauseAtSpecificTime(_initialPauseAtSpecificTime);
        setTimeStep(_initialSimulationTimeStep, true);
    }
    _initialValuesInitialized = false;
    _setSpeedModifierRaw(0);
    _desiredFasterOrSlowerSpeed = 0;

#ifdef SIM_WITH_GUI
    if ((GuiApp::mainWindow != nullptr) && _hierarchyWasEnabledBeforeSimulation &&
        App::userSettings->sceneHierarchyHiddenDuringSimulation)
        GuiApp::mainWindow->dlgCont->processCommand(OPEN_HIERARCHY_DLG_CMD);
#endif
}

bool CSimulation::getDynamicContentVisualizationOnly() const
{
    return (_dynamicContentVisualizationOnly);
}

void CSimulation::setDynamicContentVisualizationOnly(bool dynOnly)
{
    if ((!isSimulationStopped()) || (!dynOnly))
        _dynamicContentVisualizationOnly = dynOnly;
#ifdef SIM_WITH_GUI
    GuiApp::setFullDialogRefreshFlag(); // so we reflect the effect also to the toolbar button
    GuiApp::setToolbarRefreshFlag();
#endif
}

bool CSimulation::canGoSlower() const
{
    bool retVal = false;
    if (isSimulationRunning())
    {
        if (_speedModifierCount > 0)
            retVal = true;
        else
        {
            double newDt = _getNewTimeStep(_speedModifierCount - 1);
            retVal = (newDt != 0.0);
        }
    }
    return (retVal);
}

bool CSimulation::canGoFaster() const
{
    bool retVal = false;
    if (isSimulationRunning())
        retVal = (_speedModifierCount < 6);
    return (retVal);
}

bool CSimulation::getSettingsAreDefault() const
{
    double dt = _simulationTimeStep;
    if (!isSimulationStopped())
        dt = _initialSimulationTimeStep;
    return (fabs(dt - 0.05) < 0.0001);
}

void CSimulation::startOrResumeSimulation()
{
    TRACE_INTERNAL;
    _requestToPause = false;
    _requestToStop = false;
    if (isSimulationStopped())
    {
#ifdef SIM_WITH_GUI
        GuiApp::setFullScreen(_fullscreenAtSimulationStart);
#endif
        App::worldContainer->simulationAboutToStart();
        _realTimeCorrection = 0.0;
        _setSimulationTime(0.0);
        simulationTime_real = 0.0;
        simulationTime_real_noCatchUp = 0.0;
        _clearSimulationTimeHistory();
        simulationTime_real_lastInMs = (int)VDateTime::getTimeInMs();
        setSimulationStepCount(0);
        setSimulationState(sim_simulation_advancing_running);
    }
    else if (isSimulationPaused())
    {
        App::worldContainer->simulationAboutToResume();
        _realTimeCorrection = 0.0;
        setSimulationState(sim_simulation_advancing_running);
        simulationTime_real_lastInMs = (int)VDateTime::getTimeInMs();
        advanceSimulationByOneStep();
    }
}

void CSimulation::stopSimulation()
{
    TRACE_INTERNAL;
#ifdef SIM_WITH_GUI
    if (getSimulationState() != sim_simulation_stopped)
        GuiApp::setFullScreen(false);
#endif

    if (getSimulationState() != sim_simulation_advancing_lastbeforestop)
    {
        if (getSimulationState() == sim_simulation_paused)
        {
            App::worldContainer->simulationAboutToResume();
            setSimulationState(sim_simulation_advancing_running);
            advanceSimulationByOneStep(); // we paused in last simulation step. So we need to step here
        }
        if (!_requestToStop)
        {
            timeInMsWhenStopWasPressed = (int)VDateTime::getTimeInMs();
            _requestToStop = true;
        }
    }
}

void CSimulation::pauseSimulation()
{
    _requestToPause = ((_simulationState != sim_simulation_stopped) && (_simulationState != sim_simulation_paused) && (!_requestToStop));
}

bool CSimulation::isSimulationRunning() const
{
    return ((_simulationState & sim_simulation_advancing) != 0);
}

bool CSimulation::isSimulationStopped() const
{
    return (_simulationState == sim_simulation_stopped);
}

bool CSimulation::isSimulationPaused() const
{
    return (_simulationState == sim_simulation_paused);
}

void CSimulation::adjustRealTimeTimer(double deltaTime)
{
    _realTimeCorrection += deltaTime;
}

void CSimulation::advanceSimulationByOneStep()
{
    TRACE_INTERNAL;
    if (isSimulationRunning())
    {
        if (_pauseAtSpecificTime && (getSimulationTime() >= _simulationTimeToPause))
        {
            _requestToPause = true;
            setPauseAtSpecificTime(false);
        }
        if (_requestToPause)
        {
            setSimulationState(sim_simulation_paused);
            App::worldContainer->simulationPaused(); // calls sim_syscb_suspend
            _requestToPause = false;
        }
        else
        {
            App::worldContainer->simulationAboutToStep();

            setSimulationStepCount(_simulationStepCount + 1);
            if (_simulationStepCount == 1)
                _realTimeCorrection = 0.0;

            _setSimulationTime(getSimulationTime() + getTimeStep());

            int ct = (int)VDateTime::getTimeInMs();
            double drt = (double(VDateTime::getTimeDiffInMs(simulationTime_real_lastInMs)) / 1000.0 + _realTimeCorrection) *
                         getRealTimeCoeff();
            simulationTime_real += drt;
            simulationTime_real_noCatchUp += drt;
            if (simulationTime_real_noCatchUp > getSimulationTime() + getTimeStep())
                simulationTime_real_noCatchUp = getSimulationTime() + getTimeStep();
            _realTimeCorrection = 0.0;
            simulationTime_real_lastInMs = ct;
            _addToSimulationTimeHistory(getSimulationTime(), simulationTime_real);

            if (getSimulationState() == sim_simulation_advancing_running)
            {
                if (_requestToStop)
                {
                    setSimulationState(sim_simulation_advancing_lastbeforestop);
                    _requestToStop = false;
                }
            }
            else if (getSimulationState() == sim_simulation_advancing_lastbeforestop)
            {
                App::worldContainer->simulationAboutToEnd();
                setSimulationState(sim_simulation_stopped);
                App::worldContainer->simulationEnded(_removeNewObjectsAtSimulationEnd);
            }
            while (_desiredFasterOrSlowerSpeed > 0)
            {
                _goFasterOrSlower(1);
                _desiredFasterOrSlowerSpeed--;
            }
            while (_desiredFasterOrSlowerSpeed < 0)
            {
                _goFasterOrSlower(-1);
                _desiredFasterOrSlowerSpeed++;
            }
        }
    }
}

int CSimulation::getSimulationState() const
{
    return _simulationState;
}

void CSimulation::setTimeStep(double dt, bool alsoWhenRunning /*= false*/)
{
    if (isSimulationStopped() || alsoWhenRunning)
    {
        if (dt < 0.0001)
            dt = 0.0001;
        if (dt > 10.0)
            dt = 10.0;
        bool diff = (_simulationTimeStep != dt);
        if (diff)
        {
            _simulationTimeStep = dt;
            if (App::worldContainer->getEventsEnabled())
            {
                CCbor* ev = App::worldContainer->createObjectChangedEvent(sim_handle_scene, propSim_timeStep.name, true);
                ev->appendKeyDouble(propSim_timeStep.name, _simulationTimeStep);
                App::worldContainer->pushEvent();
            }
#ifdef SIM_WITH_GUI
            GuiApp::setFullDialogRefreshFlag();
#endif
        }
    }
}

double CSimulation::getTimeStep() const
{
    return (_simulationTimeStep);
}

int CSimulation::getPassesPerRendering() const
{
    int retVal = _simulationPassesPerRendering;
    if (_speedModifierCount > 0)
        retVal *= int(pow(2.0, double(_speedModifierCount)) + 0.1);
    return (retVal);
}

double CSimulation::getRealTimeCoeff() const
{
    return (_realTimeCoefficient * _getSpeedModifier_forRealTimeCoefficient());
}

void CSimulation::setIsRealTimeSimulation(bool realTime)
{
    if (isSimulationStopped())
    {
        bool diff = (_realTimeSimulation != realTime);
        if (diff)
        {
            _realTimeSimulation = realTime;
            if (App::worldContainer->getEventsEnabled())
            {
                CCbor* ev = App::worldContainer->createObjectChangedEvent(sim_handle_scene, propSim_realtimeSimulation.name, true);
                ev->appendKeyBool(propSim_realtimeSimulation.name, _realTimeSimulation);
                App::worldContainer->pushEvent();
            }
        }
    }
}

bool CSimulation::isRealTimeCalculationStepNeeded() const
{
    bool retVal = false;
    if (_realTimeSimulation && isSimulationRunning())
    {
        double crt = simulationTime_real_noCatchUp +
                     double(VDateTime::getTimeDiffInMs(simulationTime_real_lastInMs)) * getRealTimeCoeff() / 1000.0;
        retVal = (getSimulationTime() + getTimeStep() < crt);
    }
    return (retVal);
}

bool CSimulation::getIsRealTimeSimulation() const
{
    return (_realTimeSimulation);
}

void CSimulation::setRealTimeCoeff(double coeff)
{
    if (coeff < 0.0)
        coeff = 0.0;
    if (coeff > 100.0)
        coeff = 100.0;
    bool diff = (_realTimeCoefficient != coeff);
    if (diff)
    {
        _realTimeCoefficient = coeff;
        if (App::worldContainer->getEventsEnabled())
        {
            CCbor* ev = App::worldContainer->createObjectChangedEvent(sim_handle_scene, propSim_realtimeModifier.name, true);
            ev->appendKeyDouble(propSim_realtimeModifier.name, _realTimeCoefficient);
            App::worldContainer->pushEvent();
        }
    }
}

void CSimulation::setPassesPerRendering(int n)
{
    if (isSimulationStopped())
    {
        tt::limitValue(1, 200, n);
        bool diff = (_simulationPassesPerRendering != n);
        if (diff)
        {
            _simulationPassesPerRendering = n;
            if (App::worldContainer->getEventsEnabled())
            {
                CCbor* ev = App::worldContainer->createObjectChangedEvent(sim_handle_scene, propSim_stepsPerRendering.name, true);
                ev->appendKeyInt(propSim_stepsPerRendering.name, _simulationPassesPerRendering);
                App::worldContainer->pushEvent();
            }
        }
    }
}

void CSimulation::setSimulationStepCount(int cnt)
{
    bool diff = (_simulationStepCount != cnt);
    if (diff)
    {
        _simulationStepCount = cnt;
        if (App::worldContainer->getEventsEnabled())
        {
            CCbor* ev = App::worldContainer->createObjectChangedEvent(sim_handle_scene, propSim_stepCount.name, true);
            ev->appendKeyInt(propSim_stepCount.name, _simulationStepCount);
            App::worldContainer->pushEvent();
        }
    }
}

void CSimulation::appendGenesisData(CCbor* ev) const
{
#if SIM_EVENT_PROTOCOL_VERSION == 2
    ev->appendKeyInt("state", _simulationState);
    ev->appendKeyInt("time", int(_simulationTime * 1000.0));
#else
    ev->appendKeyBool(propSim_removeNewObjectsAtEnd.name, _removeNewObjectsAtSimulationEnd);
    ev->appendKeyBool(propSim_realtimeSimulation.name, _realTimeSimulation);
    ev->appendKeyBool(propSim_pauseSimulationAtTime.name, _pauseAtSpecificTime);
    ev->appendKeyBool(propSim_pauseSimulationAtError.name, _pauseAtError);
    ev->appendKeyInt(propSim_simulationState.name, _simulationState);
    ev->appendKeyInt(propSim_stepCount.name, _simulationStepCount);
    ev->appendKeyInt(propSim_stepsPerRendering.name, _simulationPassesPerRendering);
    ev->appendKeyInt(propSim_speedModifier.name, _speedModifierCount);
    ev->appendKeyDouble(propSim_simulationTime.name, _simulationTime);
    ev->appendKeyDouble(propSim_timeStep.name, _simulationTimeStep);
    ev->appendKeyDouble(propSim_timeToPause.name, _simulationTimeToPause);
    ev->appendKeyDouble(propSim_realtimeModifier.name, _realTimeCoefficient);
#endif
}

void CSimulation::setSimulationState(int state)
{
    bool diff = (_simulationState != state);
    if (diff)
    {
        _simulationState = state;
        if (App::worldContainer->getEventsEnabled())
        {
#if SIM_EVENT_PROTOCOL_VERSION == 2
            const char* cmd = "state";
            CCbor* ev = App::worldContainer->createObjectChangedEvent(sim_handle_scene, cmd, true);
            ev->appendKeyInt(cmd, _simulationState);
#else
            CCbor* ev = App::worldContainer->createObjectChangedEvent(sim_handle_scene, propSim_simulationState.name, true);
            ev->appendKeyInt(propSim_simulationState.name, _simulationState);
#endif
            App::worldContainer->pushEvent();
        }
    }
}

void CSimulation::_clearSimulationTimeHistory()
{
    simulationTime_history.clear();
    simulationTime_real_history.clear();
}

void CSimulation::_addToSimulationTimeHistory(double simTime, double simTimeReal)
{
    simulationTime_history.push_back(simTime);
    simulationTime_real_history.push_back(simTimeReal);
    if (simulationTime_history.size() > 10)
    {
        simulationTime_history.erase(simulationTime_history.begin());
        simulationTime_real_history.erase(simulationTime_real_history.begin());
    }
}

bool CSimulation::_getSimulationTimeHistoryDurations(double& simTime, double& simTimeReal) const
{
    bool retVal = false;
    if (simulationTime_history.size() < 2)
    {
        simTime = 0.0;
        simTimeReal = 0.0;
    }
    else
    {
        simTime = simulationTime_history[simulationTime_history.size() - 1] - simulationTime_history[0];
        simTimeReal =
            simulationTime_real_history[simulationTime_real_history.size() - 1] - simulationTime_real_history[0];
        retVal = true;
    }
    return (retVal);
}

void CSimulation::setPauseAtError(bool br)
{
    bool diff = (_pauseAtError != br);
    if (diff)
    {
        _pauseAtError = br;
        if (App::worldContainer->getEventsEnabled())
        {
            CCbor* ev = App::worldContainer->createObjectChangedEvent(sim_handle_scene, propSim_pauseSimulationAtError.name, true);
            ev->appendKeyBool(propSim_pauseSimulationAtError.name, _pauseAtError);
            App::worldContainer->pushEvent();
        }
    }
}

bool CSimulation::getPauseAtError() const
{
    return (_pauseAtError);
}

void CSimulation::pauseOnErrorRequested()
{
    if (isSimulationRunning())
    {
        if (_pauseAtError && (!_requestToStop))
            _requestToPause = true;
    }
}

void CSimulation::setPauseTime(double time)
{
    if (time < 0.001)
        time = 0.001;
    if (time > 604800.0)
        time = 604800.0;
    bool diff = (_simulationTimeToPause != time);
    if (diff)
    {
        _simulationTimeToPause = time;
        if (App::worldContainer->getEventsEnabled())
        {
            CCbor* ev = App::worldContainer->createObjectChangedEvent(sim_handle_scene, propSim_timeToPause.name, true);
            ev->appendKeyDouble(propSim_timeToPause.name, _simulationTimeToPause);
            App::worldContainer->pushEvent();
        }
    }
}

double CSimulation::getPauseTime() const
{
    return (_simulationTimeToPause);
}

bool CSimulation::getPauseAtSpecificTime() const
{
    return (_pauseAtSpecificTime);
}

void CSimulation::setPauseAtSpecificTime(bool e)
{
    bool diff = (_pauseAtSpecificTime != e);
    if (diff)
    {
        _pauseAtSpecificTime = e;
        if (App::worldContainer->getEventsEnabled())
        {
            CCbor* ev = App::worldContainer->createObjectChangedEvent(sim_handle_scene, propSim_pauseSimulationAtTime.name, true);
            ev->appendKeyBool(propSim_pauseSimulationAtTime.name, _pauseAtSpecificTime);
            App::worldContainer->pushEvent();
        }
    }
}

double CSimulation::getSimulationTime() const
{
    return _simulationTime;
}

void CSimulation::_setSimulationTime(double t)
{
    bool diff = (_simulationTime != t);
    if (diff)
    {
        _simulationTime = t;
        if (App::worldContainer->getEventsEnabled())
        {
#if SIM_EVENT_PROTOCOL_VERSION == 2
            const char* cmd = "time";
            CCbor* ev = App::worldContainer->createObjectChangedEvent(sim_handle_scene, cmd, true);
            ev->appendKeyInt(cmd, int(_simulationTime * 1000.0));
#else
            CCbor* ev = App::worldContainer->createObjectChangedEvent(sim_handle_scene, propSim_simulationTime.name, true);
            ev->appendKeyDouble(propSim_simulationTime.name, _simulationTime);
#endif
            App::worldContainer->pushEvent();
        }
    }
}

double CSimulation::getSimulationTime_real() const
{
    return (simulationTime_real);
}

double CSimulation::_getNewTimeStep(int newSpeedModifierCount) const
{
    double ddt = App::currentWorld->dynamicsContainer->getEffectiveStepSize();
    double dt = _simulationTimeStep;
    if (!isSimulationStopped())
        dt = _initialSimulationTimeStep;
    for (int i = 0; i < -newSpeedModifierCount; i++)
    {
        dt *= 0.5;
        if ((dt * 1.01 - ddt) < 0.0)
            return (0.0);
        if (fmod(dt * 1.00001, ddt) > ddt * 0.01)
        {
            double oldDt = dt;
            dt = ddt;
            while (dt + ddt < oldDt)
                dt += ddt;
        }
    }
    return (dt);
}

bool CSimulation::_goFasterOrSlower(int action)
{
    bool retVal = false;
    if (!App::currentWorld->simulation->isSimulationStopped())
    {
        int sm = _speedModifierCount;
        if (action < 0)
        { // We wanna go slower
            if (sm > 0)
            {
                sm--;
                retVal = true;
            }
            else
            {
                double newDt = _getNewTimeStep(sm - 1);
                if (newDt != 0.0)
                {
                    sm--;
                    setTimeStep(newDt, true);
                    retVal = true;
                }
            }
        }
        if (action > 0)
        { // We wanna go faster
            if (canGoFaster())
            {
                sm++;
                if (sm <= 0)
                    setTimeStep(_getNewTimeStep(sm), true);
                retVal = true;
            }
        }
        if (retVal)
            _setSpeedModifierRaw(sm);
    }
    return (retVal);
}

void CSimulation::_setSpeedModifierRaw(int sm)
{
    bool diff = (_speedModifierCount != sm);
    if (diff)
    {
        _speedModifierCount = sm;
        if (App::worldContainer->getEventsEnabled())
        {
            const char* cmd = propSim_speedModifier.name;
            CCbor* ev = App::worldContainer->createObjectChangedEvent(sim_handle_scene, cmd, true);
            ev->appendKeyInt(cmd, _speedModifierCount);
            App::worldContainer->pushEvent();
        }
#ifdef SIM_WITH_GUI
        GuiApp::setLightDialogRefreshFlag();
        GuiApp::setToolbarRefreshFlag();
#endif
    }
}

void CSimulation::incrementStopRequestCounter()
{
    _stopRequestCounter++;
}

int CSimulation::getStopRequestCounter() const
{
    return (_stopRequestCounter);
}

bool CSimulation::didStopRequestCounterChangeSinceSimulationStart() const
{
    return (_stopRequestCounter != _stopRequestCounterAtSimulationStart);
}

bool CSimulation::getInfo(std::string& txtLeft, std::string& txtRight, int& index) const
{
    bool retVal = false;
    if (!isSimulationStopped())
    {
        if (index == 0)
        {
            txtLeft = "Simulation time:";
            if (_realTimeSimulation)
            {
                txtRight = "";
                double st, str;
                if (_getSimulationTimeHistoryDurations(st, str))
                {
                    if (abs((st - str) / str) > 0.1)
                        txtRight = "&&fg930"; // When current simulation speed is too slow
                    else
                    {
                        if (abs(getSimulationTime() - simulationTime_real) > 10.0 * getTimeStep())
                            txtRight = "&&fg930"; // When simulation is behind
                    }
                }
                txtRight += utils::getTimeString(false, getSimulationTime() + 0.0001) + " &&fg@@@(real time: ";
                if (abs(getRealTimeCoeff() - 1.0) < 0.01)
                    txtRight += utils::getTimeString(false, simulationTime_real + 0.0001) + ")";
                else
                {
                    txtRight += utils::getTimeString(false, simulationTime_real + 0.0001) + " (x";
                    txtRight += utils::getMultString(false, getRealTimeCoeff()) + "))";
                }
                if (simulationTime_real != 0.0)
                    txtRight +=
                        " (real time fact=" + utils::getMultString(false, getSimulationTime() / simulationTime_real) +
                        ")";
                txtRight += " (dt=" + utils::getDoubleString(false, getTimeStep() * 1000.0, 1, 2) + " ms)";
            }
            else
            {
                txtRight = "&&fg@@@" + utils::getTimeString(false, getSimulationTime() + 0.0001);
                txtRight += " (dt=" + utils::getDoubleString(false, getTimeStep() * 1000.0, 1, 2) +
                            " ms, ppf=" + std::to_string(getPassesPerRendering()) + ")";
            }
            retVal = true;
        }
        else
            index = 0;
        index++;
    }
    return (retVal);
}

void CSimulation::serialize(CSer& ar)
{
    if (ar.isBinary())
    {
        if (ar.isStoring())
        {                            // Storing
            ar.storeDataName("Sts"); // for backward compatibility (03/03/2016), keep before St2
            ar << (float)_simulationTimeStep;
            ar.flush();

            ar.storeDataName("St2"); // for backward compatibility (05/09/2022), keep before St3
            ar << quint64(_simulationTimeStep * 1000000.0);
            ar.flush();

            ar.storeDataName("_t3");
            ar << _simulationTimeStep;
            ar.flush();

            ar.storeDataName("Spr");
            ar << _simulationPassesPerRendering;
            ar.flush();

            ar.storeDataName("Spi"); // for backward compatibility (05/09/2022)
            ar << int(5);
            ar.flush();

            ar.storeDataName("Ss2");
            unsigned char nothing = 0;
            SIM_SET_CLEAR_BIT(nothing, 0, _realTimeSimulation);
            // 06.09.2022 SIM_SET_CLEAR_BIT(nothing,1,_avoidBlocking);
            SIM_SET_CLEAR_BIT(nothing, 2, _pauseAtSpecificTime);
            SIM_SET_CLEAR_BIT(nothing, 3, _pauseAtError);
            // 06.09.2022 SIM_SET_CLEAR_BIT(nothing,4,_catchUpIfLate);
            SIM_SET_CLEAR_BIT(nothing, 5, _fullscreenAtSimulationStart);
            SIM_SET_CLEAR_BIT(nothing, 6, false);
            SIM_SET_CLEAR_BIT(nothing, 7, !_removeNewObjectsAtSimulationEnd);

            ar << nothing;
            ar.flush();

            ar.storeDataName("Rtc"); // for backward compatibility (03/03/2016), keep before Rt2
            ar << float(_realTimeCoefficient);
            ar.flush();

            ar.storeDataName("Rt2");
            ar << _realTimeCoefficient;
            ar.flush();

            ar.storeDataName("Pat"); // for backward compatibility (03/03/2016), keep before Pa2
            ar << (float)_simulationTimeToPause;
            ar.flush();

            ar.storeDataName("Pa2"); // for backward compatibility (05/09/2022), keep before Pa3
            ar << quint64(_simulationTimeToPause * 1000000.0);
            ar.flush();

            ar.storeDataName("_a3");
            ar << _simulationTimeToPause;
            ar.flush();

            ar.storeDataName(SER_END_OF_OBJECT);
        }
        else
        { // Loading
            int byteQuantity;
            std::string theName = "";
            int oldDefautParamsIndex;
            bool usingOldDefaultParams = true;
            while (theName.compare(SER_END_OF_OBJECT) != 0)
            {
                theName = ar.readDataName();
                if (theName.compare(SER_END_OF_OBJECT) != 0)
                {
                    bool noHit = true;
                    if (theName.compare("Sts") == 0)
                    { // for backward compatibility (03/03/2016)
                        noHit = false;
                        ar >> byteQuantity;
                        float bla;
                        ar >> bla;
                        _simulationTimeStep = (double)bla;
                    }
                    if (theName.compare("St2") == 0)
                    { // for backward compatibility (05/09/2022)
                        noHit = false;
                        ar >> byteQuantity;
                        quint64 stp;
                        ar >> stp;
                        _simulationTimeStep = double(stp) / 1000000.0;
                    }
                    if (theName.compare("St3") == 0)
                    { // for backward comp. (flt->dbl)
                        noHit = false;
                        ar >> byteQuantity;
                        float bla;
                        ar >> bla;
                        _simulationTimeStep = (double)bla;
                        usingOldDefaultParams = false;
                    }

                    if (theName.compare("_t3") == 0)
                    {
                        noHit = false;
                        ar >> byteQuantity;
                        ar >> _simulationTimeStep;
                        usingOldDefaultParams = false;
                    }

                    if (theName.compare("Spr") == 0)
                    {
                        noHit = false;
                        ar >> byteQuantity;
                        ar >> _simulationPassesPerRendering;
                    }
                    if (theName.compare("Spi") == 0)
                    {
                        noHit = false;
                        ar >> byteQuantity;
                        ar >> oldDefautParamsIndex;
                    }
                    if (theName == "Sst")
                    { // for backward compatibility (still in serialization version 15 or before)
                        noHit = false;
                        ar >> byteQuantity;
                        unsigned char nothing;
                        ar >> nothing;
                        _realTimeSimulation = SIM_IS_BIT_SET(nothing, 0);
                        _pauseAtSpecificTime = SIM_IS_BIT_SET(nothing, 2);
                        _pauseAtError = SIM_IS_BIT_SET(nothing, 3);
                        // 06.09.2022 _catchUpIfLate=SIM_IS_BIT_SET(nothing,4);
                        bool defaultSimulationTimeStep = SIM_IS_BIT_SET(nothing, 5);
                        // removed on 26.04.2025 _resetSimulationAtEnd = !SIM_IS_BIT_SET(nothing, 6);
                        _removeNewObjectsAtSimulationEnd = !SIM_IS_BIT_SET(nothing, 7);
                        if (defaultSimulationTimeStep)
                            oldDefautParamsIndex = 2; // for default parameters
                        else
                            oldDefautParamsIndex = 5; // for custom parameters
                    }
                    if (theName == "Ss2")
                    {
                        noHit = false;
                        ar >> byteQuantity;
                        unsigned char nothing;
                        ar >> nothing;
                        _realTimeSimulation = SIM_IS_BIT_SET(nothing, 0);
                        // 06.09.2022 _avoidBlocking=SIM_IS_BIT_SET(nothing,1);
                        _pauseAtSpecificTime = SIM_IS_BIT_SET(nothing, 2);
                        _pauseAtError = SIM_IS_BIT_SET(nothing, 3);
                        // 06.09.2022 _catchUpIfLate=SIM_IS_BIT_SET(nothing,4);
                        _fullscreenAtSimulationStart = SIM_IS_BIT_SET(nothing, 5);
                        // removed on 26.04.2025 _resetSimulationAtEnd = !SIM_IS_BIT_SET(nothing, 6);
                        _removeNewObjectsAtSimulationEnd = !SIM_IS_BIT_SET(nothing, 7);
                    }

                    if (theName.compare("Rt2") == 0)
                    {
                        noHit = false;
                        ar >> byteQuantity;
                        ar >> _realTimeCoefficient;
                    }
                    if (theName.compare("Rtc") == 0)
                    { // for backward compatibility (03/03/2016)
                        noHit = false;
                        ar >> byteQuantity;
                        float v;
                        ar >> v;
                        _realTimeCoefficient = double(v);
                    }
                    if (theName.compare("Pat") == 0)
                    { // for backward compatibility (03/03/2016)
                        noHit = false;
                        ar >> byteQuantity;
                        float bla;
                        ar >> bla;
                        _simulationTimeToPause = (double)bla;
                    }
                    if (theName.compare("Pa2") == 0)
                    { // for backward compatibility (05/09/2022)
                        noHit = false;
                        ar >> byteQuantity;
                        quint64 p;
                        ar >> p;
                        _simulationTimeToPause = double(p) / 1000000.0;
                    }
                    if (theName.compare("Pa3") == 0)
                    { // for backward comp. (flt->dbl)
                        noHit = false;
                        ar >> byteQuantity;
                        float bla;
                        ar >> bla;
                        _simulationTimeToPause = (double)bla;
                    }

                    if (theName.compare("_a3") == 0)
                    {
                        noHit = false;
                        ar >> byteQuantity;
                        ar >> _simulationTimeToPause;
                    }

                    if (noHit)
                        ar.loadUnknownData();
                }
            }
            if (usingOldDefaultParams)
            {
                if ((oldDefautParamsIndex >= 0) && (oldDefautParamsIndex < 5))
                {
                    const double SIMULATION_DEFAULT_TIME_STEP_OLD[5] = {0.2, 0.1, 0.05, 0.025, 0.01};
                    _simulationTimeStep = SIMULATION_DEFAULT_TIME_STEP_OLD[oldDefautParamsIndex];
                }
            }
        }
    }
    else
    {
        bool exhaustiveXml = ((ar.getFileType() != CSer::filetype_csim_xml_simplescene_file) &&
                              (ar.getFileType() != CSer::filetype_csim_xml_simplemodel_file));
        if (ar.isStoring())
        {
            ar.xmlAddNode_float("simTimeStep", _simulationTimeStep);

            ar.xmlAddNode_comment(" 'simulationTimeStep' tag: used for backward compatibility", exhaustiveXml);
            ar.xmlAddNode_float("simulationTimeStep", _simulationTimeStep);
            if (exhaustiveXml)
            {
                ar.xmlAddNode_comment(" 'simulationTimeStep_ns' tag: used for backward compatibility", exhaustiveXml);
                ar.xmlAddNode_ulonglong(
                    "simulationTimeStep_ns",
                    quint64(_simulationTimeStep * 1000000.0)); // for backward compatibility (05.09.2022)
            }

            ar.xmlAddNode_int("simulationPassesPerRendering", _simulationPassesPerRendering);

            ar.xmlAddNode_comment(" 'simulationMode' tag: used for backward compatibility", exhaustiveXml);
            ar.xmlAddNode_int("simulationMode", 5); // for backward compatibility (05.09.2022)

            ar.xmlAddNode_float("realTimeCoefficient", _realTimeCoefficient);

            ar.xmlAddNode_float("simulationTimeToPause", _simulationTimeToPause);
            if (exhaustiveXml)
            {
                ar.xmlAddNode_comment(" 'simulationTimeToPause_ns' tag: used for backward compatibility",
                                      exhaustiveXml);
                ar.xmlAddNode_ulonglong(
                    "simulationTimeToPause_ns",
                    quint64(_simulationTimeToPause * 1000000.0)); // for backward compatibility (05.09.2022)
            }

            ar.xmlPushNewNode("switches");
            ar.xmlAddNode_bool("realTime", _realTimeSimulation);
            ar.xmlAddNode_bool("pauseAtTime", _pauseAtSpecificTime);
            ar.xmlAddNode_bool("pauseAtError", _pauseAtError);
            if (exhaustiveXml)
                ar.xmlAddNode_bool("fullScreen", _fullscreenAtSimulationStart);
            // removed on 26.04.2025 ar.xmlAddNode_bool("resetAtEnd", _resetSimulationAtEnd);
            ar.xmlAddNode_bool("removeNewObjectsAtEnd", _removeNewObjectsAtSimulationEnd);
            ar.xmlPopNode();
        }
        else
        {
            int oldDefautParamsIndex;
            bool usingOldDefaultParams = true;
            if (exhaustiveXml)
            { // for backward compatibility (05.09.2022)
                quint64 step;
                ar.xmlGetNode_ulonglong("simulationTimeStep_ns", step);
                _simulationTimeStep = double(step) / 1000000.0;
            }
            ar.xmlGetNode_float("simulationTimeStep", _simulationTimeStep, exhaustiveXml);
            if (ar.xmlGetNode_float("simTimeStep", _simulationTimeStep, exhaustiveXml))
                usingOldDefaultParams = false;

            if (ar.xmlGetNode_int("simulationPassesPerRendering", _simulationPassesPerRendering, exhaustiveXml))
                tt::limitValue(1, 100, _simulationPassesPerRendering);

            ar.xmlGetNode_enum("simulationMode", oldDefautParamsIndex, exhaustiveXml, "200ms", 0, "100ms", 1, "50ms", 2,
                               "25ms", 3, "10ms", 4, "custom", 5);

            if (ar.xmlGetNode_float("realTimeCoefficient", _realTimeCoefficient, exhaustiveXml))
                tt::limitDoubleValue(0.01, 100.0, _realTimeCoefficient);

            if (exhaustiveXml)
            { // for backward compatibility (05.09.2022)
                quint64 p;
                ar.xmlGetNode_ulonglong("simulationTimeToPause_ns", p);
                _simulationTimeToPause = double(p) / 1000000.0;
            }
            ar.xmlGetNode_float("simulationTimeToPause", _simulationTimeToPause, exhaustiveXml);

            if (ar.xmlPushChildNode("switches", exhaustiveXml))
            {
                ar.xmlGetNode_bool("realTime", _realTimeSimulation, exhaustiveXml);
                ar.xmlGetNode_bool("pauseAtTime", _pauseAtSpecificTime, exhaustiveXml);
                ar.xmlGetNode_bool("pauseAtError", _pauseAtError, exhaustiveXml);
                if (exhaustiveXml)
                    ar.xmlGetNode_bool("fullScreen", _fullscreenAtSimulationStart, exhaustiveXml);
                // removed on 26.04.2025 ar.xmlGetNode_bool("resetAtEnd", _resetSimulationAtEnd, exhaustiveXml);
                ar.xmlGetNode_bool("removeNewObjectsAtEnd", _removeNewObjectsAtSimulationEnd, exhaustiveXml);
                ar.xmlPopNode();
            }
            if (usingOldDefaultParams)
            {
                if ((oldDefautParamsIndex >= 0) && (oldDefautParamsIndex < 5))
                {
                    const double SIMULATION_DEFAULT_TIME_STEP_OLD[5] = {0.2, 0.1, 0.05, 0.025, 0.01};
                    _simulationTimeStep = SIMULATION_DEFAULT_TIME_STEP_OLD[oldDefautParamsIndex];
                }
            }
        }
    }
}

#ifdef SIM_WITH_GUI
bool CSimulation::processCommand(int commandID)
{ // Return value is true if the command belonged to hierarchy menu and was executed
    if (commandID == SIMULATION_COMMANDS_TOGGLE_REAL_TIME_SIMULATION_SCCMD)
    {
        if (!VThread::isUiThread())
        { // we are NOT in the UI thread. We execute the command now:
            bool noEditMode = true;
            noEditMode = (GuiApp::getEditModeType() == NO_EDIT_MODE);
            if (App::currentWorld->simulation->isSimulationStopped() && noEditMode)
            {
                App::currentWorld->simulation->setIsRealTimeSimulation(
                    !App::currentWorld->simulation->getIsRealTimeSimulation());
                if (App::currentWorld->simulation->getIsRealTimeSimulation())
                    App::logMsg(sim_verbosity_msgs, IDSNS_TOGGLED_TO_REAL_TIME_MODE);
                else
                    App::logMsg(sim_verbosity_msgs, IDSNS_TOGGLED_TO_NON_REAL_TIME_MODE);
                GuiApp::setLightDialogRefreshFlag();
                GuiApp::setToolbarRefreshFlag(); // will trigger a refresh
                App::undoRedo_sceneChanged("");
            }
        }
        else
        { // We are in the UI thread. Execute the command via the main thread:
            SSimulationThreadCommand cmd;
            cmd.cmdId = commandID;
            App::appendSimulationThreadCommand(cmd);
        }
        return (true);
    }
    if (commandID == SIMULATION_COMMANDS_SLOWER_SIMULATION_SCCMD)
    {
        _desiredFasterOrSlowerSpeed--;
        return (true);
    }
    if (commandID == SIMULATION_COMMANDS_FASTER_SIMULATION_SCCMD)
    {
        _desiredFasterOrSlowerSpeed++;
        return (true);
    }

    if (commandID == SIMULATION_COMMANDS_TOGGLE_VISUALIZATION_SCCMD)
    {
        if (VThread::isUiThread())
        { // We are in the UI thread. We execute the command now:
            App::setOpenGlDisplayEnabled(!App::getOpenGlDisplayEnabled());
        }
        else
        { // We are not in the UI thread. Execute the command via the UI thread:
            SUIThreadCommand cmdIn;
            SUIThreadCommand cmdOut;
            cmdIn.cmdId = TOGGLE_VISUALIZATION_UITHREADCMD;
            GuiApp::uiThread->executeCommandViaUiThread(&cmdIn, &cmdOut);
        }
        return (true);
    }
    if (commandID == SIMULATION_COMMANDS_TOGGLE_DYNAMIC_CONTENT_VISUALIZATION_SCCMD)
    {
        if (!VThread::isUiThread())
        { // we are NOT in the UI thread. We execute the command now:
            if (!isSimulationStopped())
                setDynamicContentVisualizationOnly(!getDynamicContentVisualizationOnly());
        }
        else
        { // We are in the UI thread. Execute the command via the main thread:
            SSimulationThreadCommand cmd;
            cmd.cmdId = commandID;
            App::appendSimulationThreadCommand(cmd);
        }
    }

    if (commandID == SIMULATION_COMMANDS_START_RESUME_SIMULATION_REQUEST_SCCMD)
    {
        int editMode = NO_EDIT_MODE;
        editMode = GuiApp::getEditModeType();
        if (editMode == NO_EDIT_MODE)
        {
            if (!VThread::isUiThread())
            { // we are NOT in the UI thread. We execute the command now:
                App::worldContainer->simulatorMessageQueue->addCommand(sim_message_simulation_start_resume_request, 0,
                                                                       0, 0, 0, nullptr, 0);
            }
            else
            { // We are in the UI thread. Execute the command via the main thread:
                SSimulationThreadCommand cmd;
                cmd.cmdId = commandID;
                App::appendSimulationThreadCommand(cmd);
            }
        }
        return (true);
    }
    if (commandID == SIMULATION_COMMANDS_PAUSE_SIMULATION_REQUEST_SCCMD)
    {
        if (!VThread::isUiThread())
        { // we are NOT in the UI thread. We execute the command now:
            App::worldContainer->simulatorMessageQueue->addCommand(sim_message_simulation_pause_request, 0, 0, 0, 0,
                                                                   nullptr, 0);
        }
        else
        { // We are in the UI thread. Execute the command via the main thread:
            SSimulationThreadCommand cmd;
            cmd.cmdId = commandID;
            App::appendSimulationThreadCommand(cmd);
        }
        return (true);
    }
    if (commandID == SIMULATION_COMMANDS_STOP_SIMULATION_REQUEST_SCCMD)
    {
        if (!VThread::isUiThread())
        { // we are NOT in the UI thread. We execute the command now:
            App::worldContainer->simulatorMessageQueue->addCommand(sim_message_simulation_stop_request, 0, 0, 0, 0, nullptr, 0);
            incrementStopRequestCounter();
        }
        else
        { // We are in the UI thread. Execute the command via the main thread:
            SSimulationThreadCommand cmd;
            cmd.cmdId = commandID;
            App::appendSimulationThreadCommand(cmd);
        }
        return (true);
    }
    if (commandID == SIMULATION_COMMANDS_TOGGLE_TO_BULLET_2_78_ENGINE_SCCMD)
    {
        if (!VThread::isUiThread())
        { // we are NOT in the UI thread. We execute the command now:
            App::currentWorld->dynamicsContainer->setDynamicEngineType(sim_physics_bullet, 0);
        }
        else
        { // We are in the UI thread. Execute the command via the main thread:
            SSimulationThreadCommand cmd;
            cmd.cmdId = commandID;
            App::appendSimulationThreadCommand(cmd);
        }
        return (true);
    }
    if (commandID == SIMULATION_COMMANDS_TOGGLE_TO_BULLET_2_83_ENGINE_SCCMD)
    {
        if (!VThread::isUiThread())
        { // we are NOT in the UI thread. We execute the command now:
            App::currentWorld->dynamicsContainer->setDynamicEngineType(sim_physics_bullet, 283);
        }
        else
        { // We are in the UI thread. Execute the command via the main thread:
            SSimulationThreadCommand cmd;
            cmd.cmdId = commandID;
            App::appendSimulationThreadCommand(cmd);
        }
        return (true);
    }
    if (commandID == SIMULATION_COMMANDS_TOGGLE_TO_ODE_ENGINE_SCCMD)
    {
        if (!VThread::isUiThread())
        { // we are NOT in the UI thread. We execute the command now:
            App::currentWorld->dynamicsContainer->setDynamicEngineType(sim_physics_ode, 0);
        }
        else
        { // We are in the UI thread. Execute the command via the main thread:
            SSimulationThreadCommand cmd;
            cmd.cmdId = commandID;
            App::appendSimulationThreadCommand(cmd);
        }
        return (true);
    }
    if (commandID == SIMULATION_COMMANDS_TOGGLE_TO_VORTEX_ENGINE_SCCMD)
    {
        if (!VThread::isUiThread())
        { // we are NOT in the UI thread. We execute the command now:
            App::currentWorld->dynamicsContainer->setDynamicEngineType(sim_physics_vortex, 0);
        }
        else
        { // We are in the UI thread. Execute the command via the main thread:
            SSimulationThreadCommand cmd;
            cmd.cmdId = commandID;
            App::appendSimulationThreadCommand(cmd);
        }
        return (true);
    }
    if (commandID == SIMULATION_COMMANDS_TOGGLE_TO_NEWTON_ENGINE_SCCMD)
    {
        if (!VThread::isUiThread())
        { // we are NOT in the UI thread. We execute the command now:
            App::currentWorld->dynamicsContainer->setDynamicEngineType(sim_physics_newton, 0);
        }
        else
        { // We are in the UI thread. Execute the command via the main thread:
            SSimulationThreadCommand cmd;
            cmd.cmdId = commandID;
            App::appendSimulationThreadCommand(cmd);
        }
        return (true);
    }
    if (commandID == SIMULATION_COMMANDS_TOGGLE_TO_MUJOCO_ENGINE_SCCMD)
    {
        if (!VThread::isUiThread())
        { // we are NOT in the UI thread. We execute the command now:
            App::currentWorld->dynamicsContainer->setDynamicEngineType(sim_physics_mujoco, 0);
        }
        else
        { // We are in the UI thread. Execute the command via the main thread:
            SSimulationThreadCommand cmd;
            cmd.cmdId = commandID;
            App::appendSimulationThreadCommand(cmd);
        }
        return (true);
    }
    if (commandID == SIMULATION_COMMANDS_TOGGLE_TO_DRAKE_ENGINE_SCCMD)
    {
        if (!VThread::isUiThread())
        { // we are NOT in the UI thread. We execute the command now:
            App::currentWorld->dynamicsContainer->setDynamicEngineType(sim_physics_drake, 0);
        }
        else
        { // We are in the UI thread. Execute the command via the main thread:
            SSimulationThreadCommand cmd;
            cmd.cmdId = commandID;
            App::appendSimulationThreadCommand(cmd);
        }
        return (true);
    }
    if (commandID == TOGGLE_SIMULATION_DLG_CMD)
    {
        if (VThread::isUiThread())
        {
            if (GuiApp::canShowDialogs())
                GuiApp::mainWindow->dlgCont->toggle(SIMULATION_DLG);
        }
        return (true);
    }
    return (false);
}

bool CSimulation::showAndHandleEmergencyStopButton(bool showState, const char* scriptName)
{
    TRACE_INTERNAL;
    bool retVal = false;
    if (GuiApp::canShowDialogs())
    { // make sure we are not in headless mode
        bool res = GuiApp::uiThread->showOrHideEmergencyStop(showState, scriptName);
        if (showState && res)
            retVal = true; // stop button was pressed
    }
    return (retVal);
}

void CSimulation::addMenu(VMenu* menu)
{
    bool noEditMode = (GuiApp::getEditModeType() == NO_EDIT_MODE);
    bool simRunning = App::currentWorld->simulation->isSimulationRunning();
    bool simStopped = App::currentWorld->simulation->isSimulationStopped();
    bool simPaused = App::currentWorld->simulation->isSimulationPaused();
    bool canGoSlower = App::currentWorld->simulation->canGoSlower();
    bool canGoFaster = App::currentWorld->simulation->canGoFaster();
    if (simPaused)
        menu->appendMenuItem(GuiApp::mainWindow->getPlayViaGuiEnabled() && noEditMode, false,
                             SIMULATION_COMMANDS_START_RESUME_SIMULATION_REQUEST_SCCMD,
                             IDS_RESUME_SIMULATION_MENU_ITEM);
    else
        menu->appendMenuItem(GuiApp::mainWindow->getPlayViaGuiEnabled() && noEditMode && (!simRunning), false,
                             SIMULATION_COMMANDS_START_RESUME_SIMULATION_REQUEST_SCCMD, IDS_START_SIMULATION_MENU_ITEM);
    menu->appendMenuItem(GuiApp::mainWindow->getPauseViaGuiEnabled() && noEditMode && simRunning, false,
                         SIMULATION_COMMANDS_PAUSE_SIMULATION_REQUEST_SCCMD, IDS_PAUSE_SIMULATION_MENU_ITEM);
    menu->appendMenuItem(GuiApp::mainWindow->getStopViaGuiEnabled() && noEditMode && (!simStopped), false,
                         SIMULATION_COMMANDS_STOP_SIMULATION_REQUEST_SCCMD, IDS_STOP_SIMULATION_MENU_ITEM);
    menu->appendMenuSeparator();
    int version;
    int engine = App::currentWorld->dynamicsContainer->getDynamicEngineType(&version);
    menu->appendMenuItem(noEditMode && simStopped, (engine == sim_physics_bullet) && (version == 0),
                         SIMULATION_COMMANDS_TOGGLE_TO_BULLET_2_78_ENGINE_SCCMD,
                         IDS_SWITCH_TO_BULLET_2_78_ENGINE_MENU_ITEM, true);
    menu->appendMenuItem(noEditMode && simStopped, (engine == sim_physics_bullet) && (version == 283),
                         SIMULATION_COMMANDS_TOGGLE_TO_BULLET_2_83_ENGINE_SCCMD,
                         IDS_SWITCH_TO_BULLET_2_83_ENGINE_MENU_ITEM, true);
    menu->appendMenuItem(noEditMode && simStopped, engine == sim_physics_ode,
                         SIMULATION_COMMANDS_TOGGLE_TO_ODE_ENGINE_SCCMD, IDS_SWITCH_TO_ODE_ENGINE_MENU_ITEM, true);
    menu->appendMenuItem(noEditMode && simStopped, engine == sim_physics_vortex,
                         SIMULATION_COMMANDS_TOGGLE_TO_VORTEX_ENGINE_SCCMD, IDS_SWITCH_TO_VORTEX_ENGINE_MENU_ITEM,
                         true);
    menu->appendMenuItem(noEditMode && simStopped, engine == sim_physics_newton,
                         SIMULATION_COMMANDS_TOGGLE_TO_NEWTON_ENGINE_SCCMD, IDS_SWITCH_TO_NEWTON_ENGINE_MENU_ITEM,
                         true);
    menu->appendMenuItem(noEditMode && simStopped, engine == sim_physics_mujoco,
                         SIMULATION_COMMANDS_TOGGLE_TO_MUJOCO_ENGINE_SCCMD, IDS_SWITCH_TO_MUJOCO_ENGINE_MENU_ITEM,
                         true);
#ifdef HAS_DRAKE
    menu->appendMenuItem(noEditMode && simStopped, engine == sim_physics_drake,
                         SIMULATION_COMMANDS_TOGGLE_TO_DRAKE_ENGINE_SCCMD, IDS_SWITCH_TO_DRAKE_ENGINE_MENU_ITEM, true);
#endif
    menu->appendMenuSeparator();
    menu->appendMenuItem(noEditMode && simStopped, App::currentWorld->simulation->getIsRealTimeSimulation(),
                         SIMULATION_COMMANDS_TOGGLE_REAL_TIME_SIMULATION_SCCMD, IDSN_REAL_TIME_SIMULATION, true);
    menu->appendMenuItem(canGoSlower, false, SIMULATION_COMMANDS_SLOWER_SIMULATION_SCCMD, IDSN_SLOW_DOWN_SIMULATION);
    menu->appendMenuItem(canGoFaster, false, SIMULATION_COMMANDS_FASTER_SIMULATION_SCCMD, IDSN_SPEED_UP_SIMULATION);
    if (CSimFlavor::getBoolVal(12))
    {
        menu->appendMenuItem(simRunning && (!(GuiApp::mainWindow->oglSurface->isPageSelectionActive() ||
                                              GuiApp::mainWindow->oglSurface->isViewSelectionActive())),
                             !App::getOpenGlDisplayEnabled(), SIMULATION_COMMANDS_TOGGLE_VISUALIZATION_SCCMD,
                             "Toggle visualization", true);
        menu->appendMenuSeparator();
        if (GuiApp::canShowDialogs())
            menu->appendMenuItem(true, GuiApp::mainWindow->dlgCont->isVisible(SIMULATION_DLG), TOGGLE_SIMULATION_DLG_CMD,
                                 IDSN_SIMULATION_SETTINGS, true);
    }
}

void CSimulation::keyPress(int key)
{
    if (key == CTRL_SPACE_KEY)
    {
        if (isSimulationRunning())
        {
            if (GuiApp::mainWindow->getStopViaGuiEnabled())
                processCommand(SIMULATION_COMMANDS_STOP_SIMULATION_REQUEST_SCCMD);
        }
        else
        {
            if (GuiApp::mainWindow->getPlayViaGuiEnabled())
                processCommand(SIMULATION_COMMANDS_START_RESUME_SIMULATION_REQUEST_SCCMD);
        }
    }
}

#endif

int CSimulation::setBoolProperty(const char* pName, bool pState)
{
    int retVal = -1;

    if (strcmp(pName, propSim_removeNewObjectsAtEnd.name) == 0)
    {
        retVal = 1;
        setRemoveNewObjectsAtSimulationEnd(pState);
    }
    else if (strcmp(pName, propSim_realtimeSimulation.name) == 0)
    {
        retVal = 1;
        setIsRealTimeSimulation(pState);
    }
    else if (strcmp(pName, propSim_pauseSimulationAtTime.name) == 0)
    {
        retVal = 1;
        setPauseAtSpecificTime(pState);
    }
    else if (strcmp(pName, propSim_pauseSimulationAtError.name) == 0)
    {
        retVal = 1;
        setPauseAtError(pState);
    }

    return retVal;
}

int CSimulation::getBoolProperty(const char* pName, bool& pState) const
{
    int retVal = -1;

    if (strcmp(pName, propSim_removeNewObjectsAtEnd.name) == 0)
    {
        pState = _removeNewObjectsAtSimulationEnd;
        retVal = 1;
    }
    else if (strcmp(pName, propSim_realtimeSimulation.name) == 0)
    {
        pState = _realTimeSimulation;
        retVal = 1;
    }
    else if (strcmp(pName, propSim_pauseSimulationAtTime.name) == 0)
    {
        pState = _pauseAtSpecificTime;
        retVal = 1;
    }
    else if (strcmp(pName, propSim_pauseSimulationAtError.name) == 0)
    {
        pState = _pauseAtError;
        retVal = 1;
    }

    return retVal;
}

int CSimulation::setIntProperty(const char* pName, int pState)
{
    int retVal = -1;

    if (strcmp(pName, propSim_stepsPerRendering.name) == 0)
    {
        retVal = 1;
        setPassesPerRendering(pState);
    }
    else if (strcmp(pName, propSim_speedModifier.name) == 0)
    {
        retVal = 1;
        setSpeedModifierCount(pState);
    }

    return retVal;
}

int CSimulation::getIntProperty(const char* pName, int& pState) const
{
    int retVal = -1;

    if (strcmp(pName, propSim_stepCount.name) == 0)
    {
        pState = _simulationStepCount;
        retVal = 1;
    }
    else if (strcmp(pName, propSim_stepsPerRendering.name) == 0)
    {
        pState = _simulationPassesPerRendering;
        retVal = 1;
    }
    else if (strcmp(pName, propSim_simulationState.name) == 0)
    {
        pState = _simulationState;
        retVal = 1;
    }
    else if (strcmp(pName, propSim_speedModifier.name) == 0)
    {
        pState = _speedModifierCount;
        retVal = 1;
    }

    return retVal;
}

int CSimulation::setFloatProperty(const char* pName, double pState)
{
    int retVal = -1;

    if (strcmp(pName, propSim_timeStep.name) == 0)
    {
        setTimeStep(pState);
        retVal = 1;
    }
    else if (strcmp(pName, propSim_timeToPause.name) == 0)
    {
        setPauseTime(pState);
        retVal = 1;
    }
    else if (strcmp(pName, propSim_realtimeModifier.name) == 0)
    {
        setRealTimeCoeff(pState);
        retVal = 1;
    }

    return retVal;
}

int CSimulation::getFloatProperty(const char* pName, double& pState) const
{
    int retVal = -1;

    if (strcmp(pName, propSim_timeStep.name) == 0)
    {
        pState = _simulationTimeStep;
        retVal = 1;
    }
    else if (strcmp(pName, propSim_timeToPause.name) == 0)
    {
        pState = _simulationTimeToPause;
        retVal = 1;
    }
    else if (strcmp(pName, propSim_realtimeModifier.name) == 0)
    {
        pState = _realTimeCoefficient;
        retVal = 1;
    }
    else if (strcmp(pName, propSim_simulationTime.name) == 0)
    {
        pState = _simulationTime;
        retVal = 1;
    }

    return retVal;
}

int CSimulation::getPropertyName(int& index, std::string& pName) const
{
    int retVal = -1;
    for (size_t i = 0; i < allProps_sim.size(); i++)
    {
        if ((pName.size() == 0) || utils::startsWith(allProps_sim[i].name, pName.c_str()))
        {
            if ((allProps_sim[i].flags & sim_propertyinfo_deprecated) == 0)
            {
                index--;
                if (index == -1)
                {
                    pName = allProps_sim[i].name;
                    retVal = 1;
                    break;
                }
            }
        }
    }
    return retVal;
}

int CSimulation::getPropertyInfo(const char* pName, int& info, std::string& infoTxt) const
{
    int retVal = -1;
    for (size_t i = 0; i < allProps_sim.size(); i++)
    {
        if (strcmp(allProps_sim[i].name, pName) == 0)
        {
            retVal = allProps_sim[i].type;
            info = allProps_sim[i].flags;
            if ((infoTxt == "") && (strcmp(allProps_sim[i].infoTxt, "") != 0))
                infoTxt = allProps_sim[i].infoTxt;
            else
                infoTxt = allProps_sim[i].shortInfoTxt;
            break;
        }
    }
    return retVal;
}
