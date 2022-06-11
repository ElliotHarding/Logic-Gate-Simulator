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
const QColor FillColor = Qt::lightGray;
}

GateFPGA::GateFPGA(const int& x, const int& y) :
    Gate::Gate(GATE_FPGA, x, y, Settings::GateFpgaWidth, Settings::GateFpgaHeight),
    m_pDlgEdit(new DLG_FPGA(this))
{
    for (size_t x = 0; x < 10; x++)
    {
        m_inputNodes.push_back(new Node(this, Settings::InputNodesXpos, x * Settings::GapBetweenNodesY, InputNode));
        m_nodes.push_back(m_inputNodes[x]);

        m_outputNodes.push_back(new Node(this, Settings::OutputNodesXpos, x * Settings::GapBetweenNodesY, OutputNode));
        m_nodes.push_back(m_outputNodes[x]);
    }
}

GateFPGA::~GateFPGA()
{
    delete m_pDlgEdit;

    m_inputNodes.clear();
    m_outputNodes.clear();
}

void GateFPGA::draw(QPainter& painter)
{
    //Draw gate
    painter.setPen(QPen(Settings::BorderColor, Settings::GateFpgaBorderWidth * 2));
    painter.drawRect(m_geometry);

    //MiniRect
    QRect miniRect;
    miniRect.setLeft(m_geometry.left() + Settings::GateFpgaBorderWidth);
    miniRect.setRight(m_geometry.right() - Settings::GateFpgaBorderWidth);
    miniRect.setTop(m_geometry.top() + Settings::GateFpgaBorderWidth);
    miniRect.setBottom(m_geometry.bottom() - Settings::GateFpgaBorderWidth);

    painter.fillRect(miniRect, QBrush(Settings::FillColor));

    drawNodes(painter);
}

GameObject *GateFPGA::checkClicked(const QPoint& mouse)
{
    for (Node* n : m_nodes)
    {
        GameObject* pPossibleClickedNode = n->checkClicked(mouse);
        if(pPossibleClickedNode != nullptr)
        {
            return pPossibleClickedNode;
        }
    }

    if(m_pParentField->GetCurrentClickMode() == CLICK_DEFAULT)
    {
        if(m_geometry.contains(mouse))
        {
            OpenEditor();
        }
        return nullptr;
    }

    return GameObject::checkClicked(mouse);
}

void GateFPGA::SaveData(std::ofstream& storage)
{
    SaveGeneralData(storage);

    m_updateScript.SaveData(storage);

    //Add node information
    for (Node* n : m_nodes)
    {
        n->SaveData(storage);
    }

    storage << END_SAVE_TAG_GATE << std::endl;
}

void GateFPGA::UpdateOutput()
{
    m_updateScript.CalculateOutput(m_inputNodes, m_outputNodes);
}

Gate *GateFPGA::Clone()
{
    GateFPGA* clone = new GateFPGA(m_geometry.x(), m_geometry.y());

    clone->m_inputNodes = m_inputNodes;
    clone->m_outputNodes = m_outputNodes;

    clone->m_updateScript = m_updateScript;

    return clone;
}

void GateFPGA::OpenEditor()
{
    m_pDlgEdit->EditFpgaScript(&m_updateScript);
}


//      ----                    ----
//              UpdateScript
//      ----                    ----

UpdateScript::UpdateScript()
{

}

void UpdateScript::CalculateOutput(std::vector<Node*>& in, std::vector<Node*>& out)
{

}

void UpdateScript::SaveData(std::ofstream& storage)
{

}



//      ----                    ----
//               DLG_FPGA
//      ----                    ----


DLG_FPGA::DLG_FPGA(GateFPGA *parent) :
    QDialog (),
    m_pParentGate(parent)
{
}

void DLG_FPGA::EditFpgaScript(UpdateScript* pUpdateScript)
{
    show();
}
