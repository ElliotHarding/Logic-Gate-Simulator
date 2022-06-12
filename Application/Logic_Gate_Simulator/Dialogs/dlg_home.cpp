#include "dlg_home.h"
#include "ui_dlg_home.h"
#include <QLayout>
#include <QLibrary>
#include "gatereader.h"
#include "dlg_task.h"
#include "dlg_taskmanager.h"
#include "dlg_circuittaskdesignersetup.h"
#include "filelocations.h"

DLG_Home::DLG_Home(QProgressBar* progressBar, QLabel* txtProgress, QWidget *parent) :
    QMainWindow(parent),    
    ui(new Ui::DLG_Home),
    m_zoomFactor(-1)
{

    progressBar->setValue(20);
    txtProgress->setText("Setting up UI...");

    {
        ui->setupUi(this);
    }

    progressBar->setValue(45);
    txtProgress->setText("Loading additional libs");

    {
        QLibrary lib( "Comctl32.dll" );
        lib.setLoadHints( QLibrary::ResolveAllSymbolsHint );
        lib.load();
    }

    progressBar->setValue(66);
    txtProgress->setText("Intializing child components");

    {
        m_allGateFields.reserve(10);
    }
    {
        setMouseTracking(true);
        ui->PlayField->clear();
    }

    //Construction
    InitalizeDialogsAndWidgets();

    //Connections
    {
        connect(ui->actionNew_page, SIGNAL(triggered()), this, SLOT(on_btn_newPage_clicked()));
        connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(on_btn_Save_clicked()));
        connect(ui->actionLoad, SIGNAL(triggered()), this, SLOT(on_btn_load_clicked()));
        connect(ui->actionPan, SIGNAL(triggered()), this, SLOT(on_btn_Pan_clicked()));
        connect(ui->actionDrag, SIGNAL(triggered()), this, SLOT(on_btn_Drag_clicked()));
        connect(ui->actionLink, SIGNAL(triggered()), this, SLOT(on_btn_link_clicked()));
        connect(ui->actionLoad, SIGNAL(triggered()), this, SLOT(on_btn_load_clicked()));
        connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(on_btn_Save_clicked()));
        connect(ui->actionUndo, SIGNAL(triggered()), this, SLOT(on_btn_undo_clicked()));
        connect(ui->actionRedo, SIGNAL(triggered()), this, SLOT(on_btn_redo_clicked()));
        connect(ui->actionZoom, SIGNAL(triggered()), this, SLOT(on_btn_zoomIn_clicked()));
        connect(ui->actionDelete, SIGNAL(triggered()), this, SLOT(on_btn_Delete_clicked()));
        connect(ui->actionZoom_2, SIGNAL(triggered()), this, SLOT(on_btn_zoomOut_clicked()));
        connect(ui->actionDelete_Link, SIGNAL(triggered()), this, SLOT(on_btn_DeleteLink_clicked()));

        connect(ui->actionCircuit_from_truth_table_task, &QAction::triggered, [this]()
        {

        });
        connect(ui->actionTruth_table_from_circuit_task, &QAction::triggered, [this]()
        {

        });
        connect(ui->actionView_Tasks, &QAction::triggered, [this]()
        {
            on_btn_tasks_clicked();
        });
    }

    {
        addGateField("New tab");
    }

    progressBar->setValue(100);
    txtProgress->setText("Done!");
}

void DLG_Home::InitalizeDialogsAndWidgets()
{
    QRect layoutGateWidget = accountForUIOffsetts(ui->layout_GateWidget->geometry());
    QRect layoutGateInfo = accountForUIOffsetts(ui->layout_Dlg_GateInfo->geometry());

    m_pDlgLoadGates = new QFileDialog(this);
    m_pDlgInput = new QInputDialog(this);
    m_pDlgSaveGateCollection = new DLG_SaveGateCollection(this);
    m_pDlgGateInfo = new DLG_GateInfo(this);
    m_pDlgMessage = new DLG_Message(this);
    m_pDlgTextLabelEdit = new DLG_LabelGateEdit();

    //Gate widgets
    const QPoint c_GateWidgetPos = layoutGateWidget.topLeft();
    m_pWidgetAllGates = new Widget_AllGates(this, true, c_GateWidgetPos);
    m_pCurrentShownGateWidget = m_pWidgetAllGates;

    m_pWidgetCustomGates = new Widget_CustomGates(this, false, c_GateWidgetPos);
    m_pWidgetAdvancedGates = new Widget_Advanced(this, false, c_GateWidgetPos);
    m_pWidgetStandardGates = new Widget_Standard(this, false, c_GateWidgetPos);
    m_pWidgetInputGates = new Widget_InputGates(this, false, c_GateWidgetPos);

    //m_zoomSlider :
    {
        QRect layout = accountForUIOffsetts(ui->layout_ZoomSlider->geometry());
        delete ui->layout_ZoomSlider;
        m_pZoomSlider = new ZoomSlider(this, layout, c_minZoom, c_maxZoom, c_incZoom);
        m_pZoomSlider->raise();
        SetZoomFactor(0.5);
    }

    m_pDlgGateInfo->move(layoutGateInfo.topLeft());
    m_pDlgGateInfo->raise();
}

DLG_Home::~DLG_Home()
{
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

    delete m_pZoomSlider;

    //Delete gatefields
    /*for (GateField* gf : m_allGateFields)
    {
        //delete gf;
        gf = nullptr;
    }*/
    m_allGateFields.clear(); //deleted via qt

    delete ui;
}

void DLG_Home::SendUserMessage(QString message)
{
    m_pDlgMessage->ShowMessage(message);
}

void DLG_Home::AddGate(Gate *g)
{
    if(m_iCurrentGateField != -1)
    {
        m_allGateFields[size_t(m_iCurrentGateField)]->AddGate(g);
        on_btn_Drag_clicked();
    }
    else
    {
        //Failed to add gate so discard it
        delete g;
    }
}

void DLG_Home::GateSelected(Gate *g)
{
    m_pDlgGateInfo->setGate(g);
}

void DLG_Home::DeleteGate(Gate *g)
{
    for(GateField* gField : m_allGateFields)
    {
        if(gField == g->GetParent())
        {
            gField->DeleteGate(g);
        }
    }
}

void DLG_Home::addGateField(const QString& name)
{
    GateField* newGF = createNewGateField(name);
    m_allGateFields.push_back(newGF);
    m_iCurrentGateField = int8_t(m_allGateFields.size()-1);
    ui->PlayField->addTab(newGF,tr(name.toUtf8()));
}

GateField *DLG_Home::createNewGateField(const QString& name)
{
    return new GateField(this, m_zoomFactor, name.toStdString(), m_pDlgSaveGateCollection);
}

QRect DLG_Home::accountForUIOffsetts(const QRect& rect)
{
    return rect.translated(0, 20); //Todo : find out why
}

QString DLG_Home::PathToFileName(const QString s)
{
    QFileInfo fi(s);
    return fi.baseName();
}


// -- BUTTON HANDLERS FOR CLICK MODES --

void DLG_Home::on_btn_Drag_clicked()
{
    SetCurrentClickMode(CLICK_DRAG);
}
void DLG_Home::on_btn_Delete_clicked()
{
    SetCurrentClickMode(CLICK_DELETE_GATE);
}
void DLG_Home::on_btn_DeleteLink_clicked()
{
    SetCurrentClickMode(CLICK_DELETE_LINK_NODES);
}
void DLG_Home::on_btn_SelectionTool_clicked()
{
    SetCurrentClickMode(CLICK_SELECTION);
}
void DLG_Home::SelectionToolClicked()
{
    SetCurrentClickMode(CLICK_SELECTION);
}
void DLG_Home::on_btn_Pan_clicked()
{
    SetCurrentClickMode(CLICK_PAN);
}
void DLG_Home::on_btn_click_clicked()
{
    SetCurrentClickMode(CLICK_DEFAULT);
}
void DLG_Home::SetCurrentClickMode(ClickMode clickMode)
{
    m_currentClickMode = clickMode;

    if(m_iCurrentGateField != -1)
        m_allGateFields[size_t(m_iCurrentGateField)]->setCurrentClickMode(clickMode);

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

    case CLICK_DEFAULT:
        QApplication::setOverrideCursor(Qt::CursorShape::ArrowCursor);
        break;
    }
}

void DLG_Home::EditTextLabel(TextLabel *textLabelToEdit)
{
    m_pDlgTextLabelEdit->EditTextLabel(textLabelToEdit);
}

void DLG_Home::UpdateCustomGateListWidget()
{
    m_pWidgetCustomGates->UpdateList();
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
            SwitchWidgets(m_pWidgetAllGates);
            break;
        case CUSTOM_GATES:
            SwitchWidgets(m_pWidgetCustomGates);
            m_pWidgetCustomGates->UpdateList();
            break;
        case INPUT_GATES:
            SwitchWidgets(m_pWidgetInputGates);
            break;
        case STANDARD_GATES:
            SwitchWidgets(m_pWidgetStandardGates);
            break;
        case ADVANCED_GATES:
            SwitchWidgets(m_pWidgetAdvancedGates);
            break;
    }
}

void DLG_Home::SwitchWidgets(MovingWidget* newWidgetToShow)
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
    SetZoomFactor(m_zoomFactor + c_incZoom);
}
void DLG_Home::on_btn_zoomOut_clicked()
{
    SetZoomFactor(m_zoomFactor - c_incZoom);
}

//Function works for local call & external call
//Returns false if zoom value did not change, or a range limit is reached
bool DLG_Home::SetZoomFactor(qreal zoomFactor, bool updateSlider)
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
            m_pZoomSlider->SetValue(m_zoomFactor);

        if(m_iCurrentGateField != -1)
            m_allGateFields[size_t(m_iCurrentGateField)]->SetZoomLevel(m_zoomFactor);

        return true;
    }
    return false;
}


void DLG_Home::on_btn_undo_clicked()
{
    if(m_iCurrentGateField != -1)
        m_allGateFields[size_t(m_iCurrentGateField)]->Undo();
}
void DLG_Home::on_btn_redo_clicked()
{
    if(m_iCurrentGateField != -1)
        m_allGateFields[size_t(m_iCurrentGateField)]->Redo();
}

void DLG_Home::on_btn_newPage_clicked()
{
    //Request page name
    bool ok;
    QString newPageName = m_pDlgInput->getText(this, tr("Edit Name"),
                                         tr("Page name: "), QLineEdit::Normal,
                                         "", &ok);
    if(!ok)
        return;

    if(newPageName.length() > 0)
    {
        addGateField(newPageName);
    }
    else
    {
        m_pDlgMessage->ShowMessage(newPageName + "Is not a valid file name!");
    }
}

void DLG_Home::on_btn_Save_clicked()
{
    bool saveFailed = false;

    //Loop through all open gate fields and save
    for (GateField* gf : m_allGateFields)
    {
        saveFailed = gf->SaveData();
        if(!saveFailed)
            break;
    }

    if(!saveFailed)
    {
        SendUserMessage("Saving a page failed!");
    }
}

void DLG_Home::on_btn_tasks_clicked()
{
}

void DLG_Home::on_btn_load_clicked()
{
    //Promt user for gate colleciton file
    QStringList fileNames = m_pDlgLoadGates->getOpenFileNames(this);

    //Loop vars
    GateReader reader;
    std::ifstream saveFile;
    for (QString file : fileNames)
    {
        //Open file
        saveFile = std::ifstream(file.toUtf8());

        if(!file.contains(".GateField"))
        {
            m_pDlgMessage->ShowMessage("File not in gatefield format.");
            continue;
        }

        bool failed = false;

        if(saveFile.is_open())
        {
            QString name = QFileInfo(file).baseName();

            //Load gates
            m_allGateFields[size_t(m_iCurrentGateField)] = createNewGateField(name);

            //For each loaded gate, add to loadedGateField
            if (reader.ReadGateField(saveFile, m_allGateFields[size_t(m_iCurrentGateField)]))
            {
                //Add to m_allGateFields
                m_allGateFields.push_back(m_allGateFields[size_t(m_iCurrentGateField)]);

                //Add to ui
                ui->PlayField->addTab(m_allGateFields[size_t(m_iCurrentGateField)],tr(name.toUtf8()));

                continue;
            }
            else
            {
                failed = true;
            }
        }
        else
        {
            failed = true;
        }

        if(failed)
        {
            m_pDlgMessage->ShowMessage("Loading file failed");
        }
    }
}

void DLG_Home::on_PlayField_tabCloseRequested(int index)
{
    //Get pointer to widget to delete
    GateField* gf = dynamic_cast<GateField*>(ui->PlayField->widget(index));

    m_allGateFields[size_t(index)] = nullptr;
    m_allGateFields.erase(m_allGateFields.begin() + index);

    //Remove tab
    // ~ Causes tabs to be switched if there's an existing open tab & resets m_iCurrentGateField
    ui->PlayField->removeTab(index);
    delete gf;
}

void DLG_Home::on_PlayField_currentChanged(int index)
{
    m_iCurrentGateField = index;
}
