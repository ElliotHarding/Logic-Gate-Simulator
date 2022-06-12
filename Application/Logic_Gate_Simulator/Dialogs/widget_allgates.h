#ifndef WIDGET_ALLGATES_H
#define WIDGET_ALLGATES_H

#include "movingwidget.h"
#include "QPushButton"
#include "QTimer"

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
    ~Widget_AllGates() override;

    void SetScrollPosition(const float& y);
    virtual void show() override;

protected:
    virtual void wheelEvent(QWheelEvent *event) override;

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
    void on_btn_labelGate_clicked();    
    void on_btn_norGate_clicked();
    void on_btn_nandGate_clicked();
    void on_btn_xorGate_clicked();

private:
    Ui::Widget_AllGates *ui;

    //Scrolling
    const int c_scrollSpeed = 10;
    const int c_scrollMax = 100;
    const int c_scrollMin = 0;
    unsigned const int c_scrollDistance = c_scrollMax - c_scrollMin;
    int m_scroll = 0;
};

#endif // WIDGET_ALLGATES_H
