#ifndef DLG_CONFIGUREFPGA_H
#define DLG_CONFIGUREFPGA_H

#include <QDialog>

namespace Ui {
class DLG_ConfigureFPGA;
}
class GateFPGA;

class DLG_ConfigureFPGA : public QDialog
{
    Q_OBJECT

public:
    explicit DLG_ConfigureFPGA(QWidget *parent = nullptr);
    ~DLG_ConfigureFPGA();

    void open(GateFPGA* pFPGA);

private slots:
    void on_spinBox_inputs_valueChanged(int numInputs);
    void on_spinBox_outputs_valueChanged(int numOutputs);

    void on_btn_setScript_clicked();

private:
    Ui::DLG_ConfigureFPGA *ui;

    GateFPGA* m_pFpga = nullptr;
};

#endif // DLG_CONFIGUREFPGA_H
