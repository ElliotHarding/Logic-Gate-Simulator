#ifndef GATENUMBEROUTPUT_H
#define GATENUMBEROUTPUT_H

#include "gate.h"

#define GateNumberOutputHeight 50
#define GateNumberOutputWidth 100

class GateNumberOutput : public Gate
{
public:
    GateNumberOutput(id inA = idGenerator(), id inB = idGenerator(), id inC = idGenerator(), id inD = idGenerator());

    virtual void UpdateOutput() override;
    virtual void SetPosition(int x, int y) override;
    virtual void UpdateGraphics(QPainter* painter) override;

    virtual Gate* Clone() override;

protected:

    QFont m_font;
    QString m_outputText;

#define HeightStep (GateNumberOutputHeight/5)

    const int M_INPUTa_OFFSET_X = -5;
    const int M_INPUTa_OFFSET_Y = HeightStep * 1;
    Node m_inputA;

    const int M_INPUTb_OFFSET_X = -5;
    const int M_INPUTb_OFFSET_Y = HeightStep * 2;
    Node m_inputB;

    const int M_INPUTc_OFFSET_X = -5;
    const int M_INPUTc_OFFSET_Y = HeightStep * 3;
    Node m_inputC;

    const int M_INPUTd_OFFSET_X = -5;
    const int M_INPUTd_OFFSET_Y = HeightStep * 4;
    Node m_inputD;

};

#endif // GATENUMBEROUTPUT_H
