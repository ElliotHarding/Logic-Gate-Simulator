#include "gatenot.h"

GateNot::GateNot() :
    Gate::Gate(GateNotWidth,GateNotHeight,std::string(":/Resources/Gates/gate-not.png").c_str()),
    m_input(this),
    m_output(this)
{
}

GateNot::~GateNot()
{
    DetachNode(&m_input);
    DetachNode(&m_output);
}

void GateNot::UpdateOutput()
{
    bool newVal = !(m_input.value);
    m_output.value = newVal;

    //if output linked to node;
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

Node *GateNot::GetClickedNode(int clickX, int clickY)
{
    if( m_input.UpdateClicked(clickX, clickY))
        return &m_input;

    if( m_output.UpdateClicked(clickX, clickY))
        return &m_output;

    return nullptr;
}

void GateNot::DrawNodes(QPainter *painter)
{
    m_input.setPosition(m_layout.x() + M_INPUT_OFFSET_X, m_layout.y() + M_INPUT_OFFSET_Y);
    m_output.setPosition(m_layout.x() + M_OUTPUT_OFFSET_X, m_layout.y() + M_OUTPUT_OFFSET_Y);

    m_input.UpdateGraphics(painter);
    m_output.UpdateGraphics(painter);
}
