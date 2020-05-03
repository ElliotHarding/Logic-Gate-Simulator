#include "gatefield.h"
#include "dlg_home.h"
#include "dlg_savegatecollection.h"

#include <QApplication>

GateField::GateField(qreal zoomFactor, std::string name, DLG_Home* parent, DLG_SaveGateCollection* saveGateCollectionDialog, bool disableGateCollections, bool bDisableGateBackup) :
    QWidget(parent),
    m_pParent(parent),
    m_name(name),
    m_bDisableGateBackup(bDisableGateBackup),
    m_zoomFactor(zoomFactor),
    m_pDlgSaveGateCollection(saveGateCollectionDialog),
    m_pTimerThread(new TimerThread(this)),
    m_bDisableGateCollections(disableGateCollections)
{
    setAcceptDrops(true);
    setMouseTracking(true);

    m_screenPosDelta.x = 0;
    m_screenPosDelta.y = 0;

    //m_pParent->SetCurrentClickMode(CLICK_DRAG);

    saveGateCollectionDialog->SetCurrentGateField(this);

    //Reserve memory for gates
    m_allGates.reserve(20);
    m_gateBackups.reserve(20);
    for(std::vector<Gate*> g : m_gateBackups)
    {
        g.reserve(20);
    }

    const QRect geo = geometry();
    m_centerScreen = geo.center();

    m_pTimerThread->start();
}

GateField::~GateField()
{
    Enabled = false;

    m_pTimerThread->InitStop();

    //VERY VERY VERY VERY VERY BAD
    QThread::msleep(10);

    m_pTimerThread->quit();
    delete m_pTimerThread;

    //Belongs to parent DLG_Home
    m_pDlgSaveGateCollection = nullptr;
    m_pParent = nullptr;

    //Delete all gates
    m_lockAllGates.lock();
    for (size_t index = 0; index < m_allGates.size(); index++)
    {
        delete m_allGates[index];
    }
    for(std::vector<Gate*> g : m_gateBackups)
    {
        for (size_t index = 0; index < g.size(); index++)
        {
            delete g[index];
        }
        g.clear();
    }
    m_allGates.clear();
    m_gateBackups.clear();
    m_lockAllGates.unlock();

    delete m_linkNodeA;

    if(m_selectionTool)
        delete m_selectionTool;
}

void GateField::paintEvent(QPaintEvent *paintEvent)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::HighQualityAntialiasing, true);

    //Zooming
    painter.translate(m_centerScreen.x(), m_centerScreen.y());
    painter.scale(m_zoomFactor, m_zoomFactor);

    //If were currently selecting an area
    if(CurrentClickMode == CLICK_SELECTION && m_selectionTool && !m_bDisableGateCollections)
    {
        QPen pen(Qt::blue, 2);
        painter.setPen(pen);
        painter.drawRect(m_selectionTool->geometry());
    }

    //If were in the middle of linking
    if(CurrentClickMode == CLICK_LINK_NODES && m_linkNodeA)
    {
        QPen pen(Qt::blue, 2);
        painter.setPen(pen);
        painter.drawLine(m_previousDragMousePos, m_currentDragPoint);
    }

    m_lockAllGates.lock();    

    //Paint in reverse order, so gate on top of vector get's painted last
    //So if we're dragging, the one we're dragging gets painted ontop of the others
    //Since dragging move the gate to the top of the vector
    for (int index = m_allGates.size() - 1; index > -1; index--)
    {
        m_allGates[size_t(index)]->UpdateGraphics(&painter);
    }

    m_lockAllGates.unlock();
}

//MAKE SURE m_lockAllGates is locked before calling!
//Or re-implement...
void GateField::rl_updateFunction()
{
    for (Gate* g : m_allGates)
    {
        if(g->Enabled)
            g->UpdateOutput();
    }
}

ClickMode GateField::GetCurrentClickMode()
{
    return CurrentClickMode;
}

void GateField::SetZoomLevel(qreal zoom, bool zoomCenter)
{
    m_zoomFactor = zoom;

    //Set m_zoomLocation to geo.center
    if(zoomCenter)
    {
        const QRect geo = geometry();
        m_centerScreen = geo.center();
    }


    //Call to redraw
    update();
}

bool GateField::SaveGateCollection(std::ofstream& saveStream)
{
    GateCollection::SaveData(saveStream, m_selectedGates);

    //should probably return a bool...
    return true;
}

bool GateField::SaveData()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 "/home",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);

    std::ofstream saveFile(dir.toStdString() + "/" + m_name + ".GateField");

    if(saveFile.is_open())
    {
        m_lockAllGates.lock();
        for (size_t index = 0; index < m_allGates.size(); index++)
        {
            m_allGates[index]->SaveData(saveFile);
        }
        m_lockAllGates.unlock();

        //Close
        saveFile.close();
        return true;
    }

    return false;
}

void GateField::SaveData(std::ofstream& saveFile)
{
    m_lockAllGates.lock();
    for (size_t index = 0; index < m_allGates.size(); index++)
    {
        m_allGates[index]->SaveData(saveFile);
    }
    m_lockAllGates.unlock();

    //Close
    saveFile.close();
}

void GateField::DeleteGate(Gate* gateToDelete)
{
    m_lockAllGates.lock();
    for(size_t index = 0; index < m_allGates.size(); index++)
    {
        if (m_allGates[index] == gateToDelete)
        {
            //Find & remove from vector
            Gate* gObject = m_allGates[index];
            //gObject->DetachNodes(); ~ todo think its done by destructor
            m_allGates.erase(m_allGates.begin() + int8_t(index));

            //~Delete & forget
            delete gObject;
            gateToDelete = nullptr;

            rl_updateFunction();

            //Exit early
            break;
        }
    }
    m_lockAllGates.unlock();
}

void GateField::ForgetChild(Gate* gateToDelete)
{
    //dosent need mutex since call comming from child in locked m_allgates

    for(size_t index = 0; index < m_allGates.size(); index++)
    {
        if (m_allGates[index] == gateToDelete)
        {
            //forget
            m_allGates.erase(m_allGates.begin() + int8_t(index));
            gateToDelete = nullptr;

            rl_updateFunction();

            //Exit early
            break;
        }
    }
}

void GateField::Undo()
{
    if(m_backupIndex > -1 && size_t(m_backupIndex) <= m_gateBackups.size())
    {
        std::vector<Gate*> v = m_gateBackups[size_t(m_backupIndex--)];

        m_lockAllGates.lock();
        m_allGates = v;
        m_lockAllGates.unlock();
    }

    //Call to redraw
    update();
}

void GateField::Redo()
{
    if(m_backupIndex > -1 && m_backupIndex < int(m_gateBackups.size()))
    {
        std::vector<Gate*> v = m_gateBackups[size_t(m_backupIndex++)];

        m_lockAllGates.lock();
        m_allGates = v;
        m_lockAllGates.unlock();
    }

    //Call to redraw
    update();
}

//Called if don't want the next gate to be clicked to be set as the selected gate
void GateField::SkipNextGateSelectedCall(bool bStopDragging)
{
    /*
      Need GateCollection's UpdateClicked() to return true when clicked
      (So that GateField::defaultClick() returns true, so that a selection isnt started)

      But..

      Don't want the true param to call UpdateGateSelected(), since clicked gates normally do this
      Reason we don't want it is because it may be a subGate in the GateCollection that actually got clicked
    */
    m_bSkipUpdateGateSelected = true;

    if (bStopDragging)
        StopDragging();
}

void GateField::StopDragging()
{
    m_bMouseDragging = false;
}

void GateField::EditTextLabel(TextLabel *textLabelToEdit)
{
    m_pParent->EditTextLabel(textLabelToEdit);
}

void GateField::StartSaveGateCollection(std::vector<Gate*> selectedGates)
{
    m_selectedGates = selectedGates;
    m_pDlgSaveGateCollection->SetCurrentGateField(this);
    m_pDlgSaveGateCollection->open();
}

std::vector<Gate*>& GateField::GetGates()
{
    m_lockAllGates.lock();
    return m_allGates;
}

void GateField::FinishWithGates()
{
    m_lockAllGates.unlock();
}

void GateField::AddGate(Gate* go, bool newlySpawned, bool cameFromGateColleciton)
{
    if(cameFromGateColleciton)
    {
        go->SetParent(this);
        m_allGates.push_back(go);
    }
    else
    {
        if(newlySpawned)
            go->SetPosition(SPAWN_X + m_screenPosDelta.x, SPAWN_Y + m_screenPosDelta.y);

        go->SetParent(this);

        m_lockAllGates.lock();
        m_allGates.push_back(go);
        m_lockAllGates.unlock();
    }


    //Call to redraw
    update();
}

void GateField::mousePressEvent(QMouseEvent *click)
{
    const QPoint clickPos = QtPointToWorldPoint(click->pos());
    const int clickX = clickPos.x();
    const int clickY = clickPos.y();

    //Update variables
    m_bMouseDragging = true;
    m_previousDragMousePos = QPoint(clickX,clickY);
    m_currentDragPoint = m_previousDragMousePos;

    rl_backupGates();

    //If was in the middle of linking, but then user changed click mode, forget
    //the middle step variable m_linkNodeA
    if(CurrentClickMode != CLICK_LINK_NODES && m_linkNodeA)
    {
        m_linkNodeA = nullptr;
        m_pParent->ResetToPreviousClickMode();
    }

    m_lockAllGates.lock();

    if(click->buttons() & Qt::LeftButton)
    {
        rl_leftMouseClick(clickX, clickY);
    }
    else if(click->buttons() & Qt::RightButton)
    {
        rl_defaultClick(clickX,clickY);
    }
    else if(click->buttons() & Qt::MiddleButton)
    {
        rl_deleteClick(clickX,clickY);
    }

    m_lockAllGates.unlock();

    //Call to redraw
    update();
}

void GateField::rl_leftMouseClick(int clickX, int clickY)
{
    switch (CurrentClickMode)
    {
    case CLICK_DELETE_GATE:
        rl_deleteClick(clickX,clickY);
        break;

    case CLICK_DELETE_LINK_NODES:
        rl_deleteLinkedNodesClick(clickX,clickY);
        break;

    case CLICK_SELECTION:
        rl_selectionClick(clickX,clickY);
        break;

    case CLICK_PAN:
        rl_panClick(clickX, clickY);
        break;

    case CLICK_DEFAULT:
        if(rl_defaultClick(clickX,clickY))
            break;

    case CLICK_DRAG:

        if(rl_dragClick(clickX,clickY))
            break;

    case CLICK_LINK_NODES:

        if(!rl_linkNodesClick(clickX, clickY))
        {
            rl_selectionClick(clickX,clickY);
            if(!m_bDisableGateCollections)
                m_pParent->SetCurrentClickMode(CLICK_SELECTION);
        }

        break;
    }
}

void GateField::mouseMoveEvent(QMouseEvent *click)
{
    const QPoint clickPos = QtPointToWorldPoint(click->pos());

    switch (CurrentClickMode)
    {
        case CLICK_DRAG:

            m_lockAllGates.lock();
            rl_dragClick(clickPos.x(), clickPos.y());
            m_lockAllGates.unlock();

        break;


        case CLICK_PAN:

            m_lockAllGates.lock();
            rl_panClick(clickPos.x(), clickPos.y());
            m_lockAllGates.unlock();
            break;

        case CLICK_SELECTION:

            if (m_bMouseDragging)
            {
                m_lockAllGates.lock();
                rl_selectionClick(clickPos.x(), clickPos.y());
                m_lockAllGates.unlock();
            }

            break;

        case CLICK_LINK_NODES:
            m_currentDragPoint = clickPos;
            break;

        default:
            break;
    }


    //Call to redraw
    update();
}

void GateField::mouseReleaseEvent(QMouseEvent* click)
{
    const QPoint clickPos = QtPointToWorldPoint(click->pos());

    m_bMouseDragging = false;
    m_dragGate = nullptr;

    //If ending a selection
    if( m_selectionTool != nullptr && CurrentClickMode == CLICK_SELECTION && !m_bDisableGateCollections)
    {
        m_selectedGates.clear();
        m_lockAllGates.lock();

        //Get all gates inside surrounding m_selectionTool
        for (Gate* gate : m_allGates)
        {
            if( m_selectionTool->geometry().contains(gate->GetPosition()))
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
            AddGate(collection, false, true);
        }

        //Disactivate selection
        m_selectionTool = nullptr;

        m_pParent->SetCurrentClickMode(CLICK_DRAG);

        m_lockAllGates.unlock();
    }

    //Check if ending a link
    if(CurrentClickMode == CLICK_LINK_NODES)
    {
        //Change cursor as finished linking
        m_pParent->ResetToPreviousClickMode();

        for (Gate* g : m_allGates)
        {
            Node* node = g->GetClickedNode(clickPos.x(), clickPos.y());
            if(node && m_linkNodeA)
            {
                //Check not same node types
                if(node->m_nodeType == m_linkNodeA->m_nodeType)
                {
                    m_pParent->SendUserMessage("Cant link to nodes of same type");
                    return;
                }

                //Check both dont have same parent
                if(node->GetParent() == m_linkNodeA->GetParent())
                    return;

                //link nodes & update parent gates (inside LinkNode())
                bool n1Linked = node->LinkNode(m_linkNodeA);
                bool n2Linked = m_linkNodeA->LinkNode(node);

                if(!n1Linked && !n2Linked)
                {
                    if(n1Linked)
                    {
                        node->DetachNode();
                    }

                    if(n2Linked)
                    {
                        m_linkNodeA->DetachNode();
                    }
                }

                //link successful
                else
                {
                    m_linkNodeA = nullptr;
                }

                node = nullptr;
                return;
            }
            node = nullptr;
        }
    }

    //Call to redraw
    update();
}

//Handles mouse scroll for zooming, offsets gates based on mouse position
void GateField::wheelEvent(QWheelEvent *event)
{
    const QPoint scrollPos = QtPointToWorldPoint(event->pos());
    const qreal direction = event->delta() > 0 ? m_zoomScrollSpeed : -m_zoomScrollSpeed;

    //Only offset gates if zoom factor actually changes
    if (m_pParent->SetZoomFactor(m_zoomFactor + direction, true))
    {
        //Calcualte vector between previous mouse pos and current
        const double offsetX = -scrollPos.x() * direction;
        const double offsetY = -scrollPos.y() * direction;

        //Offset the gates
        //Functions with rl_ require m_lockAllGates to be locked
        m_lockAllGates.lock();
        rl_offsetGates(offsetX, offsetY);
        m_lockAllGates.unlock();
    }
}

bool GateField::rl_linkNodesClick(int clickX, int clickY)
{
    for (Gate* g : m_allGates)
    {
        Node* n = g->GetClickedNode(clickX, clickY);
        if(n)
        {
            m_linkNodeA = n;

            //Change cursor as started linking
            m_pParent->SetCurrentClickMode(CLICK_LINK_NODES);
            n = nullptr;
            return true;
        }
        n = nullptr;
    }
    return false;
}

void GateField::rl_deleteLinkedNodesClick(int clickX, int clickY)
{
    Node* node;
    for (Gate* gate : m_allGates)
    {
        //Check if iterated gate has any clicked nodes
        node = gate->GetClickedNode(clickX,clickY);
        if(node != nullptr)
        {
            node->DetachNode();

            node = nullptr;
            return; //so that we dont acidentally get more than one clicked node
        }
    }
    node = nullptr;
}

bool GateField::rl_defaultClick(int clickX, int clickY)
{
    for (Gate* gate : m_allGates)
    {
        if(gate->UpdateClicked(clickX, clickY))
        {
            if (m_bSkipUpdateGateSelected)
            {
                m_bSkipUpdateGateSelected = false;
            }
            else
            {
                UpdateGateSelected(gate);
            }

            return true;
        }
    }

    return false;
}

void GateField::rl_selectionClick(int clickX, int clickY)
{
    //If start of new selection
    if(m_selectionTool == nullptr)
    {
        m_selectionTool = new QRubberBand(QRubberBand::Rectangle, this);
        m_selectionToolOrigin = QPoint(clickX,clickY);
        m_selectionTool->setGeometry(QRect(m_selectionToolOrigin, QSize()));
    }

    else
    {
        m_selectionTool->setGeometry(
                    QRect(m_selectionToolOrigin, QPoint(clickX,clickY)).normalized()
                    );
    }

}

void GateField::rl_deleteClick(int clickX, int clickY)
{
    for (size_t index = 0; index < m_allGates.size(); index++)
    {     
        if(m_allGates[index]->DeleteClick(clickX,clickY))
        {
            Gate* gObject = m_allGates[index];
            m_allGates.erase(m_allGates.begin() + index);
            delete gObject;

            rl_updateFunction();

            UpdateGateSelected(nullptr);
            //Exit out of for so we dont delete more than one gameobject
            return;
        }
    }
}

bool GateField::rl_dragClick(int clickX, int clickY)
{
    if(!m_bMouseDragging)
        return false;

    //Already know which gate to drag
    if(m_dragGate != nullptr)
    {
        m_dragGate->UpdateDrag(clickX, clickY);
        return true;
    }

    //Look for a gate to drag
    else
    {
        //Loop through all dragable gameobjects
        for (size_t index = 0; index < m_allGates.size(); index++)
        {
            //If found an object to drag,
            if(m_allGates[index]->UpdateDrag(clickX, clickY))
            {
                if (m_bSkipUpdateGateSelected)
                {
                    m_bSkipUpdateGateSelected = false;
                }
                else
                {
                    m_dragGate = m_allGates[index];
                    UpdateGateSelected(m_allGates[index]);

                    //UpdateDrag of gatecollection may delete the gate...
                    //Call this after check for resetting m_bSkipUpdateGateSelected
                    if (m_allGates.size() == 0)
                        return true;

                    //Move the dragged object to the front of the array.
                    //This way next loop the object will be checked first
                    //This means if you drag an object over another, the object being dragged wont switch
                    moveToFront(index, m_allGates);
                }

                //Exit out of for loop so we don't drag multiple objects
                return true;
            }
        }
    }

    return false;
}

void GateField::rl_panClick(int clickX, int clickY)
{
    if(!m_bMouseDragging)
        return;

    //Calcualte vector between previous mouse pos and current
    const float offsetX = c_panSpeedMultiplier * (clickX - m_previousDragMousePos.x());
    const float offsetY = c_panSpeedMultiplier * (clickY - m_previousDragMousePos.y());

    rl_offsetGates(offsetX, offsetY);

    //Save current mouse pos as m_previousDragMousePos for next run
    m_previousDragMousePos = QPoint(clickX, clickY);
}

void GateField::moveToFront(int index, std::vector<Gate *> &vec)
{
    Gate* objectAtIndex = vec[index];

    vec.erase(vec.begin() + index);
    vec.insert(vec.begin(), objectAtIndex);
}

//Function must be called when m_allGates is mutex locked
void GateField::rl_backupGates()
{
    if (m_bDisableGateBackup)
        return;

    //Create backup of all gates
    std::vector<Gate*> backup;
    for(Gate* g : m_allGates)
    {
        backup.push_back(g->Clone());
    }
    m_gateBackups.push_back(backup);

    //If we got too many backups, delete the first row from m_gateBackups (oldest backup)
    if(m_gateBackups.size() > c_maxNumberOfBackups)
    {
        m_gateBackups.erase(m_gateBackups.begin());
    }

    m_backupIndex = m_gateBackups.size() - 1;
}

//Functions with rl_ require m_lockAllGates to be locked
void GateField::rl_offsetGates(double offsetX, double offsetY)
{
    if(offsetX != 0 || offsetY != 0)
    {
        //Add to total delta
        m_screenPosDelta.x += offsetX;
        m_screenPosDelta.y += offsetY;

        //Apply delta
        for (Gate* g : m_allGates)
            g->OffsetPosition(offsetX, offsetY);
    }
}

QPoint GateField::QtPointToWorldPoint(QPoint mousePoint) const
{
    QTransform transform;
    transform.scale(m_zoomFactor, m_zoomFactor);
    return transform.inverted().map(QPoint(mousePoint.x() - m_centerScreen.x(), mousePoint.y() - m_centerScreen.y()));
}

void GateField::UpdateGateSelected(Gate *g)
{
    if(m_pParent)
        m_pParent->GateSelected(g);
}


//      ----            ----
//           TimerThread
//      ----            ----

TimerThread::TimerThread(GateField *parent):
    QThread (),
    m_pGateField(parent),
    m_bStop(false)
{
}

void TimerThread::InitStop()
{
    m_bStop = true;
}

void TimerThread::run()
{
    while(!m_bStop)
    {
        QThread::msleep(1);

        bool reqUpdate = false;

        //GetGates causes mutex lock, so need to call FinishWithGates after
        std::vector<Gate*> gates = m_pGateField->GetGates();
        for (Gate* g : gates)
        {
            if(g->GetType() == GATE_TIMER)
            {
                //If the CheckTimer function returns true, its essentially a request
                //asking for a redraw of the gate, because it's timer state has changed
                if(dynamic_cast<GateTimer*>(g)->CheckTimer())
                    reqUpdate = true;
            }
        }

        //Release mutex
        m_pGateField->FinishWithGates();

        if(reqUpdate)
            m_pGateField->update();
    }
}
