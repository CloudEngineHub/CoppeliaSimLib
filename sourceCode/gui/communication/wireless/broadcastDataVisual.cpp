#include <simInternal.h>
#include <broadcastDataVisual.h>
#include <app.h>
#include <vDateTime.h>
#include <broadcastDataVisualRendering.h>

CBroadcastDataVisual::CBroadcastDataVisual(double timeOutSimulationTime, double actionRadius,
                                           const C7Vector& emitterConf, double emissionAngle1, double emissionAngle2)
{ // displayed if not timed out
    _timeOutSimulationTime = timeOutSimulationTime;
    _actionRadius = actionRadius;
    _emitterConf = emitterConf;
    _emissionAngle1 = emissionAngle1;
    _emissionAngle2 = emissionAngle2;
    _emitter = true;
}

CBroadcastDataVisual::CBroadcastDataVisual(const C3Vector& emitterPos, const C3Vector& receiverPos)
{ // receiving. Displayed exactly once
    _timeOutSimulationTime = 0.0;
    _emitterConf.X = emitterPos;
    _receiverPos = receiverPos;
    _emitter = false;
}

bool CBroadcastDataVisual::doesRequireDestruction(double simulationTime)
{
    if (_emitter)
        return (simulationTime > _timeOutSimulationTime);
    return (_timeOutSimulationTime != 0.0);
}

bool CBroadcastDataVisual::isReceiver()
{
    return (!_emitter);
}

CBroadcastDataVisual::~CBroadcastDataVisual()
{
}

void CBroadcastDataVisual::visualize()
{
    displayEmitterOrReceiver(this);
    if (!_emitter)
        _timeOutSimulationTime = 1.0; // indicates that this object will be destroyed
}
