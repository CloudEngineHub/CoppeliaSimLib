
#ifndef QDLGGEOMETRY_H
#define QDLGGEOMETRY_H

#include <dlgEx.h>

namespace Ui
{
class CQDlgGeometry;
}

class CQDlgGeometry : public CDlgEx
{
    Q_OBJECT

  public:
    explicit CQDlgGeometry(QWidget* parent = 0);
    ~CQDlgGeometry();

    void refresh() override;

    void cancelEvent() override;
    bool needsDestruction() override;
    bool isLinkedDataValid();
    bool doesInstanceSwitchRequireDestruction() override;

    void _initialize(int shapeHandle);
    void _setCurrentSizes();
    void _readSize(int index);
    void _readScaling(int index);

    static void display(int shapeHandle, QWidget* theParentWindow);

    int _shapeHandle;
    double scaleVal[3];
    double sizeVal[3];
    double rotationVal[3];
    bool keepProp;
    bool isPureShape;
    bool isConvex;
    bool isGroup;
    bool insideRefreshTriggered;
    std::string titleText;
    int vertexCount;
    int triangleCount;

  private slots:
    void on_qqKeepProp_clicked();

    void on_qqSizeX_editingFinished();

    void on_qqSizeY_editingFinished();

    void on_qqSizeZ_editingFinished();

    void on_qqScaleX_editingFinished();

    void on_qqScaleY_editingFinished();

    void on_qqScaleZ_editingFinished();

    void on_qqApplySize_clicked();

    void on_qqApplyScale_clicked();

  private:
    Ui::CQDlgGeometry* ui;
};

#endif // QDLGGEOMETRY_H
