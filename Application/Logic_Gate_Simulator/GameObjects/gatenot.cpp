#include "gatenot.h"

namespace Settings
{
const uint GateNotHeight = 50;
const uint GateNotWidth = 100;

const int NodeOffsetX_a = -55;
const int NodeOffsetY_a = 0;

const int NodeOffsetX_b = 55;
const int NodeOffsetY_b = 0;
}

GateNot::GateNot(const int &x, const int &y, const id &in, const id &out) :
    Gate::Gate(GATE_NOT, x, y, Settings::GateNotWidth, Settings::GateNotHeight, std::string(":/Resources/Gates/gate-not.png").c_str()),
    m_pInput(new Node(this, Settings::NodeOffsetX_a, Settings::NodeOffsetY_a, InputNode, in)),
    m_pOutput(new Node(this, Settings::NodeOffsetX_b, Settings::NodeOffsetY_b, OutputNode, out))
{
    m_nodes.push_back(m_pInput);
    m_nodes.push_back(m_pOutput);
}

void GateNot::UpdateOutput()
{
    m_pOutput->setValue(!(m_pInput->value()));
}

Gate *GateNot::Clone()
{
    GateNot* clone = new GateNot(m_geometry.x(), m_geometry.y(), m_pInput->id(), m_pOutput->id());

    //Clones without the linded nodes... linking comes later.
    clone->m_pInput->setValue(m_pInput->value());
    clone->m_pOutput->setValue(m_pOutput->value());

    return clone;
}

