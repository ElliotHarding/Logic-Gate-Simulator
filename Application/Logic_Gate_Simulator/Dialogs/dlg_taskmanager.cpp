#include "dlg_taskmanager.h"
#include "ui_dlg_taskmanager.h"
#include <math.h>
#include "filelocations.h"

DLG_TaskManager::DLG_TaskManager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DLG_TaskManager)
{
    ui->setupUi(this);
    setWindowTitle("Tasks");

    QStringList nameFilter("*.GateField");
    QDir directory(c_tasksLocation);
    QStringList fileList = directory.entryList(nameFilter);
    for (QString file : fileList)
    {
        m_tasks.push_back(c_tasksLocation.toStdString() + file.toStdString());
    }

    const int taskBtnDimension = 60;
    const int taskBtnMargin = 10;
    for (int x = 0; x < m_tasks.size(); x++)
    {
        QPushButton* newTaskBtn = new QPushButton(QString::number(x), this);
        newTaskBtn->setObjectName(QString::number(x));
        newTaskBtn->setStyleSheet(QString::fromUtf8("QPushButton{"
                                                    "border-style: solid;"
                                                    "border-color: black;"
                                                    "border-width: 2px;"
                                                    "border-radius: 10px;}"));

        if(x < 6)
            newTaskBtn->setGeometry(taskBtnMargin+(taskBtnMargin*x)+(taskBtnDimension*x), taskBtnMargin, taskBtnDimension, taskBtnDimension);
        else
             newTaskBtn->setGeometry(taskBtnMargin+(taskBtnMargin*(x-6))+(taskBtnDimension*(x-6)), taskBtnDimension + taskBtnMargin * 2, taskBtnDimension, taskBtnDimension);

        connect(newTaskBtn, &QPushButton::clicked, this, &DLG_TaskManager::OnTaskClicked);
        m_taskButtons.push_back(newTaskBtn);
        m_completedTasks.push_back(false);
    }

    const int iTasks = m_tasks.size();
    const int iCols = iTasks>6 ? 6 : iTasks;
    const int iRows = floor(iTasks/7) + 1;
    int width = (taskBtnMargin*(iCols+1)) + (taskBtnDimension*iCols);
    if (width < 3 * taskBtnDimension)
        width = 3 * taskBtnDimension;
    setGeometry(700, 500, width, (taskBtnMargin*(iRows+1)) + (taskBtnDimension*iRows));
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
    m_completedTasks[m_iCurrentTask] = true;

    QPalette pal = m_taskButtons[m_iCurrentTask]->palette();
    pal.setColor(QPalette::Button, QColor(Qt::green));
    m_taskButtons[m_iCurrentTask]->setAutoFillBackground(true);
    m_taskButtons[m_iCurrentTask]->setPalette(pal);
    m_taskButtons[m_iCurrentTask]->update();

    QPainterPath path;
    path.addRoundedRect(m_taskButtons[m_iCurrentTask]->rect(), 10, 10);
    m_taskButtons[m_iCurrentTask]->setMask(path.toFillPolygon().toPolygon());

    bool allComplete = true;
    for(int x = 0; x < m_tasks.size(); x++)
    {
        if(!m_completedTasks[x])
        {
            allComplete = false;
            break;
        }
    }

    if(allComplete)
    {
        //TODO
    }
}

void DLG_TaskManager::OnTaskClicked()
{
    //Get task number from btn that triggered function call
    QObject *senderObj = sender();
    QString senderObjName = senderObj->objectName();
    m_iCurrentTask = senderObjName.toInt();

    //Run task
    bool succeded = true;
    m_pCurrentTask = new dlg_task(this, &m_tasks[m_iCurrentTask], succeded);
    if(succeded)
    {
        m_pCurrentTask->show();
        this->hide();
    }
}
