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

    m_palActive.setColor(QPalette::Background, Qt::lightGray);
    m_palInActive = ui->btn_Delete->palette();
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
    QDir directory(CustomGatesLocation);
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
}

void Widget_CustomGates::on_customGateListWidget_itemClicked(QListWidgetItem *item)
{
    if (m_currentRow > -1 && m_currentRow <= ui->customGateListWidget->count())
    {
        if (m_bDeleting)
        {
            DeleteItem(m_currentRow);
        }
        else
        {
            CreateItem(m_currentRow);
        }
    }
}

void Widget_CustomGates::on_btn_SelectionTool_clicked()
{
    m_pParent->SelectionToolClicked();
}

void Widget_CustomGates::CreateItem(int currentRow)
{
    //Get selected file
    QString file = m_customGatesNames[currentRow];
    std::ifstream customGateFile(CustomGatesLocation.toStdString() + file.toStdString());

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

void Widget_CustomGates::DeleteItem(int index)
{
    //Get selected file
    QString file = m_customGatesNames[index];

    //Try delete file
    std::string fileName = CustomGatesLocation.toStdString() + m_customGatesNames[index].toStdString();
    if(std::remove(fileName.c_str()) == 0)
    {
        //Remove from list
        m_customGatesNames.erase (m_customGatesNames.begin()+index);

        //Remove from ui list
        ui->customGateListWidget->removeItemWidget(ui->customGateListWidget->takeItem(index));
    }
    else
    {
        m_pParent->SendUserMessage("Deleting gate collection failed!");
    }
}

void Widget_CustomGates::on_btn_Delete_clicked()
{
    m_bDeleting = !m_bDeleting;

    ui->btn_Delete->setPalette(m_bDeleting ? m_palActive : m_palInActive);
    ui->btn_Delete->setAutoFillBackground(m_bDeleting);
}

void Widget_CustomGates::on_btn_Create_clicked()
{
    m_bDeleting = false;
}

