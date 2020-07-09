#include "movingwidget.h"
#include <QPainter>
#include <QBrush>
#include "dlg_home.h"

MovingWidget::MovingWidget(DLG_Home *parent, bool setShow, QPoint loc) :
    QWidget (parent)
{    
    m_pParent = parent;

    if (!setShow)
        hide();

    move(loc);
}

MovingWidget::~MovingWidget()
{
    m_pParent = nullptr;
}
