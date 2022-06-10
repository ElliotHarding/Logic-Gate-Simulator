#ifndef GATEOUTPUTBOX_H
#define GATEOUTPUTBOX_H

#include "gate.h"

/*
    Recieves input
 */
class GateReciever : public Gate
{
public:
    GateReciever(const int& x, const int& y, const id& out = idGenerator());

    virtual void UpdateOutput() override;
    virtual Gate* Clone() override;
    virtual void draw(QPainter& painter) override;

    bool GetValue(){return m_pInput->value();}

private:
    Node* m_pInput;
};

#endif // GATEOUTPUTBOX_H
