#include "gatefield.h"
#include <QApplication>
#include "DLG_SaveGateCollection.h"

GateField::GateField(qreal zoomFactor, QWidget *parent) :
    QWidget(parent),
    m_zoomFactor(zoomFactor)
{
    setAcceptDrops(true);
    setMouseTracking(true);
}

GateField::~GateField()
{
    Enabled = false;

    delete m_saveGateCollection;

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
    m_lockAllGates.lock();
    for (size_t index = 0; index < m_allGates.size(); index++)
    {
        //m_lockAllGates.lock();
        m_allGates[index]->UpdateOutput();
        //m_lockAllGates.unlock();
    }
    m_lockAllGates.unlock();
}

GateCollection* GateField::GenerateGateCollection()
{
    const int width = m_selectionTool->geometry().width();
    const int height = m_selectionTool->geometry().height();
    m_selectionTool = nullptr;

    return new GateCollection(m_selectedGates, width, height);
}

void GateField::addGameObject(Gate* go, bool newlySpawned)
{
    if(newlySpawned)
        //Set spawn position
        go->SetPosition(SPAWN_X,SPAWN_Y);

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
        anyInputGatesToggled(click->x(),click->y());
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
            //this also resets m_selectionTool;
        }
        else
        {
            m_selectionTool = nullptr;
        }
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


void GateField::anyInputGatesToggled(int clickX, int clickY)
{
    //Loops through m_allGates, if GateInputBox found update its click state
    //Reason done seperatly to other gates :
    // - The required frequency of GateInputBox->UpdateClicked() is higher than all other gates
    //   This is because no other gates take user click input so far
    for (Gate* gate : m_allGates)
    {
        if(dynamic_cast<GateInputBox*>(gate))
        {
            dynamic_cast<GateInputBox*>(gate)->UpdateClicked(clickX, clickY);
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

            //Move the dragged object to the front of the array.
            //This way next loop the object will be checked first
            //This means if you drag an object over another, the object being dragged wont switch
            moveToFront(index, m_allGates);

            //Exit out of for loop so we don't drag multiple objects
            return;
        }
    }
}

void GateField::moveToFront(int index, std::vector<Gate *> &vec)
{
    Gate* objectAtIndex = vec[index];

    vec.erase(vec.begin() + index);
    vec.insert(vec.begin(), objectAtIndex);
}
