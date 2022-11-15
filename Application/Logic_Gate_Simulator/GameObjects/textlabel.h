#ifndef TEXTLABEL_H
#define TEXTLABEL_H

#include "gate.h"
#include "dlg_textedit.h"

namespace Settings
{
const QString GateTextLabelTextTag = "Text";
const QString GateTextLabelFontSizeTag = "FontSize";
const QString GateTextLabelBoldTag = "Bold";
const QString GateTextLabelUnderlinedTag = "Underlined";
const QString GateTextLabelAttachId = "AttachId";
}

class TextLabel : public Gate
{
public:
    TextLabel(const int& x = 0, const int& y = 0, const QString& text = "Label", const QFont& font = QFont("Helvetica", 15), const int& attachId = -1);
    ~TextLabel();

    //Game Object overrides
    virtual void draw(QPainter& painter) override;
    virtual void saveData(QDomDocument& storage, QDomElement& parentElement) override;
    virtual Gate* clone() override;

    //Gate overrides
    virtual void updateOutput() override {}

    //Text label functions
    void update(const QFont& font, const QString& string);
    QString getString();
    QFont getFont();

    void attachGate(Gate* pGate);
    int attachId() const;
    void genNewAttachId();

protected:
    QString m_string;
    QFont m_font;
    Gate* m_pAttachedGate = nullptr;
    int m_attachId;
};

class DLG_LabelGateEdit : public DLG_TextEdit
{
public:
    DLG_LabelGateEdit();
    ~DLG_LabelGateEdit();

    void editTextLabel(TextLabel* textLabel);

protected:
    virtual void updateOverrideObject();

private:
    TextLabel* m_pTextLabel;
};

#endif // TEXTLABEL_H
