#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QObject>
#include <QImage>
#include <QPainter>

class GameObject
{
public:
    GameObject(const char* iconLocation, int width, int height);
    virtual ~GameObject();

    virtual void UpdateGraphics(QPainter* painter);

    //Clicking
    virtual bool UpdateClicked(int clickX, int clickY);
    bool beingClicked = false;

    //Positioning
    void setPosition(int x, int y);
    QPoint GetPosition() {return QPoint(m_layout.x(),m_layout.y());}

protected:

    bool pointInside(int x, int y);    

    QImage m_image;

    QRect m_layout;
    int m_width;
    int m_height;
};

class DragableGameObject : public GameObject
{
public:
    DragableGameObject(const char* iconLocation, int width, int height);

    virtual bool UpdateDrag(int clickX, int clickY);
};

#endif // GAMEOBJECT_H
