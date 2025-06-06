
#ifndef QDLGSHAPEDYN_H
#define QDLGSHAPEDYN_H

#include <dlgEx.h>

namespace Ui
{
class CQDlgShapeDyn;
}

class CQDlgShapeDyn : public CDlgEx
{
    Q_OBJECT

  public:
    explicit CQDlgShapeDyn(QWidget* parent = 0);
    ~CQDlgShapeDyn();

    void refresh() override;
    void cancelEvent() override;

    static bool showDynamicWindow;
    static bool masslessInertia;
    bool inMainRefreshRoutine;

  private slots:
    void on_qqDynamic_clicked();

    void on_qqSleepModeStart_clicked();

    void on_qqAdjustEngineProperties_clicked();

    void on_qqRespondable_clicked();

    void on_a_1_clicked();
    void on_a_2_clicked();
    void on_a_3_clicked();
    void on_a_4_clicked();
    void on_a_5_clicked();
    void on_a_6_clicked();
    void on_a_7_clicked();
    void on_a_8_clicked();
    void on_a_9_clicked();
    void on_a_10_clicked();
    void on_a_11_clicked();
    void on_a_12_clicked();
    void on_a_13_clicked();
    void on_a_14_clicked();
    void on_a_15_clicked();
    void on_a_16_clicked();

    void on_qqMass_editingFinished();

    void on_qqI00_editingFinished();
    void on_qqI01_editingFinished();
    void on_qqI02_editingFinished();
    void on_qqI10_editingFinished();
    void on_qqI11_editingFinished();
    void on_qqI12_editingFinished();
    void on_qqI20_editingFinished();
    void on_qqI21_editingFinished();
    void on_qqI22_editingFinished();

    void on_qqPX_editingFinished();

    void on_qqPY_editingFinished();

    void on_qqPZ_editingFinished();

    void on_qqApplyMassAndInertiaProperties_clicked();

    void on_qqAutomaticToNonStatic_clicked();

    void on_qqApplyMaterialProperties_clicked();

    void on_qqMassless_clicked();

  private:
    void _inertiaChanged(size_t row, size_t col, QLineEdit* ct);
    void _toggleRespondableBits(int bits);

    Ui::CQDlgShapeDyn* ui;
};

#endif // QDLGSHAPEDYN_H
