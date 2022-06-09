#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QImage>
#include <QPainter>
#include <QMouseEvent>

class GameObject
{
public:
    GameObject(const uint& x, const uint& y, const uint& width, const uint& height, const char* pIconLocation = nullptr);

    virtual void setPosition(const int& x, const int& y);

    virtual void draw(QPainter& painter);

    virtual bool checkClicked(const int& x, const int& y);

    void setUserDisabled();

protected:
    QRect m_geometry;

    bool m_bEnabled = false;

private:
    QImage m_image;
};

#endif // GAMEOBJECT_H
