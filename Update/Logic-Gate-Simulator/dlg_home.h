#ifndef DLG_HOME_H
#define DLG_HOME_H

#include <QMainWindow>
#include <QMouseEvent>
#include "gameobjectpool.h"
#include "clickmode.h"

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

private slots:
    void on_btn_Drag_clicked();
    void on_btn_Delete_clicked();
    void on_btn_link_clicked();
};

#endif // DLG_HOME_H
