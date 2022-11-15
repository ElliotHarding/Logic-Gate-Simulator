#ifndef GATENOT_H
#define GATENOT_H

#include "gate.h"

class GateNot : public Gate
{
public:
    GateNot(const int& x = 0, const int& y = 0, const id& in = -1, const id& out = -1);

    virtual void updateOutput() override;
    virtual Gate* clone() override;

protected:
    Node* m_pInput;
    Node* m_pOutput;
};

#endif // GATENOT_H
