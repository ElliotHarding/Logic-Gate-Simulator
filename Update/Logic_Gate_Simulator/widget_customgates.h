#ifndef WIDGET_CUSTOMGATES_H
#define WIDGET_CUSTOMGATES_H

#include <QWidget>
#include "vector"
#include "gatecollection.h"

namespace Ui {
class Widget_CustomGates;
}

class DLG_Home;
class Widget_CustomGates : public QWidget
{
    Q_OBJECT

public:
    explicit Widget_CustomGates(DLG_Home* pParent);
    ~Widget_CustomGates();

private slots:
    void on_customGateListWidget_currentRowChanged(int currentRow);

private:
    Ui::Widget_CustomGates *ui;
    DLG_Home* m_pParent;
    std::vector<GateCollection> m_customGates;
};

#endif // WIDGET_CUSTOMGATES_H