#ifndef WIDGET_CUSTOMGATES_H
#define WIDGET_CUSTOMGATES_H

#include "movingwidget.h"
#include "gatereader.h"

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
    void on_btn_SelectionTool_clicked();
    void on_btn_Delete_clicked();
    void on_customGateListWidget_itemClicked(QListWidgetItem *item);

private:
    Ui::Widget_CustomGates *ui;

    CustomGateReader m_customGateReader;

    QPalette m_palActive;
    QPalette m_palInActive;

    bool m_bDeleting;

    void DeleteItem(QListWidgetItem* item);
    void CreateItem(const QString& name);
};

#endif // WIDGET_CUSTOMGATES_H
