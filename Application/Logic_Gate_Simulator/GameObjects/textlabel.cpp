#include "textlabel.h"
#include "dlg_textedit.h"

TextLabel::TextLabel() :
    Gate(GATE_TEXT_LABEL, 20,20),
    m_string(""),
    m_font("Helvetica", 5),
    m_bUnderlined(false),
    m_editClickZone(QRect(0,0,EDIT_ZONE_WIDTH,EDIT_ZONE_WIDTH))
{
}

void TextLabel::UpdateGraphics(QPainter *painter)
{
    painter->setBrush(QBrush(Qt::gray));
    painter->drawRect(m_editClickZone);

    painter->setFont(m_font);
    painter->drawText(GetPosition(), m_string);

    //todo underlined....
}

bool TextLabel::UpdateClicked(int clickX, int clickY)
{
    //When a textlabel is clicked on its editor opens up
    if(m_editClickZone.contains(clickX, clickY))
    {
        //Can't be bothered instanciating this in memory before,
        //its a tiny dlg anyways...
        DLG_LabelGateEdit textEditor(this);
        textEditor.show();

        return false;
    }

    return GameObject::UpdateClicked(clickX, clickY);
}

bool TextLabel::UpdateDrag(int clickX, int clickY)
{
    //When a textlabel is clicked on its editor opens up
    if(m_editClickZone.contains(clickX, clickY))
    {
        //Can't be bothered instanciating this in memory before,
        //its a tiny dlg anyways...
        DLG_LabelGateEdit textEditor(this);
        textEditor.show();

        return false;
    }

    else
        return Gate::UpdateDrag(clickX, clickY);
}

void TextLabel::SetPosition(int x, int y)
{
    Gate::SetPosition(x, y);

    m_editClickZone = QRect(Right() - EDIT_ZONE_WIDTH, Top() + EDIT_ZONE_HEIGHT, EDIT_ZONE_WIDTH, EDIT_ZONE_HEIGHT);
}

Gate* TextLabel::Clone()
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

QString TextLabel::GetString()
{
    return m_string;
}

QFont TextLabel::GetFont()
{
    return m_font;
}

bool TextLabel::IsUnderlined()
{
    return m_bUnderlined;
}




//
//      DLG_LabelGateEdit
//


DLG_LabelGateEdit::DLG_LabelGateEdit(TextLabel* textLabel) :
    DLG_TextEdit(textLabel->GetString(), textLabel->GetFont(), textLabel->IsUnderlined()),
    m_pTextLabel(textLabel)
{
}

DLG_LabelGateEdit::~DLG_LabelGateEdit()
{
    m_pTextLabel = nullptr;
}

void DLG_LabelGateEdit::UpdateOverrideObject()
{
    if(m_pTextLabel)
        m_pTextLabel->Update(m_font, m_savedString, m_bIsUnderlined);
}
