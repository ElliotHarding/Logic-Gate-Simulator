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
    ui->line_3->hide();
    ui->line_6->hide();
    ui->line_8->hide();
    ui->btn_redo->hide();
    ui->btn_undo->hide();
    m_allGateFields.push_back(new GateField(m_zoomFactor, "Task", this, m_pDlgSaveGateCollection));
    m_iCurrentGateField = 0;
    m_allGateFields[m_iCurrentGateField]->setStyleSheet("");
    m_allGateFields[m_iCurrentGateField]->setAutoFillBackground(true);

    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::white);
    m_allGateFields[m_iCurrentGateField]->setPalette(pal);

    this->layout()->addWidget(m_allGateFields[m_iCurrentGateField]);
    m_allGateFields[m_iCurrentGateField]->setGeometry(160, 65, 805, 486);
    m_allGateFields[m_iCurrentGateField]->raise();

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

dlg_task::~dlg_task()
{
    delete ui;
}
