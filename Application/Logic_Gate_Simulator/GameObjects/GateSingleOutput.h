#ifndef GATESINGLEOUTPUT_H
#define GATESINGLEOUTPUT_H

#include "gate.h"

/*
    Inherited by gates with single output
*/
class GateSingleOutput : public Gate
{
public:
    GateSingleOutput(const uint& x, const uint& y, const GateType& type, const id& nodeId, QWidget* pParent = nullptr);

    virtual void UpdateOutput() override = 0;

protected:
    void paintEvent(QPaintEvent* paintEvent) override;

    Node* m_pOutput;
};

#endif // GATESINGLEOUTPUT_H
