#ifndef GATEAND_H
#define GATEAND_H

#include "gate.h"

class GateAnd : public Gate
{
public:
    GateAnd(const int& x, const int& y, const id& inA = idGenerator(), const id& inB = idGenerator(), const id& out = idGenerator());
    GateAnd(const GateType& type, const int& x, const int& y, const id& inA = idGenerator(), const id& inB = idGenerator(), const id& out = idGenerator(), const char* iconLocation = std::string(":/Resources/Gates/gate-and.png").c_str());

    virtual void UpdateOutput() override;
    virtual Gate* Clone() override;

protected:
    Node* m_pInputA;
    Node* m_pInputB;
    Node* m_pOutput;
};

#endif // GATEAND_H
