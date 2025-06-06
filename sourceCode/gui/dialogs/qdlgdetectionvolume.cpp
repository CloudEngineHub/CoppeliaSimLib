#include <qdlgdetectionvolume.h>
#include <ui_qdlgdetectionvolume.h>
#include <tt.h>
#include <utils.h>
#include <app.h>
#include <simStrings.h>
#include <guiApp.h>

bool CQDlgDetectionVolume::showVolumeWindow = false;

CQDlgDetectionVolume::CQDlgDetectionVolume(QWidget* parent)
    : CDlgEx(parent), ui(new Ui::CQDlgDetectionVolume)
{
    _dlgType = DETECTION_VOLUME_DLG;
    ui->setupUi(this);
    inMainRefreshRoutine = false;
}

CQDlgDetectionVolume::~CQDlgDetectionVolume()
{
    delete ui;
}

void CQDlgDetectionVolume::cancelEvent()
{ // no cancel event allowed
    showVolumeWindow = false;
    CDlgEx::cancelEvent();
    GuiApp::setFullDialogRefreshFlag();
}

void CQDlgDetectionVolume::refresh()
{
    inMainRefreshRoutine = true;
    QLineEdit* lineEditToSelect = getSelectedLineEdit();

    bool noEditModeNoSim =
        (GuiApp::getEditModeType() == NO_EDIT_MODE) && App::currentWorld->simulation->isSimulationStopped();

    bool prox = App::currentWorld->sceneObjects->isLastSelectionOfType(sim_sceneobject_proximitysensor);
    bool mill = App::currentWorld->sceneObjects->isLastSelectionOfType(sim_sceneobject_mill);
    bool ssel = false;
    if (prox)
        ssel = (App::currentWorld->sceneObjects->getObjectCountInSelection(sim_sceneobject_proximitysensor) > 1);
    if (mill)
        ssel = (App::currentWorld->sceneObjects->getObjectCountInSelection(sim_sceneobject_mill) > 1);
    CConvexVolume* cv = nullptr;
    CProxSensor* proxIt = App::currentWorld->sceneObjects->getLastSelectionProxSensor();
    CMill* millIt = App::currentWorld->sceneObjects->getLastSelectionMill();
    if (prox)
        cv = proxIt->convexVolume;
    if (mill)
        cv = millIt->convexVolume;

    ui->qqApplyAll->setEnabled(ssel && noEditModeNoSim);

    if (prox || mill)
    {
        if (prox)
        {
            setWindowTitle(IDSN_DETECTION_VOLUME_PROPERTIES);

            ui->qqOffset->setEnabled(noEditModeNoSim);
            if ((proxIt->getSensorType() == sim_proximitysensor_ray) && proxIt->getRandomizedDetection())
                ui->qqOffset->setText(utils::getPosString(true, cv->getRadius()).c_str()); // Special
            else
                ui->qqOffset->setText(utils::getPosString(true, cv->getOffset()).c_str());
            ui->qqRange->setEnabled(noEditModeNoSim);
            ui->qqRange->setText(utils::getSizeString(false, cv->getRange()).c_str());
            if (proxIt->getSensorType() == sim_proximitysensor_pyramid)
            {
                ui->qqSizeX->setEnabled(noEditModeNoSim);
                ui->qqSizeX->setText(utils::getSizeString(false, cv->getXSize()).c_str());
                ui->qqSizeY->setEnabled(noEditModeNoSim);
                ui->qqSizeY->setText(utils::getSizeString(false, cv->getYSize()).c_str());
                ui->qqSizeFarX->setEnabled(noEditModeNoSim);
                ui->qqSizeFarX->setText(utils::getSizeString(false, cv->getXSizeFar()).c_str());
                ui->qqSizeFarY->setEnabled(noEditModeNoSim);
                ui->qqSizeFarY->setText(utils::getSizeString(false, cv->getYSizeFar()).c_str());

                ui->qqRadius->setEnabled(false);
                ui->qqRadius->setText("");
                ui->qqRadiusFar->setEnabled(false);
                ui->qqRadiusFar->setText("");

                ui->qqAngle->setEnabled(false);
                ui->qqAngle->setText("");

                ui->qqFaceCount->setEnabled(false);
                ui->qqFaceCount->setText("");
                ui->qqFaceCountFar->setEnabled(false);
                ui->qqFaceCountFar->setText("");

                ui->qqSubdivisions->setEnabled(false);
                ui->qqSubdivisions->setText("");
                ui->qqSubdivisionsFar->setEnabled(false);
                ui->qqSubdivisionsFar->setText("");

                ui->qqInsideGap->setEnabled(false);
                ui->qqInsideGap->setText("");
            }
            if (proxIt->getSensorType() == sim_proximitysensor_cylinder)
            {
                ui->qqRadius->setEnabled(noEditModeNoSim);
                ui->qqRadius->setText(utils::getSizeString(false, cv->getRadius()).c_str());
                ui->qqRadiusFar->setEnabled(noEditModeNoSim);
                ui->qqRadiusFar->setText(utils::getSizeString(false, cv->getRadiusFar()).c_str());
                ui->qqFaceCount->setEnabled(noEditModeNoSim);
                ui->qqFaceCount->setText(utils::getIntString(false, cv->getFaceNumber()).c_str());

                ui->qqAngle->setEnabled(false);
                ui->qqAngle->setText("");

                ui->qqSizeX->setEnabled(false);
                ui->qqSizeX->setText("");
                ui->qqSizeY->setEnabled(false);
                ui->qqSizeY->setText("");
                ui->qqSizeFarX->setEnabled(false);
                ui->qqSizeFarX->setText("");
                ui->qqSizeFarY->setEnabled(false);
                ui->qqSizeFarY->setText("");

                ui->qqFaceCountFar->setEnabled(false);
                ui->qqFaceCountFar->setText("");

                ui->qqSubdivisions->setEnabled(false);
                ui->qqSubdivisions->setText("");
                ui->qqSubdivisionsFar->setEnabled(false);
                ui->qqSubdivisionsFar->setText("");

                ui->qqInsideGap->setEnabled(false);
                ui->qqInsideGap->setText("");
            }
            if (proxIt->getSensorType() == sim_proximitysensor_ray)
            {
                ui->qqAngle->setEnabled(proxIt->getRandomizedDetection() && noEditModeNoSim);
                if (proxIt->getRandomizedDetection())
                    ui->qqAngle->setText(utils::getAngleString(false, cv->getAngle()).c_str());
                else
                    ui->qqAngle->setText("");

                ui->qqRadius->setEnabled(false);
                ui->qqRadius->setText("");
                ui->qqRadiusFar->setEnabled(false);
                ui->qqRadiusFar->setText("");

                ui->qqSizeX->setEnabled(false);
                ui->qqSizeX->setText("");
                ui->qqSizeY->setEnabled(false);
                ui->qqSizeY->setText("");
                ui->qqSizeFarX->setEnabled(false);
                ui->qqSizeFarX->setText("");
                ui->qqSizeFarY->setEnabled(false);
                ui->qqSizeFarY->setText("");

                ui->qqFaceCount->setEnabled(false);
                ui->qqFaceCount->setText("");
                ui->qqFaceCountFar->setEnabled(false);
                ui->qqFaceCountFar->setText("");

                ui->qqSubdivisions->setEnabled(false);
                ui->qqSubdivisions->setText("");
                ui->qqSubdivisionsFar->setEnabled(false);
                ui->qqSubdivisionsFar->setText("");

                ui->qqInsideGap->setEnabled(false);
                ui->qqInsideGap->setText("");
            }
            if (proxIt->getSensorType() == sim_proximitysensor_disc)
            {
                ui->qqSizeY->setEnabled(noEditModeNoSim);
                ui->qqSizeY->setText(utils::getSizeString(false, cv->getYSize()).c_str());
                ui->qqRadius->setEnabled(noEditModeNoSim);
                ui->qqRadius->setText(utils::getSizeString(false, cv->getRadius()).c_str());
                ui->qqFaceCount->setEnabled(noEditModeNoSim);
                ui->qqFaceCount->setText(utils::getIntString(false, cv->getFaceNumber()).c_str());
                ui->qqFaceCountFar->setEnabled(noEditModeNoSim);
                ui->qqFaceCountFar->setText(utils::getIntString(false, cv->getFaceNumberFar()).c_str());
                ui->qqAngle->setEnabled(noEditModeNoSim);
                ui->qqAngle->setText(utils::getAngleString(false, cv->getAngle()).c_str());
                ui->qqInsideGap->setEnabled(noEditModeNoSim);
                ui->qqInsideGap->setText(utils::get0To1String(false, cv->getInsideAngleThing()).c_str());

                ui->qqRadiusFar->setEnabled(false);
                ui->qqRadiusFar->setText("");

                ui->qqSizeX->setEnabled(false);
                ui->qqSizeX->setText("");
                ui->qqSizeFarX->setEnabled(false);
                ui->qqSizeFarX->setText("");
                ui->qqSizeFarY->setEnabled(false);
                ui->qqSizeFarY->setText("");

                ui->qqSubdivisions->setEnabled(false);
                ui->qqSubdivisions->setText("");
                ui->qqSubdivisionsFar->setEnabled(false);
                ui->qqSubdivisionsFar->setText("");
            }
            if (proxIt->getSensorType() == sim_proximitysensor_cone)
            {
                ui->qqRadius->setEnabled(noEditModeNoSim);
                ui->qqRadius->setText(utils::getSizeString(false, cv->getRadius()).c_str());
                ui->qqFaceCount->setEnabled(noEditModeNoSim);
                ui->qqFaceCount->setText(utils::getIntString(false, cv->getFaceNumber()).c_str());
                ui->qqAngle->setEnabled(noEditModeNoSim);
                ui->qqAngle->setText(utils::getAngleString(false, cv->getAngle()).c_str());
                ui->qqInsideGap->setEnabled(noEditModeNoSim);
                ui->qqInsideGap->setText(utils::get0To1String(false, cv->getInsideAngleThing()).c_str());
                ui->qqSubdivisions->setEnabled(noEditModeNoSim);
                ui->qqSubdivisions->setText(utils::getIntString(false, cv->getSubdivisions()).c_str());
                ui->qqSubdivisionsFar->setEnabled(noEditModeNoSim);
                ui->qqSubdivisionsFar->setText(utils::getIntString(false, cv->getSubdivisionsFar()).c_str());

                ui->qqRadiusFar->setEnabled(false);
                ui->qqRadiusFar->setText("");

                ui->qqSizeX->setEnabled(false);
                ui->qqSizeX->setText("");
                ui->qqSizeY->setEnabled(false);
                ui->qqSizeY->setText("");
                ui->qqSizeFarX->setEnabled(false);
                ui->qqSizeFarX->setText("");
                ui->qqSizeFarY->setEnabled(false);
                ui->qqSizeFarY->setText("");

                ui->qqFaceCountFar->setEnabled(false);
                ui->qqFaceCountFar->setText("");
            }
        }

        if (mill)
        {
            setWindowTitle(IDSN_CUTTING_VOLUME_PROPERTIES);
            ui->qqInsideGap->setEnabled(false);
            ui->qqInsideGap->setText("");
            ui->qqSubdivisions->setEnabled(false);
            ui->qqSubdivisions->setText("");

            ui->qqOffset->setEnabled(noEditModeNoSim);
            ui->qqOffset->setText(utils::getPosString(true, cv->getOffset()).c_str());
            ui->qqRange->setEnabled(noEditModeNoSim);
            ui->qqRange->setText(utils::getSizeString(false, cv->getRange()).c_str());
            if (millIt->getMillType() == sim_mill_pyramid_subtype)
            {
                ui->qqSizeX->setEnabled(noEditModeNoSim);
                ui->qqSizeX->setText(utils::getSizeString(false, cv->getXSize()).c_str());
                ui->qqSizeY->setEnabled(noEditModeNoSim);
                ui->qqSizeY->setText(utils::getSizeString(false, cv->getYSize()).c_str());
                ui->qqSizeFarX->setEnabled(noEditModeNoSim);
                ui->qqSizeFarX->setText(utils::getSizeString(false, cv->getXSizeFar()).c_str());
                ui->qqSizeFarY->setEnabled(noEditModeNoSim);
                ui->qqSizeFarY->setText(utils::getSizeString(false, cv->getYSizeFar()).c_str());

                ui->qqRadius->setEnabled(false);
                ui->qqRadius->setText("");
                ui->qqRadiusFar->setEnabled(false);
                ui->qqRadiusFar->setText("");

                ui->qqAngle->setEnabled(false);
                ui->qqAngle->setText("");

                ui->qqFaceCount->setEnabled(false);
                ui->qqFaceCount->setText("");
                ui->qqFaceCountFar->setEnabled(false);
                ui->qqFaceCountFar->setText("");

                ui->qqSubdivisions->setEnabled(false);
                ui->qqSubdivisions->setText("");
                ui->qqSubdivisionsFar->setEnabled(false);
                ui->qqSubdivisionsFar->setText("");

                ui->qqInsideGap->setEnabled(false);
                ui->qqInsideGap->setText("");
            }
            if (millIt->getMillType() == sim_mill_cylinder_subtype)
            {
                ui->qqRadius->setEnabled(noEditModeNoSim);
                ui->qqRadius->setText(utils::getSizeString(false, cv->getRadius()).c_str());
                ui->qqRadiusFar->setEnabled(noEditModeNoSim);
                ui->qqRadiusFar->setText(utils::getSizeString(false, cv->getRadiusFar()).c_str());
                ui->qqFaceCount->setEnabled(noEditModeNoSim);
                ui->qqFaceCount->setText(utils::getIntString(false, cv->getFaceNumber()).c_str());

                ui->qqAngle->setEnabled(false);
                ui->qqAngle->setText("");

                ui->qqSizeX->setEnabled(false);
                ui->qqSizeX->setText("");
                ui->qqSizeY->setEnabled(false);
                ui->qqSizeY->setText("");
                ui->qqSizeFarX->setEnabled(false);
                ui->qqSizeFarX->setText("");
                ui->qqSizeFarY->setEnabled(false);
                ui->qqSizeFarY->setText("");

                ui->qqFaceCountFar->setEnabled(false);
                ui->qqFaceCountFar->setText("");

                ui->qqSubdivisions->setEnabled(false);
                ui->qqSubdivisions->setText("");
                ui->qqSubdivisionsFar->setEnabled(false);
                ui->qqSubdivisionsFar->setText("");

                ui->qqInsideGap->setEnabled(false);
                ui->qqInsideGap->setText("");
            }
            if (millIt->getMillType() == sim_mill_disc_subtype)
            {
                ui->qqSizeY->setEnabled(noEditModeNoSim);
                ui->qqSizeY->setText(utils::getSizeString(false, cv->getYSize()).c_str());
                ui->qqFaceCountFar->setEnabled(noEditModeNoSim);
                ui->qqFaceCountFar->setText(utils::getIntString(false, cv->getFaceNumberFar()).c_str());
                ui->qqAngle->setEnabled(noEditModeNoSim);
                ui->qqAngle->setText(utils::getAngleString(false, cv->getAngle()).c_str());

                ui->qqRadius->setEnabled(false);
                ui->qqRadius->setText("");
                ui->qqRadiusFar->setEnabled(false);
                ui->qqRadiusFar->setText("");

                ui->qqSizeX->setEnabled(false);
                ui->qqSizeX->setText("");
                ui->qqSizeFarX->setEnabled(false);
                ui->qqSizeFarX->setText("");
                ui->qqSizeFarY->setEnabled(false);
                ui->qqSizeFarY->setText("");

                ui->qqFaceCount->setEnabled(false);
                ui->qqFaceCount->setText("");

                ui->qqSubdivisions->setEnabled(false);
                ui->qqSubdivisions->setText("");
                ui->qqSubdivisionsFar->setEnabled(false);
                ui->qqSubdivisionsFar->setText("");

                ui->qqInsideGap->setEnabled(false);
                ui->qqInsideGap->setText("");
            }
            if (millIt->getMillType() == sim_mill_cone_subtype)
            {
                ui->qqFaceCount->setEnabled(noEditModeNoSim);
                ui->qqFaceCount->setText(utils::getIntString(false, cv->getFaceNumber()).c_str());
                ui->qqAngle->setEnabled(noEditModeNoSim);
                ui->qqAngle->setText(utils::getAngleString(false, cv->getAngle()).c_str());
                ui->qqSubdivisionsFar->setEnabled(noEditModeNoSim);
                ui->qqSubdivisionsFar->setText(utils::getIntString(false, cv->getSubdivisionsFar()).c_str());

                ui->qqRadius->setEnabled(false);
                ui->qqRadius->setText("");
                ui->qqRadiusFar->setEnabled(false);
                ui->qqRadiusFar->setText("");

                ui->qqSizeX->setEnabled(false);
                ui->qqSizeX->setText("");
                ui->qqSizeY->setEnabled(false);
                ui->qqSizeY->setText("");
                ui->qqSizeFarX->setEnabled(false);
                ui->qqSizeFarX->setText("");
                ui->qqSizeFarY->setEnabled(false);
                ui->qqSizeFarY->setText("");

                ui->qqFaceCountFar->setEnabled(false);
                ui->qqFaceCountFar->setText("");

                ui->qqSubdivisions->setEnabled(false);
                ui->qqSubdivisions->setText("");

                ui->qqInsideGap->setEnabled(false);
                ui->qqInsideGap->setText("");
            }
        }
    }
    else
    {
        setWindowTitle(IDSN_VOLUME_PROPERTIES);
        ui->qqOffset->setEnabled(false);
        ui->qqOffset->setText("");
        ui->qqRange->setEnabled(false);
        ui->qqRange->setText("");

        ui->qqRadius->setEnabled(false);
        ui->qqRadius->setText("");
        ui->qqRadiusFar->setEnabled(false);
        ui->qqRadiusFar->setText("");

        ui->qqAngle->setEnabled(false);
        ui->qqAngle->setText("");

        ui->qqSizeX->setEnabled(false);
        ui->qqSizeX->setText("");
        ui->qqSizeY->setEnabled(false);
        ui->qqSizeY->setText("");
        ui->qqSizeFarX->setEnabled(false);
        ui->qqSizeFarX->setText("");
        ui->qqSizeFarY->setEnabled(false);
        ui->qqSizeFarY->setText("");

        ui->qqFaceCount->setEnabled(false);
        ui->qqFaceCount->setText("");
        ui->qqFaceCountFar->setEnabled(false);
        ui->qqFaceCountFar->setText("");

        ui->qqSubdivisions->setEnabled(false);
        ui->qqSubdivisions->setText("");
        ui->qqSubdivisionsFar->setEnabled(false);
        ui->qqSubdivisionsFar->setText("");

        ui->qqInsideGap->setEnabled(false);
        ui->qqInsideGap->setText("");
    }

    selectLineEdit(lineEditToSelect);
    inMainRefreshRoutine = false;
}

CConvexVolume* CQDlgDetectionVolume::getCurrentConvexVolume()
{
    CConvexVolume* cv = nullptr;
    CProxSensor* proxIt = App::currentWorld->sceneObjects->getLastSelectionProxSensor();
    CMill* millIt = App::currentWorld->sceneObjects->getLastSelectionMill();
    if (proxIt != nullptr)
        cv = proxIt->convexVolume;
    if (millIt != nullptr)
        cv = millIt->convexVolume;
    return (cv);
}

void CQDlgDetectionVolume::on_qqOffset_editingFinished()
{
    if (!ui->qqOffset->isModified())
        return;
    IF_UI_EVENT_CAN_WRITE_DATA
    {
        CProxSensor* proxSensor = App::currentWorld->sceneObjects->getLastSelectionProxSensor();
        CMill* mill = App::currentWorld->sceneObjects->getLastSelectionMill();
        CConvexVolume* cv = getCurrentConvexVolume();
        bool ok;
        double newVal = GuiApp::getEvalDouble(ui->qqOffset->text().toStdString().c_str(), &ok);
        if (ok && cv && (proxSensor != nullptr))
        {
            // special here:
            if ((proxSensor->getSensorType() == sim_proximitysensor_ray) &&
                proxSensor->getRandomizedDetection())
                App::appendSimulationThreadCommand(SET_RADIUS_DETECTIONVOLUMEGUITRIGGEREDCMD,
                                                   App::currentWorld->sceneObjects->getLastSelectionHandle(), -1,
                                                   newVal);
            else
                App::appendSimulationThreadCommand(SET_OFFSET_DETECTIONVOLUMEGUITRIGGEREDCMD,
                                                   App::currentWorld->sceneObjects->getLastSelectionHandle(), -1,
                                                   newVal);
            App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
        }
        if (ok && cv && (mill != nullptr))
        {
            App::appendSimulationThreadCommand(SET_OFFSET_DETECTIONVOLUMEGUITRIGGEREDCMD,
                                               App::currentWorld->sceneObjects->getLastSelectionHandle(), -1, newVal);
            App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
        }
        App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
    }
}

void CQDlgDetectionVolume::on_qqRadius_editingFinished()
{
    if (!ui->qqRadius->isModified())
        return;
    IF_UI_EVENT_CAN_WRITE_DATA
    {
        CConvexVolume* cv = getCurrentConvexVolume();
        bool ok;
        double newVal = GuiApp::getEvalDouble(ui->qqRadius->text().toStdString().c_str(), &ok);
        if (ok && cv)
        {
            App::appendSimulationThreadCommand(SET_RADIUS_DETECTIONVOLUMEGUITRIGGEREDCMD,
                                               App::currentWorld->sceneObjects->getLastSelectionHandle(), -1, newVal);
            App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
        }
        App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
    }
}

void CQDlgDetectionVolume::on_qqRange_editingFinished()
{
    if (!ui->qqRange->isModified())
        return;
    IF_UI_EVENT_CAN_WRITE_DATA
    {
        CConvexVolume* cv = getCurrentConvexVolume();
        bool ok;
        double newVal = GuiApp::getEvalDouble(ui->qqRange->text().toStdString().c_str(), &ok);
        if (ok && cv)
        {
            App::appendSimulationThreadCommand(SET_RANGE_DETECTIONVOLUMEGUITRIGGEREDCMD,
                                               App::currentWorld->sceneObjects->getLastSelectionHandle(), -1, newVal);
            App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
        }
        App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
    }
}

void CQDlgDetectionVolume::on_qqRadiusFar_editingFinished()
{
    if (!ui->qqRadiusFar->isModified())
        return;
    IF_UI_EVENT_CAN_WRITE_DATA
    {
        CConvexVolume* cv = getCurrentConvexVolume();
        bool ok;
        double newVal = GuiApp::getEvalDouble(ui->qqRadiusFar->text().toStdString().c_str(), &ok);
        if (ok && cv)
        {
            App::appendSimulationThreadCommand(SET_RADIUSFAR_DETECTIONVOLUMEGUITRIGGEREDCMD,
                                               App::currentWorld->sceneObjects->getLastSelectionHandle(), -1, newVal);
            App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
        }
        App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
    }
}

void CQDlgDetectionVolume::on_qqSizeX_editingFinished()
{
    if (!ui->qqSizeX->isModified())
        return;
    IF_UI_EVENT_CAN_WRITE_DATA
    {
        CConvexVolume* cv = getCurrentConvexVolume();
        bool ok;
        double newVal = GuiApp::getEvalDouble(ui->qqSizeX->text().toStdString().c_str(), &ok);
        if (ok && cv)
        {
            App::appendSimulationThreadCommand(SET_XSIZE_DETECTIONVOLUMEGUITRIGGEREDCMD,
                                               App::currentWorld->sceneObjects->getLastSelectionHandle(), -1, newVal);
            App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
        }
        App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
    }
}

void CQDlgDetectionVolume::on_qqAngle_editingFinished()
{
    if (!ui->qqAngle->isModified())
        return;
    IF_UI_EVENT_CAN_WRITE_DATA
    {
        CConvexVolume* cv = getCurrentConvexVolume();
        bool ok;
        double newVal = GuiApp::getEvalDouble(ui->qqAngle->text().toStdString().c_str(), &ok);
        if (ok && cv)
        {
            App::appendSimulationThreadCommand(SET_ANGLE_DETECTIONVOLUMEGUITRIGGEREDCMD,
                                               App::currentWorld->sceneObjects->getLastSelectionHandle(), -1,
                                               newVal * degToRad);
            App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
        }
        App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
    }
}

void CQDlgDetectionVolume::on_qqSizeY_editingFinished()
{
    if (!ui->qqSizeY->isModified())
        return;
    IF_UI_EVENT_CAN_WRITE_DATA
    {
        CConvexVolume* cv = getCurrentConvexVolume();
        bool ok;
        double newVal = GuiApp::getEvalDouble(ui->qqSizeY->text().toStdString().c_str(), &ok);
        if (ok && cv)
        {
            App::appendSimulationThreadCommand(SET_YSIZE_DETECTIONVOLUMEGUITRIGGEREDCMD,
                                               App::currentWorld->sceneObjects->getLastSelectionHandle(), -1, newVal);
            App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
        }
        App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
    }
}

void CQDlgDetectionVolume::on_qqFaceCount_editingFinished()
{
    if (!ui->qqFaceCount->isModified())
        return;
    IF_UI_EVENT_CAN_WRITE_DATA
    {
        CConvexVolume* cv = getCurrentConvexVolume();
        bool ok;
        int newVal = (int)GuiApp::getEvalInt(ui->qqFaceCount->text().toStdString().c_str(), &ok);
        if (ok && cv)
        {
            App::appendSimulationThreadCommand(SET_FACECOUNT_DETECTIONVOLUMEGUITRIGGEREDCMD,
                                               App::currentWorld->sceneObjects->getLastSelectionHandle(), newVal);
            App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
        }
        App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
    }
}

void CQDlgDetectionVolume::on_qqSizeFarX_editingFinished()
{
    if (!ui->qqSizeFarX->isModified())
        return;
    IF_UI_EVENT_CAN_WRITE_DATA
    {
        CConvexVolume* cv = getCurrentConvexVolume();
        bool ok;
        double newVal = GuiApp::getEvalDouble(ui->qqSizeFarX->text().toStdString().c_str(), &ok);
        if (ok && cv)
        {
            App::appendSimulationThreadCommand(SET_XSIZEFAR_DETECTIONVOLUMEGUITRIGGEREDCMD,
                                               App::currentWorld->sceneObjects->getLastSelectionHandle(), -1, newVal);
            App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
        }
        App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
    }
}

void CQDlgDetectionVolume::on_qqFaceCountFar_editingFinished()
{
    if (!ui->qqFaceCountFar->isModified())
        return;
    IF_UI_EVENT_CAN_WRITE_DATA
    {
        CConvexVolume* cv = getCurrentConvexVolume();
        bool ok;
        int newVal = (int)GuiApp::getEvalInt(ui->qqFaceCountFar->text().toStdString().c_str(), &ok);
        if (ok && cv)
        {
            App::appendSimulationThreadCommand(SET_FACECOUNTFAR_DETECTIONVOLUMEGUITRIGGEREDCMD,
                                               App::currentWorld->sceneObjects->getLastSelectionHandle(), newVal);
            App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
        }
        App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
    }
}

void CQDlgDetectionVolume::on_qqSizeFarY_editingFinished()
{
    if (!ui->qqSizeFarY->isModified())
        return;
    IF_UI_EVENT_CAN_WRITE_DATA
    {
        CConvexVolume* cv = getCurrentConvexVolume();
        bool ok;
        double newVal = GuiApp::getEvalDouble(ui->qqSizeFarY->text().toStdString().c_str(), &ok);
        if (ok && cv)
        {
            App::appendSimulationThreadCommand(SET_YSIZEFAR_DETECTIONVOLUMEGUITRIGGEREDCMD,
                                               App::currentWorld->sceneObjects->getLastSelectionHandle(), -1, newVal);
            App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
        }
        App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
    }
}

void CQDlgDetectionVolume::on_qqSubdivisions_editingFinished()
{
    if (!ui->qqSubdivisions->isModified())
        return;
    IF_UI_EVENT_CAN_WRITE_DATA
    {
        CProxSensor* proxSensor = App::currentWorld->sceneObjects->getLastSelectionProxSensor();
        CConvexVolume* cv = getCurrentConvexVolume();
        bool ok;
        int newVal = (int)GuiApp::getEvalInt(ui->qqSubdivisions->text().toStdString().c_str(), &ok);
        if (ok && cv && (proxSensor != nullptr))
        {
            App::appendSimulationThreadCommand(SET_SUBDIVISIONS_DETECTIONVOLUMEGUITRIGGEREDCMD,
                                               App::currentWorld->sceneObjects->getLastSelectionHandle(), newVal);
            App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
        }
        App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
    }
}

void CQDlgDetectionVolume::on_qqInsideGap_editingFinished()
{
    if (!ui->qqInsideGap->isModified())
        return;
    IF_UI_EVENT_CAN_WRITE_DATA
    {
        CProxSensor* proxSensor = App::currentWorld->sceneObjects->getLastSelectionProxSensor();
        CConvexVolume* cv = getCurrentConvexVolume();
        bool ok;
        double newVal = GuiApp::getEvalDouble(ui->qqInsideGap->text().toStdString().c_str(), &ok);
        if (ok && cv && (proxSensor != nullptr))
        {
            App::appendSimulationThreadCommand(SET_INSIDEGAP_DETECTIONVOLUMEGUITRIGGEREDCMD,
                                               App::currentWorld->sceneObjects->getLastSelectionHandle(), -1, newVal);
            App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
        }
        App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
    }
}

void CQDlgDetectionVolume::on_qqSubdivisionsFar_editingFinished()
{
    if (!ui->qqSubdivisionsFar->isModified())
        return;
    IF_UI_EVENT_CAN_WRITE_DATA
    {
        CConvexVolume* cv = getCurrentConvexVolume();
        bool ok;
        int newVal = (int)GuiApp::getEvalInt(ui->qqSubdivisionsFar->text().toStdString().c_str(), &ok);
        if (ok && cv)
        {
            App::appendSimulationThreadCommand(SET_SUBDIVISIONSFAR_DETECTIONVOLUMEGUITRIGGEREDCMD,
                                               App::currentWorld->sceneObjects->getLastSelectionHandle(), newVal);
            App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
        }
        App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
    }
}

void CQDlgDetectionVolume::on_qqApplyAll_clicked()
{
    IF_UI_EVENT_CAN_WRITE_DATA
    {
        CProxSensor* proxSensor = App::currentWorld->sceneObjects->getLastSelectionProxSensor();
        CMill* mill = App::currentWorld->sceneObjects->getLastSelectionMill();
        if ((proxSensor != nullptr) || (mill != nullptr))
        {
            SSimulationThreadCommand cmd;
            cmd.cmdId = APPLY_DETECTIONVOLUMEGUITRIGGEREDCMD;
            cmd.intParams.push_back(App::currentWorld->sceneObjects->getLastSelectionHandle());
            for (size_t i = 0; i < App::currentWorld->sceneObjects->getSelectionCount() - 1; i++)
                cmd.intParams.push_back(App::currentWorld->sceneObjects->getObjectHandleFromSelectionIndex(i));
            App::appendSimulationThreadCommand(cmd);
            App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
        }
        App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
    }
}
