#include "gateselection.h"
#include "gatecollection.h"
#include "gatefield.h"

GateSelection::GateSelection(GateField* pParent, std::vector<Gate**>& gates) :
    m_pParent(pParent)
{
    for (Gate** gate : gates)
    {
        m_ppGates.push_back(gate);
    }
}

GateSelection::~GateSelection()
{
    if(m_bDeleteGates)
    {
        for (Gate** g : m_ppGates)
        {
            m_pParent->ForgetChild((*g));
        }

        for (size_t x = 0; x < m_ppGates.size(); x++)
        {
            delete m_ppGates[x];
        }
    }

    m_ppGates.clear();
}

void GateSelection::Draw(QPainter *painter)
{
    QPen pen(Qt::blue, 2);
    painter->setPen(pen);
    painter->drawRect(m_contaningArea);

    DrawButtons(painter);
}

void GateSelection::DrawButtons(QPainter *painter)
{
    static const QImage deleteAllButton = QImage(std::string(":/Resources/Button Icons/gate-collection-delete-all.png").c_str());
    static const QImage saveButton = QImage(std::string(":/Resources/Button Icons/gate-collection-save.png").c_str());
    static const QImage deleteButton = QImage(std::string(":/Resources/Button Icons/gate-collection-delete.png").c_str());
    const int xyButtonSize = 40;

    m_deleteAllButton  = QRect(m_contaningArea.right() - xyButtonSize, m_contaningArea.bottom() - xyButtonSize, xyButtonSize, xyButtonSize);
    m_deleteButton = QRect(m_contaningArea.right() - xyButtonSize*2, m_contaningArea.bottom() - xyButtonSize, xyButtonSize, xyButtonSize);
    m_saveButton = QRect(m_contaningArea.right() - xyButtonSize*3, m_contaningArea.bottom() - xyButtonSize, xyButtonSize, xyButtonSize);

    painter->drawImage(m_deleteAllButton, deleteAllButton);
    painter->drawImage(m_deleteButton, deleteButton);
    painter->drawImage(m_saveButton, saveButton);
}

void GateSelection::UpdateContaningArea()
{
    //Variables specifying boundaries of GateCollection
    //To be used to draw bounding box
    int MINX = 99999;
    int MINY = 99999;
    int MAXX = -99999;
    int MAXY = -99999;

    for(Gate** ppGate : m_ppGates)
    {
        Gate* gate = *ppGate;
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

        gate = nullptr;
    }

    m_contaningArea = QRect(QPoint(MINX, MAXY), QPoint(MAXX, MINY));
}

bool GateSelection::UpdateDrag(int x, int y)
{
    //Save button
    if(m_saveButton.contains(x, y))
    {
        m_pParent->StartSaveGateCollection(GetSelectedGates());
        return false;
    }

    //Delete button
    else if (m_deleteButton.contains(x, y))
    {
        //Keep gates in memory, but delete this
        delete this;

        return false;
    }

    //Delete all button
    else if (m_deleteAllButton.contains(x, y))
    {
        m_bDeleteGates = true;

        //Delete this & gates in memory
        delete this;

        return false;
    }

    if(m_dragMode == DragIndividual)
    {
        return false;
    }

    //Dragmode == DragAll
    else if(m_contaningArea.contains(QPoint(x, y)))
    {
        const QPoint previousPos = m_contaningArea.center();

        //Calculate difference between new & old pos
        Vector2D displacement = {x - previousPos.x(),
                                 y - previousPos.y()};

        //apply displacement to all gates and return true
        DisplaceGates(displacement);

        return true;
    }

    return false;
}

void GateSelection::DisplaceGates(Vector2D displacement)
{
    for(Gate** ppGate : m_ppGates)
    {
        Gate* gate = *ppGate;
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
        gate = nullptr;
    }
}

std::vector<Gate *> GateSelection::GetSelectedGates()
{
    std::vector<Gate*> retrievedGates;
    for(Gate** ppGate : m_ppGates)
    {
        retrievedGates.push_back((*ppGate));
    }
    return retrievedGates;
}

int GateSelection::Left()
{
    return m_contaningArea.left() + c_borderBoxMargin;
}
int GateSelection::Right()
{
    return m_contaningArea.right() - c_borderBoxMargin;
}
int GateSelection::Top()
{
    return m_contaningArea.top() + c_borderBoxMargin;
}
int GateSelection::Bottom()
{
    return m_contaningArea.bottom() - c_borderBoxMargin;
}
