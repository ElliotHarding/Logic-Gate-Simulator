#ifndef GATENOT_H
#define GATENOT_H

#include "gate.h"

#define GateNotHeight 50
#define GateNotWidth 100

class GateNot : public Gate
{
public:
    GateNot(id in = idGenerator(), id out = idGenerator());
    ~GateNot() override;

    virtual void UpdateOutput() override;
    virtual void SetPosition(int x, int y) override;

protected:
    const int M_INPUT_OFFSET_X = 0;
    const int M_INPUT_OFFSET_Y = (GateNotHeight/2);
    Node m_input;

    const int M_OUTPUT_OFFSET_X = GateNotWidth + 15;
    const int M_OUTPUT_OFFSET_Y = (GateNotHeight/2);
    Node m_output;
};

#endif // GATENOT_H
