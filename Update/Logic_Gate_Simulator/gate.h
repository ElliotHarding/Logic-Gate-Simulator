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

static int idGenerator()
{
    static int idIndex = 0;
    return idIndex++;
}

struct NodeIds {int id; int linkedId;};
typedef int id;

class Node;
class GateField;

class Gate : public DragableGameObject
{
public:
    Gate(GateType type, int width, int height, const char* iconLocation = nullptr);
    ~Gate() override;

    void DetachNodes();

    virtual void UpdateGraphics(QPainter* painter) override;
    virtual void SaveData(std::ofstream& storage);
    virtual Node* GetClickedNode(int clickX, int clickY);
    virtual bool FindNodeWithId(id _id, Node*& node);
    virtual void AssignNewNodeIds();

    virtual void UpdateOutput() = 0;

    virtual int Left(){return m_layout.left();}
    virtual int Right(){return m_layout.right();}
    virtual int Top(){return m_layout.top();}
    virtual int Bottom(){return m_layout.bottom();}

    GateField* ParentField;

    bool Enabled = true;

    GateType GetType() {return m_type;}

protected:

    void SaveGeneralData(std::ofstream& storage);

    GateType m_type;
    std::vector<Node*> m_nodes;
};


class Node : public GameObject
{
public:
    Node(Gate* parent, int nodeId = idGenerator());
    ~Node() override;

    //Linked node
    void LinkNode(Node*& n);
    void DetachNode();
    Node* GetLinkedNode();

    //returns Gate that node is attached to
    Gate* GetParent();

    //Stored value
    bool value;

    virtual void UpdateGraphics(QPainter* painter) override;

    void SaveData(std::ofstream& storage);

    void GenNewID();

    int m_id;
private:
    Node* m_linkedNode = nullptr;
    Gate* m_parent = nullptr;

    bool m_linked = false;
};


#endif // GATE_H
