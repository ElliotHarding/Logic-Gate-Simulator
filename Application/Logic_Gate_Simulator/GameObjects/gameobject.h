#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QImage>
#include <QPainter>
#include <QMouseEvent>

class GameObject
{
public:
    GameObject(const int& x, const int& y, const uint& width, const uint& height, const char* pIconLocation = nullptr);

    virtual void setPosition(const int& x, const int& y);
    virtual QPoint position() const;

    virtual void draw(QPainter& painter);

    virtual GameObject* checkClicked(const int& x, const int& y);

    void setEnabled(const bool enabled);
    bool enabled() const;

protected:
    QRect m_geometry;
    bool m_bEnabled = true;

private:
    QImage m_image;
};

#endif // GAMEOBJECT_H
