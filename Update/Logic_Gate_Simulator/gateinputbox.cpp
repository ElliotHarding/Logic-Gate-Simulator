#include "gateinputbox.h"

GateInputBox::GateInputBox() :
    Gate::Gate(std::string(":/Resources/Resources/box.png").c_str(),GateInputBoxWidth,GateInputBoxHeight),
    m_output(this)
{
}

GateInputBox::~GateInputBox()
{
    DetachNode(&m_output);
}

void GateInputBox::UpdateOutput()
{
    //if new click
    if(!m_bColorJustSwitched && beingClicked)
    {
        m_output.value = !m_output.value;

        m_bColorJustSwitched = true;

        //if output linked to node;
        //- set value of node linked to output node
        //- update the gate owner of the linked node
        if(m_output.GetLinkedNode())
        {
            m_output.GetLinkedNode()->value = m_output.value;
            m_output.GetLinkedNode()->GetParent()->UpdateOutput();
        }
    }

    m_bColorJustSwitched = !beingClicked;

    Gate::UpdateOutput();
}

void GateInputBox::UpdateGraphics(QPainter *painter)
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

    pen.setColor(m_output.value ? Qt::red : Qt::black);
    pen.setWidth(20);
    painter->setPen(pen);
    painter->drawRect(activeRect);
}

Node *GateInputBox::GetClickedNode(int clickX, int clickY)
{
    if( m_output.UpdateClicked(clickX, clickY))
        return &m_output;

    return nullptr;
}

void GateInputBox::DrawNodes(QPainter *painter)
{
    m_output.setPosition(m_layout.x() + NODE_OFFSET_X, m_layout.y() + NODE_OFFSET_Y);
    m_output.UpdateGraphics(painter);
}

