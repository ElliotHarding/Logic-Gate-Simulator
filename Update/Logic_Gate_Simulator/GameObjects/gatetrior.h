#ifndef GATETRIOR_H
#define GATETRIOR_H

#include "gate.h"

#define GateTriOrHeight 50
#define GateTriOrWidth 100

class GateTriOr : public Gate
{
public:
    GateTriOr(id inA = idGenerator(), id inB = idGenerator(), id inC = idGenerator(), id out = idGenerator());

    virtual void UpdateOutput() override;
    virtual void SetPosition(int x, int y) override;

    virtual Gate* Clone() override;

protected:

    const int M_INPUTa_OFFSET_X = -5;
    const int M_INPUTa_OFFSET_Y = (GateTriOrHeight/2) - 11;
    Node m_inputA;

    const int M_INPUTb_OFFSET_X = -5;
    const int M_INPUTb_OFFSET_Y = GateTriOrHeight/2;
    Node m_inputB;

    const int M_INPUTc_OFFSET_X = -5;
    const int M_INPUTc_OFFSET_Y = GateTriOrHeight - 13;
    Node m_inputC;

    const int M_OUTPUT_OFFSET_X = GateTriOrWidth + 5;
    const int M_OUTPUT_OFFSET_Y = (GateTriOrHeight/2);
    Node m_output;
};

#endif // GATETRIOR_H
