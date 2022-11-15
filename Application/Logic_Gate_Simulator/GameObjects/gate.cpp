#include "gate.h"
#include "gatecollection.h"
#include "gatefield.h"
#include "textlabel.h"

static int IdIndex = 0;

namespace Settings
{
///Node dimensions
const uint NodeWidth = 15;
const uint NodeHeight = 15;
const uint NodeDrawSize = 5;

///Node drawing
const QColor NodeColor = Qt::black;
const QColor NodeLinkColorActive = Qt::red;
const QColor NodeLinkColorInActive = Qt::black;
const uint NodeLinkWidth = 1;
}

Gate::Gate(GateType type, const int& x, const int& y, const uint& width, const uint& height, const char* pIconLocation) :
    GameObject::GameObject(x, y, width, height, pIconLocation),
    m_type(type),
    m_pParentField(nullptr)
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

        for(TextLabel* pAttachedLabel : m_attachedLabels)
            m_pParentGateCollection->ForgetGate(pAttachedLabel);
    }

    if (m_pParentField)
    {
        m_pParentField->ForgetChild(this);
        m_pParentField->ForgetUpdateRequest(this);

        for(TextLabel* pAttachedLabel : m_attachedLabels)
        {
            m_pParentField->ForgetChild(pAttachedLabel);
            m_pParentField->ForgetUpdateRequest(pAttachedLabel);
        }
    }

    for(TextLabel* pAttachedLabel : m_attachedLabels)
    {
        delete pAttachedLabel;
    }
}

void Gate::setToUpdate()
{
    if(m_pParentField != nullptr)
    {
        m_pParentField->RequestUpdateGate(this);
    }
}

void Gate::draw(QPainter& painter)
{
    GameObject::draw(painter);
    drawNodes(painter);
}

void Gate::SaveData(QDomDocument& storage, QDomElement& parentElement)
{
    QDomElement gateElement = storage.createElement(Settings::GateElement);

    SaveGeneralData(storage, gateElement);

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

bool Gate::hasAttachedLabel(Gate *pGate)
{
    for(Gate* pAttachedLabel : m_attachedLabels)
    {
        if(pGate == pAttachedLabel)
        {
            return true;
        }
    }
    return false;
}

void Gate::addAttachedLabel(TextLabel* pTextLabel, const bool& setPosition, const bool& addToParentGateCollection)
{
    if(pTextLabel)
    {
        pTextLabel->attachGate(this);
        if(setPosition)
            pTextLabel->setPosition(position().x(), position().y() - 20);

        if(m_pParentGateCollection && addToParentGateCollection)
        {
            m_pParentGateCollection->AddGate(pTextLabel);
        }

        if(m_pParentField && m_pParentGateCollection == nullptr && pTextLabel->m_pParentField != m_pParentField)
        {
            m_pParentField->AddGate(pTextLabel, false);
        }

        m_attachedLabels.push_back(pTextLabel);
    }
}

void Gate::removeAttachedLabel(TextLabel *pTextLabel)
{
    for(size_t i = 0; i < m_attachedLabels.size(); i++)
    {
        if(m_attachedLabels[i] == pTextLabel)
        {
            m_attachedLabels.erase(m_attachedLabels.begin() + i);
            return;
        }
    }
}

void Gate::switchAttachedLabels(std::vector<Gate*> gates)
{
    m_attachedLabels.clear();

    for(int id : m_cloneAttachedLabelIds)
    {
        for(Gate* pGate : gates)
        {
            if(pGate->GetType() == GateType::GATE_TEXT_LABEL)
            {
                TextLabel* pTextLabel = dynamic_cast<TextLabel*>(pGate);
                if(pTextLabel->attachId() == id)
                {
                    pTextLabel->genNewAttachId();
                    addAttachedLabel(pTextLabel, false, false);
                    break;
                }
            }
            else if(pGate->GetType() == GateType::GATE_COLLECTION)
            {
                TextLabel* pPotentialAttachedLabel = dynamic_cast<GateCollection*>(pGate)->findTextLabelWithId(id);
                if(pPotentialAttachedLabel)
                {
                    pPotentialAttachedLabel->genNewAttachId();
                    addAttachedLabel(pPotentialAttachedLabel, false, false);
                    break;
                }
            }
        }
    }
    m_cloneAttachedLabelIds.clear();
}

void Gate::offsetPosition(const int& dX, const int& dY)
{
    m_geometry.translate(dX, dY);
    for (Node* n : m_nodes)
    {
        n->setPosition(m_geometry.center().x(), m_geometry.center().y());
    }

    for(TextLabel* pAttachedLabel : m_attachedLabels)
    {
        pAttachedLabel->offsetPosition(dX, dY);
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
    const QPoint originalPosition = position();

    GameObject::setPosition(x, y);
    for (Node* n : m_nodes)
    {
        n->setPosition(x, y);
    }    

    const QPoint difference = position() - originalPosition;
    for(TextLabel* pAttachedLabel : m_attachedLabels)
    {
        pAttachedLabel->offsetPosition(difference.x(), difference.y());
    }

    if(m_pParentGateCollection)
    {
        m_pParentGateCollection->UpdateContaningArea();
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

void Gate::SaveGeneralData(QDomDocument& storage, QDomElement& element)
{
    element.setAttribute(Settings::GateTypeTag, QString::number(m_type));
    element.setAttribute(Settings::GatePosXTag, QString::number(m_geometry.x()));
    element.setAttribute(Settings::GatePosYTag, QString::number(m_geometry.y()));

    QDomElement attachedLabelIds = storage.createElement(Settings::GateAttachedLabelIdsElement);
    for (TextLabel* pTextLabel : m_attachedLabels)
    {
        QDomElement id = storage.createElement(Settings::GateAttachedLabelIdElement);
        id.setAttribute(Settings::NodeIdElement, QString::number(pTextLabel->attachId()));
        attachedLabelIds.appendChild(id);
    }
    element.appendChild(attachedLabelIds);
}

void Gate::baseClone(Gate* pGate)
{
    pGate->m_pParentField = m_pParentField;
    pGate->m_pParentGateCollection = m_pParentGateCollection;

    if(m_nodes.size() != pGate->m_nodes.size())
    {
        Logger::log(LL_Error, "Gate::baseClone - Failed to clone base due to cloned nodes not being same size as nodes");
        return;
    }

    //Clones without the linded nodes... linking comes later.
    for(uint iNode = 0; iNode < m_nodes.size(); iNode++)
    {
        pGate->m_nodes[iNode]->setValue(m_nodes[iNode]->value());
    }

    pGate->m_cloneAttachedLabelIds.clear();
    for(TextLabel* pTextLabel : m_attachedLabels)
    {
        pGate->m_cloneAttachedLabelIds.push_back(pTextLabel->attachId());
    }
}

void Gate::DetachNodes()
{
    for (Node* n : m_nodes)
    {
        n->DetachNode();
    }
}

std::vector<Node*> Gate::getInputNodes()
{
    std::vector<Node*> ret;
    for (Node* n : m_nodes)
    {
        if(n->type() == NodeType::InputNode)
        {
            ret.push_back(n);
        }
    }
    return ret;
}

std::vector<Node*> Gate::getOutputNodes()
{
    std::vector<Node*> ret;
    for (Node* n : m_nodes)
    {
        if(n->type() == NodeType::OutputNode)
        {
            ret.push_back(n);
        }
    }
    return ret;
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
        painter.setPen(QPen(m_bValue ? Settings::NodeLinkColorActive : Settings::NodeLinkColorInActive, Settings::NodeLinkWidth));

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

    //Input node
    else
    {
        m_pParent->setToUpdate();
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
    QDomElement nodeElement = storage.createElement(m_nodeType == InputNode ? Settings::NodeTypeInputElement : Settings::NodeTypeOutputElement);
    nodeElement.setAttribute(Settings::NodeIdElement, QString::number(m_id));

    QDomElement linkedIds = storage.createElement(Settings::NodeLinkedIdsElement);
    for (Node* n : m_linkedNodes)
    {
        QDomElement id = storage.createElement(Settings::NodeLinkedIdElement);
        id.setAttribute(Settings::NodeIdElement, QString::number(n->m_id));
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
