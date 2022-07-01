#ifndef WIDGET_INPUTGATES_H
#define WIDGET_INPUTGATES_H

#include "movingwidget.h"

namespace Ui {
class Widget_InputGates;
}

class Widget_InputGates : public MovingWidget
{
    Q_OBJECT

public:
    explicit Widget_InputGates(DLG_Home *DLG_Home = nullptr, bool show = false, QPoint loc = QPoint(0,0));
    ~Widget_InputGates();

private slots:
    void on_btn_sourceGate_clicked();
    void on_btn_inputOn_clicked();
    void on_btn_inputOff_clicked();
    void on_btn_timerGate_clicked();

private:
    Ui::Widget_InputGates *ui;

    QPoint spawnPosition(const QPoint& buttonPoint) const;
};

#endif // WIDGET_INPUTGATES_H
