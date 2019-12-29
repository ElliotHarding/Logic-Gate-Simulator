#include "dlg_viewtasks.h"
#include "ui_dlg_viewtasks.h"

dlg_viewTasks::dlg_viewTasks(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::dlg_viewTasks)
{
    ui->setupUi(this);
}

dlg_viewTasks::~dlg_viewTasks()
{
    delete ui;
}
