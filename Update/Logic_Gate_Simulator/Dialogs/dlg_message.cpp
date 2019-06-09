#include "dlg_message.h"
#include "ui_dlg_message.h"

DLG_Message::DLG_Message(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DLG_Message)
{
    ui->setupUi(this);
}

DLG_Message::~DLG_Message()
{
    delete ui;
}

void DLG_Message::SetMessage(QString message)
{
    ui->lbl_text->setText(message);
}

void DLG_Message::on_pushButton_clicked()
{
    hide();
}
