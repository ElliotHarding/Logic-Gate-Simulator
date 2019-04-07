#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QObject>
#include <QIcon>

class GameObject : QObject
{
public:
    GameObject(const char* iconLocation, int height, int width);

    //Clicking
    virtual bool UpdateClicked(int clickX, int clickY);
    bool beingClicked = false;

    int posX;
    int posY;

protected:

    bool pointInside(int x, int y);

    int m_hitboxX = 0;
    int m_hitboxY = 0;

    int height;
    int width;

    QIcon m_icon;
};

class DragableGameObject : public GameObject
{
public:
    DragableGameObject(const char* iconLocation, int height, int width);

    virtual void UpdateDrag(int clickX, int clickY);
};

#endif // GAMEOBJECT_H
