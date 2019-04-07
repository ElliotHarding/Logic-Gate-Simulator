#include "node.h"

Node::Node(Gate* parent) :
     GameObject::GameObject("iconLocation",5,5)
{
    m_parent = parent;
    value = 0;
}
Node::~Node()
{
    m_linkedNode->DetachNode();

    delete m_parent;
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

Node *Node::GetLinkedNode()
{
    return m_linkedNode;
}
void Node::DetachNode()
{
    m_linkedNode = nullptr;
}
