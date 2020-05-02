/********************************************************************************
** Form generated from reading UI file 'dlg_message.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLG_MESSAGE_H
#define UI_DLG_MESSAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_DLG_Message
{
public:
    QPushButton *pushButton;
    QLabel *lbl_text;

    void setupUi(QDialog *DLG_Message)
    {
        if (DLG_Message->objectName().isEmpty())
            DLG_Message->setObjectName(QString::fromUtf8("DLG_Message"));
        DLG_Message->setWindowModality(Qt::WindowModal);
        DLG_Message->resize(300, 80);
        DLG_Message->setContextMenuPolicy(Qt::NoContextMenu);
        pushButton = new QPushButton(DLG_Message);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(110, 50, 80, 23));
        lbl_text = new QLabel(DLG_Message);
        lbl_text->setObjectName(QString::fromUtf8("lbl_text"));
        lbl_text->setGeometry(QRect(0, 20, 300, 13));
        lbl_text->setAlignment(Qt::AlignCenter);

        retranslateUi(DLG_Message);

        QMetaObject::connectSlotsByName(DLG_Message);
    } // setupUi

    void retranslateUi(QDialog *DLG_Message)
    {
        DLG_Message->setWindowTitle(QCoreApplication::translate("DLG_Message", "Message", nullptr));
        pushButton->setText(QCoreApplication::translate("DLG_Message", "Ok", nullptr));
        lbl_text->setText(QCoreApplication::translate("DLG_Message", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DLG_Message: public Ui_DLG_Message {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLG_MESSAGE_H
