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

class Gate : public GameObject
{
public:
    Gate(QWidget* pParent, GateType type, const uint& x, const uint& y, const uint& width, const uint& height, const char* pIconLocation = nullptr);
    ~Gate();

    virtual Gate* Clone() = 0;

    //Generic functions   
    virtual void UpdateOutput() = 0;
    virtual void SaveData(std::ofstream& storage);

    //Node functions
    virtual bool FindNodeWithId(const id& id, Node*& node);
    virtual void AssignNewNodeIds();
    void DetachNodes();
    void GetDisconnectedInputNodes(std::vector<Node*>&);
    void GetDisconnectedOutputNodes(std::vector<Node*>&);

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
    ///Construction/destruction
    Node(Gate* pParent, const uint& x, const uint& y, const NodeType& type, int nodeId = idGenerator());
    ~Node();

    ///Value
    void setValue(bool val);
    bool value();

    ///Linked nodes
    bool LinkNode(Node*& n);
    bool isLinked();
    void DetachNode();

    ///Id
    void genNewID();
    id id() const;

    ///Type
    NodeType type() const;

    Gate* GetParent();//Todo : might be able to delete this when linking reworked

    void SaveData(std::ofstream& storage);

signals:
    void onClicked(Node* pNode);
    void onReleased(Node* pNode);

protected:
    void paintEvent(QPaintEvent* paintEvent) override;
    void mousePressEvent(QMouseEvent* mouseEvent) override;
    void mouseReleaseEvent(QMouseEvent* mouseEvent) override;

private:
    ///Linked properties
    std::vector<Node*> m_linkedNodes;
    bool m_linked = false;
    std::string GetLinkedNodesIds();

    Gate* m_pParent = nullptr;

    //Stored value
    bool m_bValue;

    int m_id;

    NodeType m_nodeType = InputNode;
};


#endif // GATE_H
