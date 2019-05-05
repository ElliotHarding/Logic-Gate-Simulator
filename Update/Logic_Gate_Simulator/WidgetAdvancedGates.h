#ifndef WIDGETADVANCEDGATES_H
#define WIDGETADVANCEDGATES_H

#include <QWidget>

namespace Ui {
class WidgetAdvancedGates;
}

class WidgetAdvancedGates : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetAdvancedGates(QWidget *parent = nullptr);
    ~WidgetAdvancedGates();

private:
    Ui::WidgetAdvancedGates *ui;
};

#endif // WIDGETADVANCEDGATES_H
