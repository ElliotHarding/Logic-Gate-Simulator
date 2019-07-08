#ifndef TEXTLABEL_H
#define TEXTLABEL_H

#include "gate.h"
#include "dlg_textedit.h"

class TextLabel : public Gate
{
public:
    TextLabel();

    //Game Object overrides
    virtual void UpdateGraphics(QPainter* painter) override;
    virtual bool UpdateClicked(int clickX, int clickY) override;
    virtual void SetPosition(int x, int y) override;
    virtual Gate* Clone() override;

    //Gate overrides
    virtual void AssignNewNodeIds() override {}
    virtual void UpdateOutput() override {}

    //Text label functions
    void Update(QFont font, QString string, bool underlined);

    QString GetString();
    QFont GetFont();
    bool IsUnderlined();

protected:
    QString m_string;
    QFont m_font;
    bool m_bUnderlined;

    #define EDIT_ZONE_WIDTH 5
    #define EDIT_ZONE_HEIGHT 5
    QRect m_editClickZone;
};

class DLG_LabelGateEdit : public DLG_TextEdit
{
public:
    DLG_LabelGateEdit(TextLabel* textLabel);
    ~DLG_LabelGateEdit();

private:
    TextLabel* m_pTextLabel;
};

#endif // TEXTLABEL_H
