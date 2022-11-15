#include "gatefpga.h"
#include "gatefield.h"

#include <QScriptEngine>

namespace Settings
{
const uint GateFpgaWidth = 100;

///Node stuff
const int InputNodesXpos = -5 - GateFpgaWidth/2;
const int OutputNodesXpos = GateFpgaWidth/2 + 5;
const int GapBetweenNodesY = 25;
const uint DefaultNumberOfNodes = 5;

///Border stuff
const QColor BorderColor = Qt::darkGray;
const uint GateFpgaBorderWidth = 10;
const QPen BorderPen(Settings::BorderColor, Settings::GateFpgaBorderWidth);
}

GateFPGA::GateFPGA(const int& x, const int& y) :
    Gate::Gate(GATE_FPGA, x, y, Settings::GateFpgaWidth, Settings::DefaultNumberOfNodes * Settings::GapBetweenNodesY),
    m_script("var output1 = true, output2 = true, output3 = true, output4 = true, output5 = true;")
{
    for (size_t x = 0; x < Settings::DefaultNumberOfNodes; x++)
    {
        m_inputNodes.push_back(new Node(this, Settings::InputNodesXpos, x * Settings::GapBetweenNodesY - ((Settings::DefaultNumberOfNodes/2) * Settings::GapBetweenNodesY), InputNode));
        m_nodes.push_back(m_inputNodes[x]);

        m_outputNodes.push_back(new Node(this, Settings::OutputNodesXpos, x * Settings::GapBetweenNodesY - ((Settings::DefaultNumberOfNodes/2) * Settings::GapBetweenNodesY), OutputNode));
        m_nodes.push_back(m_outputNodes[x]);
    }
}

GateFPGA::GateFPGA(std::vector<Node*>& inputNodesToCopy, std::vector<Node*>& outputNodesToCopy, const QString& script, const int &x, const int &y) :
    Gate::Gate(GATE_FPGA, x, y, Settings::GateFpgaWidth, inputNodesToCopy.size() > outputNodesToCopy.size() ? inputNodesToCopy.size() * Settings::GapBetweenNodesY : outputNodesToCopy.size() * Settings::GapBetweenNodesY),
    m_script(script)
{
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

GateFPGA::GateFPGA(const QString& script, std::vector<NodeIds>& inputNodeInfo, std::vector<NodeIds>& outputNodeInfo, const int &x, const int &y) :
    Gate::Gate(GATE_FPGA, x, y, Settings::GateFpgaWidth, inputNodeInfo.size() > outputNodeInfo.size() ? inputNodeInfo.size() * Settings::GapBetweenNodesY : outputNodeInfo.size() * Settings::GapBetweenNodesY),
    m_script(script)
{
    const int yOffset = -(inputNodeInfo.size() > outputNodeInfo.size() ? inputNodeInfo.size()/2 * Settings::GapBetweenNodesY : outputNodeInfo.size()/2 * Settings::GapBetweenNodesY);
    for(uint i = 0; i < inputNodeInfo.size(); i++)
    {
        Node* newInputNode = new Node(this, Settings::InputNodesXpos, i * Settings::GapBetweenNodesY + yOffset, InputNode, inputNodeInfo[i].id);
        m_inputNodes.push_back(newInputNode);
        m_nodes.push_back(newInputNode);
    }
    for(uint i = 0; i < outputNodeInfo.size(); i++)
    {
        Node* newOutputNode = new Node(this, Settings::OutputNodesXpos, i * Settings::GapBetweenNodesY + yOffset, OutputNode, outputNodeInfo[i].id);
        m_outputNodes.push_back(newOutputNode);
        m_nodes.push_back(newOutputNode);
    }
}

GateFPGA::~GateFPGA()
{
    //Actual nodes are deleted via Gate destructor stored in m_nodes
    m_inputNodes.clear();
    m_outputNodes.clear();
}

void GateFPGA::draw(QPainter& painter)
{
    //Draw gate
    painter.setPen(Settings::BorderPen);
    painter.drawRect(m_geometry);

    drawNodes(painter);
}

void GateFPGA::SaveData(QDomDocument& storage, QDomElement& parentElement)
{
    QDomElement gateElement = storage.createElement(Settings::GateElement);

    SaveGeneralData(storage, gateElement);

    gateElement.setAttribute(Settings::FPGAGateScriptElement, m_script);

    for(Node* inputNode : m_inputNodes)
    {
        inputNode->SaveData(storage, gateElement);
    }

    for(Node* outputNode : m_outputNodes)
    {
        outputNode->SaveData(storage, gateElement);
    }

    parentElement.appendChild(gateElement);
}

void GateFPGA::UpdateOutput()
{
    QScriptEngine engine;
    QScriptContext* pContext = engine.pushContext();

    for(uint i = 0; i < m_inputNodes.size(); i++)
    {
        pContext->activationObject().setProperty("input" + QString::number(i+1), m_inputNodes[i]->value());
    }

    for(uint i = 0; i < m_outputNodes.size(); i++)
    {
        pContext->activationObject().setProperty("output" + QString::number(i+1), false);
    }

    engine.evaluate(m_script);

    for(uint i = 0; i < m_outputNodes.size(); i++)
    {
        m_outputNodes[i]->setValue(pContext->activationObject().property("output" + QString::number(i+1)).toBool());
    }
}

Gate* GateFPGA::Clone()
{
    GateFPGA* clone = new GateFPGA(m_inputNodes, m_outputNodes, m_script, position().x(), position().y());
    Gate::baseClone(clone);
    return clone;
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
            eraseNodeFromAllNodes(n);
            m_inputNodes.erase(m_inputNodes.begin() + i);
            delete n;
        }
    }

    else //numInputs > currentInputs
    {
        for(uint i = currentInputs; i < numInputs; i++)
        {
            m_inputNodes.push_back(new Node(this, Settings::InputNodesXpos, i * Settings::GapBetweenNodesY, InputNode));
            m_nodes.push_back(m_inputNodes[i]);
        }
    }
    updateGeometryBasedOnNodes();
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
        for(uint i = numOutputs; i < m_outputNodes.size();)
        {
            Node* n = m_outputNodes[i];
            eraseNodeFromAllNodes(n);
            m_outputNodes.erase(m_outputNodes.begin() + i);
            delete n;
        }
    }

    else //numOutputs > currentOutputs
    {
        for(uint i = currentOutputs; i < numOutputs; i++)
        {
            m_outputNodes.push_back(new Node(this, Settings::OutputNodesXpos, i * Settings::GapBetweenNodesY, OutputNode));
            m_nodes.push_back(m_outputNodes[i]);
        }
    }

    updateGeometryBasedOnNodes();
}

uint GateFPGA::getNumInputs() const
{
    return m_inputNodes.size();
}

uint GateFPGA::getNumOutputs() const
{
    return m_outputNodes.size();
}

std::vector<Node*> GateFPGA::getInputNodes()
{
    return m_inputNodes;
}

std::vector<Node*> GateFPGA::getOutputNodes()
{
    return m_outputNodes;
}

QString GateFPGA::getScript() const
{
    return m_script;
}

void GateFPGA::setScript(const QString& script)
{
    m_script = script;
}

void GateFPGA::updateGeometryBasedOnNodes()
{
    m_geometry = QRect(position().x(), position().y(), Settings::GateFpgaWidth, m_inputNodes.size() > m_outputNodes.size() ? m_inputNodes.size() * Settings::GapBetweenNodesY : m_outputNodes.size() * Settings::GapBetweenNodesY);

    const int yOffset = -(m_inputNodes.size() > m_outputNodes.size() ? m_inputNodes.size()/2 * Settings::GapBetweenNodesY : m_outputNodes.size()/2 * Settings::GapBetweenNodesY);
    for(uint i = 0; i < m_inputNodes.size(); i++)
    {
        m_inputNodes[i]->setOffsets(Settings::InputNodesXpos, i * Settings::GapBetweenNodesY + yOffset);
    }
    for(uint i = 0; i < m_outputNodes.size(); i++)
    {
        m_outputNodes[i]->setOffsets(Settings::OutputNodesXpos, i * Settings::GapBetweenNodesY + yOffset);
    }

    //Display update
    setPosition(geometry().center().x(), geometry().center().y());
}

void GateFPGA::eraseNodeFromAllNodes(Node* pNode)
{
    for(uint iAllNodes = 0; iAllNodes < m_nodes.size(); iAllNodes++)
    {
        if(pNode == m_nodes[iAllNodes])
        {
            m_nodes.erase(m_nodes.begin() + iAllNodes);
            return;
        }
    }
    Logger::log(LL_Warn, "GateFPGA::eraseNodeFromAllNodes - Node could not be found!");
}
