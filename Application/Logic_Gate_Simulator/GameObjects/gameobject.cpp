#include "gameobject.h"

GameObject::GameObject(QWidget* pParent, int width, int height, const char* iconLocation) : QWidget(pParent)
{
    if(iconLocation != nullptr)
        m_image = QImage(iconLocation);

    //Todo - check settings position
    setGeometry(0, 0, width, height);
    show();
}

GameObject::~GameObject()
{
}

void GameObject::SetUserDisabled()
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
