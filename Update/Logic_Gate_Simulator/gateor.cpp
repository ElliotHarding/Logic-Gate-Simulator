#include "gateor.h"

GateOr::GateOr() :
    Gate::Gate(GateOrWidth,GateOrHeight, std::string(":/Resources/Gates/gate-or.png").c_str()),
    m_inputA(this),
    m_inputB(this),
    m_output(this)
{
}

GateOr::~GateOr()
{
    DetachNode(&m_inputA);
    DetachNode(&m_inputB);
    DetachNode(&m_output);
}

void GateOr::UpdateOutput()
{
    const bool newVal = m_inputA.value | m_inputB.value;

    //set output node value
    m_output.value = newVal;

    //if output linked to node:
    //- set value of node linked to output node
    //- update the gate owner of the linked node
    Node* linkedNode = m_output.GetLinkedNode();
    if(linkedNode)
    {        
        linkedNode->value = newVal;        
        linkedNode->GetParent()->UpdateOutput();
    }
    delete linkedNode;

    Gate::UpdateOutput();
}

Node *GateOr::GetClickedNode(int clickX, int clickY)
{
    if( m_inputA.UpdateClicked(clickX, clickY))
        return &m_inputA;

    if( m_inputB.UpdateClicked(clickX, clickY))
        return &m_inputB;

    if( m_output.UpdateClicked(clickX, clickY))
        return &m_output;

    return nullptr;
}

void GateOr::DrawNodes(QPainter *painter)
{
    m_inputA.setPosition(m_layout.x() + M_INPUTa_OFFSET_X, m_layout.y() + M_INPUTa_OFFSET_Y);
    m_inputB.setPosition(m_layout.x() + M_INPUTb_OFFSET_X, m_layout.y() + M_INPUTb_OFFSET_Y);
    m_output.setPosition(m_layout.x() + M_OUTPUT_OFFSET_X, m_layout.y() + M_OUTPUT_OFFSET_Y);

    m_inputA.UpdateGraphics(painter);
    m_inputB.UpdateGraphics(painter);
    m_output.UpdateGraphics(painter);
}
