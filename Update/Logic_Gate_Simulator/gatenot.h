#ifndef GATENOT_H
#define GATENOT_H

#include "gate.h"

class GateNot : public Gate
{
public:
    GateNot();

    virtual void UpdateOutput() override;

    virtual Node *GetClickedNode(int clickX, int clickY) override;

    const int M_INPUT_OFFSET_X = 0;
    const int M_INPUT_OFFSET_Y = 0;
    Node m_input;

    const int M_OUTPUT_OFFSET_X = 0;
    const int M_OUTPUT_OFFSET_Y = 0;
    Node m_output;

protected:
    virtual void DrawNodes(QPainter *painter) override;
};

#endif // GATENOT_H
