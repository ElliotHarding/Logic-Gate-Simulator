#include "widget_customgates.h"
#include "ui_widget_customgates.h"
#include "dlg_home.h"
#include <QDir>
#include "gatereader.h"
#include "filelocations.h"

Widget_CustomGates::Widget_CustomGates(DLG_Home* pParent) :
    QWidget(pParent),
    ui(new Ui::Widget_CustomGates),
    m_pParent(pParent)
{
    ui->setupUi(this);

    //Find list of files in custom gate folder
    QStringList nameFilter("*.CustomGate");
    QDir directory(c_CustomGatesLocation);
    QStringList fileList = directory.entryList(nameFilter);

    //Create list of custom gates from file list
    //Also add each name of each custom gates to ui->customGateListWidget
    GateReader gReader;
    for (QString file : fileList)
    {
        std::ifstream customGateFile(file.toUtf8());
        if(customGateFile.is_open())
        {
            m_customGates.push_back(gReader.readGateCollection(customGateFile));
            QString fileName = file.mid(c_CustomGatesLocation.length(), fileName.length());
            ui->customGateListWidget->addItem(fileName);
        }
    }
}

Widget_CustomGates::~Widget_CustomGates()
{
    delete ui;
}

void Widget_CustomGates::on_customGateListWidget_currentRowChanged(int currentRow)
{
    m_pParent->AddGate(&m_customGates[currentRow]);
}
