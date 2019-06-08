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
    explicit Widget_InputGates(QWidget *parent = nullptr);
    ~Widget_InputGates();

private:
    Ui::Widget_InputGates *ui;
};

#endif // WIDGET_INPUTGATES_H
