#include "textlabel.h"

TextLabel::TextLabel() :
    DragableGameObject (TEXT_LABEL, 20,20),
    m_string(""),
    m_font("Helvetica", 5),
    m_bUnderlined(false)
{
}

void TextLabel::UpdateGraphics(QPainter *painter)
{
    painter->setFont(m_font);
    painter->drawText(GetPosition(), m_string);
}

GameObject* TextLabel::Clone()
{
    TextLabel* clone = new TextLabel();

    clone->Update(m_font, m_string, m_bUnderlined);

    //Clone position
    QPoint pos = GetPosition();
    clone->SetPosition(pos.x(), pos.y());

    return clone;
}

void TextLabel::Update(QFont font, QString string, bool isUnderlined)
{
    m_string = string;
    m_font = font;
    m_bUnderlined = isUnderlined;
}

void TextLabel::UpdateString(QString string)
{
    m_string = string;
}

void TextLabel::UpdateFont(QFont font)
{
    m_font = font;
}

void TextLabel::UpdateUnderlined(bool isUnderlined)
{
    m_bUnderlined = isUnderlined;
}
