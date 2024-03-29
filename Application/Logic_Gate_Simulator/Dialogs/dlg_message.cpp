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

void DLG_Message::showMessage(const QString& message)
{
    ui->lbl_text->setText(message);
    show();
}

void DLG_Message::on_btn_ok_clicked()
{
    hide();
}
