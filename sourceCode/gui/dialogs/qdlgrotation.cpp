#include <qdlgrotation.h>
#include <ui_qdlgrotation.h>
#include <tt.h>
#include <utils.h>
#include <app.h>
#include <simStrings.h>
#include <guiApp.h>

int CQDlgRotation::coordMode = 0; // 0=abs,1=rel to parent
double CQDlgRotation::rotAngles[3] = {0.0, 0.0, 0.0};
int CQDlgRotation::transfMode = 0; // 0=abs,1=rel to parent,2=rel to self
int CQDlgRotation::currentTab = 0; // 0=mouse rot., 1=orient., 2=rotation

int CQDlgRotation::manipulationModePermission;
int CQDlgRotation::manipulationRotationRelativeTo;
double CQDlgRotation::manipulationRotationStepSize;
bool CQDlgRotation::objectRotationSettingsLocked;

CQDlgRotation::CQDlgRotation(QWidget* parent)
    : CDlgEx(parent), ui(new Ui::CQDlgRotation)
{
    ui->setupUi(this);
    lastLastSelectionID = -1;
}

CQDlgRotation::~CQDlgRotation()
{
    delete ui;
}

void CQDlgRotation::cancelEvent()
{
    // we override this cancel event. The container window should close, not this one!!
    GuiApp::mainWindow->dlgCont->close(OBJECT_DLG);
}

void CQDlgRotation::refresh()
{
    QLineEdit* lineEditToSelect = getSelectedLineEdit();
    int editMode = GuiApp::getEditModeType();
    int lastSelID = App::currentWorld->sceneObjects->getLastSelectionHandle();
    lastLastSelectionID = lastSelID;

    ui->tabWidget->setCurrentIndex(currentTab);

    if (editMode == NO_EDIT_MODE)
    {
        bool sel = (App::currentWorld->sceneObjects->getSelectionCount() != 0);
        bool bigSel = (App::currentWorld->sceneObjects->getSelectionCount() > 1);
        _enableCoordinatePart(sel, bigSel, true);
        _enableTransformationPart(sel, sel, true);
        CSceneObject* object = App::currentWorld->sceneObjects->getLastSelectionObject();
        if (sel && (object != nullptr))
        {
            // Coordinate part:
            C3Vector euler, pos;
            if (coordMode == 0)
            {
                euler = object->getCumulativeTransformation().Q.getEulerAngles();
                pos = object->getCumulativeTransformation().X;
            }
            else
            {
                euler = object->getLocalTransformation().Q.getEulerAngles();
                pos = object->getLocalTransformation().X;
            }
            ui->qqCoordAlpha->setText(utils::getAngleString(true, euler(0)).c_str());
            ui->qqCoordBeta->setText(utils::getAngleString(true, euler(1)).c_str());
            ui->qqCoordGamma->setText(utils::getAngleString(true, euler(2)).c_str());
            ui->qqCoordWorld->setChecked(coordMode == 0);
            ui->qqCoordParent->setChecked(coordMode == 1);
            // Transformation part:
            _setValuesTransformationPart(true);
            // Manip part:
            manipulationModePermission = object->getObjectMovementPreferredAxes();
            manipulationRotationRelativeTo = object->getObjectMovementRelativity(1);
            manipulationRotationStepSize = object->getObjectMovementStepSize(1);
            objectRotationSettingsLocked = (object->getObjectMovementOptions() & (32 + 512 + 1024 + 2048)) != 0;
        }
        else
        {
            _setDefaultValuesCoordinatePart(true);
            _setDefaultValuesTransformationPart(true);
        }

        // Mouse manip part:
        ui->qqOrWorld->setEnabled((object != nullptr) && (!objectRotationSettingsLocked));
        ui->qqOrParent->setEnabled((object != nullptr) && (!objectRotationSettingsLocked));
        ui->qqOrParent->setVisible((object != nullptr) &&
                                   (manipulationRotationRelativeTo == 1)); // this mode is deprecated
        ui->qqOrOwn->setEnabled((object != nullptr) && (!objectRotationSettingsLocked));
        ui->qqOrA->setEnabled((object != nullptr) && (!objectRotationSettingsLocked));
        ui->qqOrB->setEnabled((object != nullptr) && (!objectRotationSettingsLocked));
        ui->qqOrG->setEnabled((object != nullptr) && (!objectRotationSettingsLocked));
        ui->qqOrCombo->setEnabled((object != nullptr) && (!objectRotationSettingsLocked));

        ui->qqOrWorld->setChecked((object != nullptr) && (manipulationRotationRelativeTo == 0));
        ui->qqOrParent->setChecked((object != nullptr) && (manipulationRotationRelativeTo == 1));
        ui->qqOrOwn->setChecked((object != nullptr) && (manipulationRotationRelativeTo == 2));

        ui->qqOrA->setChecked((object != nullptr) && (manipulationModePermission & 0x008));
        ui->qqOrB->setChecked((object != nullptr) && (manipulationModePermission & 0x010));
        ui->qqOrG->setChecked((object != nullptr) && (manipulationModePermission & 0x020));

        ui->qqOrCombo->clear();
        if (object != nullptr)
        {
            ui->qqOrCombo->addItem(IDS_MANIP_NONE, QVariant(-1));
            ui->qqOrCombo->addItem(IDS_DEFAULT, QVariant(0));
            ui->qqOrCombo->addItem(utils::getAngleString(false, 1.0 * degToRad).c_str(), QVariant(1000));
            ui->qqOrCombo->addItem(utils::getAngleString(false, 2.0 * degToRad).c_str(), QVariant(2000));
            ui->qqOrCombo->addItem(utils::getAngleString(false, 5.0 * degToRad).c_str(), QVariant(5000));
            ui->qqOrCombo->addItem(utils::getAngleString(false, 10.0 * degToRad).c_str(), QVariant(10000));
            ui->qqOrCombo->addItem(utils::getAngleString(false, 15.0 * degToRad).c_str(), QVariant(15000));
            ui->qqOrCombo->addItem(utils::getAngleString(false, 30.0 * degToRad).c_str(), QVariant(30000));
            ui->qqOrCombo->addItem(utils::getAngleString(false, 45.0 * degToRad).c_str(), QVariant(45000));

            if (App::currentWorld->simulation->isSimulationStopped())
            {
                if (object->getObjectMovementOptions() & 4)
                    _selectItemOfCombobox(ui->qqOrCombo, -1);
                else
                    _selectItemOfCombobox(ui->qqOrCombo,
                                          int((manipulationRotationStepSize * radToDeg + 0.0005) * 1000.0));
            }
            else
            {
                if (object->getObjectMovementOptions() & 8)
                    _selectItemOfCombobox(ui->qqOrCombo, -1);
                else
                    _selectItemOfCombobox(ui->qqOrCombo,
                                          int((manipulationRotationStepSize * radToDeg + 0.0005) * 1000.0));
            }
        }
    }
    else
    { // We are in an edit mode
        // Mouse manip part:
        ui->qqOrWorld->setEnabled(false);
        ui->qqOrWorld->setVisible(false); // this mode is deprecated
        ui->qqOrParent->setEnabled(false);
        ui->qqOrOwn->setEnabled(false);
        ui->qqOrA->setEnabled(false);
        ui->qqOrB->setEnabled(false);
        ui->qqOrG->setEnabled(false);
        ui->qqOrCombo->setEnabled(false);
        ui->qqOrWorld->setChecked(false);
        ui->qqOrParent->setChecked(false);
        ui->qqOrOwn->setChecked(false);
        ui->qqOrA->setChecked(false);
        ui->qqOrB->setChecked(false);
        ui->qqOrG->setChecked(false);
        ui->qqOrCombo->clear();

        if (editMode & (TRIANGLE_EDIT_MODE | EDGE_EDIT_MODE))
        {
            _enableCoordinatePart(false, false, true);
            _enableTransformationPart(false, false, true);
            _setDefaultValuesCoordinatePart(true);
            _setDefaultValuesTransformationPart(true);
        }
        else
        { // Vertex or path edit mode
            if (editMode & VERTEX_EDIT_MODE)
            {
                bool sel = (GuiApp::mainWindow->editModeContainer->getEditModeBufferSize() != 0);
                if (transfMode == 2)
                    transfMode = 1;

                _enableCoordinatePart(false, false, true);
                _setDefaultValuesCoordinatePart(true);
                _enableTransformationPart(sel, sel, false);
                ui->qqTransfWorld->setEnabled(sel);
                ui->qqTransfParent->setEnabled(sel);
                ui->qqTransfOwn->setEnabled(false);
                CShape* shape = GuiApp::mainWindow->editModeContainer->getEditModeShape();
                if (sel && (shape != nullptr))
                {
                    // Coordinate part:
                    int ind = GuiApp::mainWindow->editModeContainer->getLastEditModeBufferValue();
                    C3Vector pos(GuiApp::mainWindow->editModeContainer->getShapeEditMode()->getEditionVertex(ind));
                    if (coordMode == 0)
                        pos = shape->getFullCumulativeTransformation() * pos;
                    ui->qqCoordWorld->setChecked(coordMode == 0);
                    ui->qqCoordParent->setChecked(coordMode == 1);
                    // Transformation part:
                    _setValuesTransformationPart(true);
                }
                else
                    _setDefaultValuesTransformationPart(true);
            }
            if (editMode & PATH_EDIT_MODE_OLD)
            {
                bool sel = (GuiApp::mainWindow->editModeContainer->getEditModeBufferSize() != 0);
                bool bigSel = (GuiApp::mainWindow->editModeContainer->getEditModeBufferSize() > 1);

                _enableCoordinatePart(sel, bigSel, true);
                _enableTransformationPart(sel, sel, true);
                if (sel)
                {
                    CPath_old* path = GuiApp::mainWindow->editModeContainer->getEditModePath_old();
                    int ind = GuiApp::mainWindow->editModeContainer->getLastEditModeBufferValue();
                    CSimplePathPoint_old* pp =
                        GuiApp::mainWindow->editModeContainer->getEditModePathContainer_old()->getSimplePathPoint(ind);
                    if (sel && (path != nullptr) && (pp != nullptr))
                    {
                        // Coordinate part:
                        C7Vector tr(pp->getTransformation());
                        if (coordMode == 0)
                            tr = path->getFullCumulativeTransformation() * tr;
                        C3Vector euler(tr.Q.getEulerAngles());
                        ui->qqCoordAlpha->setText(utils::getAngleString(true, euler(0)).c_str());
                        ui->qqCoordBeta->setText(utils::getAngleString(true, euler(1)).c_str());
                        ui->qqCoordGamma->setText(utils::getAngleString(true, euler(2)).c_str());
                        ui->qqCoordWorld->setChecked(coordMode == 0);
                        ui->qqCoordParent->setChecked(coordMode == 1);
                        // Transformation part:
                        _setValuesTransformationPart(true);
                    }
                    else
                        _setDefaultValuesTransformationPart(true);
                }
                else
                {
                    _setDefaultValuesCoordinatePart(true);
                    _setDefaultValuesTransformationPart(true);
                }
            }
        }
    }
    selectLineEdit(lineEditToSelect);
}

void CQDlgRotation::_enableCoordinatePart(bool enableState, bool enableButtons, bool alsoRadioButtons)
{
    ui->qqCoordAlpha->setEnabled(enableState);
    ui->qqCoordBeta->setEnabled(enableState);
    ui->qqCoordGamma->setEnabled(enableState);
    ui->qqCoordApplyOr->setEnabled(enableButtons);
    if (alsoRadioButtons)
    {
        ui->qqCoordWorld->setEnabled(enableState);
        ui->qqCoordParent->setEnabled(enableState);
    }
}

void CQDlgRotation::_enableTransformationPart(bool enableState, bool enableButtons, bool alsoRadioButtons)
{
    ui->qqTransfAlpha->setEnabled(enableState);
    ui->qqTransfBeta->setEnabled(enableState);
    ui->qqTransfGamma->setEnabled(enableState);
    ui->qqTransfApplyOr->setEnabled(enableButtons);
    ui->qqTransfApplyOrX->setEnabled(enableButtons);
    ui->qqTransfApplyOrY->setEnabled(enableButtons);
    ui->qqTransfApplyOrZ->setEnabled(enableButtons);
    if (alsoRadioButtons)
    {
        ui->qqTransfWorld->setEnabled(enableState);
        ui->qqTransfParent->setEnabled(enableState);
        ui->qqTransfOwn->setEnabled(enableState);
    }
}

void CQDlgRotation::_setDefaultValuesCoordinatePart(bool alsoRadioButtons)
{
    ui->qqCoordAlpha->setText("");
    ui->qqCoordBeta->setText("");
    ui->qqCoordGamma->setText("");
    if (alsoRadioButtons)
    {
        ui->qqCoordWorld->setChecked(false);
        ui->qqCoordParent->setChecked(false);
    }
}

void CQDlgRotation::_setDefaultValuesTransformationPart(bool alsoRadioButtons)
{
    ui->qqTransfAlpha->setText("");
    ui->qqTransfBeta->setText("");
    ui->qqTransfGamma->setText("");
    if (alsoRadioButtons)
    {
        ui->qqTransfWorld->setChecked(false);
        ui->qqTransfParent->setChecked(false);
        ui->qqTransfOwn->setChecked(false);
    }
}

void CQDlgRotation::_setValuesTransformationPart(bool alsoRadioButtons)
{
    ui->qqTransfAlpha->setText(utils::getAngleString(true, rotAngles[0]).c_str());
    ui->qqTransfBeta->setText(utils::getAngleString(true, rotAngles[1]).c_str());
    ui->qqTransfGamma->setText(utils::getAngleString(true, rotAngles[2]).c_str());
    if (alsoRadioButtons)
    {
        ui->qqTransfWorld->setChecked(transfMode == 0);
        ui->qqTransfParent->setChecked(transfMode == 1);
        ui->qqTransfOwn->setChecked(transfMode == 2);
    }
}

bool CQDlgRotation::_setCoord_userUnit(double newValueInUserUnit, int index)
{
    bool retVal = false;
    int editMode = GuiApp::getEditModeType();
    CSceneObject* object = App::currentWorld->sceneObjects->getLastSelectionObject();
    if ((editMode == NO_EDIT_MODE) && (object != nullptr))
    {
        C7Vector tr;
        if (coordMode == 0)
            tr = object->getCumulativeTransformation();
        else
            tr = object->getLocalTransformation();
        tr = _getNewTransf(tr, newValueInUserUnit, index);
        SSimulationThreadCommand cmd;
        cmd.cmdId = SET_TRANSF_POSITIONTRANSLATIONGUITRIGGEREDCMD;
        cmd.intParams.push_back(App::currentWorld->sceneObjects->getLastSelectionHandle());
        cmd.intParams.push_back(coordMode);
        cmd.transfParams.push_back(tr);
        App::appendSimulationThreadCommand(cmd);
        App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
        App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
    }
    if ((editMode & PATH_EDIT_MODE_OLD) && (GuiApp::mainWindow->editModeContainer->getEditModeBufferSize() != 0) &&
        (GuiApp::mainWindow->editModeContainer->getEditModePathContainer_old() != nullptr))
    {
        CPathCont_old* pathCont = GuiApp::mainWindow->editModeContainer->getEditModePathContainer_old();
        int ind = GuiApp::mainWindow->editModeContainer->getLastEditModeBufferValue();
        CSimplePathPoint_old* pp = pathCont->getSimplePathPoint(ind);
        CPath_old* path = GuiApp::mainWindow->editModeContainer->getEditModePath_old();
        if ((pp != nullptr) && (path != nullptr))
        {
            C7Vector tr(pp->getTransformation());
            if (coordMode == 0)
                tr = path->getCumulativeTransformation() * tr;
            tr = _getNewTransf(tr, newValueInUserUnit, index);
            if (coordMode == 0)
                pp->setTransformation(path->getFullCumulativeTransformation().getInverse() * tr,
                                      pathCont->getAttributes());
            else
                pp->setTransformation(tr, pathCont->getAttributes());
            pathCont->actualizePath();
        }
        retVal = true;
    }
    if ((editMode & VERTEX_EDIT_MODE) && (GuiApp::mainWindow->editModeContainer->getEditModeBufferSize() != 0))
    {
        int ind = GuiApp::mainWindow->editModeContainer->getLastEditModeBufferValue();
        C3Vector v(GuiApp::mainWindow->editModeContainer->getShapeEditMode()->getEditionVertex(ind));
        CShape* shape = GuiApp::mainWindow->editModeContainer->getEditModeShape();
        if (shape != nullptr)
        {
            C7Vector tr;
            tr.setIdentity();
            tr.X = v;
            if (coordMode == 0)
                tr = shape->getCumulativeTransformation() * tr;
            tr = _getNewTransf(tr, newValueInUserUnit, index);
            if (coordMode == 0)
                tr = shape->getFullCumulativeTransformation().getInverse() * tr;
            GuiApp::mainWindow->editModeContainer->getShapeEditMode()->setEditionVertex(ind, tr.X);
        }
        retVal = true;
    }
    return (retVal);
}

C7Vector CQDlgRotation::_getNewTransf(const C7Vector& transf, double newValueInUserUnit, int index)
{
    C7Vector retVal(transf);
    C3Vector euler(retVal.Q.getEulerAngles());
    euler(index) = newValueInUserUnit * degToRad;
    retVal.Q.setEulerAngles(euler(0), euler(1), euler(2));
    return (retVal);
}

bool CQDlgRotation::_applyCoord()
{
    bool retVal = false;
    int editMode = GuiApp::getEditModeType();
    CSceneObject* object = App::currentWorld->sceneObjects->getLastSelectionObject();
    size_t objSelSize = App::currentWorld->sceneObjects->getSelectionCount();
    int editObjSelSize = GuiApp::mainWindow->editModeContainer->getEditModeBufferSize();
    if ((editMode == NO_EDIT_MODE) && (object != nullptr) && (objSelSize > 1))
    {
        SSimulationThreadCommand cmd;
        cmd.cmdId = APPLY_OR_ORIENTATIONROTATIONGUITRIGGEREDCMD;
        cmd.intParams.push_back(App::currentWorld->sceneObjects->getLastSelectionHandle());
        for (size_t i = 0; i < App::currentWorld->sceneObjects->getSelectionCount() - 1; i++)
            cmd.intParams.push_back(App::currentWorld->sceneObjects->getObjectHandleFromSelectionIndex(i));
        cmd.intParams.push_back(coordMode);
        App::appendSimulationThreadCommand(cmd);
        App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
        App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
    }
    if ((editMode & PATH_EDIT_MODE_OLD) && (editObjSelSize > 1) &&
        (GuiApp::mainWindow->editModeContainer->getEditModePathContainer_old() != nullptr))
    {
        CPathCont_old* pathCont = GuiApp::mainWindow->editModeContainer->getEditModePathContainer_old();
        int ind = GuiApp::mainWindow->editModeContainer->getLastEditModeBufferValue();
        CSimplePathPoint_old* pp = pathCont->getSimplePathPoint(ind);
        CPath_old* path = GuiApp::mainWindow->editModeContainer->getEditModePath_old();
        if ((pp != nullptr) && (path != nullptr))
        {
            C7Vector tr(pp->getTransformation());
            if (coordMode == 0)
                tr = path->getCumulativeTransformation() * tr;
            for (int i = 0; i < editObjSelSize - 1; i++)
            {
                CSimplePathPoint_old* ppIt =
                    GuiApp::mainWindow->editModeContainer->getPathEditMode()->getSimplePathPoint(i);
                if (ppIt != nullptr)
                {
                    C7Vector trIt(ppIt->getTransformation());
                    if (coordMode == 0)
                        trIt = path->getCumulativeTransformation() * trIt;
                    trIt.Q = tr.Q;
                    if (coordMode == 0)
                        trIt = path->getCumulativeTransformation().getInverse() * trIt;
                    ppIt->setTransformation(trIt, pathCont->getAttributes());
                }
            }
            pathCont->actualizePath();
        }
        retVal = true;
    }
    if ((editMode & VERTEX_EDIT_MODE) && (editObjSelSize > 1))
    {
        int ind = GuiApp::mainWindow->editModeContainer->getLastEditModeBufferValue();
        C3Vector v(GuiApp::mainWindow->editModeContainer->getShapeEditMode()->getEditionVertex(ind));
        CShape* shape = GuiApp::mainWindow->editModeContainer->getEditModeShape();
        if (shape != nullptr)
        {
            C7Vector tr;
            tr.setIdentity();
            tr.X = v;
            if (coordMode == 0)
                tr = shape->getCumulativeTransformation() * tr;
            for (int i = 0; i < editObjSelSize - 1; i++)
            {
                ind = GuiApp::mainWindow->editModeContainer->getEditModeBufferValue(i);
                C7Vector trIt;
                trIt.setIdentity();
                trIt.X = GuiApp::mainWindow->editModeContainer->getShapeEditMode()->getEditionVertex(ind);
                if (coordMode == 0)
                    trIt = shape->getCumulativeTransformation() * trIt;
                trIt.Q = tr.Q;
                if (coordMode == 0)
                    trIt = shape->getCumulativeTransformation().getInverse() * trIt;
                GuiApp::mainWindow->editModeContainer->getShapeEditMode()->setEditionVertex(ind, trIt.X);
            }
        }
        retVal = true;
    }
    return (retVal);
}

bool CQDlgRotation::_applyTransformation(int axis)
{ // axis: 0-2, or -1 for all axes
    bool retVal = false;
    int editMode = GuiApp::getEditModeType();
    size_t objSelSize = App::currentWorld->sceneObjects->getSelectionCount();
    int editObjSelSize = GuiApp::mainWindow->editModeContainer->getEditModeBufferSize();
    if ((editMode == NO_EDIT_MODE) && (objSelSize > 0))
    {
        double TX[3] = {0.0, 0.0, 0.0};
        if (axis == -1)
        {
            TX[0] = rotAngles[0];
            TX[1] = rotAngles[1];
            TX[2] = rotAngles[2];
        }
        else
            TX[axis] = rotAngles[axis];
        SSimulationThreadCommand cmd;
        cmd.cmdId = ROTATE_SELECTION_ORIENTATIONROTATIONGUITRIGGEREDCMD;
        for (size_t i = 0; i < App::currentWorld->sceneObjects->getSelectionCount(); i++)
            cmd.intParams.push_back(App::currentWorld->sceneObjects->getObjectHandleFromSelectionIndex(i));
        cmd.intParams.push_back(transfMode);
        cmd.doubleParams.push_back(TX[0]);
        cmd.doubleParams.push_back(TX[1]);
        cmd.doubleParams.push_back(TX[2]);
        App::appendSimulationThreadCommand(cmd);
        App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
        App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
    }
    if ((editMode & PATH_EDIT_MODE_OLD) && (editObjSelSize > 0) &&
        (GuiApp::mainWindow->editModeContainer->getEditModePathContainer_old() != nullptr))
    {
        CPathCont_old* pathCont = GuiApp::mainWindow->editModeContainer->getEditModePathContainer_old();
        CPath_old* path = GuiApp::mainWindow->editModeContainer->getEditModePath_old();
        for (int i = 0; i < editObjSelSize; i++)
        {
            CSimplePathPoint_old* pp = GuiApp::mainWindow->editModeContainer->getPathEditMode()->getSimplePathPoint(i);
            if ((pp != nullptr) && (path != nullptr))
            {
                C7Vector tr(pp->getTransformation());
                if (transfMode == 0)
                    tr = path->getCumulativeTransformation() * tr;
                _transform(tr, transfMode == 2, axis);
                if (transfMode == 0)
                    tr = path->getCumulativeTransformation().getInverse() * tr;
                pp->setTransformation(tr, pathCont->getAttributes());
            }
        }
        pathCont->actualizePath();
        retVal = true;
    }
    if ((editMode & VERTEX_EDIT_MODE) && (editObjSelSize > 0))
    {
        CShape* shape = GuiApp::mainWindow->editModeContainer->getEditModeShape();
        if (shape != nullptr)
        {
            for (int i = 0; i < editObjSelSize; i++)
            {
                C7Vector tr;
                tr.setIdentity();
                int ind = GuiApp::mainWindow->editModeContainer->getEditModeBufferValue(i);
                tr.X = GuiApp::mainWindow->editModeContainer->getShapeEditMode()->getEditionVertex(ind);
                if (transfMode == 0)
                    tr = shape->getCumulativeTransformation() * tr;
                _transform(tr, transfMode == 2, axis);
                if (transfMode == 0)
                    tr = shape->getCumulativeTransformation().getInverse() * tr;
                GuiApp::mainWindow->editModeContainer->getShapeEditMode()->setEditionVertex(ind, tr.X);
            }
        }
        retVal = true;
    }
    return (retVal);
}

void CQDlgRotation::_transform(C7Vector& tr, bool self, int axis)
{ // axis: 0-2, or -1 for all axes
    double TX[3] = {0.0, 0.0, 0.0};
    if (axis == -1)
    {
        TX[0] = rotAngles[0];
        TX[1] = rotAngles[1];
        TX[2] = rotAngles[2];
    }
    else
        TX[axis] = rotAngles[axis];
    C7Vector m;
    m.setIdentity();
    m.Q.setEulerAngles(TX[0], TX[1], TX[2]);
    if (self)
        tr = tr * m;
    else
        tr = m * tr;
}

void CQDlgRotation::on_qqCoordWorld_clicked()
{
    IF_UI_EVENT_CAN_READ_DATA
    {
        coordMode = 0;
        refresh();
    }
}

void CQDlgRotation::on_qqCoordParent_clicked()
{
    IF_UI_EVENT_CAN_READ_DATA
    {
        coordMode = 1;
        refresh();
    }
}

void CQDlgRotation::on_qqCoordAlpha_editingFinished()
{
    if (!ui->qqCoordAlpha->isModified())
        return;
    IF_UI_EVENT_CAN_READ_DATA
    {
        bool ok;
        double newVal = GuiApp::getEvalDouble(ui->qqCoordAlpha->text().toStdString().c_str(), &ok);
        if (ok)
            _setCoord_userUnit(newVal, 0);
        refresh();
    }
}

void CQDlgRotation::on_qqCoordBeta_editingFinished()
{
    if (!ui->qqCoordBeta->isModified())
        return;
    IF_UI_EVENT_CAN_READ_DATA
    {
        bool ok;
        double newVal = GuiApp::getEvalDouble(ui->qqCoordBeta->text().toStdString().c_str(), &ok);
        if (ok)
            _setCoord_userUnit(newVal, 1);
        refresh();
    }
}

void CQDlgRotation::on_qqCoordGamma_editingFinished()
{
    if (!ui->qqCoordGamma->isModified())
        return;
    IF_UI_EVENT_CAN_READ_DATA
    {
        bool ok;
        double newVal = GuiApp::getEvalDouble(ui->qqCoordGamma->text().toStdString().c_str(), &ok);
        if (ok)
            _setCoord_userUnit(newVal, 2);
        refresh();
    }
}

void CQDlgRotation::on_qqCoordApplyOr_clicked()
{
    IF_UI_EVENT_CAN_READ_DATA
    {
        if (_applyCoord())
            refresh();
    }
}

void CQDlgRotation::on_qqTransfWorld_clicked()
{
    IF_UI_EVENT_CAN_READ_DATA
    {
        transfMode = 0;
        refresh();
    }
}

void CQDlgRotation::on_qqTransfParent_clicked()
{
    IF_UI_EVENT_CAN_READ_DATA
    {
        transfMode = 1;
        refresh();
    }
}

void CQDlgRotation::on_qqTransfOwn_clicked()
{
    IF_UI_EVENT_CAN_READ_DATA
    {
        transfMode = 2;
        refresh();
    }
}

void CQDlgRotation::on_qqTransfAlpha_editingFinished()
{
    if (!ui->qqTransfAlpha->isModified())
        return;
    IF_UI_EVENT_CAN_READ_DATA
    {
        bool ok;
        double newVal = GuiApp::getEvalDouble(ui->qqTransfAlpha->text().toStdString().c_str(), &ok);
        if (ok)
        {
            newVal *= degToRad;
            newVal = fmod(newVal, piValT2);
            rotAngles[0] = newVal;
        }
        refresh();
    }
}

void CQDlgRotation::on_qqTransfBeta_editingFinished()
{
    if (!ui->qqTransfBeta->isModified())
        return;
    IF_UI_EVENT_CAN_READ_DATA
    {
        bool ok;
        double newVal = GuiApp::getEvalDouble(ui->qqTransfBeta->text().toStdString().c_str(), &ok);
        if (ok)
        {
            newVal *= degToRad;
            newVal = fmod(newVal, piValT2);
            rotAngles[1] = newVal;
        }
        refresh();
    }
}

void CQDlgRotation::on_qqTransfGamma_editingFinished()
{
    if (!ui->qqTransfGamma->isModified())
        return;
    IF_UI_EVENT_CAN_READ_DATA
    {
        bool ok;
        double newVal = GuiApp::getEvalDouble(ui->qqTransfGamma->text().toStdString().c_str(), &ok);
        if (ok)
        {
            newVal *= degToRad;
            newVal = fmod(newVal, piValT2);
            rotAngles[2] = newVal;
        }
        refresh();
    }
}

void CQDlgRotation::on_qqTransfApplyOr_clicked()
{
    IF_UI_EVENT_CAN_READ_DATA
    {
        if (_applyTransformation(-1))
            refresh();
    }
}

void CQDlgRotation::on_qqTransfApplyOrX_clicked()
{
    IF_UI_EVENT_CAN_READ_DATA
    {
        if (_applyTransformation(0))
            refresh();
    }
}

void CQDlgRotation::on_qqTransfApplyOrY_clicked()
{
    IF_UI_EVENT_CAN_READ_DATA
    {
        if (_applyTransformation(1))
            refresh();
    }
}

void CQDlgRotation::on_qqTransfApplyOrZ_clicked()
{
    IF_UI_EVENT_CAN_READ_DATA
    {
        if (_applyTransformation(2))
            refresh();
    }
}

void CQDlgRotation::on_tabWidget_currentChanged(int index)
{
    currentTab = index;
}

void CQDlgRotation::on_qqOrWorld_clicked()
{ // mouse manip
    IF_UI_EVENT_CAN_READ_DATA
    {
        App::appendSimulationThreadCommand(SET_ORRELATIVETO_OBJECTMANIPGUITRIGGEREDCMD,
                                           App::currentWorld->sceneObjects->getLastSelectionHandle(), 0);
        App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
        App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
    }
}

void CQDlgRotation::on_qqOrParent_clicked()
{ // mouse manip
    IF_UI_EVENT_CAN_READ_DATA
    {
        App::appendSimulationThreadCommand(SET_ORRELATIVETO_OBJECTMANIPGUITRIGGEREDCMD,
                                           App::currentWorld->sceneObjects->getLastSelectionHandle(), 1);
        App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
        App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
    }
}

void CQDlgRotation::on_qqOrOwn_clicked()
{ // mouse manip
    IF_UI_EVENT_CAN_READ_DATA
    {
        App::appendSimulationThreadCommand(SET_ORRELATIVETO_OBJECTMANIPGUITRIGGEREDCMD,
                                           App::currentWorld->sceneObjects->getLastSelectionHandle(), 2);
        App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
        App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
    }
}

void CQDlgRotation::on_qqOrA_clicked()
{ // mouse manip
    IF_UI_EVENT_CAN_READ_DATA
    {
        CSceneObject* object = App::currentWorld->sceneObjects->getLastSelectionObject();
        if (object != nullptr)
        {
            int permission = object->getObjectMovementPreferredAxes();
            permission = (permission & 0x07) | 0x08;
            App::appendSimulationThreadCommand(SET_PERMISSIONS_OBJECTMANIPGUITRIGGEREDCMD,
                                               App::currentWorld->sceneObjects->getLastSelectionHandle(), permission);
            App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
        }
        App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
    }
}

void CQDlgRotation::on_qqOrB_clicked()
{ // mouse manip
    IF_UI_EVENT_CAN_READ_DATA
    {
        CSceneObject* object = App::currentWorld->sceneObjects->getLastSelectionObject();
        if (object != nullptr)
        {
            int permission = object->getObjectMovementPreferredAxes();
            permission = (permission & 0x07) | 0x10;
            App::appendSimulationThreadCommand(SET_PERMISSIONS_OBJECTMANIPGUITRIGGEREDCMD,
                                               App::currentWorld->sceneObjects->getLastSelectionHandle(), permission);
            App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
        }
        App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
    }
}

void CQDlgRotation::on_qqOrG_clicked()
{ // mouse manip
    IF_UI_EVENT_CAN_READ_DATA
    {
        CSceneObject* object = App::currentWorld->sceneObjects->getLastSelectionObject();
        if (object != nullptr)
        {
            int permission = object->getObjectMovementPreferredAxes();
            permission = (permission & 0x07) | 0x20;
            App::appendSimulationThreadCommand(SET_PERMISSIONS_OBJECTMANIPGUITRIGGEREDCMD,
                                               App::currentWorld->sceneObjects->getLastSelectionHandle(), permission);
            App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
        }
        App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
    }
}

void CQDlgRotation::on_qqOrCombo_activated(int index)
{ // mouse manip
    IF_UI_EVENT_CAN_READ_DATA
    {
        App::appendSimulationThreadCommand(SET_ORSTEPSIZE_OBJECTMANIPGUITRIGGEREDCMD,
                                           App::currentWorld->sceneObjects->getLastSelectionHandle(), -1,
                                           double(ui->qqOrCombo->itemData(index).toInt()) * degToRad / 1000.0);
        App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
        App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
    }
}

void CQDlgRotation::_selectItemOfCombobox(QComboBox* theBox, int itemData)
{
    theBox->setCurrentIndex(_getIndexOfComboboxItemWithData(theBox, itemData));
}

int CQDlgRotation::_getIndexOfComboboxItemWithData(QComboBox* theBox, int itemData)
{
    for (int i = 0; i < theBox->count(); i++)
    {
        if (theBox->itemData(i).toInt() == itemData)
            return (i);
    }
    return (-1);
}
