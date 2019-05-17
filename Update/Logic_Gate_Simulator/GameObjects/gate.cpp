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
    for (size_t index = 0; index < m_nodes.size(); index++)
    {
        m_nodes.erase(m_nodes.begin() + index);
    }
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

bool Gate::FindNodeWithId(id _id, Node*& node)
{
    for (size_t index = 0; index < m_nodes.size(); index++)
    {
        if(m_nodes[index]->m_id == _id)
        {
            node = &*m_nodes[index];
            return true;
        }
    }
    return false;
}

void Gate::AssignNewNodeIds()
{
    for (Node* n : m_nodes)
    {
        n->GenNewID();
    }
}

bool Gate::DeleteClick(int clickX, int clickY)
{
    return UpdateClicked(clickX, clickY);
}

void Gate::SaveGeneralData(std::ofstream &storage)
{
    //Add general gate info
    storage << SAVE_TAG_GATE
            with std::to_string(m_type)
            with std::to_string(Enabled)
            with std::to_string(GetPosition().x())
            with std::to_string(GetPosition().y())
            << std::endl;
}

void Gate::DetachNodes()
{
    for (Node* n : m_nodes)
    {
        n->DetachNode();
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
    m_linkedNode = nullptr;
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

void Node::GenNewID()
{
    m_id = idGenerator();
}

Node *Node::GetLinkedNode()
{
    return m_linkedNode;
}

void Node::LinkNode(Node*& n)
{
    m_linked = true;
    m_linkedNode = n;
    m_parent->UpdateOutput();
}

void Node::DetachNode()
{
    if(m_linkedNode)
    {
        m_linkedNode->m_linkedNode = nullptr;
        m_linkedNode = nullptr;
    }
}
