#ifndef DLG_HOME_H
#define DLG_HOME_H

#include <QMainWindow>
#include <QMouseEvent>
#include "gameobjectpool.h"
#include "gateand.h"
#include "gateinputbox.h"
#include "gatenot.h"
#include "gateor.h"

class QMouseEvent;

namespace Ui {
class DLG_Home;
}

class DLG_Home : public QMainWindow
{
    Q_OBJECT

public:
    explicit DLG_Home(QWidget *parent = nullptr);
    ~DLG_Home();

protected:
    void mousePressEvent(QMouseEvent* mouseEvent) override;

private:
    Ui::DLG_Home *ui;

    GameObjectPool m_gameObjectController;

    ClickMode m_currentClickMode = CLICK_DRAG;

    int m_pageNumber = 2;

private slots:
    void on_btn_Drag_clicked();
    void on_btn_Delete_clicked();
    void on_btn_link_clicked();
    void on_btn_newPage_clicked();
    void on_btn_sourceGate_clicked();
    void on_btn_notGate_clicked();
    void on_btn_orGate_clicked();
    void on_btn_andGate_clicked();
};

#endif // DLG_HOME_H
