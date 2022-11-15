#include "gateand.h"

namespace Settings
{
const uint GateAndHeight = 50;
const uint GateAndWidth = 100;

const int NodeOffsetX_a = -55;
const int NodeOffsetY_a = 13;

const int NodeOffsetX_b = -55;
const int NodeOffsetY_b = -13;

const int NodeOffsetX_c = 60;
const int NodeOffsetY_c = 0;
}

GateAnd::GateAnd(const int& x, const int& y, const id& inA, const id& inB, const id& out) :
    Gate(GATE_AND, x, y, Settings::GateAndWidth, Settings::GateAndHeight, std::string(":/Resources/Gates/gate-and.png").c_str()),
    m_pInputA(new Node(this, Settings::NodeOffsetX_a, Settings::NodeOffsetY_a, InputNode, inA)),
    m_pInputB(new Node(this, Settings::NodeOffsetX_b, Settings::NodeOffsetY_b, InputNode, inB)),
    m_pOutput(new Node(this, Settings::NodeOffsetX_c, Settings::NodeOffsetY_c, OutputNode, out))
{
    m_nodes.push_back(m_pInputA);
    m_nodes.push_back(m_pInputB);
    m_nodes.push_back(m_pOutput);
}

GateAnd::GateAnd(const GateType& type, const int &x, const int &y, const id &inA, const id &inB, const id &out, const char *iconLocation) :
    Gate(type, x, y, Settings::GateAndWidth, Settings::GateAndHeight, iconLocation),
    m_pInputA(new Node(this, Settings::NodeOffsetX_a, Settings::NodeOffsetY_a, InputNode, inA)),
    m_pInputB(new Node(this, Settings::NodeOffsetX_b, Settings::NodeOffsetY_b, InputNode, inB)),
    m_pOutput(new Node(this, Settings::NodeOffsetX_c, Settings::NodeOffsetY_c, OutputNode, out))
{
    m_nodes.push_back(m_pInputA);
    m_nodes.push_back(m_pInputB);
    m_nodes.push_back(m_pOutput);
}

void GateAnd::UpdateOutput()
{
    //Perform AND operation on two input nodes
    const bool sum = m_pInputA->value() & m_pInputB->value();

    //set output node value
    m_pOutput->setValue(sum);
}

Gate *GateAnd::Clone()
{
    GateAnd* clone = new GateAnd(position().x(), position().y(), m_pInputA->id(), m_pInputB->id(), m_pOutput->id());
    Gate::baseClone(clone);

    return clone;
}
