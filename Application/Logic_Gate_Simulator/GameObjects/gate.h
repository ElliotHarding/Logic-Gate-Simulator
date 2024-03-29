#ifndef GATE_H
#define GATE_H

#include "gatetypes.h"
#include "gameobject.h"
#include "logger.h"

#include <QDomDocument>

namespace Settings
{
///Gate save element tags
const QString GateElement = "Gate";
const QString GateTypeTag = "type";
const QString GatePosXTag = "posX";
const QString GatePosYTag = "posY";
const QString GateAttachedLabelIdsElement = "AttachedLabelIds";
const QString GateAttachedLabelIdElement = "AttachedLabelId";

///Node save element tags
const QString NodeTypeInputElement = "InputNode";
const QString NodeTypeOutputElement = "OutputNode";
const QString NodeIdElement = "id";
const QString NodeLinkedIdsElement = "LinkedIds";
const QString NodeLinkedIdElement = "LinkedNode";
}

struct NodeIds {int id; std::vector<int> linkedIds;};
typedef int id;

class Node;
class GateField;
class GateCollection;
class TextLabel;

class Gate : public GameObject
{
public:
    Gate(GateType type, const int& x, const int& y, const uint& width, const uint& height, const char* pIconLocation = nullptr);
    virtual ~Gate();

    virtual Gate* clone() = 0;

    //Generic functions   
    virtual void updateOutput() = 0;
    virtual void setToUpdate();
    virtual void draw(QPainter& painter) override;
    virtual void saveData(QDomDocument& storage, QDomElement& parentElement);
    virtual Node* checkClickedNodes(const QPoint& mouse);

    //TextLabel attach functions
    bool hasAttachedLabel(Gate* pGate);
    void addAttachedLabel(TextLabel* pTextLabel, const bool& setPosition = true, const bool& addToParentGateCollection = true);
    void removeAttachedLabel(TextLabel* pTextLabel);
    virtual void switchAttachedLabels(std::vector<Gate*> gates);

    ///Position stuff
    virtual void offsetPosition(const int& dX, const int& dY);
    virtual void setPosition(const int& x, const int& y) override;
    QRect geometry() const;

    //Node functions
    virtual void collectLinkInfo(std::vector<NodeIds>& collection);
    virtual bool findNodeWithId(const id& id, Node*& node);
    virtual void assignNewNodeIds();
    void detachNodes();
    virtual std::vector<Node*> getInputNodes();
    virtual std::vector<Node*> getOutputNodes();

    //Hierarchy
    virtual void setParent(GateField* gf);
    virtual void setParentGateCollection(GateCollection* pGateCollection);
    virtual GateField* getParent();

    GateType getType() {return m_type;}

protected:
    virtual void drawNodes(QPainter& painter);

    void saveGeneralData(QDomDocument& storage, QDomElement& element);

    void baseClone(Gate* pGate);

    GateType m_type;
    std::vector<Node*> m_nodes;
    GateField* m_pParentField;
    GateCollection* m_pParentGateCollection = nullptr;
    std::vector<TextLabel*> m_attachedLabels;
    std::vector<int> m_cloneAttachedLabelIds;
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
    bool linkNode(Node*& n);
    void detachNode();

    ///Id
    void genNewID();
    id id() const;

    ///Type
    NodeType type() const;

    ///Offsets
    void setOffsets(const int& offsetX, const int& offsetY);

    Gate* getParent();

    void saveData(QDomDocument& storage, QDomElement& parentElement);

private:
    void detachNode(Node* n);

    Gate* m_pParent = nullptr;

    NodeType m_nodeType = InputNode;

    ///Linked properties
    std::vector<Node*> m_linkedNodes;

    ///Positional offset from parent gate
    int m_offsetX;
    int m_offsetY;

    //Stored value
    bool m_bValue;

    int m_id;
};


#endif // GATE_H
