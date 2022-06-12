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
    ui->customGateListWidget->clear();
    for (const QString& file : m_customGateReader.getCustomGateNames())
    {
        ui->customGateListWidget->addItem(file);
    }
}

void Widget_CustomGates::on_customGateListWidget_currentRowChanged(int currentRow)
{
    m_currentRow = currentRow;
}

void Widget_CustomGates::on_customGateListWidget_itemClicked(QListWidgetItem* item)
{
    if (m_currentRow > -1 && m_currentRow <= ui->customGateListWidget->count())
    {
        if (m_bDeleting)
        {
            DeleteItem(m_currentRow);
        }
        else
        {
            CreateItem(item->text());
        }
    }
}

void Widget_CustomGates::on_btn_SelectionTool_clicked()
{
    m_pParent->SelectionToolClicked();
}

void Widget_CustomGates::CreateItem(const QString& name)
{
    GateCollection* spawnedGateCollection = m_customGateReader.spawnCustomGate(name);
    if(spawnedGateCollection != nullptr)
    {
        m_pParent->AddGate(spawnedGateCollection);
    }
    else
    {
        m_pParent->SendUserMessage("Opening a file failed!");
    }
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

