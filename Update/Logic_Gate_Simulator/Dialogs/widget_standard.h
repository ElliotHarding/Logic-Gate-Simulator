#ifndef WIDGET_STANDARD_H
#define WIDGET_STANDARD_H

#include <QWidget>

namespace Ui {
class Widget_Standard;
}

class Widget_Standard : public QWidget
{
    Q_OBJECT

public:
    explicit Widget_Standard(QWidget *parent = nullptr);
    ~Widget_Standard();

private:
    Ui::Widget_Standard *ui;
};

#endif // WIDGET_STANDARD_H
