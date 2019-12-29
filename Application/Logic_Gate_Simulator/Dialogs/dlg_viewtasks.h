#ifndef DLG_VIEWTASKS_H
#define DLG_VIEWTASKS_H

#include <QMainWindow>

namespace Ui {
class dlg_viewTasks;
}

class dlg_viewTasks : public QMainWindow
{
    Q_OBJECT

public:
    explicit dlg_viewTasks(QWidget *parent = nullptr);
    ~dlg_viewTasks();

private:
    Ui::dlg_viewTasks *ui;
};

#endif // DLG_VIEWTASKS_H
