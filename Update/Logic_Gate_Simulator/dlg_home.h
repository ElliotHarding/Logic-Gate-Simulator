#ifndef DLG_HOME_H
#define DLG_HOME_H

#include <QMainWindow>
#include <QMouseEvent>
#include "gateand.h"
#include "gateinputbox.h"
#include "gatenot.h"
#include "gateor.h"
#include "gatefield.h"

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

private:
    Ui::DLG_Home *ui;

    int m_pageNumber = 2;

    GateField* m_currentGateField;

private slots:
    void on_btn_Drag_clicked();
    void on_btn_Delete_clicked();
    void on_btn_link_clicked();
    void on_btn_newPage_clicked();
    void on_btn_sourceGate_clicked();
    void on_btn_notGate_clicked();
    void on_btn_orGate_clicked();
    void on_btn_andGate_clicked();
    void on_PlayField_tabCloseRequested(int index);
    void on_PlayField_currentChanged(int index);
};

#endif // DLG_HOME_H
