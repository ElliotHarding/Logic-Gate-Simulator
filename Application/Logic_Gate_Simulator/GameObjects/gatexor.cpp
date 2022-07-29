#include "gatexor.h"

GateXor::GateXor(const int &x, const int &y, const id &inA, const id &inB, const id &out) :
    GateEor(GATE_XOR, x, y, inA, inB, out, std::string(":/Resources/Gates/gate-neor.png").c_str())
{
}

void GateXor::UpdateOutput()
{
    const bool newVal = !(m_pInputA->value() ^ m_pInputB->value());

    //set output node value
    m_pOutput->setValue(newVal);
}

Gate *GateXor::Clone()
{
    GateXor* clone = new GateXor(m_geometry.x(), m_geometry.y(), m_pInputA->id(), m_pInputB->id(), m_pOutput->id());
    Gate::baseClone(clone);

    return clone;
}
