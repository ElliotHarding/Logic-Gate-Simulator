#include "dlg_configurefpga.h"
#include "ui_dlg_configurefpga.h"

DLG_ConfigureFPGA::DLG_ConfigureFPGA(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DLG_ConfigureFPGA)
{
    ui->setupUi(this);
}

DLG_ConfigureFPGA::~DLG_ConfigureFPGA()
{
    delete ui;
}

void DLG_ConfigureFPGA::open(GateFPGA *pFPGA)
{
    m_pFpga = pFPGA;
    QDialog::open();
}

void DLG_ConfigureFPGA::on_spinBox_inputs_valueChanged(int arg1)
{
    if(m_pFpga)
    {

    }
}

void DLG_ConfigureFPGA::on_spinBox_outputs_valueChanged(int arg1)
{
    if(m_pFpga)
    {

    }
}
