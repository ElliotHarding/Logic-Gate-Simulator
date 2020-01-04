#include "dlg_circuittaskdesigner.h"
#include "ui_dlg_circuittaskdesigner.h"
#include <QLayout>
#include "filelocations.h"

DLG_CircuitTaskDesigner::DLG_CircuitTaskDesigner(int inputs, int outputs, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DLG_CircuitTaskDesigner)
{
    ui->setupUi(this);

    setAutoFillBackground(true);
    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::white);
    setPalette(pal);

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

    QStringList nameFilter("*.GateField");
    QDir directory(c_tasksLocation);
    QStringList fileList = directory.entryList(nameFilter);
    bool goodFileName = false;
    int fileNameInt = -1;
    std::string fileNameString = std::to_string(fileNameInt) + ".GateField";
    while (goodFileName == false)
    {
        fileNameString = std::to_string(++fileNameInt) + ".GateField";

        goodFileName = true;
        for (QString file : fileList)
        {
            if(file.toStdString() == fileNameString)
                goodFileName = false;
        }
    }

    std::ofstream saveFile(c_tasksLocation.toStdString() + fileNameString);

    saveFile << "1" << std::endl << m_newTask.m_inputs << std::endl << m_newTask.m_outputs << std::endl;
    saveFile << "{{" << std::endl;
    for (std::vector<bool> vector : m_newTask.results)
    {
        saveFile << "{" << std::endl;
        for (bool b : vector)
        {
            saveFile << b << std::endl;
        }
    }
    saveFile << "--" << std::endl;


    delete this;
}
