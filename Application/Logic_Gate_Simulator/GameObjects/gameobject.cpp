#include "gameobject.h"

GameObject::GameObject(QWidget* pParent, const uint& x, const uint& y, const uint& width, const uint& height, const char* pIconLocation) : QWidget(pParent)
{
    if(pIconLocation != nullptr)
        m_image = QImage(pIconLocation);

    setGeometry(x, y, width, height);
    show();
}

GameObject::~GameObject()
{
}

void GameObject::setPosition(const uint& x, const uint& y)
{
    setGeometry(x - geometry().width()/2, y - geometry().height()/2, geometry().width(), geometry().height());
}

void GameObject::setUserDisabled()
{
    m_bUserDisabled = true;
}

void GameObject::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.drawImage(QRect(0, 0, geometry().width(), geometry().height()), m_image);
}

void GameObject::mousePressEvent(QMouseEvent*)
{
    if(!m_bUserDisabled)
    {
        emit onClicked(this);
    }
}

void GameObject::mouseReleaseEvent(QMouseEvent*)
{
    if(!m_bUserDisabled)
    {
        emit onReleased(this);
    }
}
