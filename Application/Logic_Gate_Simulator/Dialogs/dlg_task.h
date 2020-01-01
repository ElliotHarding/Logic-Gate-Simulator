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
    std::vector<std::vector<bool>> results;//holds answer, if circuit task holds run results, else holds truth table results expected
};

class dlg_task : public DLG_Home
{
    Q_OBJECT

public:
    explicit dlg_task(Task task, QWidget *parent = nullptr);
    ~dlg_task();

protected:
    Widget_TruthTable* m_pTruthTableWidget;
    QPushButton* m_pBtnSubmit;
    Task m_task;

private slots:
    void onSubmitButtonClicked();

};

#endif // DLG_TASK_H
