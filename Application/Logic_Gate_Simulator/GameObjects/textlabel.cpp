#include "textlabel.h"
#include "dlg_textedit.h"
#include "gatefield.h"

namespace Settings
{
const uint SizeX = 20;
const uint SizeY = 20;

const uint EditButtonSize = 40;
const QImage ImgConfigureButton = QImage(std::string(":/Resources/Button Icons/gate-collection-optimize.png").c_str());

const QFont TextFont("Helvetica", 15);
}

TextLabel::TextLabel(const int &x, const int &y, const QString& text) :
    Gate(GATE_TEXT_LABEL, x, y, Settings::SizeX, Settings::SizeY),
    m_string(text),
    m_font(Settings::TextFont),
    m_editClickZone(QRect(0, 0, Settings::EditButtonSize, Settings::EditButtonSize))
{
    Update(m_font, m_string);
}

TextLabel::~TextLabel()
{
    m_pParentField = nullptr;
}

void TextLabel::draw(QPainter& painter)
{
    painter.drawImage(m_editClickZone, Settings::ImgConfigureButton);

    painter.setFont(m_font);
    painter.drawText(m_geometry, m_string);
}

void TextLabel::SaveData(QDomDocument &storage, QDomElement &parentElement)
{
    QDomElement gateElement = storage.createElement(Settings::GateElement);

    Gate::SaveGeneralData(gateElement);

    gateElement.setAttribute(Settings::GateTextLabelTextTag, m_string);

    parentElement.appendChild(gateElement);
}

GameObject *TextLabel::checkClicked(const QPoint& mouse)
{
    if(m_pParentField->GetCurrentClickMode() == CLICK_DEFAULT)
    {
        if(m_editClickZone.contains(mouse))
        {
            m_pParentField->EditTextLabel(this);
        }
        return nullptr;
    }

    return Gate::checkClicked(mouse);
}

void TextLabel::setPosition(const int& x, const int& y)
{
    Gate::setPosition(x, y);

    m_editClickZone = QRect(geometry().right(), geometry().top() - Settings::EditButtonSize, Settings::EditButtonSize, Settings::EditButtonSize);
}

Gate* TextLabel::Clone()
{
    TextLabel* clone = new TextLabel(m_geometry.x(), m_geometry.y());
    clone->Update(m_font, m_string);

    return clone;
}

void TextLabel::Update(const QFont& font, const QString& string)
{
    m_string = string;
    m_font = font;

    const QFontMetrics textFontMetrics(m_font);

    //Update dimensions since text has changed:
    m_geometry.setWidth(textFontMetrics.width(m_string));
    m_geometry.setHeight(textFontMetrics.height());
    m_editClickZone = QRect(geometry().right(), geometry().top() - Settings::EditButtonSize, Settings::EditButtonSize, Settings::EditButtonSize);
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
