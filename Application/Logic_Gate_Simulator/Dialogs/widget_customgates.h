#ifndef WIDGET_CUSTOMGATES_H
#define WIDGET_CUSTOMGATES_H

#include "movingwidget.h"
#include "vector"
#include "gatereader.h"
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
    void on_btn_Delete_clicked();
    void on_btn_Create_clicked();
    void on_customGateListWidget_itemClicked(QListWidgetItem *item);

private:
    Ui::Widget_CustomGates *ui;

    CustomGateReader m_customGateReader;

    QPalette m_palActive;
    QPalette m_palInActive;

    int m_currentRow = -1;

    bool m_bDeleting = false;

    void DeleteItem(int index);
    void CreateItem(const QString& name);
};

#endif // WIDGET_CUSTOMGATES_H
