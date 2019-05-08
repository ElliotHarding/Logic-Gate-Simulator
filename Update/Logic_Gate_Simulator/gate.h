#ifndef GATE_H
#define GATE_H

#include "gameobject.h"
#include <fstream>

#define with << std::endl <<

static const char* SAVE_TAG_GATE = "<GATE>";
static const char* SAVE_TAG_NODE = "<NODE>";

static const char* END_SAVE_TAG_GATE = "</GATE>";
static const char* END_SAVE_TAG_NODE = "</NODE>";

enum GateType
{
    GATE_AND,
    GATE_OR,
    GATE_NOT,
    GATE_EMMITTER,
    GATE_RECIEVER,
    GATE_CONST_ACTIVE,
    GATE_CONST_INACTIVE,
    GATE_COLLECTION,
    GATE_TIMER,
    GATE_NULL,
};

class Node;
class GateField;

class Gate : public DragableGameObject
{
public:
    Gate(GateType type, int width, int height, const char* iconLocation = nullptr);
    ~Gate() override;

    virtual void UpdateOutput() = 0;
    virtual void UpdateGraphics(QPainter* painter) override;
    virtual Node* GetClickedNode(int clickX, int clickY) = 0;
    virtual void SaveData(std::ofstream& storage);

    virtual int Left(){return m_layout.left();}
    virtual int Right(){return m_layout.right();}
    virtual int Top(){return m_layout.top();}
    virtual int Bottom(){return m_layout.bottom();}

    GateField* ParentField;

    bool Enabled = true; //todo implement

    GateType GetType() {return m_type;}

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
