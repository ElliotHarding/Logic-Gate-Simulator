#include "gatecollection.h"
#include "allgates.h"
#include "gatefield.h"
#include "circuitoptimizer.h"

GateCollection::GateCollection(std::vector<Gate*> gates) :
    Gate::Gate(GATE_COLLECTION, 0, 0)
{
    m_gates = gates;
    ProporgateParentAndCheckForNestedGates();
}

void GateCollection::SetParent(GateField *gf)
{
    m_pParentField = gf;

    //Proporgate for nested gates
    ProporgateParentAndCheckForNestedGates();
}

void GateCollection::ProporgateParentAndCheckForNestedGates()
{
    for (Gate* g : m_gates)
    {
        g->SetParent(m_pParentField);
        if (g->GetType() == GATE_COLLECTION)
        {
            dynamic_cast<GateCollection*>(g)->m_bIsNested = true;
            dynamic_cast<GateCollection*>(g)->m_pParentGateCollection = this;
        }
    }
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

    //dump contents onto the parent gatefield or parent gate collection...
    else
    {
        //Dump onto parent GateCollection
        if (m_bIsNested && m_pParentGateCollection)
        {
            for (Gate* g : m_gates)
                m_pParentGateCollection->AddGate(&*g);
        }

        //Dump onto parent ParentField
        else if (m_pParentField)
        {
            for (Gate* g : m_gates)
                m_pParentField->AddGate(&*g, false, true);
        }

        //Erase pointers to gates
        const int size = m_gates.size();
        for (int x = 0; x < size; x++)
        {
            m_gates.erase(m_gates.begin());
        }
    }

    m_pParentGateCollection = nullptr;
    m_pParentField = nullptr;
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
    UpdateContaningArea();

    if (m_dragMode == DragAll)
         painter->fillRect(m_contaningArea, QColor(40,40,40,20));

    for(Gate* gate : m_gates)
        gate->UpdateGraphics(painter);

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

    painter->setPen(QPen(Qt::black,0.5));
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

void GateCollection::AddGate(Gate *g)
{
    if (g->GetType() == GATE_COLLECTION)
        dynamic_cast<GateCollection*>(g)->m_pParentGateCollection = this;

    g->SetParent(m_pParentField);

    m_gates.push_back(g);
}

void GateCollection::ForgetGate(Gate *g)
{
    for(size_t index = 0; index < m_gates.size(); index++)
    {
        if (m_gates[index] == g)
        {
            //Forget
            m_gates.erase(m_gates.begin() + int8_t(index));
            g = nullptr;

            //Exit early
            break;
        }
    }

    //Update
    for(Gate* gate : m_gates)
    {
        gate->UpdateOutput();
    }
}

//Returns true if buttons we're clicked
bool GateCollection::CheckButtonClick(int clickX, int clickY)
{
    //Save button
    if(m_saveButton.contains(clickX, clickY))
    {
        m_pParentField->SkipNextGateSelectedCall();
        m_pParentField->StartSaveGateCollection(m_gates);
        m_pParentField->SkipNextGateSelectedCall();
        m_pParentField->StopDragging();

        return true;
    }

    //Delete button
    else if (m_deleteButton.contains(clickX, clickY))
    {
        //Keep gates in memory, but remove them from this list,
        //since we're deleting this collection, its gets dumped onto gatefield
        m_bDontDeleteGates = true;

        m_pParentField->UpdateGateSelected(nullptr);
        m_pParentField->SkipNextGateSelectedCall();
        m_pParentField->StopDragging();

        if (m_bIsNested)
            m_pParentGateCollection->ForgetGate(this);
        else
            m_pParentField->ForgetChild(this);

        delete this;
        return true;
    }

    //Delete all button
    else if (m_deleteAllButton.contains(clickX, clickY))
    {
        m_pParentField->UpdateGateSelected(nullptr);
        m_pParentField->SkipNextGateSelectedCall();
        m_pParentField->StopDragging();

        if (m_bIsNested)
            m_pParentGateCollection->ForgetGate(this);
        else
            m_pParentField->ForgetChild(this);

        delete this;
        return true;
    }

    //Optimize button
    else if (m_optimize.contains(clickX, clickY))
    {
        m_gates = CircuitOptimizer::Optimize(m_gates);
        m_pParentField->SkipNextGateSelectedCall();
        m_pParentField->StopDragging();
        return true;
    }

    return false;
}

bool GateCollection::UpdateDrag(int clickX, int clickY)
{
    if (CheckButtonClick(clickX,clickY))
        return true;

    if(m_dragMode == DragIndividual)
    {
        //Perform drag click for each individual gate
        for(Gate* gate : m_gates)
        {
            if(gate->UpdateDrag(clickX, clickY))
            {
                m_pParentField->UpdateGateSelected(gate);
                m_pParentField->SkipNextGateSelectedCall();
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
    if(!CheckButtonClick(clickX,clickY) && m_contaningArea.contains(QPoint(clickX,clickY)))
    {
        if(m_dragMode == DragIndividual)
        {
            //Proporgate click to sub gates
            for (Gate* g : m_gates)
            {
                if(g->UpdateClicked(clickX, clickY))
                {
                    m_pParentField->UpdateGateSelected(g);
                    m_pParentField->SkipNextGateSelectedCall();
                    return true;
                }
            }
        }

        return true;
    }

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
