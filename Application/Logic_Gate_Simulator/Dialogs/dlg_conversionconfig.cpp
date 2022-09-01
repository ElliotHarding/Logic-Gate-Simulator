#include "dlg_conversionconfig.h"
#include "ui_dlg_conversionconfig.h"

DLG_ConversionConfig::DLG_ConversionConfig(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DLG_ConversionConfig)
{
    ui->setupUi(this);
}

DLG_ConversionConfig::~DLG_ConversionConfig()
{
    delete ui;
}
