#include "dlg_gateinfo.h"
#include "ui_dlg_gateinfo.h"
#include "allgates.h"
#include "dlg_home.h"
#include "converter.h"

#include <QLayout>

DLG_GateInfo::DLG_GateInfo(DLG_Home* parent) :
    QWidget(parent),
    ui(new Ui::DLG_GateInfo),
    m_pParent(parent)
{
    ui->setupUi(this);
    uiWhenNogateSelected();

    setGateField(nullptr);
}

DLG_GateInfo::~DLG_GateInfo()
{
    delete ui;
}

void DLG_GateInfo::setGate(Gate *g)
{
    m_pGateDisplayed = g;
    if(g == nullptr)
    {
        uiWhenNogateSelected();
        return;
    }

    //Default shown
    ui->lbl_GateType->show();
    ui->btn_DeleteGate->show();
    ui->lbl_Type->show();
    ui->signalCheck->show();
    ui->btn_label->show();

    ui->lbl_Frequency->hide();
    ui->lineEdit_Frequency->hide();
    ui->signalCheck->hide();
    ui->lineEdit_Frequency->hide();
    ui->btn_Edit->hide();
    ui->btn_drag->hide();
    ui->btn_expression->hide();
    ui->btn_save->hide();
    ui->btn_truthTable->hide();
    ui->btn_DeleteGate2->hide();
    ui->btn_label2->hide();

    //Display gate specific info
    QString gateName;
    switch (m_pGateDisplayed->getType())
    {
        case GateType::GATE_OR:
            gateName = "Or Gate";
            break;
        case GateType::GATE_NOR:
            gateName = "Nor Gate";
            break;
        case GateType::GATE_AND:
            gateName = "And Gate";
            break;
        case GateType::GATE_NAND:
            gateName = "Nand Gate";
            break;
        case GateType::GATE_EOR:
            gateName = "Eor Gate";
            break;
        case GateType::GATE_XOR:
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

            const int frequency = dynamic_cast<GateTimer*>(m_pGateDisplayed)->getFrequency();
            ui->lineEdit_Frequency->setText(std::to_string(frequency).c_str());

            break;
            }
        case GateType::GATE_EMMITTER:
            gateName = "Emmiter Gate";
            ui->signalCheck->show();
            ui->signalCheck->setCheckState( dynamic_cast<GateToggle*>(m_pGateDisplayed)
                        ->getPowerState() ?
                          Qt::CheckState::Checked : Qt::CheckState::Unchecked);
            break;
        case GateType::GATE_RECIEVER:
            gateName = "Reciever Gate";
            break;
        case GateType::GATE_COLLECTION:
            {
            gateName = "Gate Collection";
            ui->btn_drag->show();
            ui->btn_expression->show();
            ui->btn_save->show();
            ui->btn_truthTable->show();
            ui->btn_DeleteGate2->show();
            ui->btn_DeleteGate->hide();
            ui->btn_label2->show();
            ui->btn_label->hide();
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
            ui->btn_label->hide();
            break;
        default:
            gateName = "";
            break;
    }
    ui->lbl_GateType->setText(gateName);

    //Call to redraw
    update();
}

void DLG_GateInfo::setGateField(GateField *pGateField)
{
    m_pGateField = pGateField;

    if(m_pGateField)
    {
        ui->lineEdit_pageUpdateFrequency->setText(QString::number(m_pGateField->updateFrequency()));
        ui->lineEdit_pageUpdateFrequency->show();
        ui->lbl_pageUpdateFrequency->show();
        ui->line_divider->show();
    }
    else
    {
        setGate(nullptr);
        ui->lineEdit_pageUpdateFrequency->hide();
        ui->lbl_pageUpdateFrequency->hide();
        ui->line_divider->hide();
    }
}

void DLG_GateInfo::on_btn_DeleteGate_clicked()
{
    if(m_pGateDisplayed)
    {
        delete m_pGateDisplayed;
    }

    setGate(nullptr);
}

void DLG_GateInfo::on_btn_DeleteGate2_clicked()
{
    if(m_pGateDisplayed)
    {
        delete m_pGateDisplayed;
    }

    setGate(nullptr);
}

void DLG_GateInfo::on_lineEdit_Frequency_editingFinished()
{
    if(m_pGateDisplayed && dynamic_cast<GateTimer*>(m_pGateDisplayed))
    {
        QString frequencyString = ui->lineEdit_Frequency->text();
        int frequency = frequencyString.toInt();

        if(frequency > 0 && frequency < 30000)
        {
            dynamic_cast<GateTimer*>(m_pGateDisplayed)->setFrequency(frequency);
        }
        else
        {
            m_pParent->sendUserMessage("Frequency out of range!");
        }
    }
    else
    {
        Logger::log(LL_Error, "DLG_GateInfo::on_lineEdit_Frequency_editingFinished - Line editing on invalid object!");
    }
}

void DLG_GateInfo::on_signalCheck_clicked()
{
    if(m_pGateDisplayed)
    {
        if(dynamic_cast<GateToggle*>(m_pGateDisplayed))
            dynamic_cast<GateToggle*>(m_pGateDisplayed)->toggleOutputState();
    }
}

void DLG_GateInfo::uiWhenNogateSelected()
{
    ui->lbl_GateType->hide();
    ui->btn_DeleteGate->hide();
    ui->lbl_Type->hide();
    ui->signalCheck->hide();
    ui->lbl_Frequency->hide();
    ui->lineEdit_Frequency->hide();
    ui->btn_Edit->hide();
    ui->btn_drag->hide();
    ui->btn_expression->hide();
    ui->btn_save->hide();
    ui->btn_truthTable->hide();
    ui->btn_DeleteGate2->hide();
    ui->btn_label->hide();
    ui->btn_label2->hide();
}

void DLG_GateInfo::on_btn_Edit_clicked()
{
    if(m_pGateDisplayed->getType() == GATE_FPGA)
    {
        if(dynamic_cast<GateFPGA*>(m_pGateDisplayed))
        {
            m_pParent->editFPGA(dynamic_cast<GateFPGA*>(m_pGateDisplayed));
        }
        else
        {
            Logger::log(LL_Error, "DLG_GateInfo::on_btn_Edit_clicked - Can't cast GateFPGA!");
        }
    }

    else if(m_pGateDisplayed->getType() == GATE_TEXT_LABEL)
    {
        if(dynamic_cast<TextLabel*>(m_pGateDisplayed))
        {
            m_pParent->editTextLabel(dynamic_cast<TextLabel*>(m_pGateDisplayed));
        }
        else
        {
            Logger::log(LL_Error, "DLG_GateInfo::on_btn_Edit_clicked - Can't cast TextLabel!");
        }
    }
}

void DLG_GateInfo::on_lineEdit_pageUpdateFrequency_editingFinished()
{
    if(m_pGateField)
    {
        QString frequencyString = ui->lineEdit_pageUpdateFrequency->text();
        int frequency = frequencyString.toInt();

        if(frequency > 0 && frequency < 30000)
        {
            m_pGateField->setUpdateFrequency(frequency);
        }
        else
        {
            m_pParent->sendUserMessage("Frequency out of range!");
        }
    }
}

void DLG_GateInfo::on_btn_drag_clicked()
{
    if(dynamic_cast<GateCollection*>(m_pGateDisplayed))
        dynamic_cast<GateCollection*>(m_pGateDisplayed)->toggleDragMode();
}

void DLG_GateInfo::on_btn_save_clicked()
{
    if(dynamic_cast<GateCollection*>(m_pGateDisplayed))
        m_pParent->startSaveGateCollection(dynamic_cast<GateCollection*>(m_pGateDisplayed));
}

void DLG_GateInfo::on_btn_truthTable_clicked()
{
    if(dynamic_cast<GateCollection*>(m_pGateDisplayed))
    {
        TruthTable table;
        ConverterResult result = Converter::circuitToTruthTable(dynamic_cast<GateCollection*>(m_pGateDisplayed)->getGates(), table);
        if(result == ConverterResult::SUCCESS)
        {
            m_pParent->showGeneratedTruthTable(table);
        }
        else
        {
            m_pParent->sendUserMessage("Internal error. Failed to generate truth table. \n Check logs for details");
        }
    }
}

void DLG_GateInfo::on_btn_expression_clicked()
{
    if(dynamic_cast<GateCollection*>(m_pGateDisplayed))
    {
        if(m_pParent->getCurrentConversionAlgorithm() == ConversionAlgorithm::Random)
        {
            TruthTable truthTable;
            if(Converter::circuitToTruthTable(dynamic_cast<GateCollection*>(m_pGateDisplayed)->getGates(), truthTable) == ConverterResult::SUCCESS)
            {
                m_pParent->runRandomConversionThread(truthTable, GoalResult::GR_BooleanExpressions);
            }
            else
            {
                m_pParent->sendUserMessage("Internal error. Failed to generate boolean expressions. \n Check logs for details");
            }

            return;
        }

        std::vector<BooleanExpression> expressions;
        ConverterResult result = Converter::circuitToBooleanExpressions(dynamic_cast<GateCollection*>(m_pGateDisplayed)->getGates(), m_pParent->getCurrentConversionAlgorithm(), expressions);
        if(result == ConverterResult::SUCCESS)
        {
            m_pParent->showGeneratedBooleanExpressions(expressions);
        }
        else
        {
            m_pParent->sendUserMessage("Internal error. Failed to generate boolean expressions. \n Check logs for details");
        }
    }
}

void DLG_GateInfo::on_btn_label_clicked()
{
    TextLabel* pLabel = new TextLabel(m_pGateDisplayed->position().x(), m_pGateDisplayed->position().y(), "Label", QFont("Helvetica", 20));
    m_pGateDisplayed->addAttachedLabel(pLabel);

    m_pParent->editTextLabel(pLabel);
}

void DLG_GateInfo::on_btn_label2_clicked()
{
    TextLabel* pLabel = new TextLabel(m_pGateDisplayed->position().x(), m_pGateDisplayed->position().y(), "Label", QFont("Helvetica", 20));
    m_pGateDisplayed->addAttachedLabel(pLabel);

    m_pParent->editTextLabel(pLabel);
}
