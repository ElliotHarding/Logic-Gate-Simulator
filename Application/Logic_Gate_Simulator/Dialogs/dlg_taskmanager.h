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
    explicit DLG_TaskManager(std::vector<Task> tasks, QWidget *parent = nullptr);
    ~DLG_TaskManager();

    void OnTaskCompleted();

private:
    Ui::DLG_TaskManager *ui;
    dlg_task* m_pCurrentTask;
    int m_iCurrentTask;

    std::vector<Task> m_tasks;
    std::vector<QPushButton*> m_taskButtons;

private slots:
    void OnTaskClicked();
};

#endif // DLG_TASKMANAGER_H
