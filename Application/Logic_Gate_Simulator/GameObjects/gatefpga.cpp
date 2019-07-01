#include "gatefpga.h"
#include "gatefield.h"

GateFPGA::GateFPGA() :
    Gate::Gate(GATE_FPGA, GateFpgaWidth, GateFpgaHeight),
    m_pDlgEdit(new DLG_FPGA(this))
{
    for (size_t x = 0; x < 10; x++)
    {
        m_inputNodes[x] = Node(this, InputNode);
        m_nodes.push_back(&m_inputNodes[x]);

        m_outputNodes[x] = Node(this, OutputNode);
        m_nodes.push_back(&m_outputNodes[x]);
    }
}

void GateFPGA::UpdateGraphics(QPainter *painter)
{
    //Draw gate
    painter->setPen(QPen(Qt::darkGray, 10));
    painter->drawRect(m_layout);

    //MiniRect
    QRect miniRect = m_layout;
    miniRect.setLeft(miniRect.left() + BorderWidth);
    miniRect.setRight(miniRect.right() - BorderWidth);
    miniRect.setTop(miniRect.top() + BorderWidth);
    miniRect.setBottom(miniRect.bottom() - BorderWidth);

    painter->setPen(QPen(Qt::lightGray, 20));
    painter->drawRect(miniRect);

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

void GateFPGA::SetPosition(int x, int y)
{
    GameObject::SetPosition(x,y);

    for (size_t index = 0; index < m_inputNodes.size(); index++)
    {
        m_inputNodes[index].SetPosition(m_layout.x() + INPUT_NODES_X, m_layout.y() + (index * NODES_Y_DIFF));
    }

    for (size_t index = 0; index < m_outputNodes.size(); index++)
    {
        m_outputNodes[index].SetPosition(m_layout.x() + OUTPUT_NODES_X, m_layout.y()+ (index * NODES_Y_DIFF));
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
            m_pDlgEdit->EditFpgaScript(&m_updateScript);
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
    const QPoint pos = GetPosition();
    clone->SetPosition(pos.x(), pos.y());

    clone->m_updateScript = m_updateScript;

    return clone;
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

void DLG_FPGA::EditFpgaScript(UpdateScript* updateScript)
{

}
