/********************************************************************************
** Form generated from reading UI file 'dlg_load.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLG_LOAD_H
#define UI_DLG_LOAD_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DLG_Load
{
public:
    QWidget *centralwidget;
    QProgressBar *progressBar;
    QLabel *lbl_progressStep;

    void setupUi(QMainWindow *DLG_Load)
    {
        if (DLG_Load->objectName().isEmpty())
            DLG_Load->setObjectName(QString::fromUtf8("DLG_Load"));
        DLG_Load->resize(279, 70);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-application.png"), QSize(), QIcon::Normal, QIcon::Off);
        DLG_Load->setWindowIcon(icon);
        centralwidget = new QWidget(DLG_Load);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(10, 40, 261, 21));
        progressBar->setValue(0);
        progressBar->setAlignment(Qt::AlignCenter);
        progressBar->setOrientation(Qt::Horizontal);
        lbl_progressStep = new QLabel(centralwidget);
        lbl_progressStep->setObjectName(QString::fromUtf8("lbl_progressStep"));
        lbl_progressStep->setGeometry(QRect(0, 10, 281, 20));
        lbl_progressStep->setTextFormat(Qt::AutoText);
        lbl_progressStep->setAlignment(Qt::AlignCenter);
        DLG_Load->setCentralWidget(centralwidget);

        retranslateUi(DLG_Load);

        QMetaObject::connectSlotsByName(DLG_Load);
    } // setupUi

    void retranslateUi(QMainWindow *DLG_Load)
    {
        DLG_Load->setWindowTitle(QCoreApplication::translate("DLG_Load", "Loading", nullptr));
        lbl_progressStep->setText(QCoreApplication::translate("DLG_Load", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DLG_Load: public Ui_DLG_Load {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLG_LOAD_H
