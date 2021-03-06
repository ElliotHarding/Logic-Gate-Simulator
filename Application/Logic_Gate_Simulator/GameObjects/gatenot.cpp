#include "gatenot.h"

GateNot::GateNot(id in, id out) :
    Gate::Gate(GATE_NOT, GateNotWidth,GateNotHeight,std::string(":/Resources/Gates/gate-not.png").c_str()),
    m_input(this,InputNode,in),
    m_output(this,OutputNode,out)
{
    m_nodes.push_back(&m_input);
    m_nodes.push_back(&m_output);
}

void GateNot::UpdateOutput()
{
    m_output.SetValue(!(m_input.GetValue()));
}

void GateNot::SetPosition(int x, int y)
{
    GameObject::SetPosition(x,y);

    m_input.SetPosition(m_layout.x() + M_INPUT_OFFSET_X, m_layout.y() + M_INPUT_OFFSET_Y);
    m_output.SetPosition(m_layout.x() + M_OUTPUT_OFFSET_X, m_layout.y() + M_OUTPUT_OFFSET_Y);
}

Gate *GateNot::Clone()
{
    GateNot* clone = new GateNot();

    //Clone position
    QPoint pos = GetPosition();
    clone->SetPosition(pos.x(), pos.y());

    //Clone nodes
    clone->m_output = m_output;
    clone->m_input = m_input;

    return clone;
}

