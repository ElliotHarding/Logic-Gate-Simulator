#ifndef WIDGET_TASKVIEW_H
#define WIDGET_TASKVIEW_H

#include <QWidget>

namespace Ui {
class widget_taskView;
}

class widget_taskView : public QWidget
{
    Q_OBJECT

public:
    explicit widget_taskView(QWidget *parent = nullptr);
    ~widget_taskView();

private:
    Ui::widget_taskView *ui;
};

#endif // WIDGET_TASKVIEW_H
