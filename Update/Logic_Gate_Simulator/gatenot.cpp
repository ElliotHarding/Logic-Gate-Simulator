#include "gatenot.h"

GateNot::GateNot(id in, id out) :
    Gate::Gate(GATE_NOT, GateNotWidth,GateNotHeight,std::string(":/Resources/Gates/gate-not.png").c_str()),
    m_input(this,in),
    m_output(this,out)
{
}

GateNot::~GateNot()
{
    if(m_output.GetLinkedNode())
        m_output.GetLinkedNode()->GetParent()->UpdateOutput();

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
    linkedNode = nullptr;
}

void GateNot::SetPosition(int x, int y)
{
    GameObject::SetPosition(x,y);

    m_input.SetPosition(m_layout.x() + M_INPUT_OFFSET_X, m_layout.y() + M_INPUT_OFFSET_Y);
    m_output.SetPosition(m_layout.x() + M_OUTPUT_OFFSET_X, m_layout.y() + M_OUTPUT_OFFSET_Y);
}

void GateNot::UpdateGraphics(QPainter *painter)
{
    m_input.UpdateGraphics(painter);
    m_output.UpdateGraphics(painter);

    Gate::UpdateGraphics(painter);
}

Node *GateNot::GetClickedNode(int clickX, int clickY)
{
    if( m_input.UpdateClicked(clickX, clickY))
        return &m_input;

    if( m_output.UpdateClicked(clickX, clickY))
        return &m_output;

    return nullptr;
}

void GateNot::SaveData(std::ofstream &storage)
{
    //Add general gate info
    Gate::SaveData(storage);

    //Add node information
    m_input.SaveData(storage);
    m_output.SaveData(storage);

    storage << END_SAVE_TAG_GATE << std::endl;
}

Node *GateNot::FindNodeWithId(id _id)
{
    if(m_output.m_id == _id)
        return &m_output;
    if(m_input.m_id == _id)
        return &m_input;
    return nullptr;
}
