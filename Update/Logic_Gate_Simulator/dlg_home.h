#ifndef DLG_HOME_H
#define DLG_HOME_H

#include <QMainWindow>
#include <QMouseEvent>
#include "simpleslider.h"
#include "gateand.h"
#include "gatenot.h"
#include "gateor.h"
#include "gateinputbox.h"
#include "gateoutputbox.h"
#include "gatefield.h"
#include "gatecollection.h"
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

    void SetZoomFactor(float zoomFactor);

private:
    Ui::DLG_Home *ui;

    //Zooming
    qreal m_ZoomFactor;
    const int c_maxZoom = 10;
    const qreal c_minZoom = 0.25;    

    //Updating gates
    LogicUpdateThread* m_updateThread;

    //Gatefields
    GateField* m_currentGateField;
    std::vector<GateField*> m_allGateFields;

    //Controls
    SimpleSlider* m_zoomSlider;
    const int c_zoomSliderWidth = 80;
    const QPoint c_zoomSliderPos = QPoint(700,135);

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
    void on_btn_recieverGate_clicked();
    void on_btn_zoomIn_clicked();
    void on_btn_zoomOut_clicked();
    void on_btn_SelectionTool_clicked();
    void on_btn_gateCollection_clicked();
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
    ~LogicUpdateThread() override;
    void stopRunning();

private:
    void run() override;

    bool m_bStop;
    std::vector<GateField*>* m_pAllGateFields;
};

#endif // DLG_HOME_H
