/********************************************************************************
** Form generated from reading UI file 'widget_advanced.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_ADVANCED_H
#define UI_WIDGET_ADVANCED_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget_Advanced
{
public:
    QPushButton *btn_recieverGate;
    QPushButton *btn_numberOutputGate;
    QPushButton *btn_fpgaGate;
    QPushButton *btn_labelGate;

    void setupUi(QWidget *Widget_Advanced)
    {
        if (Widget_Advanced->objectName().isEmpty())
            Widget_Advanced->setObjectName(QString::fromUtf8("Widget_Advanced"));
        Widget_Advanced->resize(140, 301);
        Widget_Advanced->setAutoFillBackground(false);
        Widget_Advanced->setStyleSheet(QString::fromUtf8(""));
        btn_recieverGate = new QPushButton(Widget_Advanced);
        btn_recieverGate->setObjectName(QString::fromUtf8("btn_recieverGate"));
        btn_recieverGate->setGeometry(QRect(80, 10, 50, 40));
        btn_recieverGate->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border:none;\n"
""));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-gate-input.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_recieverGate->setIcon(icon);
        btn_recieverGate->setIconSize(QSize(32, 32));
        btn_recieverGate->setAutoDefault(true);
        btn_recieverGate->setFlat(true);
        btn_numberOutputGate = new QPushButton(Widget_Advanced);
        btn_numberOutputGate->setObjectName(QString::fromUtf8("btn_numberOutputGate"));
        btn_numberOutputGate->setGeometry(QRect(10, 10, 50, 40));
        btn_numberOutputGate->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border:none;\n"
""));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Resources/Gates/gate-number-output.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_numberOutputGate->setIcon(icon1);
        btn_numberOutputGate->setIconSize(QSize(32, 32));
        btn_numberOutputGate->setAutoDefault(true);
        btn_numberOutputGate->setFlat(true);
        btn_fpgaGate = new QPushButton(Widget_Advanced);
        btn_fpgaGate->setObjectName(QString::fromUtf8("btn_fpgaGate"));
        btn_fpgaGate->setGeometry(QRect(40, 240, 50, 40));
        btn_fpgaGate->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        btn_fpgaGate->setIconSize(QSize(32, 32));
        btn_fpgaGate->setFlat(true);
        btn_labelGate = new QPushButton(Widget_Advanced);
        btn_labelGate->setObjectName(QString::fromUtf8("btn_labelGate"));
        btn_labelGate->setGeometry(QRect(10, 60, 50, 40));
        QFont font;
        font.setPointSize(11);
        font.setUnderline(false);
        btn_labelGate->setFont(font);
        btn_labelGate->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border:none;\n"
""));
        btn_labelGate->setIconSize(QSize(32, 32));
        btn_labelGate->setAutoDefault(true);
        btn_labelGate->setFlat(true);

        retranslateUi(Widget_Advanced);

        QMetaObject::connectSlotsByName(Widget_Advanced);
    } // setupUi

    void retranslateUi(QWidget *Widget_Advanced)
    {
        Widget_Advanced->setWindowTitle(QCoreApplication::translate("Widget_Advanced", "Form", nullptr));
        btn_recieverGate->setText(QString());
        btn_numberOutputGate->setText(QString());
        btn_fpgaGate->setText(QCoreApplication::translate("Widget_Advanced", "test", nullptr));
        btn_labelGate->setText(QCoreApplication::translate("Widget_Advanced", "Label", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget_Advanced: public Ui_Widget_Advanced {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_ADVANCED_H
