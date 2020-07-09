#ifndef DLG_CIRCUITTASKDESIGNER_H
#define DLG_CIRCUITTASKDESIGNER_H

#include <QMainWindow>
#include "widget_truthtable.h"
#include "dlg_task.h"

namespace Ui {
class DLG_CircuitTaskDesigner;
}

class DLG_CircuitTaskDesigner : public QMainWindow
{
    Q_OBJECT

public:
    explicit DLG_CircuitTaskDesigner(int inputs, int outputs, QWidget *parent = nullptr);
    ~DLG_CircuitTaskDesigner();

    Widget_TruthTable* m_pTruthTable;
    Task m_newTask;

private slots:
    void on_btn_done_clicked();

private:
    Ui::DLG_CircuitTaskDesigner *ui;
};

#endif // DLG_CIRCUITTASKDESIGNER_H
