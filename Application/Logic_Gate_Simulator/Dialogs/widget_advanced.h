#ifndef WIDGET_ADVANCED_H
#define WIDGET_ADVANCED_H

#include "movingwidget.h"

namespace Ui {
class Widget_Advanced;
}

class Widget_Advanced : public MovingWidget
{
    Q_OBJECT

public:
    explicit Widget_Advanced(DLG_Home *parent = nullptr, bool show = false, QPoint loc = QPoint(0,0));
    ~Widget_Advanced();

private slots:
    void on_btn_numberOutputGate_clicked();
    void on_btn_recieverGate_clicked();
    void on_btn_labelGate_clicked();
    void on_btn_fpgaGate_clicked();

private:
    Ui::Widget_Advanced *ui;
};

#endif // WIDGET_ADVANCED_H
