#ifndef GATENUMBEROUTPUT_H
#define GATENUMBEROUTPUT_H

#include "gate.h"

class GateNumberOutput : public Gate
{
public:
    GateNumberOutput(const int& x, const int& y, const id& inA = idGenerator(), const id& inB = idGenerator(), const id& inC = idGenerator(), const id& inD = idGenerator());

    virtual void UpdateOutput() override;
    virtual void draw(QPainter& painter) override;
    virtual Gate* Clone() override;

protected:
    ///Nodes
    Node* m_pInputA;
    Node* m_pInputB;
    Node* m_pInputC;
    Node* m_pInputD;

    int m_output;
};

#endif // GATENUMBEROUTPUT_H
