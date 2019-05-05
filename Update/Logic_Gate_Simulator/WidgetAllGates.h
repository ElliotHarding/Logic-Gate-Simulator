#ifndef WIDGET_ALLGATES_H
#define WIDGET_ALLGATES_H

#include <QWidget>

namespace Ui {
class WidgetAllGates;
}

class WidgetAllGates : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetAllGates(QWidget *parent = nullptr);
    ~WidgetAllGates();

private:
    Ui::WidgetAllGates *ui;
};

#endif // WIDGET_ALLGATES_H
