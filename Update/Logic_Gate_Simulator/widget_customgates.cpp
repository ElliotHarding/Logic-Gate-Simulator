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
    UpdateList();
}

Widget_CustomGates::~Widget_CustomGates()
{
    delete ui;
}

void Widget_CustomGates::UpdateList()
{
    m_customGates.clear();
    ui->customGateListWidget->clear();

    //Find list of files in custom gate folder
    QStringList nameFilter("*.CustomGate");
    QDir directory(c_CustomGatesLocation);
    QStringList fileList = directory.entryList(nameFilter);

    //Create list of custom gates from files in custom gate folder
    //Add name of each custom gate to ui->customGateListWidget
    GateReader gReader;
    for (QString file : fileList)
    {
        std::ifstream customGateFile(c_CustomGatesLocation.toStdString() + file.toStdString());
        if(customGateFile.is_open())
        {
            GateCollection* cg;
            if(gReader.ReadGateCollection(customGateFile, cg))
            {
                m_customGates.push_back(cg);
                ui->customGateListWidget->addItem(file.left(file.length() - 11));
            }
            cg = nullptr;
        }
    }
}

void Widget_CustomGates::on_customGateListWidget_currentRowChanged(int currentRow)
{
    if(currentRow > -1 && currentRow < m_customGates.size())
    {
        //Make pointer point to copy from vector
        GateCollection* pGc = new GateCollection(*(m_customGates[currentRow]));

        //Add pointer
        m_pParent->AddGate(pGc);
    }

}

void Widget_CustomGates::on_btn_SelectionTool_clicked()
{
    m_pParent->SelectionToolClicked();
}
