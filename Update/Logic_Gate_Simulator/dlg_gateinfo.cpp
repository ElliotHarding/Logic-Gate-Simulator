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
    ui->signalCheck->hide();
    ui->lbl_Frequency->hide();
    ui->lineEdit_Frequency->hide();

    m_infoUpdateThread = new InfoUpdateThread(this);
    m_infoUpdateThread->start();
}

DLG_GateInfo::~DLG_GateInfo()
{
    delete ui;
    m_gateDisplayed = nullptr;
    m_pParent = nullptr;
    m_infoUpdateThread->stop();
    delete m_infoUpdateThread;
}

void DLG_GateInfo::setGate(Gate *g)
{
    m_gateDisplayed = g;

    //Set if enabled
    ui->checkBox->setCheckState(
                m_gateDisplayed->Enabled ? Qt::CheckState::Checked : Qt::CheckState::Unchecked
                );

    //Display gate specific info
    ui->signalCheck->hide();
    ui->lbl_Frequency->hide();
    ui->lineEdit_Frequency->hide();
    ui->dragModeCheck->hide();
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
            {
            gateName = "Timer Gate";
            ui->lbl_Frequency->show();
            ui->lineEdit_Frequency->show();
            const int frequency = dynamic_cast<GateTimer*>(m_gateDisplayed)->getFrequency();
            ui->lineEdit_Frequency->setText(QString(frequency));
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
            ui->dragModeCheck->show();
            ui->dragModeCheck->setCheckState( dynamic_cast<GateCollection*>(m_gateDisplayed)
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
    }
    ui->lbl_GateType->setText(gateName);
}

void DLG_GateInfo::RefreshInfo()
{
    if(m_gateDisplayed)
        setGate(m_gateDisplayed);
}

void DLG_GateInfo::on_checkBox_clicked()
{
    if(m_gateDisplayed)
        if(m_gateDisplayed->Enabled)
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

void DLG_GateInfo::on_btn_DeleteGate_clicked()
{
    if(m_gateDisplayed)
        m_pParent->DeleteGate(m_gateDisplayed);
    m_gateDisplayed = nullptr;
}

void DLG_GateInfo::on_lineEdit_Frequency_editingFinished()
{
    QString frequencyString = ui->lineEdit_Frequency->text();
    int frequency = frequencyString.toInt();

    if(frequency > 0 && frequency < 30000)
    {
        if(m_gateDisplayed)
            dynamic_cast<GateTimer*>(m_gateDisplayed)->setFrequency(frequency);
    }
}

void DLG_GateInfo::on_dragModeCheck_clicked()
{
   if(m_gateDisplayed)
       if(dynamic_cast<GateCollection*>(m_gateDisplayed))
           dynamic_cast<GateCollection*>(m_gateDisplayed)->ToggleDragMode();
}

void DLG_GateInfo::on_signalCheck_clicked()
{
    if(m_gateDisplayed)
        if(dynamic_cast<GateToggle*>(m_gateDisplayed))
            dynamic_cast<GateToggle*>(m_gateDisplayed)->ToggleOutputState();
}


InfoUpdateThread::InfoUpdateThread(DLG_GateInfo* parent) :
    m_pInfoDialog(parent)
{

}

InfoUpdateThread::~InfoUpdateThread()
{
    m_pInfoDialog = nullptr;
}

void InfoUpdateThread::stop()
{
     m_bStopThread = true;
}

void InfoUpdateThread::run()
{
    while(!m_bStopThread)
    {
        QThread::msleep(1000);

        if(m_pInfoDialog)
        {
            m_pInfoDialog->RefreshInfo();
        }
    }
}
