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
    explicit Widget_Standard(QWidget *parent = nullptr);
    ~Widget_Standard();

private:
    Ui::Widget_Standard *ui;
};

#endif // WIDGET_STANDARD_H
