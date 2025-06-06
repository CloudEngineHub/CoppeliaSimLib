#ifndef QDLGIMAGECOLOR_H
#define QDLGIMAGECOLOR_H

#include <vDialog.h>
#include <simLib/simTypes.h>

namespace Ui
{
class CQDlgImageColor;
}

class CQDlgImageColor : public VDialog
{
    Q_OBJECT

  public:
    explicit CQDlgImageColor(QWidget* parent = 0);
    ~CQDlgImageColor();

    void cancelEvent() override;
    void okEvent() override;

    void refresh();

    bool sameAsFog;
    double red;
    double green;
    double blue;

  private slots:
    void on_qqFromFogColor_clicked();

    void on_qqRed_editingFinished();

    void on_qqGreen_editingFinished();

    void on_qqBlue_editingFinished();

    void on_qqOkCancel_accepted();

    void on_qqOkCancel_rejected();

  private:
    Ui::CQDlgImageColor* ui;
};

#endif // QDLGIMAGECOLOR_H
