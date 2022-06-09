#include "dlg_taskmanager.h"
#include "ui_dlg_taskmanager.h"
#include <math.h>
#include "filelocations.h"
#include "QDesktopServices"

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

        QStringList fileNumberAndIsComplete = file.split(".");
        m_completedTasks.push_back((fileNumberAndIsComplete.at(1) == "C"));
    }

    const int menuButtonSpace = 30;
    const int taskBtnDimension = 60;
    const int taskBtnMargin = 10;
    for (int x = 0; x < m_tasks.size(); x++)
    {
        QPushButton* newTaskBtn = new QPushButton(QString::number(x), this);
        newTaskBtn->setObjectName(QString::number(x));

        if(x < 6)
            newTaskBtn->setGeometry(taskBtnMargin+(taskBtnMargin*x)+(taskBtnDimension*x), taskBtnMargin + menuButtonSpace, taskBtnDimension, taskBtnDimension);
        else
             newTaskBtn->setGeometry(taskBtnMargin+(taskBtnMargin*(x-6))+(taskBtnDimension*(x-6)), taskBtnDimension + menuButtonSpace + taskBtnMargin * 2, taskBtnDimension, taskBtnDimension);

        MarkTaskButtonComplete(newTaskBtn, (m_completedTasks[x] == true));

        connect(newTaskBtn, &QPushButton::clicked, this, &DLG_TaskManager::OnTaskClicked);
        m_taskButtons.push_back(newTaskBtn);
    }

    const int iTasks = m_tasks.size();
    const int iCols = iTasks>6 ? 6 : iTasks;
    const int iRows = floor(iTasks/7) + 1;
    const int height = (taskBtnMargin*(iRows+1)) + (taskBtnDimension*iRows) + menuButtonSpace;
    int width = (taskBtnMargin*(iCols+1)) + (taskBtnDimension*iCols);
    if (width < 4 * taskBtnDimension)
        width = 4 * taskBtnDimension;

    setFixedSize(width, height);

    QPushButton* resetTasksButton = new QPushButton("Reset Completed", this);
    resetTasksButton->setGeometry(10, 10, 100, 25);
    connect(resetTasksButton, &QPushButton::clicked, this, &DLG_TaskManager::OnResetCompleted);

    QPushButton* viewTasksButton = new QPushButton("View Tasks", this);
    viewTasksButton->setGeometry(115, 10, 100, 25);
    connect(viewTasksButton, &QPushButton::clicked, this, &DLG_TaskManager::OnViewTasks);
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

    SetTaskCompletionState(QString::fromStdString(m_tasks[m_iCurrentTask]), true);
    MarkTaskButtonComplete(m_taskButtons[m_iCurrentTask], true);

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

void DLG_TaskManager::MarkTaskButtonComplete(QPushButton*& pb, bool complete)
{
    if(!complete)
    {
        pb->setStyleSheet(QString::fromUtf8("QPushButton{"
                                                    "border-style: solid;"
                                                    "border-color: black;"
                                                    "border-width: 2px;"
                                                    "border-radius: 10px;}"));
    }
    else
    {
        QPainterPath path;
        path.addRoundedRect(pb->rect(), 10, 10);
        pb->setMask(path.toFillPolygon().toPolygon());

        pb->setStyleSheet(QString::fromUtf8("QPushButton{"
                                                    "border-style: solid;"
                                                    "border-color: black;"
                                                    "border-width: 2px;"
                                                    "border-radius: 10px;"
                                                    "background-color: green}"));
    }
}

void DLG_TaskManager::SetTaskCompletionState(QString filename, bool complete)
{
    QStringList fileNumberAndIsComplete = filename.split(".");
    const std::string oldFileName = filename.toStdString().c_str();
    const std::string newFileName = fileNumberAndIsComplete[0].toStdString() + (complete ? ".C" : ".U") + ".GateField";
    std::rename(oldFileName.c_str(), newFileName.c_str());
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

void DLG_TaskManager::OnResetCompleted()
{
    for(int i = 0; i < m_tasks.size(); i++)
    {
        SetTaskCompletionState(QString::fromStdString(m_tasks[i]), false);
        MarkTaskButtonComplete(m_taskButtons[i], false);
    }
}

void DLG_TaskManager::OnViewTasks()
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(c_tasksLocation));
}
