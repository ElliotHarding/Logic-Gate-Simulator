#ifndef MOVINGTABWIDGET_H
#define MOVINGTABWIDGET_H

#include <QWidget>

namespace Ui {
class MovingTabWidget;
}

class MovingTabWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MovingTabWidget(QWidget *parent = nullptr);
    ~MovingTabWidget();

private:
    Ui::MovingTabWidget *ui;
};

#endif // MOVINGTABWIDGET_H
