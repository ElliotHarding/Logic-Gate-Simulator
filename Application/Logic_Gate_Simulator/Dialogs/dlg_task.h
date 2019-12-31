#ifndef DLG_TASK_H
#define DLG_TASK_H

#include <QMainWindow>
#include "dlg_home.h"
#include "widget_doubleinputtruthtable.h"
#include "widget_tripleinputtruthtable.h"

namespace Ui {
class dlg_task;
}

class dlg_task : public DLG_Home
{
    Q_OBJECT

public:
    explicit dlg_task(bool doubleTruthTable, bool taskToCreateCircuit, bool results[], QWidget *parent = nullptr);
    ~dlg_task();

protected:
    TruthTableWidgetBase* m_pTruthTableWidget;
    QPushButton* m_pBtnSubmit;

};

#endif // DLG_TASK_H
