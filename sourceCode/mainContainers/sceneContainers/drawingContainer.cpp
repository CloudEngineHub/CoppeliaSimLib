#include <simInternal.h>
#include <drawingContainer.h>
#include <viewableBase.h>
#include <app.h>

CDrawingContainer::CDrawingContainer()
{
}

CDrawingContainer::~CDrawingContainer()
{
    for (size_t i = 0; i < _allObjects.size(); i++)
    {
        delete _allObjects[i];
        _allObjects.erase(_allObjects.begin() + i);
    }
}

void CDrawingContainer::simulationEnded()
{
}

CDrawingObject* CDrawingContainer::getObject(int objectId)
{
    for (size_t i = 0; i < _allObjects.size(); i++)
    {
        if (_allObjects[i]->getObjectId() == objectId)
            return (_allObjects[i]);
    }
    return (nullptr);
}

int CDrawingContainer::addObject(CDrawingObject* it)
{
    int newId = 0;
    newId++;
    while (getObject(newId) != nullptr)
        newId++;
    it->setObjectId(newId);
    it->setObjectUniqueId();
    _allObjects.push_back(it);
    it->pushAddEvent();
    return (newId);
}

void CDrawingContainer::removeObject(int objectId)
{
    for (size_t i = 0; i < _allObjects.size(); i++)
    {
        if (_allObjects[i]->getObjectId() == objectId)
        {
            if (App::worldContainer->getEventsEnabled())
            {
                App::worldContainer->createEvent(EVENTTYPE_DRAWINGOBJECTREMOVED, -1, _allObjects[i]->getObjectUid(), nullptr, false);
                App::worldContainer->pushEvent();
            }

            delete _allObjects[i];
            _allObjects.erase(_allObjects.begin() + i);

            break;
        }
    }
}

void CDrawingContainer::eraseAllObjects()
{
    while (_allObjects.size() > 0)
        removeObject(_allObjects[0]->getObjectId());
}

void CDrawingContainer::announceObjectWillBeErased(const CSceneObject* object)
{ // Never called from copy buffer!
    size_t i = 0;
    while (i < _allObjects.size())
    {
        if (_allObjects[i]->announceObjectWillBeErased(object))
            removeObject(_allObjects[i]->getObjectId());
        else
            i++;
    }
}

void CDrawingContainer::announceScriptStateWillBeErased(int scriptHandle, bool simulationScript,
                                                        bool sceneSwitchPersistentScript)
{
    size_t i = 0;
    while (i < _allObjects.size())
    {
        if (_allObjects[i]->announceScriptStateWillBeErased(scriptHandle, simulationScript,
                                                            sceneSwitchPersistentScript))
            removeObject(_allObjects[i]->getObjectId());
        else
            i++;
    }
}

void CDrawingContainer::pushGenesisEvents()
{
    for (size_t i = 0; i < _allObjects.size(); i++)
        _allObjects[i]->pushAddEvent();
}

void CDrawingContainer::pushAppendNewPointEvents()
{
    for (size_t i = 0; i < _allObjects.size(); i++)
        _allObjects[i]->pushAppendNewPointEvent();
}

#ifdef SIM_WITH_GUI
void CDrawingContainer::renderYour3DStuff_nonTransparent(CViewableBase* renderingObject, int displayAttrib)
{
    drawAll(false, false, displayAttrib, renderingObject->getFullCumulativeTransformation().getMatrix());
}

void CDrawingContainer::renderYour3DStuff_transparent(CViewableBase* renderingObject, int displayAttrib)
{
    drawAll(false, true, displayAttrib, renderingObject->getFullCumulativeTransformation().getMatrix());
}

void CDrawingContainer::renderYour3DStuff_overlay(CViewableBase* renderingObject, int displayAttrib)
{
    drawAll(true, true, displayAttrib, renderingObject->getFullCumulativeTransformation().getMatrix());
}

void CDrawingContainer::drawAll(bool overlay, bool transparentObject, int displayAttrib, const C4X4Matrix& cameraCTM)
{
    for (size_t i = 0; i < _allObjects.size(); i++)
        _allObjects[i]->draw(overlay, transparentObject, displayAttrib, cameraCTM);
}

void CDrawingContainer::drawObjectsParentedWith(bool overlay, bool transparentObject, int parentObjectId,
                                                int displayAttrib, const C4X4Matrix& cameraCTM)
{
    if ((displayAttrib & sim_displayattribute_nodrawingobjects) == 0)
    {
        for (size_t i = 0; i < _allObjects.size(); i++)
        {
            if ((_allObjects[i]->getSceneObjectId() == parentObjectId) &&
                ((_allObjects[i]->getObjectType() & sim_drawing_painttag) != 0))
                _allObjects[i]->draw(overlay, transparentObject, displayAttrib, cameraCTM);
        }
    }
}
#endif
