#include "truthtablewidgetbase.h"

TruthTableWidgetBase::TruthTableWidgetBase(QWidget *parent) :
    QWidget(parent)
{
    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::white);
    setPalette(pal);
}

BinaryLabel::BinaryLabel(QWidget *parent) : QLabel(parent)
{
}

void BinaryLabel::SetValue(bool value)
{
    setText(value ? "1" : "0");
}

bool BinaryLabel::GetValue()
{
    return text() == "1";
}

void BinaryLabel::Disable()
{
    m_bDisabled = true;
}

void BinaryLabel::mousePressEvent(QMouseEvent *ev)
{
    if(!m_bDisabled)
        QLabel::setText(text() == "0" ? "1" : "0");
    QLabel::mousePressEvent(ev);
}
