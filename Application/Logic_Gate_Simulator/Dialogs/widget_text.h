#ifndef WIDGET_TEXT_H
#define WIDGET_TEXT_H

#include <QWidget>

namespace Ui {
class Widget_Text;
}

class Widget_Text : public QWidget
{
    Q_OBJECT

public:
    explicit Widget_Text(QString text, QWidget *parent = nullptr);
    ~Widget_Text();

private:
    Ui::Widget_Text *ui;
};

#endif // WIDGET_TEXT_H
