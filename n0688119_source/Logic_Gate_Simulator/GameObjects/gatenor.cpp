#include "gatenor.h"

GateNor::GateNor() :
    GateOr (1, GATE_NOR, std::string(":/Resources/Gates/gate-nor.png").c_str())
{
}

void GateNor::UpdateOutput()
{
    const bool newVal = !(m_inputA.GetValue() | m_inputB.GetValue());

    //set output node value
    m_output.SetValue(newVal);
}

Gate *GateNor::Clone()
{
    GateNor* clone = new GateNor();

    //Clone position
    QPoint pos = GetPosition();
    clone->SetPosition(pos.x(), pos.y());

    //Clone nodes
    clone->m_inputA = m_inputA;
    clone->m_inputB = m_inputB;
    clone->m_output = m_output;

    return clone;
}
