/********************************************************************************
** Form generated from reading UI file 'widget_standard.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_STANDARD_H
#define UI_WIDGET_STANDARD_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget_Standard
{
public:
    QPushButton *btn_notGate;
    QPushButton *btn_andGate;
    QPushButton *btn_GateTriAnd;
    QPushButton *btn_GateTriOr;
    QPushButton *btn_orGate;
    QPushButton *btn_GateEor;
    QPushButton *btn_GateTriEor;

    void setupUi(QWidget *Widget_Standard)
    {
        if (Widget_Standard->objectName().isEmpty())
            Widget_Standard->setObjectName(QString::fromUtf8("Widget_Standard"));
        Widget_Standard->resize(140, 301);
        Widget_Standard->setAutoFillBackground(false);
        Widget_Standard->setStyleSheet(QString::fromUtf8(""));
        btn_notGate = new QPushButton(Widget_Standard);
        btn_notGate->setObjectName(QString::fromUtf8("btn_notGate"));
        btn_notGate->setGeometry(QRect(45, 10, 50, 40));
        btn_notGate->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border:none;\n"
""));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-gate-not.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_notGate->setIcon(icon);
        btn_notGate->setIconSize(QSize(32, 32));
        btn_notGate->setAutoDefault(true);
        btn_notGate->setFlat(true);
        btn_andGate = new QPushButton(Widget_Standard);
        btn_andGate->setObjectName(QString::fromUtf8("btn_andGate"));
        btn_andGate->setGeometry(QRect(90, 10, 50, 40));
        btn_andGate->setAutoFillBackground(false);
        btn_andGate->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border:none;\n"
""));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-gate-and.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_andGate->setIcon(icon1);
        btn_andGate->setIconSize(QSize(32, 32));
        btn_andGate->setAutoDefault(true);
        btn_andGate->setFlat(true);
        btn_GateTriAnd = new QPushButton(Widget_Standard);
        btn_GateTriAnd->setObjectName(QString::fromUtf8("btn_GateTriAnd"));
        btn_GateTriAnd->setGeometry(QRect(45, 50, 50, 40));
        btn_GateTriAnd->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border:none;\n"
""));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Resources/Gates/gate-tri-and.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_GateTriAnd->setIcon(icon2);
        btn_GateTriAnd->setIconSize(QSize(32, 32));
        btn_GateTriAnd->setAutoDefault(true);
        btn_GateTriAnd->setFlat(true);
        btn_GateTriOr = new QPushButton(Widget_Standard);
        btn_GateTriOr->setObjectName(QString::fromUtf8("btn_GateTriOr"));
        btn_GateTriOr->setGeometry(QRect(0, 50, 50, 40));
        btn_GateTriOr->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border:none;\n"
""));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-gate-tri-or.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_GateTriOr->setIcon(icon3);
        btn_GateTriOr->setIconSize(QSize(32, 32));
        btn_GateTriOr->setAutoDefault(true);
        btn_GateTriOr->setFlat(true);
        btn_orGate = new QPushButton(Widget_Standard);
        btn_orGate->setObjectName(QString::fromUtf8("btn_orGate"));
        btn_orGate->setGeometry(QRect(0, 10, 50, 40));
        btn_orGate->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border:none;\n"
""));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-gate-or.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_orGate->setIcon(icon4);
        btn_orGate->setIconSize(QSize(32, 32));
        btn_orGate->setAutoDefault(true);
        btn_orGate->setFlat(true);
        btn_GateEor = new QPushButton(Widget_Standard);
        btn_GateEor->setObjectName(QString::fromUtf8("btn_GateEor"));
        btn_GateEor->setGeometry(QRect(90, 50, 50, 40));
        btn_GateEor->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border:none;\n"
""));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Resources/Gates/gate-eor.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_GateEor->setIcon(icon5);
        btn_GateEor->setIconSize(QSize(32, 32));
        btn_GateEor->setAutoDefault(true);
        btn_GateEor->setFlat(true);
        btn_GateTriEor = new QPushButton(Widget_Standard);
        btn_GateTriEor->setObjectName(QString::fromUtf8("btn_GateTriEor"));
        btn_GateTriEor->setGeometry(QRect(0, 90, 50, 40));
        btn_GateTriEor->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border:none;\n"
""));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/Resources/Gates/gate-tri-eor.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_GateTriEor->setIcon(icon6);
        btn_GateTriEor->setIconSize(QSize(32, 32));
        btn_GateTriEor->setAutoDefault(true);
        btn_GateTriEor->setFlat(true);

        retranslateUi(Widget_Standard);

        QMetaObject::connectSlotsByName(Widget_Standard);
    } // setupUi

    void retranslateUi(QWidget *Widget_Standard)
    {
        Widget_Standard->setWindowTitle(QCoreApplication::translate("Widget_Standard", "Form", nullptr));
        btn_notGate->setText(QString());
        btn_andGate->setText(QString());
        btn_GateTriAnd->setText(QString());
        btn_GateTriOr->setText(QString());
        btn_orGate->setText(QString());
        btn_GateEor->setText(QString());
        btn_GateTriEor->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Widget_Standard: public Ui_Widget_Standard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_STANDARD_H
