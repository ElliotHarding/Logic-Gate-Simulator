#ifndef WIDGET_CUSTOMGATES_H
#define WIDGET_CUSTOMGATES_H

#include <QWidget>

namespace Ui {
class Widget_CustomGates;
}

class Widget_CustomGates : public QWidget
{
    Q_OBJECT

public:
    explicit Widget_CustomGates(QWidget *parent = nullptr);
    ~Widget_CustomGates();

private slots:
    void on_Widget_CustomGates_destroyed();

private:
    Ui::Widget_CustomGates *ui;
};

#endif // WIDGET_CUSTOMGATES_H
