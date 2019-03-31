#include "movingwidget.h"
#include <QPainter>
#include <QBrush>
#include "dlg_home.h"

MovingWidget::MovingWidget(DLG_Home *parent) :
    QWidget (parent)
{    
    m_pParent = parent;
}

MovingWidget::~MovingWidget()
{
    m_pParent = nullptr;
}
