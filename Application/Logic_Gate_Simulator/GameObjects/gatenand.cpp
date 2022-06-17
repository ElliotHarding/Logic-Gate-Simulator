#include "gatenand.h"

GateNand::GateNand(const int &x, const int &y, const id &inA, const id &inB, const id &out) :
    GateAnd(GATE_NAND, x, y, inA, inB, out, std::string(":/Resources/Gates/gate-nand.png").c_str())
{
}

void GateNand::UpdateOutput()
{
    const bool sum = !(m_pInputA->value() & m_pInputB->value());

    //set output node value
    m_pOutput->setValue(sum);
}

Gate *GateNand::Clone()
{
    GateNand* clone = new GateNand(m_geometry.x(), m_geometry.y(), m_pInputA->id(), m_pInputB->id(), m_pOutput->id());

    //Clones without the linded nodes... linking comes later.
    clone->m_pInputA->setValue(m_pInputA->value());
    clone->m_pInputB->setValue(m_pInputB->value());
    clone->m_pOutput->setValue(m_pOutput->value());

    return clone;
}
