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
    explicit Widget_AllGates(DLG_Home* parent = nullptr);
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

private:
    Ui::Widget_AllGates *ui;
    DLG_Home* m_pParent;
};

#endif // WIDGET_ALLGATES_H
