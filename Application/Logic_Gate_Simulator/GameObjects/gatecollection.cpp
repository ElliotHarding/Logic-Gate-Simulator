#include "gatecollection.h"
#include "allgates.h"
#include "gatefield.h"

#include <cmath>

namespace Settings
{
///Drawing
const QColor DragModeFillColor = QColor(40,40,40,20);
const QColor DragIndividualBoardeColor = Qt::black;
const uint DragIndividualBoardeSize = 5;

//Number of pixels from border before gates are seen
const int BorderBoxMargin = 40;
}

GateCollection::GateCollection(std::vector<Gate*> gates) :
    Gate::Gate(GATE_COLLECTION, 0, 0, 0, 0)
{
    for(Gate* pGate : gates)
    {
        addGate(pGate);
    }
}

GateCollection::~GateCollection()
{
    if(m_dragMode == DragAll)
    {
        for(Gate* pGate : m_gates)
        {
            pGate->setParentGateCollection(nullptr);
            delete pGate;
        }
    }

    else if(m_dragMode == DragIndividual)
    {
        //Dump onto parent GateCollection
        if (m_pParentGateCollection)
        {
            for (Gate* g : m_gates)
                m_pParentGateCollection->addGate(g);
        }

        //Dump onto parent ParentField
        else if (m_pParentField)
        {
            for (Gate* g : m_gates)
            {                
                g->setParentGateCollection(nullptr);
            }
            m_pParentField->addGates(m_gates);
        }
    }

    else
    {
        Logger::log(LL_Error, "GateCollection::~GateCollection - Unknown drag mode!");
    }
}

void GateCollection::setDeleteAll()
{
    m_dragMode = DragMode::DragAll;
}

void GateCollection::setParent(GateField *gf)
{
    m_pParentField = gf;

    for (Gate* g : m_gates)
    {
        g->setParent(m_pParentField);
    }
}

void GateCollection::updateOutput()
{
    for(Gate* gate : m_gates)
    {
        gate->updateOutput();
    }
}

bool GateCollection::findNodeWithId(const id& id, Node*& pNode)
{
    for (Gate* gate : m_gates)
    {
        if(gate->findNodeWithId(id, pNode))
            return true;
    }
    return false;
}

bool isAttachedToContainedGate(Gate* pTextLabel, std::vector<Gate*>& containedGates)
{
    for(Gate* pContainedGate : containedGates)
    {
        if(pContainedGate->hasAttachedLabel(pTextLabel))
        {
            return true;
        }
    }
    return false;
}

void GateCollection::offsetPosition(const int& dX, const int& dY)
{
    for (Gate* pContainedGate1 : m_gates)
    {
        //If theres a attached label don't offset it because its attached gate will
        if(pContainedGate1->getType() != GateType::GATE_TEXT_LABEL || !isAttachedToContainedGate(pContainedGate1, m_gates))
        {
            pContainedGate1->offsetPosition(dX, dY);
        }
    }
    updateContaningArea();

    for(Gate* pAttachedLabel : m_attachedLabels)
    {
        pAttachedLabel->offsetPosition(dX, dY);
    }
}

void GateCollection::setPosition(const int &x, const int &y)
{
    const int xOffset = x - m_geometry.center().x();
    const int yOffset = y - m_geometry.center().y();
    offsetPosition(xOffset, yOffset);
}

void GateCollection::assignNewNodeIds()
{
    for (Gate* gate : m_gates)
    {
        gate->assignNewNodeIds();
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
    if (m_dragMode == DragAll)
    {
         painter.fillRect(m_geometry, Settings::DragModeFillColor);
    }
    else if(m_dragMode == DragIndividual)
    {
        painter.setPen(QPen(Settings::DragModeFillColor, Settings::DragIndividualBoardeSize));
        painter.drawRect(m_geometry);
    }

    for (int index = m_gates.size() - 1; index > -1; index--)
    {
        m_gates[index]->draw(painter);
    }
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

    return Gate::checkClicked(mouse);
}

Node* GateCollection::checkClickedNodes(const QPoint& mouse)
{
    for(Gate* g : m_gates)
    {
        Node* pNode = g->checkClickedNodes(mouse);
        if(pNode)
        {
            return pNode;
        }
    }
    return nullptr;
}

void GateCollection::saveData(QDomDocument& storage, QDomElement& parentElement)
{
    QDomElement gateCollectionElement = storage.createElement(Settings::GateElement);

    saveGeneralData(storage, gateCollectionElement);

    for(Gate* gate : m_gates)
    {
        gate->saveData(storage, gateCollectionElement);
    }

    parentElement.appendChild(gateCollectionElement);
}

void GateCollection::updateContaningArea()
{
    //Variables specifying boundaries of GateCollection
    //To be used to draw bounding box
    int MINX = std::numeric_limits<int>::max();
    int MINY = std::numeric_limits<int>::max();
    int MAXX = std::numeric_limits<int>::min();
    int MAXY = std::numeric_limits<int>::min();

    for(Gate* gate : m_gates)
    {
        if(gate->geometry().top() - Settings::BorderBoxMargin < MINY)
        {
            MINY = gate->geometry().top() - Settings::BorderBoxMargin;
        }

        if(gate->geometry().bottom() + Settings::BorderBoxMargin > MAXY)
        {
            MAXY = gate->geometry().bottom() + Settings::BorderBoxMargin;
        }

        if(gate->geometry().left() - Settings::BorderBoxMargin < MINX)
        {
            MINX = gate->geometry().left() - Settings::BorderBoxMargin;
        }

        if(gate->geometry().right() + Settings::BorderBoxMargin > MAXX)
        {
            MAXX = gate->geometry().right() + Settings::BorderBoxMargin;
        }
    }

    m_geometry = QRect(QPoint(MINX, MINY), QPoint(MAXX, MAXY));

    if(m_pParentGateCollection)
    {
        m_pParentGateCollection->updateContaningArea();
    }
}

void GateCollection::toggleDragMode()
{
    m_dragMode = (bool)m_dragMode ? DragIndividual : DragAll;
    m_pParentField->updateGateSelected(this);
    m_pParentField->update();
}

void GateCollection::addGate(Gate *g)
{
    g->setParentGateCollection(this);
    g->setParent(m_pParentField);

    if(g->getType() == GateType::GATE_TEXT_LABEL)
    {
        m_gates.insert(m_gates.begin(), g);
    }
    else
    {
        m_gates.push_back(g);
    }

    updateContaningArea();
}

void GateCollection::forgetGate(Gate *g)
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

    updateContaningArea();
}

std::vector<Gate *> GateCollection::getGates()
{
    return m_gates;
}

Gate* GateCollection::clone()
{
    std::vector<Gate*> clonedGates;
    for (Gate* pGate : m_gates)
    {
        clonedGates.push_back(pGate->clone());
    }

    GateCollection* pClone = new GateCollection(clonedGates);
    Gate::baseClone(pClone);

    //pClone->m_geometry = m_geometry; - done in constructor
    pClone->m_dragMode = m_dragMode;

    return pClone;
}

TextLabel* GateCollection::findTextLabelWithId(int id)
{
    for (Gate* pGate : m_gates)
    {
        if(pGate->getType() == GateType::GATE_TEXT_LABEL)
        {
            if(dynamic_cast<TextLabel*>(pGate)->attachId() == id)
            {
                return dynamic_cast<TextLabel*>(pGate);
            }
        }
        else if(pGate->getType() == GateType::GATE_COLLECTION)
        {
            TextLabel* pPotentialAttachedLabel = dynamic_cast<GateCollection*>(pGate)->findTextLabelWithId(id);
            if(pPotentialAttachedLabel)
            {
                return pPotentialAttachedLabel;
            }
        }
    }
    return nullptr;
}

void GateCollection::switchAttachedLabels(std::vector<Gate*> gates)
{
    for (size_t i = 0; i < m_gates.size(); i++)
    {
        m_gates[i]->switchAttachedLabels(gates);
    }

    Gate::switchAttachedLabels(gates);
}
