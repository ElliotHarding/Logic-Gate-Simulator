#include "dlg_savegatecollection.h"
#include "ui_dlg_savegatecollection.h"
#include "gatecollection.h"
#include "filelocations.h"
#include <QDir>
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

void DLG_SaveGateCollection::open(GateField* pCurrentGateField)
{
    m_pCurrentGateField = pCurrentGateField;
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

    if(!QDir(c_CustomGatesLocation).exists())
        QDir().mkdir(c_CustomGatesLocation);

    std::ofstream newGateCollection(c_CustomGatesLocation.toStdString() + name + ".CustomGate");
    if(newGateCollection.is_open())
    {
        //Generate from currentGateField & then save to newGateCollection file
        m_pCurrentGateField->SaveGateCollection(newGateCollection);
        newGateCollection.close();

        m_pParent->UpdateCustomGateListWidget();

        close();
    }
    else
    {
        ui->lb_error->setText("Bad file name!");
        ui->lb_error->show();
    }
}
