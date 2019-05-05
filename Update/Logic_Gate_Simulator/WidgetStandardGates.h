#ifndef WIDGETSTANDARDGATES_H
#define WIDGETSTANDARDGATES_H

#include <QWidget>

namespace Ui {
class WidgetStandardGates;
}

class WidgetStandardGates : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetStandardGates(QWidget *parent = nullptr);
    ~WidgetStandardGates();

private:
    Ui::WidgetStandardGates *ui;
};

#endif // WIDGETSTANDARDGATES_H
