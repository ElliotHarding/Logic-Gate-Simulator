#ifndef GATENOT_H
#define GATENOT_H

#include "gate.h"

#define GateNotHeight 50
#define GateNotWidth 100

class GateNot : public Gate
{
public:
    GateNot(id in = idGenerator(), id out = idGenerator());

    virtual void UpdateOutput() override;
    virtual void SetPosition(int x, int y) override;
    virtual Gate* Clone() override;

protected:
    const int M_INPUT_OFFSET_X = 0;
    const int M_INPUT_OFFSET_Y = (GateNotHeight/2);
    Node m_input;

    const int M_OUTPUT_OFFSET_X = GateNotWidth + 5;
    const int M_OUTPUT_OFFSET_Y = (GateNotHeight/2);
    Node m_output;
};

#endif // GATENOT_H
