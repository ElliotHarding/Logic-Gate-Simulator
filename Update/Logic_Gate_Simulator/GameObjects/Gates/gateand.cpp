#include "gateand.h"
#include <QDebug>

GateAnd::GateAnd(id inA, id inB, id out) :
    Gate::Gate(GATE_AND, GateAndWidth,GateAndHeight, std::string(":/Resources/Gates/gate-and.png").c_str()),
    m_inputA(this, inA),
    m_inputB(this, inB),
    m_output(this, out)
{
}

GateAnd::~GateAnd()
{
    if(m_output.GetLinkedNode())
        m_output.GetLinkedNode()->GetParent()->UpdateOutput();

    DetachNode(&m_inputA);
    DetachNode(&m_inputB);
    DetachNode(&m_output);
}

void GateAnd::UpdateOutput()
{
    const bool sum = m_inputA.value & m_inputB.value;

    //set output node value
    m_output.value = sum;

    //if output linked to node;
    //- set value of node linked to output node
    //- update the gate owner of the linked node
    Node* linkedNode = m_output.GetLinkedNode();
    if(linkedNode)
    {
        linkedNode->value = sum;
        linkedNode->GetParent()->UpdateOutput();
    }
    linkedNode = nullptr;
}

void GateAnd::UpdateGraphics(QPainter *painter)
{
    m_inputA.UpdateGraphics(painter);
    m_inputB.UpdateGraphics(painter);
    m_output.UpdateGraphics(painter);

    Gate::UpdateGraphics(painter);
}

void GateAnd::SetPosition(int x, int y)
{
    GameObject::SetPosition(x,y);

    m_inputA.SetPosition(m_layout.x() + M_INPUTa_OFFSET_X, m_layout.y() + M_INPUTa_OFFSET_Y);
    m_inputB.SetPosition(m_layout.x() + M_INPUTb_OFFSET_X, m_layout.y() + M_INPUTb_OFFSET_Y);
    m_output.SetPosition(m_layout.x() + M_OUTPUT_OFFSET_X, m_layout.y() + M_OUTPUT_OFFSET_Y);
}

//Returns a clicked node if the gate has a node thats been clicked
Node *GateAnd::GetClickedNode(int clickX, int clickY)
{
    if( m_inputA.UpdateClicked(clickX, clickY))
        return &m_inputA;

    if( m_inputB.UpdateClicked(clickX, clickY))
        return &m_inputB;

    if( m_output.UpdateClicked(clickX, clickY))
        return &m_output;

    return nullptr;
}

void GateAnd::SaveData(std::ofstream &storage)
{
    //Add general gate info
    Gate::SaveData(storage);

    //Add node information
    m_inputA.SaveData(storage);
    m_inputB.SaveData(storage);
    m_output.SaveData(storage);

    storage << END_SAVE_TAG_GATE << std::endl;
}

Node *GateAnd::FindNodeWithId(id _id)
{
    if(m_output.m_id == _id)
        return &m_output;
    if(m_inputA.m_id == _id)
        return &m_inputA;
    if(m_inputB.m_id == _id)
        return &m_inputB;
    return nullptr;
}
