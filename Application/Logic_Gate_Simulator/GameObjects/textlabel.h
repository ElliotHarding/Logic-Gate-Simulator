#ifndef TEXTLABEL_H
#define TEXTLABEL_H

#include "gate.h"

class TextLabel : public Gate
{
public:
    TextLabel();

    //Game Object overrides
    virtual void UpdateGraphics(QPainter* painter) override;
    virtual Gate* Clone() override;

    //Gate overrides
    virtual void AssignNewNodeIds() override {}
    virtual void UpdateOutput() override {}

    //Text label functions
    void Update(QFont font, QString string, bool underlined);
    void UpdateString(QString string);
    void UpdateFont(QFont font);
    void UpdateUnderlined(bool isUnderlined);

protected:
    QString m_string;
    QFont m_font;
    bool m_bUnderlined;
};

#endif // TEXTLABEL_H
