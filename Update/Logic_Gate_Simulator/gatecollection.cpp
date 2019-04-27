#include "gatecollection.h"

GateCollection::GateCollection(std::vector<Gate *> gates, int width, int height) :
    Gate::Gate(width, height),
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
