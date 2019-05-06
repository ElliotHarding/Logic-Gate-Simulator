#include "gatecollection.h"
#include "allgates.h"

GateCollection::GateCollection(std::vector<Gate*> gates) :
    Gate::Gate(GATE_COLLECTION, 0, 0)
{
    m_gates = gates;
}

GateCollection::GateCollection(const GateCollection &gCopy) :
    Gate::Gate(GATE_COLLECTION,0,0)
{
    for (Gate* copyGate : gCopy.m_gates)
    {
        Gate* newGate;
        switch (copyGate->GetType())
        {
        case GateType::GATE_AND:
            newGate = new GateAnd();
            break;
        case GateType::GATE_OR:
            newGate = new GateOr();
            break;
        case GateType::GATE_NOT:
            newGate = new GateNot();
            break;
        case GateType::GATE_EMMITTER:
            newGate = new GateToggle();
            break;
        case GateType::GATE_RECIEVER:
            newGate = new GateReciever();
            break;
        case GateType::GATE_CONST_ACTIVE:
            newGate = new GateReciever();
            break;
        case GateType::GATE_CONST_INACTIVE:
            newGate = new GateReciever();
            break;
        case GateType::GATE_TIMER:
            newGate = new GateTimer();
            break;
        default:
            break;
        }
        newGate->SetPosition(copyGate->GetPosition().x(), copyGate->GetPosition().y());
        m_gates.push_back(newGate);
    }
}

GateCollection::~GateCollection()
{
    for (size_t index = 0; index < m_gates.size(); index++)
    {
        delete m_gates[index];
        m_gates.erase(m_gates.begin() + (int)index);
    }
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
        if(gate->GetClickedNode(clickX, clickY))
            return gate->GetClickedNode(clickX,clickY);
    }
    return nullptr;
}

void GateCollection::SaveData(std::ofstream &storage)
{
    storage << SAVE_TAG_GATE_COLLECTION << std::endl;

    for(Gate* gate : m_gates)
    {
        gate->SaveData(storage);
    }

    storage << END_SAVE_TAG_GATE_COLLECTION << std::endl;
}

typedef QPoint Vector2D;
bool GateCollection::UpdateDrag(int clickX, int clickY)
{
    //If single gate is being dragged, only drag that gate,
    //or if area is dragged, drag entire gate collection

    //Perform drag click for each individual gate
    for(Gate* gate : m_gates)
    {
        if(gate->UpdateDrag(clickX, clickY))
        {
            return true;
        }
    }

    //If containingArea clicked store displacement variable of how far
    //it will be dragged by click
    if(containingArea().contains(QPoint(clickX,clickY)))
    {
        const QPoint previousPos = containingArea().center();

        //Calculate difference between new & old pos
        Vector2D displacement(clickX - previousPos.x(),
                              clickY - previousPos.y());

        //apply displacement to all gates and return true
        for(Gate* gate : m_gates)
        {
            gate->SetPosition(gate->GetPosition().x() + displacement.x(),
                              gate->GetPosition().y() + displacement.y());
        }
        return true;

    }
    return false;
}

bool GateCollection::UpdateClicked(int clickX, int clickY)
{
    return containingArea().contains(QPoint(clickX,clickY));
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
