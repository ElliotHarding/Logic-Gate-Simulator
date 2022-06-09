#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QObject>
#include <QImage>
#include <QPainter>

class GameObject
{
public:
    GameObject(int width, int height, const char* iconLocation = nullptr);
    ~GameObject();

    void SetUserDisabled();

    virtual void UpdateGraphics(QPainter* painter);
    virtual bool UpdateClicked(int clickX, int clickY);

    //Positioning
    virtual void SetPosition(int x, int y);
    const QPoint GetPosition() const;
    virtual void OffsetPosition(int dX, int dY);

protected:

    QImage m_image;

    QRect m_layout;
    int m_width;
    int m_height;

    bool m_bUserDisabled = false;
};

class DragableGameObject : public GameObject
{
public:
    DragableGameObject(int width, int height, const char* iconLocation = nullptr);

    virtual bool UpdateDrag(int clickX, int clickY);
};

#endif // GAMEOBJECT_H
