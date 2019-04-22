#include "dlg_home.h"
#include "ui_dlg_home.h"

DLG_Home::DLG_Home(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DLG_Home)
{
    ui->setupUi(this);
    setMouseTracking(true);
    ui->PlayField->clear();
    on_btn_newPage_clicked();

    //Start the update thread
    m_updateThread = new LogicUpdateThread(&m_allGateFields);
    //m_updateThread->start();
}

DLG_Home::~DLG_Home()
{
    m_updateThread->stopRunning();
    m_updateThread->exit();

    //Delete gatefields
    {
        //delete m_currentGateField;

        for (GateField* gf : m_allGateFields)
        {
            delete gf;
        }
    }

    delete ui;
}


void DLG_Home::UpdateThread()
{
    while (true)
    {
        for (GateField* gf : m_allGateFields)
        {
            gf->updateFunction();
        }
    }
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

void DLG_Home::on_btn_newPage_clicked()
{
    //Add gatefield
    const std::string pageName = "Page " + std::to_string(m_allGateFields.size() + 1);
    m_currentGateField = new GateField();
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
    m_pAllGateFields(allGateFields),
    m_bStop(false)
{
}

void LogicUpdateThread::run()
{
    while (!m_bStop)
        for (GateField* gf : *m_pAllGateFields)
            gf->updateFunction();
}

void LogicUpdateThread::stopRunning()
{
    m_bStop = true;
}
