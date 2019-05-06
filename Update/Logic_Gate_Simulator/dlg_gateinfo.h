#ifndef DLG_GATEINFO_H
#define DLG_GATEINFO_H

#include <QWidget>

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
    void on_checkBox_clicked();
    void on_btn_DeleteGate_clicked();
    void on_lineEdit_Frequency_editingFinished();

private:
    Ui::DLG_GateInfo *ui;
    DLG_Home* m_pParent;
    Gate* m_gateDisplayed;
};

#endif // DLG_GATEINFO_H
