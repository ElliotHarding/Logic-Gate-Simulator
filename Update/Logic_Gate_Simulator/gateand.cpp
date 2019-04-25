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
        linkedNode->GetParent()->UpdateOutput();
    }
    delete linkedNode;
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

void GateAnd::DrawNodes(QPainter *painter)
{    
    //This function gets called by seperate draw thread. So to avoid this, draw copies
    Node& pm_inputA = m_inputA;
    Node& pm_inputB = m_inputB;
    Node& pm_output = m_output;

    pm_inputA.SetPosition(m_layout.x() + M_INPUTa_OFFSET_X, m_layout.y() + M_INPUTa_OFFSET_Y);
    pm_inputB.SetPosition(m_layout.x() + M_INPUTb_OFFSET_X, m_layout.y() + M_INPUTb_OFFSET_Y);
    pm_output.SetPosition(m_layout.x() + M_OUTPUT_OFFSET_X, m_layout.y() + M_OUTPUT_OFFSET_Y);

    pm_inputA.UpdateGraphics(painter);
    pm_inputB.UpdateGraphics(painter);
    pm_output.UpdateGraphics(painter);
}
