#ifndef GATEOUTPUTBOX_H
#define GATEOUTPUTBOX_H

#include "gate.h"

/*
    Recieves input
 */
class GateReciever : public Gate
{
public:
    GateReciever(const uint& x, const uint& y, const id& out = idGenerator());

    virtual void UpdateOutput() override;
    virtual Gate* Clone() override;

    //Todo : check needed
    bool GetValue(){return m_pInput->value();}

protected:
    void paintEvent(QPaintEvent* paintEvent) override;

private:
    Node* m_pInput;
};

#endif // GATEOUTPUTBOX_H
