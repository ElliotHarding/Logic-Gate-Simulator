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

void DLG_BooleanExpressions::showExpressions(const std::vector<BooleanExpression>& expressions)
{
    clear();

    uint yPos = Settings::BooleanExpressionsRect.top();
    const uint txtExpressionWidth = Settings::BooleanExpressionsRect.width();
    for(uint iExpression = 0; iExpression < expressions.size(); iExpression++)
    {
        BooleanExpressionDisplay* pExpressionDisplay = new BooleanExpressionDisplay(this, expressions[iExpression]);
        pExpressionDisplay->setGeometry(Settings::BooleanResultsRect.left(), yPos, txtExpressionWidth, Settings::ExpressionHeight);
        m_uiExpressions.push_back(pExpressionDisplay);

        QLabel* pResultLabel = new QLabel(this);
        pResultLabel->setText("=" + QString(expressions[iExpression].resultLetter));
        pResultLabel->setGeometry(Settings::BooleanResultsRect.left(), yPos, Settings::BooleanResultsRect.width(), Settings::ExpressionHeight);
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
BooleanExpressionDisplay::BooleanExpressionDisplay(QWidget* pParent, const BooleanExpression& expression) : QLineEdit(pParent)
{
    setText(BooleanExpression(expression).lettersAsString());
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
