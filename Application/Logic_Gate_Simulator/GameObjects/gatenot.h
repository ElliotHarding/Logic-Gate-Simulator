#ifndef GATENOT_H
#define GATENOT_H

#include "gate.h"

class GateNot : public Gate
{
public:
    GateNot(const int& x, const int& y, const id& in = idGenerator(), const id& out = idGenerator());

    virtual void UpdateOutput() override;
    virtual Gate* Clone() override;

protected:
    Node* m_pInput;
    Node* m_pOutput;
};

#endif // GATENOT_H
