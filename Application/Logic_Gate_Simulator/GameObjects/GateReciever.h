#ifndef GATEOUTPUTBOX_H
#define GATEOUTPUTBOX_H

#include "gate.h"

/*
    Recieves input
 */
class GateReciever : public Gate
{
public:
    GateReciever(const uint& x, const uint& y, QWidget* pParent = nullptr, id out = idGenerator());

    virtual void UpdateOutput() override;
    virtual Gate* Clone() override;

    //todo check needed
    bool GetValue(){return m_input.GetValue();}

protected:
    void paintEvent(QPaintEvent* paintEvent) override;

private:
    Node m_input;
};

#endif // GATEOUTPUTBOX_H
