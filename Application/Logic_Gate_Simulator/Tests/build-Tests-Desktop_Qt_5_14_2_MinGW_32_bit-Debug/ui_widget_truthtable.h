/********************************************************************************
** Form generated from reading UI file 'widget_truthtable.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_TRUTHTABLE_H
#define UI_WIDGET_TRUTHTABLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget_TruthTable
{
public:

    void setupUi(QWidget *Widget_TruthTable)
    {
        if (Widget_TruthTable->objectName().isEmpty())
            Widget_TruthTable->setObjectName(QString::fromUtf8("Widget_TruthTable"));
        Widget_TruthTable->resize(200, 350);

        retranslateUi(Widget_TruthTable);

        QMetaObject::connectSlotsByName(Widget_TruthTable);
    } // setupUi

    void retranslateUi(QWidget *Widget_TruthTable)
    {
        Widget_TruthTable->setWindowTitle(QCoreApplication::translate("Widget_TruthTable", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget_TruthTable: public Ui_Widget_TruthTable {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_TRUTHTABLE_H
