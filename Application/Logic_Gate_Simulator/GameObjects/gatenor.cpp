#include "gatenor.h"

GateNor::GateNor() :
    GateOr (1, GATE_NOR, std::string(":/Resources/Gates/gate-nor.png").c_str())
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
    GateNor* clone = new GateNor();

    //Clone position
    QPoint pos = GetPosition();
    clone->SetPosition(pos.x(), pos.y());

    //Clone nodes
    clone->m_pInputA = m_pInputA;
    clone->m_pInputB = m_pInputB;
    clone->m_pOutput = m_pOutput;

    return clone;
}
