#include "dlg_truthtable.h"
#include "ui_dlg_truthtable.h"

DLG_TruthTable::DLG_TruthTable(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DLG_TruthTable)
{
    ui->setupUi(this);
}

DLG_TruthTable::~DLG_TruthTable()
{
    delete ui;
}

void DLG_TruthTable::open(const TruthTable& truthTable)
{
    QDialog::open();
}
