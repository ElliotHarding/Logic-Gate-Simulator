#ifndef WIDGET_ALLGATES_H
#define WIDGET_ALLGATES_H

#include <QWidget>

namespace Ui {
class Widget_AllGates;
}

class Widget_AllGates : public QWidget
{
    Q_OBJECT

public:
    explicit Widget_AllGates(QWidget *parent = nullptr);
    ~Widget_AllGates();

private:
    Ui::Widget_AllGates *ui;
};

#endif // WIDGET_ALLGATES_H
