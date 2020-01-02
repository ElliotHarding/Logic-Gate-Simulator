#include "dlg_home.h"
#include "ui_dlg_home.h"
#include <QLayout>
#include <QLibrary>
#include "gatereader.h"
#include "dlg_task.h"
#include "dlg_taskmanager.h"
#include "dlg_circuittaskdesignersetup.h"

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

    QRect layoutGateWidget = accountForUIOffsetts(ui->layout_GateWidget->geometry());
    QRect layoutGateInfo = accountForUIOffsetts(ui->layout_Dlg_GateInfo->geometry());

    //Construction
    {
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
             //save layout
             QRect layout = accountForUIOffsetts(ui->layout_ZoomSlider->geometry());

             ui->layout_ZoomSlider = new ZoomSlider(c_minZoom, c_maxZoom, 3, this);

             //set layout after construction
             dynamic_cast<SimpleSlider*>(ui->layout_ZoomSlider)->SetGeometry(layout);

             //setup
             ui->layout_ZoomSlider->raise();
             SetZoomFactor(0.5);
        }

        m_pDlgGateInfo->move(layoutGateInfo.topLeft());
        m_pDlgGateInfo->raise();
    }

    //Add to layout
    {
        this->layout()->addWidget(m_pDlgGateInfo);
        this->layout()->addWidget(m_pWidgetAllGates);
        this->layout()->addWidget(m_pWidgetCustomGates);
        this->layout()->addWidget(m_pWidgetAdvancedGates);
        this->layout()->addWidget(m_pWidgetStandardGates);
        this->layout()->addWidget(m_pWidgetInputGates);
    }

    //Positiong for gate widgets
    {
        /*
        const QPoint c_GateWidgetPosShowing = layoutGateWidget.topLeft();
        const QPoint c_GateWidgetPosHidden = QPoint(c_GateWidgetPosShowing.x() - c_moveWidgetDistance, c_GateWidgetPosShowing.y());

        m_pWidgetCustomGates->move(c_GateWidgetPosHidden);
        m_pWidgetAdvancedGates->move(c_GateWidgetPosHidden);
        m_pWidgetStandardGates->move(c_GateWidgetPosHidden);
        m_pWidgetInputGates->move(c_GateWidgetPosHidden);

        //Set current shown gate widget
        m_pWidgetAllGates->move(c_GateWidgetPosShowing);
        m_pWidgetAllGates->raise();
        m_pCurrentShownGateWidget = m_pWidgetAllGates;
        */
    }

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
            DLG_CircuitTaskDesignerSetup* dlgCircuitTaskDesigner = new DLG_CircuitTaskDesignerSetup(true, this);
            dlgCircuitTaskDesigner->show();
            dlgCircuitTaskDesigner = nullptr;
        });
        connect(ui->actionTruth_table_from_circuit_task, &QAction::triggered, [this]()
        {
            DLG_CircuitTaskDesignerSetup* dlgCircuitTaskDesigner = new DLG_CircuitTaskDesignerSetup(false, this);
            dlgCircuitTaskDesigner->show();
            dlgCircuitTaskDesigner = nullptr;
        });
    }

    {
        QString newTab("New tab");
        addGateField(newTab);
    }

    progressBar->setValue(100);
    txtProgress->setText("Done!");

    //test code

    Task t;
    t.m_inputs = 2;
    t.m_outputs = 1;
    t.m_bCircuitTask = true;
    t.results = {{0,0,0,1}};

    std::vector<Task> tasks = {t,t,t,t,t,t,t};

    DLG_TaskManager* taskMan = new DLG_TaskManager(tasks, this);
    taskMan->show();
}

DLG_Home::DLG_Home(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::DLG_Home),
    m_zoomFactor(-1)
{
    ui->setupUi(this);

    {
        setMouseTracking(true);
        ui->PlayField->clear();
    }

    QRect layoutGateWidget = accountForUIOffsetts(ui->layout_GateWidget->geometry());
    QRect layoutGateInfo = accountForUIOffsetts(ui->layout_Dlg_GateInfo->geometry());

    //Construction
    {
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
             //save layout
             QRect layout = accountForUIOffsetts(ui->layout_ZoomSlider->geometry());

             ui->layout_ZoomSlider = new ZoomSlider(c_minZoom, c_maxZoom, 3, this);

             //set layout after construction
             dynamic_cast<SimpleSlider*>(ui->layout_ZoomSlider)->SetGeometry(layout);

             //setup
             ui->layout_ZoomSlider->raise();
             SetZoomFactor(0.5);
        }

        m_pDlgGateInfo->move(layoutGateInfo.topLeft());
        m_pDlgGateInfo->raise();
    }

    //Add to layout
    {
        this->layout()->addWidget(m_pDlgGateInfo);
        this->layout()->addWidget(m_pWidgetAllGates);
        this->layout()->addWidget(m_pWidgetCustomGates);
        this->layout()->addWidget(m_pWidgetAdvancedGates);
        this->layout()->addWidget(m_pWidgetStandardGates);
        this->layout()->addWidget(m_pWidgetInputGates);
    }

    ui->btn_newPage->hide();
    ui->btn_Save->hide();
    ui->btn_load->hide();
    ui->PlayField->hide();
    ui->layout_ZoomSlider->hide();
    ui->btn_zoomIn->hide();
    ui->btn_zoomOut->hide();
    ui->line_3->hide();
    ui->line_6->hide();
    ui->line_8->hide();
    ui->btn_redo->hide();
    ui->btn_undo->hide();
    ui->menuFile->clear();
    delete ui->menuEdit;
    delete ui->menuTools;

    QRect geoDrag = ui->btn_Drag->geometry();
    QRect geoPan = ui->btn_Pan->geometry();
    QRect geoClick = ui->btn_click->geometry();
    QRect geoDelete = ui->btn_Delete->geometry();
    QRect geoDeleteLink = ui->btn_DeleteLink->geometry();

    const int yOffset = -130;
    geoDrag.setY(geoDrag.y() + yOffset);
    geoPan.setY(geoPan.y() + yOffset);
    geoClick.setY(geoClick.y() + yOffset);
    geoDelete.setY(geoDelete.y() + yOffset);
    geoDeleteLink.setY(geoDeleteLink.y() + yOffset);

    ui->btn_Drag->setGeometry(geoDrag);
    ui->btn_Pan->setGeometry(geoPan);
    ui->btn_click->setGeometry(geoClick);
    ui->btn_Delete->setGeometry(geoDelete);
    ui->btn_DeleteLink->setGeometry(geoDeleteLink);
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

    //Delete gatefields
    for (GateField* gf : m_allGateFields)
    {
        delete gf;
    }

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

void DLG_Home::addGateField(QString& name)
{
    GateField* newGF = createNewGateField(name);
    m_allGateFields.push_back(newGF);
    m_iCurrentGateField = int8_t(m_allGateFields.size());
    ui->PlayField->addTab(newGF,tr(name.toUtf8()));
}

GateField *DLG_Home::createNewGateField(QString name)
{
    return new GateField(m_zoomFactor, name.toStdString(), this, m_pDlgSaveGateCollection);
}

QRect DLG_Home::accountForUIOffsetts(const QRect& rect)
{
    QRect newRect(rect.left(), rect.top() + 20, rect.width(), rect.height());
    return newRect;
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
    m_previousClickMode = m_currentClickMode;
    m_currentClickMode = clickMode;

    if(m_iCurrentGateField != -1)
        m_allGateFields[size_t(m_iCurrentGateField)]->CurrentClickMode = clickMode;

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

    m_previousClickMode = clickMode;
}

void DLG_Home::ResetToPreviousClickMode()
{
    if(m_previousClickMode != CLICK_LINK_NODES)
    {
        SetCurrentClickMode(m_previousClickMode);
    }
    else
    {
        SetCurrentClickMode(CLICK_DRAG);
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

    //Old style animation:
    /*
    if(m_pCurrentShownGateWidget && newWidgetToShow != m_pCurrentShownGateWidget)
    {
        newWidgetToShow->raise();

        for (int moved = 0; moved < c_moveWidgetDistance; moved += c_moveWidgetsIncrement)
        {
            //Retract current shown widget
            const QRect currentGeo = m_pCurrentShownGateWidget->geometry();
            m_pCurrentShownGateWidget->move(currentGeo.left() - c_moveWidgetsIncrement, currentGeo.top());

            //Move out new one to show
            const QRect newWidgetGeometry = newWidgetToShow->geometry();
            newWidgetToShow->move(newWidgetGeometry.left() + c_moveWidgetsIncrement, newWidgetGeometry.top());

            //Force redraw on the widgets. Drawing new one last (on top)
            m_pCurrentShownGateWidget->repaint();
            newWidgetToShow->repaint();

            //QThread::msleep(1);
        }

        m_pCurrentShownGateWidget = newWidgetToShow;
    }
    */
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
    bool retVal = false;
    if (m_zoomFactor != zoomFactor)
    {
        //Make sure zoom factor is between c_maxZoom & c_minZoom
        if(zoomFactor > c_maxZoom)
            m_zoomFactor = c_maxZoom;

        else if(zoomFactor < c_minZoom)
            m_zoomFactor = c_minZoom;

        else
        {
            retVal = true;
            m_zoomFactor = zoomFactor;
        }

        if(updateSlider)
            dynamic_cast<ZoomSlider*>(ui->layout_ZoomSlider)->SetValue(m_zoomFactor);

        if(m_iCurrentGateField != -1)
            m_allGateFields[size_t(m_iCurrentGateField)]->SetZoomLevel(m_zoomFactor);

        return retVal;
    }
    return retVal;
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
