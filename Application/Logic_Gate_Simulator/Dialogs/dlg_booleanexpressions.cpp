#include "dlg_booleanexpressions.h"
#include "ui_dlg_booleanexpressions.h"

#include "truthtable.h"

#include <QPainter>

namespace Settings
{
const uint IntStartAlphabet = 65;
const uint IntEndAlphabet = 122;

const QFont BooleanExpressionLetterFont("Helvetica", 15);

const QRect BooleanExpressionsRect(10, 0, 300, 100);
const QRect BooleanResultsRect(320, 0, 80, 100);
}

DLG_BooleanExpressions::DLG_BooleanExpressions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DLG_BooleanExpressions)
{
    ui->setupUi(this);
}

DLG_BooleanExpressions::~DLG_BooleanExpressions()
{
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

void DLG_BooleanExpressions::on_btn_ok_clicked()
{
    for(BooleanExpressionLetter* pBooleanExpressionLetter : m_booleanLetters)
    {
        delete pBooleanExpressionLetter;
    }
    m_booleanLetters.clear();

    close();
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
    if(m_letter >= Settings::IntStartAlphabet && m_letter <= Settings::IntEndAlphabet && m_bEditable)
    {
        m_bInverted = !m_bInverted;
        update();
    }
}

void BooleanExpressionLetter::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    painter.setFont(Settings::BooleanExpressionLetterFont);
    painter.drawText(QRect(0, 10, geometry().width(), geometry().height()-10), m_letter);

    if(m_bInverted)
    {
        painter.drawText(QRect(0, 0, geometry().width(), 10), "_");
    }
}
