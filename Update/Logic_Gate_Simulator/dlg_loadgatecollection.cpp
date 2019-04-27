#include "dlg_loadgatecollection.h"
#include "ui_dlg_loadgatecollection.h"

DLG_LoadGateCollection::DLG_LoadGateCollection(GateField* currentGateField, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DLG_LoadGateCollection),
    m_currentGateField(currentGateField)
{
    ui->setupUi(this);
}

DLG_LoadGateCollection::~DLG_LoadGateCollection()
{
    delete ui;
}

void DLG_LoadGateCollection::on_btn_ok_clicked()
{
    if(m_loadedGateCollection)
    {
        m_currentGateField->addGameObject(m_loadedGateCollection);
        this->close();
    }

    //todo - currently nothing
}

void DLG_LoadGateCollection::on_btn_cancel_clicked()
{
    this->close();
}
