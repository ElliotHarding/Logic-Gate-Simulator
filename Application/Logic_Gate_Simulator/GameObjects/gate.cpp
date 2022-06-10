#include "gate.h"
#include "gatecollection.h"

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

Gate::Gate(GateType type, const uint& x, const uint& y, const uint& width, const uint& height, const char* pIconLocation) :
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

    m_pParentField = nullptr;
}

void Gate::SaveData(std::ofstream &storage)
{
    SaveGeneralData(storage);

    //Add node information
    for (Node* n : m_nodes)
    {
        n->SaveData(storage);
    }

    storage << END_SAVE_TAG_GATE << std::endl;
}

void Gate::setPosition(const int &x, const int &y)
{
    GameObject::setPosition(x, y);
    for (Node* n : m_nodes)
    {
        n->setPosition(x, y);
    }

}

QPoint Gate::getPosition()
{
    return m_geometry.topLeft();
}

//Todo : why is there a *&
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

GateField *Gate::GetParent()
{
    return m_pParentField;
}

void Gate::GetDisconnectedInputNodes(std::vector<Node*>& nodes)
{
    for (Node* n : m_nodes)
    {
        if (n->type() == NodeType::InputNode && !n->isLinked())
        {
            nodes.push_back(n);
        }
    }

}

void Gate::GetDisconnectedOutputNodes(std::vector<Node*>& nodes)
{
    for (Node* n : m_nodes)
    {
        if (n->type() == NodeType::OutputNode && !n->isLinked())
        {
            nodes.push_back(n);
        }
    }
}

void Gate::SaveGeneralData(std::ofstream &storage)
{
    //Add general gate info
    storage << SAVE_TAG_GATE
            with std::to_string(m_type)
            with std::to_string(m_bEnabled)
            with std::to_string(m_geometry.x())
            with std::to_string(m_geometry.y())
            << std::endl;
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
    GameObject::GameObject(pParent->getPosition().x() + offsetX, pParent->getPosition().y() + offsetY, Settings::NodeWidth, Settings::NodeHeight),
    m_bValue(0),
    m_pParent(pParent),
    m_id(nodeId),
    m_nodeType(type),
    m_offsetX(offsetX),
    m_offsetY(offsetY)
{
}

Node::~Node()
{
    m_pParent = nullptr;

    DetachNode();
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
    else
    {
        //Todo : check if this if statement is needed
        //m_id is > -1 to check incase this node is being deleted
        if(m_id > -1)
            m_pParent->UpdateOutput();
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

void Node::SaveData(std::ofstream &storage)
{
    std::string linkedNodeIds = GetLinkedNodesIds();

    storage << SAVE_TAG_NODE
            with std::to_string(m_id)
            with linkedNodeIds
            with END_SAVE_TAG_NODE
            << std::endl;
}

void Node::genNewID()
{
    m_id = idGenerator();
}

NodeType Node::type() const
{
    return m_nodeType;
}

id Node::id() const
{
    return m_id;
}

std::string Node::GetLinkedNodesIds()
{
    if(m_linkedNodes.size() == 0)
        return "-1";

    std::string ids = "";
    const std::string next = ",";
    for (Node* n : m_linkedNodes)
    {
        ids += std::to_string(n->m_id) + next;
    }
    return ids;
}

//Todo : why *&
bool Node::LinkNode(Node*& n)
{
    //Check if already linked
    for (Node* alreadyLinkedNode : m_linkedNodes)
    {
        if(&alreadyLinkedNode == &n)
        {
            return false;
        }
    }

    m_linkedNodes.push_back(n);
    m_pParent->UpdateOutput();//Todo : check if only when input node is needed

    return true;
}

bool Node::isLinked()
{
    return !m_linkedNodes.empty();
}

void Node::DetachNode()
{
    for (Node* n : m_linkedNodes)
    {
        for(size_t index = 0; index < n->m_linkedNodes.size(); index++)
        {
            if(this->m_id == n->m_linkedNodes[index]->m_id)
            {
                n->m_linkedNodes[index] = nullptr;
                n->m_linkedNodes.erase(n->m_linkedNodes.begin() + index);
                break;
            }
        }

        if(m_nodeType == OutputNode)
        {
            //TODO CHECK ~ MIGHT BE NEEDED, BUT TESTING REQUIRED REMOVEVAL
            //TECHNICALLY UPDATED FUNCITON IS CALLED AFTER THIS...
            n->setValue(0);
        }

        n = nullptr;
    }
    m_linkedNodes.clear();
}
