#include "gatefpga.h"
#include "gatefield.h"

GateFPGA::GateFPGA() :
    Gate::Gate(GATE_FPGA, GateFpgaWidth, GateFpgaHeight),
    m_pDlgEdit(new DLG_FPGA(this))
{
    for (size_t x = 0; x < 10; x++)
    {
        m_inputNodes.push_back(Node(this, InputNode));
        m_nodes.push_back(&m_inputNodes[x]);

        m_outputNodes.push_back(Node(this, OutputNode));
        m_nodes.push_back(&m_outputNodes[x]);
    }
}

GateFPGA::~GateFPGA()
{
    delete m_pDlgEdit;
}

void GateFPGA::UpdateGraphics(QPainter *painter)
{
    //Draw gate
    painter->setPen(QPen(Qt::darkGray, GateFpgaBorderWidth * 2));
    painter->drawRect(m_layout);

    //MiniRect
    QRect miniRect = m_layout;
    miniRect.setLeft(miniRect.left() + GateFpgaBorderWidth);
    miniRect.setRight(miniRect.right() - GateFpgaBorderWidth);
    miniRect.setTop(miniRect.top() + GateFpgaBorderWidth);
    miniRect.setBottom(miniRect.bottom() - GateFpgaBorderWidth);

    painter->fillRect(miniRect, QBrush(Qt::lightGray));

    //Draw nodes
    for (Node n : m_inputNodes)
    {
        n.UpdateGraphics(painter);
    }
    for (Node n : m_outputNodes)
    {
        n.UpdateGraphics(painter);
    }
}

void GateFPGA::setPosition(int x, int y)
{
    GameObject::setPosition(x,y);

    for (size_t index = 0; index < m_inputNodes.size(); index++)
    {
        m_inputNodes[index].setPosition(m_layout.x() + INPUT_NODES_X, m_layout.y() + (index * NODES_Y_DIFF));
    }

    for (size_t index = 0; index < m_outputNodes.size(); index++)
    {
        m_outputNodes[index].setPosition(m_layout.x() + OUTPUT_NODES_X, m_layout.y()+ (index * NODES_Y_DIFF));
    }
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

bool GateFPGA::UpdateClicked(int clickX, int clickY)
{
    bool ret = Gate::UpdateClicked(clickX, clickY);
    if(ret)
    {
        if(m_pParentField->GetCurrentClickMode() == CLICK_DEFAULT)
        {
            OpenEditor();
        }
    }

    return ret;
}

void GateFPGA::UpdateOutput()
{
    m_updateScript.CalculateOutput(m_inputNodes, m_outputNodes);
}

Gate *GateFPGA::Clone()
{
    GateFPGA* clone = new GateFPGA();

    clone->m_inputNodes = m_inputNodes;
    clone->m_outputNodes = m_outputNodes;

    //Clone position
    const QPoint pos = position();
    clone->setPosition(pos.x(), pos.y());

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

void UpdateScript::CalculateOutput(std::vector<Node>& in, std::vector<Node>& out)
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

void DLG_FPGA::EditFpgaScript(UpdateScript* updateScript)
{
    show();
}
