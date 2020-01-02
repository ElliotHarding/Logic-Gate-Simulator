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

    //todo save task

    delete this;
}
