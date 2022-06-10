#include "gateeor.h"

namespace Settings
{
const uint GateEorHeight = 50;
const uint GateEorWidth = 100;

const int NodeOffsetX_a = -55;
const int NodeOffsetY_a = 13;

const int NodeOffsetX_b = -55;
const int NodeOffsetY_b = -13;

const int NodeOffsetX_c = 60;
const int NodeOffsetY_c = 0;
}

GateEor::GateEor(const int& x, const int& y, const id& inA, const id& inB, const id& out) :
    Gate::Gate(GATE_EOR, x, y, Settings::GateEorWidth, Settings::GateEorHeight, std::string(":/Resources/Gates/gate-eor.png").c_str()),
    m_pInputA(new Node(this, Settings::NodeOffsetX_a, Settings::NodeOffsetY_a, InputNode, inA)),
    m_pInputB(new Node(this, Settings::NodeOffsetX_b, Settings::NodeOffsetY_b, InputNode, inB)),
    m_pOutput(new Node(this, Settings::NodeOffsetX_c, Settings::NodeOffsetY_c, OutputNode, out))
{
    m_nodes.push_back(m_pInputA);
    m_nodes.push_back(m_pInputB);
    m_nodes.push_back(m_pOutput);
}

GateEor::GateEor(const GateType& type, const int &x, const int &y, const id &inA, const id &inB, const id &out, const char *iconLocation) :
    Gate::Gate(type, x, y, Settings::GateEorWidth, Settings::GateEorHeight, iconLocation),
    m_pInputA(new Node(this, Settings::NodeOffsetX_a, Settings::NodeOffsetY_a, InputNode, inA)),
    m_pInputB(new Node(this, Settings::NodeOffsetX_b, Settings::NodeOffsetY_b, InputNode, inB)),
    m_pOutput(new Node(this, Settings::NodeOffsetX_c, Settings::NodeOffsetY_c, OutputNode, out))
{
    m_nodes.push_back(m_pInputA);
    m_nodes.push_back(m_pInputB);
    m_nodes.push_back(m_pOutput);
}

void GateEor::UpdateOutput()
{
    const bool newVal = m_pInputA->value() ^ m_pInputB->value();

    //set output node value
    m_pOutput->setValue(newVal);
}

Gate* GateEor::Clone()
{
    GateEor* clone = new GateEor(m_geometry.x(), m_geometry.y(), m_pInputA->id(), m_pInputB->id(), m_pOutput->id());

    //Clone nodes
    clone->m_pInputA = m_pInputA;
    clone->m_pInputB = m_pInputB;
    clone->m_pOutput = m_pOutput;

    return clone;
}
