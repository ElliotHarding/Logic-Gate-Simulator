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
        //todo setUpdateOutput()
        //linkedNode->GetParent()->UpdateOutput();
    }
    delete linkedNode;
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
    //This function gets called by seperate draw thread. So to avoid this, draw copies
    Node& pm_input = m_input;
    Node& pm_output = m_output;

    pm_input.SetPosition(m_layout.x() + M_INPUT_OFFSET_X, m_layout.y() + M_INPUT_OFFSET_Y);
    pm_output.SetPosition(m_layout.x() + M_OUTPUT_OFFSET_X, m_layout.y() + M_OUTPUT_OFFSET_Y);

    pm_input.UpdateGraphics(painter);
    pm_output.UpdateGraphics(painter);
}
