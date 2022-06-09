/********************************************************************************
** Form generated from reading UI file 'dlg_textedit.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLG_TEXTEDIT_H
#define UI_DLG_TEXTEDIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DLG_TextEdit
{
public:
    QTextEdit *textEdit;
    QPushButton *btn_Cancel;
    QPushButton *btn_Bold;
    QPushButton *btn_Underline;
    QLabel *lbl_fontSize;
    QPushButton *btn_clear;
    QWidget *widget_2;
    QWidget *widget;
    QPushButton *btn_Ok;

    void setupUi(QDialog *DLG_TextEdit)
    {
        if (DLG_TextEdit->objectName().isEmpty())
            DLG_TextEdit->setObjectName(QString::fromUtf8("DLG_TextEdit"));
        DLG_TextEdit->setWindowModality(Qt::ApplicationModal);
        DLG_TextEdit->resize(400, 190);
        DLG_TextEdit->setContextMenuPolicy(Qt::NoContextMenu);
        DLG_TextEdit->setAutoFillBackground(true);
        DLG_TextEdit->setStyleSheet(QString::fromUtf8("background-color:rgb(200,200,200);"));
        DLG_TextEdit->setModal(false);
        textEdit = new QTextEdit(DLG_TextEdit);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(10, 40, 381, 141));
        textEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        btn_Cancel = new QPushButton(DLG_TextEdit);
        btn_Cancel->setObjectName(QString::fromUtf8("btn_Cancel"));
        btn_Cancel->setGeometry(QRect(290, 0, 61, 30));
        btn_Cancel->setAutoFillBackground(true);
        btn_Cancel->setStyleSheet(QString::fromUtf8("background-color:rgb(200,200,200);"));
        btn_Cancel->setAutoDefault(false);
        btn_Cancel->setFlat(true);
        btn_Bold = new QPushButton(DLG_TextEdit);
        btn_Bold->setObjectName(QString::fromUtf8("btn_Bold"));
        btn_Bold->setGeometry(QRect(150, 0, 31, 30));
        QFont font;
        font.setBold(true);
        font.setUnderline(false);
        font.setWeight(75);
        btn_Bold->setFont(font);
        btn_Bold->setAutoFillBackground(false);
        btn_Bold->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(200, 200, 200);\n"
""));
        btn_Bold->setAutoDefault(false);
        btn_Bold->setFlat(true);
        btn_Underline = new QPushButton(DLG_TextEdit);
        btn_Underline->setObjectName(QString::fromUtf8("btn_Underline"));
        btn_Underline->setGeometry(QRect(180, 0, 31, 30));
        QFont font1;
        font1.setUnderline(true);
        btn_Underline->setFont(font1);
        btn_Underline->setAutoFillBackground(false);
        btn_Underline->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(200, 200, 200);\n"
""));
        btn_Underline->setAutoDefault(false);
        btn_Underline->setFlat(true);
        lbl_fontSize = new QLabel(DLG_TextEdit);
        lbl_fontSize->setObjectName(QString::fromUtf8("lbl_fontSize"));
        lbl_fontSize->setGeometry(QRect(120, 0, 31, 30));
        lbl_fontSize->setStyleSheet(QString::fromUtf8("background-color: rgb(200, 200, 200);"));
        lbl_fontSize->setAlignment(Qt::AlignCenter);
        btn_clear = new QPushButton(DLG_TextEdit);
        btn_clear->setObjectName(QString::fromUtf8("btn_clear"));
        btn_clear->setGeometry(QRect(210, 0, 31, 30));
        btn_clear->setAutoFillBackground(false);
        btn_clear->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(200, 200, 200);\n"
""));
        btn_clear->setAutoDefault(false);
        btn_clear->setFlat(true);
        widget_2 = new QWidget(DLG_TextEdit);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setGeometry(QRect(0, 30, 411, 171));
        widget_2->setStyleSheet(QString::fromUtf8("background-color:rgb(85,85,85);"));
        widget = new QWidget(DLG_TextEdit);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(20, 5, 91, 21));
        btn_Ok = new QPushButton(DLG_TextEdit);
        btn_Ok->setObjectName(QString::fromUtf8("btn_Ok"));
        btn_Ok->setGeometry(QRect(350, 0, 51, 30));
        btn_Ok->setAutoFillBackground(true);
        btn_Ok->setStyleSheet(QString::fromUtf8("background-color:rgb(200,200,200);"));
        btn_Ok->setAutoDefault(false);
        btn_Ok->setFlat(true);
        widget_2->raise();
        textEdit->raise();
        btn_Bold->raise();
        btn_Underline->raise();
        lbl_fontSize->raise();
        btn_clear->raise();
        widget->raise();
        btn_Cancel->raise();
        btn_Ok->raise();

        retranslateUi(DLG_TextEdit);

        btn_Bold->setDefault(false);
        btn_Underline->setDefault(false);
        btn_Ok->setDefault(false);


        QMetaObject::connectSlotsByName(DLG_TextEdit);
    } // setupUi

    void retranslateUi(QDialog *DLG_TextEdit)
    {
        DLG_TextEdit->setWindowTitle(QString());
        btn_Cancel->setText(QCoreApplication::translate("DLG_TextEdit", "Cancel", nullptr));
        btn_Bold->setText(QCoreApplication::translate("DLG_TextEdit", "B", nullptr));
        btn_Underline->setText(QCoreApplication::translate("DLG_TextEdit", "U", nullptr));
        lbl_fontSize->setText(QCoreApplication::translate("DLG_TextEdit", "10", nullptr));
        btn_clear->setText(QCoreApplication::translate("DLG_TextEdit", "C", nullptr));
        btn_Ok->setText(QCoreApplication::translate("DLG_TextEdit", "Ok", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DLG_TextEdit: public Ui_DLG_TextEdit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLG_TEXTEDIT_H
