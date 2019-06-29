#include "gameobject.h"

GameObject::GameObject(int width, int height, const char* iconLocation)
{
    if(iconLocation != nullptr)
        m_image = QImage(iconLocation);
    m_width = width;
    m_height = height;
    SetPosition(0,0);
}

GameObject::~GameObject()
{
}

void GameObject::UpdateGraphics(QPainter *painter)
{
    painter->drawImage(m_layout,m_image);
}

bool GameObject::UpdateClicked(int clickX, int clickY)
{
    return m_layout.contains(QPoint(clickX,clickY));
}

void GameObject::SetPosition(int x, int y)
{
   m_layout.setLeft(x - m_width/2);
   m_layout.setTop(y - m_height/2);
   m_layout.setRight(x + m_width/2);
   m_layout.setBottom(y + m_height/2);
}

const QPoint GameObject::GetPosition() const
{
    return QPoint(m_layout.center().x(), m_layout.center().y());
}

void GameObject::OffsetPosition(int dx, int dy)
{
    SetPosition(m_layout.center().x() + dx, m_layout.center().y() + dy);
}



//
//          DragableGameObject
//

DragableGameObject::DragableGameObject(int height, int width, const char *iconLocation) :
    GameObject::GameObject (height, width, iconLocation)
{
}

bool DragableGameObject::UpdateDrag(int clickX, int clickY)
{
    //Need to specify GameObject::UpdateClicked because overriding function GateToggle::UpdateClicked
    //Causes its output state to toggle (and we dont want it toggling on and off while dragging it)
    if(GameObject::UpdateClicked(clickX, clickY))
    {
        SetPosition(clickX,clickY);
        return true;
    }
    return false;
}
