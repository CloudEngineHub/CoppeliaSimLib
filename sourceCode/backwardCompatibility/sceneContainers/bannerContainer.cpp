#include <simInternal.h>
#include <bannerContainer.h>
#include <viewableBase.h>

CBannerContainer::CBannerContainer()
{
}

CBannerContainer::~CBannerContainer()
{ // beware, the current world could be nullptr
    eraseAllObjects(false);
}

void CBannerContainer::simulationEnded()
{
    eraseAllObjects(true);
    //  if (_initialValuesInitialized)
    //  {
    //  }
}

CBannerObject* CBannerContainer::getObject(int objectID)
{
    for (int i = 0; i < int(_allObjects.size()); i++)
    {
        if (_allObjects[i]->getObjectID() == objectID)
            return (_allObjects[i]);
    }
    return (nullptr);
}

int CBannerContainer::addObject(CBannerObject* it)
{
    int newID = 0;
    newID++;
    while (getObject(newID) != nullptr)
        newID++;
    it->setObjectID(newID);
    _allObjects.push_back(it);
    return (newID);
}

void CBannerContainer::eraseAllObjects(bool onlyThoseCreatedFromScripts)
{
    for (int i = 0; i < int(_allObjects.size()); i++)
    {
        if ((!onlyThoseCreatedFromScripts) || _allObjects[i]->getCreatedFromScript())
        {
            delete _allObjects[i];
            _allObjects.erase(_allObjects.begin() + i);
            i--; // reprocess this position
        }
    }
}

void CBannerContainer::removeObject(int objectID)
{
    for (int i = 0; i < int(_allObjects.size()); i++)
    {
        if (_allObjects[i]->getObjectID() == objectID)
        {
            delete _allObjects[i];
            _allObjects.erase(_allObjects.begin() + i);
            break;
        }
    }
}

void CBannerContainer::announceObjectWillBeErased(int objID)
{ // Never called from copy buffer!
    int i = 0;
    while (i < int(_allObjects.size()))
    {
        if (_allObjects[i]->announceObjectWillBeErased(objID))
        {
            delete _allObjects[i];
            _allObjects.erase(_allObjects.begin() + i);
        }
        else
            i++;
    }
}

#ifdef SIM_WITH_GUI
void CBannerContainer::renderYour3DStuff_nonTransparent(CViewableBase* renderingObject, int displayAttrib,
                                                        int windowSize[2], double verticalViewSizeOrAngle,
                                                        bool perspective)
{
    drawAll3DStuff(false, false, displayAttrib, renderingObject->getFullCumulativeTransformation().getMatrix(),
                   windowSize, verticalViewSizeOrAngle, perspective);
}

void CBannerContainer::renderYour3DStuff_transparent(CViewableBase* renderingObject, int displayAttrib,
                                                     int windowSize[2], double verticalViewSizeOrAngle,
                                                     bool perspective)
{
    drawAll3DStuff(false, true, displayAttrib, renderingObject->getFullCumulativeTransformation().getMatrix(),
                   windowSize, verticalViewSizeOrAngle, perspective);
}

void CBannerContainer::renderYour3DStuff_overlay(CViewableBase* renderingObject, int displayAttrib, int windowSize[2],
                                                 double verticalViewSizeOrAngle, bool perspective)
{
    drawAll3DStuff(true, true, displayAttrib, renderingObject->getFullCumulativeTransformation().getMatrix(),
                   windowSize, verticalViewSizeOrAngle, perspective);
}

void CBannerContainer::drawAll3DStuff(bool overlay, bool transparentObject, int displayAttrib,
                                      const C4X4Matrix& cameraCTM, int windowSize[2], double verticalViewSizeOrAngle,
                                      bool perspective)
{
    for (size_t i = 0; i < _allObjects.size(); i++)
        _allObjects[i]->draw3DStuff(overlay, transparentObject, displayAttrib, cameraCTM, windowSize,
                                    verticalViewSizeOrAngle, perspective);
}
#endif
