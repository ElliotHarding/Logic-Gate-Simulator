#ifndef DLG_HOME_H
#define DLG_HOME_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QFileDialog>
#include <QInputDialog>
#include <QProgressBar>
#include <QLabel>

#include "clickmode.h"
#include "gatereader.h"

#include "simpleslider.h"
#include "dlg_gateinfo.h"
#include "dlg_savegatecollection.h"
#include "dlg_message.h"
#include "dlg_configurefpga.h"

#include "movingwidget.h"
#include "widget_advanced.h"
#include "widget_allgates.h"
#include "widget_customgates.h"
#include "widget_inputgates.h"
#include "widget_standard.h"

#include "widget_spawnedgate.h"

class QMouseEvent;

namespace Ui {
class DLG_Home;
}

class TextLabel;
class DLG_LabelGateEdit; //Todo : move to own files

class DLG_Home : public QMainWindow
{
    Q_OBJECT

public:
    DLG_Home(QProgressBar* pProgressBar, QLabel* txtProgress, QWidget* parent = nullptr);
    ~DLG_Home();

    void SendUserMessage(const QString& message);
    bool SetZoomFactor(const qreal& zoomFactor, const bool& updateSlider = true);
    void AddGate(Gate* pGate);
    void GateSelected(Gate* pGate);
    void DeleteGate(Gate* pGate);
    void SelectionToolClicked();
    void UpdateCustomGateListWidget();
    void SetCurrentClickMode(const ClickMode& clickMode);
    void EditTextLabel(TextLabel* pTextLabelToEdit);
    void editFPGA(GateFPGA* pFPGA);

protected:
    Ui::DLG_Home *ui;

    //Dialogs
    DLG_GateInfo*           m_pDlgGateInfo;
    DLG_SaveGateCollection* m_pDlgSaveGateCollection;
    DLG_ConfigureFPGA*      m_pDlgEditFPGA;
    DLG_Message*            m_pDlgMessage;
    QFileDialog*            m_pDlgLoadGates;
    QInputDialog*           m_pDlgInput;
    DLG_LabelGateEdit*      m_pDlgTextLabelEdit;

    //Gate widgets
    Widget_AllGates*    m_pWidgetAllGates;
    Widget_CustomGates* m_pWidgetCustomGates;
    Widget_Advanced*    m_pWidgetAdvancedGates;
    Widget_Standard*    m_pWidgetStandardGates;
    Widget_InputGates*  m_pWidgetInputGates;
    MovingWidget* m_pCurrentShownGateWidget = nullptr;

    //Other widgets
    Widget_SpawnedGate* m_pSpawnedGateWidget;

    //Construction
    void InitalizeDialogsAndWidgets();

    //Widget animations
    void SwitchAddGatesWidget(MovingWidget* w1);

    //Zooming
    qreal m_zoomFactor;
    const int c_maxZoom = 1;
    const qreal c_minZoom = 0.2;
    const qreal c_incZoom = 0.1;
    ZoomSlider* m_pZoomSlider;

    //Gatefields
    int8_t m_iCurrentGateField;
    std::vector<GateField*> m_allGateFields;
    void addGateField(const QString& name);
    GateField* createNewGateField(const QString& name);

    QRect accountForUIOffsetts(const QRect& rect);

    //Saving
    Saver m_saver;

    //Clicking
    ClickMode m_currentClickMode = CLICK_DRAG;

private slots:

    //Tools buttons
    void on_btn_Drag_clicked();
    void on_btn_Delete_clicked();
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

    void on_btn_tasks_clicked();
};

#endif // DLG_HOME_H
