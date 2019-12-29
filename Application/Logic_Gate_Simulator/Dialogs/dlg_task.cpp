#include "dlg_task.h"
#include "ui_dlg_task.h"
#include "ui_dlg_home.h"

dlg_task::dlg_task(QWidget *parent) :
    DLG_Home(parent)
{
    ui->btn_newPage->hide();
    ui->btn_Save->hide();
    ui->btn_load->hide();
    ui->PlayField->hide();
    ui->layout_ZoomSlider->hide();
    ui->btn_zoomIn->hide();
    ui->btn_zoomOut->hide();

    m_allGateFields.push_back(new GateField(m_zoomFactor, "Task", this, m_pDlgSaveGateCollection));
    m_iCurrentGateField = 0;
    this->layout()->addWidget(m_allGateFields[m_iCurrentGateField]);
    m_allGateFields[m_iCurrentGateField]->raise();
    m_allGateFields[m_iCurrentGateField]->setLayout();
}

dlg_task::~dlg_task()
{
    delete ui;
}
