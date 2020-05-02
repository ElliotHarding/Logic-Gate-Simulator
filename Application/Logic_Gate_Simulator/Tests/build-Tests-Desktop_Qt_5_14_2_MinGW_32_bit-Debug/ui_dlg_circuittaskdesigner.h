/********************************************************************************
** Form generated from reading UI file 'dlg_circuittaskdesigner.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLG_CIRCUITTASKDESIGNER_H
#define UI_DLG_CIRCUITTASKDESIGNER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DLG_CircuitTaskDesigner
{
public:
    QWidget *centralwidget;
    QPushButton *btn_done;

    void setupUi(QMainWindow *DLG_CircuitTaskDesigner)
    {
        if (DLG_CircuitTaskDesigner->objectName().isEmpty())
            DLG_CircuitTaskDesigner->setObjectName(QString::fromUtf8("DLG_CircuitTaskDesigner"));
        DLG_CircuitTaskDesigner->resize(200, 390);
        DLG_CircuitTaskDesigner->setMinimumSize(QSize(200, 390));
        DLG_CircuitTaskDesigner->setMaximumSize(QSize(200, 390));
        DLG_CircuitTaskDesigner->setAutoFillBackground(true);
        centralwidget = new QWidget(DLG_CircuitTaskDesigner);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        btn_done = new QPushButton(centralwidget);
        btn_done->setObjectName(QString::fromUtf8("btn_done"));
        btn_done->setGeometry(QRect(50, 350, 93, 28));
        DLG_CircuitTaskDesigner->setCentralWidget(centralwidget);

        retranslateUi(DLG_CircuitTaskDesigner);

        QMetaObject::connectSlotsByName(DLG_CircuitTaskDesigner);
    } // setupUi

    void retranslateUi(QMainWindow *DLG_CircuitTaskDesigner)
    {
        DLG_CircuitTaskDesigner->setWindowTitle(QString());
        btn_done->setText(QCoreApplication::translate("DLG_CircuitTaskDesigner", "Done", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DLG_CircuitTaskDesigner: public Ui_DLG_CircuitTaskDesigner {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLG_CIRCUITTASKDESIGNER_H
