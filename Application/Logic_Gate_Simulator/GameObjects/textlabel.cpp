#include "textlabel.h"
#include "dlg_textedit.h"
#include "gatefield.h"

static int AttachIdCounter = 0;

namespace Settings
{
const uint DefaultSizeX = 20;
const uint DefaultSizeY = 20;
}

TextLabel::TextLabel(const int &x, const int &y, const QString& text, const QFont& font, const int& attachId) :
    Gate(GATE_TEXT_LABEL, x, y, Settings::DefaultSizeX, Settings::DefaultSizeY),
    m_attachId(attachId)
{
    if(attachId == -1)
    {
        m_attachId = AttachIdCounter++;
    }

    update(font, text);
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

void TextLabel::saveData(QDomDocument &storage, QDomElement &parentElement)
{
    QDomElement gateElement = storage.createElement(Settings::GateElement);

    Gate::saveGeneralData(storage, gateElement);

    gateElement.setAttribute(Settings::GateTextLabelTextTag, m_string);
    gateElement.setAttribute(Settings::GateTextLabelAttachId, QString::number(m_attachId));
    gateElement.setAttribute(Settings::GateTextLabelFontSizeTag, QString::number(m_font.pointSize()));
    gateElement.setAttribute(Settings::GateTextLabelBoldTag, QString::number(m_font.bold()));
    gateElement.setAttribute(Settings::GateTextLabelUnderlinedTag, QString::number(m_font.underline()));

    parentElement.appendChild(gateElement);
}

Gate* TextLabel::clone()
{
    TextLabel* clone = new TextLabel(position().x(), position().y(), m_string, m_font, m_attachId);

    Gate::baseClone(clone);

    return clone;
}

void TextLabel::update(const QFont& font, const QString& string)
{
    m_string = string;
    m_font = font;

    const QFontMetrics textFontMetrics(m_font);

    //Update dimensions since text has changed:
    m_geometry.setWidth(textFontMetrics.horizontalAdvance(m_string));
    m_geometry.setHeight(textFontMetrics.height());
}

QString TextLabel::getString()
{
    return m_string;
}

QFont TextLabel::getFont()
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

void DLG_LabelGateEdit::editTextLabel(TextLabel* textLabel)
{
    m_pTextLabel = textLabel;
    Setup(textLabel->getString(), textLabel->getFont());
    show();
}

void DLG_LabelGateEdit::updateOverrideObject()
{
    if(m_pTextLabel)
        m_pTextLabel->update(m_font, m_savedString);
}
