#ifndef DLG_TASK_H
#define DLG_TASK_H

#include <QMainWindow>
#include "dlg_home.h"
#include "widget_truthtable.h"

namespace Ui {
class dlg_task;
}

struct Task
{
    int m_inputs = 2;
    int m_outputs = 2;
    bool m_bCircuitTask;
    bool m_bComplete = false;

    //holds answer, if circuit task holds run results, else holds truth table results expected
    std::vector<std::vector<bool>> results;
};

class DLG_TaskManager;

class dlg_task : public DLG_Home
{
    Q_OBJECT

public:
    explicit dlg_task(DLG_TaskManager* pTaskManager, std::string taskFileName);
    ~dlg_task();

protected:
    DLG_TaskManager* m_pTaskManager;
    Widget_TruthTable* m_pTruthTableWidget;
    QPushButton* m_pBtnSubmit;
    Task m_task;
    std::vector<GateToggle*> m_inputGates;
    std::vector<GateReciever*> m_outputGates;

    int tryStoi(std::string, int);

private slots:
    void onSubmitButtonClicked();

};

#endif // DLG_TASK_H
