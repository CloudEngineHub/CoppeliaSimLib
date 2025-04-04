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

#include <octreeRendering.h>
#include <guiApp.h>

const int _cubeIndices[] = {0, 1, 2, 0, 2, 3, 4, 5, 6, 4, 6, 7, 8, 9, 10, 8, 10, 11,
                            12, 13, 14, 12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22, 20, 22, 23};

const float _cubeNormals[] = {
    -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0,
    0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0,
    1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0,
    0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0,
    0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0};

void displayOctree(COcTree* octree, CViewableBase* renderingObject, int displayAttrib)
{
    // At the beginning of every scene object display routine:
    _commonStart(octree, renderingObject);

    C3Vector normalVectorForLinesAndPoints(octree->getFullCumulativeTransformation().Q.getInverse() *
                                           C3Vector::unitZVector);

    // Object display:
    if (octree->getShouldObjectBeDisplayed(renderingObject->getObjectHandle(), displayAttrib))
    {
        if ((GuiApp::getEditModeType() & SHAPE_OR_PATH_EDIT_MODE_OLD) == 0)
        {
            if (octree->getObjectProperty() & sim_objectproperty_selectmodelbaseinstead)
                glLoadName(octree->getModelSelectionHandle());
            else
                glLoadName(octree->getObjectHandle());
        }
        else
            glLoadName(-1);

        if ((displayAttrib & sim_displayattribute_forcewireframe) && (displayAttrib & sim_displayattribute_renderpass))
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        if ((displayAttrib & sim_displayattribute_forcewireframe) == 0)
            glEnable(GL_CULL_FACE);

        _enableAuxClippingPlanes(octree->getObjectHandle());

        if (octree->getOctreeInfo() != nullptr)
        {
            std::vector<double>& _voxelPositions = octree->getCubePositions()[0];
            float* _cubeVertices = octree->getCubeVertices();
            octree->getColor()->makeCurrentColor(false);

            if (octree->getShowOctree() && ((displayAttrib & sim_displayattribute_forvisionsensor) == 0))
            {
                std::vector<double> corners;
                App::worldContainer->pluginContainer->geomPlugin_getOctreeCornersFromOctree(octree->getOctreeInfo(),
                                                                                            corners);

                glBegin(GL_LINES);
                glNormal3dv(normalVectorForLinesAndPoints.data);

                for (size_t i = 0; i < corners.size() / 24; i++)
                {
                    glVertex3dv(&corners[0] + i * 8 * 3 + 0);
                    glVertex3dv(&corners[0] + i * 8 * 3 + 3);
                    glVertex3dv(&corners[0] + i * 8 * 3 + 3);
                    glVertex3dv(&corners[0] + i * 8 * 3 + 9);
                    glVertex3dv(&corners[0] + i * 8 * 3 + 0);
                    glVertex3dv(&corners[0] + i * 8 * 3 + 6);
                    glVertex3dv(&corners[0] + i * 8 * 3 + 6);
                    glVertex3dv(&corners[0] + i * 8 * 3 + 9);

                    glVertex3dv(&corners[0] + i * 8 * 3 + 12);
                    glVertex3dv(&corners[0] + i * 8 * 3 + 15);
                    glVertex3dv(&corners[0] + i * 8 * 3 + 15);
                    glVertex3dv(&corners[0] + i * 8 * 3 + 21);
                    glVertex3dv(&corners[0] + i * 8 * 3 + 12);
                    glVertex3dv(&corners[0] + i * 8 * 3 + 18);
                    glVertex3dv(&corners[0] + i * 8 * 3 + 18);
                    glVertex3dv(&corners[0] + i * 8 * 3 + 21);

                    glVertex3dv(&corners[0] + i * 8 * 3 + 0);
                    glVertex3dv(&corners[0] + i * 8 * 3 + 12);

                    glVertex3dv(&corners[0] + i * 8 * 3 + 3);
                    glVertex3dv(&corners[0] + i * 8 * 3 + 15);

                    glVertex3dv(&corners[0] + i * 8 * 3 + 6);
                    glVertex3dv(&corners[0] + i * 8 * 3 + 18);

                    glVertex3dv(&corners[0] + i * 8 * 3 + 9);
                    glVertex3dv(&corners[0] + i * 8 * 3 + 21);
                }
                glEnd();
            }

            if (octree->getCellSizeForDisplay() != octree->getCellSize())
            { // we need to reconstruct the buffer cube:
                octree->setCellSizeForDisplay(octree->getCellSize());

                float ss = float(octree->getCellSize() * 0.5);
                int ind = 0;
                _cubeVertices[ind++] = -ss;
                _cubeVertices[ind++] = -ss;
                _cubeVertices[ind++] = ss;
                _cubeVertices[ind++] = -ss;
                _cubeVertices[ind++] = ss;
                _cubeVertices[ind++] = ss;
                _cubeVertices[ind++] = -ss;
                _cubeVertices[ind++] = ss;
                _cubeVertices[ind++] = -ss;
                _cubeVertices[ind++] = -ss;
                _cubeVertices[ind++] = -ss;
                _cubeVertices[ind++] = -ss;

                _cubeVertices[ind++] = -ss;
                _cubeVertices[ind++] = -ss;
                _cubeVertices[ind++] = -ss;
                _cubeVertices[ind++] = -ss;
                _cubeVertices[ind++] = ss;
                _cubeVertices[ind++] = -ss;
                _cubeVertices[ind++] = ss;
                _cubeVertices[ind++] = ss;
                _cubeVertices[ind++] = -ss;
                _cubeVertices[ind++] = ss;
                _cubeVertices[ind++] = -ss;
                _cubeVertices[ind++] = -ss;

                _cubeVertices[ind++] = ss;
                _cubeVertices[ind++] = -ss;
                _cubeVertices[ind++] = -ss;
                _cubeVertices[ind++] = ss;
                _cubeVertices[ind++] = ss;
                _cubeVertices[ind++] = -ss;
                _cubeVertices[ind++] = ss;
                _cubeVertices[ind++] = ss;
                _cubeVertices[ind++] = ss;
                _cubeVertices[ind++] = ss;
                _cubeVertices[ind++] = -ss;
                _cubeVertices[ind++] = ss;

                _cubeVertices[ind++] = ss;
                _cubeVertices[ind++] = -ss;
                _cubeVertices[ind++] = ss;
                _cubeVertices[ind++] = ss;
                _cubeVertices[ind++] = ss;
                _cubeVertices[ind++] = ss;
                _cubeVertices[ind++] = -ss;
                _cubeVertices[ind++] = ss;
                _cubeVertices[ind++] = ss;
                _cubeVertices[ind++] = -ss;
                _cubeVertices[ind++] = -ss;
                _cubeVertices[ind++] = ss;

                _cubeVertices[ind++] = -ss;
                _cubeVertices[ind++] = -ss;
                _cubeVertices[ind++] = ss;
                _cubeVertices[ind++] = -ss;
                _cubeVertices[ind++] = -ss;
                _cubeVertices[ind++] = -ss;
                _cubeVertices[ind++] = ss;
                _cubeVertices[ind++] = -ss;
                _cubeVertices[ind++] = -ss;
                _cubeVertices[ind++] = ss;
                _cubeVertices[ind++] = -ss;
                _cubeVertices[ind++] = ss;

                _cubeVertices[ind++] = -ss;
                _cubeVertices[ind++] = ss;
                _cubeVertices[ind++] = ss;
                _cubeVertices[ind++] = ss;
                _cubeVertices[ind++] = ss;
                _cubeVertices[ind++] = ss;
                _cubeVertices[ind++] = ss;
                _cubeVertices[ind++] = ss;
                _cubeVertices[ind++] = -ss;
                _cubeVertices[ind++] = -ss;
                _cubeVertices[ind++] = ss;
                _cubeVertices[ind++] = -ss;

                octree->setVertexBufferId(-1);
                octree->setNormalBufferId(-1);
            }

            const float blk[4] = {0.0, 0.0, 0.0, 0.0};
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, blk);
            if (octree->getUsePointsInsteadOfCubes())
            {
                glPointSize(float(octree->getPointSize()));
                ogl::drawRandom3dPointsEx(&_voxelPositions[0], (int)_voxelPositions.size() / 3, nullptr,
                                          octree->getColors(), nullptr, octree->getColorIsEmissive(),
                                          normalVectorForLinesAndPoints.data);
                glPointSize(1.0);
            }
            else
            {
                if (octree->getColorIsEmissive())
                {
                    for (size_t i = 0; i < _voxelPositions.size() / 3; i++)
                    {
                        glPushMatrix();
                        glTranslated(_voxelPositions[3 * i + 0], _voxelPositions[3 * i + 1],
                                     _voxelPositions[3 * i + 2]);
                        const float* cc = octree->getColors();
                        float c[4] = {cc[4 * i + 0], cc[4 * i + 1], cc[4 * i + 2], cc[4 * i + 3]};
                        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, c);
                        int _vertexBufferId = octree->getVertexBufferId();
                        int _normalBufferId = octree->getNormalBufferId();
                        _drawTriangles(_cubeVertices, 24, _cubeIndices, 36, _cubeNormals, nullptr, &_vertexBufferId,
                                       &_normalBufferId, nullptr);
                        octree->setVertexBufferId(_vertexBufferId);
                        octree->setNormalBufferId(_normalBufferId);
                        glEnd();
                        glPopMatrix();
                    }
                }
                else
                {
                    for (size_t i = 0; i < _voxelPositions.size() / 3; i++)
                    {
                        glPushMatrix();
                        glTranslated(_voxelPositions[3 * i + 0], _voxelPositions[3 * i + 1],
                                     _voxelPositions[3 * i + 2]);

                        const float* cc = octree->getColors();
                        float c[4] = {cc[4 * i + 0], cc[4 * i + 1], cc[4 * i + 2], cc[4 * i + 3]};
                        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, c);
                        int _vertexBufferId = octree->getVertexBufferId();
                        int _normalBufferId = octree->getNormalBufferId();
                        _drawTriangles(_cubeVertices, 24, _cubeIndices, 36, _cubeNormals, nullptr, &_vertexBufferId,
                                       &_normalBufferId, nullptr);
                        octree->setVertexBufferId(_vertexBufferId);
                        octree->setNormalBufferId(_normalBufferId);
                        glEnd();
                        glPopMatrix();
                    }
                }
            }
        }

        glDisable(GL_CULL_FACE);
        _disableAuxClippingPlanes();
    }

    // At the end of every scene object display routine:
    _commonFinish(octree, renderingObject);
}
