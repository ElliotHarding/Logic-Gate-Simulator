#include "widget_customgates.h"
#include "ui_widget_customgates.h"
#include <QDir>
#include "gatereader.h"
#include "filelocations.h"
#include "dlg_home.h"
#include "dlg_message.h"

Widget_CustomGates::Widget_CustomGates(DLG_Home* pParent, bool show, QPoint loc) :
    MovingWidget(pParent, show, loc),
    ui(new Ui::Widget_CustomGates)
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
    m_currentRow = currentRow;
    createItem();
}

void Widget_CustomGates::on_btn_SelectionTool_clicked()
{
    m_pParent->SelectionToolClicked();
}

void Widget_CustomGates::on_customGateListWidget_itemClicked(QListWidgetItem *item)
{
    createItem();
}

void Widget_CustomGates::createItem()
{
    //Check correct index
    if(m_currentRow > -1 && m_currentRow < ui->customGateListWidget->count())
    {
        //Get selected file
        QString file = m_customGatesNames[m_currentRow];
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
                m_pParent->SendUserMessage("Opening a file failed!");
            }
            cg = nullptr;
        }
        else
        {
            m_pParent->SendUserMessage("Opening a file failed!");
        }

        UpdateList();
    }
}
