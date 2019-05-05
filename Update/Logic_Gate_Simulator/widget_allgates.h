#ifndef WIDGET_ALLGATES_H
#define WIDGET_ALLGATES_H

#include <QWidget>

namespace Ui {
class Widget_AllGates;
}

class DLG_Home;
class Widget_AllGates : public QWidget
{
    Q_OBJECT

public:
    explicit Widget_AllGates(DLG_Home* parent = nullptr);
    ~Widget_AllGates();

private slots:
    void on_btn_andGate_clicked();

    void on_btn_notGate_clicked();

    void on_btn_orGate_clicked();

    void on_btn_recieverGate_clicked();

    void on_btn_sourceGate_clicked();

private:
    Ui::Widget_AllGates *ui;
    DLG_Home* m_pParent;
};

#endif // WIDGET_ALLGATES_H
