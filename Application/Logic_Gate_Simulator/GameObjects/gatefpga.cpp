#include "gatefpga.h"
#include "gatefield.h"

#include <QDebug>
#include <QScriptEngine>

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
    Gate::Gate(GATE_FPGA, x, y, Settings::GateFpgaWidth, Settings::GateFpgaHeight),
    m_script("var output1 = true, output2 = true, output3 = true, output4 = true, output5 = true;")
{
    updateEditButtonGeometry();

    for (size_t x = 0; x < 5; x++)
    {
        m_inputNodes.push_back(new Node(this, Settings::InputNodesXpos, x * Settings::GapBetweenNodesY, InputNode));
        m_nodes.push_back(m_inputNodes[x]);

        m_outputNodes.push_back(new Node(this, Settings::OutputNodesXpos, x * Settings::GapBetweenNodesY, OutputNode));
        m_nodes.push_back(m_outputNodes[x]);
    }
}

GateFPGA::GateFPGA(std::vector<Node*>& inputNodesToCopy, std::vector<Node*>& outputNodesToCopy, const int &x, const int &y) :
    Gate::Gate(GATE_FPGA, x, y, Settings::GateFpgaWidth, Settings::GateFpgaHeight),
    m_script("")
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
    GateFPGA* clone = new GateFPGA(m_inputNodes, m_outputNodes, m_geometry.x(), m_geometry.y());
    clone->m_script = m_script;
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
            eraseNodeFromAllNodes(n);
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
        for(uint i = numOutputs; i < m_outputNodes.size();)
        {
            Node* n = m_outputNodes[i];
            eraseNodeFromAllNodes(n);
            m_outputNodes.erase(m_outputNodes.begin() + i);
            delete n;
        }
        return;
    }

    //numOutputs > currentOutputs
    for(uint i = currentOutputs; i < numOutputs; i++)
    {
        m_outputNodes.push_back(new Node(this, Settings::OutputNodesXpos, i * Settings::GapBetweenNodesY, OutputNode));
        m_nodes.push_back(m_outputNodes[i]);
    }
}

uint GateFPGA::getNumInputs() const
{
    return m_inputNodes.size();
}

uint GateFPGA::getNumOutputs() const
{
    return m_outputNodes.size();
}

QString GateFPGA::getScript() const
{
    return m_script;
}

void GateFPGA::setScript(const QString& script)
{
    m_script = script;
}

void GateFPGA::updateEditButtonGeometry()
{
    m_editButtonRect = QRect(m_geometry.right(), m_geometry.top() - Settings::EditButtonSize, Settings::EditButtonSize, Settings::EditButtonSize);
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
    qDebug() << "GateFPGA::eraseNodeFromAllNodes - Node could not be found!";
}
