#include "gate.h"
#include "gatecollection.h"

static int IdIndex = 0;

namespace Settings
{
///Node dimensions
const uint NodeWidth = 15;
const uint NodeHeight = 15;
const uint NodeDrawSize = 5;

///Node drawing
const QColor NodeColor = Qt::black;
const QColor NodeLinkColor = Qt::black;//Todo : make it red if active
const uint NodeLinkWidth = 1;
}

#define with << std::endl <<

Gate::Gate(GateType type, const int& x, const int& y, const uint& width, const uint& height, const char* pIconLocation) :
    GameObject::GameObject(x, y, width, height, pIconLocation),
    m_type(type)
{
}

Gate::~Gate()
{
    DetachNodes();

    for (size_t index = 0; index < m_nodes.size(); index++)
    {
        delete m_nodes[index];
    }
    m_nodes.clear();

    if(m_pParentGateCollection)
    {
        m_pParentGateCollection->ForgetGate(this);
    }
}

void Gate::draw(QPainter& painter)
{
    GameObject::draw(painter);
    drawNodes(painter);
}

void Gate::SaveData(QDomDocument& storage, QDomElement& parentElement)
{
    QDomElement gateElement = storage.createElement("Gate");

    SaveGeneralData(gateElement);

    //Add node information
    for (Node* n : m_nodes)
    {
        n->SaveData(storage, gateElement);
    }

    parentElement.appendChild(gateElement);
}

Node* Gate::checkClickedNodes(const QPoint& mouse)
{
    for (Node* n : m_nodes)
    {
        GameObject* pPossibleClickedNode = n->checkClicked(mouse);
        if(pPossibleClickedNode != nullptr && dynamic_cast<Node*>(pPossibleClickedNode))
        {
            return dynamic_cast<Node*>(pPossibleClickedNode);
        }
    }
    return nullptr;
}

void Gate::offsetPosition(const int& dX, const int& dY)
{
    m_geometry.translate(dX, dY);
    for (Node* n : m_nodes)
    {
        n->setPosition(m_geometry.center().x(), m_geometry.center().y());
    }
}

void Gate::drawNodes(QPainter& painter)
{
    for(Node* pNode : m_nodes)
    {
        pNode->draw(painter);
    }
}

void Gate::setPosition(const int &x, const int &y)
{
    GameObject::setPosition(x, y);
    for (Node* n : m_nodes)
    {
        n->setPosition(x, y);
    }
}

QRect Gate::geometry() const
{
    return m_geometry;
}

void Gate::collectLinkInfo(std::vector<NodeIds>& collection)
{
    for(Node* n : m_nodes)
    {
        collection.push_back(n->linkInfo());
    }
}

bool Gate::FindNodeWithId(const id& id, Node*& node)
{
    for (size_t index = 0; index < m_nodes.size(); index++)
    {
        if(m_nodes[index]->id() == id)
        {
            node = &*m_nodes[index];
            return true;
        }
    }
    return false;
}

void Gate::AssignNewNodeIds()
{
    for (Node* n : m_nodes)
    {
        n->genNewID();
    }
}

void Gate::SetParent(GateField* gf)
{
    m_pParentField = gf;
}

void Gate::SetParentGateCollection(GateCollection *pGateCollection)
{
    m_pParentGateCollection = pGateCollection;
}

GateField *Gate::GetParent()
{
    return m_pParentField;
}

void Gate::SaveGeneralData(QDomElement& element)
{
    element.setAttribute("type", QString::number(m_type));
    element.setAttribute("posX", QString::number(m_geometry.x()));
    element.setAttribute("posY", QString::number(m_geometry.y()));
}

void Gate::DetachNodes()
{
    for (Node* n : m_nodes)
    {
        n->DetachNode();
    }
}

//
// -- NODE IMPLEMENTATION --
//

Node::Node(Gate* pParent, const uint& offsetX, const uint& offsetY, const NodeType& type, int nodeId) :
    GameObject::GameObject(pParent->position().x() + offsetX, pParent->position().y() + offsetY, Settings::NodeWidth, Settings::NodeHeight),
    m_pParent(pParent),
    m_nodeType(type),
    m_offsetX(offsetX),
    m_offsetY(offsetY),
    m_bValue(0),
    m_id(nodeId)
{
    if(nodeId == -1)
    {
        m_id = IdIndex++;
    }
}

Node::~Node()
{
    DetachNode();
}

Node* Node::cloneWithoutLinks(Gate* pCloneParent)
{
    Node* clone = new Node(pCloneParent, m_offsetX, m_offsetY, m_nodeType, m_id);
    return clone;
}

NodeIds Node::linkInfo()
{
    NodeIds info;
    info.id = m_id;

    for (Node* n : m_linkedNodes)
    {
        info.linkedIds.push_back(n->id());
    }

    return info;
}

void Node::draw(QPainter& painter)
{
    //if linked draw line between node and linked nodes
    if(m_nodeType == OutputNode && !m_linkedNodes.empty())
    {
        painter.setPen(QPen(Settings::NodeLinkColor, Settings::NodeLinkWidth));

        for (Node* n : m_linkedNodes)
        {
            //Find longest delta (x or y)
            const QPoint n1 = m_geometry.center();
            const QPoint n2 = n->m_geometry.center();

            QPoint midpoint;

            //Check X is longest delta
            if(abs(n1.x() - n2.x()) > abs(n1.y() - n2.y()))
                midpoint = QPoint(n1.x(), n2.y());

            else //Y is longest delta
                midpoint = QPoint(n2.x(), n1.y());

            painter.drawLine(n1, midpoint);
            painter.drawLine(n2, midpoint);
        }
    }

    //Draw node
    painter.setPen(QPen(Settings::NodeColor, Settings::NodeDrawSize));
    painter.drawEllipse(m_geometry.center(), Settings::NodeDrawSize, Settings::NodeDrawSize);
}

void Node::setPosition(const int &x, const int &y)
{
    GameObject::setPosition(x + m_offsetX, y + m_offsetY);
}

void Node::setValue(bool val)
{
    m_bValue = val;    

    if(m_nodeType == OutputNode)
    {
         for(Node* n : m_linkedNodes)
         {
            n->setValue(m_bValue);
         }
    }
}

bool Node::value()
{
    return m_bValue;
}

Gate* Node::GetParent()
{
    return m_pParent;
}

void Node::SaveData(QDomDocument& storage, QDomElement& parentElement)
{
    QDomElement nodeElement = storage.createElement(m_nodeType == InputNode ? "InputNode" : "OutputNode");
    nodeElement.setAttribute("id", QString::number(m_id));

    QDomElement linkedIds = storage.createElement("LinkedIds");
    for (Node* n : m_linkedNodes)
    {
        QDomElement id = storage.createElement(QString::number(n->m_id));
        linkedIds.appendChild(id);
    }
    nodeElement.appendChild(linkedIds);

    parentElement.appendChild(nodeElement);
}

void Node::genNewID()
{
    m_id = IdIndex++;
}

NodeType Node::type() const
{
    return m_nodeType;
}

void Node::setOffsets(const int &offsetX, const int &offsetY)
{
    m_offsetX = offsetX;
    m_offsetY = offsetY;
}

id Node::id() const
{
    return m_id;
}

bool Node::LinkNode(Node*& n)
{
    if(n->type() == type())
    {
        return false;
    }

    //Check if already linked
    for (Node* alreadyLinkedNode : m_linkedNodes)
    {
        if(alreadyLinkedNode == n)
        {
            return false;
        }
    }

    m_linkedNodes.push_back(n);

    if(m_nodeType == InputNode)
    {
        bool value = false;
        for(Node* n : m_linkedNodes)
        {
            value |= n->value();
        }
        setValue(value);
    }

    return true;
}

void Node::DetachNode()
{
    for (Node* n : m_linkedNodes)
    {
        n->DetachNode(this);
    }
    m_linkedNodes.clear();
}

void Node::DetachNode(Node *n)
{
    for (uint i = 0; i < m_linkedNodes.size(); i++)
    {
        if(m_linkedNodes[i] == n)
        {
            m_linkedNodes.erase(m_linkedNodes.begin() + i);
            break;
        }
    }

    //Check remaning attached nodes to know value
    if(m_nodeType == InputNode)
    {
        bool value = false;
        for(Node* n : m_linkedNodes)
        {
            value |= n->value();
        }
        setValue(value);
    }
}
