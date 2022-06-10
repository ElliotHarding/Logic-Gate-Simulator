#include "gatefield.h"
#include "dlg_home.h"
#include "dlg_savegatecollection.h"

#include <QApplication>

namespace Settings
{
const QPen LinkingNodeLine(Qt::blue, 2);
const QPen SelectionBorder(Qt::blue, 2);
}

GateField::GateField(qreal zoomFactor, std::string name, DLG_Home* parent, DLG_SaveGateCollection* saveGateCollectionDialog, bool disableGateCollections, bool bDisableGateBackup, bool bDisableZoom) :
    QWidget(parent),
    m_pParent(parent),
    m_name(name),
    m_bDisableGateBackup(bDisableGateBackup),
    m_zoomFactor(zoomFactor),
    m_pDlgSaveGateCollection(saveGateCollectionDialog),
    m_bDisableGateCollections(disableGateCollections),
    m_bDisableZoom(bDisableZoom)
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
}

GateField::~GateField()
{
    Enabled = false;

    //Belongs to parent DLG_Home
    m_pDlgSaveGateCollection = nullptr;
    m_pParent = nullptr;

    //Delete all gates
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

    if(m_linkNodeA)
        delete m_linkNodeA;

    if(m_selectionTool)
        delete m_selectionTool;
}

std::vector<Gate*>& GateField::GetGates()
{
    return m_allGates;
}

void GateField::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::HighQualityAntialiasing, true);

    //Zooming
    painter.translate(geometry().center().x(), geometry().center().y());
    painter.scale(m_zoomFactor, m_zoomFactor);

    //If were currently selecting an area
    if(CurrentClickMode == CLICK_SELECTION && m_selectionTool && !m_bDisableGateCollections)
    {
        painter.setPen(Settings::SelectionBorder);
        painter.drawRect(m_selectionTool->geometry());
    }

    //If were in the middle of linking
    if(m_linkNodeA)
    {
        painter.setPen(Settings::LinkingNodeLine);
        painter.drawLine(m_linkNodeA->position(), m_currentMousePos);
    }

    //Paint in reverse order, so gate on top of vector get's painted last
    //So if we're dragging, the one we're dragging gets painted ontop of the others
    //Since dragging move the gate to the top of the vector
    for (int index = m_allGates.size() - 1; index > -1; index--)
    {
        m_allGates[size_t(index)]->draw(painter);
    }
}

void GateField::rl_updateFunction()
{
    for (Gate* g : m_allGates)
    {
        if(g->enabled())
            g->UpdateOutput();
    }
}

ClickMode GateField::GetCurrentClickMode()
{
    return CurrentClickMode;
}

void GateField::SetZoomLevel(qreal zoom)
{
    if(m_bDisableZoom)
        return;

    m_zoomFactor = zoom;

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
        for (size_t index = 0; index < m_allGates.size(); index++)
        {
            m_allGates[index]->SaveData(saveFile);
        }

        //Close
        saveFile.close();
        return true;
    }

    return false;
}

void GateField::SaveData(std::ofstream& saveFile)
{
    for (size_t index = 0; index < m_allGates.size(); index++)
    {
        m_allGates[index]->SaveData(saveFile);
    }

    //Close
    saveFile.close();
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

            rl_updateFunction();
            return;
        }
    }
}

//Todo : do the history class like with paint program

void GateField::Undo()
{
    if(m_backupIndex > -1 && size_t(m_backupIndex) <= m_gateBackups.size())
    {
        std::vector<Gate*> v = m_gateBackups[size_t(m_backupIndex--)];
        m_allGates = v;
    }

    //Call to redraw
    update();
}

void GateField::Redo()
{
    if(m_backupIndex > -1 && m_backupIndex < int(m_gateBackups.size()))
    {
        std::vector<Gate*> v = m_gateBackups[size_t(m_backupIndex++)];
        m_allGates = v;
    }

    //Call to redraw
    update();
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

void GateField::AddGate(Gate* go, bool newlySpawned)
{
    go->SetParent(this);

    if(newlySpawned)
        go->setPosition(SPAWN_X + m_screenPosDelta.x, SPAWN_Y + m_screenPosDelta.y);

    m_allGates.push_back(go);

    //Call to redraw
    update();
}

void GateField::mousePressEvent(QMouseEvent *click)
{
    const QPoint clickPos = QtPointToWorldPoint(click->pos());
    const int clickX = clickPos.x();
    const int clickY = clickPos.y();

    //Update variables
    m_bMouseDown = true;
    m_previousDragMousePos = clickPos; //Todo : probably dont need these previous and current anymore.

    rl_backupGates();

    //Todo : maybe move this to when click mode changes...
    //If was in the middle of linking, but then user changed click mode, forget
    //the middle step variable m_linkNodeA
    if(CurrentClickMode != CLICK_LINK_NODES && m_linkNodeA)
    {
        m_linkNodeA = nullptr;
        m_pParent->ResetToPreviousClickMode();
    }

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
        checkStartDrag(clickX, clickY);
        break;

    case CLICK_LINK_NODES:
        checkStartLink(clickX, clickY);
        break;
    }
}

void GateField::mouseMoveEvent(QMouseEvent *click)
{
    const QPoint clickPos = QtPointToWorldPoint(click->pos());

    switch (CurrentClickMode)
    {
        case CLICK_DRAG:
            if(m_pDraggingGate)
            {
                m_pDraggingGate->setPosition(clickPos.x(), clickPos.y());
            }
            break;

        case CLICK_PAN:
            rl_panClick(clickPos.x(), clickPos.y());
            break;

        case CLICK_SELECTION:
            if (m_bMouseDown)
            {
                rl_selectionClick(clickPos.x(), clickPos.y());
            }
            break;

        case CLICK_LINK_NODES:
            if(m_linkNodeA)
            {
                m_currentMousePos = clickPos;
            }
            break;

        default:
            break;
    }


    //Call to redraw
    update();
}

void GateField::mouseReleaseEvent(QMouseEvent* click)
{
    m_bMouseDown = false;

    //If ending a dragging session
    if(m_pDraggingGate)
    {
        m_pDraggingGate = nullptr;
        return;
    }

    const QPoint clickPos = QtPointToWorldPoint(click->pos());

    //Check if ending a link attempt
    if(m_linkNodeA)
    {
        checkEndLink(clickPos.x(), clickPos.y());
        m_linkNodeA = nullptr;
        update();
    }

    //If ending a selection
    if(m_selectionTool != nullptr && CurrentClickMode == CLICK_SELECTION && !m_bDisableGateCollections)
    {
        m_selectedGates.clear();

        //Get all gates inside surrounding m_selectionTool
        for (Gate* gate : m_allGates)
        {
            if(m_selectionTool->geometry().contains(gate->position()))
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
        }

        //Disactivate selection
        m_selectionTool = nullptr;

        m_pParent->SetCurrentClickMode(CLICK_DRAG);

        //Call to redraw
        update();
    }
}

//Handles mouse scroll for zooming, offsets gates based on mouse position
void GateField::wheelEvent(QWheelEvent *event)
{
    if(m_bDisableZoom)
        return;

    const qreal direction = event->delta() > 0 ? m_zoomScrollSpeed : -m_zoomScrollSpeed;

    //Todo : seems stupid to set zoom factor for all gatefeilds
    //Only offset gates if zoom factor actually changes
    if (m_pParent->SetZoomFactor(m_zoomFactor + direction, true))
    {
        const QPoint scrollPos = QtPointToWorldPoint(event->pos());

        //Calcualte vector between previous mouse pos and current
        const double offsetX = -scrollPos.x() * direction;
        const double offsetY = -scrollPos.y() * direction;

        //Offset the gates
        rl_offsetGates(offsetX, offsetY);
    }
}

void GateField::checkStartLink(const int& clickX, const int& clickY)
{
    for (Gate* g : m_allGates)
    {
        GameObject* pPossibleClickedNode = g->checkClicked(clickX, clickY);
        if(pPossibleClickedNode != nullptr && dynamic_cast<Node*>(pPossibleClickedNode))
        {
            m_linkNodeA = dynamic_cast<Node*>(pPossibleClickedNode);

            //Change cursor as started linking
            m_pParent->SetCurrentClickMode(CLICK_LINK_NODES);
            return;
        }
    }
}

void GateField::checkEndLink(const int &clickX, const int &clickY)
{
    for (Gate* g : m_allGates)
    {
        GameObject* pPossibleClickedNode = g->checkClicked(clickX, clickY);
        if(pPossibleClickedNode != nullptr && dynamic_cast<Node*>(pPossibleClickedNode))
        {
            Node* node = dynamic_cast<Node*>(pPossibleClickedNode);

            //Check not same node types
            if(node->type() == m_linkNodeA->type())
            {
                m_pParent->SendUserMessage("Cant link to nodes of same type");
                return;
            }

            //Check both dont have same parent
            if(node->GetParent() == m_linkNodeA->GetParent())
            {
                return;
            }

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
        }
    }
}

void GateField::rl_deleteLinkedNodesClick(int clickX, int clickY)
{
    Node* node;
    for (Gate* gate : m_allGates)
    {
        //Check if iterated gate has any clicked nodes
        GameObject* pPossibleClickedNode = gate->checkClicked(clickX, clickY);

        if(pPossibleClickedNode != nullptr && dynamic_cast<Node*>(pPossibleClickedNode))
        {
            node = dynamic_cast<Node*>(pPossibleClickedNode);

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
        if(gate->checkClicked(clickX, clickY))
        {
            UpdateGateSelected(gate);
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
        if(m_allGates[index]->checkClicked(clickX,clickY))
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

void GateField::checkStartDrag(const int& clickX, const int& clickY)
{
    //Look for a gate to drag

    //Loop through all dragable gameobjects
    for (size_t index = 0; index < m_allGates.size(); index++)
    {
        GameObject* pPossibleClickedObject = m_allGates[index]->checkClicked(clickX, clickY);
        if(pPossibleClickedObject != nullptr && dynamic_cast<Gate*>(pPossibleClickedObject))
        {
            m_pDraggingGate = dynamic_cast<Gate*>(pPossibleClickedObject);
            UpdateGateSelected(m_allGates[index]);

            //Move the dragged object to the front of the array.
            //This way next loop the object will be checked first
            //This means if you drag an object over another, the object being dragged wont switch
            moveToFront(index, m_allGates);

            return;
        }
    }
}

void GateField::rl_panClick(int clickX, int clickY)
{
    if(!m_bMouseDown)
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
            g->offsetPosition(offsetX, offsetY);
    }
}

QPoint GateField::QtPointToWorldPoint(QPoint mousePoint) const
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
