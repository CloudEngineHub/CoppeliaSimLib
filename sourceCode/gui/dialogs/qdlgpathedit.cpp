#include <qdlgpathedit.h>
#include <ui_qdlgpathedit.h>
#include <app.h>
#include <tt.h>
#include <utils.h>
#include <simStrings.h>
#include <boost/lexical_cast.hpp>
#include <guiApp.h>

CQDlgPathEdit::CQDlgPathEdit(QWidget* parent)
    : CDlgEx(parent), ui(new Ui::CQDlgPathEdit)
{
    _dlgType = PATH_EDITION_DLG;
    ui->setupUi(this);
}

CQDlgPathEdit::~CQDlgPathEdit()
{
    delete ui;
}

void CQDlgPathEdit::cancelEvent()
{
    GuiApp::mainWindow->editModeContainer->processCommand(ANY_EDIT_MODE_FINISH_WITH_QUESTION_DLG_EMCMD, nullptr);
    //  defaultModalDialogEndRoutine(false);
}

void CQDlgPathEdit::okEvent()
{
    //  defaultModalDialogEndRoutine(true);
}

void CQDlgPathEdit::refresh()
{
    if (GuiApp::getEditModeType() != PATH_EDIT_MODE_OLD)
        return;
    CPathCont_old* pathCont = GuiApp::mainWindow->editModeContainer->getEditModePathContainer_old();
    int selectedPointCount = GuiApp::mainWindow->editModeContainer->getEditModeBufferSize();

    ui->qqClosed->setChecked(((pathCont->getAttributes() & sim_pathproperty_closed_path) != 0));
    ui->qqFlat->setChecked(((pathCont->getAttributes() & sim_pathproperty_flat_path) != 0));
    ui->qqAutomaticOrientation->setChecked(((pathCont->getAttributes() & sim_pathproperty_automatic_orientation) != 0));
    ui->qqKeepXup->setChecked(((pathCont->getAttributes() & sim_pathproperty_keep_x_up) != 0));

    std::string tmp =
        std::string(IDS_TOTAL_PATH_POINTS) + ": " +
        boost::lexical_cast<std::string>(GuiApp::mainWindow->editModeContainer->getEditModeBufferSize()) + "/" +
        boost::lexical_cast<std::string>(
            GuiApp::mainWindow->editModeContainer->getEditModePathContainer_old()->getSimplePathPointCount());
    ui->qqInfo->setText(tmp.c_str());

    ui->qqMakeDummies->setEnabled(selectedPointCount != 0);

    ui->qqFactor1->setEnabled(selectedPointCount != 0);
    ui->qqFactor2->setEnabled(selectedPointCount != 0);
    ui->qqPointCount->setEnabled(selectedPointCount != 0);
    ui->qqVirtualDistance->setEnabled(selectedPointCount != 0);
    ui->qqAuxFlags->setEnabled(selectedPointCount != 0);
    ui->qqAuxChannel1->setEnabled(selectedPointCount != 0);
    ui->qqAuxChannel2->setEnabled(selectedPointCount != 0);
    ui->qqAuxChannel3->setEnabled(selectedPointCount != 0);
    ui->qqAuxChannel4->setEnabled(selectedPointCount != 0);

    ui->qqApply->setEnabled(selectedPointCount > 1);

    if (selectedPointCount != 0)
    {
        CSimplePathPoint_old* it = GuiApp::mainWindow->editModeContainer->getPathEditMode()->getSimplePathPoint(
            GuiApp::mainWindow->editModeContainer->getEditModeBufferSize() - 1);
        double bInt0, bInt1;
        it->getBezierFactors(bInt0, bInt1);
        ui->qqFactor1->setText(utils::getMultString(false, bInt0).c_str());
        ui->qqFactor2->setText(utils::getMultString(false, bInt1).c_str());
        ui->qqPointCount->setText(utils::getIntString(false, it->getBezierPointCount()).c_str());
        ui->qqVirtualDistance->setText(utils::getPosString(false, it->getOnSpotDistance()).c_str());
        ui->qqAuxFlags->setText(utils::getIntString(false, it->getAuxFlags()).c_str());
        double auxChannels[4];
        it->getAuxChannels(auxChannels);
        ui->qqAuxChannel1->setText(utils::getSizeString(false, auxChannels[0]).c_str());
        ui->qqAuxChannel2->setText(utils::getSizeString(false, auxChannels[1]).c_str());
        ui->qqAuxChannel3->setText(utils::getSizeString(false, auxChannels[2]).c_str());
        ui->qqAuxChannel4->setText(utils::getSizeString(false, auxChannels[3]).c_str());
    }
    else
    {
        ui->qqFactor1->setText("");
        ui->qqFactor2->setText("");
        ui->qqPointCount->setText("");
        ui->qqVirtualDistance->setText("");
        ui->qqAuxFlags->setText("");
        ui->qqAuxChannel1->setText("");
        ui->qqAuxChannel2->setText("");
        ui->qqAuxChannel3->setText("");
        ui->qqAuxChannel4->setText("");
    }
}

CPathCont_old* CQDlgPathEdit::getPathCont()
{
    CPathCont_old* pathCont = GuiApp::mainWindow->editModeContainer->getEditModePathContainer_old();
    return (pathCont);
}

void CQDlgPathEdit::on_qqClosed_clicked()
{
    IF_UI_EVENT_CAN_READ_DATA
    {
        CPathCont_old* pathCont = getPathCont();
        if (pathCont != nullptr)
            pathCont->setAttributes(pathCont->getAttributes() ^ sim_pathproperty_closed_path);
        refresh();
    }
}

void CQDlgPathEdit::on_qqFlat_clicked()
{
    IF_UI_EVENT_CAN_READ_DATA
    {
        CPathCont_old* pathCont = getPathCont();
        if (pathCont != nullptr)
            pathCont->setAttributes(pathCont->getAttributes() ^ sim_pathproperty_flat_path);
        refresh();
    }
}

void CQDlgPathEdit::on_qqAutomaticOrientation_clicked()
{
    IF_UI_EVENT_CAN_READ_DATA
    {
        CPathCont_old* pathCont = getPathCont();
        if (pathCont != nullptr)
            pathCont->setAttributes(pathCont->getAttributes() ^ sim_pathproperty_automatic_orientation);
        refresh();
    }
}

void CQDlgPathEdit::on_qqKeepXup_clicked()
{
    IF_UI_EVENT_CAN_READ_DATA
    {
        CPathCont_old* pathCont = getPathCont();
        if (pathCont != nullptr)
            pathCont->setAttributes(pathCont->getAttributes() ^ sim_pathproperty_keep_x_up);
        refresh();
    }
}

void CQDlgPathEdit::on_qqFactor1_editingFinished()
{
    if (!ui->qqFactor1->isModified())
        return;
    IF_UI_EVENT_CAN_WRITE_DATA
    {
        int selectedPointCount = GuiApp::mainWindow->editModeContainer->getEditModeBufferSize();
        if ((GuiApp::getEditModeType() == PATH_EDIT_MODE_OLD) && (selectedPointCount != 0))
        {
            CSimplePathPoint_old* it =
                GuiApp::mainWindow->editModeContainer->getPathEditMode()->getSimplePathPoint(selectedPointCount - 1);
            double bInt0, bInt1;
            it->getBezierFactors(bInt0, bInt1);
            bool ok;
            double newVal = GuiApp::getEvalDouble(ui->qqFactor1->text().toStdString().c_str(), &ok);
            if (ok)
                it->setBezierFactors(newVal, bInt1);
            GuiApp::mainWindow->editModeContainer->getEditModePathContainer_old()->actualizePath();
        }
        refresh();
    }
}

void CQDlgPathEdit::on_qqFactor2_editingFinished()
{
    if (!ui->qqFactor2->isModified())
        return;
    IF_UI_EVENT_CAN_WRITE_DATA
    {
        int selectedPointCount = GuiApp::mainWindow->editModeContainer->getEditModeBufferSize();
        if ((GuiApp::getEditModeType() == PATH_EDIT_MODE_OLD) && (selectedPointCount != 0))
        {
            CSimplePathPoint_old* it =
                GuiApp::mainWindow->editModeContainer->getPathEditMode()->getSimplePathPoint(selectedPointCount - 1);
            double bInt0, bInt1;
            it->getBezierFactors(bInt0, bInt1);
            bool ok;
            double newVal = GuiApp::getEvalDouble(ui->qqFactor2->text().toStdString().c_str(), &ok);
            if (ok)
                it->setBezierFactors(bInt0, newVal);
            GuiApp::mainWindow->editModeContainer->getEditModePathContainer_old()->actualizePath();
        }
        refresh();
    }
}

void CQDlgPathEdit::on_qqPointCount_editingFinished()
{
    if (!ui->qqPointCount->isModified())
        return;
    IF_UI_EVENT_CAN_WRITE_DATA
    {
        int selectedPointCount = GuiApp::mainWindow->editModeContainer->getEditModeBufferSize();
        if ((GuiApp::getEditModeType() == PATH_EDIT_MODE_OLD) && (selectedPointCount != 0))
        {
            CSimplePathPoint_old* it =
                GuiApp::mainWindow->editModeContainer->getPathEditMode()->getSimplePathPoint(selectedPointCount - 1);
            bool ok;
            int newVal = (int)GuiApp::getEvalInt(ui->qqPointCount->text().toStdString().c_str(), &ok);
            if (ok)
                it->setBezierPointCount(newVal);
            GuiApp::mainWindow->editModeContainer->getEditModePathContainer_old()->actualizePath();
        }
        refresh();
    }
}

void CQDlgPathEdit::on_qqVirtualDistance_editingFinished()
{
    if (!ui->qqVirtualDistance->isModified())
        return;
    IF_UI_EVENT_CAN_WRITE_DATA
    {
        int selectedPointCount = GuiApp::mainWindow->editModeContainer->getEditModeBufferSize();
        if ((GuiApp::getEditModeType() == PATH_EDIT_MODE_OLD) && (selectedPointCount != 0))
        {
            CSimplePathPoint_old* it =
                GuiApp::mainWindow->editModeContainer->getPathEditMode()->getSimplePathPoint(selectedPointCount - 1);
            bool ok;
            double newVal = GuiApp::getEvalDouble(ui->qqVirtualDistance->text().toStdString().c_str(), &ok);
            if (ok)
                it->setOnSpotDistance(newVal);
            GuiApp::mainWindow->editModeContainer->getEditModePathContainer_old()->actualizePath();
        }
        refresh();
    }
}

void CQDlgPathEdit::on_qqApply_clicked()
{
    IF_UI_EVENT_CAN_WRITE_DATA
    {
        int selectedPointCount = GuiApp::mainWindow->editModeContainer->getEditModeBufferSize();
        if ((GuiApp::getEditModeType() == PATH_EDIT_MODE_OLD) && (selectedPointCount >= 2))
        {
            CSimplePathPoint_old* it =
                GuiApp::mainWindow->editModeContainer->getPathEditMode()->getSimplePathPoint(selectedPointCount - 1);
            double bInt0, bInt1;
            it->getBezierFactors(bInt0, bInt1);
            for (int i = 0; i < selectedPointCount - 1; i++)
            {
                CSimplePathPoint_old* it2 =
                    GuiApp::mainWindow->editModeContainer->getPathEditMode()->getSimplePathPoint(i);
                it2->setBezierFactors(bInt0, bInt1);
                it2->setMaxRelAbsVelocity(it->getMaxRelAbsVelocity());
                it2->setBezierPointCount(it->getBezierPointCount());
                it2->setOnSpotDistance(it->getOnSpotDistance());
                it2->setAuxFlags(it->getAuxFlags());
                double auxChannels[4];
                it->getAuxChannels(auxChannels);
                it2->setAuxChannels(auxChannels);
            }
            GuiApp::mainWindow->editModeContainer->getEditModePathContainer_old()->actualizePath();
        }
        refresh();
    }
}

void CQDlgPathEdit::on_qqClearSelection_clicked()
{
    IF_UI_EVENT_CAN_READ_DATA
    {
        GuiApp::mainWindow->editModeContainer->deselectEditModeBuffer();
        refresh();
    }
}

void CQDlgPathEdit::on_qqInvertSelection_clicked()
{
    IF_UI_EVENT_CAN_READ_DATA
    {
        for (int i = 0;
             i < GuiApp::mainWindow->editModeContainer->getEditModePathContainer_old()->getSimplePathPointCount(); i++)
            GuiApp::mainWindow->editModeContainer->xorAddItemToEditModeBuffer(i, true);
        refresh();
    }
}

void CQDlgPathEdit::on_qqAuxFlags_editingFinished()
{
    if (!ui->qqAuxFlags->isModified())
        return;
    IF_UI_EVENT_CAN_WRITE_DATA
    {
        int selectedPointCount = GuiApp::mainWindow->editModeContainer->getEditModeBufferSize();
        if ((GuiApp::getEditModeType() == PATH_EDIT_MODE_OLD) && (selectedPointCount != 0))
        {
            CSimplePathPoint_old* it =
                GuiApp::mainWindow->editModeContainer->getPathEditMode()->getSimplePathPoint(selectedPointCount - 1);
            bool ok;
            int newVal = (int)GuiApp::getEvalInt(ui->qqAuxFlags->text().toStdString().c_str(), &ok);
            if (ok)
            {
                tt::limitValue(0, 65535, newVal);
                it->setAuxFlags(newVal);
            }
            GuiApp::mainWindow->editModeContainer->getEditModePathContainer_old()->actualizePath();
        }
        refresh();
    }
}

void CQDlgPathEdit::on_qqAuxChannel1_editingFinished()
{
    if (!ui->qqAuxChannel1->isModified())
        return;
    IF_UI_EVENT_CAN_WRITE_DATA
    {
        int selectedPointCount = GuiApp::mainWindow->editModeContainer->getEditModeBufferSize();
        if ((GuiApp::getEditModeType() == PATH_EDIT_MODE_OLD) && (selectedPointCount != 0))
        {
            CSimplePathPoint_old* it =
                GuiApp::mainWindow->editModeContainer->getPathEditMode()->getSimplePathPoint(selectedPointCount - 1);
            bool ok;
            double newVal = GuiApp::getEvalDouble(ui->qqAuxChannel1->text().toStdString().c_str(), &ok);
            if (ok)
            {
                double auxChannels[4];
                it->getAuxChannels(auxChannels);
                auxChannels[0] = newVal;
                it->setAuxChannels(auxChannels);
            }
            GuiApp::mainWindow->editModeContainer->getEditModePathContainer_old()->actualizePath();
        }
        refresh();
    }
}

void CQDlgPathEdit::on_qqAuxChannel2_editingFinished()
{
    if (!ui->qqAuxChannel2->isModified())
        return;
    IF_UI_EVENT_CAN_WRITE_DATA
    {
        int selectedPointCount = GuiApp::mainWindow->editModeContainer->getEditModeBufferSize();
        if ((GuiApp::getEditModeType() == PATH_EDIT_MODE_OLD) && (selectedPointCount != 0))
        {
            CSimplePathPoint_old* it =
                GuiApp::mainWindow->editModeContainer->getPathEditMode()->getSimplePathPoint(selectedPointCount - 1);
            bool ok;
            double newVal = GuiApp::getEvalDouble(ui->qqAuxChannel2->text().toStdString().c_str(), &ok);
            if (ok)
            {
                double auxChannels[4];
                it->getAuxChannels(auxChannels);
                auxChannels[1] = newVal;
                it->setAuxChannels(auxChannels);
            }
            GuiApp::mainWindow->editModeContainer->getEditModePathContainer_old()->actualizePath();
        }
        refresh();
    }
}

void CQDlgPathEdit::on_qqAuxChannel3_editingFinished()
{
    if (!ui->qqAuxChannel3->isModified())
        return;
    IF_UI_EVENT_CAN_WRITE_DATA
    {
        int selectedPointCount = GuiApp::mainWindow->editModeContainer->getEditModeBufferSize();
        if ((GuiApp::getEditModeType() == PATH_EDIT_MODE_OLD) && (selectedPointCount != 0))
        {
            CSimplePathPoint_old* it =
                GuiApp::mainWindow->editModeContainer->getPathEditMode()->getSimplePathPoint(selectedPointCount - 1);
            bool ok;
            double newVal = GuiApp::getEvalDouble(ui->qqAuxChannel3->text().toStdString().c_str(), &ok);
            if (ok)
            {
                double auxChannels[4];
                it->getAuxChannels(auxChannels);
                auxChannels[2] = newVal;
                it->setAuxChannels(auxChannels);
            }
            GuiApp::mainWindow->editModeContainer->getEditModePathContainer_old()->actualizePath();
        }
        refresh();
    }
}

void CQDlgPathEdit::on_qqAuxChannel4_editingFinished()
{
    if (!ui->qqAuxChannel4->isModified())
        return;
    IF_UI_EVENT_CAN_WRITE_DATA
    {
        int selectedPointCount = GuiApp::mainWindow->editModeContainer->getEditModeBufferSize();
        if ((GuiApp::getEditModeType() == PATH_EDIT_MODE_OLD) && (selectedPointCount != 0))
        {
            CSimplePathPoint_old* it =
                GuiApp::mainWindow->editModeContainer->getPathEditMode()->getSimplePathPoint(selectedPointCount - 1);
            bool ok;
            double newVal = GuiApp::getEvalDouble(ui->qqAuxChannel4->text().toStdString().c_str(), &ok);
            if (ok)
            {
                double auxChannels[4];
                it->getAuxChannels(auxChannels);
                auxChannels[3] = newVal;
                it->setAuxChannels(auxChannels);
            }
            GuiApp::mainWindow->editModeContainer->getEditModePathContainer_old()->actualizePath();
        }
        refresh();
    }
}

void CQDlgPathEdit::on_qqMakeDummies_clicked()
{
    IF_UI_EVENT_CAN_READ_DATA
    {
        GuiApp::mainWindow->editModeContainer->getPathEditMode()->makeDummies();
        App::appendSimulationThreadCommand(FULLREFRESH_ALL_DIALOGS_GUITRIGGEREDCMD);
    }
}
