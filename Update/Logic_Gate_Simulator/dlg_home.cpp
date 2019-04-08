#include "dlg_home.h"
#include "ui_dlg_home.h"

DLG_Home::DLG_Home(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DLG_Home)
{
    ui->setupUi(this);
    setMouseTracking(true);
}

DLG_Home::~DLG_Home()
{
    delete ui;
}

void DLG_Home::mousePressEvent(QMouseEvent* click)
{
    const int clickX = click->x();
    const int clickY = click->y();

    m_gameObjectController.handleInput(clickX,clickY, m_currentClickMode);

    QMainWindow::mousePressEvent(click);
}

// -- BUTTON HANDLERS FOR CLICK MODES --

void DLG_Home::on_btn_Drag_clicked()
{
    m_currentClickMode = CLICK_DRAG;
    ui->lbl_clickMode->setText("Click Mode : Drag");
}
void DLG_Home::on_btn_Delete_clicked()
{
    m_currentClickMode = CLICK_DELETE_GATE;
    ui->lbl_clickMode->setText("Click Mode : Delete");
}
void DLG_Home::on_btn_link_clicked()
{
    m_currentClickMode = CLICK_LINK_NODES;
    ui->lbl_clickMode->setText("Click Mode : Link");
}


// -- BUTTON HANDLERS FOR NEW GATES --

void DLG_Home::on_btn_sourceGate_clicked()
{
    m_gameObjectController.addGameObject(new GateInputBox());
}
void DLG_Home::on_btn_notGate_clicked()
{
    m_gameObjectController.addGameObject(new GateNot());
}
void DLG_Home::on_btn_orGate_clicked()
{
    m_gameObjectController.addGameObject(new GateOr());
}
void DLG_Home::on_btn_andGate_clicked()
{
    m_gameObjectController.addGameObject(new GateAnd());
}


// -- OTHER BUTTON HANDLERS --

void DLG_Home::on_btn_newPage_clicked()
{
    const std::string pageName = "Page " + std::to_string(++m_pageNumber);
    ui->PlayField->addTab(new QWidget(),tr(pageName.c_str()));
}

