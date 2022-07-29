#include "dlg_booleanexpressions.h"
#include "ui_dlg_booleanexpressions.h"

#include "truthtable.h"

#include <QPainter>

namespace Settings
{
const uint IntStartAlphabet = 65;
const uint IntEndAlphabet = 122;

const QFont BooleanExpressionLetterFont("Helvetica", 15);
const QString BooleanExpressionLetterInverted = "_";

const QRect BooleanExpressionsRect(10, 80, 400, 220);
const QRect BooleanResultsRect(420, 80, 80, BooleanExpressionsRect.height());

const uint ExpressionHeight = 50;
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

void DLG_BooleanExpressions::showExpressions(std::vector<BooleanExpression>& expressions)
{
    clear();

    /*
    const uint letterHeight = Settings::BooleanExpressionsRect.height() / expressions.size();
    for(uint iExpression = 0; iExpression < expressions.size(); iExpression++)
    {
        const uint yPos = Settings::BooleanExpressionsRect.top() + (Settings::BooleanExpressionsRect.height() / expressions.size()) * iExpression;
        const uint letterWidth = Settings::BooleanExpressionsRect.width() / expressions[iExpression].letters.size();

        for(uint iLetter = 0; iLetter < expressions[iExpression].letters.size(); iLetter++)
        {
            BooleanExpressionLetter* pBooleanExpressionLetter = new BooleanExpressionLetter(this, QString(expressions[iExpression].letters[iLetter]), expressions[iExpression].inverted[iLetter], true);
            pBooleanExpressionLetter->setGeometry(Settings::BooleanExpressionsRect.left() + (iLetter * letterWidth), yPos, letterWidth, letterHeight);
            m_booleanLetters.push_back(pBooleanExpressionLetter);
        }

        BooleanExpressionLetter* pResultBooleanExpressionLetter = new BooleanExpressionLetter(this, "=" + QString(expressions[iExpression].resultLetter), false, false);
        pResultBooleanExpressionLetter->setGeometry(Settings::BooleanResultsRect.left(), yPos, Settings::BooleanResultsRect.width(), letterHeight);
        m_booleanLetters.push_back(pResultBooleanExpressionLetter);
    }*/

    uint yPos = Settings::BooleanExpressionsRect.top();
    const uint txtExpressionWidth = Settings::BooleanExpressionsRect.width();
    for(uint iExpression = 0; iExpression < expressions.size(); iExpression++)
    {
        BooleanExpressionDisplay* pExpressionDisplay = new BooleanExpressionDisplay(this, expressions[iExpression]);
        pExpressionDisplay->setGeometry(Settings::BooleanResultsRect.left(), yPos, txtExpressionWidth, Settings::ExpressionHeight);

        m_uiExpressions.push_back(pExpressionDisplay);

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
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief BooleanExpressionDisplay::BooleanExpressionDisplay
/// \param pParent
///
BooleanExpressionDisplay::BooleanExpressionDisplay(QWidget* pParent, BooleanExpression &expression) : QLineEdit(pParent)
{
    setText(expression.lettersAsString());
    m_invertedLetters = expression.inverted;
    setFont(Settings::BooleanExpressionLetterFont);
}

BooleanExpression BooleanExpressionDisplay::getExpression()
{

}

void BooleanExpressionDisplay::mousePressEvent(QMouseEvent *mouseEvent)
{

}

void BooleanExpressionDisplay::paintEvent(QPaintEvent *paintEvent)
{
    QPainter painter(this);

    const QFontMetrics textFontMetrics(Settings::BooleanExpressionLetterFont);
    painter.setFont(Settings::BooleanExpressionLetterFont);

    const uint invertedWidth = textFontMetrics.horizontalAdvance(text());
    for(uint i = 0; i < text().length(); i++)
    {
        if(m_invertedLetters[i])
        {
            painter.drawText(QPointF(i * invertedWidth, geometry().top()), Settings::BooleanExpressionLetterInverted);
        }
    }
}
