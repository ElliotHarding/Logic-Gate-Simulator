#ifndef GATEAND_H
#define GATEAND_H

#include "gate.h"

#define GateAndHeight 50
#define GateAndWidth 100

class GateAnd : public Gate
{
public:
     GateAnd(id inA = idGenerator(), id inB = idGenerator(), id out = idGenerator());
    ~GateAnd() override;

    virtual void UpdateOutput() override;
    virtual void UpdateGraphics(QPainter* painter) override;
    virtual void SetPosition(int x, int y) override;
    virtual Node* GetClickedNode(int clickX, int clickY) override;
    virtual void SaveData(std::ofstream& storage) override;
    virtual Node* FindNodeWithId(id _id) override;

protected:

    const int M_INPUTa_OFFSET_X = -5;
    const int M_INPUTa_OFFSET_Y = (GateAndHeight/2) - 12;
    Node m_inputA;

    const int M_INPUTb_OFFSET_X = -5;
    const int M_INPUTb_OFFSET_Y = GateAndHeight - 12;
    Node m_inputB;

    const int M_OUTPUT_OFFSET_X = GateAndWidth + 15;
    const int M_OUTPUT_OFFSET_Y = (GateAndHeight/2);
    Node m_output;
};

#endif // GATEAND_H
