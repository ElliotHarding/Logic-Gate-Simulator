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
    Gate(GateType type, const int& x, const int& y, const uint& width, const uint& height, const char* pIconLocation = nullptr);
    virtual ~Gate();

    virtual Gate* Clone() = 0;

    //Generic functions   
    virtual void UpdateOutput() = 0;
    virtual void draw(QPainter& painter) override;
    virtual void SaveData(std::ofstream& storage);
    virtual GameObject* checkClicked(const QPoint& mouse) override;

    ///Position stuff
    virtual void offsetPosition(const int& dX, const int& dY);
    virtual void setPosition(const int& x, const int& y) override;
    QRect geometry() const;

    //Node functions
    virtual bool FindNodeWithId(const id& id, Node*& node);
    virtual void AssignNewNodeIds();
    void DetachNodes();
    void GetDisconnectedInputNodes(std::vector<Node*>&);
    void GetDisconnectedOutputNodes(std::vector<Node*>&);

    //Hierarchy
    virtual void SetParent(GateField* gf);
    virtual GateField* GetParent();

    GateType GetType() {return m_type;}

protected:
    virtual void drawNodes(QPainter& painter);

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
    Node(Gate* pParent, const uint& offsetX, const uint& offsetY, const NodeType& type, int nodeId = idGenerator());
    virtual ~Node();

    virtual void draw(QPainter& painter);
    virtual void setPosition(const int& x, const int& y);

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

    Gate* GetParent();

    void SaveData(std::ofstream& storage);

private:
    void DetachNode(Node* n);

    ///Linked properties
    std::vector<Node*> m_linkedNodes;
    std::string GetLinkedNodesIds();

    Gate* m_pParent = nullptr;

    ///Positional offset from parent gate
    const int m_offsetX;
    const int m_offsetY;

    //Stored value
    bool m_bValue;

    int m_id;

    NodeType m_nodeType = InputNode;
};


#endif // GATE_H
