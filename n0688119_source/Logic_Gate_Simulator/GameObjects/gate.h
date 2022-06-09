#ifndef GATE_H
#define GATE_H

#include "gatetypes.h"
#include "gameobject.h"
#include <fstream>

#define with << std::endl <<

static const std::string SAVE_TAG_GATE = "<GATE>";
static const std::string SAVE_TAG_NODE = "<NODE>";
static const std::string END_SAVE_TAG_GATE = "</GATE>";
static const std::string END_SAVE_TAG_NODE = "</NODE>";

static int idGenerator()
{
    static int idIndex = 0;
    return idIndex++;
}

struct NodeIds {int id; std::vector<int> linkedIds;};
typedef int id;

class Node;
class GateField;

class Gate : public DragableGameObject
{
public:
    Gate(GateType type, int width, int height, const char* iconLocation = nullptr);
    ~Gate() override;

    virtual Gate* Clone() = 0;

    //Generic functions
    virtual void UpdateGraphics(QPainter* painter) override;    
    virtual void UpdateOutput() = 0;
    virtual void SaveData(std::ofstream& storage);
    virtual bool DeleteClick(int clickX, int clickY);

    //Node functions
    virtual Node* GetClickedNode(int clickX, int clickY);
    virtual bool FindNodeWithId(id _id, Node*& node);
    virtual void AssignNewNodeIds();
    void DetachNodes();
    virtual bool HasConnectedInputNodes();
    virtual bool HasConnectedOutputNodes();
    void GetDisconnectedInputNodes(std::vector<Node*>&);
    void GetDisconnectedOutputNodes(std::vector<Node*>&);

    //Geometry
    virtual int Left(){return m_layout.left();}
    virtual int Right(){return m_layout.right();}
    virtual int Top(){return m_layout.top();}
    virtual int Bottom(){return m_layout.bottom();}

    //Hierarchy
    virtual void SetParent(GateField* gf);
    virtual GateField* GetParent();

    bool Enabled = true;

    GateType GetType() {return m_type;}

protected:

    void SaveGeneralData(std::ofstream& storage);

    GateType m_type;
    std::vector<Node*> m_nodes;
    GateField* m_pParentField;
};

enum NodeType
{
    OutputNode,
    InputNode //Node that inputs something into gate
};

class Node : public GameObject
{
public:
    Node(Gate* parent, NodeType type, int nodeId = idGenerator());
    ~Node() override;

    void SetValue(bool val);
    bool GetValue();

    //Linked nodes
    bool LinkNode(Node*& n);
    void DetachNode();

    //returns Gate that node is attached to
    Gate* GetParent();

    virtual void UpdateGraphics(QPainter* painter) override;

    void SaveData(std::ofstream& storage);

    void GenNewID();

    bool IsLinked();

    int m_id;
    NodeType m_nodeType = InputNode;

private:
    std::vector<Node*> m_linkedNodes;
    Gate* m_parent = nullptr;

    std::string GetLinkedNodesIds();

    //Stored value
    bool m_bValue;

    bool m_linked = false;
};


#endif // GATE_H
