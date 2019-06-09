#ifndef DLG_HOME_H
#define DLG_HOME_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QThread>
#include <QFileDialog>
#include <QInputDialog>
#include <QProgressBar>
#include <QLabel>

#include "allgates.h"
#include "gatefield.h"

#include "simpleslider.h"
#include "dlg_gateinfo.h"
#include "dlg_savegatecollection.h"
#include "dlg_message.h"

#include "movingwidget.h"
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
    explicit DLG_Home(QProgressBar* progressBar, QLabel* txtProgress, QWidget* parent = nullptr);
    ~DLG_Home();

    void SendUserMessage(QString message);
    void SetZoomFactor(float zoomFactor, bool updateSlider = true);
    void AddGate(Gate* g);
    void GateSelected(Gate* g);
    void DeleteGate(Gate* g);
    void SelectionToolClicked();
    void UpdateCustomGateListWidget();

private:
    Ui::DLG_Home *ui;

    //Dialogs
    DLG_GateInfo*           m_pDlgGateInfo;
    DLG_SaveGateCollection* m_pDlgSaveGateCollection;
    DLG_Message*            m_pDlgMessage;
    QFileDialog*            m_pDlgLoadGates;
    QInputDialog*           m_pDlgInput;

    //Gate widgets
    Widget_AllGates*    m_pWidgetAllGates;
    Widget_CustomGates* m_pWidgetCustomGates;
    Widget_Advanced*    m_pWidgetAdvancedGates;
    Widget_Standard*    m_pWidgetStandardGates;
    Widget_InputGates*  m_pWidgetInputGates;
    MovingWidget* m_pCurrentShownGateWidget = nullptr;

    //Controls
    SimpleSlider* m_zoomSlider;

    //Widget animations
    void SwitchWidgets(MovingWidget* w1);
    const int c_moveWidgetsIncrement = 2;
    const int c_moveWidgetDistance = 160;

    //Zooming
    qreal m_ZoomFactor;
    const int c_maxZoom = 1;
    const qreal c_minZoom = 0.2;

    //Gatefields
    GateField* m_currentGateField = nullptr;
    std::vector<GateField*> m_allGateFields;
    void addGateField(QString& name);
    GateField* createNewGateField(QString name);

    QRect accountForUIOffsetts(const QRect& rect);

    QString PathToFileName(const QString);

private slots:

    //Tools buttons
    void on_btn_Drag_clicked();
    void on_btn_Delete_clicked();
    void on_btn_link_clicked();
    void on_btn_DeleteLink_clicked();
    void on_btn_click_clicked();
    void on_btn_Pan_clicked();

    void on_btn_newPage_clicked();

    void on_btn_zoomIn_clicked();
    void on_btn_zoomOut_clicked();

    void on_btn_Save_clicked();
    void on_btn_load_clicked();

    void on_btn_undo_clicked();
    void on_btn_redo_clicked();

    //Gate widget switching
    void on_comboBox_currentIndexChanged(int index);

    //Tabs
    void on_PlayField_tabCloseRequested(int index);
    void on_PlayField_currentChanged(int index);

};

#endif // DLG_HOME_H
