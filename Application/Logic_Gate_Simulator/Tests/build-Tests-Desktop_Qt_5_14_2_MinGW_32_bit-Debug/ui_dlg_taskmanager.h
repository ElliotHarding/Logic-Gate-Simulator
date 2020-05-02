/********************************************************************************
** Form generated from reading UI file 'dlg_taskmanager.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLG_TASKMANAGER_H
#define UI_DLG_TASKMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DLG_TaskManager
{
public:
    QAction *actionReset_Completed;
    QWidget *centralwidget;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *DLG_TaskManager)
    {
        if (DLG_TaskManager->objectName().isEmpty())
            DLG_TaskManager->setObjectName(QString::fromUtf8("DLG_TaskManager"));
        DLG_TaskManager->resize(800, 600);
        actionReset_Completed = new QAction(DLG_TaskManager);
        actionReset_Completed->setObjectName(QString::fromUtf8("actionReset_Completed"));
        centralwidget = new QWidget(DLG_TaskManager);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        DLG_TaskManager->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(DLG_TaskManager);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        DLG_TaskManager->setStatusBar(statusbar);

        retranslateUi(DLG_TaskManager);

        QMetaObject::connectSlotsByName(DLG_TaskManager);
    } // setupUi

    void retranslateUi(QMainWindow *DLG_TaskManager)
    {
        DLG_TaskManager->setWindowTitle(QCoreApplication::translate("DLG_TaskManager", "Tasks", nullptr));
        actionReset_Completed->setText(QCoreApplication::translate("DLG_TaskManager", "Reset Completed", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DLG_TaskManager: public Ui_DLG_TaskManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLG_TASKMANAGER_H
