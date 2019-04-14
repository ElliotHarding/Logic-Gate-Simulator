#ifndef GATEAND_H
#define GATEAND_H

#include "gate.h"

#define GateAndHeight 50
#define GateAndWidth 100

class GateAnd : public Gate
{
public:
    GateAnd();

    virtual void UpdateOutput() override;
    virtual Node* GetClickedNode(int clickX, int clickY) override;

protected:

    virtual void DrawNodes(QPainter *painter) override;

    const int M_INPUTa_OFFSET_X = -10;
    const int M_INPUTa_OFFSET_Y = GateAndHeight/2 + 10;
    Node m_inputA;

    const int M_INPUTb_OFFSET_X = -10;
    const int M_INPUTb_OFFSET_Y = GateAndHeight/2 - 10;
    Node m_inputB;

    const int M_OUTPUT_OFFSET_X = GateAndWidth + 10;
    const int M_OUTPUT_OFFSET_Y = GateAndHeight/2;
    Node m_output;
};

#endif // GATEAND_H
