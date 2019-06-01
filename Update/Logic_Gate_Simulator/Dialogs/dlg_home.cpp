#include "dlg_home.h"
#include "ui_dlg_home.h"
#include <QLayout>
#include <QLibrary>
#include "gatereader.h"

DLG_Home::DLG_Home(QProgressBar* progressBar, QLabel* txtProgress, QWidget *parent) :
    QMainWindow(parent),    
    ui(new Ui::DLG_Home),
    m_ZoomFactor(0.5)
{

    progressBar->setValue(10);
    txtProgress->setText("Setting up UI...");

    {
        ui->setupUi(this);
    }

    progressBar->setValue(33);
    txtProgress->setText("Loading additional libs");

    {
        QLibrary lib( "Comctl32.dll" );
        lib.setLoadHints( QLibrary::ResolveAllSymbolsHint );
        lib.load();
    }

    progressBar->setValue(66);
    txtProgress->setText("Intializing child components");

    {
        const QPoint c_GateWidgetPosShowing = QPoint(0,52);
        const QPoint c_GateWidgetPosHidden = QPoint(-160,52);

        //Gate widgets
        m_pWidgetAllGates = new Widget_AllGates(this);
        m_pWidgetCustomGates = new Widget_CustomGates(this);
        m_pWidgetAdvancedGates = new Widget_Advanced(this);
        m_pWidgetStandardGates = new Widget_Standard(this);
        m_pWidgetInputGates = new Widget_InputGates(this);

        this->layout()->addWidget(m_pWidgetAllGates);
        this->layout()->addWidget(m_pWidgetCustomGates);
        this->layout()->addWidget(m_pWidgetAdvancedGates);
        this->layout()->addWidget(m_pWidgetStandardGates);
        this->layout()->addWidget(m_pWidgetInputGates);

        m_pWidgetCustomGates->move(c_GateWidgetPosHidden);
        m_pWidgetAdvancedGates->move(c_GateWidgetPosHidden);
        m_pWidgetStandardGates->move(c_GateWidgetPosHidden);
        m_pWidgetInputGates->move(c_GateWidgetPosHidden);

        //Set current shown gate widget
        m_pWidgetAllGates->move(c_GateWidgetPosShowing);
        m_pWidgetAllGates->raise();
        m_pCurrentShownGateWidget = m_pWidgetAllGates;
    }

    {
        m_allGateFields.reserve(10);
    }

    {
        setMouseTracking(true);
        ui->PlayField->clear();
    }

    {
        m_pDlgGateInfo = new DLG_GateInfo(this);
        this->layout()->addWidget(m_pDlgGateInfo);
        m_pDlgGateInfo->move(ui->layout_Dlg_GateInfo->geometry().topLeft());
        m_pDlgGateInfo->raise();
    }

    {
         m_pDlgLoadGates = new QFileDialog(this);
         m_pDlgInput = new QInputDialog(this);
         m_pDlgSaveGateCollection = new DLG_SaveGateCollection(this);
    }

    //Add zoom slider to dialog
    {
        //Get layout & shift because menu bar offsetts y-positions
        QRect layout = ui->layout_ZoomSlider->geometry();
        layout.setY(layout.y() + 22);

        //Setup
        m_zoomSlider = new SimpleSlider(c_minZoom, c_maxZoom, layout, this);
        this->layout()->addWidget(m_zoomSlider);
    }

    progressBar->setValue(100);
    txtProgress->setText("Done!");
}

DLG_Home::~DLG_Home()
{
    //m_updateThread->stopRunning();
    //m_updateThread->exit();
    //delete m_updateThread;

    //m_currentGateField = nullptr;

    //Delete gatefields
    for (GateField* gf : m_allGateFields)
    {
        delete gf;
    }

    delete ui;
}

void DLG_Home::SetZoomFactor(float zoomFactor)
{
    m_ZoomFactor = zoomFactor;
    if(m_currentGateField)
        m_currentGateField->setZoomLevel(m_ZoomFactor);
}

void DLG_Home::AddGate(Gate *g)
{
    if(m_currentGateField)
    {
        m_currentGateField->addGameObject(g);
        on_btn_Drag_clicked();
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
        if(gField == g->ParentField)
        {
            gField->DeleteGate(g);
        }
    }
}

void DLG_Home::addGateField(QString name)
{
    m_currentGateField = createNewGateField(name);
    m_allGateFields.push_back(m_currentGateField);
    ui->PlayField->addTab(m_currentGateField,tr(name.toUtf8()));
}

GateField *DLG_Home::createNewGateField(QString name)
{
    return new GateField(m_ZoomFactor, name.toStdString(), this, m_pDlgSaveGateCollection);
}


// -- BUTTON HANDLERS FOR CLICK MODES --

void DLG_Home::on_btn_Drag_clicked()
{
    if(m_currentGateField)
    {
        m_currentGateField->setCurrentClickMode(CLICK_DRAG);
    }
    QApplication::setOverrideCursor(Qt::CursorShape::SizeAllCursor);
}
void DLG_Home::on_btn_Delete_clicked()
{
    if(m_currentGateField)
    {
        m_currentGateField->setCurrentClickMode(CLICK_DELETE_GATE);
    }
    QApplication::setOverrideCursor(Qt::CursorShape::CrossCursor);
}
void DLG_Home::on_btn_link_clicked()
{
    if(m_currentGateField)
    {
        m_currentGateField->setCurrentClickMode(CLICK_LINK_NODES);
    }
    QApplication::setOverrideCursor(Qt::CursorShape::DragLinkCursor);
}
void DLG_Home::on_btn_DeleteLink_clicked()
{
    if(m_currentGateField)
    {
        m_currentGateField->setCurrentClickMode(CLICK_DELETE_LINK_NODES);
    }
    QApplication::setOverrideCursor(Qt::CursorShape::DragLinkCursor);
}
void DLG_Home::on_btn_click_clicked()
{
    if(m_currentGateField)
    {
        m_currentGateField->setCurrentClickMode(CLICK_DEFAULT);
    }
    QApplication::setOverrideCursor(Qt::CursorShape::ArrowCursor);
}
void DLG_Home::SelectionToolClicked()
{
    if(m_currentGateField)
    {
        m_currentGateField->setCurrentClickMode(CLICK_SELECTION);
    }
    QApplication::setOverrideCursor(Qt::CursorShape::ArrowCursor);
}

void DLG_Home::on_btn_Pan_clicked()
{
    if(m_currentGateField)
    {
        m_currentGateField->setCurrentClickMode(CLICK_PAN);
    }
    QApplication::setOverrideCursor(Qt::CursorShape::ArrowCursor);
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

void DLG_Home::SwitchWidgets(QWidget* w)
{
    if(w != m_pCurrentShownGateWidget)
    {
        w->raise();    

        for (int moved = 0; moved < w->geometry().width(); moved += c_moveWidgetsIncrement)
        {
            //Retract current shown widget
            if(m_pCurrentShownGateWidget)
                MoveWidget(m_pCurrentShownGateWidget, -c_moveWidgetsIncrement);

            //Move out new one to show
            MoveWidget(w, c_moveWidgetsIncrement);

            QThread::msleep(1);
        }

        m_pCurrentShownGateWidget = w;
    }
}
void DLG_Home::MoveWidget(QWidget *w, int xDir)
{
    QRect geo = w->geometry();
    w->move(geo.left() + xDir, geo.top());
    w->repaint();
}

// -- OTHER BUTTON HANDLERS --

void DLG_Home::on_btn_zoomIn_clicked()
{
    if(m_currentGateField)
        if(m_ZoomFactor < c_maxZoom)
            m_currentGateField->setZoomLevel(m_ZoomFactor *= 2);
}

void DLG_Home::on_btn_zoomOut_clicked()
{
    if(m_currentGateField)
        if(m_ZoomFactor > c_minZoom)
            m_currentGateField->setZoomLevel(m_ZoomFactor /= 2);
}
void DLG_Home::on_btn_undo_clicked()
{
    if(m_currentGateField)
        m_currentGateField->Undo();
}
void DLG_Home::on_btn_redo_clicked()
{
    if(m_currentGateField)
        m_currentGateField->Redo();
}
void DLG_Home::on_btn_newPage_clicked()
{
    //Request page name
    bool ok;
    QString newPageName = m_pDlgInput->getText(this, tr("QInputDialog::getText()"),
                                         tr("Page name: "), QLineEdit::Normal,
                                         QDir::home().dirName(), &ok);
    if(ok)
    {
        addGateField(newPageName);
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

    //todo
    if(!saveFailed)
    {

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

        if(saveFile.is_open())
        {
            //Load gates
            m_currentGateField = createNewGateField(file);

            //For each loaded gate, add to loadedGateField
            if (reader.ReadGateField(saveFile, m_currentGateField))
            {
                //Add to m_allGateFields
                m_allGateFields.push_back(m_currentGateField);

                //Add to ui
                ui->PlayField->addTab(m_currentGateField,tr(file.toUtf8()));

                continue;
            }
        }

        //todo failed

    }
}

void DLG_Home::on_PlayField_tabCloseRequested(int index)
{
    ui->PlayField->removeTab(index);
}

void DLG_Home::on_PlayField_currentChanged(int index)
{
    QWidget* currentWidget = ui->PlayField->currentWidget();
    if(dynamic_cast<GateField*>(currentWidget))
    {
        m_currentGateField = dynamic_cast<GateField*>(currentWidget);
    }
}


#ifdef zero
//          --------------------------------
//          LogicUpdateThread implementation
//          --------------------------------

LogicUpdateThread::LogicUpdateThread(std::vector<GateField*>* allGateFields) : QThread (),
    m_bStop(false),
    m_pAllGateFields(allGateFields)
{
}

LogicUpdateThread::~LogicUpdateThread()
{
    stopRunning();
    terminate();
}

//Calls the update function of all the gates in all of the gateFields
void LogicUpdateThread::run()
{
    while (!m_bStop)
    {
        for (GateField* gf : *m_pAllGateFields)
        {
            if((gf) && gf->Enabled)
                    gf->updateFunction();

        }
        QThread::msleep(1000);
    }


}

void LogicUpdateThread::stopRunning()
{
    m_bStop = true;
}

void DLG_Home::on_btn_test_clicked()
{
    if(m_currentGateField)
    {
        m_currentGateField->addGameObject(new GateTimer());
        on_btn_Drag_clicked();
    }
}
#endif
