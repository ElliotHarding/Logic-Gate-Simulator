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
    const int clickX = click->


    QMainWindow::mousePressEvent(click);
}

void DLG_Home::on_btn_Drag_clicked()
{
    m_currentClickMode = CLICK_DRAG;
}

void DLG_Home::on_btn_Delete_clicked()
{
    m_currentClickMode = CLICK_DELETE_GATE;
}

void DLG_Home::on_btn_link_clicked()
{
    m_currentClickMode = CLICK_LINK_NODES;
}
