#include "dlg_gateinfo.h"
#include "ui_dlg_gateinfo.h"
#include "gatefield.h"
#include "allgates.h"
#include <QLayout>
#include "dlg_home.h"

DLG_GateInfo::DLG_GateInfo(DLG_Home* parent) :
    QWidget(parent),
    ui(new Ui::DLG_GateInfo),
    m_pParent(parent)
{
    ui->setupUi(this);
    UiWhenNoGateSelected();
}

DLG_GateInfo::~DLG_GateInfo()
{
    delete ui;
    m_gateDisplayed = nullptr;
    m_pParent = nullptr;
}

void DLG_GateInfo::setGate(Gate *g)
{
    m_gateDisplayed = g;
    if(g == nullptr)
    {
        UiWhenNoGateSelected();
        return;
    }
    else
    {
        //Default shown
        ui->lbl_GateType->show();
        ui->cb_Enabled->show();
        ui->btn_DeleteGate->show();
        ui->lbl_Type->show();
        ui->signalCheck->show();

        ui->lbl_Frequency->hide();
        ui->lineEdit_Frequency->hide();
        ui->cb_DragMode->hide();
        ui->signalCheck->hide();
        ui->lineEdit_Frequency->hide();
        ui->btn_Edit->hide();
    }

    //Set if enabled
    ui->cb_Enabled->setCheckState(
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
        case GateType::GATE_EOR:
            gateName = "Xor Gate";
            break;
        case GateType::GATE_TRI_OR:
            gateName = "Or Gate (Tri)";
            break;
        case GateType::GATE_TRI_AND:
            gateName = "And Gate (Tri)";
            break;
        case GateType::GATE_TRI_EOR:
            gateName = "Xor Gate (Tri)";
            break;
        case GateType::GATE_NOT:
            gateName = "Not Gate";
            break;
        case GateType::GATE_NULL:
            gateName = "Unknown Gate";
            break;
        case GateType::GATE_TIMER:
            {

            gateName = "Timer Gate";
            ui->lbl_Frequency->show();
            ui->lineEdit_Frequency->show();

            const int frequency = dynamic_cast<GateTimer*>(m_gateDisplayed)->getFrequency();
            ui->lineEdit_Frequency->setText(std::to_string(frequency).c_str());

            break;
            }
        case GateType::GATE_EMMITTER:
            gateName = "Emmiter Gate";
            ui->signalCheck->show();
            ui->signalCheck->setCheckState( dynamic_cast<GateToggle*>(m_gateDisplayed)
                        ->GetPowerState() ?
                          Qt::CheckState::Checked : Qt::CheckState::Unchecked);
            break;
        case GateType::GATE_RECIEVER:
            gateName = "Reciever Gate";
            break;
        case GateType::GATE_COLLECTION:
            {
            gateName = "Gate Collection";
            ui->cb_DragMode->show();
            ui->cb_DragMode->setCheckState( dynamic_cast<GateCollection*>(m_gateDisplayed)
                            ->IsDragAll() ?
                            Qt::CheckState::Checked : Qt::CheckState::Unchecked);
            break;
            }
        case GateType::GATE_CONST_ACTIVE:
            gateName = "Input On";
            break;
        case GateType::GATE_CONST_INACTIVE:
            gateName = "Input Off";
            break;
        case GateType::GATE_NUMBER_OUT:
            gateName = "Number output";
            break;
        case GateType::GATE_FPGA:
            gateName = "FPGA";
            ui->btn_Edit->show();
            break;
        case GateType::GATE_TEXT_LABEL:
            gateName = "Label";
            ui->btn_Edit->show();
            break;
        default:
            gateName = "";
            break;
    }
    ui->lbl_GateType->setText(gateName);

    //Call to redraw
    update();
}

void DLG_GateInfo::on_btn_DeleteGate_clicked()
{
    if(m_gateDisplayed)
    {
        GateField* gf = m_gateDisplayed->GetParent();
        m_pParent->DeleteGate(m_gateDisplayed);

        gf->update();
        gf = nullptr;
    }

    setGate(nullptr);
}

void DLG_GateInfo::on_lineEdit_Frequency_editingFinished()
{
    QString frequencyString = ui->lineEdit_Frequency->text();
    int frequency = frequencyString.toInt();

    if(frequency > 0 && frequency < 30000)
    {
        if(m_gateDisplayed)
        {
            dynamic_cast<GateTimer*>(m_gateDisplayed)->setFrequency(frequency);
            m_gateDisplayed->GetParent()->update();
        }
    }
}

void DLG_GateInfo::on_cb_DragMode_clicked()
{
   if(m_gateDisplayed)
   {
       if(dynamic_cast<GateCollection*>(m_gateDisplayed))
           dynamic_cast<GateCollection*>(m_gateDisplayed)->ToggleDragMode();
       m_gateDisplayed->GetParent()->update();
   }

}

void DLG_GateInfo::on_signalCheck_clicked()
{
    if(m_gateDisplayed)
    {
        if(dynamic_cast<GateToggle*>(m_gateDisplayed))
            dynamic_cast<GateToggle*>(m_gateDisplayed)->ToggleOutputState();

         m_gateDisplayed->GetParent()->update();
    }
}


void DLG_GateInfo::on_cb_Enabled_clicked()
{
    if(m_gateDisplayed)
    {
        if(m_gateDisplayed->Enabled)
        {
            m_gateDisplayed->Enabled = false;
            ui->cb_Enabled->setCheckState(Qt::CheckState::Unchecked);
        }
        else
        {
            m_gateDisplayed->Enabled = true;
            ui->cb_Enabled->setCheckState(Qt::CheckState::Checked);
        }

        m_gateDisplayed->GetParent()->update();
    }
}

void DLG_GateInfo::UiWhenNoGateSelected()
{
    ui->lbl_GateType->hide();
    ui->cb_Enabled->hide();
    ui->btn_DeleteGate->hide();
    ui->lbl_Type->hide();
    ui->signalCheck->hide();
    ui->lbl_Frequency->hide();
    ui->lineEdit_Frequency->hide();
    ui->cb_DragMode->hide();
    ui->btn_Edit->hide();
}

void DLG_GateInfo::on_btn_Edit_clicked()
{
    if(m_gateDisplayed->GetType() == GATE_FPGA)
    {
        dynamic_cast<GateFPGA*>(m_gateDisplayed)->OpenEditor();
    }

    if(m_gateDisplayed->GetType() == GATE_TEXT_LABEL)
    {
        dynamic_cast<TextLabel*>(m_gateDisplayed)->ShowTextEditor();
    }
}
