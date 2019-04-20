#ifndef DLG_HOME_H
#define DLG_HOME_H

#include <QMainWindow>
#include <QMouseEvent>
#include "gateand.h"
#include "gateinputbox.h"
#include "gatenot.h"
#include "gateor.h"
#include "gatefield.h"
#include <QThread>

class QMouseEvent;
class LogicUpdateThread;

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

    //Updating gates
    LogicUpdateThread* m_updateThread;
    void UpdateThread();

    //Gatefields
    GateField* m_currentGateField;
    std::vector<GateField*> m_allGateFields;

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
    void on_btn_DeleteLink_clicked();
    void on_btn_click_clicked();
};


//Update thread for gatefields (pages)
//------------------------------------
// Calls the update function of all the gates in all of the gateFields
// Runs continuously
class LogicUpdateThread : public QThread
{
    Q_OBJECT
public:
    LogicUpdateThread(std::vector<GateField*>* allGateFields);
    void stopRunning();

private:
    void run() override;

    bool m_bStop;
    std::vector<GateField*>* m_pAllGateFields;
};

#endif // DLG_HOME_H
