#ifndef GATEEOR_H
#define GATEEOR_H

#include "gate.h"

class GateEor : public Gate
{
public:
    GateEor(const int& x, const int& y, const id& inA = idGenerator(), const id& inB = idGenerator(), const id& out = idGenerator());
    GateEor(const GateType& type, const int& x = 0, const int& y = 0, const id& inA = idGenerator(), const id& inB = idGenerator(), const id& out = idGenerator(), const char* iconLocation = std::string(":/Resources/Gates/gate-eor.png").c_str());

    virtual void UpdateOutput() override;
    virtual Gate* Clone() override;

protected:
    Node* m_pInputA;
    Node* m_pInputB;
    Node* m_pOutput;
};

#endif // GATEEOR_H
