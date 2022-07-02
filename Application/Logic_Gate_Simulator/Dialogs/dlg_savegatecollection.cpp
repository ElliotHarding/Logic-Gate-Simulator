#include "dlg_savegatecollection.h"
#include "ui_dlg_savegatecollection.h"
#include "dlg_home.h"
#include "gatefield.h"

DLG_SaveGateCollection::DLG_SaveGateCollection(DLG_Home *parent) :
    QDialog(parent),
    ui(new Ui::DLG_SaveGateCollection),
    m_pParent(parent),
    m_pCurrentGateCollection(nullptr),
    m_pCurrentGateField(nullptr)
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
    ui->txt_name->setText("My Gate Collection");
    QDialog::open();
}

void DLG_SaveGateCollection::open(GateField *pGateField)
{
    m_pCurrentGateField = pGateField;
    ui->lb_error->hide();
    ui->txt_name->setText(pGateField->name());
    QDialog::open();
}

void DLG_SaveGateCollection::closeEvent(QCloseEvent* e)
{
    QDialog::closeEvent(e);
    m_pCurrentGateCollection = nullptr;
    m_pCurrentGateField = nullptr;
}

void DLG_SaveGateCollection::on_Cancel_clicked()
{
    close();
}

void DLG_SaveGateCollection::on_Save_clicked()
{
    if(m_pCurrentGateCollection == nullptr && m_pCurrentGateField == nullptr)
    {
        ui->lb_error->setText("Nothing selected to save!");
        ui->lb_error->show();
        return;
    }

    if(m_pCurrentGateCollection)
    {
        if(!m_saver.saveGateCollection(m_pCurrentGateCollection, ui->txt_name->toPlainText(), m_pParent))
        {
            ui->lb_error->setText("Failed to save! Check file name.");
            ui->lb_error->show();
            return;
        }
    }

    if(m_pCurrentGateField)
    {
        if(ui->txt_name->toPlainText().isEmpty())
        {
            ui->lb_error->setText("Bad file name!");
            ui->lb_error->show();
            return;
        }

        m_pParent->setGateFieldName(m_pCurrentGateField, ui->txt_name->toPlainText());
        if(!m_saver.saveGateField(m_pCurrentGateField, m_pParent))
        {
            ui->lb_error->setText("Failed to save! Check file name.");
            ui->lb_error->show();
            return;
        }
    }

    close();
}
