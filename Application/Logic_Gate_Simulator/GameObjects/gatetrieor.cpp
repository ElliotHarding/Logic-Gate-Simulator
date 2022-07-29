#include "gatetrieor.h"

namespace Settings
{
const uint GateTriEorHeight = 50;
const uint GateTriEorWidth = 100;

const int NodeOffsetX_a = -55;
const int NodeOffsetY_a = -11;

const int NodeOffsetX_b = -55;
const int NodeOffsetY_b = 0;

const int NodeOffsetX_c = -55;
const int NodeOffsetY_c = 12;

const int NodeOffsetX_d = 55;
const int NodeOffsetY_d = 0;
}

GateTriEor::GateTriEor(const int &x, const int &y, const id &inA, const id &inB, const id &inC, const id &out) :
    Gate::Gate(GATE_TRI_EOR, x, y, Settings::GateTriEorWidth, Settings::GateTriEorHeight, std::string(":/Resources/Gates/gate-tri-eor.png").c_str()),
    m_pInputA(new Node(this, Settings::NodeOffsetX_a, Settings::NodeOffsetY_a, InputNode, inA)),
    m_pInputB(new Node(this, Settings::NodeOffsetX_b, Settings::NodeOffsetY_b, InputNode, inB)),
    m_pInputC(new Node(this, Settings::NodeOffsetX_c, Settings::NodeOffsetY_c, InputNode, inC)),
    m_pOutput(new Node(this, Settings::NodeOffsetX_d, Settings::NodeOffsetY_d, OutputNode, out))
{
    m_nodes.push_back(m_pInputA);
    m_nodes.push_back(m_pInputB);
    m_nodes.push_back(m_pInputC);
    m_nodes.push_back(m_pOutput);
}

void GateTriEor::UpdateOutput()
{
    const bool sum = m_pInputA->value() ^ m_pInputB->value() ^ m_pInputC->value();
    m_pOutput->setValue(sum);
}

Gate *GateTriEor::Clone()
{
    GateTriEor* clone = new GateTriEor(m_geometry.x(), m_geometry.y(), m_pInputA->id(), m_pInputB->id(), m_pInputC->id(), m_pOutput->id());
    Gate::baseClone(clone);

    return clone;
}
