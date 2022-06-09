#ifndef DLG_GATEINFO_H
#define DLG_GATEINFO_H

#include <QWidget>

//Forward declerations
namespace Ui {
class DLG_GateInfo;
}
class DLG_Home;
class Gate;

class DLG_GateInfo : public QWidget
{
    Q_OBJECT

public:
    explicit DLG_GateInfo(DLG_Home* parent = nullptr);
    ~DLG_GateInfo();

    void setGate(Gate* g);

private slots:
    void on_btn_DeleteGate_clicked();
    void on_lineEdit_Frequency_editingFinished();
    void on_signalCheck_clicked();
    void on_cb_Enabled_clicked();
    void on_cb_DragMode_clicked();
    void on_btn_Edit_clicked();

private:
    Ui::DLG_GateInfo *ui;

    DLG_Home* m_pParent = nullptr;

    Gate* m_gateDisplayed = nullptr;

    bool m_bDragModeAll = true;

    void UiWhenNoGateSelected();
};

#endif // DLG_GATEINFO_H
