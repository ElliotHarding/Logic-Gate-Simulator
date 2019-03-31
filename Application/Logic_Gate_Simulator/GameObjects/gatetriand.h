#ifndef GATETRIAND_H
#define GATETRIAND_H

#include "gate.h"

#define GateTriAndHeight 50
#define GateTriAndWidth 100

class GateTriAnd : public Gate
{
public:
    GateTriAnd(id inA = idGenerator(), id inB = idGenerator(), id inC = idGenerator(), id out = idGenerator());

    virtual void UpdateOutput() override;
    virtual void SetPosition(int x, int y) override;

    virtual Gate* Clone() override;

protected:

    const int M_INPUTa_OFFSET_X = -5;
    const int M_INPUTa_OFFSET_Y = (GateTriAndHeight/2) - 11;
    Node m_inputA;

    const int M_INPUTb_OFFSET_X = -5;
    const int M_INPUTb_OFFSET_Y = GateTriAndHeight/2;
    Node m_inputB;

    const int M_INPUTc_OFFSET_X = -5;
    const int M_INPUTc_OFFSET_Y = GateTriAndHeight - 13;
    Node m_inputC;

    const int M_OUTPUT_OFFSET_X = GateTriAndWidth + 5;
    const int M_OUTPUT_OFFSET_Y = (GateTriAndHeight/2);
    Node m_output;
};

#endif // GATETRIAND_H
