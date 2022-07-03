#ifndef DLG_EditScript_H
#define DLG_EditScript_H

#include <QDialog>

namespace Ui {
class DLG_EditScript;
}
class GateFPGA;

struct TruthTable
{
    std::vector<std::vector<bool>> inValues;
    std::vector<std::vector<bool>> outValues;
};

class DLG_EditScript : public QDialog
{
    Q_OBJECT

public:
    explicit DLG_EditScript(QWidget *parent = nullptr);
    ~DLG_EditScript();

    void open(GateFPGA* pFPGA);

private slots:
    void on_spinBox_inputs_valueChanged(int numInputs);
    void on_spinBox_outputs_valueChanged(int numOutputs);

    void on_btn_setScript_clicked();
    void on_btn_genCircuit_clicked();

private:
    Ui::DLG_EditScript *ui;

    void setStartScript(const uint& numInputs);
    void setEndScript(const uint& numOutputs);

    GateFPGA* m_pFpga = nullptr;
};

#endif // DLG_EditScript_H
