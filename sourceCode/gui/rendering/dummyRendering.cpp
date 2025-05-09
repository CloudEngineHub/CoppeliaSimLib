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

#include <dummyRendering.h>
#include <guiApp.h>

void displayDummy(CDummy* dummy, CViewableBase* renderingObject, int displayAttrib)
{
    // At the beginning of every scene object display routine:
    _commonStart(dummy, renderingObject);

    C3Vector normalVectorForLinesAndPoints(dummy->getFullCumulativeTransformation().Q.getInverse() *
                                           C3Vector::unitZVector);

    // Object display:
    if (dummy->getShouldObjectBeDisplayed(renderingObject->getObjectHandle(), displayAttrib))
    {
        if ((GuiApp::getEditModeType() & SHAPE_OR_PATH_EDIT_MODE_OLD) == 0)
        {
            if (dummy->getObjectProperty() & sim_objectproperty_selectmodelbaseinstead)
                glLoadName(dummy->getModelSelectionHandle());
            else
                glLoadName(dummy->getObjectHandle());
        }
        else
            glLoadName(-1);

        if ((displayAttrib & sim_displayattribute_forcewireframe) && (displayAttrib & sim_displayattribute_renderpass))
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        if ((displayAttrib & sim_displayattribute_forcewireframe) == 0)
            glEnable(GL_CULL_FACE);

        _enableAuxClippingPlanes(dummy->getObjectHandle());
        ogl::drawReference(dummy->getDummySize());
        if (displayAttrib & sim_displayattribute_dynamiccontentonly)
            ogl::setMaterialColor(0.0f, 0.6f, 0.6f, 0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f);
        else
            dummy->getDummyColor()->makeCurrentColor((displayAttrib & sim_displayattribute_useauxcomponent) != 0);
        CDummy* linkedDummy = nullptr;
        if (dummy->getLinkedDummyHandle() != -1)
            linkedDummy = App::currentWorld->sceneObjects->getDummyFromHandle(dummy->getLinkedDummyHandle());
        ogl::drawSphere(dummy->getDummySize() / 2.0, 12, 6, false);
        glDisable(GL_CULL_FACE);
        if (linkedDummy != nullptr)
        {
            C7Vector cumulBase(dummy->getFullCumulativeTransformation());
            C7Vector cumulMobile(linkedDummy->getFullCumulativeTransformation());
            cumulMobile = cumulBase.getInverse() * cumulMobile;
            ogl::setMaterialColor(ogl::colorBlack, ogl::colorBlack, ogl::colorBlack);
            int _linkType = dummy->getDummyType();
            if ((_linkType == sim_dummy_linktype_gcs_loop_closure) || (_linkType == sim_dummy_linktype_gcs_tip) ||
                (_linkType == sim_dummy_linktype_gcs_target))
                ogl::setMaterialColor(sim_colorcomponent_ambient_diffuse, ogl::colorGreen);
            if (_linkType == sim_dummy_linktype_ik_tip_target)
                ogl::setMaterialColor(sim_colorcomponent_ambient_diffuse, ogl::colorRed);
            if ((_linkType == sim_dummytype_dynloopclosure) ||
                (_linkType == sim_dummy_linktype_dynamics_force_constraint) || (_linkType == sim_dummytype_dyntendon))
                ogl::setMaterialColor(sim_colorcomponent_ambient_diffuse, ogl::colorBlue);
            ogl::buffer.clear();
            ogl::addBuffer3DPoints(0.0, 0.0, 0.0);
            ogl::addBuffer3DPoints(cumulMobile.X.data);
            ogl::drawRandom3dLines(&ogl::buffer[0], 2, false, normalVectorForLinesAndPoints.data);
            ogl::buffer.clear();
        }
        _disableAuxClippingPlanes();
    }

    // At the end of every scene object display routine:
    _commonFinish(dummy, renderingObject);
}
