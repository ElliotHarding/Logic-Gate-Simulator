#include "node.h"

Node::Node(Gate* parent)
{
    m_parent = parent;
    value = 0;
}
Node::~Node()
{
    delete m_parent;
    delete m_linkedNode;
}

void Node::UpdatePositions(int clickX, int clickY)
{
    GameObject::UpdatePositions(clickX,clickY);
}
void Node::LinkNode(Node* n)
{
    m_linkedNode = n;
}
Gate* Node::GetParent()
{
    return m_parent;
}

void Node::updateClicked(int x, int y)
{
    if(pointInside(x,y))
    {
        beingClicked = true;
    }
    else
    {
        beingClicked = false;
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
