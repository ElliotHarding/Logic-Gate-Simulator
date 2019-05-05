#include "dlg_home.h"
#include "ui_dlg_home.h"
#include <QLayout>
#include <QFileDialog>
#include <QInputDialog>
#include "gatereader.h"

DLG_Home::DLG_Home(QWidget *parent) :
    QMainWindow(parent),    
    ui(new Ui::DLG_Home),
    m_ZoomFactor(0.5)
{
    ui->setupUi(this);
    setMouseTracking(true);
    ui->PlayField->clear();
    on_btn_newPage_clicked();

    //Add zoom slider to dialog
    m_zoomSlider = new SimpleSlider(c_minZoom, c_maxZoom, c_zoomSliderPos, c_zoomSliderWidth, this);
    this->layout()->addWidget(m_zoomSlider);

    //Start the update thread
    m_updateThread = new LogicUpdateThread(&m_allGateFields);
    m_updateThread->start();
}

DLG_Home::~DLG_Home()
{
    m_updateThread->stopRunning();
    m_updateThread->exit();
    delete m_updateThread;

    //delete m_currentGateField

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
    m_currentGateField->setZoomLevel(m_ZoomFactor);
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
void DLG_Home::on_btn_SelectionTool_clicked()
{
    if(m_currentGateField)
    {
        m_currentGateField->setCurrentClickMode(CLICK_SELECTION);
    }
    QApplication::setOverrideCursor(Qt::CursorShape::ArrowCursor);
}


// -- BUTTON HANDLERS FOR NEW GATES --

void DLG_Home::on_btn_sourceGate_clicked()
{
    if(m_currentGateField)
    {
        m_currentGateField->addGameObject(new GateToggle());
        on_btn_Drag_clicked();
    }
}
void DLG_Home::on_btn_notGate_clicked()
{
    if(m_currentGateField)
    {
        m_currentGateField->addGameObject(new GateNot());
        on_btn_Drag_clicked();
    }
}
void DLG_Home::on_btn_orGate_clicked()
{
    if(m_currentGateField)
    {
        m_currentGateField->addGameObject(new GateOr());
        on_btn_Drag_clicked();
    }
}
void DLG_Home::on_btn_andGate_clicked()
{
    if(m_currentGateField)
    {
        m_currentGateField->addGameObject(new GateAnd());
        on_btn_Drag_clicked();
    }
}
void DLG_Home::on_btn_recieverGate_clicked()
{
    if(m_currentGateField)
    {
        m_currentGateField->addGameObject(new GateReciever());
        on_btn_Drag_clicked();
    }
}
void DLG_Home::on_btn_gateCollection_clicked()
{
    if(!m_currentGateField)
        on_btn_newPage_clicked();

    //Promt user for gate colleciton file
    QStringList fileNames = QFileDialog::getOpenFileNames(this);

    //Loop vars
    GateReader reader;
    std::ifstream gateCollectionFile;
    //Go through each file and use reader to read gatecollections
    //and add them to m_currentGateField
    for (QString file : fileNames)
    {
        gateCollectionFile = std::ifstream(file.toUtf8());
        m_currentGateField->addGameObject(reader.readGateCollection(gateCollectionFile), false);
    }

    on_btn_Drag_clicked();
}

// -- OTHER BUTTON HANDLERS --

void DLG_Home::on_btn_zoomIn_clicked()
{
    if(m_ZoomFactor < c_maxZoom)
        m_currentGateField->setZoomLevel(m_ZoomFactor *= 2);
}

void DLG_Home::on_btn_zoomOut_clicked()
{
    if(m_ZoomFactor > c_minZoom)
        m_currentGateField->setZoomLevel(m_ZoomFactor /= 2);
}

void DLG_Home::on_btn_newPage_clicked()
{
    //Request page name
    bool ok;
    QString newPageName = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                         tr("Page name: "), QLineEdit::Normal,
                                         QDir::home().dirName(), &ok);
    if(ok)
    {
        //Add gatefield
        m_currentGateField = new GateField(m_ZoomFactor, newPageName.toStdString());
        m_allGateFields.push_back(m_currentGateField);
        ui->PlayField->addTab(m_currentGateField,tr(newPageName.toUtf8()));
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
    QStringList fileNames = QFileDialog::getOpenFileNames(this);

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
            std::string pageName;
            saveFile >> pageName;
            m_currentGateField = new GateField(m_ZoomFactor, pageName);

            //For each loaded gate, add to loadedGateField
            const std::vector<Gate*> loadedGates = reader.readGateFieldGates(saveFile);
            for (Gate* gate : loadedGates)
            {
                m_currentGateField->addGameObject(gate);
            }

            //Add to m_allGateFields
            m_allGateFields.push_back(m_currentGateField);

            //Add to ui
            ui->PlayField->addTab(m_currentGateField,tr(pageName.c_str()));
        }
        else {
            //todo
        }
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
        for (GateField* gf : *m_pAllGateFields)
            if(gf && (gf->Enabled == true))
                    gf->updateFunction();
}

void LogicUpdateThread::stopRunning()
{
    m_bStop = true;
}
