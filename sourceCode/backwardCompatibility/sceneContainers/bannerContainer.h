#pragma once

#include <bannerObject.h>
#include <simMath/7Vector.h>
#include <simMath/4X4Matrix.h>

class CViewableBase;

class CBannerContainer
{
  public:
    CBannerContainer();
    virtual ~CBannerContainer();

    void simulationEnded();
    int addObject(CBannerObject* it);
    CBannerObject* getObject(int objectID);
    void eraseAllObjects(bool onlyThoseCreatedFromScripts);
    void announceObjectWillBeErased(int objID);
    void removeObject(int objectID);

  private:
    std::vector<CBannerObject*> _allObjects;

#ifdef SIM_WITH_GUI
  public:
    void renderYour3DStuff_nonTransparent(CViewableBase* renderingObject, int displayAttrib, int windowSize[2],
                                          double verticalViewSizeOrAngle, bool perspective);
    void renderYour3DStuff_transparent(CViewableBase* renderingObject, int displayAttrib, int windowSize[2],
                                       double verticalViewSizeOrAngle, bool perspective);
    void renderYour3DStuff_overlay(CViewableBase* renderingObject, int displayAttrib, int windowSize[2],
                                   double verticalViewSizeOrAngle, bool perspective);
    void drawAll3DStuff(bool overlay, bool transparentObject, int displayAttrib, const C4X4Matrix& cameraCTM,
                        int windowSize[2], double verticalViewSizeOrAngle, bool perspective);
#endif
};
