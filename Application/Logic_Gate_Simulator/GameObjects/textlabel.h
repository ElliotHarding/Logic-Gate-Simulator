#ifndef TEXTLABEL_H
#define TEXTLABEL_H

#include "gate.h"
#include "dlg_textedit.h"

class DLG_LabelGateEdit;
class TextLabel : public Gate
{
public:
    TextLabel();
    ~TextLabel();

    //Game Object overrides
    virtual void UpdateGraphics(QPainter* painter) override;
    virtual bool UpdateDrag(int clickX, int clickY) override;
    virtual void setPosition(int x, int y) override;
    virtual Gate* Clone() override;

    //Gate overrides
    virtual void AssignNewNodeIds() override {}//Todo : just use Gate::Assign
    virtual void UpdateOutput() override {}

    //Text label functions
    void Update(QFont font, QString string);

    QString GetString();
    QFont GetFont();

protected:
    QString m_string;
    QFont m_font;

    #define EDIT_ZONE_WIDTH 8
    #define EDIT_ZONE_HEIGHT 8
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
