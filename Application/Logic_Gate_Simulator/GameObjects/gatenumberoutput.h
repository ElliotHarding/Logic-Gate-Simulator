#ifndef GATENUMBEROUTPUT_H
#define GATENUMBEROUTPUT_H

#include "gate.h"

class GateNumberOutput : public Gate
{
public:
    GateNumberOutput(const int& x = 0, const int& y = 0, const id& inA = -1, const id& inB = -1, const id& inC = -1, const id& inD = -1);

    virtual void updateOutput() override;
    virtual void draw(QPainter& painter) override;
    virtual Gate* clone() override;

protected:
    ///Nodes
    Node* m_pInputA;
    Node* m_pInputB;
    Node* m_pInputC;
    Node* m_pInputD;

    int m_output;
};

#endif // GATENUMBEROUTPUT_H
