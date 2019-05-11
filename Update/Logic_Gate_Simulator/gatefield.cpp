#include "gatefield.h"
#include <QApplication>
#include "DLG_SaveGateCollection.h"
#include "dlg_home.h"

GateField::GateField(qreal zoomFactor, std::string name, DLG_Home* parent) :
    QWidget(parent),
    m_pParent(parent),
    m_name(name),
    m_zoomFactor(zoomFactor)
{
    setAcceptDrops(true);
    setMouseTracking(true);

    m_panOffset.x = 0;
    m_panOffset.y = 0;

    QApplication::setOverrideCursor(Qt::CursorShape::SizeAllCursor);
    m_currentClickMode = CLICK_DRAG;
}

GateField::~GateField()
{
    Enabled = false;

    //todo
    //delete m_saveGateCollection;

    //Delete all gates
    m_lockAllGates.lock();
    for (size_t index = 0; index < m_allGates.size(); index++)
    {
        delete m_allGates[index];
    }
    m_lockAllGates.unlock();

    delete m_linkNodeA;
}

void GateField::paintEvent(QPaintEvent *paintEvent)
{
    QPainter painter(this);

    //If were currently selecting an area
    if(m_currentClickMode == CLICK_SELECTION && m_selectionTool)
    {
        QPen pen(Qt::blue, 2);
        painter.setPen(pen);
        painter.drawRect(m_selectionTool->geometry());
    }

    //painter.scale(m_zoomFactor,m_zoomFactor);

    //Panning
    QTransform panTransform;
    panTransform.translate(m_panOffset.x,m_panOffset.y);
    painter.setWorldTransform(panTransform);

    m_lockAllGates.lock();
    for (Gate* gate : m_allGates)
    {
        gate->UpdateGraphics(&painter);
    }
    m_lockAllGates.unlock();

    //Call to redraw
    update();
}

void GateField::updateFunction()
{
    if(m_lockAllGates.try_lock())
    {
        for (size_t index = 0; index < m_allGates.size(); index++)
        {
            //m_lockAllGates.lock();
            m_allGates[index]->UpdateOutput();
            //m_lockAllGates.unlock();
        }
        m_lockAllGates.unlock();
    }
}

GateCollection* GateField::GenerateGateCollection()
{
    return new GateCollection(m_selectedGates);
}

bool GateField::SaveData()
{
    std::ofstream saveFile(m_name + ".GateField");

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
    for(int index = 0; index < m_allGates.size(); index++)
    {
        if (m_allGates[index] == gateToDelete)
        {
            //Find & remove from vector
            Gate* gObject = m_allGates[index];
            m_allGates.erase(m_allGates.begin() + index);

            //Delete & forget
            delete gObject;
            gateToDelete = nullptr;

            //Exit early
            break;
        }
    }
    m_lockAllGates.unlock();
}

void GateField::addGameObject(Gate* go, bool newlySpawned)
{
    if(newlySpawned)
        go->SetPosition(SPAWN_X,SPAWN_Y);

    go->ParentField = this;

    m_lockAllGates.lock();
    m_allGates.push_back(go);
    m_lockAllGates.unlock();
}

void GateField::mousePressEvent(QMouseEvent *click)
{
    const int clickX = click->x();
    const int clickY = click->y();

    //If was in the middle of linking, but then user changed click mode, forget
    //the middle step variable m_linkNodeA
    if(m_currentClickMode != CLICK_LINK_NODES) m_linkNodeA = nullptr;

    m_lockAllGates.lock();

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

    case CLICK_DRAG:
        dragClick(clickX,clickY);//rest of dragging handeled in mouseMoveEvent
        break;

    case CLICK_SELECTION:
        selectionClick(clickX,clickY);
        break;
    }

    m_lockAllGates.unlock();
}

void GateField::mouseMoveEvent(QMouseEvent *click)
{
    if(m_bMouseDragging && m_currentClickMode == CLICK_DRAG)
    {
        m_lockAllGates.lock();
        dragClick(click->x(),click->y());
        m_lockAllGates.unlock();
    }

    if( m_selectionTool != nullptr && m_currentClickMode == CLICK_SELECTION)
    {
        m_lockAllGates.lock();
        selectionClick(click->x(),click->y());
        m_lockAllGates.unlock();
    }
}

void GateField::mouseReleaseEvent(QMouseEvent *click)
{
    m_bMouseDragging = false;

    //If ending a selection
    if( m_selectionTool != nullptr && m_currentClickMode == CLICK_SELECTION)
    {
        //Go through all gates and add gates inside selection to selectedGates vector
        m_selectedGates.clear();
        m_lockAllGates.lock();
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
            m_saveGateCollection = new DLG_SaveGateCollection(this, this);
            m_saveGateCollection->open();

            //GenerateGateCollection() gets called by the saveGateCollectionDialog
        }
        m_selectionTool = nullptr;
    }
}

void GateField::linkNodesClick(int clickX, int clickY)
{
    Node* node;
    for (size_t index = 0; index < m_allGates.size(); index++)
    {
        //Check if iterated gate has any clicked nodes
        node = (m_allGates[index])->GetClickedNode(clickX,clickY);
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

                m_linkNodeA->LinkNode(node);
                node->LinkNode(m_linkNodeA);
                m_linkNodeA = nullptr;

                //Change cursor as finished linking
                QApplication::setOverrideCursor(Qt::CursorShape::DragLinkCursor);
            }

            //delete node;
            return; //so that we dont acidentally get more than one clicked node
        }
    }
    //delete node;
}

void GateField::deleteLinkedNodesClick(int clickX, int clickY)
{
    Node* node;
    for (size_t index = 0; index < m_allGates.size(); index++)
    {
        //Check if iterated gate has any clicked nodes
        node = (m_allGates[index])->GetClickedNode(clickX,clickY);
        if(node != nullptr)
        {
            if(node->GetLinkedNode())
            {
                Node* nodeLinkedTo = node->GetLinkedNode();
                nodeLinkedTo->DetachNode();
                node->DetachNode();
                delete nodeLinkedTo;
            }

            //delete node;
            return; //so that we dont acidentally get more than one clicked node
        }
    }
    //delete node;
}

void GateField::defaultClick(int clickX, int clickY)
{
    for (Gate* gate : m_allGates)
    {
        if(gate->UpdateClicked(clickX, clickY))
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
        if(m_allGates[index]->UpdateClicked(clickX,clickY))
        {
            Gate* gObject = m_allGates[index];
            m_allGates.erase(m_allGates.begin() + index);
            delete gObject;

            updateGateSelected(nullptr);
            //Exit out of for so we dont delete more than one gameobject
            return;
        }
    }
}

void GateField::dragClick(int clickX, int clickY)
{
    //If start of drag sequence,
    if(!m_bMouseDragging)
        m_previousDragMousePos = QPoint(clickX,clickY);

    m_bMouseDragging = true;

    //Loop through all dragable gameobjects
    for (size_t index = 0; index < m_allGates.size(); index++)
    {
        //If found an object to drag,
        if(m_allGates[index]->UpdateDrag(clickX, clickY))
        {
            //Move the dragged object to the front of the array.
            //This way next loop the object will be checked first
            //This means if you drag an object over another, the object being dragged wont switch
            moveToFront(index, m_allGates);

            updateGateSelected(m_allGates[index]);

            //Exit out of for loop so we don't drag multiple objects
            return;
        }
    }

    //Panning:
    //Calcualte vector between previous mouse pos and current
    m_panOffset.x += clickX - m_previousDragMousePos.x();
    m_panOffset.y += clickY - m_previousDragMousePos.y();

    //Save current mouse pos as m_previousDragMousePos for next run
    m_previousDragMousePos = QPoint(clickX, clickY);
}

void GateField::moveToFront(int index, std::vector<Gate *> &vec)
{
    Gate* objectAtIndex = vec[index];

    vec.erase(vec.begin() + index);
    vec.insert(vec.begin(), objectAtIndex);
}

void GateField::updateGateSelected(Gate *g)
{
    if(m_pParent)
        m_pParent->GateSelected(g);
}
