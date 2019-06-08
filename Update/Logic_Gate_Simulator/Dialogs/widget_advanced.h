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
    explicit Widget_Advanced(QWidget *parent = nullptr);
    ~Widget_Advanced();

private:
    Ui::Widget_Advanced *ui;
};

#endif // WIDGET_ADVANCED_H
