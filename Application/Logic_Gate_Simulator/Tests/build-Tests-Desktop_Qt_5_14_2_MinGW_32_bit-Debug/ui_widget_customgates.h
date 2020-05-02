/********************************************************************************
** Form generated from reading UI file 'widget_customgates.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_CUSTOMGATES_H
#define UI_WIDGET_CUSTOMGATES_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget_CustomGates
{
public:
    QListWidget *customGateListWidget;
    QPushButton *btn_SelectionTool;
    QPushButton *btn_Delete;

    void setupUi(QWidget *Widget_CustomGates)
    {
        if (Widget_CustomGates->objectName().isEmpty())
            Widget_CustomGates->setObjectName(QString::fromUtf8("Widget_CustomGates"));
        Widget_CustomGates->resize(140, 301);
        Widget_CustomGates->setAutoFillBackground(false);
        Widget_CustomGates->setStyleSheet(QString::fromUtf8(""));
        customGateListWidget = new QListWidget(Widget_CustomGates);
        customGateListWidget->setObjectName(QString::fromUtf8("customGateListWidget"));
        customGateListWidget->setGeometry(QRect(10, 40, 121, 251));
        customGateListWidget->setSelectionMode(QAbstractItemView::NoSelection);
        customGateListWidget->setViewMode(QListView::ListMode);
        btn_SelectionTool = new QPushButton(Widget_CustomGates);
        btn_SelectionTool->setObjectName(QString::fromUtf8("btn_SelectionTool"));
        btn_SelectionTool->setGeometry(QRect(10, 5, 32, 32));
        btn_SelectionTool->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-gate-selection.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_SelectionTool->setIcon(icon);
        btn_SelectionTool->setIconSize(QSize(32, 32));
        btn_SelectionTool->setFlat(true);
        btn_Delete = new QPushButton(Widget_CustomGates);
        btn_Delete->setObjectName(QString::fromUtf8("btn_Delete"));
        btn_Delete->setGeometry(QRect(100, 5, 32, 32));
        btn_Delete->setStyleSheet(QString::fromUtf8(""));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-bin.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_Delete->setIcon(icon1);
        btn_Delete->setIconSize(QSize(32, 32));
        btn_Delete->setFlat(true);

        retranslateUi(Widget_CustomGates);

        QMetaObject::connectSlotsByName(Widget_CustomGates);
    } // setupUi

    void retranslateUi(QWidget *Widget_CustomGates)
    {
        Widget_CustomGates->setWindowTitle(QCoreApplication::translate("Widget_CustomGates", "Form", nullptr));
        btn_SelectionTool->setText(QString());
        btn_Delete->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Widget_CustomGates: public Ui_Widget_CustomGates {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_CUSTOMGATES_H
