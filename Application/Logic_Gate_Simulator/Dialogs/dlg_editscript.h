#ifndef DLG_EditScript_H
#define DLG_EditScript_H

#include <QDialog>
#include <QThread>

namespace Ui {
class DLG_EditScript;
}

class DLG_Home;

class Gate;
class GateFPGA;
class GateToggle;
class GateReciever;
class GateCollection;

//////////////////////////////////////////////////////////////////////////
///Circuit
class Circuit
{
public:
    Circuit(const uint& inputs, const uint& outputs);
    ~Circuit();

    GateCollection* createGateCollection();
    void deleteMainGates();

    std::vector<Gate*> mainGates;
    std::vector<GateToggle*> inputs;
    std::vector<GateReciever*> outputs;
private:
    bool m_bDeleteGates = true; //Delete gates on destructor
};

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
    void onCircuitGenSuccess(Circuit& circuit);
    void onCircuitGenFailure(const QString& failMessage);

private:
    Ui::DLG_EditScript *ui;

    DLG_Home* m_pDlgHome;

    void setStartScript(const uint& numInputs);
    void setEndScript(const uint& numOutputs);

    GateFPGA* m_pFpga = nullptr;
};

//////////////////////////////////////////////////////////////////////////
///CircuitFromScriptThread
class CircuitFromScriptThread : public QThread
{
    Q_OBJECT
public:
    CircuitFromScriptThread();

    void setup(const uint& numInputs, uint& numOutputs, const QString& script, const int& maxSeconds, const uint& percentageRandomGate, const uint& maxGates);

    void run();

signals:
    void circuitGenSuccess(Circuit& circuit);
    void circuitGenFailure(const QString& failMessage);

private:
    uint m_numInputs;
    uint m_numOutputs;
    QString m_script;
    int m_maxSeconds;
    uint m_percentageRandomGate;
    uint m_maxGates;
};

#endif // DLG_EditScript_H
