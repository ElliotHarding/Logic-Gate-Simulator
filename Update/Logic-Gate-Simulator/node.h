#ifndef NODE_H
#define NODE_H

#include "gate.h"
#include "gameobject.h"

class Node : GameObject
{
public:
    Node(Gate* parent);
    ~Node();

    virtual void UpdatePositions(int clickX, int clickY);

    //Linked node
    void LinkNode(Node* n);
    void DetachNode();
    Node* GetLinkedNode();

    Gate* GetParent();

    //Clicking
    void updateClicked(int x, int y);
    bool beingClicked = false;

    //Stored value
    bool value;

private:
    Node* m_linkedNode = nullptr;
    Gate* m_parent = nullptr;
};

#endif // NODE_H
