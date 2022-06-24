#include "widget_customgates.h"
#include "ui_widget_customgates.h"
#include "dlg_home.h"
#include "dlg_message.h"
#include "GameObjects/gatecollection.h"

namespace Settings
{
QColor ActiveDeleteButtonBackColor = Qt::lightGray;
}

Widget_CustomGates::Widget_CustomGates(DLG_Home* pParent, bool show, QPoint loc) :
    MovingWidget(pParent, show, loc),
    ui(new Ui::Widget_CustomGates),
    m_bDeleting(false)
{
    ui->setupUi(this);
    UpdateList();

    m_palActive.setColor(QPalette::Background, Settings::ActiveDeleteButtonBackColor);
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

void Widget_CustomGates::on_customGateListWidget_itemClicked(QListWidgetItem* item)
{
    if (m_bDeleting)
    {
        DeleteItem(item);
    }
    else
    {
        CreateItem(item->text());
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

void Widget_CustomGates::DeleteItem(QListWidgetItem* item)
{
    if(m_customGateReader.deleteCustomGate(item->text()))
    {
        ui->customGateListWidget->removeItemWidget(item);
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

