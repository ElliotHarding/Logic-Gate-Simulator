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
    this->close();
}

void DLG_SaveGateCollection::on_Save_clicked()
{
    std::ofstream newGateCollection(m_fileLocation);
    if(newGateCollection.is_open())
    {
        m_currentGateField->GenerateGateCollection()->SaveData(newGateCollection);
        newGateCollection.close();
    }

}
