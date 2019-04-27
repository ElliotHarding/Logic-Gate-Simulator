#include "dlg_home.h"
#include "ui_dlg_home.h"
#include <QLayout>

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
    m_zoomSlider = new SimpleSlider(0.25, 10, QPoint(50,20), 100, this);
    this->layout()->addWidget(m_zoomSlider);

    //Start the update thread
    m_updateThread = new LogicUpdateThread(&m_allGateFields);
    m_updateThread->start();
}

DLG_Home::~DLG_Home()
{
    m_updateThread->stopRunning();
    m_updateThread->exit();

    //delete m_currentGateField

    //Delete gatefields
    for (GateField* gf : m_allGateFields)
    {
        delete gf;
    }

    delete ui;
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


// -- BUTTON HANDLERS FOR NEW GATES --

void DLG_Home::on_btn_sourceGate_clicked()
{
    if(m_currentGateField)
    {
        m_currentGateField->addGameObject(new GateInputBox());
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
        m_currentGateField->addGameObject(new GateOutputBox());
        on_btn_Drag_clicked();
    }
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
    //Add gatefield
    const std::string pageName = "Page " + std::to_string(m_allGateFields.size() + 1);
    m_currentGateField = new GateField(m_ZoomFactor);
    m_allGateFields.push_back(m_currentGateField);
    ui->PlayField->addTab(m_currentGateField,tr(pageName.c_str()));
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

//Calls the update function of all the gates in all of the gateFields
void LogicUpdateThread::run()
{
    while (!m_bStop)
        for (GateField* gf : *m_pAllGateFields)
            if(gf)
                gf->updateFunction();
}

void LogicUpdateThread::stopRunning()
{
    m_bStop = true;
}


