#include "gatefpga.h"
#include "gatefield.h"

namespace Settings
{
const uint GateFpgaWidth = 100;
const uint GateFpgaHeight = 100;
const uint GateFpgaBorderWidth = 10;

const int InputNodesXpos = -5;
const int OutputNodesXpos = GateFpgaWidth + 5;
const int GapBetweenNodesY = 11;

const QColor BorderColor = Qt::darkGray;
const QColor EditButtonColor = Qt::lightGray;

const QPen BorderPen(Settings::BorderColor, Settings::GateFpgaBorderWidth);

const uint EditButtonSize = 15;
}

GateFPGA::GateFPGA(const int& x, const int& y) :
    Gate::Gate(GATE_FPGA, x, y, Settings::GateFpgaWidth, Settings::GateFpgaHeight)
{
    updateEditButtonGeometry();

    for (size_t x = 0; x < 10; x++)
    {
        m_inputNodes.push_back(new Node(this, Settings::InputNodesXpos, x * Settings::GapBetweenNodesY, InputNode));
        m_nodes.push_back(m_inputNodes[x]);

        m_outputNodes.push_back(new Node(this, Settings::OutputNodesXpos, x * Settings::GapBetweenNodesY, OutputNode));
        m_nodes.push_back(m_outputNodes[x]);
    }
}

GateFPGA::GateFPGA(std::vector<Node*>& inputNodesToCopy, std::vector<Node*>& outputNodesToCopy, const int &x, const int &y) :
    Gate::Gate(GATE_FPGA, x, y, Settings::GateFpgaWidth, Settings::GateFpgaHeight)
{
    updateEditButtonGeometry();

    for(Node* inputNode : inputNodesToCopy)
    {
        Node* newInputNode = inputNode->cloneWithoutLinks(this);
        m_inputNodes.push_back(newInputNode);
        m_nodes.push_back(newInputNode);
    }

    for(Node* outputNode : outputNodesToCopy)
    {
        Node* newOutputNode = outputNode->cloneWithoutLinks(this);
        m_outputNodes.push_back(newOutputNode);
        m_nodes.push_back(newOutputNode);
    }
}

GateFPGA::~GateFPGA()
{
    m_inputNodes.clear();
    m_outputNodes.clear();
}

void GateFPGA::draw(QPainter& painter)
{
    //Draw gate
    painter.setPen(Settings::BorderPen);
    painter.drawRect(m_geometry);

    drawNodes(painter);

    painter.fillRect(m_editButtonRect, QBrush(Settings::EditButtonColor));
}

GameObject* GateFPGA::checkClicked(const QPoint& mouse)
{
    if(m_pParentField->GetCurrentClickMode() == CLICK_DEFAULT)
    {
        if(m_editButtonRect.contains(mouse))
        {
            OpenEditor();
            return this;
        }
        return nullptr;
    }

    return GameObject::checkClicked(mouse);
}

void GateFPGA::SaveData(std::ofstream& storage)
{
    SaveGeneralData(storage);

    //Add node information
    for (Node* n : m_nodes)
    {
        n->SaveData(storage);
    }

    storage << END_SAVE_TAG_GATE << std::endl;
}

void GateFPGA::UpdateOutput()
{
    //Todo : do it
}

Gate* GateFPGA::Clone()
{
    GateFPGA* clone = new GateFPGA(m_inputNodes, m_outputNodes, m_geometry.x(), m_geometry.y());
    return clone;
}

void GateFPGA::offsetPosition(const int &dX, const int &dY)
{
    Gate::offsetPosition(dX, dY);
    updateEditButtonGeometry();
}

void GateFPGA::setPosition(const int &x, const int &y)
{
    Gate::setPosition(x, y);
    updateEditButtonGeometry();
}

void GateFPGA::OpenEditor()
{
    //Todo : check if GateFPGA is in a GateCollection. Does it have m_pParentField?
    m_pParentField->editFPGA(this);
}

void GateFPGA::setInputs(const uint& numInputs)
{
    const uint currentInputs = m_inputNodes.size();

    if(currentInputs == numInputs)
    {
        return;
    }

    if(currentInputs > numInputs)
    {
        for(uint i = numInputs; i < m_inputNodes.size();)
        {
            Node* n = m_inputNodes[i];
            for(uint iAllNodes = 0; iAllNodes < m_nodes.size(); iAllNodes++)
            {
                if(n == m_nodes[iAllNodes])
                {
                    m_nodes.erase(m_nodes.begin() + iAllNodes);
                    break;
                }
            }
            m_inputNodes.erase(m_inputNodes.begin() + i);
            delete n;
        }
        return;
    }

    //numInputs > currentInputs
    for(uint i = currentInputs; i < numInputs; i++)
    {
        m_inputNodes.push_back(new Node(this, Settings::InputNodesXpos, i * Settings::GapBetweenNodesY, InputNode));
        m_nodes.push_back(m_inputNodes[i]);
    }
}

void GateFPGA::setOutputs(const uint& numOutputs)
{
    const uint currentOutputs = m_outputNodes.size();

    if(currentOutputs == numOutputs)
    {
        return;
    }

    if(currentOutputs > numOutputs)
    {

        return;
    }

    //numOutputs > currentOutputs
}

void GateFPGA::updateEditButtonGeometry()
{
    m_editButtonRect = QRect(m_geometry.right(), m_geometry.top() - Settings::EditButtonSize, Settings::EditButtonSize, Settings::EditButtonSize);
}
