/********************************************************************************
** Form generated from reading UI file 'widget_allgates.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
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
    QFrame *ln_1;
    QFrame *ln_2;
    QPushButton *btn_GateEor;
    QPushButton *btn_GateTriEor;
    QWidget *scrollSliderLayout;
    QPushButton *btn_labelGate;
    QFrame *ln_3;
    QPushButton *btn_nandGate;
    QPushButton *btn_norGate;
    QPushButton *btn_xorGate;

    void setupUi(QWidget *Widget_AllGates)
    {
        if (Widget_AllGates->objectName().isEmpty())
            Widget_AllGates->setObjectName(QString::fromUtf8("Widget_AllGates"));
        Widget_AllGates->resize(140, 301);
        Widget_AllGates->setMouseTracking(true);
        Widget_AllGates->setAutoFillBackground(false);
        Widget_AllGates->setStyleSheet(QString::fromUtf8(""));
        btn_orGate = new QPushButton(Widget_AllGates);
        btn_orGate->setObjectName(QString::fromUtf8("btn_orGate"));
        btn_orGate->setGeometry(QRect(5, 15, 50, 40));
        btn_orGate->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border:none;\n"
""));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-gate-or.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_orGate->setIcon(icon);
        btn_orGate->setIconSize(QSize(32, 32));
        btn_orGate->setAutoDefault(true);
        btn_orGate->setFlat(true);
        btn_recieverGate = new QPushButton(Widget_AllGates);
        btn_recieverGate->setObjectName(QString::fromUtf8("btn_recieverGate"));
        btn_recieverGate->setGeometry(QRect(65, 240, 50, 40));
        btn_recieverGate->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border:none;\n"
""));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-gate-input.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_recieverGate->setIcon(icon1);
        btn_recieverGate->setIconSize(QSize(32, 32));
        btn_recieverGate->setAutoDefault(true);
        btn_recieverGate->setFlat(true);
        btn_andGate = new QPushButton(Widget_AllGates);
        btn_andGate->setObjectName(QString::fromUtf8("btn_andGate"));
        btn_andGate->setGeometry(QRect(5, 135, 50, 40));
        btn_andGate->setAutoFillBackground(false);
        btn_andGate->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border:none;\n"
""));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-gate-and.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_andGate->setIcon(icon2);
        btn_andGate->setIconSize(QSize(32, 32));
        btn_andGate->setAutoDefault(true);
        btn_andGate->setFlat(true);
        btn_notGate = new QPushButton(Widget_AllGates);
        btn_notGate->setObjectName(QString::fromUtf8("btn_notGate"));
        btn_notGate->setGeometry(QRect(65, 15, 50, 40));
        btn_notGate->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border:none;"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-gate-not.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_notGate->setIcon(icon3);
        btn_notGate->setIconSize(QSize(32, 32));
        btn_notGate->setAutoDefault(true);
        btn_notGate->setFlat(true);
        btn_sourceGate = new QPushButton(Widget_AllGates);
        btn_sourceGate->setObjectName(QString::fromUtf8("btn_sourceGate"));
        btn_sourceGate->setGeometry(QRect(5, 335, 50, 40));
        btn_sourceGate->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border:none;\n"
""));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-gate-output.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_sourceGate->setIcon(icon4);
        btn_sourceGate->setIconSize(QSize(48, 48));
        btn_sourceGate->setAutoDefault(true);
        btn_sourceGate->setFlat(true);
        btn_timerGate = new QPushButton(Widget_AllGates);
        btn_timerGate->setObjectName(QString::fromUtf8("btn_timerGate"));
        btn_timerGate->setGeometry(QRect(5, 370, 50, 40));
        btn_timerGate->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border:none;\n"
""));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-gate-timer.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_timerGate->setIcon(icon5);
        btn_timerGate->setIconSize(QSize(48, 48));
        btn_timerGate->setAutoDefault(true);
        btn_timerGate->setFlat(true);
        btn_inputOn = new QPushButton(Widget_AllGates);
        btn_inputOn->setObjectName(QString::fromUtf8("btn_inputOn"));
        btn_inputOn->setGeometry(QRect(65, 335, 50, 40));
        btn_inputOn->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border:none;\n"
""));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-gate-input-on.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_inputOn->setIcon(icon6);
        btn_inputOn->setIconSize(QSize(48, 48));
        btn_inputOn->setAutoDefault(true);
        btn_inputOn->setFlat(true);
        btn_inputOff = new QPushButton(Widget_AllGates);
        btn_inputOff->setObjectName(QString::fromUtf8("btn_inputOff"));
        btn_inputOff->setGeometry(QRect(65, 370, 50, 40));
        btn_inputOff->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border:none;\n"
""));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-gate-input-off.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_inputOff->setIcon(icon7);
        btn_inputOff->setIconSize(QSize(48, 48));
        btn_inputOff->setAutoDefault(true);
        btn_inputOff->setFlat(true);
        btn_GateTriAnd = new QPushButton(Widget_AllGates);
        btn_GateTriAnd->setObjectName(QString::fromUtf8("btn_GateTriAnd"));
        btn_GateTriAnd->setGeometry(QRect(65, 55, 50, 40));
        btn_GateTriAnd->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border:none;\n"
""));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/Resources/Gates/gate-tri-and.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_GateTriAnd->setIcon(icon8);
        btn_GateTriAnd->setIconSize(QSize(32, 32));
        btn_GateTriAnd->setAutoDefault(true);
        btn_GateTriAnd->setFlat(true);
        btn_GateTriOr = new QPushButton(Widget_AllGates);
        btn_GateTriOr->setObjectName(QString::fromUtf8("btn_GateTriOr"));
        btn_GateTriOr->setGeometry(QRect(5, 55, 50, 40));
        btn_GateTriOr->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border:none;\n"
""));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-gate-tri-or.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_GateTriOr->setIcon(icon9);
        btn_GateTriOr->setIconSize(QSize(32, 32));
        btn_GateTriOr->setAutoDefault(true);
        btn_GateTriOr->setFlat(true);
        btn_numberOutputGate = new QPushButton(Widget_AllGates);
        btn_numberOutputGate->setObjectName(QString::fromUtf8("btn_numberOutputGate"));
        btn_numberOutputGate->setGeometry(QRect(5, 240, 50, 40));
        btn_numberOutputGate->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border:none;\n"
""));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/Resources/Gates/gate-number-output.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_numberOutputGate->setIcon(icon10);
        btn_numberOutputGate->setIconSize(QSize(32, 32));
        btn_numberOutputGate->setAutoDefault(true);
        btn_numberOutputGate->setFlat(true);
        ln_1 = new QFrame(Widget_AllGates);
        ln_1->setObjectName(QString::fromUtf8("ln_1"));
        ln_1->setGeometry(QRect(5, 225, 101, 16));
        ln_1->setFrameShape(QFrame::HLine);
        ln_1->setFrameShadow(QFrame::Sunken);
        ln_2 = new QFrame(Widget_AllGates);
        ln_2->setObjectName(QString::fromUtf8("ln_2"));
        ln_2->setGeometry(QRect(5, 320, 101, 16));
        ln_2->setFrameShape(QFrame::HLine);
        ln_2->setFrameShadow(QFrame::Sunken);
        btn_GateEor = new QPushButton(Widget_AllGates);
        btn_GateEor->setObjectName(QString::fromUtf8("btn_GateEor"));
        btn_GateEor->setGeometry(QRect(65, 95, 50, 40));
        btn_GateEor->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border:none;\n"
""));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/Resources/Gates/gate-eor.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_GateEor->setIcon(icon11);
        btn_GateEor->setIconSize(QSize(32, 32));
        btn_GateEor->setAutoDefault(true);
        btn_GateEor->setFlat(true);
        btn_GateTriEor = new QPushButton(Widget_AllGates);
        btn_GateTriEor->setObjectName(QString::fromUtf8("btn_GateTriEor"));
        btn_GateTriEor->setGeometry(QRect(5, 95, 50, 40));
        btn_GateTriEor->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border:none;\n"
""));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/Resources/Gates/gate-tri-eor.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_GateTriEor->setIcon(icon12);
        btn_GateTriEor->setIconSize(QSize(32, 32));
        btn_GateTriEor->setAutoDefault(true);
        btn_GateTriEor->setFlat(true);
        scrollSliderLayout = new QWidget(Widget_AllGates);
        scrollSliderLayout->setObjectName(QString::fromUtf8("scrollSliderLayout"));
        scrollSliderLayout->setGeometry(QRect(120, 5, 21, 290));
        scrollSliderLayout->setMouseTracking(true);
        btn_labelGate = new QPushButton(Widget_AllGates);
        btn_labelGate->setObjectName(QString::fromUtf8("btn_labelGate"));
        btn_labelGate->setGeometry(QRect(5, 280, 50, 40));
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
        ln_3 = new QFrame(Widget_AllGates);
        ln_3->setObjectName(QString::fromUtf8("ln_3"));
        ln_3->setGeometry(QRect(5, 410, 101, 16));
        ln_3->setFrameShape(QFrame::HLine);
        ln_3->setFrameShadow(QFrame::Sunken);
        btn_nandGate = new QPushButton(Widget_AllGates);
        btn_nandGate->setObjectName(QString::fromUtf8("btn_nandGate"));
        btn_nandGate->setGeometry(QRect(5, 175, 50, 40));
        btn_nandGate->setAutoFillBackground(false);
        btn_nandGate->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border:none;\n"
""));
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/Resources/Gates/gate-nand.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_nandGate->setIcon(icon13);
        btn_nandGate->setIconSize(QSize(32, 32));
        btn_nandGate->setAutoDefault(true);
        btn_nandGate->setFlat(true);
        btn_norGate = new QPushButton(Widget_AllGates);
        btn_norGate->setObjectName(QString::fromUtf8("btn_norGate"));
        btn_norGate->setGeometry(QRect(65, 135, 50, 40));
        btn_norGate->setAutoFillBackground(false);
        btn_norGate->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border:none;\n"
""));
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/Resources/Gates/gate-nor.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_norGate->setIcon(icon14);
        btn_norGate->setIconSize(QSize(32, 32));
        btn_norGate->setAutoDefault(true);
        btn_norGate->setFlat(true);
        btn_xorGate = new QPushButton(Widget_AllGates);
        btn_xorGate->setObjectName(QString::fromUtf8("btn_xorGate"));
        btn_xorGate->setGeometry(QRect(65, 175, 50, 40));
        btn_xorGate->setAutoFillBackground(false);
        btn_xorGate->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border:none;\n"
""));
        QIcon icon15;
        icon15.addFile(QString::fromUtf8(":/Resources/Gates/gate-neor.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_xorGate->setIcon(icon15);
        btn_xorGate->setIconSize(QSize(32, 32));
        btn_xorGate->setAutoDefault(true);
        btn_xorGate->setFlat(true);
        scrollSliderLayout->raise();
        btn_orGate->raise();
        btn_recieverGate->raise();
        btn_andGate->raise();
        btn_notGate->raise();
        btn_sourceGate->raise();
        btn_timerGate->raise();
        btn_inputOn->raise();
        btn_inputOff->raise();
        btn_GateTriAnd->raise();
        btn_GateTriOr->raise();
        btn_numberOutputGate->raise();
        ln_1->raise();
        ln_2->raise();
        btn_GateEor->raise();
        btn_GateTriEor->raise();
        btn_labelGate->raise();
        ln_3->raise();
        btn_nandGate->raise();
        btn_norGate->raise();
        btn_xorGate->raise();

        retranslateUi(Widget_AllGates);

        btn_notGate->setDefault(false);


        QMetaObject::connectSlotsByName(Widget_AllGates);
    } // setupUi

    void retranslateUi(QWidget *Widget_AllGates)
    {
        Widget_AllGates->setWindowTitle(QCoreApplication::translate("Widget_AllGates", "Form", nullptr));
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
        btn_GateEor->setText(QString());
        btn_GateTriEor->setText(QString());
        btn_labelGate->setText(QCoreApplication::translate("Widget_AllGates", "Label", nullptr));
        btn_nandGate->setText(QString());
        btn_norGate->setText(QString());
        btn_xorGate->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Widget_AllGates: public Ui_Widget_AllGates {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_ALLGATES_H
