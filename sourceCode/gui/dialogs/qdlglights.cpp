#include <qdlglights.h>
#include <ui_qdlglights.h>
#include <tt.h>
#include <utils.h>
#include <qdlgmaterial.h>
#include <qdlglightmaterial.h>
#include <app.h>
#include <guiApp.h>

CQDlgLights::CQDlgLights(QWidget* parent)
    : CDlgEx(parent), ui(new Ui::CQDlgLights)
{
    _dlgType = LIGHT_DLG;
    ui->setupUi(this);
}

CQDlgLights::~CQDlgLights()
{
    delete ui;
}

void CQDlgLights::cancelEvent()
{
    // we override this cancel event. The container window should close, not this one!!
    GuiApp::mainWindow->dlgCont->close(OBJECT_DLG);
}

void CQDlgLights::refresh()
{
    QLineEdit* lineEditToSelect = getSelectedLineEdit();
    bool noEditModeNoSim =
        (GuiApp::getEditModeType() == NO_EDIT_MODE) && App::currentWorld->simulation->isSimulationStopped();

    CLight* it = App::currentWorld->sceneObjects->getLastSelectionLight();

    ui->qqEnabled->setEnabled((it != nullptr) && noEditModeNoSim);
    ui->qqLocal->setEnabled((it != nullptr) && noEditModeNoSim);
    ui->qqLocal->setVisible(App::userSettings->showOldDlgs);
    ui->qqSize->setEnabled((it != nullptr) && noEditModeNoSim);
    ui->qqLightColor->setEnabled((it != nullptr) && noEditModeNoSim);

    if (it != nullptr)
    {
        int lt = it->getLightType();
        ui->qqEnabled->setChecked(it->getLightActive() && noEditModeNoSim);
        ui->qqLocal->setChecked(it->getLightIsLocal());
        ui->qqCasingColor->setEnabled((lt != sim_light_omnidirectional) && noEditModeNoSim);

        ui->qqSize->setText(utils::getSizeString(false, it->getLightSize()).c_str());

        ui->qqConstantFactor->setEnabled((lt != sim_light_directional) && noEditModeNoSim);
        ui->qqLinearFactor->setEnabled((lt != sim_light_directional) && noEditModeNoSim);
        ui->qqQuadraticFactor->setEnabled((lt != sim_light_directional) && noEditModeNoSim);
        ui->qqSpotExponent->setEnabled((lt == sim_light_spot) && noEditModeNoSim);
        ui->qqSpotCutoff->setEnabled((lt == sim_light_spot) && noEditModeNoSim);

        if (lt == sim_light_spot)
        {
            ui->qqSpotExponent->setText(utils::getIntString(false, it->getSpotExponent()).c_str());
            ui->qqSpotCutoff->setText(utils::getAngleString(false, it->getSpotCutoffAngle()).c_str());
        }
        else
        {
            ui->qqSpotExponent->setText("");
            ui->qqSpotCutoff->setText("");
        }
        if (lt != sim_light_directional)
        {
            double arr[3];
            it->getAttenuationFactors(arr);
            ui->qqConstantFactor->setText(utils::getDoubleString(false, arr[0], 2, 4).c_str());
            ui->qqLinearFactor->setText(utils::getDoubleString(false, arr[1], 2, 4).c_str());
            ui->qqQuadraticFactor->setText(utils::getDoubleString(false, arr[2], 2, 4).c_str());
        }
        else
        {
            ui->qqConstantFactor->setText("");
            ui->qqLinearFactor->setText("");
            ui->qqQuadraticFactor->setText("");
        }
    }
    else
    {
        ui->qqConstantFactor->setEnabled(false);
        ui->qqLinearFactor->setEnabled(false);
        ui->qqQuadraticFactor->setEnabled(false);
        ui->qqSpotCutoff->setEnabled(false);
        ui->qqSpotExponent->setEnabled(false);
        ui->qqCasingColor->setEnabled(false);
        ui->qqEnabled->setChecked(false);
        ui->qqLocal->setChecked(false);
        ui->qqSize->setText("");
        ui->qqConstantFactor->setText("");
        ui->qqLinearFactor->setText("");
        ui->qqQuadraticFactor->setText("");
        ui->qqSpotCutoff->setText("");
        ui->qqSpotExponent->setText("");
    }
    selectLineEdit(lineEditToSelect);
}

void CQDlgLights::on_qqEnabled_clicked()
{
    IF_UI_EVENT_CAN_READ_DATA
    {
        App::appendSimulationThreadCommand(TOGGLE_ENABLED_LIGHTGUITRIGGEREDCMD,
                                           App::currentWorld->sceneObjects->getLastSelectionHandle());
        App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
        App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
    }
}

void CQDlgLights::on_qqLocal_clicked()
{
    IF_UI_EVENT_CAN_READ_DATA
    {
        App::appendSimulationThreadCommand(TOGGLE_LIGHTISLOCAL_LIGHTGUITRIGGEREDCMD,
                                           App::currentWorld->sceneObjects->getLastSelectionHandle());
        App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
        App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
    }
}

void CQDlgLights::on_qqSize_editingFinished()
{
    if (!ui->qqSize->isModified())
        return;
    IF_UI_EVENT_CAN_READ_DATA
    {
        bool ok;
        double newVal = GuiApp::getEvalDouble(ui->qqSize->text().toStdString().c_str(), &ok);
        if (ok)
        {
            App::appendSimulationThreadCommand(SET_SIZE_LIGHTGUITRIGGEREDCMD,
                                               App::currentWorld->sceneObjects->getLastSelectionHandle(), -1, newVal);
            App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
        }
        App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
    }
}

void CQDlgLights::on_qqSpotCutoff_editingFinished()
{
    if (!ui->qqSpotCutoff->isModified())
        return;
    IF_UI_EVENT_CAN_READ_DATA
    {
        bool ok;
        double newVal = GuiApp::getEvalDouble(ui->qqSpotCutoff->text().toStdString().c_str(), &ok);
        if (ok)
        {
            App::appendSimulationThreadCommand(SET_SPOTCUTOFF_LIGHTGUITRIGGEREDCMD,
                                               App::currentWorld->sceneObjects->getLastSelectionHandle(), -1,
                                               newVal * degToRad);
            App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
        }
        App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
    }
}

void CQDlgLights::on_qqSpotExponent_editingFinished()
{
    if (!ui->qqSpotExponent->isModified())
        return;
    IF_UI_EVENT_CAN_READ_DATA
    {
        bool ok;
        int newVal = (int)GuiApp::getEvalInt(ui->qqSpotExponent->text().toStdString().c_str(), &ok);
        if (ok)
        {
            App::appendSimulationThreadCommand(SET_SPOTEXPONENT_LIGHTGUITRIGGEREDCMD,
                                               App::currentWorld->sceneObjects->getLastSelectionHandle(), newVal);
            App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
        }
        App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
    }
}

void CQDlgLights::on_qqConstantFactor_editingFinished()
{
    if (!ui->qqConstantFactor->isModified())
        return;
    IF_UI_EVENT_CAN_READ_DATA
    {
        bool ok;
        double newVal = GuiApp::getEvalDouble(ui->qqConstantFactor->text().toStdString().c_str(), &ok);
        if (ok)
        {
            App::appendSimulationThreadCommand(SET_CONSTATTENUATION_LIGHTGUITRIGGEREDCMD,
                                               App::currentWorld->sceneObjects->getLastSelectionHandle(), -1, newVal);
            App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
        }
        App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
    }
}

void CQDlgLights::on_qqLinearFactor_editingFinished()
{
    if (!ui->qqLinearFactor->isModified())
        return;
    IF_UI_EVENT_CAN_READ_DATA
    {
        bool ok;
        double newVal = GuiApp::getEvalDouble(ui->qqLinearFactor->text().toStdString().c_str(), &ok);
        if (ok)
        {
            App::appendSimulationThreadCommand(SET_LINATTENUATION_LIGHTGUITRIGGEREDCMD,
                                               App::currentWorld->sceneObjects->getLastSelectionHandle(), -1, newVal);
            App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
        }
        App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
    }
}

void CQDlgLights::on_qqQuadraticFactor_editingFinished()
{
    if (!ui->qqQuadraticFactor->isModified())
        return;
    IF_UI_EVENT_CAN_READ_DATA
    {
        bool ok;
        double newVal = GuiApp::getEvalDouble(ui->qqQuadraticFactor->text().toStdString().c_str(), &ok);
        if (ok)
        {
            App::appendSimulationThreadCommand(SET_QUADATTENUATION_LIGHTGUITRIGGEREDCMD,
                                               App::currentWorld->sceneObjects->getLastSelectionHandle(), -1, newVal);
            App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
        }
        App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
    }
}

void CQDlgLights::on_qqLightColor_clicked()
{
    IF_UI_EVENT_CAN_READ_DATA
    {
        CQDlgLightMaterial::displayMaterialDlg(
            COLOR_ID_LIGHT_LIGHT, App::currentWorld->sceneObjects->getLastSelectionHandle(), -1, GuiApp::mainWindow);
    }
}

void CQDlgLights::on_qqCasingColor_clicked()
{
    IF_UI_EVENT_CAN_READ_DATA
    {
        CQDlgMaterial::displayMaterialDlg(
            COLOR_ID_LIGHT_CASING, App::currentWorld->sceneObjects->getLastSelectionHandle(), -1, GuiApp::mainWindow);
    }
}
