#ifndef WIDGETCUSTOMGATES_H
#define WIDGETCUSTOMGATES_H

#include <QWidget>

namespace Ui {
class Ui_WidgetCustomGates;
}

class WidgetCustomGates : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetCustomGates(QWidget *parent = nullptr);
    ~WidgetCustomGates();

private:
    Ui::Ui_WidgetCustomGates *ui;
};

#endif // WIDGETCUSTOMGATES_H
