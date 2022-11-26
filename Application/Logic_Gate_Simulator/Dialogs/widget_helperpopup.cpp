#include "widget_helperpopup.h"
#include "ui_widget_helperpopup.h"
#include "dlg_home.h"

Widget_HelperPopup::Widget_HelperPopup(DLG_Home* pHome) :
    QWidget(pHome),
    ui(new Ui::Widget_HelperPopup),
    m_pHome(pHome)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    ui->pushButton->setAttribute(Qt::WA_TranslucentBackground, false);
}

Widget_HelperPopup::~Widget_HelperPopup()
{
    delete ui;
}

void Widget_HelperPopup::popup(const QPoint& location, const QString& tipText)
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

