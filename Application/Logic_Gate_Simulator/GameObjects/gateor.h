#ifndef GATEOR_H
#define GATEOR_H

#include "gate.h"

class GateOr : public Gate
{
public:
    GateOr(const int& x = 0, const int& y = 0, const id& inA = idGenerator(), const id& inB = idGenerator(), const id& out = idGenerator());
    GateOr(const GateType& type, const int& x, const int& y, const id& inA = idGenerator(), const id& inB = idGenerator(), const id& out = idGenerator(), const char* iconLocation = std::string(":/Resources/Gates/gate-or.png").c_str());

    virtual void UpdateOutput() override;
    virtual Gate* Clone() override;

protected:
    Node* m_pInputA;
    Node* m_pInputB;
    Node* m_pOutput;
};

#endif // GATEOR_H
