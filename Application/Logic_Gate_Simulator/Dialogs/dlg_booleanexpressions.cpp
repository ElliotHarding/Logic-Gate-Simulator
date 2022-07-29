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

const uint ExpressionDisplayLeftMargin = 2;
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
BooleanExpressionDisplay::BooleanExpressionDisplay(QWidget* pParent, const BooleanExpression& expression) : QLineEdit(pParent)
{
    m_oldText = BooleanExpression(expression).lettersAsString();
    setText(m_oldText);
    m_invertedLetters = expression.inverted;
    setFont(Settings::BooleanExpressionLetterFont);

    connect(this, SIGNAL(textChanged(const QString&)), this, SLOT(onTextChanged(const QString&)));
}

BooleanExpression BooleanExpressionDisplay::getExpression()
{
    BooleanExpression expression;
    return expression;
}

void BooleanExpressionDisplay::onTextChanged(const QString& newText)
{
    if(m_oldText == newText)
    {
        return;
    }

    const int sizeDiff = newText.length() - m_oldText.length();

    //If extra letters
    if(sizeDiff > 0)
    {
        //Add extra m_invertedLetters
        for(int i = 0; i < sizeDiff; i++)
        {
            m_invertedLetters.push_back(false);
        }
    }

    //If removed a letter
    else if(sizeDiff < 0)
    {
        for(int i = 0; i < m_oldText.length(); i++)
        {
            if(i >= newText.size())
            {
                m_invertedLetters.erase(m_invertedLetters.begin() + i);
            }
            else if(newText[i] != m_oldText[i])
            {
                m_invertedLetters.erase(m_invertedLetters.begin() + i);
            }
        }
    }

    m_oldText = newText;

    update();
}

void BooleanExpressionDisplay::mousePressEvent(QMouseEvent* mouseEvent)
{
    QLineEdit::mousePressEvent(mouseEvent);

    const QFontMetrics textFontMetrics(Settings::BooleanExpressionLetterFont);
    const QString currentText = text();
    const uint invertedWidth = textFontMetrics.horizontalAdvance(currentText) / currentText.length();
    const uint letterIndex = mouseEvent->pos().x() / invertedWidth;

    if(letterIndex < m_invertedLetters.size() && letterIndex < (uint)currentText.length() && currentText[letterIndex] >= "A" && currentText[letterIndex] <= "Z")
    {
        m_invertedLetters[letterIndex] = !m_invertedLetters[letterIndex];
    }

    update();
}

void BooleanExpressionDisplay::paintEvent(QPaintEvent* paintEvent)
{
    QLineEdit::paintEvent(paintEvent);

    QPainter painter(this);

    const QFontMetrics textFontMetrics(Settings::BooleanExpressionLetterFont);
    painter.setFont(Settings::BooleanExpressionLetterFont);

    const QString currentText = text();
    const uint currentTextLen = currentText.length();

    const uint invertedWidth = textFontMetrics.horizontalAdvance(currentText) / currentTextLen;
    for(uint i = 0; i < currentTextLen; i++)
    {
        if(m_invertedLetters[i])
        {
            painter.drawText(QPointF(Settings::ExpressionDisplayLeftMargin + i * invertedWidth, 0), Settings::BooleanExpressionLetterInverted);
        }
    }
}
