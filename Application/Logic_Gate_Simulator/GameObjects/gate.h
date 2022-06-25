#ifndef GATE_H
#define GATE_H

#include "gatetypes.h"
#include "gameobject.h"

#include <QDomDocument>

struct NodeIds {int id; std::vector<int> linkedIds;};
typedef int id;

class Node;
class GateField;
class GateCollection;

class Gate : public GameObject
{
public:
    Gate(GateType type, const int& x, const int& y, const uint& width, const uint& height, const char* pIconLocation = nullptr);
    virtual ~Gate();

    virtual Gate* Clone() = 0;

    //Generic functions   
    virtual void UpdateOutput() = 0;
    virtual void draw(QPainter& painter) override;
    virtual void SaveData(QDomDocument& storage, QDomElement& parentElement);
    virtual Node* checkClickedNodes(const QPoint& mouse);

    ///Position stuff
    virtual void offsetPosition(const int& dX, const int& dY);
    virtual void setPosition(const int& x, const int& y) override;
    QRect geometry() const;

    //Node functions
    virtual void collectLinkInfo(std::vector<NodeIds>& collection);
    virtual bool FindNodeWithId(const id& id, Node*& node);
    virtual void AssignNewNodeIds();
    void DetachNodes();

    //Hierarchy
    virtual void SetParent(GateField* gf);
    virtual void SetParentGateCollection(GateCollection* pGateCollection);
    virtual GateField* GetParent();

    GateType GetType() {return m_type;}

protected:
    virtual void drawNodes(QPainter& painter);

    void SaveGeneralData(QDomElement& element);

    GateType m_type;
    std::vector<Node*> m_nodes;
    GateField* m_pParentField;
    GateCollection* m_pParentGateCollection = nullptr;
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
    Node(Gate* pParent, const uint& offsetX, const uint& offsetY, const NodeType& type, int nodeId = -1);
    virtual ~Node();

    Node* cloneWithoutLinks(Gate* pCloneParent);

    virtual NodeIds linkInfo();

    virtual void draw(QPainter& painter);
    virtual void setPosition(const int& x, const int& y);

    ///Value
    void setValue(bool val);
    bool value();

    ///Linked nodes
    bool LinkNode(Node*& n);
    void DetachNode();

    ///Id
    void genNewID();
    id id() const;

    ///Type
    NodeType type() const;

    ///Offsets
    void setOffsets(const int& offsetX, const int& offsetY);

    Gate* GetParent();

    void SaveData(QDomDocument& storage, QDomElement& parentElement);

private:
    void DetachNode(Node* n);

    Gate* m_pParent = nullptr;

    NodeType m_nodeType = InputNode;

    ///Linked properties
    std::vector<Node*> m_linkedNodes;
    QString GetLinkedNodesIds() const;

    ///Positional offset from parent gate
    int m_offsetX;
    int m_offsetY;

    //Stored value
    bool m_bValue;

    int m_id;
};


#endif // GATE_H
