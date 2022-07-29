#include "gatecollection.h"
#include "allgates.h"
#include "gatefield.h"

#include "truthtable.h"

#include <QDebug>
#include <cmath>

namespace Settings
{
///Drawing
const QColor DragModeFillColor = QColor(40,40,40,20);
const QColor DragIndividualBoardeColor = Qt::black;
const uint DragIndividualBoardeSize = 5;

///UI Buttons
const QImage ImgDeleteAllButton = QImage(std::string(":/Resources/Button Icons/gate-collection-delete-all.png").c_str());
const QImage ImgSaveButton = QImage(std::string(":/Resources/Button Icons/gate-collection-save.png").c_str());
const QImage ImgDeleteButton = QImage(std::string(":/Resources/Button Icons/gate-collection-delete.png").c_str());
const QImage ImgDragButton = QImage(std::string(":/Resources/Button Icons/gate-collection-move-gates.png").c_str());
const QImage ImgTruthTableButton = QImage(std::string(":/Resources/Button Icons/gate-collection-truth-table.png").c_str());
const QImage ImgBooleanExpressions = QImage(std::string(":/Resources/Button Icons/gate-collection-boolean-expressions.png").c_str());
//const QImage ImgOptimizeButton = QImage(std::string(":/Resources/Button Icons/gate-collection-optimize.png").c_str());
//const QImage ImgNandOptimizeButton = QImage(std::string(":/Resources/Button Icons/gate-collection-nand.png").c_str());
const uint ButtonSize = 40;

//Number of pixels from border before gates are seen
const int BorderBoxMargin = 40;
}

GateCollection::GateCollection(std::vector<Gate*> gates) :
    Gate::Gate(GATE_COLLECTION, 0, 0, 0, 0)
{
    m_gates = gates;
    for(Gate* pGate : m_gates)
    {
        pGate->SetParentGateCollection(this);
    }

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

bool GateCollection::generateTruthTable(TruthTable& table)
{
    std::vector<NodeIds> linkInfo;
    collectLinkInfo(linkInfo);

    for(NodeIds nodeIds : linkInfo)
    {
        for(int linkId : nodeIds.linkedIds)
        {
            Node* pNode;
            if(!FindNodeWithId(linkId, pNode))
            {
                m_pParentField->SendUserMessage("Failed. Circuit includes external connections!");
                return false;
            }
        }
    }

    std::vector<GateToggle*> inputGates;
    std::vector<Gate*> mainGates;
    std::vector<GateReciever*> resultGates;
    for (Gate* g : m_gates)
    {
        if(g->GetType() == GateType::GATE_EMMITTER)
        {
            if(dynamic_cast<GateToggle*>(g))
            {
                inputGates.push_back(dynamic_cast<GateToggle*>(g));
            }
            else
            {
                qDebug() << "GateCollection::generateTruthTable - Failed to cast GateToggle";
                m_pParentField->SendUserMessage("Failed. Internal error.");
                return false;
            }
        }

        else if(g->GetType() == GateType::GATE_RECIEVER)
        {
            if(dynamic_cast<GateReciever*>(g))
            {
                resultGates.push_back(dynamic_cast<GateReciever*>(g));
            }
            else
            {
                qDebug() << "GateCollection::generateTruthTable - Failed to cast GateReciever";
                m_pParentField->SendUserMessage("Failed. Internal error.");
                return false;
            }
        }

        else if(g->GetType() == GateType::GATE_TIMER || g->GetType() == GateType::GATE_NULL || g->GetType() == GateType::GATE_COLLECTION)
        {
            m_pParentField->SendUserMessage("Failed. Unsupported gate type for truth table. \n No nested gate collections. No timer gates.");
            return false;
        }

        else
        {
            mainGates.push_back(g);
        }
    }

    if(inputGates.empty())
    {
        m_pParentField->SendUserMessage("Failed to generate. No input(emmiter) gates.");
        return false;
    }

    if(resultGates.empty())
    {
        m_pParentField->SendUserMessage("Failed to generate. No result(reciever) gates.");
        return false;
    }

    const uint numInputs = inputGates.size();
    const uint numOutputs = resultGates.size();
    const uint numMainGates = mainGates.size();

    table.size = pow(2, numInputs);
    for (uint iTableRun = 0; iTableRun < table.size; iTableRun++)
    {
        //Generate input values
        std::vector<bool> inputValues = table.genInputs(iTableRun, numInputs);
        table.inValues.push_back(inputValues);

        for(uint iInput = 0; iInput < numInputs; iInput++)
        {
            inputGates[iInput]->SetPowerState(inputValues[iInput]);
        }

        //Must be a better way of doing this...
        for(uint i = 0; i < numMainGates; i++)
        {
            for(Gate* g : mainGates)
            {
                g->UpdateOutput();
            }
        }

        //Generate output values
        std::vector<bool> outputValues;
        for(uint iOutput = 0; iOutput < numOutputs; iOutput++)
        {
            outputValues.push_back(resultGates[iOutput]->GetValue());
        }
        table.outValues.push_back(outputValues);
    }

    return true;
}

GateCollection::~GateCollection()
{
    //When deleted the gate collection filed can dump its contents onto the parent gatefield
    if(!m_bDontDeleteGates)
    {
        for(Gate* pGate : m_gates)
        {
            pGate->SetParentGateCollection(nullptr);
            delete pGate;
        }
    }

    //dump contents onto the parent gatefield or parent gate collection...
    else
    {
        //Dump onto parent GateCollection
        if (m_pParentGateCollection)
        {
            for (Gate* g : m_gates)
                m_pParentGateCollection->AddGate(g);
        }

        //Dump onto parent ParentField
        else if (m_pParentField)
        {
            for (Gate* g : m_gates)
            {
                m_pParentField->AddGate(g, false);
                g->SetParentGateCollection(nullptr);
            }
        }

        //Check if something went wrong
        else
        {
            qDebug() << "GateCollection::~GateCollection - Nothing to dump gates onto!";
        }
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
        return checkButtonClick(mouse);
    }

    else if(m_dragMode == DragAll)
    {
        GameObject* pClicked = Gate::checkClicked(mouse);
        if(!pClicked)
        {
            return checkButtonClick(mouse);
        }
        else
        {
            return pClicked;
        }
    }

    else
    {
        qDebug() << "GateCollection::checkClicked - Undefined drag mode!";
        return nullptr;
    }
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

void GateCollection::DrawButtons(QPainter& painter)
{
    painter.drawImage(m_deleteAllButton, Settings::ImgDeleteAllButton);
    painter.drawImage(m_deleteButton, Settings::ImgDeleteButton);
    painter.drawImage(m_saveButton, Settings::ImgSaveButton);
    painter.drawImage(m_dragAllButton, Settings::ImgDragButton);
    painter.drawImage(m_truthTableButton, Settings::ImgTruthTableButton);
    painter.drawImage(m_booleanExpressionsButton, Settings::ImgBooleanExpressions);
}

void GateCollection::SaveData(QDomDocument& storage, QDomElement& parentElement)
{
    QDomElement gateCollectionElement = storage.createElement(Settings::GateElement);

    SaveGeneralData(gateCollectionElement);

    for(Gate* gate : m_gates)
    {
        gate->SaveData(storage, gateCollectionElement);
    }

    parentElement.appendChild(gateCollectionElement);
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
        }

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

    m_deleteAllButton  = QRect(m_geometry.right() - Settings::ButtonSize, m_geometry.top() - Settings::ButtonSize, Settings::ButtonSize, Settings::ButtonSize);
    m_deleteButton = QRect(m_geometry.right() - Settings::ButtonSize*2, m_geometry.top() - Settings::ButtonSize, Settings::ButtonSize, Settings::ButtonSize);
    m_saveButton = QRect(m_geometry.right() - Settings::ButtonSize*3, m_geometry.top() - Settings::ButtonSize, Settings::ButtonSize, Settings::ButtonSize);
    m_dragAllButton = QRect(m_geometry.right() - Settings::ButtonSize*4, m_geometry.top() - Settings::ButtonSize, Settings::ButtonSize, Settings::ButtonSize);
    m_truthTableButton = QRect(m_geometry.right() - Settings::ButtonSize*5, m_geometry.top() - Settings::ButtonSize, Settings::ButtonSize, Settings::ButtonSize);
    m_booleanExpressionsButton = QRect(m_geometry.right() - Settings::ButtonSize*6, m_geometry.top() - Settings::ButtonSize, Settings::ButtonSize, Settings::ButtonSize);
}

void GateCollection::ToggleDragMode()
{
    m_dragMode = (bool)m_dragMode ? DragIndividual : DragAll;
    m_pParentField->UpdateGateSelected(this);
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

GameObject* GateCollection::checkButtonClick(const QPoint& mouse)
{
    //Save button
    if(m_saveButton.contains(mouse))
    {
        m_pParentField->StartSaveGateCollection(this);
        if(m_pParentField->GetCurrentClickMode() == CLICK_DEFAULT)
        {
            return this;
        }
        if(m_pParentField->GetCurrentClickMode() == CLICK_DRAG)
        {
            m_pParentField->UpdateGateSelected(this);
        }
        return nullptr;
    }

    //Delete button
    else if (m_deleteButton.contains(mouse))
    {
        //Keep gates in memory, but remove them from this list,
        //since we're deleting this collection, its gets dumped onto gatefield
        m_bDontDeleteGates = true;

        m_pParentField->UpdateGateSelected(nullptr);

        if (m_pParentGateCollection)
        {
            m_pParentGateCollection->ForgetGate(this);
        }
        else if(m_pParentField)
        {
            m_pParentField->ForgetChild(this);
        }

        delete this;
    }

    //Delete all button
    else if (m_deleteAllButton.contains(mouse))
    {
        m_pParentField->UpdateGateSelected(nullptr);

        if (m_pParentGateCollection)
        {
            m_pParentGateCollection->ForgetGate(this);
        }
        else if(m_pParentField)
        {
            m_pParentField->ForgetChild(this);
        }
        delete this;
    }

    else if (m_truthTableButton.contains(mouse))
    {
        TruthTable table;
        if(generateTruthTable(table))
        {
            m_pParentField->showTruthTable(table);
        }

        if(m_pParentField->GetCurrentClickMode() == CLICK_DEFAULT)
        {
            return this;
        }
        if(m_pParentField->GetCurrentClickMode() == CLICK_DRAG)
        {
            m_pParentField->UpdateGateSelected(this);
        }
        return nullptr;
    }

    else if (m_dragAllButton.contains(mouse))
    {
        ToggleDragMode();
        if(m_pParentField->GetCurrentClickMode() == CLICK_DEFAULT)
        {
            return this;
        }
        if(m_pParentField->GetCurrentClickMode() == CLICK_DRAG)
        {
            m_pParentField->UpdateGateSelected(this);
        }
        return nullptr;
    }

    else if(m_booleanExpressionsButton.contains(mouse))
    {
        TruthTable table;
        if(generateTruthTable(table))
        {
            std::vector<BooleanExpression> expressions;
            ExpressionCalculatorResult result = BooleanExpressionCalculator::truthTableToBooleanExpressions(table, expressions);
            if(result == ExpressionCalculatorResult::SUCESS)
            {
                if(m_pParentField)
                {
                    m_pParentField->showBooleanExpressions(expressions);
                }
                else
                {
                    qDebug() << "GateCollection::checkButtonClick - Failed to display boolean expressions.";
                }
            }
            else
            {
                m_pParentField->SendUserMessage("Internal error. Failed to generate boolean expressions.");
            }
        }

        if(m_pParentField->GetCurrentClickMode() == CLICK_DEFAULT)
        {
            return this;
        }
        if(m_pParentField->GetCurrentClickMode() == CLICK_DRAG)
        {
            m_pParentField->UpdateGateSelected(this);
        }
        return nullptr;
    }

    return nullptr;
}

Gate* GateCollection::Clone()
{
    std::vector<Gate*> clonedGates;
    for (Gate* pGate : m_gates)
    {
        clonedGates.push_back(pGate->Clone());
    }

    GateCollection* pClone = new GateCollection(clonedGates);
    Gate::baseClone(pClone);

    pClone->m_geometry = m_geometry;
    pClone->m_dragMode = m_dragMode;

    return pClone;
}
