/********************************************************************************
** Form generated from reading UI file 'widget_text.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_TEXT_H
#define UI_WIDGET_TEXT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget_Text
{
public:
    QLabel *lbl_text;

    void setupUi(QWidget *Widget_Text)
    {
        if (Widget_Text->objectName().isEmpty())
            Widget_Text->setObjectName(QString::fromUtf8("Widget_Text"));
        Widget_Text->resize(200, 70);
        lbl_text = new QLabel(Widget_Text);
        lbl_text->setObjectName(QString::fromUtf8("lbl_text"));
        lbl_text->setGeometry(QRect(10, 10, 181, 51));
        lbl_text->setAlignment(Qt::AlignCenter);

        retranslateUi(Widget_Text);

        QMetaObject::connectSlotsByName(Widget_Text);
    } // setupUi

    void retranslateUi(QWidget *Widget_Text)
    {
        Widget_Text->setWindowTitle(QCoreApplication::translate("Widget_Text", "Form", nullptr));
        lbl_text->setText(QCoreApplication::translate("Widget_Text", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget_Text: public Ui_Widget_Text {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_TEXT_H
