/********************************************************************************
** Form generated from reading UI file 'widget_inputgates.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_INPUTGATES_H
#define UI_WIDGET_INPUTGATES_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget_InputGates
{
public:
    QPushButton *btn_timerGate;
    QPushButton *btn_sourceGate;
    QPushButton *btn_inputOff;
    QPushButton *btn_inputOn;

    void setupUi(QWidget *Widget_InputGates)
    {
        if (Widget_InputGates->objectName().isEmpty())
            Widget_InputGates->setObjectName(QString::fromUtf8("Widget_InputGates"));
        Widget_InputGates->resize(140, 301);
        Widget_InputGates->setAutoFillBackground(false);
        Widget_InputGates->setStyleSheet(QString::fromUtf8(""));
        btn_timerGate = new QPushButton(Widget_InputGates);
        btn_timerGate->setObjectName(QString::fromUtf8("btn_timerGate"));
        btn_timerGate->setGeometry(QRect(-5, 50, 50, 40));
        btn_timerGate->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border:none;\n"
""));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-gate-timer.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_timerGate->setIcon(icon);
        btn_timerGate->setIconSize(QSize(48, 48));
        btn_timerGate->setAutoDefault(true);
        btn_timerGate->setFlat(true);
        btn_sourceGate = new QPushButton(Widget_InputGates);
        btn_sourceGate->setObjectName(QString::fromUtf8("btn_sourceGate"));
        btn_sourceGate->setGeometry(QRect(-5, 10, 50, 40));
        btn_sourceGate->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border:none;\n"
""));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-gate-output.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_sourceGate->setIcon(icon1);
        btn_sourceGate->setIconSize(QSize(48, 48));
        btn_sourceGate->setAutoDefault(true);
        btn_sourceGate->setFlat(true);
        btn_inputOff = new QPushButton(Widget_InputGates);
        btn_inputOff->setObjectName(QString::fromUtf8("btn_inputOff"));
        btn_inputOff->setGeometry(QRect(95, 10, 50, 40));
        btn_inputOff->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border:none;\n"
""));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-gate-input-off.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_inputOff->setIcon(icon2);
        btn_inputOff->setIconSize(QSize(48, 48));
        btn_inputOff->setAutoDefault(true);
        btn_inputOff->setFlat(true);
        btn_inputOn = new QPushButton(Widget_InputGates);
        btn_inputOn->setObjectName(QString::fromUtf8("btn_inputOn"));
        btn_inputOn->setGeometry(QRect(45, 10, 50, 40));
        btn_inputOn->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border:none;\n"
""));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-gate-input-on.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_inputOn->setIcon(icon3);
        btn_inputOn->setIconSize(QSize(48, 48));
        btn_inputOn->setAutoDefault(true);
        btn_inputOn->setFlat(true);

        retranslateUi(Widget_InputGates);

        QMetaObject::connectSlotsByName(Widget_InputGates);
    } // setupUi

    void retranslateUi(QWidget *Widget_InputGates)
    {
        Widget_InputGates->setWindowTitle(QCoreApplication::translate("Widget_InputGates", "Form", nullptr));
        btn_timerGate->setText(QString());
        btn_sourceGate->setText(QString());
        btn_inputOff->setText(QString());
        btn_inputOn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Widget_InputGates: public Ui_Widget_InputGates {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_INPUTGATES_H
