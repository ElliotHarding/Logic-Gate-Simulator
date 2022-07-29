#include "dlg_booleanexpressions.h"
#include "ui_dlg_booleanexpressions.h"

#include "truthtable.h"

#include <QPainter>
#include <QMouseEvent>

#include <cmath>

namespace Settings
{
const uint IntStartAlphabet = 65;
const uint IntEndAlphabet = 122;

const QFont BooleanExpressionLetterFont("Helvetica", 15);
const QString BooleanExpressionLetterInverted = "_";

const QRect BooleanExpressionsRect(10, 80, 500, 220);

const uint ExpressionDisplayInvertedMargin = 2;
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

    const uint letterHeight = Settings::BooleanExpressionsRect.height() / expressions.size();
    const uint txtExpressionWidth = Settings::BooleanExpressionsRect.width();
    for(uint iExpression = 0; iExpression < expressions.size(); iExpression++)
    {
        const uint yPos = Settings::BooleanExpressionsRect.top() + (Settings::BooleanExpressionsRect.height() / expressions.size()) * iExpression;

        BooleanExpressionDisplay* pExpressionDisplay = new BooleanExpressionDisplay(this, expressions[iExpression]);
        pExpressionDisplay->setGeometry(Settings::BooleanExpressionsRect.left(), yPos, txtExpressionWidth, letterHeight);
        m_uiExpressions.push_back(pExpressionDisplay);
    }

    open();
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
    for(BooleanExpressionDisplay* pBooleanExpressionDispaly : m_uiExpressions)
    {
        delete pBooleanExpressionDispaly;
    }
    m_uiExpressions.clear();
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief BooleanExpressionDisplay::BooleanExpressionDisplay
/// \param pParent
///
BooleanExpressionDisplay::BooleanExpressionDisplay(QWidget* pParent, const BooleanExpression& expression) : QWidget(pParent)
{
    m_expression = expression;
    setFont(Settings::BooleanExpressionLetterFont);
}

BooleanExpression BooleanExpressionDisplay::getExpression()
{
    BooleanExpression expression;
    return expression;
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
