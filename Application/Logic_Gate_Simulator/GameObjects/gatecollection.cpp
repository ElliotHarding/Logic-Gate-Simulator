#include "gatecollection.h"
#include "allgates.h"
#include "gatefield.h"
#include "circuitoptimizer.h"

GateCollection::GateCollection(std::vector<Gate*> gates) :
    Gate::Gate(GATE_COLLECTION, 0, 0)
{
    m_gates = gates;
}

GateCollection::~GateCollection()
{

    //When deleted the gate collection filed can dump its contents onto the parent gatefield
    if(!m_bDontDeleteGates)
    {
        for (size_t index = 0; index < m_gates.size(); index++)
        {
            m_gates[index]->DetachNodes();
            delete m_gates[index];
            m_gates.erase(m_gates.begin() + (int)index);
        }
    }

    //dump contents onto the parent gatefield
    else
    {
        if(m_pParentField)
        {
            for (Gate* g : m_gates)
            {
                m_pParentField->AddGate(&*g, false, true);
            }

            //todo
            //very lazy code.... fix up

            const int size = m_gates.size();
            for (int x = 0; x < size; x++)
            {
                m_gates.erase(m_gates.begin());
            }
        }
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
        if(!m_bDontDeleteGates)
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
    if (m_dragMode == DragAll)
         painter->fillRect(m_contaningArea, QColor(20,20,20,20));

    for(Gate* gate : m_gates)
    {
        //Draw gate
        gate->UpdateGraphics(painter);
    }

    UpdateContaningArea();

    DrawButtons(painter);

    //Draw bounding box
    painter->setPen(QPen(Qt::black,2));
    painter->drawRect(m_contaningArea);
}

void GateCollection::DrawButtons(QPainter *painter)
{
    static const QImage deleteAllButton = QImage(std::string(":/Resources/Button Icons/gate-collection-delete-all.png").c_str());
    static const QImage saveButton = QImage(std::string(":/Resources/Button Icons/gate-collection-save.png").c_str());
    static const QImage deleteButton = QImage(std::string(":/Resources/Button Icons/gate-collection-delete.png").c_str());
    const int xyButtonSize = 40;

    m_deleteAllButton  = QRect(m_contaningArea.right() - xyButtonSize, m_contaningArea.bottom() - xyButtonSize, xyButtonSize, xyButtonSize);
    m_deleteButton = QRect(m_contaningArea.right() - xyButtonSize*2, m_contaningArea.bottom() - xyButtonSize, xyButtonSize, xyButtonSize);
    m_saveButton = QRect(m_contaningArea.right() - xyButtonSize*3, m_contaningArea.bottom() - xyButtonSize, xyButtonSize, xyButtonSize);
    m_optimize = QRect(m_contaningArea.right() - xyButtonSize*4, m_contaningArea.bottom() - xyButtonSize, xyButtonSize, xyButtonSize);

    painter->drawImage(m_deleteAllButton, deleteAllButton);
    painter->drawImage(m_deleteButton, deleteButton);
    painter->drawImage(m_saveButton, saveButton);

    painter->drawRect(m_optimize);
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

void GateCollection::SaveData(std::ofstream &storage, std::vector<Gate *> gates)
{
    //should probably return a bool here

    //Add general gate info
    storage << SAVE_TAG_GATE
            with std::to_string(GATE_COLLECTION)
            with std::to_string(1)
            with std::to_string(0)
            with std::to_string(0)
            << std::endl;

    for(Gate* gate : gates)
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

    //Save button
    if(m_saveButton.contains(clickX, clickY))
    {
        m_pParentField->StartSaveGateCollection(m_gates);
        return false;
    }

    //Delete button
    else if (m_deleteButton.contains(clickX, clickY))
    {
        //Keep gates in memory, but remove them from this list,
        //since we're deleting this collection, its gets dumped onto gatefield
        m_bDontDeleteGates = true;

        m_pParentField->ForgetChild(this);
        delete this;

        return false;
    }

    //Delete all button
    else if (m_deleteAllButton.contains(clickX, clickY))
    {
        m_pParentField->ForgetChild(this);
        delete this;

        return false;
    }

    //Optimize button
    else if (m_optimize.contains(clickX, clickY))
    {
        m_gates = CircuitOptimizer::Optimize(m_gates);
        return false;
    }

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
