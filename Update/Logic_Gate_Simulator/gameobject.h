#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QObject>
#include <QImage>
#include <QPainter>

class GameObject
{
public:
    GameObject(const char* iconLocation, int height, int width);
    virtual ~GameObject();

    virtual void UpdateGraphics(QPainter* painter);

    //Clicking
    virtual bool UpdateClicked(int clickX, int clickY);
    bool beingClicked = false;

    int posX;
    int posY;

protected:

    bool pointInside(int x, int y);

    int m_hitboxX = 0;
    int m_hitboxY = 0;

    int m_height;
    int m_width;

    QImage m_image;
};

class DragableGameObject : public GameObject
{
public:
    DragableGameObject(const char* iconLocation, int height, int width);

    virtual bool UpdateDrag(int clickX, int clickY);
};

#endif // GAMEOBJECT_H
