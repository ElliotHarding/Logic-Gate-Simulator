#ifndef TEXTLABEL_H
#define TEXTLABEL_H

#include "gameobject.h"

class TextLabel : public DragableGameObject
{
public:
    TextLabel();

    //Game Object overrides
    virtual void UpdateGraphics(QPainter* painter) override;
    virtual GameObject* Clone() override;

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
