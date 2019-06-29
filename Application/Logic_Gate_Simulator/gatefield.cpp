#include "gatefield.h"
#include "dlg_home.h"
#include "dlg_savegatecollection.h"

#include <QApplication>

GateField::GateField(qreal zoomFactor, std::string name, DLG_Home* parent, DLG_SaveGateCollection* saveGateCollectionDialog) :
    QWidget(parent),
    m_pParent(parent),
    m_name(name),
    m_zoomFactor(zoomFactor),
    m_pDlgSaveGateCollection(saveGateCollectionDialog)
{
    setAcceptDrops(true);
    setMouseTracking(true);

    m_screenPosDelta.x = 0;
    m_screenPosDelta.y = 0;

    QApplication::setOverrideCursor(Qt::CursorShape::SizeAllCursor);
    m_currentClickMode = CLICK_DRAG;

    saveGateCollectionDialog->SetCurrentGateField(this);

    m_allGates.reserve(20);
    m_gateBackups.reserve(20);
    for(std::vector<Gate*> g : m_gateBackups)
    {
        g.reserve(20);
    }
}

GateField::~GateField()
{
    Enabled = false;

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
    }
    m_lockAllGates.unlock();

    delete m_linkNodeA;

    if(m_selectionTool)
        delete m_selectionTool;
}

void GateField::paintEvent(QPaintEvent *paintEvent)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    //Zooming
    painter.scale(m_zoomFactor, m_zoomFactor);

    //If were currently selecting an area
    if(m_currentClickMode == CLICK_SELECTION && m_selectionTool)
    {
        QPen pen(Qt::blue, 2);
        painter.drawRect(m_selectionTool->geometry());
    }

    m_lockAllGates.lock();
    for (Gate* gate : m_allGates)
    {
        gate->UpdateGraphics(&painter);
    }
    m_lockAllGates.unlock();

    //Call to redraw
    update();
}

//MAKE SURE m_lockAllGates is locked before calling!
//Or re-implement...
void GateField::updateFunction()
{
    for (Gate* g : m_allGates)
    {
        if(g->Enabled)
            g->UpdateOutput();
    }
}

void GateField::setCurrentClickMode(ClickMode clickMode)
{
    m_currentClickMode = clickMode;
}

void GateField::setZoomLevel(qreal zoom)
{
     m_zoomFactor = zoom;
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

            updateFunction();

            //Exit early
            break;
        }
    }
    m_lockAllGates.unlock();
}

void GateField::Undo()
{
    if(m_backupIndex > -1 && size_t(m_backupIndex) < m_gateBackups.size())
    {
        std::vector<Gate*> v = m_gateBackups[size_t(m_backupIndex--)];

        m_lockAllGates.lock();
        m_allGates = v;
        m_lockAllGates.unlock();
    }
}

void GateField::Redo()
{
    if(size_t(m_backupIndex) < m_gateBackups.size())
    {
        std::vector<Gate*> v = m_gateBackups[size_t(m_backupIndex++)];

        m_lockAllGates.lock();
        m_allGates = v;
        m_lockAllGates.unlock();
    }
}

void GateField::addGameObject(Gate* go, bool newlySpawned)
{
    if(newlySpawned)
        go->SetPosition(SPAWN_X + m_screenPosDelta.x, SPAWN_Y + m_screenPosDelta.y);

    go->ParentField = this;

    m_lockAllGates.lock();
    m_allGates.push_back(go);
    m_lockAllGates.unlock();
}

void GateField::mousePressEvent(QMouseEvent *click)
{
    const QPoint clickPos = GetClickFromMouseEvent(click);
    const int clickX = clickPos.x();
    const int clickY = clickPos.y();

    BackupGates();

    //If was in the middle of linking, but then user changed click mode, forget
    //the middle step variable m_linkNodeA
    if(m_currentClickMode != CLICK_LINK_NODES)
        m_linkNodeA = nullptr;

    m_lockAllGates.lock();

    if(click->buttons() & Qt::LeftButton)
    {
        leftMouseClick(clickX, clickY);
    }
    else if(click->buttons() & Qt::RightButton)
    {
        rightMouseClick(clickX, clickY);
    }
    else if(click->buttons() & Qt::MiddleButton)
    {
        middleMouseClick(clickX, clickY);
    }

    m_lockAllGates.unlock();
}

void GateField::leftMouseClick(int clickX, int clickY)
{
    switch (m_currentClickMode)
    {
    case CLICK_LINK_NODES:
        linkNodesClick(clickX,clickY);
        break;

    case CLICK_DELETE_GATE:
        deleteClick(clickX,clickY);
        break;

    case CLICK_DELETE_LINK_NODES:
        deleteLinkedNodesClick(clickX,clickY);
        break;

    case CLICK_DEFAULT:
        defaultClick(clickX,clickY);
        break;

    case CLICK_SELECTION:
        selectionClick(clickX,clickY);
        break;

    case CLICK_DRAG:
        dragClick(clickX,clickY);//rest of dragging handeled in mouseMoveEvent
        break;

    case CLICK_PAN:
        panClick(clickX, clickY);//rest of dragging handeled in mouseMoveEvent
        break;
    }
}

void GateField::rightMouseClick(int clickX, int clickY)
{
    defaultClick(clickX,clickY);
}

void GateField::middleMouseClick(int clickX, int clickY)
{
    deleteClick(clickX,clickY);
}

void GateField::mouseMoveEvent(QMouseEvent *click)
{
    const QPoint clickPos = GetClickFromMouseEvent(click);

    if(m_bMouseDragging && m_currentClickMode == CLICK_DRAG && m_dragGate != nullptr)
    {
        m_lockAllGates.lock();
        if(m_dragGate->GetType() != GATE_COLLECTION)
        {
            m_dragGate->SetPosition(clickPos.x(), clickPos.y());
        }
        else
        {
            dragClick(clickPos.x(), clickPos.y());
        }
        m_lockAllGates.unlock();
    }

    if(m_bMouseDragging && m_currentClickMode == CLICK_PAN)
    {
        m_lockAllGates.lock();
        panClick(clickPos.x(), clickPos.y());
        m_lockAllGates.unlock();
    }

    if( m_selectionTool != nullptr && m_currentClickMode == CLICK_SELECTION)
    {
        m_lockAllGates.lock();
        selectionClick(clickPos.x(), clickPos.y());
        m_lockAllGates.unlock();
    }
}

void GateField::mouseReleaseEvent(QMouseEvent* click)
{
    m_bMouseDragging = false;
    m_dragGate = nullptr;

    //If ending a selection
    if( m_selectionTool != nullptr && m_currentClickMode == CLICK_SELECTION)
    {
        //Go through all gates and add gates inside selection to selectedGates vector
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

        m_lockAllGates.unlock();

        //Selection contains some gates, then we can save them as a gate collection
        if(m_selectedGates.size() > 0)
        {
            m_pDlgSaveGateCollection->SetCurrentGateField(this);
            m_pDlgSaveGateCollection->open();
            //GenerateGateCollection() gets called by the saveGateCollectionDialog
        }
        m_selectionTool = nullptr;
    }
}

void GateField::linkNodesClick(int clickX, int clickY)
{
    Node* node;
    for (Gate* gate : m_allGates)
    {
        //Check if iterated gate has any clicked nodes
        node = gate->GetClickedNode(clickX,clickY);
        if(node != nullptr)
        {
            //If m_linkNodeA is a null pointer then its the first node to be clicked
            if(m_linkNodeA == nullptr)
            {
                m_linkNodeA = node;

                //Change cursor as moving to next linking step and need to notify user
                QApplication::setOverrideCursor(Qt::CursorShape::DragCopyCursor);
            }

            //Otherwise click on second node, so link first & second and then set m_linkNodeA to null
            else
            {
                //Not gonna link to itself!
                if (&node == &m_linkNodeA)
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

                //Change cursor as finished linking
                QApplication::setOverrideCursor(Qt::CursorShape::DragLinkCursor);
            }

            node = nullptr;
            return; //so that we dont acidentally get more than one clicked node
        }
    }
    node = nullptr;
}

void GateField::deleteLinkedNodesClick(int clickX, int clickY)
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

void GateField::defaultClick(int clickX, int clickY)
{
    for (Gate* gate : m_allGates)
    {
        if(gate->GetType() == GATE_COLLECTION)
        {
            Gate* subGate = dynamic_cast<GateCollection*>(gate)->UpdateClicked_Override(clickX,clickY);
            if(subGate != nullptr)
            {
                updateGateSelected(subGate);
            }
        }
        else if(gate->UpdateClicked(clickX, clickY))
        {
            updateGateSelected(gate);
        }
    }
}

void GateField::selectionClick(int clickX, int clickY)
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

void GateField::deleteClick(int clickX, int clickY)
{
    for (size_t index = 0; index < m_allGates.size(); index++)
    {     
        if(m_allGates[index]->DeleteClick(clickX,clickY))
        {
            Gate* gObject = m_allGates[index];
            m_allGates.erase(m_allGates.begin() + index);
            //gObject->DetachNodes(); ~ Think its done by the destructor
            delete gObject;

            updateFunction();

            updateGateSelected(nullptr);
            //Exit out of for so we dont delete more than one gameobject
            return;
        }
    }
}

void GateField::dragClick(int clickX, int clickY)
{
    //Loop through all dragable gameobjects
    for (size_t index = 0; index < m_allGates.size(); index++)
    {
        //If found an object to drag,
        if(m_allGates[index]->UpdateDrag(clickX, clickY))
        {
            m_bMouseDragging = true;
            m_dragGate = m_allGates[index];

            //Move the dragged object to the front of the array.
            //This way next loop the object will be checked first
            //This means if you drag an object over another, the object being dragged wont switch
            moveToFront(index, m_allGates);

            if(m_allGates[index]->GetType() == GATE_COLLECTION)
            {
                Gate* g = dynamic_cast<GateCollection*>(m_allGates[index])->UpdateClicked_Override(clickX, clickY);
                if(g != nullptr)
                    updateGateSelected(g);
            }
            else
            {
                updateGateSelected(m_allGates[index]);
            }

            //Exit out of for loop so we don't drag multiple objects
            return;
        }
    }
}

void GateField::panClick(int clickX, int clickY)
{
    //If start of drag sequence,
    if(!m_bMouseDragging)
        m_previousDragMousePos = QPoint(clickX,clickY);
    m_bMouseDragging = true;

    //Calcualte vector between previous mouse pos and current
    const float offsetX = c_panSpeedMultiplier * (clickX - m_previousDragMousePos.x());
    const float offsetY = c_panSpeedMultiplier * (clickY - m_previousDragMousePos.y());

    //Add to total delta
    m_screenPosDelta.x += offsetX;
    m_screenPosDelta.y += offsetY;

    //Apply delta
    if(offsetX != 0 || offsetY != 0)
        for (Gate* g : m_allGates)
        {
            g->OffsetPosition(offsetX, offsetY);
        }

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
void GateField::BackupGates()
{

    //So if were in the middle of an undo (ie. backup index has gone back a bit)
    //Pop back the redos
    if(m_backupIndex != m_gateBackups.size())
    {
        const int diff = m_gateBackups.size() - m_backupIndex;
        for (int index = 0; index < diff; index++)
        {
            m_gateBackups.pop_back();
        }
    }

    //Create backup of all gates
    std::vector<Gate*> backup;
    for(Gate* g : m_allGates)
    {
        backup.push_back(g->Clone());
    }

    m_gateBackups.push_back(backup);
    m_backupIndex++;

    if(m_gateBackups.size() > c_maxNumberOfBackups)
    {
        m_gateBackups.erase(m_gateBackups.begin());
    }
}

QPoint GateField::GetClickFromMouseEvent(QMouseEvent *mouseEvent) const
{
    QTransform transform;
    transform.scale(m_zoomFactor, m_zoomFactor);
    return transform.inverted().map(QPoint(mouseEvent->x(), mouseEvent->y()));
}

void GateField::updateGateSelected(Gate *g)
{
    if(m_pParent)
        m_pParent->GateSelected(g);
}
