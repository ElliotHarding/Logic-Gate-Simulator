#ifndef GATE_H
#define GATE_H

#include "gameobject.h"
#include <fstream>

class Node;

class Gate : public DragableGameObject
{
public:
    Gate(int width, int height, const char* iconLocation = nullptr);
    ~Gate() override;

    virtual void UpdateOutput() = 0;
    virtual void UpdateGraphics(QPainter* painter) override;

    virtual Node* GetClickedNode(int clickX, int clickY) = 0;

    virtual void SaveData(std::ofstream& storage) = 0;

protected:
    void DetachNode(Node* node);

    std::string m_gateName;
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

private:
    Node* m_linkedNode = nullptr;
    Gate* m_parent = nullptr;
};


#endif // GATE_H
