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
#include "logger.h"
#include "truthtabletobooleanexpressionthread.h"

#include "simpleslider.h"
#include "dlg_savegatecollection.h"
#include "dlg_message.h"
#include "dlg_editscript.h"
#include "dlg_truthtable.h"
#include "dlg_booleanexpressions.h"
#include "dlg_conversionconfig.h"
#include "dlg_gateinfo.h"

#include "movingwidget.h"
#include "widget_advanced.h"
#include "widget_allgates.h"
#include "widget_customgates.h"
#include "widget_inputgates.h"
#include "widget_standard.h"
#include "widget_spawnedgate.h"
#include "widget_helperpopup.h"

#include "textlabel.h"

class QMouseEvent;

namespace Ui {
class DLG_Home;
}

class DLG_Home : public QMainWindow
{
    Q_OBJECT

public:
    DLG_Home(QProgressBar* pProgressBar, QLabel* txtProgress, QWidget* parent = nullptr);
    ~DLG_Home();

    ///Direct user communication
    void sendUserMessage(const QString& message);
    bool requestUserInputString(const QString& title, const QString& context, QString& result);

    ///Gate operations
    void newlySpawnedGate(Gate* pGate, const QPoint& spawnPosition);
    void dropSpawnedGate(Gate* pGate);
    void gateSelected(Gate* pGate);
    void editTextLabel(TextLabel* pTextLabelToEdit);
    void editFPGA(GateFPGA* pFPGA);

    ///Gate field operations
    void setGateFieldName(GateField* pGateField, const QString& name);
    void startSaveGateCollection(GateCollection* pGateCollection);
    bool setZoomFactor(const qreal& zoomFactor, const bool& updateSlider = true);

    ///Click mode
    void setCurrentClickMode(const ClickMode& clickMode);
    void saveCurrentClickMode();
    void restorePreviousClickMode();
    ClickMode currentClickMode() const;

    ///Conversion options
    CircuitOptions getCircuitGenOptions() const;
    ConversionAlgorithm getCurrentConversionAlgorithm() const;

    ///Helper popup functions
    void nextHelperTip();
    void previousHelperTip();

    ///Other functions
    void selectionToolClicked();
    void updateCustomGateListWidget();
    void runRandomConversionThread(const TruthTable& truthTable, const GoalResult& goalResult);

public slots:
    ///Dialog interactions
    void showGeneratedCircuit(GateCollection* pGateCollection);
    void showGeneratedTruthTable(const TruthTable& truthTable);
    void showGeneratedBooleanExpressions(const std::vector<BooleanExpression> expressions);

    void failedRandomConversion(const QString& failMessage);

protected:
    void moveEvent(QMoveEvent* event) override;
    virtual void closeEvent(QCloseEvent *event) override;

    Ui::DLG_Home *ui;

    //Dialogs
    DLG_GateInfo*           m_pDlgGateInfo;
    DLG_SaveGateCollection* m_pDlgSaveGateCollection;
    DLG_EditScript*         m_pDlgEditScript;
    DLG_Message*            m_pDlgMessage;
    QFileDialog*            m_pDlgLoadGates;
    QInputDialog*           m_pDlgInput;
    DLG_LabelGateEdit*      m_pDlgTextLabelEdit;
    DLG_TruthTable*         m_pDlgTruthTable;
    DLG_BooleanExpressions* m_pDlgBooleanExpressions;
    DLG_ConversionConfig*   m_pDlgConversionConfig;

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
    void initalizeDialogsAndWidgets();

    //Widget animations
    void switchNewlySpawnedGatesWidget(MovingWidget* w1);

    //Zooming
    qreal m_zoomFactor;
    const int c_maxZoom = 1;
    const qreal c_minZoom = 0.2;
    const qreal c_incZoom = 0.1;
    ZoomSlider* m_pZoomSlider;

    //Gatefields
    int8_t m_iCurrentGateField;
    std::vector<GateField*> m_allGateFields;
    void newlySpawnedGateField(const QString& name);
    GateField* createNewGateField(const QString& name);

    //Helper tip popup
    HelperTip m_currentHelperTip;

    QRect accountForUIOffsetts(const QRect& rect) const;

    //Clicking
    ClickMode m_currentClickMode = CLICK_DRAG;
    ClickMode m_savedClickMode = CLICK_DRAG;

    RandomConversionThread* m_pRandomConversionThread;

private slots:

    //Tools buttons
    void on_btn_Drag_clicked();
    void on_btn_Delete_clicked();
    void on_btn_DeleteLink_clicked();
    void on_btn_click_clicked();
    void on_btn_Pan_clicked();

    void on_btn_newPage_clicked();
    void on_btn_setPageName_clicked();

    void on_btn_zoomIn_clicked();
    void on_btn_zoomOut_clicked();

    void on_btn_Save_clicked();
    void on_btn_load_clicked();

    void on_btn_undo_clicked();
    void on_btn_redo_clicked();

    void on_btn_createScript_clicked();
    void on_btn_createTruthTable();
    void on_btn_createExpressions();

    void on_btn_conversionConfig();

    //Gate widget switching
    void on_comboBox_currentIndexChanged(int index);

    //Tabs
    void on_PlayField_tabCloseRequested(int index);
    void on_PlayField_currentChanged(int index);
};

#endif // DLG_HOME_H
