#ifndef GATEAND_H
#define GATEAND_H

#include "gate.h"

class GateAnd : public Gate
{
public:
    GateAnd();

    virtual void UpdateOutput() override;
    virtual Node* GetClickedNode(int clickX, int clickY) override;

protected:

    virtual void DrawNodes(QPainter *painter) override;

    const int M_INPUTa_OFFSET_X = 0;
    const int M_INPUTa_OFFSET_Y = 0;
    Node m_inputA;

    const int M_INPUTb_OFFSET_X = 0;
    const int M_INPUTb_OFFSET_Y = 0;
    Node m_inputB;

    const int M_OUTPUT_OFFSET_X = 0;
    const int M_OUTPUT_OFFSET_Y = 0;
    Node m_output;
};

#endif // GATEAND_H
