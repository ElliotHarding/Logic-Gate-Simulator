#ifndef DLG_TRUTHTABLETASKDESIGNER_H
#define DLG_TRUTHTABLETASKDESIGNER_H
#include "dlg_task.h"

class DLG_TruthTableTaskDesigner : public DLG_Home
{
    Q_OBJECT

public:
    explicit DLG_TruthTableTaskDesigner(int iInputs, int iOutputs);
    ~DLG_TruthTableTaskDesigner();

    std::vector<GateToggle*> m_inputGates;
    std::vector<GateReciever*> m_outputGates;
    QPushButton* m_pBtnSubmit;
    Task m_task;

protected slots:
    void onSubmitButton();
};

#endif // DLG_TRUTHTABLETASKDESIGNER_H
