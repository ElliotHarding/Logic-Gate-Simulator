#ifndef GATEAND_H
#define GATEAND_H

#include "gate.h"

class GateAnd : public Gate
{
public:
    GateAnd(const int& x = 0, const int& y = 0, const id& inA = -1, const id& inB = -1, const id& out = -1);
    GateAnd(const GateType& type, const int& x, const int& y, const id& inA = -1, const id& inB = -1, const id& out = -1, const char* iconLocation = std::string(":/Resources/Gates/gate-and.png").c_str());

    virtual void updateOutput() override;
    virtual Gate* clone() override;

protected:
    Node* m_pInputA;
    Node* m_pInputB;
    Node* m_pOutput;
};

#endif // GATEAND_H
