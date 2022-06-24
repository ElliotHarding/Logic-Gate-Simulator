#ifndef GATETRIOR_H
#define GATETRIOR_H

#include "gate.h"

class GateTriOr : public Gate
{
public:
    GateTriOr(const int& x = 0, const int& y = 0, const id& inA = -1, const id& inB = -1, const id& inC = -1, const id& out = -1);

    virtual void UpdateOutput() override;
    virtual Gate* Clone() override;

protected:
    ///Nodes
    Node* m_pInputA;
    Node* m_pInputB;
    Node* m_pInputC;
    Node* m_pOutput;
};

#endif // GATETRIOR_H
