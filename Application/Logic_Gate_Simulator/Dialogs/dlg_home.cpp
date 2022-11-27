#include "dlg_home.h"
#include "ui_dlg_home.h"
#include "gatefield.h"
#include "customsettings.h"

#include <QLayout>
#include <QLibrary>
#include <QDesktopWidget>

namespace Settings
{
const QPoint UiOffset = QPoint(0, 20); //Todo ~ figure out why this is needed

const QString DefaultPageName = "New Page";
}

DLG_Home::DLG_Home(QProgressBar* pProgressBar, QLabel* txtProgress, QWidget *parent) :
    QMainWindow(parent),    
    ui(new Ui::DLG_Home),
    m_zoomFactor(-1),
    m_pRandomConversionThread(new RandomConversionThread())
{

    pProgressBar->setValue(20);
    txtProgress->setText("Setting up UI...");

    {
        ui->setupUi(this);
    }

    pProgressBar->setValue(45);
    txtProgress->setText("Loading additional libs");

    {
        QLibrary lib( "Comctl32.dll" );
        lib.setLoadHints( QLibrary::ResolveAllSymbolsHint );
        lib.load();
    }

    qRegisterMetaType<std::vector<BooleanExpression>>("std::vector<BooleanExpression>");

    pProgressBar->setValue(66);
    txtProgress->setText("Intializing child components");

    {
        m_allGateFields.reserve(10);
    }
    {
        setMouseTracking(true);
        ui->PlayField->clear();
    }

    //Construction
    initalizeDialogsAndWidgets();

    //Connections
    {
        connect(ui->actionNew_page, SIGNAL(triggered()), this, SLOT(on_btn_newPage_clicked()));
        connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(on_btn_Save_clicked()));
        connect(ui->actionLoad, SIGNAL(triggered()), this, SLOT(on_btn_load_clicked()));
        connect(ui->actionPan, SIGNAL(triggered()), this, SLOT(on_btn_Pan_clicked()));
        connect(ui->actionEdit, SIGNAL(triggered()), this, SLOT(on_btn_click_clicked()));
        connect(ui->actionDrag, SIGNAL(triggered()), this, SLOT(on_btn_Drag_clicked()));
        connect(ui->actionLoad, SIGNAL(triggered()), this, SLOT(on_btn_load_clicked()));
        connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(on_btn_Save_clicked()));
        connect(ui->actionUndo, SIGNAL(triggered()), this, SLOT(on_btn_undo_clicked()));
        connect(ui->actionRedo, SIGNAL(triggered()), this, SLOT(on_btn_redo_clicked()));
        connect(ui->actionZoom, SIGNAL(triggered()), this, SLOT(on_btn_zoomIn_clicked()));
        connect(ui->actionDelete, SIGNAL(triggered()), this, SLOT(on_btn_Delete_clicked()));
        connect(ui->actionZoom_2, SIGNAL(triggered()), this, SLOT(on_btn_zoomOut_clicked()));
        connect(ui->actionDelete_Link, SIGNAL(triggered()), this, SLOT(on_btn_DeleteLink_clicked()));
        connect(ui->actionSet_Page_Name, SIGNAL(triggered()), this, SLOT(on_btn_setPageName_clicked()));
        connect(ui->actionCreate_Script, SIGNAL(triggered()), this, SLOT(on_btn_createScript_clicked()));
        connect(ui->actionCreate_Truth_Table, SIGNAL(triggered()), this, SLOT(on_btn_createTruthTable()));
        connect(ui->actionCreate_Expressions, SIGNAL(triggered()), this, SLOT(on_btn_createExpressions()));
        connect(ui->actionConversion_And_Generation_Settings, SIGNAL(triggered()), this, SLOT(on_btn_conversionConfig()));

        connect(m_pRandomConversionThread, SIGNAL(circuitGenSuccess(GateCollection*)), this, SLOT(showGeneratedCircuit(GateCollection*)));
        connect(m_pRandomConversionThread, SIGNAL(expressionsGenSuccess(const std::vector<BooleanExpression>)), this, SLOT(showGeneratedBooleanExpressions(const std::vector<BooleanExpression>)));
        connect(m_pRandomConversionThread, SIGNAL(generationFailure(const QString&)), this, SLOT(failedRandomConversion(const QString&)));
    }

    {
        newlySpawnedGateField(Settings::DefaultPageName);
    }

    pProgressBar->setValue(100);
    txtProgress->setText("Done!");
}

void DLG_Home::initalizeDialogsAndWidgets()
{
    //Dialogs
    m_pDlgLoadGates = new QFileDialog(this);
    m_pDlgInput = new QInputDialog(this);
    m_pDlgSaveGateCollection = new DLG_SaveGateCollection(this);
    m_pDlgGateInfo = new DLG_GateInfo(this);
    m_pDlgMessage = new DLG_Message(this);
    m_pDlgTextLabelEdit = new DLG_LabelGateEdit();
    m_pDlgEditScript = new DLG_EditScript(this);
    m_pDlgTruthTable = new DLG_TruthTable(this);
    m_pDlgBooleanExpressions = new DLG_BooleanExpressions(this);
    m_pDlgConversionConfig = new DLG_ConversionConfig(this);

    //Other widgets
    m_pSpawnedGateWidget = new Widget_SpawnedGate(this);
    m_pHelperPopup = new Widget_HelperPopup(this);
    m_pHelperPopup->raise();
    m_currentHelperTip = HT_First;
    m_pHelperPopup->popup(QApplication::desktop()->screen()->rect().center() - QPoint(50, 50), "Welcome to logic gate simulator. \n Use the arrows to continue the tutorial.", false, 10);

    //Gate widgets
    const QPoint c_GateWidgetPos = accountForUIOffsetts(ui->layout_GateWidget->geometry()).topLeft();
    m_pWidgetAllGates = new Widget_AllGates(this, true, c_GateWidgetPos);
    m_pWidgetCustomGates = new Widget_CustomGates(this, false, c_GateWidgetPos);
    m_pWidgetAdvancedGates = new Widget_Advanced(this, false, c_GateWidgetPos);
    m_pWidgetStandardGates = new Widget_Standard(this, false, c_GateWidgetPos);
    m_pWidgetInputGates = new Widget_InputGates(this, false, c_GateWidgetPos);
    m_pCurrentShownGateWidget = m_pWidgetAllGates;

    //m_zoomSlider :
    {
        QRect layout = accountForUIOffsetts(ui->layout_ZoomSlider->geometry());
        delete ui->layout_ZoomSlider;
        m_pZoomSlider = new ZoomSlider(this, layout, c_minZoom, c_maxZoom, c_incZoom);
        m_pZoomSlider->raise();
        setZoomFactor(0.5);
    }

    m_pDlgGateInfo->move(accountForUIOffsetts(ui->layout_Dlg_GateInfo->geometry()).topLeft());
    m_pDlgGateInfo->raise();
}

DLG_Home::~DLG_Home()
{
    CustomSettings::close();

    delete m_pRandomConversionThread;

    delete m_pSpawnedGateWidget;
    delete m_pHelperPopup;

    delete m_pWidgetAllGates;
    delete m_pWidgetCustomGates;
    delete m_pWidgetAdvancedGates;
    delete m_pWidgetStandardGates;
    delete m_pWidgetInputGates;

    delete m_pDlgLoadGates;
    delete m_pDlgInput;
    delete m_pDlgSaveGateCollection;
    delete m_pDlgGateInfo;
    delete m_pDlgMessage;
    delete m_pDlgTextLabelEdit;
    delete m_pDlgEditScript;
    delete m_pDlgTruthTable;
    delete m_pDlgBooleanExpressions;
    delete m_pDlgConversionConfig;

    delete m_pZoomSlider;

    m_allGateFields.clear(); //deleted via qt

    delete ui;
}

void DLG_Home::sendUserMessage(const QString& message)
{
    m_pDlgMessage->showMessage(message);
}

///////////////////////
/// \brief DLG_Home::newlySpawnedGate
/// \param pGate gate to try drop onto GateField
/// \param spawnPosition DLG_Home relative spawn position
///
void DLG_Home::newlySpawnedGate(Gate* pGate, const QPoint& spawnPosition)
{
    m_pSpawnedGateWidget->open(pGate, spawnPosition);
}

///////////////////////////////////////////
/// \brief DLG_Home::addGateToGateField
/// \param pGate Gate to add to current gatefield (position relative to DLG_Home)
///
void DLG_Home::dropSpawnedGate(Gate* pGate)
{
    if(pGate == nullptr)
        return;

    //Check for current gatefield
    if(m_iCurrentGateField == -1)
    {
        newlySpawnedGateField(Settings::DefaultPageName);
    }

    //Position of pGate currently is relative to DLG_Home
    //Set position relative to current GateField
    const QPoint offset = -ui->PlayField->geometry().topLeft() - Settings::UiOffset - Settings::UiOffset;
    pGate->offsetPosition(offset.x(), offset.y());

    //Check pGate is in bounds of current gatefield
    if(m_allGateFields[size_t(m_iCurrentGateField)]->geometry().intersects(pGate->geometry()))
    {
        m_allGateFields[size_t(m_iCurrentGateField)]->addGate(pGate);
    }
    else
    {
        sendUserMessage("Must place gate onto page!");
        delete pGate;
    }
}

void DLG_Home::gateSelected(Gate* pGate)
{
    m_pDlgGateInfo->setGate(pGate);
}

void DLG_Home::newlySpawnedGateField(const QString& name)
{
    GateField* newGF = createNewGateField(name);
    m_allGateFields.push_back(newGF);
    m_iCurrentGateField = int8_t(m_allGateFields.size()-1);
    ui->PlayField->addTab(newGF, tr(name.toUtf8()));
}

GateField *DLG_Home::createNewGateField(const QString& name)
{
    return new GateField(this, m_zoomFactor, name);
}

QRect DLG_Home::accountForUIOffsetts(const QRect& rect) const
{
    return rect.translated(Settings::UiOffset); //Todo : find out why this is needed
}


// -- BUTTON HANDLERS FOR CLICK MODES --

void DLG_Home::on_btn_Drag_clicked()
{
    setCurrentClickMode(CLICK_DRAG);
}
void DLG_Home::on_btn_Delete_clicked()
{
    setCurrentClickMode(CLICK_DELETE_GATE);
}
void DLG_Home::on_btn_DeleteLink_clicked()
{
    setCurrentClickMode(CLICK_DELETE_LINK_NODES);
}
void DLG_Home::selectionToolClicked()
{
    setCurrentClickMode(CLICK_SELECTION);
}
void DLG_Home::on_btn_Pan_clicked()
{
    setCurrentClickMode(CLICK_PAN);
}
void DLG_Home::on_btn_click_clicked()
{
    setCurrentClickMode(CLICK_LINK_NODES);
}
void DLG_Home::setCurrentClickMode(const ClickMode& clickMode)
{
    m_currentClickMode = clickMode;

    switch (clickMode)
    {
    case CLICK_PAN:
        QApplication::setOverrideCursor(Qt::CursorShape::ArrowCursor);
        break;

    case CLICK_DRAG:
        QApplication::setOverrideCursor(Qt::CursorShape::SizeAllCursor);
        break;

    case CLICK_SELECTION:
        QApplication::setOverrideCursor(Qt::CursorShape::ArrowCursor);
        break;

    case CLICK_LINK_NODES:
        QApplication::setOverrideCursor(Qt::CursorShape::DragLinkCursor);
        break;

    case CLICK_DELETE_GATE:
        QApplication::setOverrideCursor(Qt::CursorShape::CrossCursor);
        break;

    case CLICK_DELETE_LINK_NODES:
        QApplication::setOverrideCursor(Qt::CursorShape::DragLinkCursor);
        break;

    default:
        QApplication::setOverrideCursor(Qt::CursorShape::ArrowCursor);
        Logger::log(LL_Error, "DLG_Home::setCurrentClickMode - Unknown click mode!");
        break;
    }
}

void DLG_Home::saveCurrentClickMode()
{
    m_savedClickMode = m_currentClickMode;
}

void DLG_Home::restorePreviousClickMode()
{
    setCurrentClickMode(m_savedClickMode);
}

ClickMode DLG_Home::currentClickMode() const
{
    return m_currentClickMode;
}

CircuitOptions DLG_Home::getCircuitGenOptions() const
{
    return m_pDlgConversionConfig->getCircuitGenOptions();
}

ConversionAlgorithm DLG_Home::getCurrentConversionAlgorithm() const
{
    return m_pDlgConversionConfig->getAlgorithm();
}

void DLG_Home::nextHelperTip()
{
    if(m_currentHelperTip == HT_Last)
    {
        setHelperTip(HT_First);
    }
    else
    {
        setHelperTip(HelperTip(m_currentHelperTip + 1));
    }
}

void DLG_Home::previousHelperTip()
{
    if(m_currentHelperTip == HT_First)
    {
        setHelperTip(HT_Last);
    }
    else
    {
        setHelperTip(HelperTip(m_currentHelperTip - 1));
    }
}

void DLG_Home::setHelperTip(const HelperTip &helperTip)
{
    m_currentHelperTip = helperTip;

    switch(m_currentHelperTip)
    {
    case HT_First:
        m_pHelperPopup->popup(QPoint(300, 300), "Welcome to logic gate simulator. \n Use the arrows to continue the tutorial.", false, 0);
        break;

    case HT_SpawnAndGate:
    {
        switchNewlySpawnedGatesWidget(m_pWidgetAllGates);

        if(m_iCurrentGateField == -1)
        {
            newlySpawnedGateField(Settings::DefaultPageName);
        }

        m_pHelperPopup->popup(m_pWidgetAllGates->getAndGateButtonPosition(), "Select the AND gate. Then drag it \n onto the page.", true, 90);
        break;
    }

    case HT_SpawnReceiverGate:
    {
        switchNewlySpawnedGatesWidget(m_pWidgetAllGates);

        if(m_iCurrentGateField == -1)
        {
            newlySpawnedGateField(Settings::DefaultPageName);
        }

        m_pHelperPopup->popup(m_pWidgetAllGates->getReceiverGateButtonPosition(), "Select the RECEIVER gate. Then drag it \n onto the page.", true, 90);
        break;
    }

    case HT_ShowInputGates:
    {
        m_pHelperPopup->popup(ui->comboBox->geometry().center() + Settings::UiOffset, "Select the Input Gates tab.", true, 90);
        break;
    }

    case HT_SpawnToggleGate:
    {
        switchNewlySpawnedGatesWidget(m_pWidgetInputGates);

        if(m_iCurrentGateField == -1)
        {
            newlySpawnedGateField(Settings::DefaultPageName);
        }

        m_pHelperPopup->popup(m_pWidgetInputGates->getToggleGateBtnLocation(), "Select two Toggle gates. Then drag them \n onto the page.", true, 90);
        break;
    }

    case HT_Last:
        m_pHelperPopup->popup(QPoint(300, 300), "This is the end of the tutorial. \n Use the arrows to start again.", false, 0);
        break;

    default:
        Logger::log(LogLevel::LL_Error, "DLG_Home::setHelperTip - Unknown helper tip option selected.");
        break;
    }
}

void DLG_Home::editTextLabel(TextLabel* pTextLabelToEdit)
{
    m_pDlgTextLabelEdit->editTextLabel(pTextLabelToEdit);
}

void DLG_Home::editFPGA(GateFPGA* pFPGA)
{
    m_pDlgEditScript->open(pFPGA);
}

void DLG_Home::setGateFieldName(GateField* pGateField, const QString& name)
{
    ui->PlayField->setTabText(ui->PlayField->indexOf(pGateField), name);
    pGateField->setName(name);
}

bool DLG_Home::requestUserInputString(const QString& title, const QString& context, QString& result)
{
    bool ok;
    result = m_pDlgInput->getText(this, title,
                                        context, QLineEdit::Normal,
                                        "", &ok);
    return ok;
}

void DLG_Home::startSaveGateCollection(GateCollection *pGateCollection)
{
    m_pDlgSaveGateCollection->open(pGateCollection);
}

void DLG_Home::moveEvent(QMoveEvent* event)
{
    QMainWindow::moveEvent(event);

    m_pSpawnedGateWidget->setGeometry(geometry());
}

void DLG_Home::closeEvent(QCloseEvent *event)
{
    CustomSettings::close();
    QWidget::closeEvent(event);

    delete this;
}

void DLG_Home::updateCustomGateListWidget()
{
    m_pWidgetCustomGates->updateList();
}

void DLG_Home::runRandomConversionThread(const TruthTable &truthTable, const GoalResult& goalResult)
{
    if(m_pRandomConversionThread->isRunning())
    {
        sendUserMessage("Already generating!");
        return;
    }

    m_pRandomConversionThread->start(truthTable, getCircuitGenOptions(), goalResult);

}

void DLG_Home::showGeneratedCircuit(GateCollection *pGateCollection)
{
    if(pGateCollection == nullptr)
        return;

    //Check for current gatefield
    if(m_iCurrentGateField == -1)
    {
        newlySpawnedGateField(Settings::DefaultPageName);
    }

    QPoint centerField = m_allGateFields[size_t(m_iCurrentGateField)]->geometry().center();
    pGateCollection->setPosition(centerField.x(), centerField.y());

    m_allGateFields[size_t(m_iCurrentGateField)]->addGate(pGateCollection);

    m_pDlgTruthTable->close();
    m_pDlgBooleanExpressions->close();
    m_pDlgEditScript->close();
}

void DLG_Home::showGeneratedTruthTable(const TruthTable& truthTable)
{
    m_pDlgTruthTable->open(truthTable);
    m_pDlgBooleanExpressions->close();
    m_pDlgEditScript->close();
}

void DLG_Home::showGeneratedBooleanExpressions(const std::vector<BooleanExpression> expressions)
{
    m_pDlgBooleanExpressions->showExpressions(expressions);
    m_pDlgTruthTable->close();
    m_pDlgEditScript->close();
}

void DLG_Home::failedRandomConversion(const QString& failMessage)
{
    sendUserMessage(failMessage);
}

// -- HANDLERS FOR GATES MENU BUTTONS --

enum GateWidgetPage
{
    ALL_GATES,
    STANDARD_GATES,
    CUSTOM_GATES,
    INPUT_GATES,
    ADVANCED_GATES
};

void DLG_Home::on_comboBox_currentIndexChanged(int index)
{
    switch (index)
    {
        case ALL_GATES:
            switchNewlySpawnedGatesWidget(m_pWidgetAllGates);
            break;
        case CUSTOM_GATES:
            switchNewlySpawnedGatesWidget(m_pWidgetCustomGates);
            m_pWidgetCustomGates->updateList();
            break;
        case INPUT_GATES:
            switchNewlySpawnedGatesWidget(m_pWidgetInputGates);
            break;
        case STANDARD_GATES:
            switchNewlySpawnedGatesWidget(m_pWidgetStandardGates);
            break;
        case ADVANCED_GATES:
            switchNewlySpawnedGatesWidget(m_pWidgetAdvancedGates);
            break;
    }
}

void DLG_Home::switchNewlySpawnedGatesWidget(MovingWidget* newWidgetToShow)
{
    if(m_pCurrentShownGateWidget && newWidgetToShow != m_pCurrentShownGateWidget)
    {
        m_pCurrentShownGateWidget->hide();
        newWidgetToShow->show();

        m_pCurrentShownGateWidget = newWidgetToShow;
    }
}

// -- OTHER BUTTON HANDLERS --

void DLG_Home::on_btn_zoomIn_clicked()
{  
    setZoomFactor(m_zoomFactor + c_incZoom);
}
void DLG_Home::on_btn_zoomOut_clicked()
{
    setZoomFactor(m_zoomFactor - c_incZoom);
}

//Function works for local call & external call
//Returns false if zoom value did not change, or a range limit is reached
bool DLG_Home::setZoomFactor(const qreal& zoomFactor, const bool& updateSlider)
{
    if (m_zoomFactor != zoomFactor)
    {
        //Make sure zoom factor is between c_maxZoom & c_minZoom
        if(zoomFactor > c_maxZoom)
            m_zoomFactor = c_maxZoom;

        else if(zoomFactor < c_minZoom)
            m_zoomFactor = c_minZoom;

        else
        {
            m_zoomFactor = zoomFactor;
        }

        if(updateSlider)
            m_pZoomSlider->setValue(m_zoomFactor);

        if(m_iCurrentGateField != -1)
            m_allGateFields[size_t(m_iCurrentGateField)]->setZoomLevel(m_zoomFactor);

        m_pSpawnedGateWidget->setZoomFactor(m_zoomFactor);

        return true;
    }
    return false;
}


void DLG_Home::on_btn_undo_clicked()
{
    if(m_iCurrentGateField != -1)
        m_allGateFields[size_t(m_iCurrentGateField)]->undo();
}
void DLG_Home::on_btn_redo_clicked()
{
    if(m_iCurrentGateField != -1)
        m_allGateFields[size_t(m_iCurrentGateField)]->redo();
}

void DLG_Home::on_btn_createScript_clicked()
{
    m_pDlgEditScript->open(nullptr);
}

void DLG_Home::on_btn_createTruthTable()
{
    m_pDlgTruthTable->open();
}

void DLG_Home::on_btn_createExpressions()
{
    m_pDlgBooleanExpressions->open();
}

void DLG_Home::on_btn_conversionConfig()
{
    m_pDlgConversionConfig->open();
}

void DLG_Home::on_btn_newPage_clicked()
{
    //Request page name
    QString newPageName;
    if(requestUserInputString("Edit Name", "Page name: ", newPageName))
    {
        if(newPageName.length() > 0)
        {
            newlySpawnedGateField(newPageName);
        }
        else
        {
            m_pDlgMessage->showMessage(newPageName + "Is not a valid file name!");
        }
    }
}

void DLG_Home::on_btn_setPageName_clicked()
{
    if(m_iCurrentGateField != -1)
    {
        m_pDlgSaveGateCollection->open(m_allGateFields[size_t(m_iCurrentGateField)], true);
    }
    else
    {
        sendUserMessage("Nothing to set a name of!");
    }
}

void DLG_Home::on_btn_Save_clicked()
{
    if(m_iCurrentGateField != -1)
    {
        m_pDlgSaveGateCollection->open(m_allGateFields[size_t(m_iCurrentGateField)]);
    }
    else
    {
        sendUserMessage("Nothing to save!");
    }
}

void DLG_Home::on_btn_load_clicked()
{
    //Promt user for gate colleciton file
    QStringList fileNames = m_pDlgLoadGates->getOpenFileNames(this);

    //Loop vars
    GateReader reader;
    QString errorMessage;
    for (const QString& file : fileNames)
    {
        GateField* pNewGateField = createNewGateField(QFileInfo(file).baseName());
        if(reader.ReadGateField(file, pNewGateField, errorMessage))
        {
            m_allGateFields.push_back(pNewGateField);
            ui->PlayField->addTab(pNewGateField, QFileInfo(file).baseName());
        }
        else
        {
            m_pDlgMessage->showMessage(errorMessage);
        }
    }
}

void DLG_Home::on_PlayField_tabCloseRequested(int index)
{
    if(dynamic_cast<GateField*>(ui->PlayField->widget(index)))
    {
        GateField* gf = dynamic_cast<GateField*>(ui->PlayField->widget(index));

        m_allGateFields.erase(m_allGateFields.begin() + index);

        m_pDlgGateInfo->setGateField(nullptr);

        //Remove tab
        // ~ Causes tabs to be switched if there's an existing open tab & resets m_iCurrentGateField
        ui->PlayField->removeTab(index);
        delete gf;
    }
}

void DLG_Home::on_PlayField_currentChanged(int index)
{
    m_iCurrentGateField = index;

    if(dynamic_cast<GateField*>(ui->PlayField->widget(index)))
    {
        m_pDlgGateInfo->setGateField(dynamic_cast<GateField*>(ui->PlayField->widget(index)));
    }
}
