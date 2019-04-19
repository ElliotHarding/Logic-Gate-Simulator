#include "gate.h"

Gate::Gate(const char* iconLocation, int width, int height) :
    DragableGameObject::DragableGameObject(iconLocation, width, height)
{
}

Gate::~Gate()
{
}

bool Gate::UpdateDrag(int clickX, int clickY)
{
    return DragableGameObject::UpdateDrag(clickX, clickY);
}

void Gate::UpdateOutput()
{

}

void Gate::UpdateGraphics(QPainter* painter)
{
    GameObject::UpdateGraphics(painter);

    DrawNodes(painter);
}

void Gate::DetachNode(Node *node)
{
    if(node->GetLinkedNode())
        node->GetLinkedNode()->DetachNode();
    node->DetachNode();
}


//
// -- NODE IMPLEMENTATION --
//

Node::Node(Gate* parent) :
     GameObject::GameObject("Resources/circle.png",15,15)
{
    m_parent = parent;
    value = 0;
}
Node::~Node()
{
    m_parent = nullptr;
    delete m_parent;
    m_linkedNode = nullptr;
    delete m_linkedNode;
}

void Node::LinkNode(Node* n)
{
    m_linkedNode = n;
}

Gate* Node::GetParent()
{
    return m_parent;
}

void Node::UpdateGraphics(QPainter* painter)
{
    //Paiting variables to be used
    QPainterPath path;
    QPen pen(Qt::black, 10);

    //Draw node
    painter->setPen(pen);
    QPoint position(m_layout.x(),m_layout.y());
    painter->drawEllipse(position,10,10);

    //Bug where there's a whole in the node, can't be bothered to look up filling a circle
    painter->drawEllipse(position,4,4);

    //if linked draw line between node and linked node
    if(m_linkedNode)
    {
        //setting todo
        pen.setWidth(1);

        painter->drawLine(m_linkedNode->GetPosition(),GetPosition());
    }
}

Node *Node::GetLinkedNode()
{
    return m_linkedNode;
}
void Node::DetachNode()
{
    m_linkedNode = nullptr;
}
