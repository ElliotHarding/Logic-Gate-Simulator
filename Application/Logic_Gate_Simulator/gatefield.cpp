#include "gatefield.h"
#include "dlg_home.h"
#include "dlg_savegatecollection.h"
#include "gate.h"
#include "GateToggle.h"
#include "GateTimer.h"
#include "gatecollection.h"

#include <QApplication>
#include <QDebug>

namespace Settings
{
const QPen LinkingNodeLine(Qt::blue, 2);
const QPen SelectionBorder(Qt::blue, 2);

const float PanSpeed = 0.75;
const qreal ZoomScrollSpeed = 0.05;

const uint MaxGateFieldHistory = 20;

const uint DefaultUpdateFrequencyMs = 200;
}

GateField::GateField(DLG_Home* pParent, const qreal& zoomFactor, const QString& name, DLG_SaveGateCollection* pSaveGateCollectionDialog) :
    QWidget(pParent),
    m_pParent(pParent),
    m_name(name),
    m_zoomFactor(zoomFactor),
    m_pDlgSaveGateCollection(pSaveGateCollectionDialog)
{
    setAcceptDrops(true);
    setMouseTracking(true);

    connect(&m_gateUpdateTimer, SIGNAL(timeout()), this, SLOT(onRequestUpdateGates()));
    m_gateUpdateTimer.setTimerType(Qt::PreciseTimer);
    m_gateUpdateFrequencyMs = Settings::DefaultUpdateFrequencyMs;

    //Todo : only running when page is showing? Or make use of multiple pages running
    m_gateUpdateTimer.start(m_gateUpdateFrequencyMs);
}

GateField::~GateField()
{
    //Belongs to parent DLG_Home
    m_pDlgSaveGateCollection = nullptr;
    m_pParent = nullptr;

    //Delete all gates
    for (size_t index = 0; index < m_allGates.size(); index++)
    {
        delete m_allGates[index];
    }

    if(m_pLinkingNode)
        delete m_pLinkingNode;

    if(m_pSelectionTool)
        delete m_pSelectionTool;
}

void GateField::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::HighQualityAntialiasing, true);

    //Zooming
    painter.translate(geometry().center().x(), geometry().center().y());
    painter.scale(m_zoomFactor, m_zoomFactor);

    //If were currently selecting an area
    if(m_pSelectionTool)
    {
        painter.setPen(Settings::SelectionBorder);
        painter.drawRect(m_pSelectionTool->geometry());
    }

    //Paint in reverse order, so gate on top of vector get's painted last
    //So if we're dragging, the one we're dragging gets painted ontop of the others
    //Since dragging move the gate to the top of the vector
    for (int index = m_allGates.size() - 1; index > -1; index--)
    {
        m_allGates[size_t(index)]->draw(painter);
    }

    //If were in the middle of linking
    if(m_pLinkingNode)
    {
        painter.setPen(Settings::LinkingNodeLine);
        painter.drawLine(m_pLinkingNode->position(), m_currentMousePos);
    }
}

ClickMode GateField::GetCurrentClickMode()
{
    return m_currentClickMode;
}

void GateField::setCurrentClickMode(const ClickMode& mode)
{
    m_currentClickMode = mode;
}

void GateField::setUpdateFrequency(const uint& frequencyMs)
{
    m_gateUpdateFrequencyMs = frequencyMs;

    m_gateUpdateTimer.stop();
    m_gateUpdateTimer.start(frequencyMs);

    //Todo : only running when page is showing? Or make use of multiple pages running
}

uint GateField::updateFrequency() const
{
    return m_gateUpdateFrequencyMs;
}

void GateField::editFPGA(GateFPGA* pFPGA)
{
    m_pParent->editFPGA(pFPGA);
}

void GateField::onRequestUpdateGates()
{
    for (int index = m_allGates.size() - 1; index > -1; index--)
    {
        m_allGates[size_t(index)]->UpdateOutput();
    }
    update();
}

void GateField::SetZoomLevel(const qreal& zoom)
{
    m_zoomFactor = zoom;
    update();
}

void GateField::SaveData(QDomDocument& saveFile, QDomElement& gateFieldElement)
{
    for (size_t index = 0; index < m_allGates.size(); index++)
    {        
        m_allGates[index]->SaveData(saveFile, gateFieldElement);
    }
}

void GateField::DeleteGate(Gate* gateToDelete)
{
    for(size_t index = 0; index < m_allGates.size(); index++)
    {
        if (m_allGates[index] == gateToDelete)
        {
            //Find & remove from vector
            m_allGates.erase(m_allGates.begin() + int8_t(index));
            delete gateToDelete;

            return;
        }
    }
}

void GateField::ForgetChild(Gate* gateToDelete)
{
    for(size_t index = 0; index < m_allGates.size(); index++)
    {
        if (m_allGates[index] == gateToDelete)
        {
            //forget
            m_allGates.erase(m_allGates.begin() + int8_t(index));
            return;
        }
    }
}

void GateField::Undo()
{
    m_history.undoHistory(m_allGates);

    //Call to redraw
    update();
}

void GateField::Redo()
{
    m_history.redoHistory(m_allGates);

    //Call to redraw
    update();
}

void GateField::EditTextLabel(TextLabel *textLabelToEdit)
{
    m_pParent->EditTextLabel(textLabelToEdit);
}

void GateField::StartSaveGateCollection(GateCollection* pGateCollection)
{
    m_pDlgSaveGateCollection->open(pGateCollection);
}

QString GateField::name() const
{
    return m_name;
}

void GateField::AddGate(Gate* go, const bool& newlySpawned)
{
    go->SetParent(this);

    if(newlySpawned)
    {
        QPoint center = qtPointToWorldPoint(QPoint(geometry().width()/2, geometry().height()/2));
        go->setPosition(center.x(), center.y());
    }

    m_allGates.push_back(go);
    UpdateGateSelected(go);

    //Temp. When newlySpawned position stuff changes.
    m_history.recordHistory(m_allGates);

    //Call to redraw
    update();
}

void GateField::mousePressEvent(QMouseEvent *click)
{
    const QPoint clickPos = qtPointToWorldPoint(click->pos());

    //Update variables
    m_bMouseDown = true;
    m_previousDragMousePos = clickPos; //Todo : probably dont need these previous and current anymore.

    if(m_pLinkingNode)
    {
        m_pLinkingNode = nullptr;
        m_pParent->SetCurrentClickMode(CLICK_DEFAULT);
    }

    if(click->buttons() & Qt::LeftButton)
    {
        switch (m_currentClickMode)
        {
        case CLICK_DELETE_GATE:
            checkDelete(clickPos);
            break;

        case CLICK_DELETE_LINK_NODES:
            checkDeleteNodeLink(clickPos);
            break;

        case CLICK_SELECTION:
            editSelection(clickPos);
            break;

        case CLICK_PAN:
            m_previousDragMousePos = clickPos;
            break;

        case CLICK_DEFAULT:
            if(!checkStartLink(clickPos))
            {
                if(!checkGateSelect(clickPos))
                {
                    editSelection(clickPos);
                }
            }
            break;

        case CLICK_DRAG:
            checkStartDrag(clickPos);
            break;
        }
    }
    else if(click->buttons() & Qt::RightButton)
    {
        checkGateSelect(clickPos);
    }
    else if(click->buttons() & Qt::MiddleButton)
    {
        checkDeleteNodeLink(clickPos);
    }
}

void GateField::mouseMoveEvent(QMouseEvent *click)
{
    const QPoint clickPos = qtPointToWorldPoint(click->pos());

    switch (m_currentClickMode)
    {
        case CLICK_DRAG:
            if(m_pDraggingGate)
            {
                m_pDraggingGate->setPosition(clickPos.x(), clickPos.y());
                update();
            }
            break;

        case CLICK_PAN:
            if(m_bMouseDown)
            {
                doPan(clickPos);
            }
            break;

        case CLICK_SELECTION:
            if (m_bMouseDown)
            {
                editSelection(clickPos);
            }
            break;

        case CLICK_LINK_NODES:
            if(m_pLinkingNode)
            {
                m_currentMousePos = clickPos;
                update();
            }
            break;

        default:
            break;
    }
}

void GateField::mouseReleaseEvent(QMouseEvent* click)
{
    m_bMouseDown = false;

    //If ending a dragging session
    if(m_pDraggingGate)
    {
        m_pDraggingGate = nullptr;
        m_history.recordHistory(m_allGates);
        return;
    }

    const QPoint clickPos = qtPointToWorldPoint(click->pos());

    //Check if ending a link attempt
    if(m_pLinkingNode)
    {
        checkEndLink(clickPos);
    }

    //If ending a selection
    if(m_pSelectionTool != nullptr)
    {
        m_selectedGates.clear();

        //Get all gates inside surrounding m_pSelectionTool
        for (Gate* gate : m_allGates)
        {
            if(m_pSelectionTool->geometry().contains(gate->position()))
            {
                m_selectedGates.push_back(gate);
            }
        }

        //Add the gates to collection
        if(m_selectedGates.size() > 1)
        {
            GateCollection* collection = new GateCollection(m_selectedGates);

            //Remove gates from m_allgates
            for (Gate* g : m_selectedGates)
                ForgetChild(g);

            //Add gate collection to m_allGates
            AddGate(collection, false);

            m_history.recordHistory(m_allGates);
        }

        //Disactivate selection
        delete m_pSelectionTool;
        m_pSelectionTool = nullptr;

        m_pParent->SetCurrentClickMode(CLICK_DRAG);

        //Call to redraw
        update();
    }
}

//Handles mouse scroll for zooming, offsets gates based on mouse position
void GateField::wheelEvent(QWheelEvent *event)
{
    const qreal direction = event->delta() > 0 ? Settings::ZoomScrollSpeed : -Settings::ZoomScrollSpeed;

    //Todo : seems stupid to set zoom factor for all gatefeilds
    //Only offset gates if zoom factor actually changes
    if (m_pParent->SetZoomFactor(m_zoomFactor + direction, true))
    {
        const QPoint scrollPos = qtPointToWorldPoint(event->pos());

        //Calcualte vector between previous mouse pos and current
        const double offsetX = -scrollPos.x() * direction;
        const double offsetY = -scrollPos.y() * direction;

        //Offset the gates
        offsetGates(offsetX, offsetY);
    }
}

bool GateField::checkStartLink(const QPoint& mouse)
{
    for (Gate* g : m_allGates)
    {
        m_pLinkingNode = g->checkClickedNodes(mouse);
        if(m_pLinkingNode != nullptr)
        {
            m_currentMousePos = m_pLinkingNode->position();

            //Change cursor as started linking
            m_pParent->SetCurrentClickMode(CLICK_LINK_NODES);
            update();
            return true;
        }
    }
    return false;
}

void GateField::checkEndLink(const QPoint& mouse)
{
    for (Gate* g : m_allGates)
    {
        Node* pPossibleClickedNode = g->checkClickedNodes(mouse);
        if(pPossibleClickedNode != nullptr)
        {
            //Check not same node types
            if(pPossibleClickedNode->type() == m_pLinkingNode->type())
            {
                m_pParent->SendUserMessage("Cant link to nodes of same type");
                m_pLinkingNode = nullptr;
                update();
                return;
            }

            //Check both dont have same parent
            if(pPossibleClickedNode->GetParent() == m_pLinkingNode->GetParent())
            {
                m_pLinkingNode = nullptr;
                update();
                return;
            }

            //link nodes & update parent gates (inside LinkNode())
            bool n1Linked = pPossibleClickedNode->LinkNode(m_pLinkingNode);
            bool n2Linked = m_pLinkingNode->LinkNode(pPossibleClickedNode);

            if(!n1Linked && !n2Linked)
            {
                if(n1Linked)
                {
                    pPossibleClickedNode->DetachNode();
                }

                if(n2Linked)
                {
                    m_pLinkingNode->DetachNode();
                }

                qDebug() << "GateField::checkEndLink - Linking failed!";
            }
            else
            {
                m_history.recordHistory(m_allGates);
            }
        }
    }

    m_pParent->SetCurrentClickMode(CLICK_DEFAULT);
    m_pLinkingNode = nullptr;
    update();
}

void GateField::checkDeleteNodeLink(const QPoint& mouse)
{
    for (Gate* gate : m_allGates)
    {
        //Check if iterated gate has any clicked nodes
        Node* pPossibleClickedNode = gate->checkClickedNodes(mouse);
        if(pPossibleClickedNode != nullptr)
        {
            pPossibleClickedNode->DetachNode();
            update();
            return;
        }
    }
}

bool GateField::checkGateSelect(const QPoint& mouse)
{
    for (Gate* gate : m_allGates)
    {
        if(gate->checkClicked(mouse))
        {
            UpdateGateSelected(gate);
            return true;
        }
    }
    return false;
}

void GateField::editSelection(const QPoint& mouse)
{
    //If start of new selection
    if(m_pSelectionTool == nullptr)
    {
        m_pSelectionTool = new QRubberBand(QRubberBand::Rectangle, this);
        m_selectionToolOrigin = mouse;
        m_pSelectionTool->setGeometry(QRect(m_selectionToolOrigin, QSize()));

        setCurrentClickMode(CLICK_SELECTION);
    }
    else
    {
        m_pSelectionTool->setGeometry(QRect(m_selectionToolOrigin, mouse).normalized());
    }

    update();
}

void GateField::checkDelete(const QPoint& mouse)
{
    for (size_t index = 0; index < m_allGates.size(); index++)
    {     
        if(m_allGates[index]->checkClicked(mouse))
        {
            Gate* gObject = m_allGates[index];
            m_allGates.erase(m_allGates.begin() + index);
            delete gObject;

            UpdateGateSelected(nullptr);
            update();
            return;
        }
    }
}

void GateField::checkStartDrag(const QPoint& mouse)
{
    //Look for a gate to drag

    //Loop through all dragable gameobjects
    for (size_t index = 0; index < m_allGates.size(); index++)
    {
        GameObject* pPossibleClickedObject = m_allGates[index]->checkClicked(mouse);
        if(pPossibleClickedObject != nullptr && dynamic_cast<Gate*>(pPossibleClickedObject))
        {
            m_pDraggingGate = dynamic_cast<Gate*>(pPossibleClickedObject);
            UpdateGateSelected(m_allGates[index]);

            //Move the dragged object to the front of the array.
            //This way next loop the object will be checked first
            //This means if you drag an object over another, the object being dragged wont switch
            moveToFront(index, m_allGates);

            update();
            return;
        }
    }
}

void GateField::doPan(const QPoint& mouse)
{
    //Calcualte vector between previous mouse pos and current
    const float offsetX = Settings::PanSpeed * (mouse.x() - m_previousDragMousePos.x());
    const float offsetY = Settings::PanSpeed * (mouse.y() - m_previousDragMousePos.y());

    offsetGates(offsetX, offsetY);

    m_previousDragMousePos = mouse;
}

void GateField::moveToFront(const uint& index, std::vector<Gate *> &vec)
{
    Gate* objectAtIndex = vec[index];

    vec.erase(vec.begin() + index);
    vec.insert(vec.begin(), objectAtIndex);
}

void GateField::offsetGates(const double& offsetX, const double& offsetY)
{
    //Apply delta
    for (Gate* g : m_allGates)
        g->offsetPosition(offsetX, offsetY);

    update();
}

QPoint GateField::qtPointToWorldPoint(const QPoint& mousePoint) const
{
    QTransform transform;
    transform.scale(m_zoomFactor, m_zoomFactor);
    return transform.inverted().map(QPoint(mousePoint.x() - geometry().center().x(), mousePoint.y() - geometry().center().y()));
}

void GateField::UpdateGateSelected(Gate *g)
{
    if(m_pParent)
        m_pParent->GateSelected(g);
}

////////////////////////////////////////////////////////////////////////////////////////
/// GateFieldHistory
///
/// Records history of GateField
///
/// TODO : Only record changes, not entire list of gates
void GateFieldHistory::recordHistory(const std::vector<Gate*>& snapshot)
{
    std::vector<Gate*> clonedSnapshot;
    for(Gate* g : snapshot)
    {
        clonedSnapshot.push_back(g->Clone());
    }

    //Todo : could merge Clone() and collectLinkInfo() for gate. Unless decide todo them individually elsewhere...

    //Copy link info into clonedSnapshot gates
    std::vector<NodeIds> linkInfo;
    for(Gate* g : snapshot)
    {
        g->collectLinkInfo(linkInfo);
    }
    GateReader::linkNodes(clonedSnapshot, linkInfo);

    for(Gate* g : clonedSnapshot)
    {
        g->AssignNewNodeIds();
    }

    m_history.push_back(clonedSnapshot);

    if(Settings::MaxGateFieldHistory < m_history.size())
    {
        for (size_t index = 0; index < m_history[0].size(); index++)
        {
            delete m_history[0][index];
        }
        m_history.erase(m_history.begin());
    }

    m_historyIndex = m_history.size() - 1;
}

bool GateFieldHistory::undoHistory(std::vector<Gate*>& currentSnapshot)
{
    if(m_historyIndex > 0)
    {
        currentSnapshot = m_history[--m_historyIndex];
        return true;
    }
    return false;
}

bool GateFieldHistory::redoHistory(std::vector<Gate*>& currentSnapshot)
{
    if(m_historyIndex < m_history.size() - 1)
    {
        currentSnapshot = m_history[++m_historyIndex];
        return true;
    }
    return false;
}

GateFieldHistory::~GateFieldHistory()
{
    for(std::vector<Gate*> historyItem : m_history)
    {
        for (size_t index = 0; index < historyItem.size(); index++)
        {
            delete historyItem[index];
        }
    }
}
