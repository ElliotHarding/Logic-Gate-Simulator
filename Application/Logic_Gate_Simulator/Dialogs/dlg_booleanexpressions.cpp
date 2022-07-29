#include "dlg_booleanexpressions.h"
#include "ui_dlg_booleanexpressions.h"

#include "truthtable.h"

#include <QPainter>
#include <QMouseEvent>

namespace Settings
{
const uint IntStartAlphabet = 65;
const uint IntEndAlphabet = 122;

const QFont BooleanExpressionLetterFont("Helvetica", 15);
const QString BooleanExpressionLetterInverted = "_";

const QRect BooleanExpressionsRect(10, 80, 400, 220);
const QRect BooleanResultsRect(420, 80, 80, BooleanExpressionsRect.height());

const uint ExpressionHeight = 50;

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

    uint yPos = Settings::BooleanExpressionsRect.top();
    const uint txtExpressionWidth = Settings::BooleanExpressionsRect.width();
    for(uint iExpression = 0; iExpression < expressions.size(); iExpression++)
    {
        BooleanExpressionDisplay* pExpressionDisplay = new BooleanExpressionDisplay(this, expressions[iExpression]);
        pExpressionDisplay->setGeometry(Settings::BooleanExpressionsRect.left(), yPos, txtExpressionWidth, Settings::ExpressionHeight);
        m_uiExpressions.push_back(pExpressionDisplay);

        QLabel* pResultLabel = new QLabel(this);
        pResultLabel->setText("=" + QString(expressions[iExpression].resultLetter));
        pResultLabel->setGeometry(Settings::BooleanResultsRect.left(), yPos, Settings::BooleanResultsRect.width(), Settings::ExpressionHeight);
        pResultLabel->setFont(Settings::BooleanExpressionLetterFont);
        m_uiResultLabels.push_back(pResultLabel);

        yPos += Settings::ExpressionHeight;
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

    for(QLabel* pResultLabel : m_uiResultLabels)
    {
        delete pResultLabel;
    }
    m_uiResultLabels.clear();
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
    const uint letterSpaceWidth = geometry().width() / m_expression.letters.size();
    const uint letterIndex = mouseEvent->pos().x() / letterSpaceWidth;

    if(letterIndex < m_expression.letters.size() && m_expression.letters[letterIndex] >= char(Settings::IntStartAlphabet) && m_expression.letters[letterIndex] <= char(Settings::IntEndAlphabet))
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

    const uint letterSpaceWidth = geometry().width() / m_expression.letters.size();
    for(uint i = 0; i < m_expression.letters.size(); i++)
    {
        if(m_expression.inverted[i])
        {
            painter.drawText(QPointF((letterSpaceWidth/2) + (letterSpaceWidth * i) - (textFontMetrics.horizontalAdvance(m_expression.letters[i])/2), Settings::ExpressionDisplayInvertedMargin), Settings::BooleanExpressionLetterInverted);
        }
        painter.drawText(QPointF((letterSpaceWidth/2) + (letterSpaceWidth * i) - (textFontMetrics.horizontalAdvance(m_expression.letters[i])/2), (geometry().height()/2) - textFontMetrics.height()), QString(m_expression.letters[i]));
    }
}
