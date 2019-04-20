#include "gatefield.h"
#include <QApplication>

GateField::GateField(QWidget *parent) : QWidget(parent)
{
    setAcceptDrops(true);
    setMouseTracking(true);
}

GateField::~GateField()
{
    //Delete all gates
    for (size_t index = 0; index < m_allGates.size(); index++)
    {
        delete m_allGates[index];
    }

    delete m_linkNodeA;
}

void GateField::paintEvent(QPaintEvent *paintEvent)
{
    QPainter painter(this);

    //Draw all gates & all lines between nodes (handeled via nodes)
    for (size_t index = 0; index < m_allGates.size(); index++)
    {
        m_allGates[index]->UpdateGraphics(&painter);
    }

    updateFunction();

    //Call to update widget (so another draw call)
    //update();
    //qApp->processEvents();
}

void GateField::updateFunction()
{
    for (size_t index = 0; index < m_allGates.size(); index++)
    {
        m_allGates[index]->UpdateOutput();
    }
}

void GateField::addGameObject(Gate* go)
{
    //Set spawn position
    go->setPosition(SPAWN_X,SPAWN_Y);

    m_allGates.push_back(go);
}

void GateField::mousePressEvent(QMouseEvent *click)
{
    const int clickX = click->x();
    const int clickY = click->y();

    //If was in the middle of linking, but then user changed click mode, forget
    //the middle step variable m_linkNodeA
    if(m_currentClickMode != CLICK_LINK_NODES) m_linkNodeA = nullptr;

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

    //rest of dragging handeled in mouseMoveEvent
    case CLICK_DRAG:
        dragClick(clickX,clickY);
        break;
    }

    QWidget::mousePressEvent(click);
}

void GateField::mouseMoveEvent(QMouseEvent *click)
{
    if(m_bMouseDragging)
    {
        dragClick(click->x(),click->y());
    }
}

void GateField::mouseReleaseEvent(QMouseEvent *click)
{
    m_bMouseDragging = false;
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

            delete node;
            return; //so that we dont acidentally get more than one clicked node
        }
    }
    delete node;
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

            delete node;
            return; //so that we dont acidentally get more than one clicked node
        }
    }
    delete node;
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
        //If found an object to drag, exit out of for loop
        //so we don't drag multiple objects
        if(m_allGates[index]->UpdateDrag(clickX, clickY))
        {
            m_bMouseDragging = true;
            return;
        }
    }
}
