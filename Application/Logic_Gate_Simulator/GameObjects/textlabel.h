#ifndef TEXTLABEL_H
#define TEXTLABEL_H

#include "gate.h"
#include "dlg_textedit.h"

class DLG_LabelGateEdit;
class TextLabel : public Gate
{
public:
    TextLabel(const int &x, const int &y);
    ~TextLabel();

    //Game Object overrides
    virtual void draw(QPainter& painter) override;
    virtual GameObject* checkClicked(const QPoint& mouse) override;
    virtual void setPosition(const int& x, const int& y) override;
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
    QRect m_editClickZone;
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
