#include "dlg_booleanexpressions.h"
#include "ui_dlg_booleanexpressions.h"

#include "truthtable.h"

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
const uint ExpressionDisplayInvertedMargin = 2;
const uint ExpressionDisplayRemoveButtonSize = 10;
}

DLG_BooleanExpressions::DLG_BooleanExpressions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DLG_BooleanExpressions)
{
    ui->setupUi(this);
}

DLG_BooleanExpressions::~DLG_BooleanExpressions()
{
    clear();
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

    const uint layerIndex = ui->list_expressions->row(pItem);

    ui->list_expressions->removeItemWidget(pItem);
    delete pItem;

    if(layerIndex == 0)//Todo
    {
        return;//todo
    }
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

}

void DLG_BooleanExpressions::on_btn_genTruthTable_clicked()
{
    //Todo gen boolean expressions vector from UI

}

void DLG_BooleanExpressions::clear()
{
    //Todo check it deletes items...
    ui->list_expressions->clear();
}

void DLG_BooleanExpressions::on_btn_addExpression_clicked()
{
    BooleanExpression newExpression;
    newExpression.addTerm('A');
    newExpression.resultLetter = Settings::IntEndAlphabet - ui->list_expressions->count();

    addUiExpression(newExpression);
}

void DLG_BooleanExpressions::addUiExpression(const BooleanExpression &expression)
{
    QListWidgetItem* pItem = new QListWidgetItem();
    BooleanExpressionDisplay* pExpressionDisplay = new BooleanExpressionDisplay(this, pItem, expression, QRect(0, 0, ui->list_expressions->width() * 0.8, Settings::ExpressionDisplayHeight));
    pItem->setSizeHint(QSize(ui->list_expressions->width(), Settings::ExpressionDisplayHeight));
    ui->list_expressions->addItem(pItem);
    ui->list_expressions->setItemWidget(pItem, pExpressionDisplay);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief BooleanExpressionDisplay::BooleanExpressionDisplay
/// \param pParent
///
BooleanExpressionDisplay::BooleanExpressionDisplay(DLG_BooleanExpressions* pParent, QListWidgetItem* pListWidgetItem, const BooleanExpression& expression, const QRect& cfgGeometry) : QWidget(pParent),
    m_pParent(pParent),
    m_pListWidgetItem(pListWidgetItem),
    m_expression(expression)
{
    setFont(Settings::BooleanExpressionLetterFont);

    setGeometry(cfgGeometry);

    m_pRemoveBtn = new QPushButton(this);
    m_pRemoveBtn->setGeometry(geometry().width() - Settings::ExpressionDisplayRemoveButtonSize, geometry().height()/2 - Settings::ExpressionDisplayRemoveButtonSize/2, Settings::ExpressionDisplayRemoveButtonSize, Settings::ExpressionDisplayRemoveButtonSize);
    connect(m_pRemoveBtn, SIGNAL(pressed()), this, SLOT(onRemoveButtonClicked()));
}

BooleanExpressionDisplay::~BooleanExpressionDisplay()
{
    delete m_pRemoveBtn;
}

BooleanExpression BooleanExpressionDisplay::getExpression()
{
    return m_expression;
}

void BooleanExpressionDisplay::mousePressEvent(QMouseEvent* mouseEvent)
{
    const uint letterSpaceWidth = geometry().width() / (m_expression.letters.size() + 1);
    const uint letterIndex = std::ceil(mouseEvent->pos().x() / letterSpaceWidth);

    if(letterIndex < m_expression.letters.size() && letterIndex < m_expression.letters.size() && m_expression.letters[letterIndex] >= char(Settings::IntStartAlphabet) && m_expression.letters[letterIndex] <= char(Settings::IntEndAlphabet))
    {
        m_expression.inverted[letterIndex] = !m_expression.inverted[letterIndex];
    }

    update();
}

void BooleanExpressionDisplay::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    const QFontMetrics textFontMetrics(Settings::BooleanExpressionLetterFont);
    painter.setFont(Settings::BooleanExpressionLetterFont);

    const uint lettersSize = m_expression.letters.size();
    const uint letterSpaceWidth = geometry().width() / (m_expression.letters.size() + 1);
    for(uint i = 0; i < lettersSize; i++)
    {
        if(m_expression.inverted[i])
        {
            painter.drawText(QPointF((letterSpaceWidth/2) + (letterSpaceWidth * i) - (textFontMetrics.horizontalAdvance(m_expression.letters[i])/2), Settings::ExpressionDisplayInvertedMargin), Settings::BooleanExpressionLetterInverted);
        }
        painter.drawText(QPointF((letterSpaceWidth/2) + (letterSpaceWidth * i) - (textFontMetrics.horizontalAdvance(m_expression.letters[i])/2), (geometry().height()/2) + (textFontMetrics.height()/2)), QString(m_expression.letters[i]));
    }

    const QString resultLetterDispaly = "=" + QString(m_expression.resultLetter);
    painter.drawText(QPointF((letterSpaceWidth/2) + (letterSpaceWidth * lettersSize) - (textFontMetrics.horizontalAdvance(resultLetterDispaly)/2), (geometry().height()/2) + (textFontMetrics.height()/2)), resultLetterDispaly);
}

void BooleanExpressionDisplay::onRemoveButtonClicked()
{
    m_pParent->removeUiExpression(m_pListWidgetItem);
}
