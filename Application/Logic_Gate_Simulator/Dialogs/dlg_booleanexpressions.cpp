#include "dlg_booleanexpressions.h"
#include "ui_dlg_booleanexpressions.h"
#include "dlg_home.h"

#include "truthtable.h"
#include "converter.h"
#include "gatecollection.h"

#include <QPainter>
#include <QMouseEvent>
#include <cmath>

namespace Settings
{
const uint ExpressionDisplayHeight = 50;
const QRect ExpressionDisplayRemoveButtonGeometry = QRect(460, 13, 24, 24);
const QRect ExpressionDisplayTextGeometry = QRect(10, 10, 420, 30);
const QRect ExpressionDisplayResultLabelGeometry = QRect(440, 15, 30, 20);
}

DLG_BooleanExpressions::DLG_BooleanExpressions(DLG_Home* pHome) :
    QDialog(pHome),
    ui(new Ui::DLG_BooleanExpressions),
    m_pHome(pHome)
{
    ui->setupUi(this);
}

DLG_BooleanExpressions::~DLG_BooleanExpressions()
{
    clear();
    delete ui;
}

void DLG_BooleanExpressions::open()
{
    if(ui->list_expressions->count() == 0)
    {
        BooleanExpression newExpression;
        newExpression.letters = {'A', 'B'};
        newExpression.resultLetter = 'Z';
        addUiExpression(newExpression);
    }

    QDialog::open();
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
}

void DLG_BooleanExpressions::addUiExpression(const BooleanExpression &expression)
{
    QListWidgetItem* pItem = new QListWidgetItem();
    BooleanExpressionDisplay* pExpressionDisplay = new BooleanExpressionDisplay(this, pItem, expression);
    pItem->setSizeHint(QSize(ui->list_expressions->width() * 0.8, Settings::ExpressionDisplayHeight));
    ui->list_expressions->addItem(pItem);
    ui->list_expressions->setItemWidget(pItem, pExpressionDisplay);
}

void DLG_BooleanExpressions::on_btn_ok_clicked()
{
    close();
}

void DLG_BooleanExpressions::on_btn_genCircuit_clicked()
{
    std::vector<BooleanExpression> expressions;
    for(int i = 0; i < ui->list_expressions->count(); i++)
    {
        BooleanExpressionDisplay* pExpressionDisplay = dynamic_cast<BooleanExpressionDisplay*>(ui->list_expressions->itemWidget(ui->list_expressions->item(i)));
        expressions.push_back(pExpressionDisplay->getExpression());
    }

    GateCollection* pNewGateCollection = new GateCollection(std::vector<Gate*>());
    if(Converter::booleanExpressionsToCircuit(expressions, m_pHome->getCircuitGenOptions(), pNewGateCollection) == ConverterResult::SUCCESS)
    {
        m_pHome->showGeneratedCircuit(pNewGateCollection);
    }
    else
    {
        delete pNewGateCollection;
        m_pHome->sendUserMessage("Failed to convert to circuit. Check format of boolean expressions.");
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
    if(Converter::expressionsToTruthTable(expressions, truthTable) == ConverterResult::SUCCESS)
    {
        m_pHome->showGeneratedTruthTable(truthTable);
        close();
    }
    else
    {
        m_pHome->sendUserMessage("Failed to generate truth table! Check format of boolean expressions.");
    }
}

void DLG_BooleanExpressions::on_btn_simplify_clicked()
{
    std::vector<BooleanExpression> expressions;
    for(int i = 0; i < ui->list_expressions->count(); i++)
    {
        BooleanExpressionDisplay* pExpressionDisplay = dynamic_cast<BooleanExpressionDisplay*>(ui->list_expressions->itemWidget(ui->list_expressions->item(i)));
        expressions.push_back(pExpressionDisplay->getExpression());
    }

    if(m_pHome->getCurrentConversionAlgorithm() == ConversionAlgorithm::Random)
    {
        TruthTable tt;
        if(Converter::expressionsToTruthTable(expressions, tt) == ConverterResult::SUCCESS)
        {
            m_pHome->runRandomConversionThread(tt, GoalResult::GR_BooleanExpressions);
        }
        else
        {
            m_pHome->sendUserMessage("Failed to optimize expressions.\n Please check they are a valid format");
        }
        return;
    }

    if(Converter::simplifyBooleanExpressions(expressions, m_pHome->getCurrentConversionAlgorithm()) == ConverterResult::SUCCESS)
    {
        showExpressions(expressions);
        m_pHome->sendUserMessage("Optimization complete.\n Check out alternative algorithms in settings.");
    }
    else
    {
        m_pHome->sendUserMessage("Failed to optimize expressions.\n Please check they are a valid format");
    }
}

void DLG_BooleanExpressions::on_btn_addExpression_clicked()
{
    BooleanExpression newExpression;
    newExpression.addTerm('A');

    char newResultLetter = 'Z';
    bool found = true;
    while(found)
    {
        found = false;
        for(int i = 0; i < ui->list_expressions->count(); i++)
        {
            BooleanExpressionDisplay* pExpressionDisplay = dynamic_cast<BooleanExpressionDisplay*>(ui->list_expressions->itemWidget(ui->list_expressions->item(i)));
            if(pExpressionDisplay->getExpression().resultLetter == newResultLetter)
            {
                found = true;
                newResultLetter--;
                break;
            }
        }
    }

    newExpression.resultLetter = newResultLetter;

    addUiExpression(newExpression);
}

void DLG_BooleanExpressions::clear()
{
    ui->list_expressions->clear();
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
    m_pExpressionText(new BooleanExpressionLineEdit(this, expression, pParent)),
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

void BooleanExpressionDisplay::updateResultLetter(const char& resultLetter)
{
    m_resultLetter = resultLetter;
    m_pResultLabel->setText("= " + QString(m_resultLetter));
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
BooleanExpressionLineEdit::BooleanExpressionLineEdit(QWidget* pParent, const BooleanExpression& expression, DLG_BooleanExpressions* pDlgExpressions) : QLineEdit(pParent),
    m_pDlgExpressions(pDlgExpressions)
{
    QString displayedExpression = "";
    for(uint i = 0; i < expression.letters.size(); i++)
    {
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
        expression.letters.push_back(displayedExpression[i].toLatin1());
    }

    return expression;
}

