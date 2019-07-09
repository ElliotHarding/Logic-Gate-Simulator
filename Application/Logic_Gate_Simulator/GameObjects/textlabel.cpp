#include "textlabel.h"
#include "dlg_textedit.h"

TextLabel::TextLabel() :
    Gate(GATE_TEXT_LABEL, 20,20),
    m_string("Label"),
    m_font("Helvetica", 15),
    m_editClickZone(QRect(0,0,EDIT_ZONE_WIDTH,EDIT_ZONE_WIDTH))
{

    //Can't be bothered instanciating this in memory before,
    //its a tiny dlg anyways...
    m_pEditDlg = new DLG_LabelGateEdit(this);

    Update(m_font, m_string);
}

TextLabel::~TextLabel()
{
    m_pEditDlg = nullptr;
}

void TextLabel::UpdateGraphics(QPainter *painter)
{
    painter->setBrush(QBrush(Qt::gray));
    painter->drawRect(m_editClickZone);

    painter->setFont(m_font);
    painter->drawText(m_layout, m_string);
}

bool TextLabel::UpdateDrag(int clickX, int clickY)
{
    //When a textlabel is clicked on its editor opens up
    if(m_editClickZone.contains(clickX, clickY))
    {
        m_pEditDlg->show();

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

    const QPoint pos = GetPosition();
    m_layout.setLeft(pos.x() - m_width/2);
    m_layout.setTop(pos.y() - m_height/2);
    m_layout.setRight(pos.x() + m_width/2);
    m_layout.setBottom(pos.y()  + m_height/2);
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


DLG_LabelGateEdit::DLG_LabelGateEdit(TextLabel* textLabel) :
    DLG_TextEdit(textLabel->GetString(), textLabel->GetFont()),
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
        m_pTextLabel->Update(m_font, m_savedString);
}
