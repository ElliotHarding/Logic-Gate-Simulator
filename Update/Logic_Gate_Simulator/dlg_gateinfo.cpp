#include "dlg_gateinfo.h"
#include "ui_dlg_gateinfo.h"
#include "AllGates.h"

DLG_GateInfo::DLG_GateInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DLG_GateInfo)
{
    ui->setupUi(this);
}

DLG_GateInfo::~DLG_GateInfo()
{
    delete ui;
}

void DLG_GateInfo::setGate(Gate *g)
{

}
