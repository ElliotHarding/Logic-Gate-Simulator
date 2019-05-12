#ifndef GATEOR_H
#define GATEOR_H

#include "gate.h"

#define GateOrWidth 100
#define GateOrHeight 50

class GateOr : public Gate
{
public:
    GateOr(id inA = idGenerator(), id inB = idGenerator(), id out = idGenerator());
    ~GateOr() override;

    virtual void UpdateOutput() override;
    virtual void SetPosition(int x, int y) override;
    virtual void UpdateGraphics(QPainter* painter) override;
    virtual Node *GetClickedNode(int clickX, int clickY) override;
    virtual void SaveData(std::ofstream& storage) override;
    virtual Node* FindNodeWithId(id _id) override;

protected:

    const int M_INPUTa_OFFSET_X = -5;
    const int M_INPUTa_OFFSET_Y = (GateOrHeight/2) - 12;
    Node m_inputA;

    const int M_INPUTb_OFFSET_X = -5;
    const int M_INPUTb_OFFSET_Y = GateOrHeight - 12;
    Node m_inputB;

    const int M_OUTPUT_OFFSET_X = GateOrWidth + 15;
    const int M_OUTPUT_OFFSET_Y = (GateOrHeight/2);
    Node m_output;
};

#endif // GATEOR_H
