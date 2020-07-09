#include "textlabel.h"
#include "dlg_textedit.h"
#include "gatefield.h"

TextLabel::TextLabel() :
    Gate(GATE_TEXT_LABEL, 20,20),
    m_string("Label"),
    m_font("Helvetica", 15),
    m_editClickZone(QRect(0,0,EDIT_ZONE_WIDTH,EDIT_ZONE_WIDTH))
{
    Update(m_font, m_string);
}

TextLabel::~TextLabel()
{
    m_pParentField = nullptr;
}

void TextLabel::UpdateGraphics(QPainter *painter)
{
    painter->fillRect(m_editClickZone, QBrush(Qt::gray));

    painter->setFont(m_font);
    painter->drawText(m_layout, m_string);
}

bool TextLabel::UpdateDrag(int clickX, int clickY)
{
    //When a textlabel is clicked on its editor opens up
    if(m_editClickZone.contains(clickX, clickY))
    {
        m_pParentField->EditTextLabel(this);
        return false;
    }

    else
        return Gate::UpdateDrag(clickX, clickY);
}

void TextLabel::SetPosition(int x, int y)
{
    Gate::SetPosition(x, y);

    m_editClickZone = QRect(Right(), Top(), EDIT_ZONE_WIDTH, EDIT_ZONE_HEIGHT);
}

Gate* TextLabel::Clone()
{
    TextLabel* clone = new TextLabel();

    clone->Update(m_font, m_string);

    //Clone position
    QPoint pos = GetPosition();
    clone->SetPosition(pos.x(), pos.y());

    return clone;
}

void TextLabel::Update(QFont font, QString string)
{
    m_string = string;
    m_font = font;

    QFontMetrics fm(m_font);

    //Update dimensions since text has changed:
    m_width = fm.width(m_string);
    m_height = fm.height();

    //Rests everything due to changed m_width & m_height
    SetPosition(GetPosition().x(), GetPosition().y());
}

QString TextLabel::GetString()
{
    return m_string;
}

QFont TextLabel::GetFont()
{
    return m_font;
}




//
//      DLG_LabelGateEdit
//


DLG_LabelGateEdit::DLG_LabelGateEdit() :
    DLG_TextEdit(),
    m_pTextLabel(nullptr)
{
}

DLG_LabelGateEdit::~DLG_LabelGateEdit()
{
    m_pTextLabel = nullptr;
}

void DLG_LabelGateEdit::EditTextLabel(TextLabel* textLabel)
{
    m_pTextLabel = textLabel;
    Setup(textLabel->GetString(), textLabel->GetFont());
    show();
}

void DLG_LabelGateEdit::UpdateOverrideObject()
{
    if(m_pTextLabel)
        m_pTextLabel->Update(m_font, m_savedString);
}
