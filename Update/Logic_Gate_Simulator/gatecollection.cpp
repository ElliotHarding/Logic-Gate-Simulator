#include "gatecollection.h"

GateCollection::GateCollection(std::vector<Gate *> gates) :
    Gate::Gate(0, 0),
    m_gates(gates)
{
}

void GateCollection::UpdateOutput()
{
    for(Gate* gate : m_gates)
    {
        gate->UpdateOutput();
    }
}

void GateCollection::UpdateGraphics(QPainter *painter)
{
    for(Gate* gate : m_gates)
    {
        gate->UpdateGraphics(painter);
    }
}

Node *GateCollection::GetClickedNode(int clickX, int clickY)
{
    for(Gate* gate : m_gates)
    {
        gate->GetClickedNode(clickX, clickY);
    }
}

void GateCollection::SaveData(std::ofstream &storage)
{
    storage << "--GateCollection--" << std::endl;
    storage << std::to_string(m_layout.left()) << std::endl;
    storage << std::to_string(m_layout.right()) << std::endl;
    storage << std::to_string(m_layout.top()) << std::endl;
    storage << std::to_string(m_layout.bottom()) << std::endl;

    for(Gate* gate : m_gates)
    {
        gate->SaveData(storage);
    }

    storage << "--EndGateCollection--" << std::endl;
}

typedef QPoint Vector2D;
bool GateCollection::UpdateDrag(int clickX, int clickY)
{
    //Perform drag operation if mouse inside hitbox
    if(GameObject::UpdateClicked(clickX, clickY))
    {
        //Set new pos, store old pos
        QPoint currentPos = GetPosition();
        SetPosition(clickX,clickY);
        QPoint newPos = GetPosition();

        //Calculate difference between new & old pos
        Vector2D displacement = Vector2D(currentPos.x() - newPos.x() ,
                                         currentPos.y() - newPos.y());

        //Apply displacement to all gates
        for(Gate* gate : m_gates)
        {
            gate->SetPosition(gate->GetPosition().x() + displacement.x(),
                              gate->GetPosition().y() + displacement.y());
        }

        return true;
    }
    return false;
}
