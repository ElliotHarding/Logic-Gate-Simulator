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

    for(Gate* gate : m_gates)
    {
        gate->SaveData(storage);
    }

    storage << "--EndGateCollection--" << std::endl;
}

typedef QPoint Vector2D;
bool GateCollection::UpdateDrag(int clickX, int clickY)
{
    Vector2D displacement(0,0);

    //Check if any gate has been clicked.
    //If so store displacement variable of how far it will be dragged by click
    for(Gate* gate : m_gates)
    {
        QPoint previousPos = gate->GetPosition();
        if(gate->UpdateClicked(clickX, clickY))
        {
            QPoint newPos = QPoint(clickX, clickY);

            //Calculate difference between new & old pos
            displacement = Vector2D(previousPos.x() - newPos.x() ,
                                             previousPos.y() - newPos.y());

            break;
        }
    }

    //If one of the gates displaced, apply displacement to all gates
    //And return true
    if(displacement.x() != 0 || displacement.y() != 0)
    {
        for(Gate* gate : m_gates)
        {
            gate->SetPosition(gate->GetPosition().x() + displacement.x(),
                              gate->GetPosition().y() + displacement.y());
        }
        return true;
    }
    return false;
}
