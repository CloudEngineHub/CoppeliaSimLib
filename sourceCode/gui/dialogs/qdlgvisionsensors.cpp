#include <qdlgvisionsensors.h>
#include <ui_qdlgvisionsensors.h>
#include <tt.h>
#include <utils.h>
#include <qdlgmaterial.h>
#include <qdlgimagecolor.h>
#include <simStrings.h>
#include <app.h>
#include <vMessageBox.h>
#include <guiApp.h>

CQDlgVisionSensors::CQDlgVisionSensors(QWidget* parent)
    : CDlgEx(parent), ui(new Ui::CQDlgVisionSensors)
{
    _dlgType = VISION_SENSOR_DLG;
    ui->setupUi(this);
    inMainRefreshRoutine = false;
}

CQDlgVisionSensors::~CQDlgVisionSensors()
{
    delete ui;
}

void CQDlgVisionSensors::cancelEvent()
{
    // we override this cancel event. The container window should close, not this one!!
    GuiApp::mainWindow->dlgCont->close(OBJECT_DLG);
}

void CQDlgVisionSensors::refresh()
{
    inMainRefreshRoutine = true;
    QLineEdit* lineEditToSelect = getSelectedLineEdit();

    CVisionSensor* it = App::currentWorld->sceneObjects->getLastSelectionVisionSensor();

    bool isSensor = App::currentWorld->sceneObjects->isLastSelectionOfType(sim_sceneobject_visionsensor);
    bool manySensors = App::currentWorld->sceneObjects->getObjectCountInSelection(sim_sceneobject_visionsensor) > 1;
    bool noEditModeAndNoSim =
        (GuiApp::getEditModeType() == NO_EDIT_MODE) && App::currentWorld->simulation->isSimulationStopped();

    ui->qqNearPlane->setEnabled(isSensor && noEditModeAndNoSim);
    ui->qqFarPlane->setEnabled(isSensor && noEditModeAndNoSim);

    ui->qqPerspectiveAngleOrOrthographicSize->setEnabled(isSensor && noEditModeAndNoSim);

    ui->qqResX->setEnabled(isSensor && noEditModeAndNoSim);
    ui->qqResY->setEnabled(isSensor && noEditModeAndNoSim);

    ui->qqSizeX->setEnabled(isSensor && noEditModeAndNoSim);

    ui->qqExplicitHandling->setEnabled(isSensor && noEditModeAndNoSim);
    ui->qqExternalInput->setEnabled(isSensor && noEditModeAndNoSim);
    ui->qqLocalLights->setEnabled(isSensor && noEditModeAndNoSim);
    ui->qqLocalLights->setVisible(App::userSettings->showOldDlgs);

    ui->qqShowFog->setVisible(App::userSettings->showOldDlgs);
    ui->qqShowFog->setEnabled(isSensor && noEditModeAndNoSim);

    ui->qqShowVolume->setEnabled(isSensor && noEditModeAndNoSim);

    ui->qqIgnoreRGB->setEnabled(isSensor && noEditModeAndNoSim);
    ui->qqIgnoreDepth->setEnabled(isSensor && noEditModeAndNoSim && (it->getRenderMode() != sim_rendermode_povray));
    ui->qqIgnorePacket1->setEnabled(isSensor && noEditModeAndNoSim);

    ui->qqCasingColor->setEnabled(isSensor && noEditModeAndNoSim);

    ui->qqApplyMainProperties->setEnabled(isSensor && manySensors && noEditModeAndNoSim);
    ui->qqApplyColors->setEnabled(isSensor && manySensors && noEditModeAndNoSim);

    ui->qqAdjustImageColor->setEnabled(isSensor && noEditModeAndNoSim);

    ui->qqRenderModeCombo->setEnabled(isSensor && noEditModeAndNoSim);
    ui->qqRenderModeCombo->clear();

    if (isSensor)
    {
        CVisionSensor* s = App::currentWorld->sceneObjects->getLastSelectionVisionSensor();

        ui->qqShowFog->setChecked(!s->getHideFog());

        double np, fp;
        s->getClippingPlanes(np, fp);
        ui->qqNearPlane->setText(utils::getSizeString(false, np).c_str());
        ui->qqFarPlane->setText(utils::getSizeString(false, fp).c_str());

        if (s->getPerspective())
            ui->qqPerspectiveAngleOrOrthographicSize->setText(utils::getAngleString(false, s->getViewAngle()).c_str());
        else
            ui->qqPerspectiveAngleOrOrthographicSize->setText(
                utils::getSizeString(false, s->getOrthoViewSize()).c_str());

        int r[2];
        s->getResolution(r);
        ui->qqResX->setText(utils::getIntString(false, r[0]).c_str());
        ui->qqResY->setText(utils::getIntString(false, r[1]).c_str());
        ui->qqSizeX->setText(utils::getSizeString(false, s->getVisionSensorSize()).c_str());

        ui->qqExplicitHandling->setChecked(s->getExplicitHandling());
        ui->qqExternalInput->setChecked(s->getUseExternalImage());
        ui->qqLocalLights->setChecked(s->getuseLocalLights());

        ui->qqShowVolume->setChecked(s->getShowVolume());

        ui->qqIgnoreRGB->setChecked(s->getIgnoreRGBInfo());
        ui->qqIgnoreDepth->setChecked(s->getIgnoreDepthInfo());
        ui->qqIgnorePacket1->setChecked(!s->getComputeImageBasicStats());

        ui->qqRenderModeCombo->addItem("Legacy OpenGL", QVariant(sim_rendermode_opengl));
        if (it->getRenderMode() == sim_rendermode_auxchannels) // deprecated
            ui->qqRenderModeCombo->addItem("Legacy OpenGL (deprecated)", QVariant(sim_rendermode_auxchannels));
        ui->qqRenderModeCombo->addItem("Legacy OpenGL, color coded handles", QVariant(sim_rendermode_colorcoded));
        ui->qqRenderModeCombo->addItem("POV-Ray", QVariant(sim_rendermode_povray));
        if (it->getRenderMode() == sim_rendermode_extrenderer) // deprecated
            ui->qqRenderModeCombo->addItem("External renderer (deprecated)", QVariant(sim_rendermode_extrenderer));
        ui->qqRenderModeCombo->addItem("OpenGL 3", QVariant(sim_rendermode_opengl3));
        /* for now
        ui->qqRenderModeCombo->addItem("OpenGL",QVariant(sim_rendermode_oglimg));
        ui->qqRenderModeCombo->addItem("OpenGL, color coded handles",QVariant(sim_rendermode_codedimg));
        */

        // Select current item:
        for (int i = 0; i < ui->qqRenderModeCombo->count(); i++)
        {
            if (ui->qqRenderModeCombo->itemData(i).toInt() == it->getRenderMode())
            {
                ui->qqRenderModeCombo->setCurrentIndex(i);
                break;
            }
        }
    }
    else
    {
        ui->qqNearPlane->setText("");
        ui->qqFarPlane->setText("");

        ui->qqPerspectiveAngleOrOrthographicSize->setText("");

        ui->qqResX->setText("");
        ui->qqResY->setText("");

        ui->qqSizeX->setText("");

        ui->qqExplicitHandling->setChecked(false);
        ui->qqExternalInput->setChecked(false);
        ui->qqLocalLights->setChecked(false);

        ui->qqShowFog->setChecked(false);

        ui->qqShowVolume->setChecked(false);
        ui->qqIgnoreRGB->setChecked(false);
        ui->qqIgnoreDepth->setChecked(false);
        ui->qqIgnorePacket1->setChecked(false);
    }

    selectLineEdit(lineEditToSelect);
    inMainRefreshRoutine = false;
}

void CQDlgVisionSensors::on_qqExplicitHandling_clicked()
{
    IF_UI_EVENT_CAN_READ_DATA
    {
        App::appendSimulationThreadCommand(TOGGLE_EXPLICITHANDLING_VISIONSENSORGUITRIGGEREDCMD,
                                           App::currentWorld->sceneObjects->getLastSelectionHandle());
        App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
        App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
    }
}

void CQDlgVisionSensors::on_qqExternalInput_clicked()
{
    IF_UI_EVENT_CAN_READ_DATA
    {
        App::appendSimulationThreadCommand(TOGGLE_EXTERNALINPUT_VISIONSENSORGUITRIGGEREDCMD,
                                           App::currentWorld->sceneObjects->getLastSelectionHandle());
        App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
        App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
    }
}

void CQDlgVisionSensors::on_qqLocalLights_clicked()
{
    IF_UI_EVENT_CAN_READ_DATA
    {
        App::appendSimulationThreadCommand(TOGGLE_LOCALLIGHTS_VISIONSENSORGUITRIGGEREDCMD,
                                           App::currentWorld->sceneObjects->getLastSelectionHandle());
        App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
        App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
    }
}

void CQDlgVisionSensors::on_qqShowVolume_clicked()
{
    IF_UI_EVENT_CAN_READ_DATA
    {
        App::appendSimulationThreadCommand(TOGGLE_SHOWVOLUME_VISIONSENSORGUITRIGGEREDCMD,
                                           App::currentWorld->sceneObjects->getLastSelectionHandle());
        App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
        App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
    }
}

void CQDlgVisionSensors::on_qqShowFog_clicked()
{
    IF_UI_EVENT_CAN_READ_DATA
    {
        App::appendSimulationThreadCommand(TOGGLE_SHOWFOG_VISIONSENSORGUITRIGGEREDCMD,
                                           App::currentWorld->sceneObjects->getLastSelectionHandle());
        App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
        App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
    }
}

void CQDlgVisionSensors::on_qqNearPlane_editingFinished()
{
    if (!ui->qqNearPlane->isModified())
        return;
    IF_UI_EVENT_CAN_READ_DATA
    {
        bool ok;
        double newVal = GuiApp::getEvalDouble(ui->qqNearPlane->text().toStdString().c_str(), &ok);
        if (ok)
        {
            App::appendSimulationThreadCommand(SET_NEARCLIPPING_VISIONSENSORGUITRIGGEREDCMD,
                                               App::currentWorld->sceneObjects->getLastSelectionHandle(), -1, newVal);
            App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
        }
        App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
    }
}

void CQDlgVisionSensors::on_qqFarPlane_editingFinished()
{
    if (!ui->qqFarPlane->isModified())
        return;
    IF_UI_EVENT_CAN_READ_DATA
    {
        bool ok;
        double newVal = GuiApp::getEvalDouble(ui->qqFarPlane->text().toStdString().c_str(), &ok);
        if (ok)
        {
            App::appendSimulationThreadCommand(SET_FARCLIPPING_VISIONSENSORGUITRIGGEREDCMD,
                                               App::currentWorld->sceneObjects->getLastSelectionHandle(), -1, newVal);
            App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
        }
        App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
    }
}

void CQDlgVisionSensors::on_qqPerspectiveAngleOrOrthographicSize_editingFinished()
{
    if (!ui->qqPerspectiveAngleOrOrthographicSize->isModified())
        return;
    IF_UI_EVENT_CAN_READ_DATA
    {
        bool ok;
        double newVal =
            GuiApp::getEvalDouble(ui->qqPerspectiveAngleOrOrthographicSize->text().toStdString().c_str(), &ok);
        if (ok)
        {
            CVisionSensor* it = App::currentWorld->sceneObjects->getLastSelectionVisionSensor();
            if ((it != nullptr) && it->getPerspective())
                newVal *= degToRad;
            App::appendSimulationThreadCommand(SET_PERSPECTANGLE_OR_ORTHOSIZE_VISIONSENSORGUITRIGGEREDCMD,
                                               App::currentWorld->sceneObjects->getLastSelectionHandle(), -1, newVal);
            App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
        }
        App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
    }
}

void CQDlgVisionSensors::on_qqResX_editingFinished()
{
    if (!ui->qqResX->isModified())
        return;
    IF_UI_EVENT_CAN_WRITE_DATA
    {
        CVisionSensor* it = App::currentWorld->sceneObjects->getLastSelectionVisionSensor();
        if (it != nullptr)
        {
            bool ok;
            int newVal = (int)GuiApp::getEvalInt(ui->qqResX->text().toStdString().c_str(), &ok);
            if (ok)
            {
                int r[2];
                it->getResolution(r);
                if (newVal != r[0])
                {
                    r[0] = newVal;
                    SSimulationThreadCommand cmd;
                    cmd.cmdId = SET_RESOLUTION_VISIONSENSORGUITRIGGEREDCMD;
                    cmd.intParams.push_back(it->getObjectHandle());
                    cmd.intParams.push_back(r[0]);
                    cmd.intParams.push_back(r[1]);
                    App::appendSimulationThreadCommand(cmd);
                    App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
                }
            }
        }
        App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
    }
}

void CQDlgVisionSensors::on_qqResY_editingFinished()
{
    if (!ui->qqResY->isModified())
        return;
    IF_UI_EVENT_CAN_WRITE_DATA
    {
        CVisionSensor* it = App::currentWorld->sceneObjects->getLastSelectionVisionSensor();
        if (it != nullptr)
        {
            bool ok;
            int newVal = (int)GuiApp::getEvalInt(ui->qqResY->text().toStdString().c_str(), &ok);
            if (ok)
            {
                int r[2];
                it->getResolution(r);
                if (newVal != r[1])
                {
                    r[1] = newVal;
                    SSimulationThreadCommand cmd;
                    cmd.cmdId = SET_RESOLUTION_VISIONSENSORGUITRIGGEREDCMD;
                    cmd.intParams.push_back(it->getObjectHandle());
                    cmd.intParams.push_back(r[0]);
                    cmd.intParams.push_back(r[1]);
                    App::appendSimulationThreadCommand(cmd);
                    App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
                }
            }
        }
        App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
    }
}

void CQDlgVisionSensors::on_qqSizeX_editingFinished()
{
    if (!ui->qqSizeX->isModified())
        return;
    IF_UI_EVENT_CAN_READ_DATA
    {
        CVisionSensor* it = App::currentWorld->sceneObjects->getLastSelectionVisionSensor();
        if (it != nullptr)
        {
            bool ok;
            double newVal = GuiApp::getEvalDouble(ui->qqSizeX->text().toStdString().c_str(), &ok);
            if (ok)
            {
                SSimulationThreadCommand cmd;
                cmd.cmdId = SET_OBJECTSIZE_VISIONSENSORGUITRIGGEREDCMD;
                cmd.intParams.push_back(it->getObjectHandle());
                cmd.doubleParams.push_back(newVal);
                App::appendSimulationThreadCommand(cmd);
                App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
            }
            App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
        }
    }
}

void CQDlgVisionSensors::on_qqAdjustImageColor_clicked()
{
    IF_UI_EVENT_CAN_WRITE_DATA
    {
        CVisionSensor* it = App::currentWorld->sceneObjects->getLastSelectionVisionSensor();
        if (it != nullptr)
        {
            CQDlgImageColor theDialog(this);
            float col[3];
            it->getDefaultBufferValues(col);
            theDialog.sameAsFog = it->getUseEnvironmentBackgroundColor();
            theDialog.red = col[0];
            theDialog.green = col[1];
            theDialog.blue = col[2];
            theDialog.refresh();
            if (theDialog.makeDialogModal() != VDIALOG_MODAL_RETURN_CANCEL)
            {
                col[0] = theDialog.red;
                col[1] = theDialog.green;
                col[2] = theDialog.blue;
                SSimulationThreadCommand cmd;
                cmd.cmdId = SET_DEFAULTIMGCOL_VISIONSENSORGUITRIGGEREDCMD;
                cmd.intParams.push_back(it->getObjectHandle());
                cmd.doubleParams.push_back(col[0]);
                cmd.doubleParams.push_back(col[1]);
                cmd.doubleParams.push_back(col[2]);
                cmd.boolParams.push_back(theDialog.sameAsFog);
                App::appendSimulationThreadCommand(cmd);
                App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
                App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
            }
        }
    }
}

void CQDlgVisionSensors::on_qqApplyMainProperties_clicked()
{
    IF_UI_EVENT_CAN_WRITE_DATA
    {
        CVisionSensor* last = App::currentWorld->sceneObjects->getLastSelectionVisionSensor();
        if (last != nullptr)
        {
            SSimulationThreadCommand cmd;
            cmd.cmdId = APPLY_MAINPROP_TO_SELECTION_VISIONSENSORGUITRIGGEREDCMD;
            cmd.intParams.push_back(last->getObjectHandle());
            for (size_t i = 0; i < App::currentWorld->sceneObjects->getSelectionCount() - 1; i++)
            {
                CVisionSensor* it = App::currentWorld->sceneObjects->getVisionSensorFromHandle(
                    App::currentWorld->sceneObjects->getObjectHandleFromSelectionIndex(i));
                if (it != nullptr)
                    cmd.intParams.push_back(it->getObjectHandle());
            }
            App::appendSimulationThreadCommand(cmd);
            App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
        }
    }
}

void CQDlgVisionSensors::on_qqCasingColor_clicked()
{
    IF_UI_EVENT_CAN_READ_DATA
    {
        CQDlgMaterial::displayMaterialDlg(
            COLOR_ID_VISIONSENSOR, App::currentWorld->sceneObjects->getLastSelectionHandle(), -1, GuiApp::mainWindow);
    }
}

void CQDlgVisionSensors::on_qqApplyColors_clicked()
{
    IF_UI_EVENT_CAN_READ_DATA
    {
        CVisionSensor* last = App::currentWorld->sceneObjects->getLastSelectionVisionSensor();
        if (last != nullptr)
        {
            SSimulationThreadCommand cmd;
            cmd.cmdId = APPLY_VISUALPROP_TO_SELECTION_VISIONSENSORGUITRIGGEREDCMD;
            cmd.intParams.push_back(last->getObjectHandle());
            for (size_t i = 0; i < App::currentWorld->sceneObjects->getSelectionCount() - 1; i++)
            {
                CVisionSensor* it = App::currentWorld->sceneObjects->getVisionSensorFromHandle(
                    App::currentWorld->sceneObjects->getObjectHandleFromSelectionIndex(i));
                if (it != nullptr)
                    cmd.intParams.push_back(it->getObjectHandle());
            }
            App::appendSimulationThreadCommand(cmd);
            App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
        }
    }
}

void CQDlgVisionSensors::on_qqIgnoreRGB_clicked()
{
    IF_UI_EVENT_CAN_READ_DATA
    {
        App::appendSimulationThreadCommand(TOGGLE_IGNORERGB_VISIONSENSORGUITRIGGEREDCMD,
                                           App::currentWorld->sceneObjects->getLastSelectionHandle());
        App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
        App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
    }
}

void CQDlgVisionSensors::on_qqIgnoreDepth_clicked()
{
    IF_UI_EVENT_CAN_READ_DATA
    {
        App::appendSimulationThreadCommand(TOGGLE_IGNOREDEPTH_VISIONSENSORGUITRIGGEREDCMD,
                                           App::currentWorld->sceneObjects->getLastSelectionHandle());
        App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
        App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
    }
}

void CQDlgVisionSensors::on_qqIgnorePacket1_clicked()
{
    IF_UI_EVENT_CAN_READ_DATA
    {
        App::appendSimulationThreadCommand(TOGGLE_PACKET1BLANK_VISIONSENSORGUITRIGGEREDCMD,
                                           App::currentWorld->sceneObjects->getLastSelectionHandle());
        App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
        App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
    }
}

void CQDlgVisionSensors::on_qqRenderModeCombo_currentIndexChanged(int index)
{
    if (!inMainRefreshRoutine)
    {
        IF_UI_EVENT_CAN_WRITE_DATA
        {
            int renderMode = ui->qqRenderModeCombo->itemData(ui->qqRenderModeCombo->currentIndex()).toInt();
            App::appendSimulationThreadCommand(SET_RENDERMODE_VISIONSENSORGUITRIGGEREDCMD,
                                               App::currentWorld->sceneObjects->getLastSelectionHandle(), renderMode);
            App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
            App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
        }
    }
}
