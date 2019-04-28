#include "dlg_savegatecollection.h"
#include "ui_dlg_savegatecollection.h"
#include "gatecollection.h"

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
    //Dummy call to GenerateGateCollection to reset the selector tool in m_currentGateField
    m_currentGateField->GenerateGateCollection();

    //Close
    this->close();
}

void DLG_SaveGateCollection::on_Save_clicked()
{
    std::string name = ui->txt_name->toPlainText().toStdString();

    std::ofstream newGateCollection(name + ".txt");
    if(newGateCollection.is_open())
    {
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
