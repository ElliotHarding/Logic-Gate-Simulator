#include "widget_helperpopup.h"
#include "ui_widget_helperpopup.h"
#include "dlg_home.h"

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
        m_pCircleTarget->setLocation(homeLocation + location, circleDiameter);
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
}

Widget_CircleTarget::~Widget_CircleTarget()
{
}

void Widget_CircleTarget::setLocation(const QPoint &location, const uint& circleDiameter)
{
    QRect geo(location.x() - circleDiameter/2, location.y() - circleDiameter/2, circleDiameter, circleDiameter);
    setGeometry(geo);
    show();
}

void Widget_CircleTarget::paintEvent(QPaintEvent *paintEvent)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::HighQualityAntialiasing, true);

    painter.setPen(QPen(Settings::CircleColor, Settings::CircleWidth));
    QRect drawRect = QRect(0, 0, geometry().width(), geometry().height());
    painter.drawEllipse(drawRect);
}
