#include "gateand.h"
#include <QDebug>

GateAnd::GateAnd() :
    Gate::Gate(GateAndWidth,GateAndHeight, std::string(":/Resources/Gates/gate-and.png").c_str()),
    m_inputA(this),
    m_inputB(this),
    m_output(this)
{
    qDebug() << "And gate created";
}

GateAnd::~GateAnd()
{
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

        //todo setUpdateOutput()
        //linkedNode->GetParent()->UpdateOutput();
    }
    delete linkedNode;
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

}
