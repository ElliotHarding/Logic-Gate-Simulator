#ifndef GATE_H
#define GATE_H

#include "gameobject.h"

class Node;

class Gate : public DragableGameObject
{
public:
    Gate(const char* iconLocation, int height, int width);

    virtual bool    UpdateDrag(int clickX, int clickY) override;
    virtual void    UpdateOutput();
    virtual void    UpdateGraphics(QPainter* painter) override;

    virtual Node* GetClickedNode(int clickX, int clickY) = 0;

protected:
    virtual void DrawNodes() = 0;
};

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


#endif // GATE_H
