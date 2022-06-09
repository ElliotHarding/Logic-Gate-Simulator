#ifndef GATEEOR_H
#define GATEEOR_H

#include "gate.h"

#define GateEorWidth 100
#define GateEorHeight 50

class GateEor : public Gate
{
public:
    GateEor(id inA = idGenerator(), id inB = idGenerator(), id out = idGenerator());
    GateEor(bool notEorGate, GateType type = GATE_EOR, const char* iconLocation = std::string(":/Resources/Gates/gate-eor.png").c_str(),
            id inA = idGenerator(), id inB = idGenerator(), id out = idGenerator());

    virtual void UpdateOutput() override;
    virtual void SetPosition(int x, int y) override;
    virtual Gate* Clone() override;

protected:

    const int M_INPUTa_OFFSET_X = -5;
    const int M_INPUTa_OFFSET_Y = (GateEorHeight/2) - 12;
    Node m_inputA;

    const int M_INPUTb_OFFSET_X = -5;
    const int M_INPUTb_OFFSET_Y = GateEorHeight - 12;
    Node m_inputB;

    const int M_OUTPUT_OFFSET_X = GateEorWidth + 5;
    const int M_OUTPUT_OFFSET_Y = (GateEorHeight/2);
    Node m_output;
};

#endif // GATEEOR_H
