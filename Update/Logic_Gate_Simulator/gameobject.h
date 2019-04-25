#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QObject>
#include <QImage>
#include <QPainter>
#include <QMutex>

class GameObject
{
public:
    GameObject(int width, int height, const char* iconLocation = nullptr);
    virtual ~GameObject();

    virtual void UpdateGraphics(QPainter* painter);
    virtual bool UpdateClicked(int clickX, int clickY);

    //Positioning
    void setPosition(int x, int y);
    QPoint GetPosition();

protected:

    QMutex mutex_getPosition;
    QMutex mutex_setPosition;
    QMutex mutex_contains;

    QImage m_image;

    QRect m_layout;
    int m_width;
    int m_height;
};

class DragableGameObject : public GameObject
{
public:
    DragableGameObject(int width, int height, const char* iconLocation = nullptr);

    virtual bool UpdateDrag(int clickX, int clickY);
};

#endif // GAMEOBJECT_H
