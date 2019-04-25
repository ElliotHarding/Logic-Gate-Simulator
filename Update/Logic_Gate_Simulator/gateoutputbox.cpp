#include "gateoutputbox.h"

GateOutputBox::GateOutputBox() :
    Gate::Gate(GateOutputBoxWidth,GateOutputBoxHeight),
    m_input(this)
{
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
//Gate::UpdateGraphics(painter) <-- can't use this as dont want to draw the png
//this happens to also call DrawNodes() so...
DrawNodes(painter);
//not the best fix... should have a differnet class structure

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

Node *GateOutputBox::GetClickedNode(int clickX, int clickY)
{
    if( m_input.UpdateClicked(clickX, clickY))
        return &m_input;

    return nullptr;
}

void GateOutputBox::DrawNodes(QPainter *painter)
{
    //This function gets called by seperate draw thread. So to avoid this, draw copies
    Node& pm_input = m_input;

    pm_input.SetPosition(m_layout.x() + NODE_OFFSET_X, m_layout.y() + NODE_OFFSET_Y);
    pm_input.UpdateGraphics(painter);
}

