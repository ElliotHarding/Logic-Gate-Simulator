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
        //Draw gate
        gate->UpdateGraphics(painter);
    }

    //Draw bounding box
    painter->setPen(Qt::black);
    painter->drawRect(containingArea());
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

    //If single gate is being dragged, or entire gate collection
    bool singleGateDrag = false;

    //Perform drag click for each individual gate
    for(Gate* gate : m_gates)
    {
        if(gate->UpdateDrag(clickX, clickY))
        {
            singleGateDrag = true;
            return true;
        }
    }

    //If containingArea clicked store displacement variable of how far
    //it will be dragged by click
    if(containingArea().contains(QPoint(clickX,clickY)))
    {
        const QPoint previousPos = QPoint(containingArea().center().x(),containingArea().center().y());
        const QPoint newPos = QPoint(clickX, clickY);

        //Calculate difference between new & old pos
        displacement = Vector2D(newPos.x() - previousPos.x(),
                                newPos.y() - previousPos.y());

    }

    //apply displacement to all gates and return true
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

QRect GateCollection::containingArea()
{
    //Variables specifying boundaries of GateCollection
    //To be used to draw bounding box
    int MINX = 99999;
    int MINY = 99999;
    int MAXX = -99999;
    int MAXY = -99999;

    for(Gate* gate : m_gates)
    {
        if(gate->Left() < MINX)
        {
            MINX = gate->Left() - c_borderBoxMargin;
        }

        if(gate->Right() > MAXX)
        {
            MAXX = gate->Right() + c_borderBoxMargin;
        }

        if(gate->Top() < MINY)
        {
            MINY = gate->Top() - c_borderBoxMargin;
        }

        if(gate->Bottom() > MAXY)
        {
            MAXY = gate->Bottom() + c_borderBoxMargin;
        }
    }

    return QRect(QPoint(MINX, MAXY), QPoint(MAXX, MINY));
}
