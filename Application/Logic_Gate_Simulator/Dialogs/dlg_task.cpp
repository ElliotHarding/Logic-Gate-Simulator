#include "dlg_task.h"
#include "ui_dlg_task.h"
#include "ui_dlg_home.h"
#include "dlg_taskmanager.h"
#include "gatereader.h"

dlg_task::dlg_task(DLG_TaskManager* pTaskManager, Task task) :
    DLG_Home(pTaskManager),
    m_pTaskManager(pTaskManager),
    m_task(task)
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
    //ui->menuBar->hide();

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

    m_pBtnSubmit = new QPushButton("Submit", this);
    m_pBtnSubmit->setGeometry(805, 470, 120, 40);

    m_pTruthTableWidget = new Widget_TruthTable(m_task.m_inputs, m_task.m_outputs, this);
    m_pTruthTableWidget->raise();
    m_pTruthTableWidget->setAutoFillBackground(true);
    m_pTruthTableWidget->setGeometry(765, 110, 200, 350);

    m_allGateFields.push_back(new GateField(m_zoomFactor, "Task", this, m_pDlgSaveGateCollection));
    m_iCurrentGateField = 0;
    m_allGateFields[m_iCurrentGateField]->setAutoFillBackground(true);
    m_allGateFields[m_iCurrentGateField]->setGeometry(160, 65, 595, 486);
    m_allGateFields[m_iCurrentGateField]->raise();

    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::white);
    m_allGateFields[m_iCurrentGateField]->setPalette(pal);

    if(m_task.m_bCircuitTask)
    {
        m_pTruthTableWidget->SetResults(m_task.results);

        std::ifstream saveFile = std::ifstream(m_task.m_circuitFileName.toUtf8());

        GateReader reader;
        reader.ReadGateField(saveFile, m_allGateFields[m_iCurrentGateField]);

        std::vector<Gate*>& gates = m_allGateFields[m_iCurrentGateField]->GetGates();
        for (Gate* g : gates)
            g->SetUserDisabled();
    }
    else
    {
        int ylen = (486*2)/(m_task.m_inputs+1);
        for (int x = 0; x < task.m_inputs; ++x)
        {
            GateToggle* newGate = new GateToggle();
            newGate->SetPosition(5, ylen * (x + 1));
            newGate->SetUserDisabled();
            m_allGateFields[m_iCurrentGateField]->AddGate(newGate, false, false);
            m_inputGates.push_back(newGate);
        }

        ylen = (486*2)/(m_task.m_outputs+1);
        for(int x = 0; x < m_task.m_outputs; x++)
        {
            GateReciever* newGate = new GateReciever();
            newGate->SetPosition(1000, ylen * (x + 1));
            newGate->SetUserDisabled();
            m_allGateFields[m_iCurrentGateField]->AddGate(newGate, false, false);
            m_outputGates.push_back(newGate);
        }
    }

    connect(m_pBtnSubmit, &QPushButton::clicked, this, &dlg_task::onSubmitButtonClicked);

    this->layout()->addWidget(m_pTruthTableWidget);
    this->layout()->addWidget(m_allGateFields[m_iCurrentGateField]);
    this->layout()->addWidget(m_pBtnSubmit);
}

dlg_task::~dlg_task()
{
    m_pTaskManager = nullptr;
    delete m_pTruthTableWidget;
    delete m_pBtnSubmit;

    for(int x = 0; x < m_outputGates.size(); x++)
        m_outputGates[x] = nullptr;

    for(int x = 0; x < m_inputGates.size(); x++)
        m_inputGates[x] = nullptr;

    //delete m_allGateFields[m_iCurrentGateField]; deleted via ~dlg_home

    delete ui;
}

void dlg_task::onSubmitButtonClicked()
{
    if(m_task.m_bCircuitTask)
    {
        std::vector<std::vector<bool>> inputs;
        if(m_task.m_inputs == 1)
            inputs = valuesFor1inputs;
        else if(m_task.m_inputs == 2)
            inputs = valuesFor2inputs;
        else if(m_task.m_inputs == 3)
            inputs = valuesFor3inputs;
        else
            inputs = valuesFor4inputs;

        m_allGateFields[m_iCurrentGateField]->GetGates(); //call lock on gates

        const int numRows = inputs[0].size();
        for(int row = 0; row < numRows; row++)
        {
            for(int input = 0; input < m_task.m_inputs; input++)
            {
                m_inputGates[input]->SetPowerState(inputs[input][row]);
            }

            for (int output = 0; output < m_outputGates.size(); output++)
            {
                GateReciever* outputGate = m_outputGates[output];
                if (m_task.results[output][row] != outputGate->GetValue())
                {
                    SendUserMessage("Incorrect! Try again.");
                    m_allGateFields[m_iCurrentGateField]->FinishWithGates();
                    return;
                }
            }
        }

        m_allGateFields[m_iCurrentGateField]->FinishWithGates();
    }
    else
    {
        const std::vector<std::vector<bool>> answers = m_pTruthTableWidget->GetAnswer();
        for (int iVec = 0; iVec < answers.size(); iVec++)
        {
            for(int iRes = 0; iRes < answers[iVec].size(); iRes++)
            {
                if(answers[iVec][iRes] != m_task.results[iVec][iRes])
                {
                    SendUserMessage("Incorrect! Try again.");
                    return;
                }
            }
        }
    }

    m_pTaskManager->OnTaskCompleted();
}
