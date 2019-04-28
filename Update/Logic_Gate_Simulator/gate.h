#ifndef GATE_H
#define GATE_H

#include "gameobject.h"
#include <fstream>

#define with << std::endl <<

enum GateType
{
    GATE_AND = 1,
    GATE_OR = 2,
    GATE_NOT = 3,
    GATE_EMMITTER = 4,
    GATE_RECIEVER = 5,
    GATE_CUSTOM = 6,
    GATE_NULL
};

class Node;
class Gate : public DragableGameObject
{
public:
    Gate(int width, int height, const char* iconLocation = nullptr);
    ~Gate() override;

    virtual void UpdateOutput() = 0;
    virtual void UpdateGraphics(QPainter* painter) override;

    virtual Node* GetClickedNode(int clickX, int clickY) = 0;
    virtual void SaveData(std::ofstream& storage);

    int Left(){return m_layout.left();};
    int Right(){return m_layout.right();};
    int Top(){return m_layout.top();};
    int Bottom(){return m_layout.bottom();};

protected:
    void DetachNode(Node* node);
    GateType m_type;
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

    void SaveData(std::ofstream& storage);
private:
    Node* m_linkedNode = nullptr;
    Gate* m_parent = nullptr;
    int m_id = -1;
    int m_linkedId = -1;
};


#endif // GATE_H
