#ifndef GATETRIEOR_H
#define GATETRIEOR_H

#include "gate.h"

class GateTriEor : public Gate
{
public:
    GateTriEor(const int &x, const int &y, const id& inA = idGenerator(), const id& inB = idGenerator(), const id& inC = idGenerator(), const id& out = idGenerator());

    virtual void UpdateOutput() override;
    virtual Gate* Clone() override;

protected:
    ///Nodes
    Node* m_pInputA;
    Node* m_pInputB;
    Node* m_pInputC;
    Node* m_pOutput;
};

#endif // GATETRIEOR_H
