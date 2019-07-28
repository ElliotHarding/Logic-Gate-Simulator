#ifndef WIDGET_STANDARD_H
#define WIDGET_STANDARD_H

#include "movingwidget.h"

namespace Ui {
class Widget_Standard;
}

class Widget_Standard : public MovingWidget
{
    Q_OBJECT

public:
    explicit Widget_Standard(DLG_Home *parent = nullptr, bool show = false, QPoint loc = QPoint(0,0));
    ~Widget_Standard();

private slots:
    void on_btn_orGate_clicked();
    void on_btn_notGate_clicked();
    void on_btn_andGate_clicked();
    void on_btn_GateTriOr_clicked();
    void on_btn_GateTriAnd_clicked();

    void on_btn_GateEor_clicked();

    void on_btn_GateTriEor_clicked();

private:
    Ui::Widget_Standard *ui;
};

#endif // WIDGET_STANDARD_H
