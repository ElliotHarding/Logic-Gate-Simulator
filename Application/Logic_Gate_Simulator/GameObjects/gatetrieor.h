#ifndef GATETRIEOR_H
#define GATETRIEOR_H

#include "gate.h"

#define GateTriEorHeight 50
#define GateTriEorWidth 100

class GateTriEor : public Gate
{
public:
    GateTriEor(id inA = idGenerator(), id inB = idGenerator(), id inC = idGenerator(), id out = idGenerator());

    virtual void UpdateOutput() override;
    virtual void SetPosition(int x, int y) override;

    virtual Gate* Clone() override;

protected:

    const int M_INPUTa_OFFSET_X = -5;
    const int M_INPUTa_OFFSET_Y = (GateTriEorHeight/2) - 11;
    Node m_inputA;

    const int M_INPUTb_OFFSET_X = -5;
    const int M_INPUTb_OFFSET_Y = GateTriEorHeight/2;
    Node m_inputB;

    const int M_INPUTc_OFFSET_X = -5;
    const int M_INPUTc_OFFSET_Y = GateTriEorHeight - 13;
    Node m_inputC;

    const int M_OUTPUT_OFFSET_X = GateTriEorWidth + 5;
    const int M_OUTPUT_OFFSET_Y = (GateTriEorHeight/2);
    Node m_output;
};

#endif // GATETRIEOR_H
