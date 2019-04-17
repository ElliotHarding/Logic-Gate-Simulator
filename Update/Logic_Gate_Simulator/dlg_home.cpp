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
}

DLG_Home::~DLG_Home()
{
    delete m_currentGateField;
    delete ui;
}

// -- BUTTON HANDLERS FOR CLICK MODES --

void DLG_Home::on_btn_Drag_clicked()
{
    if(m_currentGateField)
    {
        m_currentGateField->setCurrentClickMode(CLICK_DRAG);
    }
    ui->lbl_clickMode->setText("Click Mode : Drag");

    QApplication::setOverrideCursor(Qt::CursorShape::SizeAllCursor);
}
void DLG_Home::on_btn_Delete_clicked()
{
    if(m_currentGateField)
    {
        m_currentGateField->setCurrentClickMode(CLICK_DELETE_GATE);
    }
    ui->lbl_clickMode->setText("Click on something to delete it!");

    QApplication::setOverrideCursor(Qt::CursorShape::CrossCursor);
}
void DLG_Home::on_btn_link_clicked()
{
    if(m_currentGateField)
    {
        m_currentGateField->setCurrentClickMode(CLICK_LINK_NODES);
    }
    ui->lbl_clickMode->setText("Select two nodes to connect");

    QApplication::setOverrideCursor(Qt::CursorShape::DragLinkCursor);
}
void DLG_Home::on_btn_DeleteLink_clicked()
{
    if(m_currentGateField)
    {
        m_currentGateField->setCurrentClickMode(CLICK_LINK_NODES);
    }
    ui->lbl_clickMode->setText("Select two nodes to drag");

    QApplication::setOverrideCursor(Qt::CursorShape::DragLinkCursor);
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


// -- OTHER BUTTON HANDLERS --

void DLG_Home::on_btn_newPage_clicked()
{
    const std::string pageName = "Page " + std::to_string(++m_pageNumber);
    m_currentGateField = new GateField();
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
