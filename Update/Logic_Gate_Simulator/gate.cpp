#include "gate.h"
#include "gatecollection.h"

#define with << std::endl <<

Gate::Gate(GateType type, int width, int height, const char* iconLocation) :
    DragableGameObject::DragableGameObject(width, height, iconLocation),
    m_type(type)
{
}

Gate::~Gate()
{
    DetachNodes();
}

void Gate::UpdateGraphics(QPainter* painter)
{
    for (Node* n : m_nodes)
    {
        n->UpdateGraphics(painter);
    }

    GameObject::UpdateGraphics(painter);
}

void Gate::SaveData(std::ofstream &storage)
{
    SaveGeneralData(storage);

    //Add node information
    for (Node* n : m_nodes)
    {
        n->SaveData(storage);
    }

    storage << END_SAVE_TAG_GATE << std::endl;
}

Node *Gate::GetClickedNode(int clickX, int clickY)
{
    for (Node* n : m_nodes)
    {
        if(n->UpdateClicked(clickX, clickY))
            return n;
    }
    return nullptr;
}

Node *Gate::FindNodeWithId(id _id)
{
    for (Node* n : m_nodes)
    {
        if(n->m_id == _id)
            return n;
    }
    return nullptr;
}

void Gate::SaveGeneralData(std::ofstream &storage)
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

void Gate::DetachNodes()
{
    for (size_t index = 0; index < m_nodes.size(); index++)
    {
        Node* n = m_nodes[index];

        if(n->GetLinkedNode())
        {
            n->GetLinkedNode()->DetachNode();
            n->DetachNode();
        }

        m_nodes.erase(m_nodes.begin() + index);
        delete n;
    }
}


//
// -- NODE IMPLEMENTATION --
//

Node::Node(Gate *parent, int id) :
    GameObject::GameObject(15,15),
    value(0),
    m_parent(parent),
    m_id(id)
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
    int linkedNodeId = -1;
    if(m_linkedNode)
         linkedNodeId = m_linkedNode->m_id;

    storage << SAVE_TAG_NODE
            with std::to_string(m_id)
            with std::to_string(linkedNodeId)
            with END_SAVE_TAG_NODE
            << std::endl;
}

Node *Node::GetLinkedNode()
{
    return m_linkedNode;
}

void Node::LinkNode(Node*& n)
{
    m_linkedNode = n;
    m_parent->UpdateOutput();
}

void Node::DetachNode()
{
    if(m_linkedNode)
        m_linkedNode = nullptr;
    m_parent->UpdateOutput();
}
