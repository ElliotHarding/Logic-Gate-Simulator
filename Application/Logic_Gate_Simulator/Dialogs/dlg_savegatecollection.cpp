#include "dlg_savegatecollection.h"
#include "ui_dlg_savegatecollection.h"
#include "gatecollection.h"
#include "filelocations.h"
#include <QDir>
#include "dlg_home.h"

DLG_SaveGateCollection::DLG_SaveGateCollection(DLG_Home *parent) :
    QDialog(parent),
    m_pParent(parent),
    ui(new Ui::DLG_SaveGateCollection)
{
    ui->setupUi(this);
    ui->lb_error->hide();
}

DLG_SaveGateCollection::~DLG_SaveGateCollection()
{
    m_pParent = nullptr;
    delete ui;
}

void DLG_SaveGateCollection::open(GateField* currentGateField)
{
    m_currentGateField = currentGateField;
    ui->lb_error->hide();
    QDialog::open();
}

void DLG_SaveGateCollection::on_Cancel_clicked()
{
    //Close
    this->close();
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
        m_currentGateField->SaveGateCollection(newGateCollection);
        newGateCollection.close();

        m_pParent->UpdateCustomGateListWidget();

        //Close
        this->close();
    }
    else
    {
        ui->lb_error->setText("Bad file name!");
        ui->lb_error->show();
    }
}
