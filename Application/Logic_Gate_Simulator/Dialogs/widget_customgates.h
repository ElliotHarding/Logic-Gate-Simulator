#ifndef WIDGET_CUSTOMGATES_H
#define WIDGET_CUSTOMGATES_H

#include "movingwidget.h"
#include "vector"
#include "gatecollection.h"
#include <QListWidgetItem>

namespace Ui {
class Widget_CustomGates;
}

class DLG_Home;
class Widget_CustomGates : public MovingWidget
{
    Q_OBJECT

public:
    explicit Widget_CustomGates(DLG_Home* pParent, bool show = false, QPoint loc = QPoint(0,0));
    ~Widget_CustomGates();

    void UpdateList();

private slots:
    void on_customGateListWidget_currentRowChanged(int currentRow);
    void on_btn_SelectionTool_clicked();

    void on_customGateListWidget_itemClicked(QListWidgetItem *item);
    void createItem();

private:
    Ui::Widget_CustomGates *ui;
    std::vector<QString> m_customGatesNames;
    int m_currentRow = -1;
};

#endif // WIDGET_CUSTOMGATES_H
