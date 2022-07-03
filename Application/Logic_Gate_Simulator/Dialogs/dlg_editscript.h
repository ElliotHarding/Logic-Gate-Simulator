#ifndef DLG_EditScript_H
#define DLG_EditScript_H

#include <QDialog>

namespace Ui {
class DLG_EditScript;
}
class GateFPGA;
class DLG_Home;
class Gate;
class GateToggle;
class GateReciever;

struct TruthTable
{
    std::vector<std::vector<bool>> inValues;
    std::vector<std::vector<bool>> outValues;
    uint size;
};

class Circuit
{
public:
    Circuit(const uint& inputs, const uint& outputs);

    //Not done in destructor cuz we might want to use em elsewhere
    void deleteAllGates();
    void deleteMainCircuit();

    std::vector<Gate*> mainGates;
    std::vector<GateToggle*> inputs;
    std::vector<GateReciever*> outputs;
};

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

private:
    Ui::DLG_EditScript *ui;

    DLG_Home* m_pDlgHome;

    void setStartScript(const uint& numInputs);
    void setEndScript(const uint& numOutputs);

    void onCircuitGenSucess(const Circuit& circuit);

    GateFPGA* m_pFpga = nullptr;
};

#endif // DLG_EditScript_H