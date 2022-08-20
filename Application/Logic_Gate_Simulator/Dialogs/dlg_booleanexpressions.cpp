#include "dlg_booleanexpressions.h"
#include "ui_dlg_booleanexpressions.h"
#include "dlg_home.h"

#include "truthtable.h"
#include "gatecollection.h"
#include "circuitfromscriptthread.h"

#include <QPainter>
#include <QMouseEvent>
#include <QListWidgetItem>

#include <cmath>

namespace Settings
{
const uint IntStartAlphabet = 65;
const uint IntEndAlphabet = 122;

const QFont BooleanExpressionLetterFont("Helvetica", 15);
const QString BooleanExpressionLetterInverted = "_";

const uint ExpressionDisplayHeight = 50;
const QRect ExpressionDisplayRemoveButtonGeometry = QRect(460, 13, 24, 24);
const QRect ExpressionDisplayTextGeometry = QRect(10, 10, 420, 30);
const QRect ExpressionDisplayResultLabelGeometry = QRect(440, 15, 30, 20);
}

DLG_BooleanExpressions::DLG_BooleanExpressions(DLG_Home* pHome) :
    QDialog(pHome),
    m_pHome(pHome),
    ui(new Ui::DLG_BooleanExpressions),
    m_pCircuitFromTruthTableThread(new CircuitFromTruthTableThread())
{
    ui->setupUi(this);

    connect(m_pCircuitFromTruthTableThread, SIGNAL(circuitGenSuccess(GateCollection*)), this, SLOT(onCircuitGenSuccess(GateCollection*)));
    connect(m_pCircuitFromTruthTableThread, SIGNAL(circuitGenFailure(const QString&)), this, SLOT(onCircuitGenFailure(const QString&)));
}

DLG_BooleanExpressions::~DLG_BooleanExpressions()
{
    clear();
    delete m_pCircuitFromTruthTableThread;
    delete ui;
}

void DLG_BooleanExpressions::showExpressions(const std::vector<BooleanExpression>& expressions)
{
    clear();

    for(const BooleanExpression& expression : expressions)
    {
        addUiExpression(expression);
    }

    open();
}

void DLG_BooleanExpressions::removeUiExpression(QListWidgetItem* pItem)
{
    //Don't delete the last expression
    if(ui->list_expressions->count() <= 1)
    {
        return;
    }

    ui->list_expressions->removeItemWidget(pItem);
    delete pItem;

    ui->spinBox_outputs->setValue(ui->list_expressions->count());
}

void DLG_BooleanExpressions::closeEvent(QCloseEvent* e)
{
    QDialog::closeEvent(e);
    clear();
}

void DLG_BooleanExpressions::on_btn_ok_clicked()
{
    clear();
    close();
}

void DLG_BooleanExpressions::on_btn_genCircuit_clicked()
{
    if(m_pCircuitFromTruthTableThread->isRunning())
    {
        m_pHome->SendUserMessage("Already generating!");
        return;
    }

    std::vector<BooleanExpression> expressions;
    for(int i = 0; i < ui->list_expressions->count(); i++)
    {
        BooleanExpressionDisplay* pExpressionDisplay = dynamic_cast<BooleanExpressionDisplay*>(ui->list_expressions->itemWidget(ui->list_expressions->item(i)));
        expressions.push_back(pExpressionDisplay->getExpression());
    }

    TruthTable truthTable;
    if(BooleanExpressionCalculator::expressionsToTruthTable(expressions, truthTable) == ExpressionCalculatorResult::SUCCESS)
    {
        //Todo expose to user interface
        const uint maxSeconds = 100;
        const uint percentageRandomGate = 30;
        const uint maxGates = 10;

        if(!m_pCircuitFromTruthTableThread->start(truthTable, maxSeconds, percentageRandomGate, maxGates))
        {
            m_pHome->SendUserMessage("Failed to convert to circuit. Check format.");
        }
    }
    else
    {
        m_pHome->SendUserMessage("Failed to convert to circuit. Check format of boolean expressions.");
    }
}

void DLG_BooleanExpressions::on_btn_genTruthTable_clicked()
{
    std::vector<BooleanExpression> expressions;

    for(int i = 0; i < ui->list_expressions->count(); i++)
    {
        BooleanExpressionDisplay* pExpressionDisplay = dynamic_cast<BooleanExpressionDisplay*>(ui->list_expressions->itemWidget(ui->list_expressions->item(i)));
        expressions.push_back(pExpressionDisplay->getExpression());
    }

    TruthTable truthTable;
    if(BooleanExpressionCalculator::expressionsToTruthTable(expressions, truthTable) == ExpressionCalculatorResult::SUCCESS)
    {
        m_pHome->showTruthTable(truthTable);
        close();
    }
    else
    {
        m_pHome->SendUserMessage("Failed to generate truth table! Check format of boolean expressions.");
    }
}

void DLG_BooleanExpressions::clear()
{
    ui->list_expressions->clear();
}

void DLG_BooleanExpressions::on_btn_addExpression_clicked()
{
    BooleanExpression newExpression;
    newExpression.addTerm('A');
    newExpression.resultLetter = Settings::IntEndAlphabet - ui->list_expressions->count();

    addUiExpression(newExpression);
}

void DLG_BooleanExpressions::onCircuitGenSuccess(GateCollection* pNewCircuit)
{
    m_pHome->AddGateToGateField(pNewCircuit);
    close();
}

void DLG_BooleanExpressions::onCircuitGenFailure(const QString& failMessage)
{
    m_pHome->SendUserMessage(failMessage);
}

void DLG_BooleanExpressions::addUiExpression(const BooleanExpression &expression)
{
    QListWidgetItem* pItem = new QListWidgetItem();
    BooleanExpressionDisplay* pExpressionDisplay = new BooleanExpressionDisplay(this, pItem, expression);
    pItem->setSizeHint(QSize(ui->list_expressions->width() * 0.8, Settings::ExpressionDisplayHeight));
    ui->list_expressions->addItem(pItem);
    ui->list_expressions->setItemWidget(pItem, pExpressionDisplay);

    ui->spinBox_outputs->setValue(ui->list_expressions->count());
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief BooleanExpressionDisplay::BooleanExpressionDisplay
/// \param pParent
///
BooleanExpressionDisplay::BooleanExpressionDisplay(DLG_BooleanExpressions* pParent, QListWidgetItem* pListWidgetItem, const BooleanExpression& expression) : QWidget(pParent),
    m_pParent(pParent),
    m_pListWidgetItem(pListWidgetItem),
    m_resultLetter(expression.resultLetter),
    m_pRemoveBtn(new QPushButton(this)),
    m_pExpressionText(new BooleanExpressionLineEdit(this, expression)),
    m_pResultLabel(new QLabel(this))
{
    m_pRemoveBtn->setText("X");
    connect(m_pRemoveBtn, SIGNAL(pressed()), this, SLOT(onRemoveButtonClicked()));

    m_pResultLabel->setText("= " + QString(expression.resultLetter));
}

BooleanExpressionDisplay::~BooleanExpressionDisplay()
{
    delete m_pRemoveBtn;
}

BooleanExpression BooleanExpressionDisplay::getExpression()
{
    BooleanExpression expression = m_pExpressionText->getExpression();
    expression.resultLetter = m_resultLetter;
    return expression;
}

void BooleanExpressionDisplay::resizeEvent(QResizeEvent*)
{
    m_pRemoveBtn->setGeometry(Settings::ExpressionDisplayRemoveButtonGeometry);
    m_pExpressionText->setGeometry(Settings::ExpressionDisplayTextGeometry);
    m_pResultLabel->setGeometry(Settings::ExpressionDisplayResultLabelGeometry);
}

void BooleanExpressionDisplay::onRemoveButtonClicked()
{
    m_pParent->removeUiExpression(m_pListWidgetItem);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief BooleanExpressionLineEdit::BooleanExpressionLineEdit
/// \param pParent
/// \param expression
///
BooleanExpressionLineEdit::BooleanExpressionLineEdit(QWidget* pParent, const BooleanExpression& expression) : QLineEdit(pParent)
{
    QString displayedExpression = "";
    for(uint i = 0; i < expression.letters.size(); i++)
    {
        if(expression.inverted[i])
        {
            displayedExpression += "!";
        }
        displayedExpression += QString(expression.letters[i]);
    }
    setText(displayedExpression);
}

BooleanExpression BooleanExpressionLineEdit::getExpression()
{
    BooleanExpression expression;

    const QString displayedExpression = text();
    for(int i = 0; i < displayedExpression.length(); i++)
    {
        if(displayedExpression[i] == "!")
        {
            i++;
            expression.inverted.push_back(true);
        }
        else
        {
            expression.inverted.push_back(false);
        }
        expression.letters.push_back(displayedExpression[i].toLatin1());
    }

    return expression;
}
