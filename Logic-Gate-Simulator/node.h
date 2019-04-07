#ifndef NODE_H
#define NODE_H

#include "gate.h"
#include "gameobject.h"

class Node : public GameObject
{
public:
    Node(Gate* parent);
    ~Node();

    //Linked node
    void LinkNode(Node* n);
    void DetachNode();
    Node* GetLinkedNode();

    //returns Gate that node is attached to
    Gate* GetParent();

    //Stored value
    bool value;

private:
    Node* m_linkedNode = nullptr;
    Gate* m_parent = nullptr;
};

#endif // NODE_H
