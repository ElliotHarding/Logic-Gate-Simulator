#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QObject>
#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QMouseEvent>

class GameObject
{
public:
    GameObject(const uint& x, const uint& y, const uint& width, const uint& height, const char* pIconLocation = nullptr);
    ~GameObject();

    virtual void setPosition(const int& x, const int& y);

    virtual void updateGraphics(QPainter* painter);

    virtual bool checkClicked(const int& x, const int& y);

    void setUserDisabled();

private:
    QImage m_image;

    QRect m_geometry;

    bool m_bUserDisabled = false;
};

#endif // GAMEOBJECT_H
