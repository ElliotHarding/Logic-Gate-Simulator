#include "gameobject.h"

GameObject::GameObject(const int& x, const int& y, const uint& width, const uint& height, const char* pIconLocation) :
    m_geometry(x - width/2, y - height/2, width, height)
{
    if(pIconLocation != nullptr)
        m_image = QImage(pIconLocation);
}

GameObject* GameObject::checkClicked(const QPoint& mouse)
{
    return m_geometry.contains(mouse) ? this : nullptr;
}

void GameObject::setPosition(const int& x, const int& y)
{
    m_geometry = QRect(x - m_geometry.width()/2, y - m_geometry.height()/2, m_geometry.width(), m_geometry.height());
}

QPoint GameObject::position() const
{
    return m_geometry.center();
}

void GameObject::draw(QPainter& painter)
{
    painter.drawImage(m_geometry, m_image);
}
