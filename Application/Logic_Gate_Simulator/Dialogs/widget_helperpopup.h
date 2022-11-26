#ifndef WIDGET_HELPERPOPUP_H
#define WIDGET_HELPERPOPUP_H

#include <QWidget>

namespace Ui {
class Widget_HelperPopup;
}

class Widget_HelperPopup : public QWidget
{
    Q_OBJECT

public:
    explicit Widget_HelperPopup(QWidget *parent = nullptr);
    ~Widget_HelperPopup();

private slots:
    void on_btn_close_clicked();

    void on_btn_next_clicked();

    void on_btn_previous_clicked();

private:
    Ui::Widget_HelperPopup *ui;
};

#endif // WIDGET_HELPERPOPUP_H
