#include "dlg_conversionconfig.h"
#include "ui_dlg_conversionconfig.h"
#include "customsettings.h"

#include <QMap>

namespace Settings
{
const QMap<QString, ConversionAlgorithm> ConversionAlgorithmNames = {
    {"No optimization", NoOptimization},
    {"Quine-McCluskey", QuineMcCluskey},
    {"Random", Random}
};
}

DLG_ConversionConfig::DLG_ConversionConfig(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DLG_ConversionConfig)
{
    ui->setupUi(this);
    ui->comboBox_algorithm->clear();
    for(QString algorithmName : Settings::ConversionAlgorithmNames.keys())
    {
        ui->comboBox_algorithm->addItem(algorithmName);
    }
    ui->comboBox_algorithm->setCurrentText(CustomSettings::readSetting("ConversionAlgorithm", "Quine-McCluskey"));
}

DLG_ConversionConfig::~DLG_ConversionConfig()
{
    delete ui;
}

ConversionAlgorithm DLG_ConversionConfig::getAlgorithm() const
{
    if(Settings::ConversionAlgorithmNames.find(ui->comboBox_algorithm->currentText()) != Settings::ConversionAlgorithmNames.end())
    {
        return Settings::ConversionAlgorithmNames[ui->comboBox_algorithm->currentText()];
    }
    return NoAlgorithm;
}

CircuitOptions DLG_ConversionConfig::getCircuitGenOptions() const
{
    CircuitOptions options(ui->cb_inverseGates->isChecked(), ui->cb_nandOnly->isChecked(), ui->cb_largeInputGates->isChecked(), ui->spinBox_maxGenTime->value(), getAlgorithm());
    return options;
}
