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

#include <jointRendering.h>
#include <guiApp.h>

void displayJoint(CJoint* joint, CViewableBase* renderingObject, int displayAttrib)
{
    // At the beginning of every scene object display routine:
    _commonStart(joint, renderingObject);

    bool guiIsRendering = ((displayAttrib & sim_displayattribute_forvisionsensor) == 0);

    double sizeParam = joint->getLength() / 4.0;
    if (sizeParam < joint->getDiameter())
        sizeParam = joint->getDiameter();
    if (sizeParam > 10.0 * joint->getDiameter())
        sizeParam = 10.0 * joint->getDiameter();

    // Object display:
    if (joint->getShouldObjectBeDisplayed(renderingObject->getObjectHandle(), displayAttrib))
    {
        _enableAuxClippingPlanes(joint->getObjectHandle());
        if (displayAttrib & sim_displayattribute_dynamiccontentonly)
        {
            if (joint->getDynamicFlag() == 4)
            {
                if (joint->getDynCtrlMode() == sim_jointdynctrl_free)
                    ogl::setMaterialColor(0.0f, 0.3f, 1.0f, 0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f);
                else
                    ogl::setMaterialColor(1.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f);
            }
        }
        else
            joint->getColor(false)->makeCurrentColor((displayAttrib & sim_displayattribute_useauxcomponent) != 0);

        _displayJoint(joint, displayAttrib, true, sizeParam);

        if (displayAttrib & sim_displayattribute_dynamiccontentonly)
            ogl::setMaterialColor(0.1f, 0.1f, 0.1f, 0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f);
        else
            joint->getColor(true)->makeCurrentColor((displayAttrib & sim_displayattribute_useauxcomponent) != 0);
        _displayJoint(joint, displayAttrib, false, sizeParam);
        _disableAuxClippingPlanes();
    }

    // At the end of every scene object display routine:
    _commonFinish(joint, renderingObject);
}

void _displayJoint(CJoint* joint, int displayAttrib, bool partOne, double sizeParam)
{
    if ((GuiApp::getEditModeType() & SHAPE_OR_PATH_EDIT_MODE_OLD) == 0)
    {
        if (joint->getObjectProperty() & sim_objectproperty_selectmodelbaseinstead)
            glLoadName(joint->getModelSelectionHandle());
        else
            glLoadName(joint->getObjectHandle());
    }
    else
        glLoadName(-1);

    glPushAttrib(GL_POLYGON_BIT);
    if ((displayAttrib & sim_displayattribute_forcewireframe) && (displayAttrib & sim_displayattribute_renderpass))
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glPushMatrix();
    if (joint->getJointType() == sim_joint_spherical)
    {
        if (partOne)
        {
            glEnable(GL_CULL_FACE);
            glCullFace(GL_FRONT);
            ogl::drawSphere(joint->getDiameter(), 16, 8, true);
            glDisable(GL_CULL_FACE);
        }
        else
        {
            C7Vector tr(joint->getIntrinsicTransformation(true));
            glTranslated(tr.X(0), tr.X(1), tr.X(2));
            C4Vector axis = tr.Q.getAngleAndAxis();
            glRotated(axis(0) * radToDeg, axis(1), axis(2), axis(3));

            ogl::drawSphere(joint->getDiameter() / 1.5, 16, 8, true);
        }
    }
    if (joint->getJointType() == sim_joint_revolute)
    {
        if (partOne)
            ogl::drawCylinder(joint->getDiameter(), joint->getLength(), 8, 0, true);
        else
        {
            C7Vector tr(joint->getIntrinsicTransformation(true));
            glTranslated(tr.X(0), tr.X(1), tr.X(2));
            C4Vector axis = tr.Q.getAngleAndAxis();
            glRotated(axis(0) * radToDeg, axis(1), axis(2), axis(3));

            ogl::drawCylinder(joint->getDiameter() / 2.0, joint->getLength() * 1.2, 8, 0, true);
        }
    }
    if (joint->getJointType() == sim_joint_prismatic)
    {
        if (partOne)
            ogl::drawBox(joint->getDiameter(), joint->getDiameter(), joint->getLength(), true, nullptr);
        else
        {
            C7Vector tr(joint->getIntrinsicTransformation(true));
            glTranslated(tr.X(0), tr.X(1), tr.X(2));
            C4Vector axis = tr.Q.getAngleAndAxis();
            glRotated(axis(0) * radToDeg, axis(1), axis(2), axis(3));

            ogl::drawBox(joint->getDiameter() / 2.0, joint->getDiameter() / 2.0, joint->getLength() * 1.2, true,
                         nullptr);
        }
    }
    glPopAttrib();
    glPopMatrix();
}
