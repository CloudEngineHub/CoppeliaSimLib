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

#include <graphRendering.h>
#include <graphingRoutines_old.h>
#include <guiApp.h>

void displayGraph(CGraph* graph, CViewableBase* renderingObject, int displayAttrib)
{ // This is a quite ugly routine which requires refactoring!
    // At the beginning of every scene object display routine:
    _commonStart(graph, renderingObject);

    // Bounding box display:
    double size = graph->getGraphSize();

    C3Vector normalVectorForLinesAndPoints(graph->getFullCumulativeTransformation().Q.getInverse() *
                                           C3Vector::unitZVector);

    // Object display:
    if (graph->getShouldObjectBeDisplayed(renderingObject->getObjectHandle(), displayAttrib))
    {
        if ((GuiApp::getEditModeType() & SHAPE_OR_PATH_EDIT_MODE_OLD) == 0)
        {
            if (graph->getObjectProperty() & sim_objectproperty_selectmodelbaseinstead)
                glLoadName(graph->getModelSelectionHandle());
            else
                glLoadName(graph->getObjectHandle());
        }
        else
            glLoadName(-1);

        if ((displayAttrib & sim_displayattribute_forcewireframe) && (displayAttrib & sim_displayattribute_renderpass))
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        _enableAuxClippingPlanes(graph->getObjectHandle());
        graph->getColor()->makeCurrentColor((displayAttrib & sim_displayattribute_useauxcomponent) != 0);
        if (graph->xYZPlanesDisplay && (!graph->getJustDrawCurves()) &&
            ((displayAttrib & sim_displayattribute_forvisionsensor) == 0))
        {
            int subdiv = 5;
            double step = size / (double)subdiv;
            ogl::buffer.clear();
            for (int i = 0; i < subdiv + 1; i++)
            {
                ogl::addBuffer3DPoints(-size / 2.0 + i * step, -size / 2.0, 0.0);
                ogl::addBuffer3DPoints(-size / 2.0 + i * step, +size / 2.0, 0.0);
                ogl::addBuffer3DPoints(-size / 2.0, -size / 2.0 + i * step, 0.0);
                ogl::addBuffer3DPoints(+size / 2.0, -size / 2.0 + i * step, 0.0);

                ogl::addBuffer3DPoints(0.0, -size / 2.0 + i * step, -size / 2.0);
                ogl::addBuffer3DPoints(0.0, -size / 2.0 + i * step, +size / 2.0);
                ogl::addBuffer3DPoints(0.0, -size / 2.0, -size / 2.0 + i * step);
                ogl::addBuffer3DPoints(0.0, +size / 2.0, -size / 2.0 + i * step);

                ogl::addBuffer3DPoints(-size / 2.0 + i * step, 0.0, -size / 2.0);
                ogl::addBuffer3DPoints(-size / 2.0 + i * step, 0.0, +size / 2.0);
                ogl::addBuffer3DPoints(-size / 2.0, 0.0, -size / 2.0 + i * step);
                ogl::addBuffer3DPoints(+size / 2.0, 0.0, -size / 2.0 + i * step);
            }
            ogl::drawRandom3dLines(&ogl::buffer[0], (int)ogl::buffer.size() / 3, false,
                                   normalVectorForLinesAndPoints.data);
            ogl::buffer.clear();
        }
        if ((!graph->getJustDrawCurves()) && ((displayAttrib & sim_displayattribute_forvisionsensor) == 0))
            ogl::drawSphere(size / 32.0, 10, 5, true);

        if ((!graph->getJustDrawCurves()) && ((displayAttrib & (sim_displayattribute_forvisionsensor)) == 0))
            ogl::drawReference(size / 2.0);

        // Display the trajectories..
        ogl::setMaterialColor(ogl::colorBlack, ogl::colorBlack, ogl::colorBlack);
        C7Vector thisInv(graph->getFullCumulativeTransformation().getInverse());

        for (int i = 0; i < int(graph->curves3d_old.size()); i++)
        {
            if (graph->curves3d_old[i]->getVisible())
            {
                if ((graph->getJustDrawCurves() && graph->curves3d_old[i]->getVisibleOnTopOfEverything()) ||
                    ((!graph->getJustDrawCurves()) && (!graph->curves3d_old[i]->getVisibleOnTopOfEverything())))
                {
                    CGraphData_old* part0 = graph->getGraphData(graph->curves3d_old[i]->data[0]);
                    CGraphData_old* part1 = graph->getGraphData(graph->curves3d_old[i]->data[1]);
                    CGraphData_old* part2 = graph->getGraphData(graph->curves3d_old[i]->data[2]);
                    int pos = 0;
                    int absIndex;
                    double point[3];
                    glLineWidth((float)graph->curves3d_old[i]->get3DCurveWidth());
                    glPointSize((float)graph->curves3d_old[i]->get3DCurveWidth());
                    if (graph->curves3d_old[i]->getVisibleOnTopOfEverything())
                    {
                        glDepthMask(GL_FALSE);
                        glDisable(GL_DEPTH_TEST);
                    }
                    bool cyclic0, cyclic1, cyclic2;
                    double range0, range1, range2;
                    if (part0 != nullptr)
                        CGraphingRoutines_old::getCyclicAndRangeValues(part0, cyclic0, range0);
                    if (part1 != nullptr)
                        CGraphingRoutines_old::getCyclicAndRangeValues(part1, cyclic1, range1);
                    if (part2 != nullptr)
                        CGraphingRoutines_old::getCyclicAndRangeValues(part2, cyclic2, range2);

                    ogl::buffer.clear();
                    while (graph->getAbsIndexOfPosition(pos++, absIndex))
                    {
                        bool dataIsValid = true;
                        if (part0 != nullptr)
                        {
                            if (!graph->getData(part0, absIndex, point[0], cyclic0, range0, false))
                                dataIsValid = false;
                        }
                        else
                            dataIsValid = false;
                        if (part1 != nullptr)
                        {
                            if (!graph->getData(part1, absIndex, point[1], cyclic1, range1, false))
                                dataIsValid = false;
                        }
                        else
                            dataIsValid = false;
                        if (part2 != nullptr)
                        {
                            if (!graph->getData(part2, absIndex, point[2], cyclic2, range2, false))
                                dataIsValid = false;
                        }
                        else
                            dataIsValid = false;

                        if (dataIsValid)
                        {
                            C3Vector pp(point);
                            if (graph->curves3d_old[i]->getCurveRelativeToWorld())
                                pp = thisInv * pp;
                            ogl::addBuffer3DPoints(pp.data);
                        }
                    }
                    if (ogl::buffer.size() > 0)
                    {
                        ogl::setMaterialColor(graph->curves3d_old[i]->curveColor.getColorsPtr(), ogl::colorBlack,
                                              graph->curves3d_old[i]->curveColor.getColorsPtr() + 9);
                        if (graph->curves3d_old[i]->getLinkPoints())
                            ogl::drawRandom3dLines(&ogl::buffer[0], (int)ogl::buffer.size() / 3, true,
                                                   normalVectorForLinesAndPoints.data);
                        else
                            ogl::drawRandom3dPoints(&ogl::buffer[0], (int)ogl::buffer.size() / 3,
                                                    normalVectorForLinesAndPoints.data);
                        if (graph->curves3d_old[i]->getLabel() && (displayAttrib & sim_displayattribute_renderpass) &&
                            ((displayAttrib & sim_displayattribute_forvisionsensor) == 0))
                            ogl::drawBitmapTextTo3dPosition(&ogl::buffer[0], graph->curves3d_old[i]->getName().c_str(),
                                                            normalVectorForLinesAndPoints.data);
                    }
                    ogl::buffer.clear();
                    glDepthMask(GL_TRUE);
                    glEnable(GL_DEPTH_TEST);
                    glLineWidth(1.0);
                    glPointSize(1.0);
                }
            }
        }

        // Static curves now:
        if ((displayAttrib & sim_displayattribute_forvisionsensor) == 0)
        {
            for (int i = 0; i < int(graph->staticStreamsAndCurves_old.size()); i++)
            {
                if (graph->staticStreamsAndCurves_old[i]->getCurveType() == 2)
                {
                    CStaticGraphCurve_old* it = graph->staticStreamsAndCurves_old[i];
                    glLineWidth((float)it->getCurveWidth());
                    glPointSize((float)it->getCurveWidth());
                    glLineStipple(1, 0xE187);
                    glEnable(GL_LINE_STIPPLE);
                    ogl::buffer.clear();

                    for (int j = 0; j < int(it->values.size() / 3); j++)
                    {
                        C3Vector pp(&it->values[3 * j + 0]);
                        if (it->getRelativeToWorld())
                            pp = thisInv * pp;
                        ogl::addBuffer3DPoints(pp.data);
                    }

                    if (ogl::buffer.size() > 0)
                    {
                        ogl::setMaterialColor(it->ambientColor, ogl::colorBlack, it->emissiveColor);
                        if (it->getLinkPoints())
                            ogl::drawRandom3dLines(&ogl::buffer[0], (int)ogl::buffer.size() / 3, true,
                                                   normalVectorForLinesAndPoints.data);
                        else
                            ogl::drawRandom3dPoints(&ogl::buffer[0], (int)ogl::buffer.size() / 3,
                                                    normalVectorForLinesAndPoints.data);
                        if (it->getLabel() && (displayAttrib & sim_displayattribute_renderpass) &&
                            ((displayAttrib & sim_displayattribute_forvisionsensor) == 0))
                            ogl::drawBitmapTextTo3dPosition(&ogl::buffer[0], (it->getName() + " [STATIC]").c_str(),
                                                            normalVectorForLinesAndPoints.data);
                    }
                    ogl::buffer.clear();
                    glLineWidth(1.0);
                    glPointSize(1.0);
                    glDisable(GL_LINE_STIPPLE);
                }
            }
        }

        _disableAuxClippingPlanes();
    }

    // At the end of every scene object display routine:
    _commonFinish(graph, renderingObject);
}
