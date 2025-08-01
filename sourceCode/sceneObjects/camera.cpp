#include <camera.h>
#include <simInternal.h>
#include <tt.h>
#include <meshManip.h>
#include <global.h>
#include <sceneObjectOperations.h>
#include <graphingRoutines_old.h>
#include <simStrings.h>
#include <vDateTime.h>
#include <utils.h>
#include <app.h>
#ifdef SIM_WITH_GUI
#include <cameraRendering.h>
#include <guiApp.h>
#include <rendering.h>
#include <oGL.h>
#endif

unsigned int CCamera::selectBuff[SELECTION_BUFFER_SIZE * 4];

CCamera::CCamera()
{
    commonInit();
}

std::string CCamera::getObjectTypeInfo() const
{
    return "camera";
}

std::string CCamera::getObjectTypeInfoExtended() const
{
    return getObjectTypeInfo();
}
bool CCamera::isPotentiallyCollidable() const
{
    return (false);
}
bool CCamera::isPotentiallyMeasurable() const
{
    return (false);
}
bool CCamera::isPotentiallyDetectable() const
{
    return (false);
}
bool CCamera::isPotentiallyRenderable() const
{
    return (false);
}

CColorObject* CCamera::getColor(bool secondPart)
{
    if (secondPart)
        return (&_color_removeSoon);
    return (&_color);
}

void CCamera::frameSceneOrSelectedObjects(double windowWidthByHeight, bool forPerspectiveProjection,
                                          std::vector<int>* selectedObjects, bool useSystemSelection,
                                          bool includeModelObjects, double scalingFactor, CSView* optionalView)
{
    std::vector<double> pts;
    C7Vector camTr(getFullCumulativeTransformation());
    C7Vector camTrInv(camTr.getInverse());
    int editMode = NO_EDIT_MODE;
    int displAttributes = 0;
    if (App::currentWorld->simulation->getDynamicContentVisualizationOnly())
        displAttributes = sim_displayattribute_dynamiccontentonly;

#ifdef SIM_WITH_GUI
    if (GuiApp::mainWindow != nullptr)
    {
        editMode = GuiApp::getEditModeType();
        if ((editMode & SHAPE_EDIT_MODE) != 0)
        { // just take the vertices
            if (GuiApp::mainWindow->editModeContainer->getShapeEditMode()->getEditionVerticesSize() == 0)
                editMode = NO_EDIT_MODE;
            else
            {
                CSceneObject* parentObj = GuiApp::mainWindow->editModeContainer->getEditModeShape();
                if (parentObj != nullptr)
                {
                    C7Vector parentTr(parentObj->getFullCumulativeTransformation());
                    if (editMode == VERTEX_EDIT_MODE)
                    {
                        for (int i = 0;
                             i <
                             GuiApp::mainWindow->editModeContainer->getShapeEditMode()->getEditionVerticesSize() / 3;
                             i++)
                        {
                            C3Vector v(GuiApp::mainWindow->editModeContainer->getShapeEditMode()->getEditionVertex(i));
                            v = camTrInv * parentTr * v;
                            pts.push_back(v(0));
                            pts.push_back(v(1));
                            pts.push_back(v(2));
                        }
                        scalingFactor *= 0.98;
                    }
                    else
                    { // Triangle or edge edit mode:
                        if (GuiApp::mainWindow->editModeContainer->getShapeEditMode()->getEditionIndicesSize() != 0)
                        {
                            for (int i = 0;
                                 i <
                                 GuiApp::mainWindow->editModeContainer->getShapeEditMode()->getEditionIndicesSize() / 3;
                                 i++)
                            { // here we will get every vertex many times, but it doesn't really matter
                                int ind[3];
                                GuiApp::mainWindow->editModeContainer->getShapeEditMode()->getEditionTriangle(i, ind);
                                for (int j = 0; j < 3; j++)
                                {
                                    C3Vector v(
                                        GuiApp::mainWindow->editModeContainer->getShapeEditMode()->getEditionVertex(
                                            ind[j]));
                                    v = camTrInv * parentTr * v;
                                    pts.push_back(v(0));
                                    pts.push_back(v(1));
                                    pts.push_back(v(2));
                                }
                            }
                            scalingFactor *= 0.98;
                        }
                        else
                            editMode = NO_EDIT_MODE;
                    }
                }
                else
                    editMode = NO_EDIT_MODE;
            }
        }
        if ((editMode & PATH_EDIT_MODE_OLD) != 0)
        { // just take the path points
            if (GuiApp::mainWindow->editModeContainer->getEditModePathContainer_old() == nullptr)
                editMode = NO_EDIT_MODE;
            else
            {
                int cnt =
                    GuiApp::mainWindow->editModeContainer->getEditModePathContainer_old()->getSimplePathPointCount();
                CPath_old* path = GuiApp::mainWindow->editModeContainer->getEditModePath_old();
                if ((cnt != 0) && (path != nullptr))
                {
                    C7Vector parentTr(path->getFullCumulativeTransformation());
                    for (int i = 0; i < cnt; i++)
                    {
                        CSimplePathPoint_old* pp =
                            GuiApp::mainWindow->editModeContainer->getEditModePathContainer_old()->getSimplePathPoint(
                                i);
                        C3Vector v(camTrInv * parentTr * pp->getTransformation().X);
                        pts.push_back(v(0));
                        pts.push_back(v(1));
                        pts.push_back(v(2));
                    }
                    scalingFactor *= 0.98;
                }
                else
                    editMode = NO_EDIT_MODE;
            }
        }
    }
#endif

    if ((editMode == NO_EDIT_MODE) || ((editMode & MULTISHAPE_EDIT_MODE) != 0))
    {
        std::vector<CSceneObject*> sel;
        if (editMode == NO_EDIT_MODE)
        {
            CSceneObject* skybox = App::currentWorld->sceneObjects->getObjectFromName_old(IDSOGL_SKYBOX_DO_NOT_RENAME);
            // 1. List of all visible objects, excluding this camera, the skybox and objects flaged as
            // "ignoreViewFitting":
            std::vector<CSceneObject*> visibleObjs;
            for (size_t i = 0; i < App::currentWorld->sceneObjects->getObjectCount(); i++)
            {
                CSceneObject* it = App::currentWorld->sceneObjects->getObjectFromIndex(i);
                if (it != this)
                {
                    bool displayMaybe = it->getShouldObjectBeDisplayed(_objectHandle, displAttributes);
                    if (displayMaybe)
                    {
                        if (((skybox == nullptr) || (!it->hasAncestor(skybox))) &&
                            ((it->getObjectProperty() & sim_objectproperty_ignoreviewfitting) == 0))
                            visibleObjs.push_back(it);
                    }
                }
            }
            // 1.b if the list of visible objects is empty, include the objects normally ignored for view fitting!
            if (visibleObjs.size() == 0)
            {
                for (size_t i = 0; i < App::currentWorld->sceneObjects->getObjectCount(); i++)
                {
                    CSceneObject* it = App::currentWorld->sceneObjects->getObjectFromIndex(i);
                    if (it != this)
                    {
                        bool displayMaybe = it->getShouldObjectBeDisplayed(_objectHandle, displAttributes);
                        if (displayMaybe)
                        {
                            if ((skybox == nullptr) || (!it->hasAncestor(skybox)))
                                visibleObjs.push_back(it);
                        }
                    }
                }
            }
            // 2. List of current selection, excluding this camera and the skybox objects:
            std::vector<int> tmp;
            if (useSystemSelection)
                App::currentWorld->sceneObjects->getSelectedObjectHandles(tmp);
            else
            {
                if (selectedObjects != nullptr)
                    tmp.assign(selectedObjects->begin(), selectedObjects->end());
            }
            if (includeModelObjects)
                App::currentWorld->sceneObjects->addModelObjects(tmp);
            std::vector<CSceneObject*> selectionVisibleObjs;
            for (int i = 0; i < int(tmp.size()); i++)
            { // We only wanna have visible objects, otherwise we get strange behaviour with some models!! And only
                // objects that are not ignored by the view-fitting:
                CSceneObject* it = App::currentWorld->sceneObjects->getObjectFromHandle(tmp[i]);
                if ((it != nullptr) && (it != this))
                {
                    bool displayMaybe = it->getShouldObjectBeDisplayed(_objectHandle, displAttributes);
                    if (displayMaybe)
                    {
                        if (((skybox == nullptr) || (!it->hasAncestor(skybox))) &&
                            ((it->getObjectProperty() & sim_objectproperty_ignoreviewfitting) == 0))
                            selectionVisibleObjs.push_back(it);
                    }
                }
            }
            // 3. set-up a list of all objects that should be framed:
            if (selectionVisibleObjs.size() != 0)
                sel.assign(selectionVisibleObjs.begin(), selectionVisibleObjs.end());
            else
                sel.assign(visibleObjs.begin(), visibleObjs.end());
        }

#ifdef SIM_WITH_GUI
        if (GuiApp::mainWindow != nullptr)
        {
            if ((editMode & MULTISHAPE_EDIT_MODE) != 0)
            {
                CShape* sh = GuiApp::mainWindow->editModeContainer->getEditModeShape();
                if (sh != nullptr)
                    sel.push_back(sh);
            }
        }
#endif

        // 4. Now do the calculations:
        // 4.a Get all relative coordinates of all oriented bounding box corners, or all relative vertices:
        for (int i = 0; i < int(sel.size()); i++)
        {
            CSceneObject* it = sel[i];
            bool done = false;
            if (it->getObjectType() == sim_sceneobject_path)
            {
                done = true;
                CPath_old* path = (CPath_old*)it;
                int cnt = path->pathContainer->getSimplePathPointCount();
                if ((cnt != 0) && (path != nullptr))
                {
                    C7Vector parentTr(path->getFullCumulativeTransformation());
                    for (int i = 0; i < cnt; i++)
                    {
                        CSimplePathPoint_old* pp = path->pathContainer->getSimplePathPoint(i);
                        C3Vector v(camTrInv * parentTr * pp->getTransformation().X);
                        pts.push_back(v(0));
                        pts.push_back(v(1));
                        pts.push_back(v(2));
                    }
                }
            }
            if (it->getObjectType() == sim_sceneobject_shape)
            {
                done = true;
                CShape* shape = (CShape*)it;
                C7Vector trr(camTrInv * shape->getFullCumulativeTransformation());
                std::vector<double> wvert;
                shape->getMesh()->getCumulativeMeshes(C7Vector::identityTransformation, wvert, nullptr, nullptr);
                for (int j = 0; j < int(wvert.size()) / 3; j++)
                {
                    C3Vector vq(&wvert[3 * j + 0]);
                    vq *= trr;
                    pts.push_back(vq(0));
                    pts.push_back(vq(1));
                    pts.push_back(vq(2));
                }
            }
            if (it->getObjectType() == sim_sceneobject_pointcloud)
            {
                done = true;
                CPointCloud* ptCloud = (CPointCloud*)it;
                C7Vector trr(camTrInv * ptCloud->getCumulativeTransformation());
                std::vector<double>* wvert = ptCloud->getPoints();
                for (int j = 0; j < int(wvert->size()) / 3; j++)
                {
                    C3Vector vq(&(wvert[0])[3 * j + 0]);
                    vq *= trr;
                    pts.push_back(vq(0));
                    pts.push_back(vq(1));
                    pts.push_back(vq(2));
                }
            }
            if (it->getObjectType() == sim_sceneobject_octree)
            {
                done = true;
                COcTree* octree = (COcTree*)it;
                C7Vector trr(camTrInv * octree->getCumulativeTransformation());
                std::vector<double>* wvert = octree->getCubePositions();
                for (int j = 0; j < int(wvert->size()) / 3; j++)
                {
                    C3Vector vq(&(wvert[0])[3 * j + 0]);
                    vq *= trr;
                    pts.push_back(vq(0));
                    pts.push_back(vq(1));
                    pts.push_back(vq(2));
                }
            }
            if (!done)
            {
                C3Vector minV(C3Vector::inf);
                C3Vector maxV(C3Vector::ninf);
                C3Vector bbs;
                C7Vector tr(camTrInv * it->getCumulativeTransformation() * it->getBB(&bbs));
                bbs *= 2.0;
                C3Vector v;
                for (double k = -1.0; k < 2.0; k = k + 2.0)
                {
                    v(0) = bbs(0) * k * 0.5;
                    for (double l = -1.0; l < 2.0; l = l + 2.0)
                    {
                        v(1) = bbs(1) * l * 0.5;
                        for (double m = -1.0; m < 2.0; m = m + 2.0)
                        {
                            v(2) = bbs(2) * m * 0.5;
                            C3Vector w(tr * v);
                            maxV.keepMax(w);
                            minV.keepMin(w);
                        }
                    }
                }
                for (int k = 0; k < 2; k++)
                {
                    for (int l = 0; l < 2; l++)
                    {
                        for (int m = 0; m < 2; m++)
                        {
                            pts.push_back(minV(0) + (maxV(0) - minV(0)) * k);
                            pts.push_back(minV(1) + (maxV(1) - minV(1)) * l);
                            pts.push_back(minV(2) + (maxV(2) - minV(2)) * m);
                        }
                    }
                }
            }
        }
    }

    if (pts.size() == 0)
        return;

    if (getTrackedObjectHandle() != -1)
    { // When tracking an object, we should stay on the current view axis. To do this, we simply reflect all points
        // left/right/top/bottom relative to the camera!
        std::vector<double> ptsC(pts);
        pts.clear();
        for (int i = 0; i < int(ptsC.size()) / 3; i++)
        {
            C3Vector wv(&ptsC[3 * i + 0]);
            pts.push_back(wv(0));
            pts.push_back(wv(1));
            pts.push_back(wv(2));
            pts.push_back(-wv(0));
            pts.push_back(wv(1));
            pts.push_back(wv(2));
            pts.push_back(wv(0));
            pts.push_back(-wv(1));
            pts.push_back(wv(2));
            pts.push_back(-wv(0));
            pts.push_back(-wv(1));
            pts.push_back(wv(2));
        }
    }
    /* // Here trying to scale the points, instead of camera angle/camera ortho view size
       //
        double qwmin,qwmax;
        for (int i=0;i<int(pts.size())/3;i++)
        {
            if (i==0)
            {
                qwmin=pts[3*i+2];
                qwmax=pts[3*i+2];
            }
            else
            {
                if (qwmin>pts[3*i+2])
                    qwmin=pts[3*i+2];
                if (qwmax<pts[3*i+2])
                    qwmax=pts[3*i+2];
            }
        }

        double qwavg=(qwmax+qwmin)*0.5;
        for (int i=0;i<int(pts.size())/3;i++)
        {
            pts[3*i+0]*=1.0/scalingFactor;
            pts[3*i+1]*=1.0/scalingFactor;
            pts[3*i+2]=(pts[3*i+2]-qwavg)*(1.0/scalingFactor)+qwavg;
        }
    */
    C3Vector relativeCameraTranslation;
    relativeCameraTranslation.clear();
    double nearClippingPlaneCorrection = 0.0;
    double farClippingPlaneCorrection = 0.0;
    double viewSizeCorrection = 0.0;
    if (forPerspectiveProjection)
    {
        C3Vector relativeCameraTranslation_verticalAdjustment;
        C3Vector relativeCameraTranslation_horizontalAdjustment;
        relativeCameraTranslation_verticalAdjustment.clear();
        relativeCameraTranslation_horizontalAdjustment.clear();
        std::vector<double> cop(pts);
        //*****************
        double effectiveAngle = getViewAngle() * scalingFactor;
        if (effectiveAngle > piValue)
            effectiveAngle = piValue;

        if (windowWidthByHeight > 1.0)
            effectiveAngle /= windowWidthByHeight;

        C4X4Matrix lowerLimit;
        lowerLimit.buildXRotation(effectiveAngle * 0.5);
        C4X4Matrix lowerLimitInv(lowerLimit.getInverse());
        C3Vector minw;
        C3Vector maxw;
        for (int i = 0; i < int(pts.size()) / 3; i++)
        {
            C3Vector w(pts[3 * i + 0], pts[3 * i + 1], pts[3 * i + 2]);
            w *= lowerLimitInv;
            if (i == 0)
            {
                minw = w;
                maxw = w;
            }
            else
            {
                minw.keepMin(w);
                maxw.keepMax(w);
            }
        }
        C4X4Matrix cm(getFullLocalTransformation().getMatrix() * lowerLimit);
        relativeCameraTranslation_verticalAdjustment = cm.M.axis[1] * minw(1);

        C3Vector camShift(lowerLimit.M.axis[1] * minw(1));
        for (int i = 0; i < int(pts.size()) / 3; i++)
        {
            pts[3 * i + 0] -= camShift(0);
            pts[3 * i + 1] -= camShift(1);
            pts[3 * i + 2] -= camShift(2);
        }

        C4X4Matrix upperLimit;
        upperLimit.buildXRotation(-effectiveAngle * 0.5);
        C4X4Matrix upperLimitInv(upperLimit.getInverse());
        for (int i = 0; i < int(pts.size()) / 3; i++)
        {
            C3Vector w(pts[3 * i + 0], pts[3 * i + 1], pts[3 * i + 2]);
            w *= upperLimitInv;
            if (i == 0)
            {
                minw = w;
                maxw = w;
            }
            else
            {
                minw.keepMin(w);
                maxw.keepMax(w);
            }
        }

        cm = getFullLocalTransformation().getMatrix() * lowerLimit;
        double dist = -maxw(1) / sin(effectiveAngle);
        relativeCameraTranslation_verticalAdjustment += cm.M.axis[2] * dist;

        // ***************** left-right

        pts.assign(cop.begin(), cop.end());

        effectiveAngle = getViewAngle() * scalingFactor;
        if (windowWidthByHeight < 1.0)
            effectiveAngle *= windowWidthByHeight;

        C4X4Matrix leftLimit;
        leftLimit.buildYRotation(effectiveAngle * 0.5);
        C4X4Matrix leftLimitInv(leftLimit.getInverse());
        for (int i = 0; i < int(pts.size()) / 3; i++)
        {
            C3Vector w(pts[3 * i + 0], pts[3 * i + 1], pts[3 * i + 2]);
            w *= leftLimitInv;
            if (i == 0)
            {
                minw = w;
                maxw = w;
            }
            else
            {
                minw.keepMin(w);
                maxw.keepMax(w);
            }
        }
        cm = getFullLocalTransformation().getMatrix() * leftLimit;
        relativeCameraTranslation_horizontalAdjustment = cm.M.axis[0] * maxw(0);

        camShift = leftLimit.M.axis[0] * maxw(0);
        for (int i = 0; i < int(pts.size()) / 3; i++)
        {
            pts[3 * i + 0] -= camShift(0);
            pts[3 * i + 1] -= camShift(1);
            pts[3 * i + 2] -= camShift(2);
        }

        C4X4Matrix rightLimit;
        rightLimit.buildYRotation(-effectiveAngle * 0.5);
        C4X4Matrix rightLimitInv(rightLimit.getInverse());
        for (int i = 0; i < int(pts.size()) / 3; i++)
        {
            C3Vector w(pts[3 * i + 0], pts[3 * i + 1], pts[3 * i + 2]);
            w *= rightLimitInv;
            if (i == 0)
            {
                minw = w;
                maxw = w;
            }
            else
            {
                minw.keepMin(w);
                maxw.keepMax(w);
            }
        }

        cm = getFullLocalTransformation().getMatrix() * leftLimit;
        dist = minw(0) / sin(effectiveAngle);
        relativeCameraTranslation_horizontalAdjustment += cm.M.axis[2] * dist;

        // Decide which coords to select
        cm = getFullLocalTransformation().getMatrix();
        C3Vector vert(cm.getInverse() * relativeCameraTranslation_verticalAdjustment);
        C3Vector horiz(cm.getInverse() * relativeCameraTranslation_horizontalAdjustment);
        C3Vector f;
        f(0) = horiz(0);
        f(1) = vert(1);
        f(2) = vert(2);
        if (horiz(2) < vert(2))
            f(2) = horiz(2);
        relativeCameraTranslation = cm * f;

        // Adjust the near and far clipping planes if needed:
        pts.assign(cop.begin(), cop.end());
        C4X4Matrix ncm(cm);
        ncm.X += relativeCameraTranslation;
        C4X4Matrix tr(ncm.getInverse() * cm);
        for (int i = 0; i < int(pts.size()) / 3; i++)
        {
            C3Vector w(pts[3 * i + 0], pts[3 * i + 1], pts[3 * i + 2]);
            w *= tr;
            if (i == 0)
            {
                minw = w;
                maxw = w;
            }
            else
            {
                minw.keepMin(w);
                maxw.keepMax(w);
            }
        }
        double zCorr = 0.0;
        if (minw(2) < _nearClippingPlane)
            zCorr = minw(2) - _nearClippingPlane;
        relativeCameraTranslation += cm.M.axis[2] * zCorr; // zCorr is negative or 0
        if (maxw(2) > _farClippingPlane + zCorr)
            farClippingPlaneCorrection = maxw(2) - zCorr - _farClippingPlane;
    }
    else
    { // orthographic projection:
        C3Vector minw;
        C3Vector maxw;
        for (int i = 0; i < int(pts.size()) / 3; i++)
        {
            C3Vector w(pts[3 * i + 0], pts[3 * i + 1], pts[3 * i + 2]);
            if (i == 0)
            {
                minw = w;
                maxw = w;
            }
            else
            {
                minw.keepMin(w);
                maxw.keepMax(w);
            }
        }
        C3Vector center((minw + maxw) / 2.0);
        // Move the camera to look at the center of those points (just 2 translations) + backshift if needed:
        double backShift = 0.0;
        if (minw(2) < _nearClippingPlane)
            backShift = minw(2) - _nearClippingPlane;
        C4X4Matrix cm(getFullLocalTransformation().getMatrix());
        relativeCameraTranslation = cm.M.axis[0] * center(0) + cm.M.axis[1] * center(1) + cm.M.axis[2] * backShift;
        if (maxw(2) > ((_farClippingPlane + backShift) / 1.2))
            farClippingPlaneCorrection = (maxw(2) - (_farClippingPlane + backShift)) * 1.2;
        double vs = getOrthoViewSize();
        double dx = (maxw(0) - minw(0)) / scalingFactor;
        double dy = (maxw(1) - minw(1)) / scalingFactor;
        double rap = 9999999.0;
        if (dy != 0.0)
            rap = dx / dy;
        if (windowWidthByHeight > 1.0)
        {
            if (rap >= windowWidthByHeight)
                viewSizeCorrection = dx - vs;
            else
                viewSizeCorrection = (dy - vs / windowWidthByHeight) * windowWidthByHeight;
        }
        else
        {
            if (rap <= windowWidthByHeight)
                viewSizeCorrection = dy - vs;
            else
                viewSizeCorrection = (dx - vs * windowWidthByHeight) / windowWidthByHeight;
        }
    }
    C4X4Matrix cm(getFullLocalTransformation().getMatrix());
    cm.X += relativeCameraTranslation;

    setClippingPlanes(_nearClippingPlane + nearClippingPlaneCorrection, _farClippingPlane + farClippingPlaneCorrection);
    setOrthoViewSize(getOrthoViewSize() + viewSizeCorrection);
    CSceneObject* cameraParentProxy = nullptr;
    if (getUseParentObjectAsManipulationProxy())
        cameraParentProxy = getParent();

    if (cameraParentProxy != nullptr)
    { // We report the same camera opening to all cameras attached to cameraParentProxy
        if (!forPerspectiveProjection)
        {
            for (size_t i = 0; i < cameraParentProxy->getChildCount(); i++)
            {
                CSceneObject* child = cameraParentProxy->getChildFromIndex(i);
                if (child->getObjectType() == sim_sceneobject_camera)
                    ((CCamera*)child)->setOrthoViewSize(getOrthoViewSize());
            }
        }
        cameraParentProxy->setLocalTransformation(cameraParentProxy->getFullLocalTransformation() *
                                                  cm.getTransformation() * getFullLocalTransformation().getInverse());
    }
    else
        setLocalTransformation(cm.getTransformation());
}

void CCamera::commonInit()
{
    _showVolume = false;
    _objectType = sim_sceneobject_camera;
    _nearClippingPlane = 0.05;
    _farClippingPlane = 30.0;
    _cameraSize = 0.05;
    _renderMode = sim_rendermode_opengl;
    _renderModeDuringSimulation = false;
    _renderModeDuringRecording = false;
    _isMainCamera = false;

    _viewAngle = 60.0 * degToRad;
    _orthoViewSize = 2.0;
    _hideFog = false;
    _useLocalLights = false;
    _allowPicking = true;
    if (_extensionString.size() != 0)
        _extensionString += " ";
    _extensionString += "povray {focalBlur {false} focalDist {2.00} aperture{0.05} blurSamples{10}}";
    hitForMouseUpProcessing_minus2MeansIgnore = -2;
    _attributesForRendering = sim_displayattribute_renderpass;
    _textureNameForExtGeneratedView = (unsigned int)-1;

    _viewModeSet_old = true;
    _allowTranslation = true;
    _allowRotation = true;

    _objectMovementPreferredAxes = 0x013;

    _trackedObjectHandle = -1;
    _visibilityLayer = CAMERA_LIGHT_LAYER;
    _localObjectSpecialProperty = 0;
    _useParentObjectAsManipulationProxy = false;

    _color.setDefaultValues();
    _color.setColor(0.9f, 0.2f, 0.2f, sim_colorcomponent_ambient_diffuse);
    _color_removeSoon.setDefaultValues();
    _color_removeSoon.setColor(0.22f, 0.22f, 0.22f, sim_colorcomponent_ambient_diffuse);

    _objectAlias = getObjectTypeInfo();
    _objectName_old = getObjectTypeInfo();
    _objectAltName_old = tt::getObjectAltNameFromObjectName(_objectName_old.c_str());
    computeBoundingBox();
    computeVolumeVectors();
}

void CCamera::setAllowTranslation(bool allow)
{
    if (_allowTranslation != allow)
    {
        _allowTranslation = allow;
        if (_isInScene && App::worldContainer->getEventsEnabled())
        {
#if SIM_EVENT_PROTOCOL_VERSION == 2
            const char* cmd = "allowTranslation";
#else
            const char* cmd = propCamera_translationEnabled.name;
#endif
            CCbor* ev = App::worldContainer->createSceneObjectChangedEvent(this, false, cmd, true);
            ev->appendKeyBool(cmd, _allowTranslation);
            App::worldContainer->pushEvent();
        }
    }
}

bool CCamera::getAllowTranslation() const
{
    return _allowTranslation;
}

void CCamera::setAllowRotation(bool allow)
{
    if (_allowRotation != allow)
    {
        _allowRotation = allow;
        if (_isInScene && App::worldContainer->getEventsEnabled())
        {
#if SIM_EVENT_PROTOCOL_VERSION == 2
            const char* cmd = "allowRotation";
#else
            const char* cmd = propCamera_rotationEnabled.name;
#endif
            CCbor* ev = App::worldContainer->createSceneObjectChangedEvent(this, false, cmd, true);
            ev->appendKeyBool(cmd, _allowRotation);
            App::worldContainer->pushEvent();
        }
    }
}

bool CCamera::getAllowRotation() const
{
    return _allowRotation;
}

bool CCamera::getIsMainCamera()
{
    bool retVal = _isMainCamera;
    _isMainCamera = false;
    return (retVal);
}

std::string CCamera::getTrackedObjectLoadAlias() const
{
    return (_trackedObjectLoadAlias);
}

std::string CCamera::getTrackedObjectLoadName_old() const
{
    return (_trackedObjectLoadName_old);
}

void CCamera::shiftCameraInCameraManipulationMode(const C3Vector& newLocalPos)
{
    C4X4Matrix oldLocal(_localTransformation.getMatrix());
    C4X4Matrix newLocal(oldLocal);
    newLocal.X = newLocalPos;
    C4X4Matrix tr(oldLocal.getInverse() * newLocal);
    if (!_allowTranslation)
        tr.X.clear();
    setLocalTransformation(oldLocal * tr);
}
void CCamera::rotateCameraInCameraManipulationMode(const C7Vector& newLocalConf)
{
    if (_allowRotation)
        setLocalTransformation(newLocalConf);
}

void CCamera::computeBoundingBox()
{
    C7Vector fr;
    fr.Q.setIdentity();
    fr.X = C3Vector(0.0, 0.9, -0.9) * _cameraSize;
    _setBB(fr, C3Vector(1.0, 2.8, 3.8) * _cameraSize * 0.5);
}

void CCamera::setIsInScene(bool s)
{
    CSceneObject::setIsInScene(s);
    if (s)
        _color.setEventParams(true, _objectHandle);
    else
        _color.setEventParams(true, -1);
}

CCamera::~CCamera()
{
#ifdef SIM_WITH_GUI
    if (_textureNameForExtGeneratedView != (unsigned int)-1)
    {
        SUIThreadCommand cmdIn;
        SUIThreadCommand cmdOut;
        cmdIn.cmdId = DESTROY_GL_TEXTURE_UITHREADCMD;
        cmdIn.uintParams.push_back(_textureNameForExtGeneratedView);
        GuiApp::uiThread->executeCommandViaUiThread(&cmdIn, &cmdOut);
        _textureNameForExtGeneratedView = (unsigned int)-1;
    }
#endif
}

void CCamera::handleCameraTracking()
{
    TRACE_INTERNAL;
    CSceneObject* tr = App::currentWorld->sceneObjects->getObjectFromHandle(_trackedObjectHandle);
    if ((tr == nullptr) || (tr == this) || tr->hasAncestor(this))
        setTrackedObjectHandle(-1);
    else
    {
        C7Vector tracked(tr->getFullCumulativeTransformation());
        C7Vector self(getFullCumulativeTransformation());
        C4Vector rot1(self.Q.getAxis(2), tracked.X - self.X);
        self.Q = rot1 * self.Q;
        // We check if the camera looks to +Z or -Z:
        C3Vector zAxis(self.Q.getAxis(2));
        if ((fabs(zAxis(0)) > 0.00001) || (fabs(zAxis(1)) > 0.00001))
        { // Camera does not look to +Z or -Z:
            C3Vector rotAxis(zAxis ^ C3Vector(0.0, 0.0, 1.0));
            C4Vector rot(piValue / 2.0, rotAxis);
            zAxis = rot * zAxis;
            C4Vector rot2(self.Q.getAxis(1), zAxis);
            self.Q = rot2 * self.Q;
            C7Vector parentInv(getFullParentCumulativeTransformation().getInverse());
            setLocalTransformation(parentInv * self);

            // Keep head up:
            C7Vector cameraCTM(getCumulativeTransformation());
            C3X3Matrix trM2(cameraCTM.Q);
            if ((fabs(trM2.axis[2](0)) > 0.00001) || (fabs(trM2.axis[2](1)) > 0.00001))
            { // We have to do it:
                double val = 1.0;
                if (trM2.axis[1](2) < 0.0)
                    val = -1.0;
                C3Vector rotAx(trM2.axis[2] ^ C3Vector(0.0, 0.0, val));
                C3Vector target(C4Vector(piValue / 2.0, rotAx) * trM2.axis[2]);
                C4Vector rot(trM2.axis[1], target);
                cameraCTM.Q = rot * cameraCTM.Q;
                setLocalTransformation(getFullParentCumulativeTransformation().getInverse() * cameraCTM);
            }
        }
    }
}

void CCamera::scaleObject(double scalingFactor)
{
    setCameraSize(_cameraSize * scalingFactor);
    setClippingPlanes(_nearClippingPlane * scalingFactor, _farClippingPlane * scalingFactor);
    setOrthoViewSize(_orthoViewSize * scalingFactor);

    CSceneObject::scaleObject(scalingFactor);
}

void CCamera::setCameraSize(double size)
{
    tt::limitValue(0.001, 100.0, size);
    if (_cameraSize != size)
    {
        _cameraSize = size;
        if (_isInScene && App::worldContainer->getEventsEnabled())
        {
            const char* cmd = propCamera_size.name;
            CCbor* ev = App::worldContainer->createSceneObjectChangedEvent(this, false, cmd, true);
            ev->appendKeyDouble(cmd, _cameraSize);
            App::worldContainer->pushEvent();
        }
        computeBoundingBox();
    }
}

double CCamera::getCameraSize() const
{
    return _cameraSize;
}

int CCamera::getTrackedObjectHandle() const
{
    return _trackedObjectHandle;
}

void CCamera::setUseParentObjectAsManipulationProxy(bool useParent)
{
    bool diff = (_useParentObjectAsManipulationProxy != useParent);
    if (diff)
    {
        _useParentObjectAsManipulationProxy = useParent;
        if (_isInScene && App::worldContainer->getEventsEnabled())
        {
            const char* cmd = propCamera_parentAsManipProxy.name;
            CCbor* ev = App::worldContainer->createSceneObjectChangedEvent(this, false, cmd, true);
            ev->appendKeyBool(cmd, _useParentObjectAsManipulationProxy);
            App::worldContainer->pushEvent();
        }
    }
}

bool CCamera::getUseParentObjectAsManipulationProxy() const
{
    return _useParentObjectAsManipulationProxy;
}

void CCamera::setTrackedObjectHandle(int trackedObjHandle)
{
    int oldTr = _trackedObjectHandle;
    if ((trackedObjHandle != _objectHandle) && (trackedObjHandle != _trackedObjectHandle))
    {
        if (App::currentWorld->sceneObjects->getObjectFromHandle(trackedObjHandle) != nullptr)
            _trackedObjectHandle = trackedObjHandle;
        else
            _trackedObjectHandle = -1;
    }
    if (oldTr != _trackedObjectHandle)
    {
        if (_isInScene && App::worldContainer->getEventsEnabled())
        {
            const char* cmd = propCamera_trackedObjectHandle.name;
            CCbor* ev = App::worldContainer->createSceneObjectChangedEvent(this, false, cmd, true);
            ev->appendKeyInt(cmd, _trackedObjectHandle);
            App::worldContainer->pushEvent();
        }
        handleCameraTracking();
#ifdef SIM_WITH_GUI
        GuiApp::setLightDialogRefreshFlag();
#endif
    }
}

void CCamera::removeSceneDependencies()
{
    CSceneObject::removeSceneDependencies();
    setTrackedObjectHandle(-1);
}

void CCamera::addSpecializedObjectEventData(CCbor* ev)
{
#if SIM_EVENT_PROTOCOL_VERSION == 2
    ev->openKeyMap(getObjectTypeInfo().c_str());
    ev->openKeyArray("colors");
    float c[9];
    _color.getColor(c, sim_colorcomponent_ambient_diffuse);
    _color.getColor(c + 3, sim_colorcomponent_specular);
    _color.getColor(c + 6, sim_colorcomponent_emission);
    ev->appendFloatArray(c, 9);
    _color_removeSoon.getColor(c, sim_colorcomponent_ambient_diffuse);
    _color_removeSoon.getColor(c + 3, sim_colorcomponent_specular);
    _color_removeSoon.getColor(c + 6, sim_colorcomponent_emission);
    ev->appendFloatArray(c, 9);
    ev->closeArrayOrMap(); // "colors"
    ev->appendKeyBool("perspectiveMode", _perspective);
    ev->appendKeyBool("allowTranslation", _allowTranslation);
    ev->appendKeyBool("allowRotation", _allowRotation);
    ev->appendKeyDouble("nearClippingPlane", _nearClippingPlane);
    ev->appendKeyDouble("farClippingPlane", _farClippingPlane);
    ev->appendKeyDouble("orthoSize", _orthoViewSize);
    ev->openKeyMap("frustumVectors");
    ev->appendKeyDoubleArray("near", _volumeVectorNear.data, 3);
    ev->appendKeyDoubleArray("far", _volumeVectorFar.data, 3);
    ev->closeArrayOrMap(); // "frustumVectors"
#else
    _color.addGenesisEventData(ev);
#endif
    ev->appendKeyDouble(propCamera_size.name, _cameraSize);
    ev->appendKeyBool(propCamera_parentAsManipProxy.name, _useParentObjectAsManipulationProxy);
    ev->appendKeyBool(propCamera_translationEnabled.name, _allowTranslation);
    ev->appendKeyBool(propCamera_rotationEnabled.name, _allowRotation);
    ev->appendKeyInt(propCamera_trackedObjectHandle.name, _trackedObjectHandle);
    CViewableBase::addSpecializedObjectEventData(ev);
#if SIM_EVENT_PROTOCOL_VERSION == 2
    ev->closeArrayOrMap(); //"camera"
#endif
}

CSceneObject* CCamera::copyYourself()
{
    CCamera* newCamera = (CCamera*)CSceneObject::copyYourself();

    // Various
    newCamera->_cameraSize = _cameraSize;
    newCamera->_renderMode = _renderMode;
    newCamera->_renderModeDuringSimulation = _renderModeDuringSimulation;
    newCamera->_renderModeDuringRecording = _renderModeDuringRecording;
    newCamera->_viewAngle = _viewAngle;
    newCamera->_viewModeSet_old = _viewModeSet_old;
    newCamera->_perspective = _perspective;
    newCamera->_orthoViewSize = _orthoViewSize;
    newCamera->_nearClippingPlane = _nearClippingPlane;
    newCamera->_farClippingPlane = _farClippingPlane;
    newCamera->_volumeVectorNear = _volumeVectorNear;
    newCamera->_volumeVectorFar = _volumeVectorFar;
    newCamera->_hideFog = _hideFog;
    newCamera->_trackedObjectHandle = _trackedObjectHandle;
    newCamera->_useParentObjectAsManipulationProxy = _useParentObjectAsManipulationProxy;
    newCamera->_allowTranslation = _allowTranslation;
    newCamera->_allowRotation = _allowRotation;
    newCamera->_useLocalLights = _useLocalLights;
    newCamera->_allowPicking = _allowPicking;
    newCamera->_showVolume = _showVolume;
    _color.copyYourselfInto(&newCamera->_color);

    return (newCamera);
}

void CCamera::announceObjectWillBeErased(const CSceneObject* object, bool copyBuffer)
{ // copyBuffer is false by default (if true, we are 'talking' to objects
    // in the copyBuffer)
    CSceneObject::announceObjectWillBeErased(object, copyBuffer);
    if (_trackedObjectHandle == object->getObjectHandle())
        setTrackedObjectHandle(-1);
}
void CCamera::announceCollectionWillBeErased(int groupID, bool copyBuffer)
{ // copyBuffer is false by default (if true, we are 'talking' to objects
    // in the copyBuffer)
    CSceneObject::announceCollectionWillBeErased(groupID, copyBuffer);
}
void CCamera::announceCollisionWillBeErased(int collisionID, bool copyBuffer)
{ // copyBuffer is false by default (if true, we are 'talking' to objects
    // in the copyBuffer)
    CSceneObject::announceCollisionWillBeErased(collisionID, copyBuffer);
}
void CCamera::announceDistanceWillBeErased(int distanceID, bool copyBuffer)
{ // copyBuffer is false by default (if true, we are 'talking' to objects
    // in the copyBuffer)
    CSceneObject::announceDistanceWillBeErased(distanceID, copyBuffer);
}
void CCamera::announceIkObjectWillBeErased(int ikGroupID, bool copyBuffer)
{ // copyBuffer is false by default (if true, we are 'talking' to objects
    // in the copyBuffer)
    CSceneObject::announceIkObjectWillBeErased(ikGroupID, copyBuffer);
}
void CCamera::performObjectLoadingMapping(const std::map<int, int>* map, int opType)
{
    CSceneObject::performObjectLoadingMapping(map, opType);
    _trackedObjectHandle = CWorld::getLoadingMapping(map, _trackedObjectHandle);
}
void CCamera::performCollectionLoadingMapping(const std::map<int, int>* map, int opType)
{
    CSceneObject::performCollectionLoadingMapping(map, opType);
}
void CCamera::performCollisionLoadingMapping(const std::map<int, int>* map, int opType)
{
    CSceneObject::performCollisionLoadingMapping(map, opType);
}
void CCamera::performDistanceLoadingMapping(const std::map<int, int>* map, int opType)
{
    CSceneObject::performDistanceLoadingMapping(map, opType);
}
void CCamera::performIkLoadingMapping(const std::map<int, int>* map, int opType)
{
    CSceneObject::performIkLoadingMapping(map, opType);
}

void CCamera::performTextureObjectLoadingMapping(const std::map<int, int>* map, int opType)
{
    CSceneObject::performTextureObjectLoadingMapping(map, opType);
}

void CCamera::performDynMaterialObjectLoadingMapping(const std::map<int, int>* map)
{
    CSceneObject::performDynMaterialObjectLoadingMapping(map);
}

int CCamera::getPerspectiveOperation_old() const
{ // normally, use get/setPerspective instead
    int retVal = -1;
    if (_viewModeSet_old)
    {
        if (_perspective)
            retVal = 1;
        else
            retVal = 0;
    }
    return (retVal);
}

int CCamera::getViewOrientation() const
{
    C3X3Matrix m(getFullCumulativeTransformation().Q);
    if (fabs(m.axis[2].getAngle(C3Vector(-1.0, 0.0, 0.0)) * radToDeg) < 0.1)
        return (POSITIVE_X_VIEW);
    if (fabs(m.axis[2].getAngle(C3Vector(+1.0, 0.0, 0.0)) * radToDeg) < 0.1)
        return (NEGATIVE_X_VIEW);
    if (fabs(m.axis[2].getAngle(C3Vector(0.0, -1.0, 0.0)) * radToDeg) < 0.1)
        return (POSITIVE_Y_VIEW);
    if (fabs(m.axis[2].getAngle(C3Vector(0.0, +1.0, 0.0)) * radToDeg) < 0.1)
        return (NEGATIVE_Y_VIEW);
    if (fabs(m.axis[2].getAngle(C3Vector(0.0, 0.0, -1.0)) * radToDeg) < 0.1)
        return (POSITIVE_Z_VIEW);
    if (fabs(m.axis[2].getAngle(C3Vector(0.0, 0.0, +1.0)) * radToDeg) < 0.1)
        return (NEGATIVE_Z_VIEW);
    return (NO_SPECIFIC_VIEW);
}
void CCamera::setViewOrientation(int ori, bool setPositionAlso)
{ // setPositionAlso is false by default
    double alpha, beta, gamma, x, y, z;
    bool done = false;
    if (ori == POSITIVE_X_VIEW)
    {
        alpha = 0.0;
        beta = -90.0;
        gamma = -90.0;
        x = +3.0;
        y = 0.0;
        z = 0.0;
        done = true;
    }
    if (ori == NEGATIVE_X_VIEW)
    {
        alpha = 0.0;
        beta = +90.0;
        gamma = +90.0;
        x = -3.0;
        y = 0.0;
        z = 0.0;
        done = true;
    }
    if (ori == POSITIVE_Y_VIEW)
    {
        alpha = +90.0;
        beta = 0.0;
        gamma = 0.0;
        x = 0.0;
        y = +3.0;
        z = 0.0;
        done = true;
    }
    if (ori == NEGATIVE_Y_VIEW)
    {
        alpha = -90.0;
        beta = 0.0;
        gamma = +180.0;
        x = 0.0;
        y = -3.0;
        z = 0.0;
        done = true;
    }
    if (ori == POSITIVE_Z_VIEW)
    {
        alpha = +180.0;
        beta = 0.0;
        gamma = 0.0;
        x = 0.0;
        y = 0.0;
        z = +3.0;
        done = true;
    }
    if (ori == NEGATIVE_Z_VIEW)
    {
        alpha = 0.0;
        beta = 0.0;
        gamma = +180.0;
        x = 0.0;
        y = 0.0;
        z = -3.0;
        done = true;
    }
    if (done)
    {
        C7Vector tot(getFullCumulativeTransformation());
        tot.Q.setEulerAngles(C3Vector(alpha * degToRad, beta * degToRad, gamma * degToRad));
        if (setPositionAlso)
            tot.X.setData(x, y, z);
        C7Vector parentInv(getFullParentCumulativeTransformation().getInverse());
        setLocalTransformation(parentInv * tot);
    }
}

void CCamera::setAllowPicking(bool a)
{
    _allowPicking = a;
}

bool CCamera::getAllowPicking() const
{
    return (_allowPicking);
}

void CCamera::initializeInitialValues(bool simulationAlreadyRunning)
{ // is called at simulation start, but also after object(s) have been copied into a scene!
    CSceneObject::initializeInitialValues(simulationAlreadyRunning);
    _initialViewAngle = _viewAngle;
    _initialOrthoViewSize = _orthoViewSize;
}

void CCamera::simulationAboutToStart()
{
    initializeInitialValues(false);
    CSceneObject::simulationAboutToStart();
}

void CCamera::simulationEnded()
{ // Remember, this is not guaranteed to be run! (the object can be copied during simulation, and pasted after it
    // ended). For thoses situations there is the initializeInitialValues routine!
    if (_initialValuesInitialized)
    {
        if ((getCumulativeModelProperty() & sim_modelproperty_not_reset) == 0)
        {
            setViewAngle(_initialViewAngle);
            setOrthoViewSize(_initialOrthoViewSize);
        }
    }
    CSceneObject::simulationEnded();
}

void CCamera::serialize(CSer& ar)
{
    CSceneObject::serialize(ar);
    if (ar.isBinary())
    {
        if (ar.isStoring())
        { // Storing
            int trck = -1;
            if (_trackedObjectHandle != -1)
                trck = _trackedObjectHandle;

            ar.storeDataName("_p4");
            ar << trck;
            ar << _cameraSize;
            ar.flush();

            double ovs = _orthoViewSize;
            ar.storeDataName("_p3");
            if (_ignorePosAndCameraOrthoviewSize_forUndoRedo)
                ovs = 1.0;
            ar << ovs << _viewAngle;
            ar.flush();

            ar.storeDataName("_cp");
            ar << _nearClippingPlane << _farClippingPlane;
            ar.flush();

            ar.storeDataName("Cmp"); // keep for backward compatibility (28.09.2022)
            int tmp = 0;
            if (_allowTranslation)
                tmp |= 7;
            if (_allowRotation)
                tmp |= 24;
            ar << tmp;
            ar.flush();

            ar.storeDataName("Rmd");
            ar << int(sim_rendermode_opengl); // for backward compatibility 28/06/2019
            ar.flush();

            ar.storeDataName("Rm2");
            ar << _renderMode;
            ar.flush();

            // reserved ar.storeDataName("Rcm");

            ar.storeDataName("Cpm"); // keep for backward compatibility (22.06.2023)
            int po = -1;
            if (_viewModeSet_old)
            {
                if (_perspective)
                    po = 1;
                else
                    po = 0;
            }
            ar << po;
            ar.flush();

            ar.storeDataName("Ca2");
            unsigned char nothing = 0;
            SIM_SET_CLEAR_BIT(nothing, 0, _useParentObjectAsManipulationProxy);
            SIM_SET_CLEAR_BIT(nothing, 1, _hideFog);
            SIM_SET_CLEAR_BIT(nothing, 2, _useLocalLights);
            SIM_SET_CLEAR_BIT(nothing, 3, !_allowPicking);
            // SIM_SET_CLEAR_BIT(nothing,4,!_perspective);
            SIM_SET_CLEAR_BIT(nothing, 5, _renderModeDuringSimulation);
            SIM_SET_CLEAR_BIT(nothing, 6, _renderModeDuringRecording);
            SIM_SET_CLEAR_BIT(nothing, 7, _showVolume);
            ar << nothing;
            ar.flush();

            ar.storeDataName("Ca3");
            nothing = 0;
            SIM_SET_CLEAR_BIT(nothing, 0, _viewModeSet_old);
            SIM_SET_CLEAR_BIT(nothing, 1, _perspective);
            ar << nothing;
            ar.flush();

            ar.storeDataName("Cl1");
            ar.setCountingMode();
            _color.serialize(ar, 0);
            if (ar.setWritingMode())
                _color.serialize(ar, 0);

            ar.storeDataName(SER_END_OF_OBJECT);
        }
        else
        { // Loading
            int byteQuantity;
            std::string theName = "";
            bool povFocalBlurEnabled_backwardCompatibility_3_2_2016 = false;
            _viewModeSet_old = false;
            while (theName.compare(SER_END_OF_OBJECT) != 0)
            {
                theName = ar.readDataName();
                if (theName.compare(SER_END_OF_OBJECT) != 0)
                {
                    bool noHit = true;
                    if (theName.compare("Cp4") == 0)
                    { // for backward comp. (flt->dbl)
                        noHit = false;
                        ar >> byteQuantity;
                        ar >> _trackedObjectHandle;
                        float bla;
                        ar >> bla;
                        _cameraSize = (double)bla;
                    }

                    if (theName.compare("_p4") == 0)
                    {
                        noHit = false;
                        ar >> byteQuantity;
                        ar >> _trackedObjectHandle;
                        ar >> _cameraSize;
                    }

                    if (theName.compare("Cp3") == 0)
                    { // for backward comp. (flt->dbl)
                        noHit = false;
                        ar >> byteQuantity;
                        float bla, bli;
                        ar >> bla >> bli;
                        _orthoViewSize = (double)bla;
                        _viewAngle = (double)bli;
                    }

                    if (theName.compare("_p3") == 0)
                    {
                        noHit = false;
                        ar >> byteQuantity;
                        ar >> _orthoViewSize >> _viewAngle;
                    }

                    if (theName.compare("Ccp") == 0)
                    { // for backward comp. (flt->dbl)
                        noHit = false;
                        ar >> byteQuantity;
                        float bla, bli;
                        ar >> bla >> bli;
                        _nearClippingPlane = (double)bla;
                        _farClippingPlane = (double)bli;
                    }

                    if (theName.compare("_cp") == 0)
                    {
                        noHit = false;
                        ar >> byteQuantity;
                        ar >> _nearClippingPlane >> _farClippingPlane;
                    }

                    if (theName == "Caz")
                    { // keep for backward compatibility (2010/07/13)
                        noHit = false;
                        ar >> byteQuantity;
                        unsigned char nothing;
                        ar >> nothing;
                        _useParentObjectAsManipulationProxy = SIM_IS_BIT_SET(nothing, 0);
                    }
                    if (theName.compare("Cpm") == 0)
                    { // keep for backward compatibility (22.06.2023)
                        noHit = false;
                        ar >> byteQuantity;
                        int po;
                        ar >> po;
                        _perspective = (po != 0);
                        _viewModeSet_old = (po >= 0);
                    }
                    if (theName == "Ca2")
                    {
                        noHit = false;
                        ar >> byteQuantity;
                        unsigned char nothing;
                        ar >> nothing;
                        _useParentObjectAsManipulationProxy = SIM_IS_BIT_SET(nothing, 0);
                        _hideFog = SIM_IS_BIT_SET(nothing, 1);
                        _useLocalLights = SIM_IS_BIT_SET(nothing, 2);
                        _allowPicking = !SIM_IS_BIT_SET(nothing, 3);
                        //_perspective=!SIM_IS_BIT_SET(nothing,4);
                        _renderModeDuringSimulation = SIM_IS_BIT_SET(nothing, 5);
                        _renderModeDuringRecording = SIM_IS_BIT_SET(nothing, 6);
                        _showVolume = SIM_IS_BIT_SET(nothing, 7);
                    }
                    if (theName.compare("Rm2") == 0)
                    {
                        noHit = false;
                        ar >> byteQuantity;
                        ar >> _renderMode;
                    }
                    if (theName == "Ca3")
                    {
                        noHit = false;
                        ar >> byteQuantity;
                        unsigned char nothing;
                        ar >> nothing;
                        _viewModeSet_old = SIM_IS_BIT_SET(nothing, 0);
                        _perspective = SIM_IS_BIT_SET(nothing, 1);
                    }
                    if (theName.compare("Rmd") == 0)
                    { // keep for backward compatibility 28/06/2019
                        noHit = false;
                        ar >> byteQuantity;
                        ar >> _renderMode;
                        if (_renderMode != 0)
                        {
                            if (_renderMode == 1)
                            {
                                _renderMode = sim_rendermode_povray;
                                _renderModeDuringSimulation = true;
                                _renderModeDuringRecording = true;
                            }
                            else if (_renderMode == 2)
                            {
                                _renderMode = sim_rendermode_povray;
                                _renderModeDuringSimulation = true;
                                _renderModeDuringRecording = false;
                            }
                            else if (_renderMode == 5)
                                _renderMode = sim_rendermode_extrenderer;
                            else
                                _renderMode = sim_rendermode_opengl;
                        }
                    }
                    if (theName.compare("Pv1") == 0)
                    { // Keep for backward compatibility (3/2/2016)
                        noHit = false;
                        ar >> byteQuantity;
                        float povFocalDistance, povAperture;
                        int povBlurSamples;
                        ar >> povFocalDistance >> povAperture;
                        ar >> povBlurSamples;
                        _extensionString = "povray {focalBlur {";
                        if (povFocalBlurEnabled_backwardCompatibility_3_2_2016)
                            _extensionString += "true} focalDist {";
                        else
                            _extensionString += "false} focalDist {";
                        _extensionString += utils::getSizeString(false, (double)povFocalDistance);
                        _extensionString += "} aperture {";
                        _extensionString += utils::getSizeString(false, (double)povAperture);
                        _extensionString += "} blurSamples {";
                        _extensionString += utils::getIntString(false, povBlurSamples);
                        _extensionString += "}}";
                    }
                    if (theName.compare("Cl1") == 0)
                    {
                        noHit = false;
                        ar >> byteQuantity;
                        _color.serialize(ar, 0);
                    }
                    if (theName.compare("Cmp") == 0)
                    { // for backward compatibility (29.09.2022)
                        noHit = false;
                        ar >> byteQuantity;
                        int tmp;
                        ar >> tmp;
                        _allowTranslation = ((tmp & 0x07) != 0);
                        _allowRotation = ((tmp & 0x08) != 0);
                    }
                    if (noHit)
                        ar.loadUnknownData();
                }
            }

            if (ar.getCoppeliaSimVersionThatWroteThisFile() < 20509)
            { // For backward compatibility (27/7/2011)
                if ((_objectName_old.compare("DefaultXViewCamera") == 0) ||
                    (_objectName_old.compare("DefaultYViewCamera") == 0) ||
                    (_objectName_old.compare("DefaultZViewCamera") == 0))
                    _hideFog = true;
            }

            if (ar.getSerializationVersionThatWroteThisFile() < 17)
                utils::scaleColorUp_(_color.getColorsPtr());
            computeBoundingBox();
            computeVolumeVectors();
        }
    }
    else
    {
        bool exhaustiveXml = ((ar.getFileType() != CSer::filetype_csim_xml_simplescene_file) &&
                              (ar.getFileType() != CSer::filetype_csim_xml_simplemodel_file));
        if (ar.isStoring())
        {
            if (!exhaustiveXml)
            {
                int h = App::currentWorld->pageContainer->getMainCameraHandle();
                ar.xmlAddNode_bool("mainCamera", h == _objectHandle);
            }
            int trck = -1;
            if (_trackedObjectHandle != -1)
                trck = _trackedObjectHandle;
            if (exhaustiveXml)
                ar.xmlAddNode_int("trackedObjectHandle", trck);
            else
            {
                std::string str;
                CSceneObject* it = App::currentWorld->sceneObjects->getObjectFromHandle(trck);
                if (it != nullptr)
                    str = it->getObjectName_old();
                ar.xmlAddNode_comment(
                    " 'trackedObject' tag only provided for backward compatibility, use instead 'trackedObjectAlias' tag",
                    exhaustiveXml);
                ar.xmlAddNode_string("trackedObject", str.c_str());
                if (it != nullptr)
                {
                    str = it->getObjectAlias() + "*";
                    str += std::to_string(it->getObjectHandle());
                }
                ar.xmlAddNode_string("trackedObjectAlias", str.c_str());
            }

            ar.xmlAddNode_float("size", _cameraSize);

            ar.xmlAddNode_float("orthoViewSize", _orthoViewSize);

            ar.xmlAddNode_float("viewAngle", _viewAngle * 180.0 / piValue);

            ar.xmlAddNode_2float("clippingPlanes", _nearClippingPlane, _farClippingPlane);

            if (exhaustiveXml)
                ar.xmlAddNode_int("renderMode", _renderMode);

            ar.xmlPushNewNode("switches");
            if (exhaustiveXml)
                ar.xmlAddNode_bool("allowTranslation", _allowTranslation);
            if (exhaustiveXml)
                ar.xmlAddNode_bool("allowRotation", _allowRotation);
            if (exhaustiveXml)
                ar.xmlAddNode_bool("useParentAsManipulationProxy", _useParentObjectAsManipulationProxy);
            if (exhaustiveXml)
                ar.xmlAddNode_bool("useLocalLights", _useLocalLights);
            if (exhaustiveXml)
                ar.xmlAddNode_bool("allowPicking", _allowPicking);
            if (exhaustiveXml)
                ar.xmlAddNode_bool("showVolume", _showVolume);
            if (exhaustiveXml)
                ar.xmlAddNode_bool("renderModeOnlyDuringSimulation", _renderModeDuringSimulation);
            if (exhaustiveXml)
                ar.xmlAddNode_bool("renderModeOnlyDuringRecording", _renderModeDuringRecording);
            ar.xmlAddNode_bool("perspectiveMode", _perspective);
            ar.xmlPopNode();

            if (exhaustiveXml)
            {
                ar.xmlPushNewNode("objectColor");
                _color.serialize(ar, 0);
                ar.xmlPopNode();
            }
            else
            {
                int rgb[3];
                for (size_t l = 0; l < 3; l++)
                    rgb[l] = int(_color.getColorsPtr()[l] * 255.1);
                ar.xmlAddNode_ints("objectColor", rgb, 3);
            }
        }
        else
        {
            if (!exhaustiveXml)
                ar.xmlGetNode_bool("mainCamera", _isMainCamera, exhaustiveXml);

            if (exhaustiveXml)
                ar.xmlGetNode_int("trackedObjectHandle", _trackedObjectHandle);
            else
            {
                ar.xmlGetNode_string("trackedObjectAlias", _trackedObjectLoadAlias, exhaustiveXml);
                ar.xmlGetNode_string("trackedObject", _trackedObjectLoadName_old, exhaustiveXml);
            }

            ar.xmlGetNode_float("size", _cameraSize, exhaustiveXml);

            ar.xmlGetNode_float("orthoViewSize", _orthoViewSize, exhaustiveXml);

            if (ar.xmlGetNode_float("viewAngle", _viewAngle, exhaustiveXml))
                _viewAngle *= piValue / 180.0;

            ar.xmlGetNode_2float("clippingPlanes", _nearClippingPlane, _farClippingPlane, exhaustiveXml);

            if (exhaustiveXml)
                ar.xmlGetNode_int("renderMode", _renderMode);

            if (ar.xmlPushChildNode("switches", exhaustiveXml))
            {
                ar.xmlGetNode_bool("perspectiveMode", _perspective, false);
                ar.xmlGetNode_bool("allowTranslation", _allowTranslation, exhaustiveXml);
                ar.xmlGetNode_bool("allowRotation", _allowRotation, exhaustiveXml);
                ar.xmlGetNode_bool("useParentAsManipulationProxy", _useParentObjectAsManipulationProxy, exhaustiveXml);
                ar.xmlGetNode_bool("useLocalLights", _useLocalLights, exhaustiveXml);
                ar.xmlGetNode_bool("allowPicking", _allowPicking, exhaustiveXml);
                ar.xmlGetNode_bool("showVolume", _showVolume, false);
                ar.xmlGetNode_bool("renderModeOnlyDuringSimulation", _renderModeDuringSimulation, exhaustiveXml);
                ar.xmlGetNode_bool("renderModeOnlyDuringRecording", _renderModeDuringRecording, exhaustiveXml);
                ar.xmlPopNode();
            }

            if (exhaustiveXml)
            {
                if (ar.xmlPushChildNode("objectColor", false))
                {
                    _color.serialize(ar, 0);
                    ar.xmlPopNode();
                }
            }
            else
            {
                int rgb[3];
                if (ar.xmlGetNode_ints("objectColor", rgb, 3, false))
                    _color.setColor(float(rgb[0]) / 255.1, float(rgb[1]) / 255.1, float(rgb[2]) / 255.1,
                                    sim_colorcomponent_ambient_diffuse);
            }

            if (ar.xmlPushChildNode("color", false))
            { // for backward compatibility
                if (exhaustiveXml)
                {
                    if (ar.xmlPushChildNode("part1"))
                    {
                        _color.serialize(ar, 0);
                        ar.xmlPopNode();
                    }
                    if (ar.xmlPushChildNode("part2"))
                    {
                        _color_removeSoon.serialize(ar, 0);
                        ar.xmlPopNode();
                    }
                }
                else
                {
                    int rgb[3];
                    if (ar.xmlGetNode_ints("part1", rgb, 3, exhaustiveXml))
                        _color.setColor(float(rgb[0]) / 255.1, float(rgb[1]) / 255.1, float(rgb[2]) / 255.1,
                                        sim_colorcomponent_ambient_diffuse);
                    if (ar.xmlGetNode_ints("part2", rgb, 3, exhaustiveXml))
                        _color_removeSoon.setColor(float(rgb[0]) / 255.1, float(rgb[1]) / 255.1, float(rgb[2]) / 255.1,
                                                   sim_colorcomponent_ambient_diffuse);
                }
                ar.xmlPopNode();
            }
            computeBoundingBox();
            computeVolumeVectors();
        }
    }
}

#ifdef SIM_WITH_GUI
void CCamera::display(CViewableBase* renderingObject, int displayAttrib)
{
    displayCamera(this, renderingObject, displayAttrib);
}

void CCamera::lookIn(int windowSize[2], CSView* subView, bool drawText, bool passiveSubView)
{ // drawText is false and passiveSubView is true by default
    TRACE_INTERNAL;
    // Default values (used for instance in view selection mode)

    // This routine is quite messy and needs refactoring!!!
    bool isPerspective = true;
    int renderingMode = RENDERING_MODE_SOLID;
    bool displ_ref = false;
    int currentWinSize[2];
    int mouseRelativePosition[2];
    int mouseDownRelativePosition[2];
    int selectionStatus = NOSELECTION;
    bool mouseIsDown = false;
    bool mouseJustWentDown = false;
    bool mouseJustWentUp = false;
    bool mouseMovedWhileDown = false;
    int navigationMode = sim_navigation_passive;
    if (windowSize != nullptr)
    {
        currentWinSize[0] = windowSize[0];
        currentWinSize[1] = windowSize[1];
    }
    if (subView != nullptr)
    {
        isPerspective = subView->getPerspectiveDisplay();
        if (!_viewModeSet_old)
        {
            setPerspective(isPerspective);
            _viewModeSet_old = true;
        }
        isPerspective = _perspective;
        renderingMode = subView->getRenderingMode();
        displ_ref = true;
        subView->getViewSize(currentWinSize);

        subView->getMouseRelativePosition(mouseRelativePosition);
        subView->getMouseDownRelativePosition(mouseDownRelativePosition);
        if (!passiveSubView)
        {
            selectionStatus = subView->getSelectionStatus();
            mouseIsDown = subView->isMouseDown();
            mouseJustWentDown = subView->didMouseJustGoDown();
            mouseJustWentUp = subView->didMouseJustGoUp();
            mouseMovedWhileDown = subView->didMouseMoveWhileDown();
            navigationMode = GuiApp::getMouseMode() & 0x00ff;
        }
    }

    // Set data for view frustum culling
    _planesCalculated = false;
    _currentViewSize[0] = currentWinSize[0];
    _currentViewSize[1] = currentWinSize[1];
    _currentPerspective = isPerspective;

    // There is a maximum of 3 passes:
    // Pass 0 : DEPTHPASS : Pass used when doing depth perception
    //          Everything should be drawn as
    //          glPolygonMode (GL_FRONT_AND_BACK,GL_FILL)
    //          This pass is never displayed and can be skipped
    // Pass 1 : PICKPASS : Pass used for picking
    //          This pass might be displayed and can be skipped
    // Pass 2 : RENDERPASS : Pass which is always displayed and cannot be skipped

    int passes[3] = {RENDERPASS, -1, -1}; // last should always be rendering pass!

    bool specialSelectionAndNavigationPass = false;
    bool regularObjectsCannotBeSelected = false;
    bool processHitForMouseUpProcessing = false;
    if (subView != nullptr)
    {
        if (hitForMouseUpProcessing_minus2MeansIgnore != -2)
        {
            int mousePos[2];
            int mouseDownPos[2];
            subView->getMouseRelativePosition(mousePos);
            subView->getMouseDownRelativePosition(mouseDownPos);
            int dx[2] = {mouseDownPos[0] - mousePos[0], mouseDownPos[1] - mousePos[1]};
            if (dx[0] * dx[0] + dx[1] * dx[1] > 1)
                hitForMouseUpProcessing_minus2MeansIgnore = -2;
        }
        if (mouseJustWentDown)
        {
            hitForMouseUpProcessing_minus2MeansIgnore = -2;
            if (mouseJustWentUp)
            {
                processHitForMouseUpProcessing = true;
                if (selectionStatus == NOSELECTION)
                {
                    passes[0] = PICKPASS;
                    passes[1] = RENDERPASS;
                    mouseIsDown = false;
                }
                else
                {
                    passes[0] = PICKPASS;
                    passes[1] = RENDERPASS;
                }
            }
            else
            {
                if (selectionStatus == NOSELECTION)
                { // no ctrl or shift key
                    passes[0] = DEPTHPASS;
                    passes[1] = RENDERPASS;
                    // Until 3.2.1:
                    //                  passes[0]=DEPTHPASS;
                    //                  passes[1]=PICKPASS;
                    //                  passes[2]=RENDERPASS;
                    if ((GuiApp::getMouseMode() & sim_navigation_clickselection) == 0)
                        regularObjectsCannotBeSelected = true;
                    else
                        specialSelectionAndNavigationPass = true;
                }
                else if (selectionStatus == SHIFTSELECTION)
                { // shift key
                    //                  pass=RENDERPASS;
                    //                  numberOfPasses=1;
                }
                else
                { // ctrl key
                    passes[0] = PICKPASS;
                    passes[1] = RENDERPASS;
                }
            }
        }
        else if (mouseJustWentUp)
        {
            processHitForMouseUpProcessing = true;
            if (selectionStatus == SHIFTSELECTION)
            {
                if (((GuiApp::getEditModeType() & SHAPE_EDIT_MODE) != 0) && (GuiApp::mainWindow->getKeyDownState() & 1))
                    passes[0] = COLORCODEDPICKPASS;
                else
                    passes[0] = PICKPASS;
                passes[1] = RENDERPASS;
            }
            else
            {
                // New since 3.2.2:
                if (GuiApp::mainWindow->getMouseButtonState() & 16)
                { // last mouse down was left and no ctrl key was pressed
                    int mousePos[2];
                    int mouseDownPos[2];
                    subView->getMouseRelativePosition(mousePos);
                    subView->getMouseDownRelativePosition(mouseDownPos);
                    if ((abs(mousePos[0] - mouseDownPos[0]) < 2) && (abs(mousePos[1] - mouseDownPos[1]) < 2))
                    {
                        passes[0] = PICKPASS;
                        passes[1] = RENDERPASS;
                    }
                }
            }
        }
    }

    //  App::currentWorld->objCont->setUniqueSelectedPathID(-1);

    if (getInternalRendering())
    { // regular rendering
        for (int passIndex = 0; passIndex < 3; passIndex++)
        {
            // Keep following 2, it seems on Mac we otherwise always have a problem. Even if it seems that the depth
            // test is always restored after disabling it...
            glEnable(GL_DEPTH_TEST);
            glDepthMask(GL_TRUE);

            int pass = passes[passIndex];
            if (pass == -1)
                break;
            if (pass == RENDERPASS)
                App::currentWorld->environment->setBackgroundColor(currentWinSize);
            else
            {
                glClearColor(0.0, 0.0, 0.0, 0.0);
                glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
            }

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();

            if (pass == PICKPASS)
            {
                if (!_allowPicking)
                    break;
                GLint viewport[4];
                glSelectBuffer(SELECTION_BUFFER_SIZE * 4 - 4, selectBuff); //+4 is for...? Sometime
                // the application badly crashes during picking, and I guess it might be because
                // openGL is accessing forbidden memory... But I don't know!!

                glGetIntegerv(GL_VIEWPORT, viewport);
                glRenderMode(GL_SELECT);
                glInitNames();
                glPushName(0);
                int mouseX = mouseRelativePosition[0];
                int mouseY = mouseRelativePosition[1];
                tt::limitValue(1, currentWinSize[0], mouseX);
                tt::limitValue(1, currentWinSize[1], mouseY);
                int pickSizeX = abs(mouseX - mouseDownRelativePosition[0]);
                int pickSizeY = abs(mouseY - mouseDownRelativePosition[1]);
                tt::limitValue(1, 10000, pickSizeX);
                tt::limitValue(1, 10000, pickSizeY);
                int centerX = (mouseX + mouseDownRelativePosition[0]) / 2;
                int centerY = (mouseY + mouseDownRelativePosition[1]) / 2;
                if (selectionStatus == SHIFTSELECTION)
                    ogl::pickMatrixSpecial(centerX + viewport[0], centerY + viewport[1], pickSizeX, pickSizeY,
                                           viewport);
                else
                    ogl::pickMatrixSpecial(mouseX + viewport[0], mouseY + viewport[1], 3, 3, viewport);
            }

            if (pass != PICKPASS)
                glRenderMode(GL_RENDER);

            double ratio = (double)(currentWinSize[0] / (double)currentWinSize[1]);
            if (isPerspective)
            {
                if (ratio > 1.0)
                {
                    double a = 2.0 * atan(tan(_viewAngle / 2.0) / ratio) * radToDeg;
                    ogl::perspectiveSpecial(a, ratio, _nearClippingPlane, _farClippingPlane);
                }
                else
                    ogl::perspectiveSpecial(_viewAngle * radToDeg, ratio, _nearClippingPlane, _farClippingPlane);
            }
            else
            {
                if (ratio > 1.0)
                    glOrtho(-_orthoViewSize * 0.5, _orthoViewSize * 0.5, -_orthoViewSize * 0.5 / ratio,
                            _orthoViewSize * 0.5 / ratio, ORTHO_CAMERA_NEAR_CLIPPING_PLANE,
                            ORTHO_CAMERA_FAR_CLIPPING_PLANE);
                else
                    glOrtho(-_orthoViewSize * 0.5 * ratio, _orthoViewSize * 0.5 * ratio, -_orthoViewSize * 0.5,
                            _orthoViewSize * 0.5, ORTHO_CAMERA_NEAR_CLIPPING_PLANE, ORTHO_CAMERA_FAR_CLIPPING_PLANE);
            }
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            C4X4Matrix m4(getFullCumulativeTransformation().getMatrix());

            if (GuiApp::mainWindow->getHasStereo())
            { // handle stereo cameras correctly
                C4X4Matrix displ;
                displ.setIdentity();
                if (GuiApp::mainWindow->getLeftEye())
                    displ.X(0) = GuiApp::mainWindow->getStereoDistance() / 2;
                else
                    displ.X(0) = -GuiApp::mainWindow->getStereoDistance() / 2;
                m4 = m4 * displ;
            }

            // The following 6 instructions have the same effect as gluLookAt()
            m4.inverse();
            m4.rotateAroundY(piValue);
            CMatrix m4_(m4);
            m4_.transpose();
            glLoadMatrixd(m4_.data.data());

            if (pass == RENDERPASS)
            {
                App::currentWorld->environment->activateAmbientLight(true);
                App::currentWorld->environment->activateFogIfEnabled(
                    this, App::currentWorld->simulation->getDynamicContentVisualizationOnly());
                _activateNonAmbientLights(-1, this);
            }
            else
            { // Without lights is faster
                App::currentWorld->environment->activateAmbientLight(false);
                App::currentWorld->environment->deactivateFog();
                _activateNonAmbientLights(-2, nullptr);
            }

            if ((pass == DEPTHPASS) || (pass == RENDERPASS))
            {
                _handleMirrors(renderingMode, selectionStatus == NOSELECTION, pass, navigationMode, currentWinSize,
                               subView);
            }

            bool manipOverlayNeeded = false;
            if (mouseIsDown && (!passiveSubView) && (pass == RENDERPASS) && (selectionStatus == NOSELECTION) &&
                ((navigationMode == sim_navigation_camerarotate) || (navigationMode == sim_navigation_camerashift) ||
                 (navigationMode == sim_navigation_objectshift) || (navigationMode == sim_navigation_objectrotate)))
            {
                double centerPos[3];
                subView->getCenterPosition(centerPos);
                double mousePosDepth = subView->getMousePositionDepth();
                glLoadName(-1);
                ogl::setMaterialColor(ogl::colorBlack, ogl::colorBlack, ogl::colorBlack);
                if ((navigationMode == sim_navigation_camerarotate) || (navigationMode == sim_navigation_camerashift))
                {
                    ogl::setMaterialColor(sim_colorcomponent_emission, ogl::colorRed);
                    glPushMatrix();
                    glTranslated(centerPos[0], centerPos[1], centerPos[2]);
                    double sphereRadius = 10.0;
                    if (isPerspective)
                    {
                        if (ratio > 1.0)
                            sphereRadius = mousePosDepth * tan(_viewAngle * 0.5) * sphereRadius / currentWinSize[0];
                        else
                            sphereRadius = mousePosDepth * tan(_viewAngle * 0.5) * sphereRadius / currentWinSize[1];
                    }
                    else
                    {
                        if (ratio > 1.0)
                            sphereRadius = _orthoViewSize * 0.f * sphereRadius / currentWinSize[0];
                        else
                            sphereRadius = _orthoViewSize * 0.5 * sphereRadius / currentWinSize[1];
                    }
                    App::currentWorld->environment->temporarilyDeactivateFog();

                    ogl::drawSphere(sphereRadius, 10, 5, true);
                    glPopMatrix();

                    // Following is a bit dirty, but quick ;)
                    double clippNear = _nearClippingPlane;
                    if (!isPerspective)
                        clippNear = ORTHO_CAMERA_NEAR_CLIPPING_PLANE;
                    if (mousePosDepth == clippNear)
                    { // We should display a differentiated thing here (kind of half-error!)
                        C7Vector cct(getCumulativeTransformation());
                        C7Vector icct(cct.getInverse());
                        C3Vector c(centerPos);
                        C3Vector rc(icct * c);
                        double di = 2.0;
                        for (int jk = 0; jk < 2; jk++)
                        {
                            for (double i0 = -di; i0 < 2.2 * di; i0 += 2.0 * di)
                            {
                                for (double j0 = -di; j0 < 2.2 * di; j0 += 2.0 * di)
                                {
                                    c = rc + C3Vector(i0 * sphereRadius, j0 * sphereRadius, 0.0);
                                    c = cct * c;
                                    glPushMatrix();
                                    glTranslated(c(0), c(1), c(2));
                                    ogl::drawSphere(sphereRadius, 10, 5, true);
                                    glPopMatrix();
                                }
                            }
                            di *= 2.0;
                        }
                    }
                    else
                    { // we display some neat wireframe!
                    }
                    App::currentWorld->environment->reactivateFogThatWasTemporarilyDisabled();
                }
                else
                    manipOverlayNeeded = true;
            }

            // rendering:
            _drawObjects(renderingMode, pass, currentWinSize, subView, false);

            if (manipOverlayNeeded)
            {
                double val = _orthoViewSize;
                if (_currentPerspective)
                    val = 2.0 * tan(_viewAngle * 0.5);
                for (size_t i = 0; i < App::currentWorld->sceneObjects->getObjectCount(); i++)
                {
                    CSceneObject* it = App::currentWorld->sceneObjects->getObjectFromIndex(i);
                    it->displayManipulationModeOverlayGrid(this, val, _currentPerspective);
                }
            }

            if (pass == DEPTHPASS)
                performDepthPerception(subView, isPerspective);
            if (pass == PICKPASS)
                hitForMouseUpProcessing_minus2MeansIgnore = handleHits(glRenderMode(GL_RENDER), selectBuff);

            if (pass == COLORCODEDPICKPASS)
            {
                GLint viewport[4];
                glGetIntegerv(GL_VIEWPORT, viewport);

                int mouseX = mouseRelativePosition[0];
                int mouseY = mouseRelativePosition[1];
                tt::limitValue(1, currentWinSize[0], mouseX);
                tt::limitValue(1, currentWinSize[1], mouseY);
                int pickSizeX = abs(mouseX - mouseDownRelativePosition[0]);
                int pickSizeY = abs(mouseY - mouseDownRelativePosition[1]);
                tt::limitValue(1, 10000, pickSizeX);
                tt::limitValue(1, 10000, pickSizeY);
                unsigned char* bf = new unsigned char[pickSizeX * pickSizeY * 3];
                glPixelStorei(GL_PACK_ALIGNMENT, 1);
                glReadPixels(std::min<int>(mouseX, mouseDownRelativePosition[0]) + viewport[0],
                             std::min<int>(mouseY, mouseDownRelativePosition[1]) + viewport[1], pickSizeX, pickSizeY,
                             GL_RGB, GL_UNSIGNED_BYTE, bf);
                glPixelStorei(GL_PACK_ALIGNMENT, 4); // important to restore! Really?
                std::vector<bool> sel;
                sel.resize(1000000, false);
                for (int i = 0; i < pickSizeX * pickSizeY; i++)
                {
                    unsigned int v = bf[3 * i + 0] + (bf[3 * i + 1] << 8) + (bf[3 * i + 2] << 16);
                    if (v < 1000000)
                        sel[v] = true;
                }

                for (int i = 1; i < 1000000; i++)
                {
                    if (sel[i])
                        GuiApp::mainWindow->editModeContainer->addItemToEditModeBuffer(i - 1, true);
                }

                delete[] bf;
            }

            if (processHitForMouseUpProcessing)
            {
                if (((GuiApp::getMouseMode() & 0x0300) & sim_navigation_clickselection) &&
                    ((GuiApp::mainWindow->getKeyDownState() & 3) == 0) &&
                    (hitForMouseUpProcessing_minus2MeansIgnore != -2))
                    handleMouseUpHit(hitForMouseUpProcessing_minus2MeansIgnore);
                hitForMouseUpProcessing_minus2MeansIgnore = -2;
                processHitForMouseUpProcessing = false;
            }

            glRenderMode(GL_RENDER);
            pass++;
        }
    }

    App::currentWorld->environment->deactivateFog();

    // Following is used to generate an externally rendered view:
    if (!getInternalRendering())
    {
        char* buff = new char[_currentViewSize[0] * _currentViewSize[1] * 3];
        int rendererIndex = _renderMode - sim_rendermode_povray;

        bool renderView = true;
        if (GuiApp::mainWindow->simulationRecorder->getIsRecording() && (rendererIndex < 2))
            renderView = GuiApp::mainWindow->simulationRecorder->willNextFrameBeRecorded();

        if (renderView)
        { // When using a ray-tracer during video recording, and we want to record not every frame, don't render those
            // frames!!
            GuiApp::mainWindow->openglWidget->doneCurrent();

#ifdef SIM_WITH_GUI
            _extRenderer_prepareView(rendererIndex, _currentViewSize, isPerspective);
#endif
            _extRenderer_prepareLights();

            if ((_renderMode == sim_rendermode_povray) || (_renderMode == sim_rendermode_opengl3))
                setFrustumCullingTemporarilyDisabled(true); // important with ray-tracers and similar

            // Draw objects:
            _drawObjects(RENDERING_MODE_SOLID, RENDERPASS, currentWinSize, subView, false);

            if ((_renderMode == sim_rendermode_povray) || (_renderMode == sim_rendermode_opengl3))
                setFrustumCullingTemporarilyDisabled(false); // important with ray-tracers and similar

            _extRenderer_retrieveImage(buff);

            GuiApp::mainWindow->openglWidget->makeCurrent();
        }

        // we want to apply a new image!
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, _currentViewSize[0], 0, _currentViewSize[1], -100, 100);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glDisable(GL_DEPTH_TEST);
        ogl::setMaterialColor(sim_colorcomponent_emission, ogl::colorWhite);
        if (_textureNameForExtGeneratedView == (unsigned int)-1)
            _textureNameForExtGeneratedView = ogl::genTexture(); // glGenTextures(1,&_textureNameForExtGeneratedView);
        glBindTexture(GL_TEXTURE_2D, _textureNameForExtGeneratedView);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _currentViewSize[0], _currentViewSize[1], 0, GL_RGB, GL_UNSIGNED_BYTE,
                     buff);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 4); // important to restore! Really?

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // keep to GL_LINEAR here!!
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, _textureNameForExtGeneratedView);

        glColor3f(1.0, 1.0, 1.0);

        glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0);
        glVertex3i(0, 0, 0);
        glTexCoord2f(0.0, 1.0);
        glVertex3i(0, _currentViewSize[1], 0);
        glTexCoord2f(1.0, 1.0);
        glVertex3i(_currentViewSize[0], _currentViewSize[1], 0);
        glTexCoord2f(1.0, 0.0);
        glVertex3i(_currentViewSize[0], 0, 0);
        glEnd();

        glDisable(GL_TEXTURE_2D);
        glEnable(GL_DEPTH_TEST);
        delete[] buff;
    }

    _drawOverlay(passiveSubView, drawText, displ_ref, currentWinSize, subView);
}

void CCamera::_handleMirrors(int renderingMode, bool noSelection, int pass, int navigationMode, int currentWinSize[2],
                             CSView* subView)
{
    if (App::currentWorld->sceneObjects->getObjectCount(sim_sceneobject_mirror) == 0)
        return;

    C7Vector camTr(getFullCumulativeTransformation());
    C7Vector camTri(camTr.getInverse());
    setFrustumCullingTemporarilyDisabled(true);
    // Prep stencil buffer:
    glEnable(GL_STENCIL_TEST);
    glClearStencil(0);
    glClear(GL_STENCIL_BUFFER_BIT);
    int drawOk = 1;

    std::vector<int> allMirrors;
    std::vector<double> allMirrorDist;
    for (size_t mir = 0; mir < App::currentWorld->sceneObjects->getObjectCount(sim_sceneobject_mirror); mir++)
    {
        CMirror* myMirror = App::currentWorld->sceneObjects->getMirrorFromIndex(mir);
        C7Vector mmtr(myMirror->getFullCumulativeTransformation());
        mmtr = camTri * mmtr;

        if ((!myMirror->isObjectPartOfInvisibleModel()) &&
            (App::currentWorld->environment->getActiveLayers() & myMirror->getVisibilityLayer()) &&
            myMirror->getIsMirror())
        {
            allMirrors.push_back(myMirror->getObjectHandle());
            allMirrorDist.push_back(mmtr.X(2));
        }
    }
    tt::orderAscending(allMirrorDist, allMirrors);

    for (int mir = 0; mir < int(allMirrors.size()); mir++)
    {
        CMirror* myMirror = App::currentWorld->sceneObjects->getMirrorFromHandle(allMirrors[mir]);

        C7Vector mtr(myMirror->getFullCumulativeTransformation());
        C7Vector mtri(mtr.getInverse());
        C3Vector mtrN(mtr.Q.getMatrix().axis[2]);
        C4Vector mtrAxis = mtr.Q.getAngleAndAxis();
        C4Vector mtriAxis = mtri.Q.getAngleAndAxis();
        double d = (mtrN * mtr.X);
        C3Vector v0(+myMirror->getMirrorWidth() * 0.5, -myMirror->getMirrorHeight() * 0.5, 0.0);
        C3Vector v1(+myMirror->getMirrorWidth() * 0.5, +myMirror->getMirrorHeight() * 0.5, 0.0);
        C3Vector v2(-myMirror->getMirrorWidth() * 0.5, +myMirror->getMirrorHeight() * 0.5, 0.0);
        C3Vector v3(-myMirror->getMirrorWidth() * 0.5, -myMirror->getMirrorHeight() * 0.5, 0.0);
        v0 *= mtr;
        v1 *= mtr;
        v2 *= mtr;
        v3 *= mtr;

        C3Vector MirrCam(camTr.X - mtr.X);
        bool inFrontOfMirror =
            (((MirrCam * mtrN) > 0.0) && myMirror->getActive() && (!App::currentWorld->mainSettings_old->mirrorsDisabled));

        glStencilFunc(GL_ALWAYS, drawOk, drawOk);  // we can draw everywhere
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE); // we draw drawOk where depth test passes
        glDepthMask(GL_FALSE);
        glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
        glBegin(GL_QUADS);
        glVertex3dv(v0.data);
        glVertex3dv(v1.data);
        glVertex3dv(v2.data);
        glVertex3dv(v3.data);
        glEnd();
        glDepthMask(GL_TRUE);
        glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

        // Enable stencil masking:
        glStencilFunc(GL_EQUAL, drawOk, drawOk); // we draw only where stencil is drawOk
        glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

        // Draw the mirror view:
        if (inFrontOfMirror)
        {
            glEnable(GL_CLIP_PLANE0);
            double cpv[4] = {-mtrN(0), -mtrN(1), -mtrN(2), d};
            glClipPlane(GL_CLIP_PLANE0, cpv);
            glPushMatrix();
            glTranslated(mtr.X(0), mtr.X(1), mtr.X(2));
            glRotated(mtrAxis(0) * radToDeg, mtrAxis(1), mtrAxis(2), mtrAxis(3));
            glScalef(1., 1., -1.);
            glTranslated(mtri.X(0), mtri.X(1), mtri.X(2));
            glRotated(mtriAxis(0) * radToDeg, mtriAxis(1), mtriAxis(2), mtriAxis(3));
            glFrontFace(GL_CW);
            CMirror::currentMirrorContentBeingRendered = myMirror->getObjectHandle();
            _drawObjects(renderingMode, pass, currentWinSize, subView, true);
            CMirror::currentMirrorContentBeingRendered = -1;
            glFrontFace(GL_CCW);
            glPopMatrix();
            glDisable(GL_CLIP_PLANE0);
        }

        // Now draw the mirror overlay:
        glPushAttrib(0xffffffff);
        glDepthFunc(GL_ALWAYS);
        ogl::disableLighting_useWithCare(); // only temporarily
        if (inFrontOfMirror)
        {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glColor4d(myMirror->mirrorColor[0], myMirror->mirrorColor[1], myMirror->mirrorColor[2],
                      1.0 - myMirror->getReflectance());
        }
        else
        {
            glColor4d(myMirror->mirrorColor[0], myMirror->mirrorColor[1], myMirror->mirrorColor[2], 1.0);
        }
        glBegin(GL_QUADS);
        glVertex3dv(v0.data);
        glVertex3dv(v1.data);
        glVertex3dv(v2.data);
        glVertex3dv(v3.data);
        glEnd();
        ogl::enableLighting_useWithCare();
        glPopAttrib();
        glDepthFunc(GL_LEQUAL);
        drawOk++;
    }
    glDisable(GL_STENCIL_TEST);

    setFrustumCullingTemporarilyDisabled(false);
}

bool CCamera::_extRenderer_prepareView(int extRendererIndex, int resolution[2], bool perspective)
{ // Set-up the resolution, clear color, camera properties and camera pose:

    bool retVal = App::worldContainer->pluginContainer->selectExtRenderer(extRendererIndex);

    void* data[30];
    data[0] = resolution + 0;
    data[1] = resolution + 1;
    data[2] = App::currentWorld->environment->fogBackgroundColor;
    C7Vector tr(getFullCumulativeTransformation());
    float x[3] = {(float)tr.X(0), (float)tr.X(1), (float)tr.X(2)};
    data[3] = x;
    float q[4] = {(float)tr.Q(0), (float)tr.Q(1), (float)tr.Q(2), (float)tr.Q(3)};
    data[4] = q;
    int options = 0;
    float xAngle_size;
    float yAngle_size;
    float ratio = (float)(resolution[0] / (float)resolution[1]);
    float nearClip, farClip;
    if (perspective)
    {
        if (ratio > 1.0f)
        {
            xAngle_size = (float)_viewAngle;
            yAngle_size = 2.0f * atan(tan(_viewAngle / 2.0f) / ratio);
        }
        else
        {
            xAngle_size = 2.0f * atan(tan(_viewAngle / 2.0f) * ratio);
            yAngle_size = (float)_viewAngle;
        }
        nearClip = (float)_nearClippingPlane;
        farClip = (float)_farClippingPlane;
    }
    else
    {
        options |= 1;
        if (ratio > 1.0f)
        {
            xAngle_size = (float)_orthoViewSize;
            yAngle_size = (float)_orthoViewSize / ratio;
        }
        else
        {
            xAngle_size = (float)_orthoViewSize * ratio;
            yAngle_size = (float)_orthoViewSize;
        }
        nearClip = (float)ORTHO_CAMERA_NEAR_CLIPPING_PLANE;
        farClip = (float)ORTHO_CAMERA_FAR_CLIPPING_PLANE;
    }
    data[5] = &options;
    data[6] = &xAngle_size;
    data[7] = &yAngle_size;
    float va = (float)_viewAngle;
    data[8] = &va;
    data[9] = &nearClip;
    data[10] = &farClip;
    data[11] = App::currentWorld->environment->ambientLightColor;
    data[12] = App::currentWorld->environment->fogBackgroundColor;
    int fogType = App::currentWorld->environment->getFogType();
    float fogStart = (float)App::currentWorld->environment->getFogStart();
    float fogEnd = (float)App::currentWorld->environment->getFogEnd();
    float fogDensity = (float)App::currentWorld->environment->getFogDensity();
    bool fogEnabled = App::currentWorld->environment->getFogEnabled();
    data[13] = &fogType;
    data[14] = &fogStart;
    data[15] = &fogEnd;
    data[16] = &fogDensity;
    data[17] = &fogEnabled;
    float ovs = (float)_orthoViewSize;
    data[18] = &ovs;
    data[19] = &_objectHandle;
    data[20] = nullptr;
    data[21] = nullptr;

    // Following actually free since CoppeliaSim 3.3.0
    // But the older PovRay plugin version crash without this:
    float povFogDist = 4.0f;
    float povFogTransp = 0.5f;
    bool povFocalBlurEnabled = false;
    float povFocalLength = 0.0f;
    float povAperture = 0.0f;
    int povBlurSamples;
    data[22] = &povFogDist;
    data[23] = &povFogTransp;
    data[24] = &povFocalBlurEnabled;
    data[25] = &povFocalLength;
    data[26] = &povAperture;
    data[27] = &povBlurSamples;

#ifdef SIM_WITH_GUI
#ifdef USES_QGLWIDGET
    QGLWidget* otherWidgetToShareResourcesWith = nullptr;
#else
    QOpenGLWidget* otherWidgetToShareResourcesWith = nullptr;
#endif
    if (GuiApp::mainWindow != nullptr)
        data[28] = GuiApp::mainWindow->openglWidget;
#endif

    App::worldContainer->pluginContainer->extRenderer(sim_message_eventcallback_extrenderer_start, data);
    return (retVal);
}

void CCamera::_extRenderer_prepareLights()
{ // Set-up the lights:
    for (size_t li = 0; li < App::currentWorld->sceneObjects->getObjectCount(sim_sceneobject_light); li++)
    {
        CLight* light = App::currentWorld->sceneObjects->getLightFromIndex(li);
        if (light->getLightActive())
        {
            void* data[20];
            int lightType = light->getLightType();
            data[0] = &lightType;
            float cutoffAngle = (float)light->getSpotCutoffAngle();
            data[1] = &cutoffAngle;
            int spotExponent = light->getSpotExponent();
            data[2] = &spotExponent;
            data[3] = light->getColor(true)->getColorsPtr();
            double arr[3];
            light->getAttenuationFactors(arr);
            float constAttenuation = (float)arr[0];
            data[4] = &constAttenuation;
            float linAttenuation = (float)arr[1];
            data[5] = &linAttenuation;
            float quadAttenuation = (float)arr[2];
            data[6] = &quadAttenuation;
            C7Vector tr(light->getFullCumulativeTransformation());
            float x[3] = {(float)tr.X(0), (float)tr.X(1), (float)tr.X(2)};
            data[7] = x;
            float q[4] = {(float)tr.Q(0), (float)tr.Q(1), (float)tr.Q(2), (float)tr.Q(3)};
            data[8] = q;
            float lightSize = (float)light->getLightSize();
            data[9] = &lightSize;
            bool lightIsVisible = light->getShouldObjectBeDisplayed(_objectHandle, 0);
            data[11] = &lightIsVisible;
            int lightHandle = light->getObjectHandle();
            data[13] = &lightHandle;

            // Following actually free since CoppeliaSim 3.3.0
            // But the older PovRay plugin version crash without this:
            float povFadeXDist = 0.0f;
            bool povNoShadow = false;
            data[10] = &povFadeXDist;
            data[12] = &povNoShadow;

            App::worldContainer->pluginContainer->extRenderer(sim_message_eventcallback_extrenderer_light, data);
        }
    }
}

void CCamera::_extRenderer_retrieveImage(char* rgbBuffer)
{ // Fetch the finished image:
    void* data[20];
    data[0] = rgbBuffer;
    data[1] = nullptr;
    bool readRgb = true;
    data[2] = &readRgb;
    bool readDepth = false;
    data[3] = &readDepth;
    App::worldContainer->pluginContainer->extRenderer(sim_message_eventcallback_extrenderer_stop, data);
}

void CCamera::_drawObjects(int renderingMode, int pass, int currentWinSize[2], CSView* subView, bool mirrored)
{
    TRACE_INTERNAL;

    int displayAttrib = _attributesForRendering;
    if (pass == DEPTHPASS)
        displayAttrib = sim_displayattribute_depthpass | sim_displayattribute_forbidedges;
    if (mirrored)
        displayAttrib = sim_displayattribute_mirror;
    if (pass == PICKPASS)
        displayAttrib = sim_displayattribute_pickpass | sim_displayattribute_forbidedges;
    if (pass == COLORCODEDPICKPASS)
        displayAttrib = sim_displayattribute_colorcodedpickpass | sim_displayattribute_forbidedges;
    if (((renderingMode == RENDERING_MODE_WIREFRAME_EDGES) || (renderingMode == RENDERING_MODE_WIREFRAME_TRIANGLES)) &&
        (pass == RENDERPASS))
    {
        displayAttrib |= sim_displayattribute_forcewireframe;
        if (renderingMode == RENDERING_MODE_WIREFRAME_TRIANGLES)
            displayAttrib |= sim_displayattribute_trianglewireframe;
    }

    if (App::currentWorld->simulation->getDynamicContentVisualizationOnly())
        displayAttrib |= sim_displayattribute_dynamiccontentonly;

    int viewIndex = -1;
    if (subView != nullptr)
    {
        if ((!subView->getShowEdges()) || CEnvironment::getShapeEdgesTemporarilyDisabled())
            displayAttrib |= sim_displayattribute_forbidedges;
        if (subView->getThickEdges())
            displayAttrib |= sim_displayattribute_thickEdges;
        viewIndex = int(subView->getViewIndex());
    }

    bool shapeEditMode = ((GuiApp::getEditModeType() & SHAPE_EDIT_MODE) != 0);
    bool multiShapeEditMode = ((GuiApp::getEditModeType() & MULTISHAPE_EDIT_MODE) != 0);
    bool shapeEditModeAndPicking = (shapeEditMode && ((pass == PICKPASS) || (pass == COLORCODEDPICKPASS)));

    // If selection size is bigger than 10, we set up a fast index:
    std::vector<unsigned char>* selMap = nullptr; // An arry which will show which object is selected
    if (App::currentWorld->sceneObjects->getSelectionCount() > 10)
    {
        selMap = new std::vector<unsigned char>(App::currentWorld->sceneObjects->getHighestObjectHandle() + 1, 0);
        for (size_t i = 0; i < App::currentWorld->sceneObjects->getSelectionCount(); i++)
            selMap->at(App::currentWorld->sceneObjects->getObjectHandleFromSelectionIndex(i)) = 1;
    }
    int lastSel = -1;
    if (App::currentWorld->sceneObjects->getSelectionCount() > 0)
        lastSel = App::currentWorld->sceneObjects->getObjectHandleFromSelectionIndex(
            App::currentWorld->sceneObjects->getSelectionCount() - 1);

    std::vector<CSceneObject*> toRender;
    CSceneObject* viewBoxObject = _getInfoOfWhatNeedsToBeRendered(toRender);

    if (viewBoxObject != nullptr)
    { // we set the same position as the camera, but we keep the initial orientation
        // If the camera is in ortho view mode, we additionally shift it along the viewing axis
        // to be sure we don't cover anything visible with the far side of the box (the near side is clipped by model
        // settings)
        C4Vector rel(viewBoxObject->getLocalTransformation().Q);
        C7Vector cam(getFullCumulativeTransformation());
        if (!_currentPerspective)
        {
            C3Vector minV(C3Vector::inf);
            C3Vector maxV(C3Vector::ninf);
            viewBoxObject->getModelBB((getCumulativeTransformation() * getBB(nullptr)).getInverse(), minV, maxV, true);
            double shift = ORTHO_CAMERA_FAR_CLIPPING_PLANE - 0.505 * (maxV(2) - minV(2)); // just a bit more than half!
            cam.X += cam.Q.getMatrix().axis[2] * shift;
        }
        C7Vector newLocal(viewBoxObject->getFullParentCumulativeTransformation().getInverse() * cam);
        newLocal.Q = rel;
        viewBoxObject->setLocalTransformation(newLocal);
    }

    // For those special drawing routines that require the window size and other info:
    double verticalViewSizeOrAngle;
    double ratio = (double)(currentWinSize[0] / (double)currentWinSize[1]);
    if (_currentPerspective)
    {
        if (ratio > 1.0)
            verticalViewSizeOrAngle = 2.0 * atan(tan(_viewAngle / 2.0) / ratio);
        else
            verticalViewSizeOrAngle = _viewAngle;
    }
    else
    {
        if (ratio > 1.0)
            verticalViewSizeOrAngle = _orthoViewSize / ratio;
        else
            verticalViewSizeOrAngle = _orthoViewSize;
    }

    if (!multiShapeEditMode)
    {
        if (getInternalRendering())
        {
            glInitNames();
            glPushName(-1);
            glShadeModel(GL_SMOOTH);

            if ((displayAttrib & (sim_displayattribute_colorcoded | sim_displayattribute_colorcodedpickpass)) == 0)
                glEnable(GL_DITHER);
            else
                glDisable(GL_DITHER);

            _prepareAuxClippingPlanes();
            _enableAuxClippingPlanes(-1);
        }

        if (!shapeEditModeAndPicking)
        {
            if (getInternalRendering()) // following not yet implemented for ext. rendering
                App::currentWorld->renderYourGeneralObject3DStuff_beforeRegularObjects(
                    this, displayAttrib, currentWinSize, verticalViewSizeOrAngle,
                    _currentPerspective); // those objects are not supposed to be translucid!
        }

        if (getInternalRendering())
            _disableAuxClippingPlanes();

        if (!shapeEditModeAndPicking)
        {
            for (int rp = 0; rp < int(toRender.size()); rp++)
            {
                CSceneObject* it = toRender[rp];
                int atr = displayAttrib;
                if (((it->getCumulativeObjectProperty() & sim_objectproperty_depthinvisible) == 0) ||
                    (pass != DEPTHPASS))
                {
                    if (selMap != nullptr)
                    {
                        if (selMap->at(it->getObjectHandle()) != 0)
                            atr |= sim_displayattribute_selected;
                        if (it->getObjectHandle() == lastSel)
                            atr |= sim_displayattribute_mainselection;
                    }
                    else
                    {
                        for (size_t i = 0; i < App::currentWorld->sceneObjects->getSelectionCount(); i++)
                        {
                            if (it->getObjectHandle() ==
                                App::currentWorld->sceneObjects->getObjectHandleFromSelectionIndex(i))
                            {
                                atr |= sim_displayattribute_selected;
                                if (it->getObjectHandle() == lastSel)
                                    atr |= sim_displayattribute_mainselection;
                                break;
                            }
                        }
                    }
                    // Draw everything except for the camera you look through (unless we look through the mirror) and
                    // the object which is being edited!
                    if ((it->getObjectHandle() != getObjectHandle()) || mirrored)
                    {
                        if ((GuiApp::getEditModeType() & SHAPE_OR_PATH_EDIT_MODE_OLD) == 0)
                        {
                            if (getInternalRendering())
                                it->display(this, atr);
                            else
                            {
                                if (it->getObjectType() == sim_sceneobject_shape)
                                    ((CShape*)it)->display_extRenderer(this, atr);
                            }
                        }
                        else if (it->getObjectHandle() != GuiApp::mainWindow->editModeContainer->getEditModeObjectID())
                            it->display(this, atr);
                    }
                }
            }

            double val = _orthoViewSize;
            if (_currentPerspective)
                val = 2.0 * tan(_viewAngle * 0.5);

            // Display inertia box overlays:
            if (GuiApp::getShowInertias() && ((displayAttrib & sim_displayattribute_renderpass) != 0) &&
                ((GuiApp::getEditModeType() & SHAPE_OR_PATH_EDIT_MODE_OLD) == 0) && getInternalRendering())
            {
                for (size_t rp = 0; rp < toRender.size(); rp++)
                {
                    if (toRender[rp]->getObjectType() == sim_sceneobject_shape)
                    {
                        CShape* it = (CShape*)toRender[rp];
                        if (!it->getStatic())
                            it->displayInertia(this, val, _currentPerspective);
                    }
                }
            }

            // Display frames and bounding boxes of selected items:
            if (((displayAttrib & sim_displayattribute_renderpass) != 0) &&
                ((GuiApp::getEditModeType() & SHAPE_OR_PATH_EDIT_MODE_OLD) == 0) && getInternalRendering())
            {
                for (size_t rp = 0; rp < toRender.size(); rp++)
                {
                    CSceneObject* it = toRender[rp];
                    if (it->getSelected() && ((it->getObjectHandle() != getObjectHandle()) || mirrored))
                    {
                        it->displayFrames(this, val, _currentPerspective);
                        it->displayBoundingBox(this, it->getObjectHandle() == lastSel);
                    }
                }
            }
        }

        if (selMap != nullptr)
        {
            delete selMap;
            selMap = nullptr;
        }

        if (getInternalRendering())
            _enableAuxClippingPlanes(-1);

        if (!shapeEditModeAndPicking)
        {
            if (getInternalRendering()) // following not yet implemented for ext. rendering
                App::currentWorld->renderYourGeneralObject3DStuff_afterRegularObjects(
                    this, displayAttrib, currentWinSize, verticalViewSizeOrAngle,
                    _currentPerspective); // those objects can be translucid
            if (getInternalRendering())   // following not yet implemented for ext. rendering
                App::currentWorld->renderYourGeneralObject3DStuff_onTopOfRegularObjects(
                    this, displayAttrib, currentWinSize, verticalViewSizeOrAngle,
                    _currentPerspective); // those objects are overlay
            if (getInternalRendering())
            { // Now we display all graphs' 3D curves that should appear on top of everything:
                for (size_t i = 0; i < App::currentWorld->sceneObjects->getObjectCount(sim_sceneobject_graph); i++)
                {
                    CGraph* it = App::currentWorld->sceneObjects->getGraphFromIndex(i);
                    if (it != nullptr)
                    {
                        it->setJustDrawCurves(true);
                        it->display(this, displayAttrib);
                        it->setJustDrawCurves(false);
                    }
                }
            }
        }

        if (getInternalRendering())
            _disableAuxClippingPlanes();

        // We render the object being edited last (the vertices appear above everything)
        if (getInternalRendering())
        {
            if (GuiApp::getEditModeType() & SHAPE_OR_PATH_EDIT_MODE_OLD)
            {
                CSceneObject* it = GuiApp::mainWindow->editModeContainer->getEditModeObject();
                if (it != nullptr)
                    it->display(this, displayAttrib);
            }
        }

        if (getInternalRendering())
        {
            glLoadName(-1);

            if (pass == RENDERPASS)
            {
                // Wireless communication activities:
                if ((displayAttrib & sim_displayattribute_dynamiccontentonly) == 0)
                    App::currentWorld->sceneObjects->embeddedScriptContainer->broadcastDataContainer.visualizeCommunications((int)VDateTime::getTimeInMs());
            }
        }
    }
    else
    { // Multishape edit mode:
        CShape* it = GuiApp::mainWindow->editModeContainer->getEditModeShape();
        if (it != nullptr)
            it->display(this, displayAttrib);
    }

    SModelThumbnailInfo* info = GuiApp::mainWindow->openglWidget->getModelDragAndDropInfo();
    if ((pass == RENDERPASS) && (info != nullptr))
    {
        double ss = info->modelNonDefaultTranslationStepSize;
        if (ss == 0.0)
            ss = App::userSettings->getTranslationStepSize();
        double x = info->desiredDropPos(0) - fmod(info->desiredDropPos(0), ss);
        double y = info->desiredDropPos(1) - fmod(info->desiredDropPos(1), ss);
        const float pink[3] = {1.0, 1.0, 0.0};
        ogl::setMaterialColor(pink, ogl::colorBlack, ogl::colorBlack);
        ogl::setBlending(false);
        glPushMatrix();
        glTranslated(x + info->modelTr.X(0), y + info->modelTr.X(1), info->modelTr.X(2));
        C4Vector axis = info->modelTr.Q.getAngleAndAxis();
        glRotated(axis(0) * radToDeg, axis(1), axis(2), axis(3));
        ogl::drawBox(info->modelBoundingBoxSize(0), info->modelBoundingBoxSize(1), info->modelBoundingBoxSize(2), true,
                     nullptr);
        glPopMatrix();
        ogl::setMaterialColor(ogl::colorBlack, ogl::colorBlack, pink);
        glPushMatrix();
        glTranslated(x, y, 0.002);
        glLineWidth(2.0);
        ogl::drawCircle(0.125, 32);
        ogl::drawCircle(0.25, 32);
        ogl::drawCircle(0.5, 32);
        ogl::drawCircle(1.0, 32);
        ogl::drawCircle(2.0, 32);
        glPopMatrix();
        glLineStipple(1, 0x0F0F);
        glEnable(GL_LINE_STIPPLE);
        ogl::buffer.clear();
        ogl::addBuffer3DPoints(x, y, 0.0);
        ogl::addBuffer3DPoints(x, y, info->modelTr.X(2));
        ogl::drawRandom3dLines(&ogl::buffer[0], int(ogl::buffer.size() / 3), false, nullptr);
        glDisable(GL_LINE_STIPPLE);
        glLineWidth(1.0);
    }
}

CSceneObject* CCamera::_getInfoOfWhatNeedsToBeRendered(std::vector<CSceneObject*>& toRender)
{
    std::vector<int> transparentObjects;
    std::vector<double> transparentObjectDist;
    C7Vector camTrInv(getCumulativeTransformation().getInverse());
    CSceneObject* viewBoxObject = nullptr;
    for (size_t i = 0; i < App::currentWorld->sceneObjects->getObjectCount(); i++)
    {
        CSceneObject* it = App::currentWorld->sceneObjects->getObjectFromIndex(i);
        if (it->getObjectType() == sim_sceneobject_shape)
        {
            CShape* sh = (CShape*)it;
            if (sh->getContainsTransparentComponent())
            {
                C7Vector obj(it->getCumulativeTransformation());
                transparentObjectDist.push_back(-(camTrInv * obj).X(2) - it->getTransparentObjectDistanceOffset());
                transparentObjects.push_back(it->getObjectHandle());
            }
            else
                toRender.push_back(it);
        }
        else
        {
            if (it->getObjectType() == sim_sceneobject_mirror)
            {
                CMirror* mir = (CMirror*)it;
                if (mir->getContainsTransparentComponent())
                {
                    C7Vector obj(it->getCumulativeTransformation());
                    transparentObjectDist.push_back(-(camTrInv * obj).X(2) - it->getTransparentObjectDistanceOffset());
                    transparentObjects.push_back(it->getObjectHandle());
                }
                else
                    toRender.push_back(it);
            }
            else
                toRender.push_back(it);
        }
        if (it->getObjectName_old() == IDSOGL_SKYBOX_DO_NOT_RENAME)
            viewBoxObject = it;
    }

    tt::orderAscending(transparentObjectDist, transparentObjects);
    for (int i = 0; i < int(transparentObjects.size()); i++)
        toRender.push_back(App::currentWorld->sceneObjects->getObjectFromHandle(transparentObjects[i]));

    return (viewBoxObject);
}

void CCamera::performDepthPerception(CSView* subView, bool isPerspective)
{
    TRACE_INTERNAL;
    if (subView == nullptr)
        return;
    int mouseMode = GuiApp::getMouseMode();
    int windowSize[2];
    subView->getViewSize(windowSize);
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    GLfloat pixel[1];
    double farDivFarMinusNear = _farClippingPlane / (_farClippingPlane - _nearClippingPlane);
    if (!isPerspective)
        farDivFarMinusNear =
            ORTHO_CAMERA_FAR_CLIPPING_PLANE / (ORTHO_CAMERA_FAR_CLIPPING_PLANE - ORTHO_CAMERA_NEAR_CLIPPING_PLANE);
    C4X4Matrix m(getCumulativeTransformation());

    int mouseRelativePosition[2];
    subView->getMouseRelativePosition(mouseRelativePosition);

    glReadPixels(mouseRelativePosition[0] + viewport[0], mouseRelativePosition[1] + viewport[1], 1, 1,
                 GL_DEPTH_COMPONENT, GL_FLOAT, pixel);
    if (isPerspective)
        subView->setMousePositionDepth(_nearClippingPlane * _farClippingPlane /
                                       ((_farClippingPlane - _nearClippingPlane) * (farDivFarMinusNear - pixel[0])));
    else
        subView->setMousePositionDepth(ORTHO_CAMERA_NEAR_CLIPPING_PLANE +
                                       pixel[0] * (ORTHO_CAMERA_FAR_CLIPPING_PLANE - ORTHO_CAMERA_NEAR_CLIPPING_PLANE));

    double clippFar = _farClippingPlane;
    double clippNear = _nearClippingPlane;
    if (!isPerspective)
    {
        clippFar = ORTHO_CAMERA_FAR_CLIPPING_PLANE;
        clippNear = ORTHO_CAMERA_NEAR_CLIPPING_PLANE;
    }

    if (pixel[0] >= (1.0 - 2.0 * std::numeric_limits<double>::epsilon()))
    { // The cursor hit the far clipping plane:
        subView->setMousePositionDepth(clippNear);
        double p[3];
        (m.X + m.M.axis[2] * clippNear).getData(p);
        subView->setCenterPosition(p);
    }
    else
    {
        double yShift;
        double xShift;
        double ratio = (double)(windowSize[0] / (double)windowSize[1]);
        int mouseDownRelPos[2];
        subView->getMouseDownRelativePosition(mouseDownRelPos);
        if (isPerspective)
        {
            if (ratio > 1.0)
            {
                double tmp = (windowSize[0] / 2) / tan(_viewAngle * 0.5);
                xShift = (-mouseDownRelPos[0] + (windowSize[0] / 2)) * subView->getMousePositionDepth() / tmp;
                double angle2 = 2.0 * atan(tan(_viewAngle / 2.0) / ratio) * radToDeg;
                tmp = (windowSize[1] / 2) / tan(angle2 * degToRad * 0.5);
                yShift = (mouseDownRelPos[1] - (windowSize[1] / 2)) * subView->getMousePositionDepth() / tmp;
            }
            else
            {
                double tmp = (windowSize[1] / 2) / tan(_viewAngle * 0.5);
                yShift = (mouseDownRelPos[1] - (windowSize[1] / 2)) * subView->getMousePositionDepth() / tmp;
                double angle2 = 2.0 * atan(tan(_viewAngle / 2.0) * ratio) * radToDeg;
                tmp = (windowSize[0] / 2) / tan(angle2 * degToRad * 0.5);
                xShift = (-mouseDownRelPos[0] + (windowSize[0] / 2)) * subView->getMousePositionDepth() / tmp;
            }
        }
        else
        {
            if (ratio > 1.0)
            {
                double tmp = windowSize[0] / _orthoViewSize;
                xShift = (-mouseDownRelPos[0] + (windowSize[0] / 2)) / tmp;
                tmp = windowSize[1] / (_orthoViewSize / ratio);
                yShift = (+mouseDownRelPos[1] - (windowSize[1] / 2)) / tmp;
            }
            else
            {
                double tmp = windowSize[1] / _orthoViewSize;
                yShift = (mouseDownRelPos[1] - (windowSize[1] / 2)) / tmp;
                tmp = windowSize[0] / (_orthoViewSize * ratio);
                xShift = (-mouseDownRelPos[0] + (windowSize[0] / 2)) / tmp;
            }
        }
        double p[3];

        (m.X + m.M.axis[2] * subView->getMousePositionDepth() + m.M.axis[1] * yShift + m.M.axis[0] * xShift).getData(p);
        subView->setCenterPosition(p);
    }
}

void CCamera::_drawOverlay(bool passiveView, bool drawText, bool displ_ref, int windowSize[2], CSView* subView)
{
    TRACE_INTERNAL;
    int navigationMode = sim_navigation_passive;
    int selectionMode = NOSELECTION;
    if (subView != nullptr)
    {
        navigationMode = GuiApp::getMouseMode() & 0x00ff;
        selectionMode = subView->getSelectionStatus();
    }
    ogl::setMaterialColor(ogl::colorBlack, ogl::colorBlack, ogl::colorBlack);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, windowSize[0], 0, windowSize[1], -100, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST);

    // Draw the selection square
    if ((selectionMode == SHIFTSELECTION) && (subView != nullptr) && subView->isMouseDown())
    {
        int mouseDownRelPos[2];
        int mouseRelPos[2];
        subView->getMouseDownRelativePosition(mouseDownRelPos);
        subView->getMouseRelativePosition(mouseRelPos);
        int x1 = mouseDownRelPos[0];
        int y1 = mouseDownRelPos[1];
        int x2 = mouseRelPos[0];
        int y2 = mouseRelPos[1];
        tt::limitValue(0, windowSize[0], x1);
        tt::limitValue(0, windowSize[1], y1);
        tt::limitValue(0, windowSize[0], x2);
        tt::limitValue(0, windowSize[1], y2);

        ogl::setMaterialColor(sim_colorcomponent_emission, ogl::colorYellow);
        ogl::setAlpha(0.2);
        ogl::setBlending(true, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBegin(GL_QUADS);
        glVertex3i(x1, y1, 0);
        glVertex3i(x1, y2, 0);
        glVertex3i(x2, y2, 0);
        glVertex3i(x2, y1, 0);
        glVertex3i(x1, y1, 0);
        glEnd();
        ogl::setBlending(false);
        ogl::setMaterialColor(sim_colorcomponent_emission, ogl::colorWhite);
        glBegin(GL_LINE_STRIP);
        glVertex3i(x1, y1, 0);
        glVertex3i(x1, y2, 0);
        glVertex3i(x2, y2, 0);
        glVertex3i(x2, y1, 0);
        glVertex3i(x1, y1, 0);
        glEnd();
        glDisable(GL_LINE_STIPPLE);
    }

    if (App::userSettings->displayWorldReference && displ_ref)
    {
        glTranslated(double(windowSize[0] - 60.0 * GuiApp::sc), 40.0 * GuiApp::sc, 0.0);
        C7Vector tr2(getFullCumulativeTransformation());
        tr2.inverse();
        C4X4Matrix m1;
        m1.buildYRotation(piValue);
        C7Vector tr0(m1.getTransformation() * tr2);
        double refSize = 30.0 * GuiApp::sc;

        C3Vector euler(tr0.Q.getEulerAngles());
        glPushMatrix();
        glRotated(euler(0) * radToDeg, 1.0, 0.0, 0.0);
        glRotated(euler(1) * radToDeg, 0.0, 1.0, 0.0);
        glRotated(euler(2) * radToDeg, 0.0, 0.0, 1.0);

        glLineWidth((float)GuiApp::sc);
        ogl::drawReference(refSize);
        glLineWidth(1.0);

        glPopMatrix();
        ogl::setTextColor(ogl::colorBlack);
        glTranslated(0.2 * refSize, 0.2 * refSize, 0.0);
        C3X3Matrix m0(tr0.Q.getMatrix());
        ogl::drawBitmapTextIntoScene(m0(0, 0) * refSize, m0(1, 0) * refSize, 0.0, IDSOGL_X);
        ogl::drawBitmapTextIntoScene(m0(0, 1) * refSize, m0(1, 1) * refSize, 0.0, IDSOGL_Y);
        ogl::drawBitmapTextIntoScene(m0(0, 2) * refSize, m0(1, 2) * refSize, 0.0, IDSOGL_Z);
    }
    glEnable(GL_DEPTH_TEST);
}

int CCamera::getSingleHit(int hits, unsigned int selectBuff[], bool ignoreDepthBuffer,
                          int& hitThatIgnoresTheSelectableFlag)
{ // this routine is called in non-edit mode, but also while in an edit mode!!
    TRACE_INTERNAL;
    hitThatIgnoresTheSelectableFlag = -1;
    if (hits != 0)
    {
        unsigned int nearestObj = 0;
        unsigned int distance = selectBuff[1];
        for (int i = 0; i < hits; i++)
        {
            if (i == 0)
            { // the first hit. We always take this one into account
                distance = selectBuff[4 * i + 1];
                nearestObj = selectBuff[4 * i + 3];
                hitThatIgnoresTheSelectableFlag = nearestObj;
                if ((nearestObj <= SIM_IDEND_SCENEOBJECT) && (GuiApp::getEditModeType() == NO_EDIT_MODE))
                { // since 3/6/2013 we check for the selectable flag here instead of in the object display routine
                    CSceneObject* theObj = App::currentWorld->sceneObjects->getObjectFromHandle(nearestObj);
                    if ((theObj != nullptr) &&
                        ((theObj->getCumulativeObjectProperty() & sim_objectproperty_selectable) == 0))
                        nearestObj = (unsigned int)-1;
                }
            }
            else
            {
                if (!ignoreDepthBuffer)
                {
                    bool shapeEditAndNoHitYet =
                        ((GuiApp::getEditModeType() & SHAPE_EDIT_MODE) && (nearestObj == (unsigned int)-1));
                    if ((selectBuff[4 * i + 1] <= distance) || shapeEditAndNoHitYet)
                    { // this hit is closer
                        distance = selectBuff[4 * i + 1];
                        nearestObj = selectBuff[4 * i + 3];
                        hitThatIgnoresTheSelectableFlag = nearestObj;
                        if ((nearestObj <= SIM_IDEND_SCENEOBJECT) && (GuiApp::getEditModeType() == NO_EDIT_MODE))
                        { // since 3/6/2013 we check for the selectable flag here instead of in the object display
                            // routine
                            CSceneObject* theObj = App::currentWorld->sceneObjects->getObjectFromHandle(nearestObj);
                            if ((theObj != nullptr) &&
                                ((theObj->getCumulativeObjectProperty() & sim_objectproperty_selectable) == 0))
                                nearestObj = (unsigned int)-1;
                        }
                    }
                }
                else
                {
                    if (nearestObj == (unsigned int)-1)
                    { // we take this hit since we don't yet have a hit
                        distance = selectBuff[4 * i + 1];
                        nearestObj = selectBuff[4 * i + 3];
                        hitThatIgnoresTheSelectableFlag = nearestObj;
                        if ((nearestObj <= SIM_IDEND_SCENEOBJECT) && (GuiApp::getEditModeType() == NO_EDIT_MODE))
                        { // since 3/6/2013 we check for the selectable flag here instead of in the object display
                            // routine
                            CSceneObject* theObj = App::currentWorld->sceneObjects->getObjectFromHandle(nearestObj);
                            if ((theObj != nullptr) &&
                                ((theObj->getCumulativeObjectProperty() & sim_objectproperty_selectable) == 0))
                                nearestObj = (unsigned int)-1;
                        }
                    }
                }
            }
        }

        if (nearestObj == (unsigned int)-1)
            return (-1); // we didn't hit anything
        else
            return ((int)nearestObj); // we hit this ID
    }
    else
        return (-1); // we didn't hit anything
}

int CCamera::getSeveralHits(int hits, unsigned int selectBuff[], std::vector<int>& hitList)
{ // this routine is called in non-edit mode, but also while in an edit mode!!
    TRACE_INTERNAL;
    hitList.clear();
    if (hits != 0)
    {
        int cnt = 0;
        for (int i = 0; i < hits; i++)
        {
            unsigned int theHit = selectBuff[4 * i + 3];
            if (theHit != ((unsigned int)-1))
            {
                if ((theHit <= SIM_IDEND_SCENEOBJECT) && (GuiApp::getEditModeType() == NO_EDIT_MODE))
                { // since 3/6/2013 we check for the selectable flag here instead of in the object display routine
                    CSceneObject* theObj = App::currentWorld->sceneObjects->getObjectFromHandle(theHit);
                    if ((theObj != nullptr) &&
                        ((theObj->getCumulativeObjectProperty() & sim_objectproperty_selectable) == 0))
                        theHit = (unsigned int)-1;
                }
                if (int(theHit) != -1)
                {
                    cnt++;
                    hitList.push_back((int)theHit);
                }
            }
        }
        return (cnt);
    }
    else
        return (0); // we didn't hit anything
}

void CCamera::handleMouseUpHit(int hitId)
{
    TRACE_INTERNAL;
    if (hitId == -1)
    {
        if ((GuiApp::getEditModeType() & SHAPE_OR_PATH_EDIT_MODE_OLD) == 0)
            App::currentWorld->sceneObjects->deselectObjects();
        else
            GuiApp::mainWindow->editModeContainer->deselectEditModeBuffer();
    }
    else
    {
        if ((hitId < SIM_IDEND_SCENEOBJECT) ||
            (hitId >=
             NON_OBJECT_PICKING_ID_PATH_PTS_START)) // We need the NON_OBJECT_PICKING_ID_PATH_PTS_START start here to
                                                    // select individual path points when not in path edit mode!!!!!!!
        {
            if ((GuiApp::getEditModeType() & SHAPE_OR_PATH_EDIT_MODE_OLD) == 0)
            {
                App::currentWorld->sceneObjects->deselectObjects();
                App::currentWorld->sceneObjects->addObjectToSelection(hitId);
            }
            else
            {
                GuiApp::mainWindow->editModeContainer->deselectEditModeBuffer();
                GuiApp::mainWindow->editModeContainer->addItemToEditModeBuffer(hitId, false);
            }
        }
        if ((hitId >= NON_OBJECT_PICKING_ID_BANNER_START) && (hitId < NON_OBJECT_PICKING_ID_BANNER_END))
            _handleBannerClick(hitId - NON_OBJECT_PICKING_ID_BANNER_START);
    }
}

int CCamera::handleHits(int hits, unsigned int selectBuff[])
{ // -2 means: handle no mouse up hits. Otherwise, handle mouse up hits!
    TRACE_INTERNAL;
    if (GuiApp::mainWindow == nullptr)
        return (-2);
    if (GuiApp::mainWindow->getMouseButtonState() &
        4) // added on 2011/01/12 because this routine is now also called when not in click-select mode, etc. We need to
           // make sure we don't have a "virtual" left mouse button clicked triggered by the right mouse button
        return (-2);
    if (GuiApp::mainWindow->getKeyDownState() & 2)
    {
        std::vector<int> hitList;
        if (getSeveralHits(hits, selectBuff, hitList) > 0)
        {
            for (int i = 0; i < int(hitList.size()); i++)
            {
                if ((hitList[i] < SIM_IDEND_SCENEOBJECT) ||
                    (hitList[i] >=
                     NON_OBJECT_PICKING_ID_PATH_PTS_START)) // We need the NON_OBJECT_PICKING_ID_PATH_PTS_START start
                                                            // here to select individual path points when not in path
                                                            // edit mode!!!!!!!
                {
                    if ((GuiApp::getEditModeType() & SHAPE_OR_PATH_EDIT_MODE_OLD) == 0)
                        App::currentWorld->sceneObjects->addObjectToSelection(hitList[i]);
                    else
                        GuiApp::mainWindow->editModeContainer->addItemToEditModeBuffer(hitList[i], true);
                }
                if ((hitList[i] >= NON_OBJECT_PICKING_ID_BANNER_START) &&
                    (hitList[i] < NON_OBJECT_PICKING_ID_BANNER_END))
                    _handleBannerClick(hitList[i] - NON_OBJECT_PICKING_ID_BANNER_START);
            }
        }
        return (-2);
    }
    else
    {
        if (GuiApp::mainWindow->getKeyDownState() & 1)
        {
            int dummy;
            bool ignoreDepth =
                ((GuiApp::getEditModeType() & VERTEX_EDIT_MODE) || (GuiApp::getEditModeType() & EDGE_EDIT_MODE)) &&
                GuiApp::mainWindow->editModeContainer->getShapeEditMode()->getShowHiddenVerticeAndEdges();
            int hitId = getSingleHit(hits, selectBuff, ignoreDepth, dummy);
            if (hitId == -1)
            {
                if ((GuiApp::getEditModeType() & SHAPE_OR_PATH_EDIT_MODE_OLD) == 0)
                    App::currentWorld->sceneObjects->deselectObjects();
                else
                    GuiApp::mainWindow->editModeContainer->deselectEditModeBuffer();
            }
            else
            {
                if ((hitId < SIM_IDEND_SCENEOBJECT) ||
                    (hitId >= NON_OBJECT_PICKING_ID_PATH_PTS_START)) // We need the NON_OBJECT_PICKING_ID_PATH_PTS_START
                                                                     // start here to select individual path points when
                                                                     // not in path edit mode!!!!!!!
                {
                    if ((GuiApp::getEditModeType() & SHAPE_OR_PATH_EDIT_MODE_OLD) == 0)
                        App::currentWorld->sceneObjects->xorAddObjectToSelection(hitId);
                    else
                        GuiApp::mainWindow->editModeContainer->xorAddItemToEditModeBuffer(hitId, false);
                }
                if ((hitId >= NON_OBJECT_PICKING_ID_BANNER_START) && (hitId < NON_OBJECT_PICKING_ID_BANNER_END))
                    _handleBannerClick(hitId - NON_OBJECT_PICKING_ID_BANNER_START);
            }
            return (-2);
        }
        else
        { // no ctrl or shift key down here. We simply return the hit for processing at a later stage
            int hitThatIgnoresTheSelectableFlag;
            bool ignoreDepth =
                ((GuiApp::getEditModeType() & VERTEX_EDIT_MODE) || (GuiApp::getEditModeType() & EDGE_EDIT_MODE)) &&
                GuiApp::mainWindow->editModeContainer->getShapeEditMode()->getShowHiddenVerticeAndEdges();
            int hitId = getSingleHit(hits, selectBuff, ignoreDepth, hitThatIgnoresTheSelectableFlag);

            // OLD:
            int data[4] = {hitThatIgnoresTheSelectableFlag, 0, 0, 0};
            App::worldContainer->pluginContainer->sendEventCallbackMessageToAllPlugins_old(
                sim_message_eventcallback_pickselectdown, data);
            App::currentWorld->outsideCommandQueue_old->addCommand(sim_message_pick_select_down,
                                                                   hitThatIgnoresTheSelectableFlag, 0, 0, 0, nullptr, 0);

            return (hitId);
        }
    }
    return (-2);
}

void CCamera::_handleBannerClick(int bannerID)
{
    TRACE_INTERNAL;
    if (GuiApp::getEditModeType() != NO_EDIT_MODE)
        return;
    CBannerObject* it = App::currentWorld->bannerCont_old->getObject(bannerID);
    if ((it != nullptr) && it->isVisible())
    {
        if (it->getOptions() & sim_banner_clickselectsparent)
        {
            if (it->getParentObjectHandle() >= 0)
                App::currentWorld->sceneObjects->addObjectToSelection(it->getParentObjectHandle());
        }
        if (it->getOptions() & sim_banner_clicktriggersevent)
            App::currentWorld->outsideCommandQueue_old->addCommand(sim_message_bannerclicked, bannerID, 0, 0, 0, nullptr,
                                                                   0);
    }
}

void CCamera::setAttributesForRendering(int attr)
{
    _attributesForRendering = attr;
}

int CCamera::getAttributesForRendering() const
{
    return (_attributesForRendering);
}

void CCamera::setRenderMode(int mode, bool duringSimulation, bool duringRecording)
{
    _renderMode = mode;
    _renderModeDuringSimulation = duringSimulation;
    _renderModeDuringRecording = duringRecording;
}

int CCamera::getRenderMode(bool* duringSimulation, bool* duringRecording) const
{
    if (duringSimulation != nullptr)
        duringSimulation[0] = _renderModeDuringSimulation;
    if (duringRecording != nullptr)
        duringRecording[0] = _renderModeDuringRecording;
    return (_renderMode);
}

bool CCamera::getInternalRendering() const
{
    if (_renderMode != sim_rendermode_opengl)
    {
        if (GuiApp::getEditModeType() == NO_EDIT_MODE)
        {
            if ((_renderMode == sim_rendermode_povray) || (_renderMode == sim_rendermode_extrenderer) ||
                (_renderMode == sim_rendermode_opengl3))
            {
                if (App::currentWorld->simulation->isSimulationRunning() || (!_renderModeDuringSimulation))
                    return (GuiApp::mainWindow->simulationRecorder->getIsRecording() != _renderModeDuringRecording);
            }
        }
    }
    return (true);
}
#endif

int CCamera::setBoolProperty(const char* ppName, bool pState)
{
    std::string _pName(utils::getWithoutPrefix(utils::getWithoutPrefix(ppName, "object.").c_str(), "camera."));
    const char* pName = _pName.c_str();
    int retVal = CViewableBase::setBoolProperty(pName, pState);
    if (retVal == -1)
    {
        if (_pName == propCamera_parentAsManipProxy.name)
        {
            setUseParentObjectAsManipulationProxy(pState);
            retVal = 1;
        }
        else if (_pName == propCamera_translationEnabled.name)
        {
            setAllowTranslation(pState);
            retVal = 1;
        }
        else if (_pName == propCamera_rotationEnabled.name)
        {
            setAllowRotation(pState);
            retVal = 1;
        }
    }

    return retVal;
}

int CCamera::getBoolProperty(const char* ppName, bool& pState) const
{
    std::string _pName(utils::getWithoutPrefix(utils::getWithoutPrefix(ppName, "object.").c_str(), "camera."));
    const char* pName = _pName.c_str();
    int retVal = CViewableBase::getBoolProperty(pName, pState);
    if (retVal == -1)
    {
        if (_pName == propCamera_parentAsManipProxy.name)
        {
            pState = _useParentObjectAsManipulationProxy;
            retVal = 1;
        }
        else if (_pName == propCamera_translationEnabled.name)
        {
            pState = _allowTranslation;
            retVal = 1;
        }
        else if (_pName == propCamera_rotationEnabled.name)
        {
            pState = _allowRotation;
            retVal = 1;
        }
    }

    return retVal;
}

int CCamera::setIntProperty(const char* ppName, int pState)
{
    std::string _pName(utils::getWithoutPrefix(utils::getWithoutPrefix(ppName, "object.").c_str(), "camera."));
    const char* pName = _pName.c_str();
    int retVal = CViewableBase::setIntProperty(pName, pState);
    if (retVal == -1)
    {
        if (_pName == propCamera_trackedObjectHandle.name)
        {
            setTrackedObjectHandle(pState);
            retVal = 1;
        }
    }

    return retVal;
}

int CCamera::getIntProperty(const char* ppName, int& pState) const
{
    std::string _pName(utils::getWithoutPrefix(utils::getWithoutPrefix(ppName, "object.").c_str(), "camera."));
    const char* pName = _pName.c_str();
    int retVal = CViewableBase::getIntProperty(pName, pState);
    if (retVal == -1)
    {
        if (_pName == propCamera_trackedObjectHandle.name)
        {
            pState = _trackedObjectHandle;
            retVal = 1;
        }
    }

    return retVal;
}

int CCamera::setFloatProperty(const char* ppName, double pState)
{
    std::string _pName(utils::getWithoutPrefix(utils::getWithoutPrefix(ppName, "object.").c_str(), "camera."));
    const char* pName = _pName.c_str();
    int retVal = CViewableBase::setFloatProperty(pName, pState);
    if (retVal == -1)
        retVal = _color.setFloatProperty(pName, pState);
    if (retVal == -1)
    {
        if (_pName == propCamera_size.name)
        {
            setCameraSize(pState);
            retVal = 1;
        }
    }

    return retVal;
}

int CCamera::getFloatProperty(const char* ppName, double& pState) const
{
    std::string _pName(utils::getWithoutPrefix(utils::getWithoutPrefix(ppName, "object.").c_str(), "camera."));
    const char* pName = _pName.c_str();
    int retVal = CViewableBase::getFloatProperty(pName, pState);
    if (retVal == -1)
        retVal = _color.getFloatProperty(pName, pState);
    if (retVal == -1)
    {
        if (_pName == propCamera_size.name)
        {
            pState = _cameraSize;
            retVal = 1;
        }
    }

    return retVal;
}

int CCamera::setIntArray2Property(const char* ppName, const int* pState)
{
    std::string _pName(utils::getWithoutPrefix(utils::getWithoutPrefix(ppName, "object.").c_str(), "camera."));
    const char* pName = _pName.c_str();
    int retVal = CViewableBase::setIntArray2Property(pName, pState);
    if (retVal == -1)
    {
    }

    return retVal;
}

int CCamera::getIntArray2Property(const char* ppName, int* pState) const
{
    std::string _pName(utils::getWithoutPrefix(utils::getWithoutPrefix(ppName, "object.").c_str(), "camera."));
    const char* pName = _pName.c_str();
    int retVal = CViewableBase::getIntArray2Property(pName, pState);
    if (retVal == -1)
    {
    }

    return retVal;
}

int CCamera::setVector2Property(const char* ppName, const double* pState)
{
    std::string _pName(utils::getWithoutPrefix(utils::getWithoutPrefix(ppName, "object.").c_str(), "camera."));
    const char* pName = _pName.c_str();
    int retVal = CViewableBase::setVector2Property(pName, pState);
    if (retVal == -1)
    {
    }

    return retVal;
}

int CCamera::getVector2Property(const char* ppName, double* pState) const
{
    std::string _pName(utils::getWithoutPrefix(utils::getWithoutPrefix(ppName, "object.").c_str(), "camera."));
    const char* pName = _pName.c_str();
    int retVal = CViewableBase::getVector2Property(pName, pState);
    if (retVal == -1)
    {
    }

    return retVal;
}

int CCamera::setColorProperty(const char* ppName, const float* pState)
{
    std::string _pName(utils::getWithoutPrefix(utils::getWithoutPrefix(ppName, "object.").c_str(), "camera."));
    const char* pName = _pName.c_str();
    int retVal = CViewableBase::setColorProperty(pName, pState);
    if (retVal == -1)
        retVal = _color.setColorProperty(pName, pState);
    if (retVal != -1)
    {
    }
    return retVal;
}

int CCamera::getColorProperty(const char* ppName, float* pState) const
{
    std::string _pName(utils::getWithoutPrefix(utils::getWithoutPrefix(ppName, "object.").c_str(), "camera."));
    const char* pName = _pName.c_str();
    int retVal = CViewableBase::getColorProperty(pName, pState);
    if (retVal == -1)
        retVal = _color.getColorProperty(pName, pState);
    if (retVal != -1)
    {
    }
    return retVal;
}

int CCamera::setVector3Property(const char* ppName, const C3Vector& pState)
{
    std::string _pName(utils::getWithoutPrefix(utils::getWithoutPrefix(ppName, "object.").c_str(), "camera."));
    const char* pName = _pName.c_str();
    int retVal = CViewableBase::setVector3Property(pName, pState);
    if (retVal == -1)
    {
    }

    return retVal;
}

int CCamera::getVector3Property(const char* ppName, C3Vector& pState) const
{
    std::string _pName(utils::getWithoutPrefix(utils::getWithoutPrefix(ppName, "object.").c_str(), "camera."));
    const char* pName = _pName.c_str();
    int retVal = CViewableBase::getVector3Property(pName, pState);
    if (retVal == -1)
    {
    }

    return retVal;
}

int CCamera::setFloatArrayProperty(const char* ppName, const double* v, int vL)
{
    std::string _pName(utils::getWithoutPrefix(utils::getWithoutPrefix(ppName, "object.").c_str(), "camera."));
    const char* pName = _pName.c_str();
    if (v == nullptr)
        vL = 0;
    int retVal = CViewableBase::setFloatArrayProperty(pName, v, vL);
    if (retVal == -1)
    {
    }

    return retVal;
}

int CCamera::getFloatArrayProperty(const char* ppName, std::vector<double>& pState) const
{
    std::string _pName(utils::getWithoutPrefix(utils::getWithoutPrefix(ppName, "object.").c_str(), "camera."));
    const char* pName = _pName.c_str();
    pState.clear();
    int retVal = CViewableBase::getFloatArrayProperty(pName, pState);
    if (retVal == -1)
    {
    }

    return retVal;
}

int CCamera::setIntArrayProperty(const char* ppName, const int* v, int vL)
{
    std::string _pName(utils::getWithoutPrefix(utils::getWithoutPrefix(ppName, "object.").c_str(), "camera."));
    const char* pName = _pName.c_str();
    if (v == nullptr)
        vL = 0;
    int retVal = CViewableBase::setIntArrayProperty(pName, v, vL);
    if (retVal == -1)
    {
    }

    return retVal;
}

int CCamera::getIntArrayProperty(const char* ppName, std::vector<int>& pState) const
{
    std::string _pName(utils::getWithoutPrefix(utils::getWithoutPrefix(ppName, "object.").c_str(), "camera."));
    const char* pName = _pName.c_str();
    pState.clear();
    int retVal = CViewableBase::getIntArrayProperty(pName, pState);
    if (retVal == -1)
    {
    }

    return retVal;
}

int CCamera::getPropertyName(int& index, std::string& pName, std::string& appartenance) const
{
    int retVal = CSceneObject::getPropertyName(index, pName, appartenance);
    if (retVal == -1)
    {
        appartenance += ".camera";
        retVal = _color.getPropertyName(index, pName);
    }
    if (retVal == -1)
        retVal = CViewableBase::getPropertyName_vstatic(index, pName);
    if (retVal == -1)
    {
        for (size_t i = 0; i < allProps_camera.size(); i++)
        {
            if ((pName.size() == 0) || utils::startsWith(allProps_camera[i].name, pName.c_str()))
            {
                if ((allProps_camera[i].flags & sim_propertyinfo_deprecated) == 0)
                {
                    index--;
                    if (index == -1)
                    {
                        pName = allProps_camera[i].name;
                        retVal = 1;
                        break;
                    }
                }
            }
        }
    }
    return retVal;
}

int CCamera::getPropertyName_static(int& index, std::string& pName, std::string& appartenance)
{
    int retVal = CSceneObject::getPropertyName_bstatic(index, pName, appartenance);
    if (retVal == -1)
    {
        appartenance += ".camera";
        retVal = CColorObject::getPropertyName_static(index, pName, 1 + 4 + 8, "");
    }
    if (retVal == -1)
        retVal = CViewableBase::getPropertyName_vstatic(index, pName);
    if (retVal == -1)
    {
        for (size_t i = 0; i < allProps_camera.size(); i++)
        {
            if ((pName.size() == 0) || utils::startsWith(allProps_camera[i].name, pName.c_str()))
            {
                if ((allProps_camera[i].flags & sim_propertyinfo_deprecated) == 0)
                {
                    index--;
                    if (index == -1)
                    {
                        pName = allProps_camera[i].name;
                        retVal = 1;
                        break;
                    }
                }
            }
        }
    }
    return retVal;
}

int CCamera::getPropertyInfo(const char* ppName, int& info, std::string& infoTxt) const
{
    std::string _pName(utils::getWithoutPrefix(utils::getWithoutPrefix(ppName, "object.").c_str(), "camera."));
    const char* pName = _pName.c_str();
    int retVal = CSceneObject::getPropertyInfo(pName, info, infoTxt);
    if (retVal == -1)
        retVal = _color.getPropertyInfo(pName, info, infoTxt);
    if (retVal == -1)
        retVal = CViewableBase::getPropertyInfo_vstatic(pName, info, infoTxt);
    if (retVal == -1)
    {
        for (size_t i = 0; i < allProps_camera.size(); i++)
        {
            if (strcmp(allProps_camera[i].name, pName) == 0)
            {
                retVal = allProps_camera[i].type;
                info = allProps_camera[i].flags;
                if ((infoTxt == "") && (strcmp(allProps_camera[i].infoTxt, "") != 0))
                    infoTxt = allProps_camera[i].infoTxt;
                else
                    infoTxt = allProps_camera[i].shortInfoTxt;
                break;
            }
        }
    }
    return retVal;
}

int CCamera::getPropertyInfo_static(const char* ppName, int& info, std::string& infoTxt)
{
    std::string _pName(utils::getWithoutPrefix(utils::getWithoutPrefix(ppName, "object.").c_str(), "camera."));
    const char* pName = _pName.c_str();
    int retVal = CSceneObject::getPropertyInfo_bstatic(pName, info, infoTxt);
    if (retVal == -1)
        retVal = CColorObject::getPropertyInfo_static(pName, info, infoTxt, 1 + 4 + 8, "");
    if (retVal == -1)
        retVal = CViewableBase::getPropertyInfo_vstatic(pName, info, infoTxt);
    if (retVal == -1)
    {
        for (size_t i = 0; i < allProps_camera.size(); i++)
        {
            if (strcmp(allProps_camera[i].name, pName) == 0)
            {
                retVal = allProps_camera[i].type;
                info = allProps_camera[i].flags;
                if ((infoTxt == "") && (strcmp(allProps_camera[i].infoTxt, "") != 0))
                    infoTxt = allProps_camera[i].infoTxt;
                else
                    infoTxt = allProps_camera[i].shortInfoTxt;
                break;
            }
        }
    }
    return retVal;
}
