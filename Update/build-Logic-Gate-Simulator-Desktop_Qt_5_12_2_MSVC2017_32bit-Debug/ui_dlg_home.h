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
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
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
    QWidget *widget;
    QWidget *tab;
    QWidget *tab2;
    QPushButton *btn_Drag;
    QPushButton *btn_Delete;
    QPushButton *btn_link;
    QPushButton *btn_newPage;
    QPushButton *btn_orGate;
    QPushButton *btn_notGate;
    QPushButton *btn_andGate;
    QPushButton *btn_sourceGate;
    QPushButton *btn_DeleteLink;
    QPushButton *btn_click;

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
        PlayField->setElideMode(Qt::ElideMiddle);
        PlayField->setUsesScrollButtons(false);
        PlayField->setDocumentMode(false);
        PlayField->setTabsClosable(true);
        PlayField->setTabBarAutoHide(false);
        widget = new QWidget();
        widget->setObjectName(QString::fromUtf8("widget"));
        PlayField->addTab(widget, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        PlayField->addTab(tab, QString());
        tab2 = new QWidget();
        tab2->setObjectName(QString::fromUtf8("tab2"));
        PlayField->addTab(tab2, QString());
        btn_Drag = new QPushButton(centralwidget);
        btn_Drag->setObjectName(QString::fromUtf8("btn_Drag"));
        btn_Drag->setGeometry(QRect(750, 70, 41, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Resources/Resources/icon-drag.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_Drag->setIcon(icon);
        btn_Drag->setIconSize(QSize(32, 32));
        btn_Delete = new QPushButton(centralwidget);
        btn_Delete->setObjectName(QString::fromUtf8("btn_Delete"));
        btn_Delete->setGeometry(QRect(700, 70, 41, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Resources/Resources/icon-bin.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_Delete->setIcon(icon1);
        btn_Delete->setIconSize(QSize(32, 32));
        btn_link = new QPushButton(centralwidget);
        btn_link->setObjectName(QString::fromUtf8("btn_link"));
        btn_link->setGeometry(QRect(700, 120, 41, 41));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Resources/Resources/icon-link-basic.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_link->setIcon(icon2);
        btn_link->setIconSize(QSize(32, 32));
        btn_newPage = new QPushButton(centralwidget);
        btn_newPage->setObjectName(QString::fromUtf8("btn_newPage"));
        btn_newPage->setGeometry(QRect(690, 20, 101, 41));
        btn_orGate = new QPushButton(centralwidget);
        btn_orGate->setObjectName(QString::fromUtf8("btn_orGate"));
        btn_orGate->setGeometry(QRect(110, 530, 75, 61));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Resources/Resources/gate-or.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_orGate->setIcon(icon3);
        btn_orGate->setIconSize(QSize(64, 64));
        btn_notGate = new QPushButton(centralwidget);
        btn_notGate->setObjectName(QString::fromUtf8("btn_notGate"));
        btn_notGate->setGeometry(QRect(200, 530, 75, 61));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Resources/Resources/gate-not.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_notGate->setIcon(icon4);
        btn_notGate->setIconSize(QSize(64, 64));
        btn_andGate = new QPushButton(centralwidget);
        btn_andGate->setObjectName(QString::fromUtf8("btn_andGate"));
        btn_andGate->setGeometry(QRect(20, 530, 75, 61));
        btn_andGate->setAutoFillBackground(false);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Resources/Resources/gate-and.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_andGate->setIcon(icon5);
        btn_andGate->setIconSize(QSize(70, 64));
        btn_sourceGate = new QPushButton(centralwidget);
        btn_sourceGate->setObjectName(QString::fromUtf8("btn_sourceGate"));
        btn_sourceGate->setGeometry(QRect(290, 530, 75, 61));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/Resources/Resources/box.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_sourceGate->setIcon(icon6);
        btn_sourceGate->setIconSize(QSize(64, 64));
        btn_DeleteLink = new QPushButton(centralwidget);
        btn_DeleteLink->setObjectName(QString::fromUtf8("btn_DeleteLink"));
        btn_DeleteLink->setGeometry(QRect(750, 120, 41, 41));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/Resources/Resources/icon-link-delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_DeleteLink->setIcon(icon7);
        btn_DeleteLink->setIconSize(QSize(32, 32));
        btn_click = new QPushButton(centralwidget);
        btn_click->setObjectName(QString::fromUtf8("btn_click"));
        btn_click->setGeometry(QRect(700, 170, 41, 41));
        btn_click->setIcon(icon2);
        btn_click->setIconSize(QSize(32, 32));
        DLG_Home->setCentralWidget(centralwidget);

        retranslateUi(DLG_Home);

        PlayField->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(DLG_Home);
    } // setupUi

    void retranslateUi(QMainWindow *DLG_Home)
    {
        DLG_Home->setWindowTitle(QApplication::translate("DLG_Home", "MainWindow", nullptr));
        actionNew_page->setText(QApplication::translate("DLG_Home", "New page", nullptr));
        PlayField->setTabText(PlayField->indexOf(widget), QApplication::translate("DLG_Home", "Page", nullptr));
        PlayField->setTabText(PlayField->indexOf(tab), QApplication::translate("DLG_Home", "Page 1", nullptr));
        PlayField->setTabText(PlayField->indexOf(tab2), QApplication::translate("DLG_Home", "Page 2", nullptr));
        btn_Drag->setText(QString());
        btn_Delete->setText(QString());
        btn_link->setText(QString());
        btn_newPage->setText(QApplication::translate("DLG_Home", "New Page", nullptr));
        btn_orGate->setText(QString());
        btn_notGate->setText(QString());
        btn_andGate->setText(QString());
        btn_sourceGate->setText(QString());
        btn_DeleteLink->setText(QString());
        btn_click->setText(QApplication::translate("DLG_Home", "a", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DLG_Home: public Ui_DLG_Home {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLG_HOME_H
