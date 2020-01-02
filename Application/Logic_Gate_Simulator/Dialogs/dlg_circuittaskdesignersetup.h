#ifndef DLG_CIRCUITTASKDESIGNERSETUP_H
#define DLG_CIRCUITTASKDESIGNERSETUP_H

#include <QMainWindow>

namespace Ui {
class DLG_CircuitTaskDesignerSetup;
}

class DLG_CircuitTaskDesignerSetup : public QMainWindow
{
    Q_OBJECT

public:
    explicit DLG_CircuitTaskDesignerSetup(bool circuitTask, QWidget *parent = nullptr);
    ~DLG_CircuitTaskDesignerSetup();

private slots:
    void on_btn_ok_clicked();

private:
    Ui::DLG_CircuitTaskDesignerSetup *ui;
    bool m_bCircuitTask;
};

#endif // DLG_CIRCUITTASKDESIGNERSETUP_H
