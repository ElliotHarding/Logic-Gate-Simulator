#include "dlg_taskmanager.h"
#include "ui_dlg_taskmanager.h"

DLG_TaskManager::DLG_TaskManager(std::vector<Task> tasks, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DLG_TaskManager),
    m_tasks(tasks)
{
    ui->setupUi(this);

    //test code
    m_pCurrentTask = new dlg_task(this, tasks[0], this);
    m_pCurrentTask->show();
    this->hide();
}

DLG_TaskManager::~DLG_TaskManager()
{
    delete ui;
}

void DLG_TaskManager::OnTaskCompleted()
{
    this->show();
    delete m_pCurrentTask;
    m_pCurrentTask = nullptr;
}
