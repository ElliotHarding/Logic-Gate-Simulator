/********************************************************************************
** Form generated from reading UI file 'widget_allgates.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_ALLGATES_H
#define UI_WIDGET_ALLGATES_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget_AllGates
{
public:
    QPushButton *btn_orGate;
    QPushButton *btn_recieverGate;
    QPushButton *btn_andGate;
    QPushButton *btn_notGate;
    QPushButton *btn_sourceGate;
    QPushButton *btn_timerGate;
    QPushButton *btn_inputOn;
    QPushButton *btn_inputOff;
    QPushButton *btn_GateTriAnd;
    QPushButton *btn_GateTriOr;
    QPushButton *btn_numberOutputGate;
    QFrame *line;
    QFrame *line_2;

    void setupUi(QWidget *Widget_AllGates)
    {
        if (Widget_AllGates->objectName().isEmpty())
            Widget_AllGates->setObjectName(QString::fromUtf8("Widget_AllGates"));
        Widget_AllGates->resize(140, 301);
        Widget_AllGates->setAutoFillBackground(false);
        Widget_AllGates->setStyleSheet(QString::fromUtf8(""));
        btn_orGate = new QPushButton(Widget_AllGates);
        btn_orGate->setObjectName(QString::fromUtf8("btn_orGate"));
        btn_orGate->setGeometry(QRect(-5, 0, 50, 40));
        btn_orGate->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-gate-or.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_orGate->setIcon(icon);
        btn_orGate->setIconSize(QSize(32, 32));
        btn_orGate->setFlat(true);
        btn_recieverGate = new QPushButton(Widget_AllGates);
        btn_recieverGate->setObjectName(QString::fromUtf8("btn_recieverGate"));
        btn_recieverGate->setGeometry(QRect(70, 90, 50, 40));
        btn_recieverGate->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-gate-input.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_recieverGate->setIcon(icon1);
        btn_recieverGate->setIconSize(QSize(32, 32));
        btn_recieverGate->setFlat(true);
        btn_andGate = new QPushButton(Widget_AllGates);
        btn_andGate->setObjectName(QString::fromUtf8("btn_andGate"));
        btn_andGate->setGeometry(QRect(95, 0, 50, 40));
        btn_andGate->setAutoFillBackground(false);
        btn_andGate->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-gate-and.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_andGate->setIcon(icon2);
        btn_andGate->setIconSize(QSize(32, 32));
        btn_andGate->setFlat(true);
        btn_notGate = new QPushButton(Widget_AllGates);
        btn_notGate->setObjectName(QString::fromUtf8("btn_notGate"));
        btn_notGate->setGeometry(QRect(45, 0, 50, 40));
        btn_notGate->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-gate-not.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_notGate->setIcon(icon3);
        btn_notGate->setIconSize(QSize(32, 32));
        btn_notGate->setFlat(true);
        btn_sourceGate = new QPushButton(Widget_AllGates);
        btn_sourceGate->setObjectName(QString::fromUtf8("btn_sourceGate"));
        btn_sourceGate->setGeometry(QRect(-5, 150, 50, 40));
        btn_sourceGate->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-gate-output.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_sourceGate->setIcon(icon4);
        btn_sourceGate->setIconSize(QSize(48, 48));
        btn_sourceGate->setFlat(true);
        btn_timerGate = new QPushButton(Widget_AllGates);
        btn_timerGate->setObjectName(QString::fromUtf8("btn_timerGate"));
        btn_timerGate->setGeometry(QRect(-5, 190, 50, 40));
        btn_timerGate->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-gate-timer.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_timerGate->setIcon(icon5);
        btn_timerGate->setIconSize(QSize(48, 48));
        btn_timerGate->setFlat(true);
        btn_inputOn = new QPushButton(Widget_AllGates);
        btn_inputOn->setObjectName(QString::fromUtf8("btn_inputOn"));
        btn_inputOn->setGeometry(QRect(45, 150, 50, 40));
        btn_inputOn->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-gate-input-on.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_inputOn->setIcon(icon6);
        btn_inputOn->setIconSize(QSize(48, 48));
        btn_inputOn->setFlat(true);
        btn_inputOff = new QPushButton(Widget_AllGates);
        btn_inputOff->setObjectName(QString::fromUtf8("btn_inputOff"));
        btn_inputOff->setGeometry(QRect(95, 150, 50, 40));
        btn_inputOff->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-gate-input-off.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_inputOff->setIcon(icon7);
        btn_inputOff->setIconSize(QSize(48, 48));
        btn_inputOff->setFlat(true);
        btn_GateTriAnd = new QPushButton(Widget_AllGates);
        btn_GateTriAnd->setObjectName(QString::fromUtf8("btn_GateTriAnd"));
        btn_GateTriAnd->setGeometry(QRect(45, 40, 50, 40));
        btn_GateTriAnd->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/Resources/Gates/gate-tri-and.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_GateTriAnd->setIcon(icon8);
        btn_GateTriAnd->setIconSize(QSize(32, 32));
        btn_GateTriAnd->setFlat(true);
        btn_GateTriOr = new QPushButton(Widget_AllGates);
        btn_GateTriOr->setObjectName(QString::fromUtf8("btn_GateTriOr"));
        btn_GateTriOr->setGeometry(QRect(0, 40, 50, 40));
        btn_GateTriOr->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-gate-tri-or.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_GateTriOr->setIcon(icon9);
        btn_GateTriOr->setIconSize(QSize(32, 32));
        btn_GateTriOr->setFlat(true);
        btn_numberOutputGate = new QPushButton(Widget_AllGates);
        btn_numberOutputGate->setObjectName(QString::fromUtf8("btn_numberOutputGate"));
        btn_numberOutputGate->setGeometry(QRect(10, 90, 50, 40));
        btn_numberOutputGate->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/Resources/Gates/gate-number-output.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_numberOutputGate->setIcon(icon10);
        btn_numberOutputGate->setIconSize(QSize(32, 32));
        btn_numberOutputGate->setFlat(true);
        line = new QFrame(Widget_AllGates);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(10, 80, 118, 3));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(Widget_AllGates);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(10, 140, 118, 3));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        retranslateUi(Widget_AllGates);

        QMetaObject::connectSlotsByName(Widget_AllGates);
    } // setupUi

    void retranslateUi(QWidget *Widget_AllGates)
    {
        Widget_AllGates->setWindowTitle(QApplication::translate("Widget_AllGates", "Form", nullptr));
        btn_orGate->setText(QString());
        btn_recieverGate->setText(QString());
        btn_andGate->setText(QString());
        btn_notGate->setText(QString());
        btn_sourceGate->setText(QString());
        btn_timerGate->setText(QString());
        btn_inputOn->setText(QString());
        btn_inputOff->setText(QString());
        btn_GateTriAnd->setText(QString());
        btn_GateTriOr->setText(QString());
        btn_numberOutputGate->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Widget_AllGates: public Ui_Widget_AllGates {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_ALLGATES_H
