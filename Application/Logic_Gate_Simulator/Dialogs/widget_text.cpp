#include "widget_text.h"
#include "ui_widget_text.h"

Widget_Text::Widget_Text(QString text, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget_Text)
{
    ui->setupUi(this);
    ui->lbl_text->setText(text);

    setAutoFillBackground(true);
    QPalette pal;
    pal.setColor(QPalette::Background, Qt::white);
    setPalette(pal);
}

Widget_Text::~Widget_Text()
{
    delete ui;
}
