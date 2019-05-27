#include "dlg_load.h"
#include "ui_dlg_load.h"
#include "dlg_home.h"

DLG_Load::DLG_Load(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DLG_Load)
{
    ui->setupUi(this);
}

DLG_Load::~DLG_Load()
{
    delete ui;
}

void DLG_Load::on_btnLoad_clicked()
{
    ui->progressBar->setValue(0);
    DLG_Home* home = new DLG_Home(ui->progressBar);
    home->show();
}
