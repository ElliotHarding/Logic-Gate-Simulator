#ifndef GATEOUTPUTBOX_H
#define GATEOUTPUTBOX_H

#include "gate.h"

/*
    Recieves input
 */
class GateReciever : public Gate
{
public:
    GateReciever(const int& x = 0, const int& y = 0, const id& out = -1);

    virtual void updateOutput() override;
    virtual Gate* clone() override;
    virtual void draw(QPainter& painter) override;

    bool getValue(){return m_pInput->value();}

private:
    Node* m_pInput;
};

#endif // GATEOUTPUTBOX_H
