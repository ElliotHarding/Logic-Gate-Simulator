#ifndef WIDGET_ALLGATES_H
#define WIDGET_ALLGATES_H

#include "movingwidget.h"

namespace Ui {
class Widget_AllGates;
}

class DLG_Home;
class Widget_AllGates : public MovingWidget
{
    Q_OBJECT

public:
    explicit Widget_AllGates(DLG_Home* parent = nullptr, bool show = false, QPoint loc = QPoint(0,0));
    ~Widget_AllGates();

private slots:
    void on_btn_andGate_clicked();
    void on_btn_notGate_clicked();
    void on_btn_orGate_clicked();
    void on_btn_recieverGate_clicked();
    void on_btn_sourceGate_clicked();
    void on_btn_timerGate_clicked();
    void on_btn_inputOn_clicked();
    void on_btn_inputOff_clicked();
    void on_btn_GateTriAnd_clicked();
    void on_btn_GateTriOr_clicked();
    void on_btn_numberOutputGate_clicked();
    void on_btn_GateEor_clicked();
    void on_btn_GateTriEor_clicked();

private:
    Ui::Widget_AllGates *ui;

    void SetupGateButtons();
};

#endif // WIDGET_ALLGATES_H
