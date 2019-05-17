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
    m_customGatesNames.clear();
    ui->customGateListWidget->clear();

    //Find list of files in custom gate folder
    QStringList nameFilter("*.CustomGate");
    QDir directory(c_CustomGatesLocation);
    QStringList fileList = directory.entryList(nameFilter);

    for (QString file : fileList)
    {
        ui->customGateListWidget->addItem(file.left(file.length() - 11));
        m_customGatesNames.push_back(file);
    }
}

void Widget_CustomGates::on_customGateListWidget_currentRowChanged(int currentRow)
{
    //Check correct index
    if(currentRow > -1 && currentRow < ui->customGateListWidget->count())
    {

        //Get selected file
        QString file = m_customGatesNames[currentRow];
        std::ifstream customGateFile(c_CustomGatesLocation.toStdString() + file.toStdString());

        //Read into pointer and send to m_pParent
        if(customGateFile.is_open())
        {
            GateCollection* cg;
            static GateReader gReader;
            if(gReader.ReadGateCollection(customGateFile, cg))
            {
                //Add pointer
                m_pParent->AddGate(cg);
            }
            else
            {
                //todo
            }
            cg = nullptr;
        }
    }
}

void Widget_CustomGates::on_btn_SelectionTool_clicked()
{
    m_pParent->SelectionToolClicked();
}
