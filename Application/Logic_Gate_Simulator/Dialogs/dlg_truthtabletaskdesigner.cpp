#include "dlg_truthtabletaskdesigner.h"

DLG_TruthTableTaskDesigner::DLG_TruthTableTaskDesigner(int iInputs, int iOutputs) :
    DLG_Home(nullptr)
{
    m_pBtnSubmit = new QPushButton("Submit", this);
    m_pBtnSubmit->setGeometry(805, 470, 120, 40);

    m_allGateFields.push_back(new GateField(m_zoomFactor, "Task", this, m_pDlgSaveGateCollection));
    m_iCurrentGateField = 0;
    m_allGateFields[m_iCurrentGateField]->setAutoFillBackground(true);
    m_allGateFields[m_iCurrentGateField]->setGeometry(160, 65, 595, 486);
    m_allGateFields[m_iCurrentGateField]->raise();

    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::white);
    m_allGateFields[m_iCurrentGateField]->setPalette(pal);

    connect(m_pBtnSubmit, &QPushButton::clicked, this, &DLG_TruthTableTaskDesigner::onSubmitButton);

    this->layout()->addWidget(m_allGateFields[m_iCurrentGateField]);
    this->layout()->addWidget(m_pBtnSubmit);

    m_task.m_inputs = iInputs;
    m_task.m_outputs = iOutputs;
    m_task.m_bCircuitTask = false;

    int ylen = (486*2)/(m_task.m_inputs+1);
    for (int x = 0; x < iInputs; ++x)
    {
        GateToggle* newGate = new GateToggle();
        newGate->SetPosition(5, ylen * (x + 1));
        newGate->SetUserDisabled();
        m_allGateFields[m_iCurrentGateField]->AddGate(newGate, false, false);
        m_inputGates.push_back(newGate);
    }

    ylen = (486*2)/(m_task.m_outputs+1);
    for(int x = 0; x < iOutputs; x++)
    {
        GateReciever* newGate = new GateReciever();
        newGate->SetPosition(1000, ylen * (x + 1));
        newGate->SetUserDisabled();
        m_allGateFields[m_iCurrentGateField]->AddGate(newGate, false, false);
        m_outputGates.push_back(newGate);
    }
}

DLG_TruthTableTaskDesigner::~DLG_TruthTableTaskDesigner()
{
    for (int x = 0; x < m_inputGates.size(); x++)
    {
        m_inputGates[x] = nullptr;
    }
    for (int x = 0; x < m_outputGates.size(); x++)
    {
        m_outputGates[x] = nullptr;
    }
}

void DLG_TruthTableTaskDesigner::onSubmitButton()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 "/tasks",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);

    std::ofstream saveFile(dir.toStdString() + "/" + "todo" + ".GateField");

    //state that its a truth table task with 1
    saveFile << "0" << std::endl << m_task.m_inputs << std::endl << m_task.m_outputs << std::endl << std::endl;

    //save gates
    m_allGateFields[m_iCurrentGateField]->SaveData(saveFile);

    delete this;
}
