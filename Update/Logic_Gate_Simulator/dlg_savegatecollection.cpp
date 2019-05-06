#include "dlg_savegatecollection.h"
#include "ui_dlg_savegatecollection.h"
#include "gatecollection.h"
#include "filelocations.h"

DLG_SaveGateCollection::DLG_SaveGateCollection(GateField* currentGateField, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DLG_SaveGateCollection),
    m_currentGateField(currentGateField)
{
    ui->setupUi(this);
}

DLG_SaveGateCollection::~DLG_SaveGateCollection()
{
    delete ui;
}

void DLG_SaveGateCollection::on_Cancel_clicked()
{
    //Close
    this->close();
}

void DLG_SaveGateCollection::on_Save_clicked()
{
    std::string name = ui->txt_name->toPlainText().toStdString();

    std::ofstream newGateCollection(c_CustomGatesLocation.toStdString() + name + ".txt");
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
        //todo tell user bad file name
    }
}