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

const QRect BooleanExpressionsRect(10, 10, 400, 200);
const QRect BooleanResultsRect(420, 10, 80, BooleanExpressionsRect.height());
}

DLG_BooleanExpressions::DLG_BooleanExpressions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DLG_BooleanExpressions)
{
    ui->setupUi(this);
}

DLG_BooleanExpressions::~DLG_BooleanExpressions()
{
    clearBooleanLetters();;
    delete ui;
}

void DLG_BooleanExpressions::showExpressions(const std::vector<BooleanExpression>& expressions)
{
    const uint letterHeight = Settings::BooleanExpressionsRect.height() / expressions.size();
    for(uint iExpression = 0; iExpression < expressions.size(); iExpression++)
    {
        const uint yPos = Settings::BooleanExpressionsRect.top() + (Settings::BooleanExpressionsRect.height() / expressions.size()) * iExpression;
        const uint letterWidth = Settings::BooleanExpressionsRect.width() / expressions[iExpression].letters.size();

        for(uint iLetter = 0; iLetter < expressions[iExpression].letters.size(); iLetter++)
        {
            BooleanExpressionLetter* pBooleanExpressionLetter = new BooleanExpressionLetter(this, QString(expressions[iExpression].letters[iLetter]), expressions[iExpression].inverted[iLetter], true);
            pBooleanExpressionLetter->setGeometry(Settings::BooleanExpressionsRect.left() + (iLetter * letterWidth), yPos, letterWidth, letterHeight);
            pBooleanExpressionLetter->raise();
            pBooleanExpressionLetter->show();
            m_booleanLetters.push_back(pBooleanExpressionLetter);
        }

        BooleanExpressionLetter* pResultBooleanExpressionLetter = new BooleanExpressionLetter(this, "= " + QString(expressions[iExpression].resultLetter), false, false);
        pResultBooleanExpressionLetter->setGeometry(Settings::BooleanResultsRect.left(), yPos, Settings::BooleanResultsRect.width(), letterHeight);
        m_booleanLetters.push_back(pResultBooleanExpressionLetter);
    }

    open();
}

void DLG_BooleanExpressions::closeEvent(QCloseEvent* e)
{
    QDialog::closeEvent(e);
    clearBooleanLetters();
}

void DLG_BooleanExpressions::on_btn_ok_clicked()
{
    clearBooleanLetters();
    close();
}

void DLG_BooleanExpressions::clearBooleanLetters()
{
    for(BooleanExpressionLetter* pBooleanExpressionLetter : m_booleanLetters)
    {
        delete pBooleanExpressionLetter;
    }
    m_booleanLetters.clear();
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief BooleanExpressionLetter::BooleanExpressionLetter
/// \param pParent
///
BooleanExpressionLetter::BooleanExpressionLetter(QWidget* pParent, const QString& letter, const bool& inverted, const bool& editable) : QWidget(pParent),
    m_letter(letter),
    m_bInverted(inverted),
    m_bEditable(editable)
{
}

void BooleanExpressionLetter::mousePressEvent(QMouseEvent*)
{
    if(m_bEditable && m_letter >= Settings::IntStartAlphabet && m_letter <= Settings::IntEndAlphabet)
    {
        m_bInverted = !m_bInverted;
        update();
    }
}

void BooleanExpressionLetter::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    const QFontMetrics textFontMetrics(Settings::BooleanExpressionLetterFont);
    painter.setFont(Settings::BooleanExpressionLetterFont);

    const qreal xCenter = geometry().width()/2;
    const qreal yCenter = geometry().height()/2;
    painter.drawText(QPointF(xCenter - (textFontMetrics.horizontalAdvance(m_letter)/2), yCenter - textFontMetrics.height()/2), m_letter);

    if(m_bInverted)
    {
        painter.drawText(QPointF(xCenter - (textFontMetrics.horizontalAdvance(Settings::BooleanExpressionLetterInverted)/2), 0), Settings::BooleanExpressionLetterInverted);
    }
}
