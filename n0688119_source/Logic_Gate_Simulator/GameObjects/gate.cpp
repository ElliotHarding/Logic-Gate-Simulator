#include "gate.h"
#include "gatecollection.h"

#define with << std::endl <<

Gate::Gate(GateType type, int width, int height, const char* iconLocation) :
    DragableGameObject::DragableGameObject(width, height, iconLocation),
    m_type(type)
{
}

Gate::~Gate()
{
    for (size_t index = 0; index < m_nodes.size(); index++)
    {
        m_nodes[index] = nullptr;
    }
    m_nodes.clear();

    m_pParentField = nullptr;
}

void Gate::UpdateGraphics(QPainter* painter)
{
    GameObject::UpdateGraphics(painter);

    for (Node* n : m_nodes)
    {
        n->UpdateGraphics(painter);
    }
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

Node *Gate::GetClickedNode(int clickX, int clickY)
{
    for (Node* n : m_nodes)
    {
        if(n->UpdateClicked(clickX, clickY))
            return n;
    }
    return nullptr;
}

bool Gate::FindNodeWithId(id _id, Node*& node)
{
    for (size_t index = 0; index < m_nodes.size(); index++)
    {
        if(m_nodes[index]->m_id == _id)
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
        n->GenNewID();
    }
}

bool Gate::DeleteClick(int clickX, int clickY)
{
    return UpdateClicked(clickX, clickY);
}

void Gate::SetParent(GateField* gf)
{
    m_pParentField = gf;
}

GateField *Gate::GetParent()
{
    return m_pParentField;
}

bool Gate::HasConnectedInputNodes()
{
    for (Node* n : m_nodes)
    {
        if (n->m_nodeType == NodeType::InputNode && n->IsLinked())
        {
            return true;
        }
    }

    return false;
}

bool Gate::HasConnectedOutputNodes()
{
    for (Node* n : m_nodes)
    {
        if (n->m_nodeType == NodeType::OutputNode && n->IsLinked())
        {
            return true;
        }
    }

    return false;
}

void Gate::GetDisconnectedInputNodes(std::vector<Node*>& nodes)
{
    for (Node* n : m_nodes)
    {
        if (n->m_nodeType == NodeType::InputNode && !n->IsLinked())
        {
            nodes.push_back(n);
        }
    }

}

void Gate::GetDisconnectedOutputNodes(std::vector<Node*>& nodes)
{
    for (Node* n : m_nodes)
    {
        if (n->m_nodeType == NodeType::OutputNode && !n->IsLinked())
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
            with std::to_string(Enabled)
            with std::to_string(GetPosition().x())
            with std::to_string(GetPosition().y())
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

Node::Node(Gate *parent, NodeType type, int id) :
    GameObject::GameObject(15,15),
    m_bValue(0),
    m_parent(parent),
    m_id(id),
    m_nodeType(type)
{
}

Node::~Node()
{
    m_parent = nullptr;

    DetachNode();
}

void Node::SetValue(bool val)
{
    m_bValue = val;    

    if(m_nodeType == OutputNode)
    {
         for(Node* n : m_linkedNodes)
         {
            n->SetValue(m_bValue);
            /*if(n->GetParent())
            {
                n->GetParent()->UpdateOutput();
            }*/
         }
    }
    else
    {
        //Having this here means can't update any input nodes in any UpdateOutput() functions
        //otherwise circular code.

        //So when gatefeild is being deleted, m_parent causes crash cuz not deleted yet
        //think solution would be to implement a clone function for nodes, but it's alot of effort
        //just for this fix, when the solution of checking if m_id > 0 seems to work

        //m_id is > -1 to check incase this node is being deleted
        if(m_id > -1)
            m_parent->UpdateOutput();
    }
}

bool Node::GetValue()
{
    return m_bValue;
}

Gate* Node::GetParent()
{
    return m_parent;
}

void Node::UpdateGraphics(QPainter* painter)
{
    //if linked draw line between node and linked nodes
    if(m_nodeType == OutputNode)
    {
        painter->setPen(QPen(Qt::black, 1));

        for (Node* n : m_linkedNodes)
        {
            //Find longest delta (x or y)
            const QPoint n1 = GetPosition();
            const QPoint n2 = n->GetPosition();
            QPoint midpoint;

            //Check X is longest delta
            if(abs(n1.x() - n2.x()) > abs(n1.y() - n2.y()))
                midpoint = QPoint(n1.x(), n2.y());

            else //Y is longest delta
                midpoint = QPoint(n2.x(), n1.y());

            painter->drawLine(n1, midpoint);
            painter->drawLine(n2, midpoint);
        }
    }

    //Draw node
    painter->setPen(QPen(Qt::black,5));
    QPoint position(GetPosition());
    painter->drawEllipse(position,5,5);
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

void Node::GenNewID()
{
    m_id = idGenerator();
}

bool Node::IsLinked()
{
    return m_linked;
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

    m_linked = true;
    m_linkedNodes.push_back(n);
    m_parent->UpdateOutput();

    return true;
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
            n->SetValue(0);
        }

        n = nullptr;
    }
    m_linkedNodes.clear();
    m_linked = false;
}