#include "gateoutputbox.h"

GateOutputBox::GateOutputBox() :
    Gate::Gate(GateOutputBoxWidth,GateOutputBoxHeight),
    m_input(this)
{
    m_type = GateType::GATE_RECIEVER;
}

GateOutputBox::~GateOutputBox()
{
    DetachNode(&m_input);
}

void GateOutputBox::UpdateOutput()
{

    if(m_input.GetLinkedNode())
    {
        m_input.value = m_input.GetLinkedNode()->value;
    }

}

void GateOutputBox::UpdateGraphics(QPainter *painter)
{
    //Draw nodes
    m_input.UpdateGraphics(painter);

    //Paiting variables to be used
    QPainterPath path;
    QPen pen(Qt::black, 10);

    //Draw gate
    painter->setPen(pen);
    painter->drawRect(m_layout);

    //Draw active/inactive button
    QRect activeRect = m_layout;
    activeRect.setLeft(activeRect.left() + BorderWidth);
    activeRect.setRight(activeRect.right() - BorderWidth);
    activeRect.setTop(activeRect.top() + BorderWidth);
    activeRect.setBottom(activeRect.bottom() - BorderWidth);

    pen.setColor(m_input.value ? Qt::red : Qt::black);
    pen.setWidth(20);
    painter->setPen(pen);
    painter->drawRect(activeRect);
}

void GateOutputBox::SetPosition(int x, int y)
{
    GameObject::SetPosition(x,y);

     m_input.SetPosition(m_layout.x() + NODE_OFFSET_X, m_layout.y() + NODE_OFFSET_Y);
}

Node *GateOutputBox::GetClickedNode(int clickX, int clickY)
{
    if( m_input.UpdateClicked(clickX, clickY))
        return &m_input;

    return nullptr;
}

void GateOutputBox::SaveData(std::ofstream &storage)
{
    //Add general gate info
    Gate::SaveData(storage);

    //Add node information
    m_input.SaveData(storage);
}

