/*
Source code based on the V-REP library source code from Coppelia
Robotics AG on September 2019

Copyright (C) 2006-2023 Coppelia Robotics AG
Copyright (C) 2019 Robot Nordic ApS

All rights reserved.

GNU GPL license:
================
The code in this file is free software: you can redistribute it and/or
modify it under the terms of the GNU General Public License as
published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.

See the GNU General Public License for more details.
<http://www.gnu.org/licenses/>
*/

#include <mirrorRendering.h>
#include <guiApp.h>

void displayMirror(CMirror* mirror, CViewableBase* renderingObject, int displayAttrib)
{
    // At the beginning of every scene object display routine:
    _commonStart(mirror, renderingObject);

    // Object display:
    if (mirror->getShouldObjectBeDisplayed(renderingObject->getObjectHandle(), displayAttrib))
    {
        if ((GuiApp::getEditModeType() & SHAPE_OR_PATH_EDIT_MODE_OLD) == 0)
        {
            if (mirror->getObjectProperty() & sim_objectproperty_selectmodelbaseinstead)
                glLoadName(mirror->getModelSelectionHandle());
            else
                glLoadName(mirror->getObjectHandle());
        }
        else
            glLoadName(-1);

        if ((displayAttrib & sim_displayattribute_forcewireframe) && (displayAttrib & sim_displayattribute_renderpass))
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        _enableAuxClippingPlanes(mirror->getObjectHandle());
        if (((displayAttrib & sim_displayattribute_pickpass) ||
             ((mirror->currentMirrorContentBeingRendered != mirror->getObjectHandle()) &&
              (mirror->currentMirrorContentBeingRendered != -1))) &&
            mirror->getIsMirror())
        {
            ogl::disableLighting_useWithCare(); // only temporarily
            ogl::setMaterialColor(mirror->mirrorColor, ogl::colorBlack, ogl::colorBlack);
            ogl::drawPlane(mirror->getMirrorWidth(), mirror->getMirrorHeight());
            ogl::enableLighting_useWithCare();
        }
        _disableAuxClippingPlanes();
        // For this part we want the clipping planes disabled:
        if (!mirror->getIsMirror())
        {
            mirror->getClipPlaneColor()->makeCurrentColor((displayAttrib & sim_displayattribute_useauxcomponent) != 0);
            ogl::drawPlane(mirror->getMirrorWidth(), mirror->getMirrorHeight());
        }
    }

    // At the end of every scene object display routine:
    _commonFinish(mirror, renderingObject);
}
