#include "dlg_savegatecollection.h"
#include "ui_dlg_savegatecollection.h"
#include "dlg_home.h"

DLG_SaveGateCollection::DLG_SaveGateCollection(DLG_Home *parent) :
    QDialog(parent),
    ui(new Ui::DLG_SaveGateCollection),
    m_pParent(parent)
{
    ui->setupUi(this);
    ui->lb_error->hide();
}

DLG_SaveGateCollection::~DLG_SaveGateCollection()
{
    delete ui;
}

void DLG_SaveGateCollection::open(GateCollection* pGateCollection)
{
    m_pCurrentGateCollection = pGateCollection;
    ui->lb_error->hide();
    QDialog::open();
}

void DLG_SaveGateCollection::on_Cancel_clicked()
{
    close();
}

void DLG_SaveGateCollection::on_Save_clicked()
{
    std::string name = ui->txt_name->toPlainText().toStdString();

    if(m_pCurrentGateCollection == nullptr)
    {
        ui->lb_error->setText("No gate collection selected!");
        ui->lb_error->show();
        return;
    }

    if(!m_saver.saveGateCollection(m_pCurrentGateCollection, name, m_pParent))
    {
        ui->lb_error->setText("Bad file name!");
        ui->lb_error->show();
    }

    close();
}
