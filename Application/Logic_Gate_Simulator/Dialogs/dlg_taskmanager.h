#ifndef DLG_TASKMANAGER_H
#define DLG_TASKMANAGER_H

#include <QMainWindow>
#include "dlg_task.h"

namespace Ui {
class DLG_TaskManager;
}

class DLG_TaskManager : public QMainWindow
{
    Q_OBJECT

public:
    explicit DLG_TaskManager(QWidget *parent = nullptr);
    ~DLG_TaskManager();

    void OnTaskCompleted();

private:
    Ui::DLG_TaskManager *ui;
    dlg_task* m_pCurrentTask;
    int m_iCurrentTask;

    std::vector<bool> m_completedTasks;
    std::vector<std::string> m_tasks;
    std::vector<QPushButton*> m_taskButtons;

    void MarkTaskButtonComplete(QPushButton*&, bool complete);
    void SetTaskCompletionState(QString filename, bool complete);

private slots:
    void OnTaskClicked();
    void OnResetCompleted();
    void OnViewTasks();
};

#endif // DLG_TASKMANAGER_H
