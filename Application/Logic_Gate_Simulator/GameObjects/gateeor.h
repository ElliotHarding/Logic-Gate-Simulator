#ifndef GATEEOR_H
#define GATEEOR_H

#include "gate.h"

class GateEor : public Gate
{
public:
    GateEor(const int& x = 0, const int& y = 0, const id& inA = -1, const id& inB = -1, const id& out = -1);
    GateEor(const GateType& type, const int& x = 0, const int& y = 0, const id& inA = -1, const id& inB = -1, const id& out = -1, const char* iconLocation = std::string(":/Resources/Gates/gate-eor.png").c_str());

    virtual void UpdateOutput() override;
    virtual Gate* Clone() override;

protected:
    Node* m_pInputA;
    Node* m_pInputB;
    Node* m_pOutput;
};

#endif // GATEEOR_H
