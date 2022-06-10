#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QImage>
#include <QPainter>
#include <QMouseEvent>

class GameObject
{
public:
    GameObject(const int& x, const int& y, const uint& width, const uint& height, const char* pIconLocation = nullptr);

    ///Position
    virtual void setPosition(const int& x, const int& y);
    virtual QPoint position() const;

    ///Enabled
    void setEnabled(const bool enabled);
    bool enabled() const;

    virtual void draw(QPainter& painter);

    virtual GameObject* checkClicked(const int& x, const int& y);

protected:
    QRect m_geometry;
    bool m_bEnabled = true;

private:
    QImage m_image;
};

#endif // GAMEOBJECT_H
