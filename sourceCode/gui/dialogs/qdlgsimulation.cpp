#include <qdlgsimulation.h>
#include <ui_qdlgsimulation.h>
#include <app.h>
#include <tt.h>
#include <utils.h>
#include <simStrings.h>
#ifdef SIM_WITH_GUI
#include <guiApp.h>
#endif

CQDlgSimulation::CQDlgSimulation(QWidget* parent)
    : CDlgEx(parent), ui(new Ui::CQDlgSimulation)
{
    _dlgType = SIMULATION_DLG;
    ui->setupUi(this);
    inMainRefreshRoutine = false;
}

CQDlgSimulation::~CQDlgSimulation()
{
    delete ui;
}

void CQDlgSimulation::refresh()
{
    inMainRefreshRoutine = true;
    QLineEdit* lineEditToSelect = getSelectedLineEdit();
    bool noEditMode = GuiApp::getEditModeType() == NO_EDIT_MODE;
    bool noEditModeNoSim = noEditMode && App::currentWorld->simulation->isSimulationStopped();

    ui->qqTimeStep->setEnabled(noEditModeNoSim);
    ui->qqFullscreen->setEnabled(noEditModeNoSim);
    ui->qqScriptExecutionPasses->setEnabled(noEditModeNoSim);
    ui->qqRealTime->setEnabled(noEditModeNoSim);
    ui->qqMultiplicationCoefficient->setEnabled(noEditModeNoSim &&
                                                App::currentWorld->simulation->getIsRealTimeSimulation());
    ui->qqPauseTime->setEnabled(noEditModeNoSim && App::currentWorld->simulation->getPauseAtSpecificTime());
    ui->qqPauseWhenTimeHigher->setEnabled(noEditModeNoSim);
    ui->qqPauseOnScriptError->setEnabled(noEditModeNoSim);
    ui->qqRemoveNewObjects->setEnabled(noEditMode);

    ui->qqEngineCombo->setEnabled(noEditModeNoSim && App::currentWorld->dynamicsContainer->getDynamicsEnabled());
    ui->qqContactPoints->setEnabled(noEditMode && App::currentWorld->dynamicsContainer->getDynamicsEnabled());
    ui->qqAdjustEngine->setEnabled(noEditModeNoSim && App::currentWorld->dynamicsContainer->getDynamicsEnabled());
    ui->qqDynTimeStep->setEnabled(noEditModeNoSim && App::currentWorld->dynamicsContainer->getDynamicsEnabled());
    ui->qqGravityX->setEnabled(noEditModeNoSim && App::currentWorld->dynamicsContainer->getDynamicsEnabled());
    ui->qqGravityY->setEnabled(noEditModeNoSim && App::currentWorld->dynamicsContainer->getDynamicsEnabled());
    ui->qqGravityZ->setEnabled(noEditModeNoSim && App::currentWorld->dynamicsContainer->getDynamicsEnabled());

    ui->qqRealTime->setChecked(App::currentWorld->simulation->getIsRealTimeSimulation());
    ui->qqTimeStep->setText(utils::getTimeString(true, App::currentWorld->simulation->getTimeStep()).c_str());
    ui->qqFullscreen->setChecked(App::currentWorld->simulation->getFullscreenAtSimulationStart());

    ui->qqScriptExecutionPasses->setText(
        utils::getIntString(false, App::currentWorld->simulation->getPassesPerRendering()).c_str());
    ui->qqMultiplicationCoefficient->setText(
        utils::getMultString(false, App::currentWorld->simulation->getRealTimeCoeff()).c_str());

    ui->qqRemoveNewObjects->setChecked(App::currentWorld->simulation->getRemoveNewObjectsAtSimulationEnd());

    ui->qqPauseTime->setText(utils::getTimeString(true, App::currentWorld->simulation->getPauseTime()).c_str());
    ui->qqPauseWhenTimeHigher->setChecked(App::currentWorld->simulation->getPauseAtSpecificTime());
    ui->qqPauseOnScriptError->setChecked(App::currentWorld->simulation->getPauseAtError());

    if (App::currentWorld->dynamicsContainer->getSettingsAreDefault() &&
        App::currentWorld->simulation->getSettingsAreDefault())
        ui->qqInfo->setText("");
    else
    {
        ui->qqInfo->setText("Detected non-default settings!");
        ui->qqInfo->setStyleSheet("QLabel { color : red; }");
    }
    ui->qqEnabled->setChecked(App::currentWorld->dynamicsContainer->getDynamicsEnabled());
    ui->qqEngineCombo->clear();
    ui->qqEngineCombo->addItem(IDS_BULLET_2_78, 0);
    ui->qqEngineCombo->addItem(IDS_BULLET_2_83, 1);
    ui->qqEngineCombo->addItem(IDS_ODE, 2);
    ui->qqEngineCombo->addItem(IDS_VORTEX, 3);
    ui->qqEngineCombo->addItem(IDS_NEWTON, 4);
    ui->qqEngineCombo->addItem(IDS_MUJOCO, 5);
#ifdef HAS_DRAKE
    ui->qqEngineCombo->addItem(IDS_DRAKE, 6);
#endif
    int ver;
    int eng = App::currentWorld->dynamicsContainer->getDynamicEngineType(&ver);
    if ((eng == sim_physics_bullet) && (ver == 0))
        ui->qqEngineCombo->setCurrentIndex(0);
    if ((eng == sim_physics_bullet) && (ver == 283))
        ui->qqEngineCombo->setCurrentIndex(1);
    if (eng == sim_physics_ode)
        ui->qqEngineCombo->setCurrentIndex(2);
    if (eng == sim_physics_vortex)
        ui->qqEngineCombo->setCurrentIndex(3);
    if (eng == sim_physics_newton)
        ui->qqEngineCombo->setCurrentIndex(4);
    if (eng == sim_physics_mujoco)
        ui->qqEngineCombo->setCurrentIndex(5);
    if (eng == sim_physics_drake)
        ui->qqEngineCombo->setCurrentIndex(6);
    ui->qqDynamicsDtLabel->setText(
        (std::string("Dynamics dt (effective dt=") +
         utils::getDoubleString(false, App::currentWorld->dynamicsContainer->getEffectiveStepSize() * 1000.0, 1, 3) +
         "ms)")
            .c_str());
    ui->qqDynTimeStep->setText(
        utils::getTimeString(true, App::currentWorld->dynamicsContainer->getDesiredStepSize()).c_str());
    ui->qqContactPoints->setChecked(App::currentWorld->dynamicsContainer->getDisplayContactPoints());
    C3Vector accel(App::currentWorld->dynamicsContainer->getGravity());
    ui->qqGravityX->setText(utils::getGravityString(true, accel(0)).c_str());
    ui->qqGravityY->setText(utils::getGravityString(true, accel(1)).c_str());
    ui->qqGravityZ->setText(utils::getGravityString(true, accel(2)).c_str());

    selectLineEdit(lineEditToSelect);
    inMainRefreshRoutine = false;
}

void CQDlgSimulation::on_qqTimeStep_editingFinished()
{
    if (!ui->qqTimeStep->isModified())
        return;
    IF_UI_EVENT_CAN_READ_DATA
    {
        if (App::currentWorld->simulation->isSimulationStopped())
        {
            bool ok;
            double newVal = GuiApp::getEvalDouble(ui->qqTimeStep->text().toStdString().c_str(), &ok);
            if (ok)
            {
                SSimulationThreadCommand cmd;
                cmd.cmdId = SET_TIMESTEP_SIMULATIONGUITRIGGEREDCMD;
                cmd.doubleParams.push_back(newVal);
                App::appendSimulationThreadCommand(cmd);
                App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
            }
            App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
        }
    }
}

void CQDlgSimulation::on_qqScriptExecutionPasses_editingFinished()
{
    if (!ui->qqScriptExecutionPasses->isModified())
        return;
    IF_UI_EVENT_CAN_READ_DATA
    {
        if (App::currentWorld->simulation->isSimulationStopped())
        {
            bool ok;
            int newVal = (int)GuiApp::getEvalInt(ui->qqScriptExecutionPasses->text().toStdString().c_str(), &ok);
            if (ok)
            {
                App::appendSimulationThreadCommand(SET_PPF_SIMULATIONGUITRIGGEREDCMD, newVal);
                App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
            }
            App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
        }
    }
}

void CQDlgSimulation::on_qqRealTime_clicked()
{
    IF_UI_EVENT_CAN_READ_DATA
    {
        if (App::currentWorld->simulation->isSimulationStopped())
        {
            App::appendSimulationThreadCommand(TOGGLE_REALTIME_SIMULATIONGUITRIGGEREDCMD);
            App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
            App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
        }
    }
}

void CQDlgSimulation::on_qqMultiplicationCoefficient_editingFinished()
{
    if (!ui->qqMultiplicationCoefficient->isModified())
        return;
    IF_UI_EVENT_CAN_READ_DATA
    {
        if (App::currentWorld->simulation->isSimulationStopped())
        {
            bool ok;
            double newVal = GuiApp::getEvalDouble(ui->qqMultiplicationCoefficient->text().toStdString().c_str(), &ok);
            if (ok)
            {
                App::appendSimulationThreadCommand(SET_REALTIMEFACTOR_SIMULATIONGUITRIGGEREDCMD, -1, -1, newVal);
                App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
            }
            App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
        }
    }
}

void CQDlgSimulation::on_qqPauseWhenTimeHigher_clicked()
{
    IF_UI_EVENT_CAN_READ_DATA
    {
        App::appendSimulationThreadCommand(TOGGLE_PAUSEATTIME_SIMULATIONGUITRIGGEREDCMD);
        App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
        App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
    }
}

void CQDlgSimulation::on_qqPauseTime_editingFinished()
{
    if (!ui->qqPauseTime->isModified())
        return;
    IF_UI_EVENT_CAN_READ_DATA
    {
        if (App::currentWorld->simulation->isSimulationStopped())
        {
            bool ok;
            double newVal = GuiApp::getEvalDouble(ui->qqPauseTime->text().toStdString().c_str(), &ok);
            if (ok)
            {
                SSimulationThreadCommand cmd;
                cmd.cmdId = SET_PAUSETIME_SIMULATIONGUITRIGGEREDCMD;
                cmd.doubleParams.push_back(newVal);
                App::appendSimulationThreadCommand(cmd);
                App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
            }
            App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
        }
    }
}

void CQDlgSimulation::on_qqPauseOnScriptError_clicked()
{
    IF_UI_EVENT_CAN_READ_DATA
    {
        App::appendSimulationThreadCommand(TOGGLE_PAUSEATERROR_SIMULATIONGUITRIGGEREDCMD);
        App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
        App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
    }
}

void CQDlgSimulation::on_qqRemoveNewObjects_clicked()
{
    IF_UI_EVENT_CAN_READ_DATA
    {
        App::appendSimulationThreadCommand(TOGGLE_REMOVENEWOBJECTS_SIMULATIONGUITRIGGEREDCMD);
        App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
        App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
    }
}

void CQDlgSimulation::on_qqFullscreen_clicked()
{
    IF_UI_EVENT_CAN_READ_DATA
    {
        App::appendSimulationThreadCommand(TOGGLE_FULLSCREENATSTART_SIMULATIONGUITRIGGEREDCMD);
        App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
        App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
    }
}

void CQDlgSimulation::on_qqEnabled_clicked()
{
    IF_UI_EVENT_CAN_WRITE_DATA
    {
        App::appendSimulationThreadCommand(TOGGLE_DYNAMICS_DYNAMICSGUITRIGGEREDCMD);
        App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
        App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
    }
}

void CQDlgSimulation::on_qqEngineCombo_currentIndexChanged(int index)
{
    if (!inMainRefreshRoutine)
    {
        IF_UI_EVENT_CAN_READ_DATA
        {
            int index = ui->qqEngineCombo->itemData(ui->qqEngineCombo->currentIndex()).toInt();
            int ver = 0;
            int eng = 0;
            if ((index == 0) || (index == 1))
                eng = sim_physics_bullet;
            if (index == 1)
                ver = 283;
            if (index == 2)
                eng = sim_physics_ode;
            if (index == 3)
                eng = sim_physics_vortex;
            if (index == 4)
                eng = sim_physics_newton;
            if (index == 5)
                eng = sim_physics_mujoco;
            if (index == 6)
                eng = sim_physics_drake;

            App::appendSimulationThreadCommand(SET_ENGINE_DYNAMICSGUITRIGGEREDCMD, eng, ver);
            App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
            App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
            App::appendSimulationThreadCommand(REFRESH_TOOLBARS_GUITRIGGEREDCMD);
        }
    }
}

void CQDlgSimulation::on_qqContactPoints_clicked()
{
    IF_UI_EVENT_CAN_READ_DATA
    {
        App::appendSimulationThreadCommand(TOGGLE_DISPLAYCONTACTS_DYNAMICSGUITRIGGEREDCMD);
        App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
        App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
    }
}

void CQDlgSimulation::on_qqAdjustEngine_clicked()
{
    IF_UI_EVENT_CAN_WRITE_DATA
    {
        SSimulationThreadCommand cmd;
        cmd.cmdId = SET_ENGINEPARAMS_DYNAMICSGUITRIGGEREDCMD;
        App::appendSimulationThreadCommand(cmd);
        App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
        App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
    }
}

void CQDlgSimulation::on_qqGravityX_editingFinished()
{
    if (!ui->qqGravityX->isModified())
        return;
    IF_UI_EVENT_CAN_READ_DATA
    {
        bool ok;
        double newVal = GuiApp::getEvalDouble(ui->qqGravityX->text().toStdString().c_str(), &ok);
        if (ok)
        {
            C3Vector vect = App::currentWorld->dynamicsContainer->getGravity();
            vect(0) = newVal;
            SSimulationThreadCommand cmd;
            cmd.cmdId = SET_GRAVITY_DYNAMICSGUITRIGGEREDCMD;
            cmd.posParams.push_back(vect);
            App::appendSimulationThreadCommand(cmd);
            App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
        }
        App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
    }
}

void CQDlgSimulation::on_qqGravityY_editingFinished()
{
    if (!ui->qqGravityY->isModified())
        return;
    IF_UI_EVENT_CAN_READ_DATA
    {
        bool ok;
        double newVal = GuiApp::getEvalDouble(ui->qqGravityY->text().toStdString().c_str(), &ok);
        if (ok)
        {
            C3Vector vect = App::currentWorld->dynamicsContainer->getGravity();
            vect(1) = newVal;
            SSimulationThreadCommand cmd;
            cmd.cmdId = SET_GRAVITY_DYNAMICSGUITRIGGEREDCMD;
            cmd.posParams.push_back(vect);
            App::appendSimulationThreadCommand(cmd);
            App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
        }
        App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
    }
}

void CQDlgSimulation::on_qqGravityZ_editingFinished()
{
    if (!ui->qqGravityZ->isModified())
        return;
    IF_UI_EVENT_CAN_READ_DATA
    {
        bool ok;
        double newVal = GuiApp::getEvalDouble(ui->qqGravityZ->text().toStdString().c_str(), &ok);
        if (ok)
        {
            C3Vector vect = App::currentWorld->dynamicsContainer->getGravity();
            vect(2) = newVal;
            SSimulationThreadCommand cmd;
            cmd.cmdId = SET_GRAVITY_DYNAMICSGUITRIGGEREDCMD;
            cmd.posParams.push_back(vect);
            App::appendSimulationThreadCommand(cmd);
            App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
        }
        App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
    }
}

void CQDlgSimulation::on_qqDynTimeStep_editingFinished()
{
    if (!ui->qqDynTimeStep->isModified())
        return;
    IF_UI_EVENT_CAN_READ_DATA
    {
        bool ok;
        double newVal = GuiApp::getEvalDouble(ui->qqDynTimeStep->text().toStdString().c_str(), &ok);
        if (ok)
        {
            SSimulationThreadCommand cmd;
            cmd.cmdId = SET_TIMESTEP_DYNAMICSGUITRIGGEREDCMD;
            cmd.doubleParams.push_back(newVal);
            App::appendSimulationThreadCommand(cmd);
            App::appendSimulationThreadCommand(POST_SCENE_CHANGED_ANNOUNCEMENT_GUITRIGGEREDCMD);
        }
        App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
    }
}
