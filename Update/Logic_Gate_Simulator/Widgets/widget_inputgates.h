#ifndef WIDGET_INPUTGATES_H
#define WIDGET_INPUTGATES_H

#include <QWidget>

namespace Ui {
class Widget_InputGates;
}

class Widget_InputGates : public QWidget
{
    Q_OBJECT

public:
    explicit Widget_InputGates(QWidget *parent = nullptr);
    ~Widget_InputGates();

private:
    Ui::Widget_InputGates *ui;
};

#endif // WIDGET_INPUTGATES_H
