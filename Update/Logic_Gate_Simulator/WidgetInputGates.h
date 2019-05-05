#ifndef WIDGETINPUTGATES_H
#define WIDGETINPUTGATES_H

#include <QWidget>

namespace Ui {
class WidgetInputGates;
}

class WidgetInputGates : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetInputGates(QWidget *parent = nullptr);
    ~WidgetInputGates();

private:
    Ui::WidgetInputGates *ui;
};

#endif // WIDGETINPUTGATES_H
