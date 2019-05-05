#ifndef DLG_GATEINFO_H
#define DLG_GATEINFO_H

#include <QWidget>

namespace Ui {
class DLG_GateInfo;
}

class Gate;
class DLG_GateInfo : public QWidget
{
    Q_OBJECT

public:
    explicit DLG_GateInfo(QWidget *parent = nullptr);
    ~DLG_GateInfo();

    void setGate(Gate* g);

private slots:
    void on_btn_Delete_clicked();
    void on_checkBox_stateChanged(int arg1);

private:
    Ui::DLG_GateInfo *ui;

    Gate* m_gateDisplayed;
};

#endif // DLG_GATEINFO_H
