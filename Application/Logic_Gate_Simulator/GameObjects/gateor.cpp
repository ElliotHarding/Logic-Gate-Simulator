#include "gateor.h"

namespace Settings
{
const uint GateOrHeight = 50;
const uint GateOrWidth = 100;

const int NodeOffsetX_a = -55;
const int NodeOffsetY_a = 13;

const int NodeOffsetX_b = -55;
const int NodeOffsetY_b = -13;

const int NodeOffsetX_c = 60;
const int NodeOffsetY_c = 0;
}

GateOr::GateOr(const int &x, const int &y, const id &inA, const id &inB, const id &out) :
    Gate::Gate(GATE_OR, x, y, Settings::GateOrWidth, Settings::GateOrHeight, std::string(":/Resources/Gates/gate-or.png").c_str()),
    m_pInputA(new Node(this, Settings::NodeOffsetX_a, Settings::NodeOffsetY_a, InputNode, inA)),
    m_pInputB(new Node(this, Settings::NodeOffsetX_b, Settings::NodeOffsetY_b, InputNode, inB)),
    m_pOutput(new Node(this, Settings::NodeOffsetX_c, Settings::NodeOffsetY_c, OutputNode, out))
{
    m_nodes.push_back(m_pInputA);
    m_nodes.push_back(m_pInputB);
    m_nodes.push_back(m_pOutput);
}

GateOr::GateOr(const GateType& type, const int &x, const int &y, const id &inA, const id &inB, const id &out, const char *iconLocation) :
    Gate::Gate(type, x, y, Settings::GateOrWidth, Settings::GateOrHeight, iconLocation),
    m_pInputA(new Node(this, Settings::NodeOffsetX_a, Settings::NodeOffsetY_a, InputNode, inA)),
    m_pInputB(new Node(this, Settings::NodeOffsetX_b, Settings::NodeOffsetY_b, InputNode, inB)),
    m_pOutput(new Node(this, Settings::NodeOffsetX_c, Settings::NodeOffsetY_c, OutputNode, out))
{
    m_nodes.push_back(m_pInputA);
    m_nodes.push_back(m_pInputB);
    m_nodes.push_back(m_pOutput);
}

void GateOr::UpdateOutput()
{
    const bool newVal = m_pInputA->value() | m_pInputB->value();

    //set output node value
    m_pOutput->setValue(newVal);
}

Gate* GateOr::Clone()
{
    GateOr* clone = new GateOr(m_geometry.x(), m_geometry.y(), m_pInputA->id(), m_pInputB->id(), m_pOutput->id());

    //Clones without the linded nodes... linking comes later.
    clone->m_pInputA->setValue(m_pInputA->value());
    clone->m_pInputB->setValue(m_pInputB->value());
    clone->m_pOutput->setValue(m_pOutput->value());

    return clone;
}
