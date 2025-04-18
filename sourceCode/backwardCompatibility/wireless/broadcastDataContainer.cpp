#include <simInternal.h>
#include <broadcastDataContainer.h>
#include <app.h>
#include <vDateTime.h>

bool CBroadcastDataContainer::_wirelessForceShow_emission = false;
bool CBroadcastDataContainer::_wirelessForceShow_reception = false;

bool CBroadcastDataContainer::getWirelessForceShow_emission()
{
    return (_wirelessForceShow_emission);
}

void CBroadcastDataContainer::setWirelessForceShow_emission(bool f)
{
    _wirelessForceShow_emission = f;
}

bool CBroadcastDataContainer::getWirelessForceShow_reception()
{
    return (_wirelessForceShow_reception);
}

void CBroadcastDataContainer::setWirelessForceShow_reception(bool f)
{
    _wirelessForceShow_reception = f;
}

CBroadcastDataContainer::CBroadcastDataContainer()
{
}

CBroadcastDataContainer::~CBroadcastDataContainer()
{
    eraseAllObjects();
}

void CBroadcastDataContainer::simulationAboutToStart()
{
}

void CBroadcastDataContainer::simulationEnded()
{
    eraseAllObjects();
}

void CBroadcastDataContainer::broadcastData(int emitterID, int targetID, int dataHeader, std::string& dataName,
                                            double timeOutSimulationTime, double actionRadius, int antennaHandle,
                                            double emissionAngle1, double emissionAngle2, const char* data,
                                            int dataLength)
{ // Called by the SIM or UI thread
    CBroadcastData* it =
        new CBroadcastData(emitterID, targetID, dataHeader, dataName, timeOutSimulationTime, actionRadius,
                           antennaHandle, emissionAngle1, emissionAngle2, data, dataLength);
    _allObjects.push_back(it);
    if (App::currentWorld->environment->getVisualizeWirelessEmitters() || _wirelessForceShow_emission)
    {
        bool err = false;
        C7Vector antennaConf;
        antennaConf.setIdentity();
        if (antennaHandle != sim_handle_default)
        {
            CSceneObject* it = App::currentWorld->sceneObjects->getObjectFromHandle(antennaHandle);
            if (it != nullptr)
                antennaConf = it->getCumulativeTransformation();
            else
                err = true;
        }
#ifdef SIM_WITH_GUI
        if (!err)
        {
            CBroadcastDataVisual* itv = new CBroadcastDataVisual(timeOutSimulationTime, actionRadius, antennaConf,
                                                                 emissionAngle1, emissionAngle2);
            _allVisualObjects.push_back(itv);
        }
#endif
    }
}

char* CBroadcastDataContainer::receiveData(int receiverID, double simulationTime, int dataHeader, std::string& dataName,
                                           int antennaHandle, int& dataLength, int index, int& senderID,
                                           int& dataHeaderR, std::string& dataNameR)
{
    int originalIndex = index;
    char* retVal = nullptr;
    for (size_t i = 0; i < _allObjects.size(); i++)
    {
        retVal = _allObjects[i]->receiveData(receiverID, simulationTime, dataHeader, dataName, antennaHandle,
                                             dataLength, senderID, dataHeaderR, dataNameR, originalIndex == -1);
        if (retVal != nullptr)
        {
            if (originalIndex == -1)
            {
                if (App::currentWorld->environment->getVisualizeWirelessReceivers() || _wirelessForceShow_reception)
                {
                    bool err = false;
                    C3Vector antennaPos1;
                    antennaPos1.clear();
                    if (_allObjects[i]->getAntennaHandle() != sim_handle_default)
                    {
                        CSceneObject* it =
                            App::currentWorld->sceneObjects->getObjectFromHandle(_allObjects[i]->getAntennaHandle());
                        if (it != nullptr)
                            antennaPos1 = it->getCumulativeTransformation().X;
                        else
                            err = true;
                    }
                    C3Vector antennaPos2;
                    antennaPos2.clear();
                    if (antennaHandle != sim_handle_default)
                    {
                        CSceneObject* it = App::currentWorld->sceneObjects->getObjectFromHandle(antennaHandle);
                        if (it != nullptr)
                            antennaPos2 = it->getCumulativeTransformation().X;
                        else
                            err = true;
                    }
#ifdef SIM_WITH_GUI
                    if (!err)
                    {
                        CBroadcastDataVisual* itv = new CBroadcastDataVisual(antennaPos1, antennaPos2);
                        _allVisualObjects.push_back(itv);
                    }
#endif
                }
                return (retVal);
            }
            index--;
            if (index == -1)
                return (retVal);
            retVal = nullptr;
        }
    }
    return (retVal);
}

void CBroadcastDataContainer::eraseAllObjects()
{
    for (size_t i = 0; i < _allObjects.size(); i++)
        delete _allObjects[i];
    _allObjects.clear();
#ifdef SIM_WITH_GUI
    for (size_t i = 0; i < _allVisualObjects.size(); i++)
        delete _allVisualObjects[i];
    _allVisualObjects.clear();
#endif
}

void CBroadcastDataContainer::removeObject(int index)
{
    delete _allObjects[index];
    _allObjects.erase(_allObjects.begin() + index);
}

void CBroadcastDataContainer::removeTimedOutObjects(double simulationTime)
{
    for (int i = 0; i < int(_allObjects.size()); i++)
    {
        if (_allObjects[i]->doesRequireDestruction(simulationTime))
        {
            removeObject(i);
            i--;
        }
    }

#ifdef SIM_WITH_GUI
    for (int i = 0; i < int(_allVisualObjects.size()); i++)
    {
        if (_allVisualObjects[i]->doesRequireDestruction(simulationTime))
        {
            delete _allVisualObjects[i];
            _allVisualObjects.erase(_allVisualObjects.begin() + i);
            i--;
        }
    }
#endif
}

#ifdef SIM_WITH_GUI
void CBroadcastDataContainer::visualizeCommunications(int pcTimeInMs)
{
    for (size_t i = 0; i < _allVisualObjects.size(); i++)
        _allVisualObjects[i]->visualize();
}
#endif
