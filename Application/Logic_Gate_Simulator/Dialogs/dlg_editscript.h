#ifndef DLG_EditScript_H
#define DLG_EditScript_H

#include "circuit.h"

#include <QDialog>

namespace Ui {
class DLG_EditScript;
}

class DLG_Home;

class Gate;
class GateFPGA;
class GateToggle;
class GateReciever;
class GateCollection;
class CircuitFromScriptThread;

//////////////////////////////////////////////////////////////////////////
///DLG_EditScript
class DLG_EditScript : public QDialog
{
    Q_OBJECT

public:
    explicit DLG_EditScript(DLG_Home* pParent);
    ~DLG_EditScript();

    void open(GateFPGA* pFPGA);

private slots:
    void on_spinBox_inputs_valueChanged(int numInputs);
    void on_spinBox_outputs_valueChanged(int numOutputs);

    void on_btn_setScript_clicked();
    void on_btn_genCircuit_clicked();
    void on_btn_genTuthTable_clicked();

private slots:
    void onCircuitGenSuccess(Circuit circuit);
    void onCircuitGenFailure(const QString& failMessage);

private:
    Ui::DLG_EditScript *ui;

    DLG_Home* m_pDlgHome;

    void setStartScript(const uint& numInputs);
    void setEndScript(const uint& numOutputs);

    GateFPGA* m_pFpga = nullptr;

    CircuitFromScriptThread* m_pCircuitFromScriptThread;
};

#endif // DLG_EditScript_H
