#include "gatecollection.h"
#include "allgates.h"
#include "gatefield.h"

#include <QDebug>

namespace Settings
{
///Drawing
const QColor DragModeFillColor = QColor(40,40,40,20);
const QColor DragIndividualBoardeColor = Qt::black;
const uint DragIndividualBoardeSize = 2;

///UI Buttons
const QImage ImgDeleteAllButton = QImage(std::string(":/Resources/Button Icons/gate-collection-delete-all.png").c_str());
const QImage ImgSaveButton = QImage(std::string(":/Resources/Button Icons/gate-collection-save.png").c_str());
const QImage ImgDeleteButton = QImage(std::string(":/Resources/Button Icons/gate-collection-delete.png").c_str());
const QImage ImgDragButton = QImage(std::string(":/Resources/Button Icons/gate-collection-move-gates.png").c_str());
const QImage ImgOptimizeButton = QImage(std::string(":/Resources/Button Icons/gate-collection-optimize.png").c_str());
const QImage ImgNandOptimizeButton = QImage(std::string(":/Resources/Button Icons/gate-collection-nand.png").c_str());
const uint ButtonSize = 40;

//Number of pixels from border before gates are seen
const uint BorderBoxMargin = 40;
}

GateCollection::GateCollection(std::vector<Gate*> gates) :
    Gate::Gate(GATE_COLLECTION, 0, 0, 0, 0)
{
    m_gates = gates;
    UpdateContaningArea();
    ProporgateParentAndCheckForNestedGates();
}

void GateCollection::SetParent(GateField *gf)
{
    m_pParentField = gf;

    for (Gate* g : m_gates)
    {
        g->SetParent(m_pParentField);
    }
}

void GateCollection::ProporgateParentAndCheckForNestedGates()
{
    for (Gate* g : m_gates)
    {
        g->SetParent(m_pParentField);
        g->SetParentGateCollection(this);
    }
}

GateCollection::~GateCollection()
{
    //When deleted the gate collection filed can dump its contents onto the parent gatefield
    if(!m_bDontDeleteGates)
    {
        for(Gate* pGate : m_gates)
        {
            delete pGate;
        }
        m_gates.clear();
    }

    //dump contents onto the parent gatefield or parent gate collection...
    else
    {
        //Dump onto parent GateCollection
        if (m_pParentGateCollection)
        {
            for (Gate* g : m_gates)
                m_pParentGateCollection->AddGate(&*g);
        }

        //Dump onto parent ParentField
        else if (m_pParentField)
        {
            for (Gate* g : m_gates)
            {
                m_pParentField->AddGate(&*g, false);
                g->SetParentGateCollection(nullptr);
            }
        }

        //Check if something went wrong
        else
        {
            qDebug() << "GateCollection::~GateCollection - Nothing to dump gates onto!";
        }

        //Erase pointers to gates
        m_gates.clear();
    }
}

void GateCollection::UpdateOutput()
{
    for(Gate* gate : m_gates)
    {
        gate->UpdateOutput();
    }
}

bool GateCollection::FindNodeWithId(const id& id, Node*& pNode)
{
    for (Gate* gate : m_gates)
    {
        if(gate->FindNodeWithId(id, pNode))
            return true;
    }
    return false;
}

void GateCollection::offsetPosition(const int& dX, const int& dY)
{
    for (Gate* gate : m_gates)
    {
        gate->offsetPosition(dX, dY);
    }
    UpdateContaningArea();
}

void GateCollection::setPosition(const int &x, const int &y)
{
    const int xOffset = x - m_geometry.center().x();
    const int yOffset = y - m_geometry.center().y();
    offsetPosition(xOffset, yOffset);
}

void GateCollection::AssignNewNodeIds()
{
    for (Gate* gate : m_gates)
    {
        gate->AssignNewNodeIds();
    }
}

void GateCollection::collectLinkInfo(std::vector<NodeIds> &collection)
{
    for (Gate* gate : m_gates)
    {
        gate->collectLinkInfo(collection);
    }
}

void GateCollection::draw(QPainter& painter)
{
    UpdateContaningArea();

    if (m_dragMode == DragAll)
    {
         painter.fillRect(m_geometry, Settings::DragModeFillColor);
    }
    else if(m_dragMode == DragIndividual)
    {
        painter.setPen(QPen(Settings::DragModeFillColor, Settings::DragIndividualBoardeSize));
        painter.drawRect(m_geometry);
    }

    for(Gate* gate : m_gates)
    {
        gate->draw(painter);
    }

    DrawButtons(painter);
}

GameObject* GateCollection::checkClicked(const QPoint& mouse)
{
    if (m_dragMode == DragIndividual)
    {
        for(Gate* pGate : m_gates)
        {
            GameObject* pPossibleClickedObject = pGate->checkClicked(mouse);
            if(pPossibleClickedObject != nullptr)
            {
                return pPossibleClickedObject;
            }
        }
    }

    GameObject* pClicked = Gate::checkClicked(mouse);
    if(!pClicked)
    {
        checkButtonClick(mouse);
        return nullptr;
    }
    else
    {
        return pClicked;
    }
}

void GateCollection::DrawButtons(QPainter& painter)
{
    m_deleteAllButton  = QRect(m_geometry.right() - Settings::ButtonSize, m_geometry.bottom() - Settings::ButtonSize, Settings::ButtonSize, Settings::ButtonSize);
    m_deleteButton = QRect(m_geometry.right() - Settings::ButtonSize*2, m_geometry.bottom() - Settings::ButtonSize, Settings::ButtonSize, Settings::ButtonSize);
    m_saveButton = QRect(m_geometry.right() - Settings::ButtonSize*3, m_geometry.bottom() - Settings::ButtonSize, Settings::ButtonSize, Settings::ButtonSize);
    m_dragAllButton = QRect(m_geometry.right() - Settings::ButtonSize*4, m_geometry.bottom() - Settings::ButtonSize, Settings::ButtonSize, Settings::ButtonSize);
    //m_optimize = QRect(m_contaningArea.right() - xyButtonSize*5, m_contaningArea.bottom() - xyButtonSize, xyButtonSize, xyButtonSize);
    //m_nandOptimize = QRect(m_contaningArea.right() - xyButtonSize*6, m_contaningArea.bottom() - xyButtonSize, xyButtonSize, xyButtonSize);

    painter.drawImage(m_deleteAllButton, Settings::ImgDeleteAllButton);
    painter.drawImage(m_deleteButton, Settings::ImgDeleteButton);
    painter.drawImage(m_saveButton, Settings::ImgSaveButton);
    painter.drawImage(m_dragAllButton, Settings::ImgDragButton);
    //painter.drawImage(m_optimize, Settings::ImgOptimizeButton);
    //painter.drawImage(m_nandOptimize, Settings::ImgNandOptimizeButton);
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

void GateCollection::UpdateContaningArea()
{
    //Variables specifying boundaries of GateCollection
    //To be used to draw bounding box
    int MINX = std::numeric_limits<int>::max();
    int MINY = std::numeric_limits<int>::max();
    int MAXX = std::numeric_limits<int>::min();
    int MAXY = std::numeric_limits<int>::min();

    for(Gate* gate : m_gates)
    {
        if(gate->GetType() == GATE_COLLECTION)
        {
            if(dynamic_cast<GateCollection*>(gate))
                dynamic_cast<GateCollection*>(gate)->UpdateContaningArea();

            if(gate->geometry().bottom() < MINY)
            {
                MINY = gate->geometry().bottom() + Settings::BorderBoxMargin;
            }

            if(gate->geometry().top() > MAXY)
            {
                MAXY = gate->geometry().top() - Settings::BorderBoxMargin;
            }
        }
        else
        {
            if(gate->geometry().top() < MINY)
            {
                MINY = gate->geometry().top() - Settings::BorderBoxMargin;
            }

            if(gate->geometry().bottom() > MAXY)
            {
                MAXY = gate->geometry().bottom() + Settings::BorderBoxMargin;
            }
        }

        if(gate->geometry().left() < MINX)
        {
            MINX = gate->geometry().left() - Settings::BorderBoxMargin;
        }

        if(gate->geometry().right() > MAXX)
        {
            MAXX = gate->geometry().right() + Settings::BorderBoxMargin;
        }
    }

    m_geometry = QRect(QPoint(MINX, MAXY), QPoint(MAXX, MINY));
}

void GateCollection::ToggleDragMode()
{
    m_dragMode = (bool)m_dragMode ? DragIndividual : DragAll;
    m_pParentField->update();
}

bool GateCollection::IsDragAll()
{
    return (bool)m_dragMode;
}

void GateCollection::AddGate(Gate *g)
{
    g->SetParentGateCollection(this);
    g->SetParent(m_pParentField);

    m_gates.push_back(g);

    UpdateContaningArea();
}

void GateCollection::ForgetGate(Gate *g)
{
    for(size_t index = 0; index < m_gates.size(); index++)
    {
        if (m_gates[index] == g)
        {
            //Forget
            m_gates.erase(m_gates.begin() + index);

            //Exit early
            break;
        }
    }

    UpdateContaningArea();
}

//Returns true if buttons we're clicked
bool GateCollection::checkButtonClick(const QPoint& mouse)
{
    //Save button
    if(m_saveButton.contains(mouse))
    {
        m_pParentField->StartSaveGateCollection(this);
        return true;
    }

    //Delete button
    else if (m_deleteButton.contains(mouse))
    {
        //Keep gates in memory, but remove them from this list,
        //since we're deleting this collection, its gets dumped onto gatefield
        m_bDontDeleteGates = true;

        m_pParentField->UpdateGateSelected(nullptr);

        if (m_pParentGateCollection)
            m_pParentGateCollection->ForgetGate(this);
        else
            m_pParentField->ForgetChild(this);

        delete this;
        return true;
    }

    //Delete all button
    else if (m_deleteAllButton.contains(mouse))
    {
        m_pParentField->UpdateGateSelected(nullptr);

        if (m_pParentGateCollection)
            m_pParentGateCollection->ForgetGate(this);
        else
            m_pParentField->ForgetChild(this);

        delete this;
        return true;
    }

    /* //Optimize button
    else if (m_optimize.contains(mouse))
    {
        m_gates = CircuitOptimizer::Optimize(m_gates, false);
        return true;
    }*/

    else if (m_dragAllButton.contains(mouse))
    {
        ToggleDragMode();
        return true;
    }
    /*
    else if (m_nandOptimize.contains(mouse))
    {
        m_gates = CircuitOptimizer::Optimize(m_gates, true);
        return true;
    }*/

    return false;
}

Gate* GateCollection::Clone()
{
    std::vector<Gate*> clonedGates;
    for (Gate* pGate : m_gates)
    {
        clonedGates.push_back(pGate->Clone());
    }

    GateCollection* pClone = new GateCollection(clonedGates);

    pClone->m_geometry = m_geometry;

    return pClone;
}
