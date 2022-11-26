#ifndef WIDGET_HELPERPOPUP_H
#define WIDGET_HELPERPOPUP_H

#include <QWidget>
#include <QPropertyAnimation>

namespace Ui {
class Widget_HelperPopup;
}

namespace Settings
{
const int PopupWidth = 240;
const int PopupHeight = 65;
const int PopupDistance = 30;

const QColor CircleColor = Qt::red;
const int CircleWidth = 5;
const uint CircleAnimationTimeMs = 1000;
}

enum HelperTip
{
    HT_First,
    HT_SpawnAndGate,
    HT_Last
};

class DLG_Home;
class Widget_CircleTarget;

class Widget_HelperPopup : public QWidget
{
    Q_OBJECT

public:
    explicit Widget_HelperPopup(DLG_Home* pHome);
    ~Widget_HelperPopup();

    void popup(const QPoint& location, const QString& tipText, const bool& showCircle, const uint& circleDiameter);

private slots:
    void on_btn_close_clicked();
    void on_btn_next_clicked();
    void on_btn_previous_clicked();

private:
    Ui::Widget_HelperPopup *ui;
    DLG_Home* m_pHome;
    Widget_CircleTarget* m_pCircleTarget;
};

class Widget_CircleTarget : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(int circleWidth READ circleWidth WRITE setCircleWidth)

public:
    Widget_CircleTarget(DLG_Home* pHome);
    ~Widget_CircleTarget();

    void setLocation(const QPoint& location, const uint& circleDiameter);

    void hide();

    void setCircleWidth(int width);
    int circleWidth();

protected:
    void paintEvent(QPaintEvent* paintEvent) override;

    int m_circleWidth = Settings::CircleWidth;

    ///Animations
    QSequentialAnimationGroup* m_pWidthAnimationGroup;
    QPropertyAnimation* m_pWidthValueIncAnimation;
    QPropertyAnimation* m_pWidthValueDecAnimation;
};

#endif // WIDGET_HELPERPOPUP_H
