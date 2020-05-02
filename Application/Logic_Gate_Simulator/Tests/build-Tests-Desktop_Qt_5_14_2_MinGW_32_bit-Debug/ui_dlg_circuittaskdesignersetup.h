/********************************************************************************
** Form generated from reading UI file 'dlg_circuittaskdesignersetup.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLG_CIRCUITTASKDESIGNERSETUP_H
#define UI_DLG_CIRCUITTASKDESIGNERSETUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DLG_CircuitTaskDesignerSetup
{
public:
    QWidget *centralwidget;
    QPushButton *btn_ok;
    QTextEdit *txt_inputs;
    QLabel *label;
    QLabel *label_2;
    QTextEdit *txt_outputs;
    QLabel *label_3;

    void setupUi(QMainWindow *DLG_CircuitTaskDesignerSetup)
    {
        if (DLG_CircuitTaskDesignerSetup->objectName().isEmpty())
            DLG_CircuitTaskDesignerSetup->setObjectName(QString::fromUtf8("DLG_CircuitTaskDesignerSetup"));
        DLG_CircuitTaskDesignerSetup->resize(180, 156);
        centralwidget = new QWidget(DLG_CircuitTaskDesignerSetup);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        btn_ok = new QPushButton(centralwidget);
        btn_ok->setObjectName(QString::fromUtf8("btn_ok"));
        btn_ok->setGeometry(QRect(50, 120, 80, 28));
        txt_inputs = new QTextEdit(centralwidget);
        txt_inputs->setObjectName(QString::fromUtf8("txt_inputs"));
        txt_inputs->setGeometry(QRect(130, 40, 41, 27));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 42, 111, 21));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 82, 111, 21));
        txt_outputs = new QTextEdit(centralwidget);
        txt_outputs->setObjectName(QString::fromUtf8("txt_outputs"));
        txt_outputs->setGeometry(QRect(130, 80, 41, 27));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 10, 141, 20));
        label_3->setAlignment(Qt::AlignCenter);
        DLG_CircuitTaskDesignerSetup->setCentralWidget(centralwidget);

        retranslateUi(DLG_CircuitTaskDesignerSetup);

        QMetaObject::connectSlotsByName(DLG_CircuitTaskDesignerSetup);
    } // setupUi

    void retranslateUi(QMainWindow *DLG_CircuitTaskDesignerSetup)
    {
        DLG_CircuitTaskDesignerSetup->setWindowTitle(QString());
        btn_ok->setText(QCoreApplication::translate("DLG_CircuitTaskDesignerSetup", "Ok", nullptr));
        label->setText(QCoreApplication::translate("DLG_CircuitTaskDesignerSetup", "Number of inputs:", nullptr));
        label_2->setText(QCoreApplication::translate("DLG_CircuitTaskDesignerSetup", "Number of outputs:", nullptr));
        label_3->setText(QCoreApplication::translate("DLG_CircuitTaskDesignerSetup", "Circuit design", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DLG_CircuitTaskDesignerSetup: public Ui_DLG_CircuitTaskDesignerSetup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLG_CIRCUITTASKDESIGNERSETUP_H
