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


    //todo inputs & outputs
}

void DLG_TruthTableTaskDesigner::onSubmitButton()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 "/tasks",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);

    std::ofstream saveFile(dir.toStdString() + "/" + "todo" + ".GateField");

    //state that its a truth table task with 1
    saveFile << "1" << std::endl << m_task.m_inputs << std::endl << m_task.m_outputs << std::endl;

    //save gates
    m_allGateFields[m_iCurrentGateField]->SaveData(saveFile);

    delete this;
}
