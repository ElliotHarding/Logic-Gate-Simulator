#ifndef DLG_TASK_H
#define DLG_TASK_H

#include <QMainWindow>
#include "dlg_home.h"

namespace Ui {
class dlg_task;
}

class dlg_task : public DLG_Home
{
    Q_OBJECT

public:
    explicit dlg_task(QWidget *parent = nullptr);
    ~dlg_task();

protected:


};

#endif // DLG_TASK_H
