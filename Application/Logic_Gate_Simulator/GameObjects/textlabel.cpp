#include "textlabel.h"
#include "dlg_textedit.h"
#include "gatefield.h"

static int AttachIdCounter = 0;

namespace Settings
{
const uint DefaultSizeX = 20;
const uint DefaultSizeY = 20;

const QFont TextFont("Helvetica", 15);
}

TextLabel::TextLabel(const int &x, const int &y, const QString& text, const int& attachId) :
    Gate(GATE_TEXT_LABEL, x, y, Settings::DefaultSizeX, Settings::DefaultSizeY),
    m_string(text),
    m_font(Settings::TextFont),
    m_attachId(attachId)
{
    if(attachId == -1)
    {
        m_attachId = AttachIdCounter++;
    }

    Update(m_font, m_string);
}

TextLabel::~TextLabel()
{
    if(m_pAttachedGate)
    {
        m_pAttachedGate->removeAttachedLabel(this);
    }
}

void TextLabel::draw(QPainter& painter)
{
    painter.setFont(m_font);
    painter.drawText(m_geometry, m_string);
}

void TextLabel::SaveData(QDomDocument &storage, QDomElement &parentElement)
{
    QDomElement gateElement = storage.createElement(Settings::GateElement);

    Gate::SaveGeneralData(gateElement);

    gateElement.setAttribute(Settings::GateTextLabelTextTag, m_string);
    gateElement.setAttribute(Settings::GateTextLabelAttachId, m_attachId);

    parentElement.appendChild(gateElement);
}

Gate* TextLabel::Clone()
{
    TextLabel* clone = new TextLabel(m_geometry.x(), m_geometry.y(), m_string, m_attachId);
    clone->Update(m_font, m_string);

    Gate::baseClone(clone);

    return clone;
}

void TextLabel::Update(const QFont& font, const QString& string)
{
    m_string = string;
    m_font = font;

    const QFontMetrics textFontMetrics(m_font);

    //Update dimensions since text has changed:
    m_geometry.setWidth(textFontMetrics.horizontalAdvance(m_string));
    m_geometry.setHeight(textFontMetrics.height());
}

QString TextLabel::GetString()
{
    return m_string;
}

QFont TextLabel::GetFont()
{
    return m_font;
}

void TextLabel::attachGate(Gate* pGate)
{
    m_pAttachedGate = pGate;
}

int TextLabel::attachId() const
{
    return m_attachId;
}

void TextLabel::genNewAttachId()
{
    m_attachId = AttachIdCounter++;
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
