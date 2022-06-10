#include "gateeor.h"

namespace Settings
{
const uint GateEorHeight = 50;
const uint GateEorWidth = 100;

const int NodeOffsetX_a = -5;
const int NodeOffsetY_a = (GateEorHeight/2) - 12;

const int NodeOffsetX_b = -5;
const int NodeOffsetY_b = GateEorHeight - 12;

const int NodeOffsetX_c = GateEorWidth + 5;
const int NodeOffsetY_c = (GateEorHeight/2);
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

/*
GateEor::GateEor(bool notEorGate, GateType type, const char* iconLocation, id inA, id inB, id out) :
    Gate::Gate(type, GateEorWidth,GateEorHeight, iconLocation),
    m_inputA(this, InputNode, inA),
    m_inputB(this, InputNode, inB),
    m_output(this, OutputNode, out)
{
    m_nodes.push_back(&m_inputA);
    m_nodes.push_back(&m_inputB);
    m_nodes.push_back(&m_output);
}*/

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
