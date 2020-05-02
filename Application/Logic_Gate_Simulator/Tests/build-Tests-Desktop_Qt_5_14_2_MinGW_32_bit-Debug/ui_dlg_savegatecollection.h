/********************************************************************************
** Form generated from reading UI file 'dlg_savegatecollection.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLG_SAVEGATECOLLECTION_H
#define UI_DLG_SAVEGATECOLLECTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_DLG_SaveGateCollection
{
public:
    QPushButton *Cancel;
    QPushButton *Save;
    QTextEdit *txt_name;
    QLabel *lblName;
    QLabel *lb_error;

    void setupUi(QDialog *DLG_SaveGateCollection)
    {
        if (DLG_SaveGateCollection->objectName().isEmpty())
            DLG_SaveGateCollection->setObjectName(QString::fromUtf8("DLG_SaveGateCollection"));
        DLG_SaveGateCollection->resize(252, 95);
        Cancel = new QPushButton(DLG_SaveGateCollection);
        Cancel->setObjectName(QString::fromUtf8("Cancel"));
        Cancel->setGeometry(QRect(20, 60, 81, 23));
        Save = new QPushButton(DLG_SaveGateCollection);
        Save->setObjectName(QString::fromUtf8("Save"));
        Save->setGeometry(QRect(144, 60, 81, 23));
        txt_name = new QTextEdit(DLG_SaveGateCollection);
        txt_name->setObjectName(QString::fromUtf8("txt_name"));
        txt_name->setGeometry(QRect(20, 30, 211, 21));
        txt_name->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        txt_name->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        lblName = new QLabel(DLG_SaveGateCollection);
        lblName->setObjectName(QString::fromUtf8("lblName"));
        lblName->setGeometry(QRect(20, 10, 47, 13));
        lb_error = new QLabel(DLG_SaveGateCollection);
        lb_error->setObjectName(QString::fromUtf8("lb_error"));
        lb_error->setGeometry(QRect(180, 10, 61, 16));
        lb_error->setStyleSheet(QString::fromUtf8(""));

        retranslateUi(DLG_SaveGateCollection);

        QMetaObject::connectSlotsByName(DLG_SaveGateCollection);
    } // setupUi

    void retranslateUi(QDialog *DLG_SaveGateCollection)
    {
        DLG_SaveGateCollection->setWindowTitle(QCoreApplication::translate("DLG_SaveGateCollection", "Name Custom Gate", nullptr));
        Cancel->setText(QCoreApplication::translate("DLG_SaveGateCollection", "Cancel", nullptr));
        Save->setText(QCoreApplication::translate("DLG_SaveGateCollection", "Save", nullptr));
        lblName->setText(QCoreApplication::translate("DLG_SaveGateCollection", "Name", nullptr));
        lb_error->setText(QCoreApplication::translate("DLG_SaveGateCollection", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DLG_SaveGateCollection: public Ui_DLG_SaveGateCollection {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLG_SAVEGATECOLLECTION_H
