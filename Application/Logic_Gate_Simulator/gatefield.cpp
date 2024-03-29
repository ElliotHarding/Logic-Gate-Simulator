#include "gatefield.h"
#include "dlg_home.h"

#include <QApplication>

namespace Settings
{
const QPen LinkingNodeLine(Qt::blue, 2);
const QPen SelectionBorder(Qt::blue, 2);

const float PanSpeed = 0.75;
const qreal ZoomScrollSpeed = 0.05;

const uint MaxGateFieldHistory = 20;
}

GateField::GateField(DLG_Home* pParent, const qreal& zoomFactor, const QString& name, const uint& updateFrequency) :
    QWidget(pParent),
    m_pParent(pParent),
    m_name(name),
    m_gateUpdateFrequencyMs(updateFrequency),
    m_zoomFactor(zoomFactor)
{
    setAcceptDrops(true);
    setMouseTracking(true);

    connect(&m_gateUpdateTimer, SIGNAL(timeout()), this, SLOT(onrequestUpdateGates()));
    m_gateUpdateTimer.setTimerType(Qt::PreciseTimer);

    //Todo : only running when page is showing? Or make use of multiple pages running
    m_gateUpdateTimer.start(m_gateUpdateFrequencyMs);
}

GateField::~GateField()
{
    //Belongs to parent DLG_Home
    m_pParent = nullptr;

    //Delete all gates
    for (size_t index = m_allGates.size() - 1; index > -1 ; index--)
    {
        m_allGates[index]->setParent(nullptr);
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

void GateField::onrequestUpdateGates()
{
    for (int index = m_gatesToUpdate.size() - 1; index > -1; index--)
    {
        m_gatesToUpdate[size_t(index)]->updateOutput();
    }
    m_gatesToUpdate.clear();
    update();
}

void GateField::setZoomLevel(const qreal& zoom)
{
    m_zoomFactor = zoom;
    update();
}

void GateField::saveData(QDomDocument& saveFile)
{
    QDomElement gateFieldElement = saveFile.createElement(Settings::GateFieldElement);
    gateFieldElement.setAttribute(Settings::GateFieldFrequencyTag, QString::number(m_gateUpdateFrequencyMs));
    for (size_t index = 0; index < m_allGates.size(); index++)
    {        
        m_allGates[index]->saveData(saveFile, gateFieldElement);
    }
    saveFile.appendChild(gateFieldElement);
}

void GateField::forgetChild(Gate* pGateToForget)
{
    for(size_t index = 0; index < m_allGates.size(); index++)
    {
        if (m_allGates[index] == pGateToForget)
        {
            //forget
            m_allGates.erase(m_allGates.begin() + int8_t(index));

            forgetUpdateRequest(pGateToForget);

            return;
        }
    }
}

void GateField::forgetUpdateRequest(Gate* pGate)
{
    //Todo ~ Find out why can't use m_gatesToUpdate.erase

    std::vector<Gate*> newGatesToUpdate;
    for(size_t index = 0; index < m_gatesToUpdate.size(); index++)
    {
        if(m_gatesToUpdate[index] != pGate)
            newGatesToUpdate.push_back(m_gatesToUpdate[index]);
    }
    m_gatesToUpdate = newGatesToUpdate;
}

void GateField::requestUpdateGate(Gate* pGate)
{
    for(size_t index = 0; index < m_gatesToUpdate.size(); index++)
    {
        if(m_gatesToUpdate[index] == pGate)
            return;
    }
    m_gatesToUpdate.push_back(pGate);
}

void GateField::undo()
{
    m_history.undoHistory(m_allGates);

    //Call to redraw
    update();
}

void GateField::redo()
{
    m_history.redoHistory(m_allGates);

    //Call to redraw
    update();
}

void GateField::setName(const QString& name)
{
    m_name = name;
}

QString GateField::name() const
{
    return m_name;
}

void GateField::addGate(Gate* go, const bool& newlySpawned)
{
    go->setParent(this);

    if(newlySpawned) //If newley spawned has GateField::QWidget relative position
    {
        const QPoint worldPos = qtPointToWorldPoint(go->position());
        go->setPosition(worldPos.x(), worldPos.y());
    }

    //Put new gate at front so its on top of others
    // - Lazy way todo it
    m_allGates.push_back(go);
    moveToFront(m_allGates.size()-1, m_allGates);

    updateGateSelected(go);

    m_pParent->setCurrentClickMode(CLICK_DRAG);

    m_history.recordHistory(m_allGates);

    //Call to redraw
    update();
}

void GateField::addGates(std::vector<Gate*>& gates)
{
    for(Gate* go : gates)
    {
        go->setParent(this);

        //Put new gate at front so its on top of others
        // - Lazy way todo it
        m_allGates.push_back(go);
        moveToFront(m_allGates.size()-1, m_allGates);
    }

    updateGateSelected(gates[gates.size()-1]);

    m_pParent->setCurrentClickMode(CLICK_DRAG);

    m_history.recordHistory(m_allGates);

    //Call to redraw
    update();
}

void GateField::mousePressEvent(QMouseEvent *click)
{
    const QPoint clickPos = qtPointToWorldPoint(click->pos());

    //Update variables
    m_bMouseDown = true;

    if(m_pLinkingNode)
    {
        m_pLinkingNode = nullptr;
    }

    if(click->buttons() & Qt::LeftButton)
    {
        switch (m_pParent->currentClickMode())
        {
        case CLICK_DELETE_GATE:
            checkDelete(clickPos);
            break;

        case CLICK_DELETE_LINK_NODES:
            checkDeleteNodeLink(clickPos);
            break;

        case CLICK_PAN:
            m_previousDragMousePos = clickPos;
            break;

        case CLICK_LINK_NODES:
            if(!checkStartLink(clickPos))
            {
                if(!checkGateSelect(clickPos))
                {
                    editSelection(clickPos);
                }
            }
            break;

        case CLICK_DRAG:
            if(!checkStartDrag(clickPos))
            {
                if(!checkGateSelect(clickPos))
                {
                    editSelection(clickPos);
                }
            }
            break;
        case CLICK_SELECTION:
            Logger::log(LL_Error, "GateField::mousePressEvent - Invalid current click mode (Selection)");
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

    switch (m_pParent->currentClickMode())
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

    //Check if ending a link attempt
    if(m_pLinkingNode)
    {
        checkEndLink(qtPointToWorldPoint(click->pos()));
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
                forgetChild(g);

            //Add gate collection to m_allGates
            addGate(collection, false);

            m_history.recordHistory(m_allGates);

            m_pParent->setCurrentClickMode(CLICK_DRAG);
        }

        //Disactivate selection
        delete m_pSelectionTool;
        m_pSelectionTool = nullptr;

        m_pParent->restorePreviousClickMode();

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
    if (m_pParent->setZoomFactor(m_zoomFactor + direction, true))
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
            m_pParent->setCurrentClickMode(CLICK_LINK_NODES);
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
            //Check not the same node as one linking to
            if(pPossibleClickedNode == m_pLinkingNode)
            {
                break;
            }

            //Check not same node types
            if(pPossibleClickedNode->type() == m_pLinkingNode->type())
            {
                m_pParent->sendUserMessage("Cant link to nodes of same type");
                break;
            }

            //Check both dont have same parent
            if(pPossibleClickedNode->getParent() == m_pLinkingNode->getParent())
            {
                break;
            }

            //link nodes & update parent gates (inside linkNode())
            bool n1Linked = pPossibleClickedNode->linkNode(m_pLinkingNode);
            bool n2Linked = m_pLinkingNode->linkNode(pPossibleClickedNode);

            if(!n1Linked && !n2Linked)
            {
                if(n1Linked)
                {
                    pPossibleClickedNode->detachNode();
                }

                if(n2Linked)
                {
                    m_pLinkingNode->detachNode();
                }

                Logger::log(LL_Error, "GateField::checkEndLink - Linking failed!");
            }
            else
            {
                m_history.recordHistory(m_allGates);
            }
        }
    }

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
            pPossibleClickedNode->detachNode();
            update();
            return;
        }
    }
}

bool GateField::checkGateSelect(const QPoint& mouse)
{
    for (Gate* gate : m_allGates)
    {
        GameObject* pSelectedGo = gate->checkClicked(mouse);
        if(pSelectedGo != nullptr && dynamic_cast<Gate*>(pSelectedGo))
        {
            updateGateSelected(dynamic_cast<Gate*>(pSelectedGo));
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

        m_pParent->saveCurrentClickMode();
        m_pParent->setCurrentClickMode(CLICK_SELECTION);
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
        GameObject* pPotentiallyClickedObject = m_allGates[index]->checkClicked(mouse);
        if(pPotentiallyClickedObject != nullptr && dynamic_cast<Gate*>(pPotentiallyClickedObject))
        {
            Gate* gObject = dynamic_cast<Gate*>(pPotentiallyClickedObject);

            //Need to check that gObject is actually stored in m_allGates
            if(m_allGates[index] == gObject)
            {
                m_allGates.erase(m_allGates.begin() + index);
            }

            delete gObject;

            updateGateSelected(nullptr);
            update();
            return;
        }
    }
}

bool GateField::checkStartDrag(const QPoint& mouse)
{
    //Look for a gate to drag

    //Loop through all dragable gameobjects
    for (size_t index = 0; index < m_allGates.size(); index++)
    {
        GameObject* pPossibleClickedObject = m_allGates[index]->checkClicked(mouse);
        if(pPossibleClickedObject != nullptr && dynamic_cast<Gate*>(pPossibleClickedObject))
        {
            m_pDraggingGate = dynamic_cast<Gate*>(pPossibleClickedObject);
            updateGateSelected(m_pDraggingGate);

            //Move the dragged object to the front of the array.
            //This way next loop the object will be checked first
            //This means if you drag an object over another, the object being dragged wont switch
            moveToFront(index, m_allGates);

            update();
            return true;
        }
    }

    return false;
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

    //Is the gate moving to front a textlabel?
    if(objectAtIndex->getType() == GateType::GATE_TEXT_LABEL)
    {
        vec.insert(vec.begin(), objectAtIndex);
    }
    else
    {
        //Move to front after all textlabels (they always go on top)
        for(uint i = 0; i < vec.size(); i++)
        {
            if(vec[i]->getType() != GateType::GATE_TEXT_LABEL)
            {
                vec.insert(vec.begin() + i, objectAtIndex);
                return;
            }
        }

        vec.insert(vec.begin() + vec.size(), objectAtIndex);
    }
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

void GateField::updateGateSelected(Gate *g)
{
    if(m_pParent)
        m_pParent->gateSelected(g);
}

void GateField::sendUserMessage(const QString& message)
{
    if(m_pParent)
        m_pParent->sendUserMessage(message);
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
        clonedSnapshot.push_back(g->clone());
    }

    //Todo : could merge clone() and collectLinkInfo() for gate. Unless decide todo them individually elsewhere...

    //Copy link info into clonedSnapshot gates
    std::vector<NodeIds> linkInfo;
    for(Gate* g : snapshot)
    {
        g->collectLinkInfo(linkInfo);
    }
    GateReader::linkNodes(clonedSnapshot, linkInfo);

    for(Gate* g : clonedSnapshot)
    {
        g->assignNewNodeIds();
        g->switchAttachedLabels(clonedSnapshot);
    }

    //Remove all history saves after current m_historyIndex
    for(size_t i = m_historyIndex + 1; i < m_history.size(); i++)
    {
        for (size_t index = m_history[i].size() - 1; index > -1 ; index--)
        {
            if(m_history[i][index]->getType() == GateType::GATE_COLLECTION)
            {
                dynamic_cast<GateCollection*>(m_history[i][index])->setDeleteAll();
            }
            delete m_history[i][index];
        }
    }

    m_history.push_back(clonedSnapshot);

    //Delete excess history - todo : test if crash without reverse
    if(Settings::MaxGateFieldHistory < m_history.size())
    {
        deleteIndexOfHistory(0);
        m_history.erase(m_history.begin());
    }

    m_historyIndex = m_history.size() - 1;
}

bool GateFieldHistory::undoHistory(std::vector<Gate*>& currentSnapshot)
{
    if(m_historyIndex > 0)
    {       
        if(m_historyIndex == m_history.size() - 1)
        {
            deleteIndexOfHistory(m_historyIndex);
            m_history[m_historyIndex] = currentSnapshot;
        }

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
        for (size_t index = historyItem.size() - 1; index > -1 ; index--)
        {
            if(historyItem[index]->getType() == GateType::GATE_COLLECTION)
            {
                dynamic_cast<GateCollection*>(historyItem[index])->setDeleteAll();
            }
            delete historyItem[index];
        }
    }
}

void GateFieldHistory::deleteIndexOfHistory(const size_t& historyIndex)
{
    for (size_t index = m_history[historyIndex].size() - 1; index > -1 ; index--)
    {
        if(m_history[historyIndex][index]->getType() == GateType::GATE_COLLECTION)
        {
            dynamic_cast<GateCollection*>(m_history[historyIndex][index])->setDeleteAll();
        }
        delete m_history[historyIndex][index];
    }
}
