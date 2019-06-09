#include "gatecollection.h"
#include "allgates.h"

GateCollection::GateCollection(std::vector<Gate*> gates) :
    Gate::Gate(GATE_COLLECTION, 0, 0)
{
    m_gates = gates;
}

GateCollection::~GateCollection()
{
    for (Gate* g : m_gates)
    {
        g->DetachNodes();
    }

    for (size_t index = 0; index < m_gates.size(); index++)
    {
        delete m_gates[index];
        m_gates.erase(m_gates.begin() + (int)index);
    }
}

void GateCollection::UpdateOutput()
{
    if(Enabled)
        for(Gate* gate : m_gates)
        {
            gate->UpdateOutput();
        }
}

bool GateCollection::FindNodeWithId(id _id, Node*& n)
{
    for (Gate* gate : m_gates)
    {
        if(gate->FindNodeWithId(_id, n))
            return true;
    }
    return false;
}

void GateCollection::OffsetPosition(int dX, int dY)
{
    for (Gate* gate : m_gates)
    {
        gate->OffsetPosition(dX, dY);
    }
}

void GateCollection::AssignNewNodeIds()
{
    for (Gate* gate : m_gates)
    {
        gate->AssignNewNodeIds();
    }
}

bool GateCollection::DeleteClick(int clickX, int clickY)
{
    if(m_contaningArea.contains(QPoint(clickX,clickY)))
    {
        if(m_dragMode == DragIndividual)
        {
            for(size_t index = 0; index < m_gates.size(); index++)
            {
                if(m_gates[index]->DeleteClick(clickX, clickY))
                {
                    Gate* gObject = m_gates[index];
                    gObject->DetachNodes();
                    m_gates.erase(m_gates.begin() + index);
                    delete gObject;

                    return false;
                }
            }
        }

        //returning true causes entire gate collection to be deleted
        return true;
    }

    return false;
}

void GateCollection::UpdateGraphics(QPainter *painter)
{
    for(Gate* gate : m_gates)
    {
        //Draw gate
        gate->UpdateGraphics(painter);
    }

    UpdateContaningArea();

    //Draw bounding box
    painter->setPen(QPen(Qt::black,2));
    painter->drawRect(m_contaningArea);

    if (m_dragMode == DragAll)
         painter->fillRect(m_contaningArea, QColor(20,20,20,20));
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
    SaveGeneralData(storage);

    for(Gate* gate : m_gates)
    {
        gate->SaveData(storage);
    }

    storage << END_SAVE_TAG_GATE << std::endl;
}

void GateCollection::DisplaceGates(Vector2D displacement)
{
    for(Gate* gate : m_gates)
    {
        if(gate->GetType() == GATE_COLLECTION)
        {
            if(dynamic_cast<GateCollection*>(gate))
                dynamic_cast<GateCollection*>(gate)->DisplaceGates(displacement);
        }
        else
        {
            gate->SetPosition(gate->GetPosition().x() + displacement.x,
                              gate->GetPosition().y() + displacement.y);
        }
    }
}

void GateCollection::ToggleDragMode()
{
    m_dragMode = (bool)m_dragMode ? DragIndividual : DragAll;
}

bool GateCollection::IsDragAll()
{
    return (bool)m_dragMode;
}


bool GateCollection::UpdateDrag(int clickX, int clickY)
{

    if(m_dragMode == DragIndividual)
    {
        //Perform drag click for each individual gate
        for(Gate* gate : m_gates)
        {
            if(gate->UpdateDrag(clickX, clickY))
            {
                return true;
            }
        }
    }

    //If containingArea clicked store displacement variable of how far
    //it will be dragged by click
    /*else*/ if(m_contaningArea.contains(QPoint(clickX,clickY)))
    {
        const QPoint previousPos = containingArea().center();

        //Calculate difference between new & old pos
        Vector2D displacement = {clickX - previousPos.x(),
                                 clickY - previousPos.y()};

        //apply displacement to all gates and return true
        for(Gate* gate : m_gates)
        {
            if(gate->GetType() == GATE_COLLECTION)
            {
                if(dynamic_cast<GateCollection*>(gate))
                    dynamic_cast<GateCollection*>(gate)->DisplaceGates(displacement);
            }
            else
            {
                gate->SetPosition(gate->GetPosition().x() + displacement.x,
                                  gate->GetPosition().y() + displacement.y);
            }
        }
        return true;
    }
    return false;
}

bool GateCollection::UpdateClicked(int clickX, int clickY)
{
    //DISABLED FOR THIS GATE TYPE, BUT NEEDED TO OVERRIDE.
    return false;
}

Gate *GateCollection::Clone()
{
    std::vector<Gate*> backupGates;
    for (Gate* g : m_gates)
    {
        backupGates.push_back(g->Clone());
    }

    GateCollection* clone = new GateCollection(backupGates);

    //Clone position
    QPoint pos = GetPosition();
    clone->SetPosition(pos.x(), pos.y());

    clone->m_contaningArea = m_contaningArea;

    return clone;
}

Gate *GateCollection::UpdateClicked_Override(int clickX, int clickY)
{
    if(m_contaningArea.contains(QPoint(clickX,clickY)))
    {
        if(m_dragMode == DragIndividual)
        {
            for (Gate* g : m_gates)
            {
                if(g->GetType() == GATE_COLLECTION)
                {
                    Gate* subG = dynamic_cast<GateCollection*>(g)->UpdateClicked_Override(clickX, clickY);
                    if(subG)
                    {
                        return subG;
                    }
                }
                else if(g->UpdateClicked(clickX, clickY))
                {
                    return g;
                }
            }

            //If gate collection clicked, but no sub gates clicked, return gate collection
            return this;
        }
        else
        {
            return this;
        }
    }
    return nullptr;
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
        if(gate->GetType() == GATE_COLLECTION)
        {
            if(dynamic_cast<GateCollection*>(gate))
                dynamic_cast<GateCollection*>(gate)->UpdateContaningArea();

            if(gate->Bottom() < MINY)
            {
                MINY = gate->Bottom() + c_borderBoxMargin;
            }

            if(gate->Top() > MAXY)
            {
                MAXY = gate->Top() - c_borderBoxMargin;
            }
        }
        else
        {
            if(gate->Top() < MINY)
            {
                MINY = gate->Top() - c_borderBoxMargin;
            }

            if(gate->Bottom() > MAXY)
            {
                MAXY = gate->Bottom() + c_borderBoxMargin;
            }
        }

        if(gate->Left() < MINX)
        {
            MINX = gate->Left() - c_borderBoxMargin;
        }

        if(gate->Right() > MAXX)
        {
            MAXX = gate->Right() + c_borderBoxMargin;
        }
    }

    return QRect(QPoint(MINX, MAXY), QPoint(MAXX, MINY));
}
