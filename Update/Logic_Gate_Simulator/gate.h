#ifndef GATE_H
#define GATE_H

#include "gameobject.h"

class Node;

class Gate : public DragableGameObject
{
public:
    Gate(const char* iconLocation, int width, int height);

    virtual bool    UpdateDrag(int clickX, int clickY) override;
    virtual void    UpdateOutput();
    virtual void    UpdateGraphics(QPainter* painter) override;

    virtual Node* GetClickedNode(int clickX, int clickY) = 0;

protected:
    virtual void DrawNodes(QPainter *painter) = 0;
};

class Node : public GameObject
{
public:
    Node(Gate* parent);
    ~Node() override;

    //Linked node
    void LinkNode(Node* n);
    void DetachNode();
    Node* GetLinkedNode();

    //returns Gate that node is attached to
    Gate* GetParent();

    //Stored value
    bool value;

    virtual void UpdateGraphics(QPainter* painter) override;

    //God I know i'm doing this wrong but whatever if it works i aint changing it, liek the compiler will probs do it for me right?
    QPoint GetPosition (){return QPoint((m_layout.right() - m_layout.left()) + m_layout.left(), (m_layout.bottom() - m_layout.top()) + m_layout.top());}

private:
    Node* m_linkedNode = nullptr;
    Gate* m_parent = nullptr;
};


#endif // GATE_H
