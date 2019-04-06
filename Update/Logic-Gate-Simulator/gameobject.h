#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QObject>
#include <QIcon>

class GameObject : QObject
{
public:
    GameObject(char* iconLocation, int posX, int posY, int height, int width);

    virtual void UpdatePositions(int clickX, int clickY);
    int posX;
    int posY;

protected:
    int m_hitboxX = 0;
    int m_hitboxY = 0;

    int height;
    int width;

    QIcon m_icon;

    bool pointInside(int x, int y);
};

#endif // GAMEOBJECT_H
