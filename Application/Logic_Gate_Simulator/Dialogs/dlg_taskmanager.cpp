#include "dlg_taskmanager.h"
#include "ui_dlg_taskmanager.h"

DLG_TaskManager::DLG_TaskManager(std::vector<Task> tasks, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DLG_TaskManager),
    m_tasks(tasks)
{
    ui->setupUi(this);

    const int taskBtnDimension = 60;
    const int taskBtnMargin = 10;
    for (int x = 0; x < tasks.size(); x++)
    {
        QPushButton* newTaskBtn = new QPushButton(QString::number(x), this);

        if(x < 6)
            newTaskBtn->setGeometry((taskBtnMargin*x)+(taskBtnDimension*x), taskBtnMargin, taskBtnDimension, taskBtnDimension);
        else
             newTaskBtn->setGeometry((taskBtnMargin*(x-6))+(taskBtnDimension*(x-6)), taskBtnDimension + taskBtnMargin * 2, taskBtnDimension, taskBtnDimension);

        connect(newTaskBtn, &QPushButton::clicked, this, &DLG_TaskManager::OnTaskClicked);
        m_taskButtons.push_back(newTaskBtn);
    }
}

DLG_TaskManager::~DLG_TaskManager()
{
    delete ui;
    for (int x = 0; x < m_taskButtons.size(); x++)
    {
        delete m_taskButtons[x];
    }
}

void DLG_TaskManager::OnTaskCompleted()
{
    this->show();
    delete m_pCurrentTask;
    m_pCurrentTask = nullptr;
    m_taskButtons[m_iCurrentTask]->setDisabled(true);
    m_tasks[m_iCurrentTask].m_bComplete = true;
}

void DLG_TaskManager::OnTaskClicked()
{
    QObject *senderObj = sender(); // This will give Sender object
    QString senderObjName = senderObj->objectName();
    int taskNum = senderObjName.toInt();
    m_iCurrentTask = taskNum;

    m_pCurrentTask = new dlg_task(this, m_tasks[taskNum]);
    m_pCurrentTask->show();
    this->hide();
}
