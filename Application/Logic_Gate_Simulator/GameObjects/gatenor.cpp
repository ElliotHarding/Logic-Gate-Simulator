#include "gatenor.h"

GateNor::GateNor(const int &x, const int &y, const id &inA, const id &inB, const id &out) :
    GateOr(GATE_NOR, x, y, inA, inB, out, std::string(":/Resources/Gates/gate-nor.png").c_str())
{
}

void GateNor::UpdateOutput()
{
    const bool newVal = !(m_pInputA->value() | m_pInputB->value());

    //set output node value
    m_pOutput->setValue(newVal);
}

Gate *GateNor::Clone()
{
    GateNor* clone = new GateNor(position().x(), position().y(), m_pInputA->id(), m_pInputB->id(), m_pOutput->id());
    Gate::baseClone(clone);

    return clone;
}
