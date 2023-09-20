#pragma once

#include <QEventLoop>
#include <simMath/3Vector.h>
#include <simMath/4Vector.h>
#include <simMath/7Vector.h>
#include <vMutex.h>
#include <vThread.h>

struct SSimulationThreadCommand
{
    int cmdId;
    int sceneUniqueId;
    int postTime;
    int execDelay;
    std::vector<bool> boolParams;
    std::vector<int> intParams;
    std::vector<quint64> uint64Params;
    std::vector<unsigned char> uint8Params;
    std::vector<double> doubleParams;
    std::vector<void*> objectParams;
    std::vector<std::string> stringParams;
    std::vector<C3Vector> posParams;
    std::vector<C4Vector> quatParams;
    std::vector<C7Vector> transfParams;
    std::vector<std::vector<int> > intVectorParams;
    std::vector<std::vector<float> > floatVectorParams;
    std::vector<std::vector<double> > doubleVectorParams;
};

class CSimThread : public QObject
{
    Q_OBJECT

public:
    CSimThread();
    virtual ~CSimThread();
    void handleExtCalls();
    void executeMessages();
    void setRenderingAllowed(bool a);
    void appendSimulationThreadCommand(SSimulationThreadCommand cmd,int executionDelay=0);

private:
    QEventLoop _eventLoop;
    bool _renderingAllowed;
    void _handleSimulationThreadCommands();
    void _executeSimulationThreadCommand(SSimulationThreadCommand cmd);

    VMutex _simulationThreadCommandsMutex;
    std::vector<SSimulationThreadCommand> _simulationThreadCommands_tmp;
    std::vector<SSimulationThreadCommand> _simulationThreadCommands;
    void _handleClickRayIntersection_old(SSimulationThreadCommand cmd);
    void _handleAutoSaveSceneCommand(SSimulationThreadCommand cmd);
    bool _renderRequired();
};
