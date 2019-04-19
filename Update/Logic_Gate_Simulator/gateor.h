#ifndef GATEOR_H
#define GATEOR_H

#include "gate.h"

#define GateOrWidth 100
#define GateOrHeight 50

class GateOr : public Gate
{
public:
    GateOr();
    ~GateOr() override;

    virtual void UpdateOutput() override;

    virtual Node *GetClickedNode(int clickX, int clickY) override;

protected:
    virtual void DrawNodes(QPainter *painter) override;

    const int M_INPUTa_OFFSET_X = -5;
    const int M_INPUTa_OFFSET_Y = (GateOrHeight/2) - 5;
    Node m_inputA;

    const int M_INPUTb_OFFSET_X = -5;
    const int M_INPUTb_OFFSET_Y = GateOrHeight - 7;
    Node m_inputB;

    const int M_OUTPUT_OFFSET_X = GateOrWidth + 15;
    const int M_OUTPUT_OFFSET_Y = (GateOrHeight/2) + 7;
    Node m_output;
};

#endif // GATEOR_H
