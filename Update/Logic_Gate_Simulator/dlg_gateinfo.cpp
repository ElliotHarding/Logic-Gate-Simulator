#include "dlg_gateinfo.h"
#include "ui_dlg_gateinfo.h"
#include "gatefield.h"
#include "allgates.h"
#include <QLayout>

DLG_GateInfo::DLG_GateInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DLG_GateInfo)
{
    ui->setupUi(this);
}

DLG_GateInfo::~DLG_GateInfo()
{
    delete ui;
    m_gateDisplayed = nullptr;
}

void DLG_GateInfo::setGate(Gate *g)
{
    if(m_gateDisplayed != g)
    {
        m_gateDisplayed = g;

        //Set if enabled
        ui->checkBox->setCheckState(
                    m_gateDisplayed->Enabled ? Qt::CheckState::Checked : Qt::CheckState::Unchecked
                    );

        //Display gate specific info
        QString gateName;
        switch (m_gateDisplayed->GetType())
        {
            case GateType::GATE_OR:
                gateName = "Or Gate";
                break;
            case GateType::GATE_AND:
                gateName = "And Gate";
                break;
            case GateType::GATE_NOT:
                gateName = "Not Gate";
                break;
            case GateType::GATE_NULL:
                gateName = "Unknown Gate";
                break;
            case GateType::GATE_TIMER:
                gateName = "Timer Gate";
                break;
            case GateType::GATE_EMMITTER:
                gateName = "Emmiter Gate";
                break;
            case GateType::GATE_RECIEVER:
                gateName = "Reciever Gate";
                break;
            case GateType::GATE_COLLECTION:
                gateName = "Gate Collection";
                break;
            case GateType::GATE_CONST_ACTIVE:
                gateName = "Input On";
                break;
            case GateType::GATE_CONST_INACTIVE:
                gateName = "Input Off";
                break;
        }
        ui->lbl_GateType->setText(gateName);
    }
}

void DLG_GateInfo::on_btn_Delete_clicked()
{
    if (m_gateDisplayed->ParentField)
    {
        m_gateDisplayed->ParentField->removeGate(m_gateDisplayed);
        m_gateDisplayed = nullptr;
    }
}

void DLG_GateInfo::on_checkBox_clicked()
{
    if(ui->checkBox->checkState() == Qt::CheckState::Checked)
    {
        m_gateDisplayed->Enabled = false;
        ui->checkBox->setCheckState(Qt::CheckState::Unchecked);
    }
    else
    {
        m_gateDisplayed->Enabled = true;
        ui->checkBox->setCheckState(Qt::CheckState::Checked);
    }
}
