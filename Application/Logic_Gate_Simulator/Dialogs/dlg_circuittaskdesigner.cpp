#include "dlg_circuittaskdesigner.h"
#include "ui_dlg_circuittaskdesigner.h"
#include <QLayout>

DLG_CircuitTaskDesigner::DLG_CircuitTaskDesigner(int inputs, int outputs, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DLG_CircuitTaskDesigner)
{
    ui->setupUi(this);

    m_pTruthTable = new Widget_TruthTable(inputs, outputs, this);
    m_pTruthTable->setAutoFillBackground(true);
    m_pTruthTable->setGeometry(0, 0, 200, 350);
    this->layout()->addWidget(m_pTruthTable);
    m_newTask.m_inputs = inputs;
    m_newTask.m_outputs = outputs;
    m_newTask.m_bCircuitTask = true;
}

DLG_CircuitTaskDesigner::~DLG_CircuitTaskDesigner()
{
    delete ui;
}

void DLG_CircuitTaskDesigner::on_btn_done_clicked()
{
    m_newTask.results = m_pTruthTable->GetAnswer();

    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 "/tasks",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);
    std::ofstream saveFile(dir.toStdString() + "/" + "todo" + ".GateField");

    saveFile << "0" << std::endl << m_newTask.m_inputs << std::endl << m_newTask.m_outputs << std::endl;
    saveFile << "{" << std::endl;
    for (std::vector<bool> vector : m_newTask.results)
    {
        saveFile << "{" << std::endl;
        for (bool b : vector)
        {
            saveFile << b << std::endl;
        }
        saveFile << "}" << std::endl;
    }
    saveFile << "}" << std::endl;

    delete this;
}
