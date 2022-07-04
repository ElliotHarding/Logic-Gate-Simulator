#ifndef TEXTLABEL_H
#define TEXTLABEL_H

#include "gate.h"
#include "dlg_textedit.h"

namespace Settings
{
const QString GateTextLabelTextTag = "Text";
}

class TextLabel : public Gate
{
public:
    TextLabel(const int& x = 0, const int& y = 0, const QString& text = "Label");
    ~TextLabel();

    //Game Object overrides
    virtual void draw(QPainter& painter) override;
    virtual void SaveData(QDomDocument& storage, QDomElement& parentElement) override;
    virtual Gate* Clone() override;

    //Gate overrides
    virtual void UpdateOutput() override {}

    //Text label functions
    void Update(const QFont& font, const QString& string);

    QString GetString();
    QFont GetFont();

protected:
    QString m_string;
    QFont m_font;
};

class DLG_LabelGateEdit : public DLG_TextEdit
{
public:
    DLG_LabelGateEdit();
    ~DLG_LabelGateEdit();

    void EditTextLabel(TextLabel* textLabel);

protected:
    virtual void UpdateOverrideObject();

private:
    TextLabel* m_pTextLabel;
};

#endif // TEXTLABEL_H
