/********************************************************************************
** Form generated from reading UI file 'widget_standard.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
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
        btn_notGate->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-gate-not.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_notGate->setIcon(icon);
        btn_notGate->setIconSize(QSize(32, 32));
        btn_notGate->setFlat(true);
        btn_andGate = new QPushButton(Widget_Standard);
        btn_andGate->setObjectName(QString::fromUtf8("btn_andGate"));
        btn_andGate->setGeometry(QRect(95, 10, 50, 40));
        btn_andGate->setAutoFillBackground(false);
        btn_andGate->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-gate-and.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_andGate->setIcon(icon1);
        btn_andGate->setIconSize(QSize(32, 32));
        btn_andGate->setFlat(true);
        btn_GateTriAnd = new QPushButton(Widget_Standard);
        btn_GateTriAnd->setObjectName(QString::fromUtf8("btn_GateTriAnd"));
        btn_GateTriAnd->setGeometry(QRect(45, 50, 50, 40));
        btn_GateTriAnd->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Resources/Gates/gate-tri-and.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_GateTriAnd->setIcon(icon2);
        btn_GateTriAnd->setIconSize(QSize(32, 32));
        btn_GateTriAnd->setFlat(true);
        btn_GateTriOr = new QPushButton(Widget_Standard);
        btn_GateTriOr->setObjectName(QString::fromUtf8("btn_GateTriOr"));
        btn_GateTriOr->setGeometry(QRect(-5, 50, 50, 40));
        btn_GateTriOr->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-gate-tri-or.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_GateTriOr->setIcon(icon3);
        btn_GateTriOr->setIconSize(QSize(32, 32));
        btn_GateTriOr->setFlat(true);
        btn_orGate = new QPushButton(Widget_Standard);
        btn_orGate->setObjectName(QString::fromUtf8("btn_orGate"));
        btn_orGate->setGeometry(QRect(-5, 10, 50, 40));
        btn_orGate->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-gate-or.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_orGate->setIcon(icon4);
        btn_orGate->setIconSize(QSize(32, 32));
        btn_orGate->setFlat(true);

        retranslateUi(Widget_Standard);

        QMetaObject::connectSlotsByName(Widget_Standard);
    } // setupUi

    void retranslateUi(QWidget *Widget_Standard)
    {
        Widget_Standard->setWindowTitle(QApplication::translate("Widget_Standard", "Form", nullptr));
        btn_notGate->setText(QString());
        btn_andGate->setText(QString());
        btn_GateTriAnd->setText(QString());
        btn_GateTriOr->setText(QString());
        btn_orGate->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Widget_Standard: public Ui_Widget_Standard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_STANDARD_H
