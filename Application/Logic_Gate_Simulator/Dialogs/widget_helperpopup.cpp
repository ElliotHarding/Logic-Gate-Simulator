#include "widget_helperpopup.h"
#include "ui_widget_helperpopup.h"
#include "dlg_home.h"

#include <QSequentialAnimationGroup>
#include <QAbstractAnimation>

Widget_HelperPopup::Widget_HelperPopup(DLG_Home* pHome) :
    QWidget(pHome),
    ui(new Ui::Widget_HelperPopup),
    m_pHome(pHome),
    m_pCircleTarget(new Widget_CircleTarget(pHome))
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
}

Widget_HelperPopup::~Widget_HelperPopup()
{
    delete ui;
}

void Widget_HelperPopup::popup(const QPoint& location, const QString& tipText, const bool& showCircle, const uint& circleDiameter)
{
    const QPoint homeLocation = m_pHome->geometry().topLeft();
    if(location.x() < m_pHome->geometry().width() - Settings::PopupWidth * 2)
    {
        if(location.y() < Settings::PopupHeight * 2)
        {
            move(location + homeLocation + QPoint(Settings::PopupDistance, Settings::PopupDistance));
        }
        else
        {
            move(QPoint(location.x() + Settings::PopupDistance + homeLocation.x(), location.y() - Settings::PopupHeight - Settings::PopupDistance + homeLocation.y()));
        }
    }
    else
    {
        if(location.y() < Settings::PopupHeight * 2)
        {
            move(QPoint(location.x() - Settings::PopupWidth - Settings::PopupDistance + homeLocation.x(), location.y() + Settings::PopupDistance + homeLocation.y()));
        }
        else
        {
            move(QPoint(location.x() - Settings::PopupWidth - Settings::PopupDistance + homeLocation.x(), location.y() - Settings::PopupHeight - Settings::PopupDistance + homeLocation.y()));
        }
    }

    if(showCircle)
    {
        m_pCircleTarget->setLocation(location, circleDiameter);
    }
    else
    {
        m_pCircleTarget->hide();
    }

    ui->lbl_tipText->setText(tipText);
    show();
}

void Widget_HelperPopup::on_btn_close_clicked()
{
    hide();
}

void Widget_HelperPopup::on_btn_next_clicked()
{
    m_pHome->nextHelperTip();
}

void Widget_HelperPopup::on_btn_previous_clicked()
{
    m_pHome->previousHelperTip();
}

Widget_CircleTarget::Widget_CircleTarget(DLG_Home *pHome) : QWidget(pHome)
{
    raise();

    m_pWidthAnimationGroup = new QSequentialAnimationGroup(this);

    m_pWidthValueIncAnimation = new QPropertyAnimation(this, "circleWidth");
    m_pWidthValueIncAnimation->setDuration(Settings::CircleAnimationTimeMs);
    m_pWidthValueIncAnimation->setStartValue(Settings::CircleWidth - 3);
    m_pWidthValueIncAnimation->setEndValue(Settings::CircleWidth + 4);

    m_pWidthValueDecAnimation = new QPropertyAnimation(this, "circleWidth");
    m_pWidthValueDecAnimation->setDuration(Settings::CircleAnimationTimeMs);
    m_pWidthValueDecAnimation->setStartValue(Settings::CircleWidth + 4);
    m_pWidthValueDecAnimation->setEndValue(Settings::CircleWidth - 4);

    m_pWidthAnimationGroup->addAnimation(m_pWidthValueIncAnimation);
    m_pWidthAnimationGroup->addAnimation(m_pWidthValueDecAnimation);
}

Widget_CircleTarget::~Widget_CircleTarget()
{
    m_pWidthValueIncAnimation->stop();
    m_pWidthValueDecAnimation->stop();
    m_pWidthAnimationGroup->stop();
    delete m_pWidthValueDecAnimation;
    delete m_pWidthValueIncAnimation;
    delete m_pWidthAnimationGroup;
}

void Widget_CircleTarget::setLocation(const QPoint &location, const uint& circleDiameter)
{
    QRect geo(location.x() - circleDiameter/2, location.y() - circleDiameter/2, circleDiameter, circleDiameter);
    setGeometry(geo);
    show();
    raise();
    m_pWidthAnimationGroup->start();
}

void Widget_CircleTarget::hide()
{
    m_pWidthAnimationGroup->stop();
    QWidget::hide();
}

void Widget_CircleTarget::setCircleWidth(int width)
{
    m_circleWidth = width;
    update();

    if(width == Settings::CircleWidth - 4)
    {
        m_pWidthAnimationGroup->setLoopCount(m_pWidthAnimationGroup->loopCount() + 1);
    }
}

int Widget_CircleTarget::circleWidth()
{
    return m_circleWidth;
}

void Widget_CircleTarget::paintEvent(QPaintEvent *paintEvent)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::HighQualityAntialiasing, true);

    painter.setPen(QPen(Settings::CircleColor, m_circleWidth));
    QRect drawRect = QRect(geometry().width() / 4, geometry().height() / 4, geometry().width() / 2, geometry().height() / 2);
    painter.drawEllipse(drawRect);
}
