#include "gate.h"

#define with << std::endl <<

Gate::Gate(GateType type, int width, int height, const char* iconLocation) :
    DragableGameObject::DragableGameObject(width, height, iconLocation)
{
    m_type = type;
}

Gate::~Gate()
{
}

void Gate::UpdateGraphics(QPainter* painter)
{
    GameObject::UpdateGraphics(painter);
}

void Gate::SaveData(std::ofstream &storage)
{
    //Add general gate info
    // - addition data such as nodes and END_SAVE_TAG_GATE
    //   are stored in overiding function
    storage << SAVE_TAG_GATE
            with std::to_string(m_type)
            with std::to_string(GetPosition().x())
            with std::to_string(GetPosition().y())
            << std::endl;
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
     GameObject::GameObject(15,15),     
     value(0),
     m_parent(parent)
{
}

Node::~Node()
{
    m_parent = nullptr;
    delete m_parent;

    if(m_linkedNode)
    {
        m_linkedNode->DetachNode();
        m_linkedNode = nullptr;
    }
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
    painter->setPen(pen);

    //if linked draw line between node and linked node
    if(m_linkedNode)
    {
        //setting todo
        pen.setWidth(1);

        painter->drawLine(m_linkedNode->GetPosition(),GetPosition());
    }

    //Draw node
    QPoint position(GetPosition());
    painter->drawEllipse(position,10,10);

    //Bug where there's a whole in the node, can't be bothered to look up filling a circle
    painter->drawEllipse(position,4,4);
}

void Node::SaveData(std::ofstream &storage)
{
    storage << SAVE_TAG_NODE
            with std::to_string(m_id)
            with std::to_string(m_linkedId)
            with END_SAVE_TAG_NODE
            << std::endl;
}

Node *Node::GetLinkedNode()
{
    return m_linkedNode;
}
void Node::DetachNode()
{
    if(m_linkedNode)
        m_linkedNode = nullptr;
}
