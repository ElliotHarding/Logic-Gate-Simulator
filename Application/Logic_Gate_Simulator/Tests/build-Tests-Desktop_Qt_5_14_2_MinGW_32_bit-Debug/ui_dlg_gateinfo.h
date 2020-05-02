/********************************************************************************
** Form generated from reading UI file 'dlg_gateinfo.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLG_GATEINFO_H
#define UI_DLG_GATEINFO_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DLG_GateInfo
{
public:
    QCheckBox *cb_Enabled;
    QPushButton *btn_DeleteGate;
    QLabel *lbl_Type;
    QLabel *lbl_GateType;
    QCheckBox *signalCheck;
    QLineEdit *lineEdit_Frequency;
    QLabel *lbl_Frequency;
    QCheckBox *cb_DragMode;
    QPushButton *btn_Edit;

    void setupUi(QWidget *DLG_GateInfo)
    {
        if (DLG_GateInfo->objectName().isEmpty())
            DLG_GateInfo->setObjectName(QString::fromUtf8("DLG_GateInfo"));
        DLG_GateInfo->resize(140, 175);
        DLG_GateInfo->setAutoFillBackground(false);
        DLG_GateInfo->setStyleSheet(QString::fromUtf8(""));
        cb_Enabled = new QCheckBox(DLG_GateInfo);
        cb_Enabled->setObjectName(QString::fromUtf8("cb_Enabled"));
        cb_Enabled->setGeometry(QRect(5, 50, 141, 17));
        btn_DeleteGate = new QPushButton(DLG_GateInfo);
        btn_DeleteGate->setObjectName(QString::fromUtf8("btn_DeleteGate"));
        btn_DeleteGate->setGeometry(QRect(110, 5, 31, 31));
        btn_DeleteGate->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-bin.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_DeleteGate->setIcon(icon);
        btn_DeleteGate->setIconSize(QSize(22, 22));
        btn_DeleteGate->setFlat(true);
        lbl_Type = new QLabel(DLG_GateInfo);
        lbl_Type->setObjectName(QString::fromUtf8("lbl_Type"));
        lbl_Type->setGeometry(QRect(5, 5, 41, 21));
        lbl_GateType = new QLabel(DLG_GateInfo);
        lbl_GateType->setObjectName(QString::fromUtf8("lbl_GateType"));
        lbl_GateType->setGeometry(QRect(10, 20, 81, 21));
        signalCheck = new QCheckBox(DLG_GateInfo);
        signalCheck->setObjectName(QString::fromUtf8("signalCheck"));
        signalCheck->setGeometry(QRect(5, 80, 141, 17));
        lineEdit_Frequency = new QLineEdit(DLG_GateInfo);
        lineEdit_Frequency->setObjectName(QString::fromUtf8("lineEdit_Frequency"));
        lineEdit_Frequency->setGeometry(QRect(10, 150, 121, 20));
        lbl_Frequency = new QLabel(DLG_GateInfo);
        lbl_Frequency->setObjectName(QString::fromUtf8("lbl_Frequency"));
        lbl_Frequency->setGeometry(QRect(10, 130, 111, 21));
        cb_DragMode = new QCheckBox(DLG_GateInfo);
        cb_DragMode->setObjectName(QString::fromUtf8("cb_DragMode"));
        cb_DragMode->setGeometry(QRect(5, 80, 141, 17));
        btn_Edit = new QPushButton(DLG_GateInfo);
        btn_Edit->setObjectName(QString::fromUtf8("btn_Edit"));
        btn_Edit->setGeometry(QRect(80, 9, 31, 21));
        cb_DragMode->raise();
        cb_Enabled->raise();
        btn_DeleteGate->raise();
        lbl_Type->raise();
        lbl_GateType->raise();
        signalCheck->raise();
        lineEdit_Frequency->raise();
        lbl_Frequency->raise();
        btn_Edit->raise();

        retranslateUi(DLG_GateInfo);

        QMetaObject::connectSlotsByName(DLG_GateInfo);
    } // setupUi

    void retranslateUi(QWidget *DLG_GateInfo)
    {
        DLG_GateInfo->setWindowTitle(QCoreApplication::translate("DLG_GateInfo", "Form", nullptr));
        cb_Enabled->setText(QCoreApplication::translate("DLG_GateInfo", "Enabled", nullptr));
        btn_DeleteGate->setText(QString());
        lbl_Type->setText(QCoreApplication::translate("DLG_GateInfo", "Type :", nullptr));
        lbl_GateType->setText(QCoreApplication::translate("DLG_GateInfo", "-", nullptr));
        signalCheck->setText(QCoreApplication::translate("DLG_GateInfo", "Input Signal", nullptr));
        lbl_Frequency->setText(QCoreApplication::translate("DLG_GateInfo", "Frequency", nullptr));
        cb_DragMode->setText(QCoreApplication::translate("DLG_GateInfo", "Drag All", nullptr));
        btn_Edit->setText(QCoreApplication::translate("DLG_GateInfo", "Edit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DLG_GateInfo: public Ui_DLG_GateInfo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLG_GATEINFO_H
