#ifndef DLG_HOME_H
#define DLG_HOME_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QThread>

#include "allgates.h"
#include "simpleslider.h"
#include "dlg_gateinfo.h"
#include "gatefield.h"

#include "widget_advanced.h"
#include "widget_allgates.h"
#include "widget_customgates.h"
#include "widget_inputgates.h"
#include "widget_standard.h"

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
    void AddGate(Gate* g);
    void GateSelected(Gate* g);
    void DeleteGate(Gate* g);

private:
    Ui::DLG_Home *ui;

    //Ui elements
    DLG_GateInfo* m_gateInfo;
    const QPoint c_GateInfoWidgetPos = QPoint(850,350);

    //Gate widgets
    Widget_AllGates*    m_pWidgetAllGates;
    Widget_CustomGates* m_pWidgetCustomGates;
    Widget_Advanced*    m_pWidgetAdvancedGates;
    Widget_Standard*    m_pWidgetStandardGates;
    Widget_InputGates*  m_pWidgetInputGates;
    QWidget* m_pCurrentShownGateWidget = nullptr;
    const QPoint c_GateWidgetPosShowing = QPoint(0,60);
    const QPoint c_GateWidgetPosHidden = QPoint(-160,60);

    //Widget animations
    void MoveWidget(QWidget* w, int xDir);
    void SwitchWidgets(QWidget* w1);

    //Zooming
    qreal m_ZoomFactor;
    const int c_maxZoom = 10;
    const qreal c_minZoom = 0.25;    

    //Updating gates
    LogicUpdateThread* m_updateThread;

    //Gatefields
    GateField* m_currentGateField;
    std::vector<GateField*> m_allGateFields;
    void addGateField(QString name);

    //Controls
    SimpleSlider* m_zoomSlider;
    const int c_zoomSliderWidth = 80;
    const QPoint c_zoomSliderPos = QPoint(900,130);

private slots:
    void on_btn_Drag_clicked();
    void on_btn_Delete_clicked();
    void on_btn_link_clicked();
    void on_btn_newPage_clicked();
    void on_PlayField_tabCloseRequested(int index);
    void on_PlayField_currentChanged(int index);
    void on_btn_DeleteLink_clicked();
    void on_btn_click_clicked();
    void on_btn_zoomIn_clicked();
    void on_btn_zoomOut_clicked();
    void on_btn_SelectionTool_clicked();
    void on_btn_Save_clicked();
    void on_btn_load_clicked();
    void on_btn_test_clicked();
    void on_menu_btn_allGates_clicked();
    void on_menu_btn_customGates_clicked();
    void on_menu_btn_InputGates_clicked();
    void on_menu_btn_standardGates_clicked();
    void on_menu_btn_advancedGates_clicked();
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
