#ifndef DLG_GATEINFO_H
#define DLG_GATEINFO_H

#include <QWidget>

#include "gatefield.h"

//Forward declerations
namespace Ui {
class DLG_GateInfo;
}
class DLG_Home;

class DLG_GateInfo : public QWidget
{
    Q_OBJECT

public:
    explicit DLG_GateInfo(DLG_Home* parent = nullptr);
    ~DLG_GateInfo();

    void setGate(Gate* g);
    void setGateField(GateField* pGateField);

private slots:
    void on_btn_DeleteGate_clicked();
    void on_lineEdit_Frequency_editingFinished();
    void on_signalCheck_clicked();
    void on_btn_Edit_clicked();

    void on_lineEdit_pageUpdateFrequency_editingFinished();

    void on_btn_drag_clicked();

    void on_btn_save_clicked();

    void on_btn_truthTable_clicked();

    void on_btn_expression_clicked();

    void on_btn_DeleteGate2_clicked();

    void on_btn_label_clicked();

    void on_btn_label2_clicked();

private:
    Ui::DLG_GateInfo *ui;

    DLG_Home* m_pParent = nullptr;

    Gate* m_pGateDisplayed = nullptr;
    GateField* m_pGateField = nullptr;

    void UiWhenNoGateSelected();
};

#endif // DLG_GATEINFO_H
