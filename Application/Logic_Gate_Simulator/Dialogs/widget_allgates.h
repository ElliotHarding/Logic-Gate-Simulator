#ifndef WIDGET_ALLGATES_H
#define WIDGET_ALLGATES_H

#include "movingwidget.h"
#include "QPushButton"

namespace Ui {
class Widget_AllGates;
}

class DLG_Home;
class GateSlider;
class Widget_AllGates : public MovingWidget
{
    Q_OBJECT

public:
    explicit Widget_AllGates(DLG_Home* parent = nullptr, bool show = false, QPoint loc = QPoint(0,0));
    ~Widget_AllGates();

    void SetScrollPosition(float y);

private slots:
    void on_btn_andGate_clicked();
    void on_btn_notGate_clicked();
    void on_btn_orGate_clicked();
    void on_btn_recieverGate_clicked();
    void on_btn_sourceGate_clicked();
    void on_btn_timerGate_clicked();
    void on_btn_inputOn_clicked();
    void on_btn_inputOff_clicked();
    void on_btn_GateTriAnd_clicked();
    void on_btn_GateTriOr_clicked();
    void on_btn_numberOutputGate_clicked();
    void on_btn_GateEor_clicked();
    void on_btn_GateTriEor_clicked();

private:
    Ui::Widget_AllGates *ui;

    GateSlider* m_pGateSlider;

    struct WidgetAndPosition
    {
        QWidget* widget;
        QRect originalLayout;
    };
    std::vector<WidgetAndPosition> m_buttons;
};

#endif // WIDGET_ALLGATES_H
