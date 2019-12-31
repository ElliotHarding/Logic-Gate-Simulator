#ifndef DLG_TASK_H
#define DLG_TASK_H

#include <QMainWindow>
#include "dlg_home.h"
#include "widget_doubleinputtruthtable.h"
#include "widget_tripleinputtruthtable.h"

namespace Ui {
class dlg_task;
}

struct Task
{
    bool m_bDoubleTruthTable;
    bool m_bCircuitTask;
    bool results[]; //holds answer, if circuit task holds run results, else holds truth table results expected

    bool Verify(std::vector<bool> answer);
};

class dlg_task : public DLG_Home
{
    Q_OBJECT

public:
    explicit dlg_task(Task task, QWidget *parent = nullptr);
    ~dlg_task();

protected:
    TruthTableWidgetBase* m_pTruthTableWidget;
    QPushButton* m_pBtnSubmit;
    Task m_task;

private slots:
    void onSubmitButtonClicked();

};

#endif // DLG_TASK_H
