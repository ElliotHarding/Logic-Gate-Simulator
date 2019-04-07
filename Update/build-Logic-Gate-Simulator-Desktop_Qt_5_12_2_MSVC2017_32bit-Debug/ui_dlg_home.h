/********************************************************************************
** Form generated from reading UI file 'dlg_home.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLG_HOME_H
#define UI_DLG_HOME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DLG_Home
{
public:
    QAction *actionNew_page;
    QWidget *centralwidget;
    QTabWidget *PlayField;
    QWidget *tab;
    QWidget *tab2;
    QPushButton *btn_Drag;
    QPushButton *btn_Delete;
    QPushButton *btn_link;
    QLabel *lbl_clickMode;
    QPushButton *btn_newPage;

    void setupUi(QMainWindow *DLG_Home)
    {
        if (DLG_Home->objectName().isEmpty())
            DLG_Home->setObjectName(QString::fromUtf8("DLG_Home"));
        DLG_Home->resize(800, 600);
        actionNew_page = new QAction(DLG_Home);
        actionNew_page->setObjectName(QString::fromUtf8("actionNew_page"));
        centralwidget = new QWidget(DLG_Home);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        PlayField = new QTabWidget(centralwidget);
        PlayField->setObjectName(QString::fromUtf8("PlayField"));
        PlayField->setGeometry(QRect(0, 0, 681, 521));
        PlayField->setElideMode(Qt::ElideNone);
        PlayField->setDocumentMode(false);
        PlayField->setTabsClosable(true);
        PlayField->setTabBarAutoHide(false);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        PlayField->addTab(tab, QString());
        tab2 = new QWidget();
        tab2->setObjectName(QString::fromUtf8("tab2"));
        PlayField->addTab(tab2, QString());
        btn_Drag = new QPushButton(centralwidget);
        btn_Drag->setObjectName(QString::fromUtf8("btn_Drag"));
        btn_Drag->setGeometry(QRect(690, 190, 101, 41));
        btn_Delete = new QPushButton(centralwidget);
        btn_Delete->setObjectName(QString::fromUtf8("btn_Delete"));
        btn_Delete->setGeometry(QRect(690, 240, 101, 41));
        btn_link = new QPushButton(centralwidget);
        btn_link->setObjectName(QString::fromUtf8("btn_link"));
        btn_link->setGeometry(QRect(690, 290, 101, 41));
        lbl_clickMode = new QLabel(centralwidget);
        lbl_clickMode->setObjectName(QString::fromUtf8("lbl_clickMode"));
        lbl_clickMode->setGeometry(QRect(690, 150, 91, 31));
        lbl_clickMode->setAlignment(Qt::AlignCenter);
        btn_newPage = new QPushButton(centralwidget);
        btn_newPage->setObjectName(QString::fromUtf8("btn_newPage"));
        btn_newPage->setGeometry(QRect(690, 20, 101, 41));
        DLG_Home->setCentralWidget(centralwidget);

        retranslateUi(DLG_Home);

        PlayField->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(DLG_Home);
    } // setupUi

    void retranslateUi(QMainWindow *DLG_Home)
    {
        DLG_Home->setWindowTitle(QApplication::translate("DLG_Home", "MainWindow", nullptr));
        actionNew_page->setText(QApplication::translate("DLG_Home", "New page", nullptr));
        PlayField->setTabText(PlayField->indexOf(tab), QApplication::translate("DLG_Home", "Tab 1", nullptr));
        PlayField->setTabText(PlayField->indexOf(tab2), QApplication::translate("DLG_Home", "Tab 2", nullptr));
        btn_Drag->setText(QApplication::translate("DLG_Home", "Drag", nullptr));
        btn_Delete->setText(QApplication::translate("DLG_Home", "Delete", nullptr));
        btn_link->setText(QApplication::translate("DLG_Home", "Link", nullptr));
        lbl_clickMode->setText(QApplication::translate("DLG_Home", "Click Mode : Drag", nullptr));
        btn_newPage->setText(QApplication::translate("DLG_Home", "New Page", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DLG_Home: public Ui_DLG_Home {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLG_HOME_H
