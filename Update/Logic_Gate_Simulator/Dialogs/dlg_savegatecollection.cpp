#include "dlg_savegatecollection.h"
#include "ui_dlg_savegatecollection.h"
#include "gatecollection.h"
#include "filelocations.h"
#include <QDir>

DLG_SaveGateCollection::DLG_SaveGateCollection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DLG_SaveGateCollection)
{
    ui->setupUi(this);
    ui->lb_error->hide();
}

DLG_SaveGateCollection::~DLG_SaveGateCollection()
{
    delete ui;
}

void DLG_SaveGateCollection::SetCurrentGateField(GateField* currentGateField)
{
     m_currentGateField = currentGateField;
}

void DLG_SaveGateCollection::open()
{
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
        m_currentGateField->GenerateGateCollection()->SaveData(newGateCollection);
        newGateCollection.close();

        //Close
        this->close();
    }
    else
    {
        ui->lb_error->setText("Bad file name!");
        ui->lb_error->show();
    }
}
