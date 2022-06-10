#include "dlg_task.h"
//#include "ui_dlg_task.h"
//#include "ui_dlg_home.h"
#include "dlg_taskmanager.h"
#include "gatereader.h"
#include "widget_text.h"

dlg_task::dlg_task(DLG_TaskManager* pTaskManager, std::string* taskFileName, bool& succeded) :
    DLG_Home(pTaskManager),
    m_pTaskManager(pTaskManager)
{
    //Read task file

    std::ifstream taskFile = std::ifstream(*taskFileName);

    if(!taskFile.is_open())
    {
        delete this;
        succeded = false;
        return;
    }

    std::string readString;
    taskFile >> readString;
    m_task.m_bCircuitTask = tryStoi(readString, 1);

    taskFile >> readString;
    m_task.m_inputs = tryStoi(readString, 1);

    taskFile >> readString;
    m_task.m_outputs = tryStoi(readString, 1);

    m_pTruthTableWidget = new Widget_TruthTable(m_task.m_inputs, m_task.m_outputs, this);
    m_pTruthTableWidget->raise();
    m_pTruthTableWidget->setAutoFillBackground(true);

    m_allGateFields.push_back(new GateField(m_zoomFactor, "Task", this, m_pDlgSaveGateCollection, true, true, true));
    m_iCurrentGateField = 0;
    m_allGateFields[m_iCurrentGateField]->setAutoFillBackground(true);
    m_allGateFields[m_iCurrentGateField]->raise();

    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::white);
    m_allGateFields[m_iCurrentGateField]->setPalette(pal);

    Widget_Text* taskInfo;

    if(m_task.m_bCircuitTask)
    {
        taskInfo = new Widget_Text("Create the circuit that matches \nthe truth table", this);

        int ylen = (486*2)/(m_task.m_inputs+1);
        for (int x = 0; x < m_task.m_inputs; ++x)
        {
            GateToggle* newGate = new GateToggle(5, ylen * (x + 1));
            newGate->setEnabled(false);
            m_allGateFields[m_iCurrentGateField]->AddGate(newGate, false);
            m_inputGates.push_back(newGate);
        }

        ylen = (486*2)/(m_task.m_outputs+1);
        for(int x = 0; x < m_task.m_outputs; x++)
        {
            GateReciever* newGate = new GateReciever(1000, ylen * (x + 1));
            newGate->setEnabled(false);
            m_allGateFields[m_iCurrentGateField]->AddGate(newGate, false);
            m_outputGates.push_back(newGate);
        }

        //read bools
        std::vector<std::vector<bool>> results;
        results.push_back(std::vector<bool>());

        taskFile >> readString;
        taskFile >> readString;
        taskFile >> readString;
        while(readString != "--")
        {
            if(readString == "{")
            {
                results.push_back(std::vector<bool>());
            }
            results[results.size()-1].push_back(tryStoi(readString, 0));
            taskFile >> readString;
        }

        m_task.results = results;
        m_pTruthTableWidget->SetResults(m_task.results);
    }
    else
    {
        taskInfo = new Widget_Text("Fill the truth table to match \nthe circuit", this);

        GateReader reader;
        reader.ReadGateField(taskFile, m_allGateFields[m_iCurrentGateField], false);

        std::vector<Gate*>& gates = m_allGateFields[m_iCurrentGateField]->GetGates();
        for (Gate* g : gates)
        {
            if(g->GetType() == GateType::GATE_EMMITTER)
                m_inputGates.push_back(dynamic_cast<GateToggle*>(g));
            else if(g->GetType() == GateType::GATE_RECIEVER)
                m_outputGates.push_back(dynamic_cast<GateReciever*>(g));

            g->setEnabled(false);
        }
    }

    m_pBtnSubmit = new QPushButton("Submit", this);

    taskInfo->setGeometry(765, 65, 200, 70);
    m_pTruthTableWidget->setGeometry(765, 143, 200, 350);
    m_pBtnSubmit->setGeometry(805, 503, 120, 40);
    m_allGateFields[m_iCurrentGateField]->setGeometry(160, 65, 595, 486);

    connect(m_pBtnSubmit, &QPushButton::clicked, this, &dlg_task::onSubmitButtonClicked);

    this->layout()->addWidget(m_pTruthTableWidget);
    this->layout()->addWidget(m_allGateFields[m_iCurrentGateField]);
    this->layout()->addWidget(m_pBtnSubmit);
}

dlg_task::~dlg_task()
{
    m_pTaskManager = nullptr;

    if(m_pTruthTableWidget)
        delete m_pTruthTableWidget;

    if(m_pBtnSubmit)
        delete m_pBtnSubmit;

    //Actual pointers get cleared by gatefield
    m_outputGates.clear();
    m_inputGates.clear();

    //delete m_allGateFields[m_iCurrentGateField]; deleted via ~dlg_home

    delete ui;
}

void dlg_task::onSubmitButtonClicked()
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

    std::vector<std::vector<bool>> answers;
    if(m_task.m_bCircuitTask)
        answers = m_task.results;
    else
        answers = m_pTruthTableWidget->GetAnswer();

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
            if (answers[output][row] != outputGate->GetValue())
            {
                //Incorrect ~ reset
                for(int input = 0; input < m_task.m_inputs; input++)
                {
                    m_inputGates[input]->SetPowerState(0);
                }

                //Notify user
                SendUserMessage("Incorrect! Try again.");
                return;
            }
        }
    }

    m_pTaskManager->OnTaskCompleted();
}

int dlg_task::tryStoi(std::string s, int defaultVal)
{
    try
    {
        return std::stoi(s);
    }
    catch (...)
    {
        return defaultVal;
    }
}

void dlg_task::closeEvent(QCloseEvent *event)
{
    m_pTaskManager->show();
    event->accept();
}
