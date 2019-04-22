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
#include <QtWidgets/QFrame>
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
    QFrame *line;
    QFrame *line_2;
    QFrame *line_3;
    QFrame *line_4;
    QFrame *line_5;
    QFrame *line_6;
    QPushButton *btn_Save;
    QPushButton *btn_load;
    QPushButton *btn_recieverGate;
    QPushButton *btn_gateCollection;

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
        PlayField->setGeometry(QRect(0, 0, 671, 591));
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
        btn_Drag->setGeometry(QRect(740, 100, 51, 41));
        btn_Drag->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-drag.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_Drag->setIcon(icon);
        btn_Drag->setIconSize(QSize(32, 32));
        btn_Delete = new QPushButton(centralwidget);
        btn_Delete->setObjectName(QString::fromUtf8("btn_Delete"));
        btn_Delete->setGeometry(QRect(740, 200, 51, 41));
        btn_Delete->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-bin.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_Delete->setIcon(icon1);
        btn_Delete->setIconSize(QSize(32, 32));
        btn_link = new QPushButton(centralwidget);
        btn_link->setObjectName(QString::fromUtf8("btn_link"));
        btn_link->setGeometry(QRect(680, 150, 51, 41));
        btn_link->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-link-basic.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_link->setIcon(icon2);
        btn_link->setIconSize(QSize(32, 32));
        btn_newPage = new QPushButton(centralwidget);
        btn_newPage->setObjectName(QString::fromUtf8("btn_newPage"));
        btn_newPage->setGeometry(QRect(740, 40, 51, 41));
        btn_newPage->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-new-page.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_newPage->setIcon(icon3);
        btn_newPage->setIconSize(QSize(32, 32));
        btn_orGate = new QPushButton(centralwidget);
        btn_orGate->setObjectName(QString::fromUtf8("btn_orGate"));
        btn_orGate->setGeometry(QRect(680, 330, 51, 41));
        btn_orGate->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-gate-or.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_orGate->setIcon(icon4);
        btn_orGate->setIconSize(QSize(40, 40));
        btn_notGate = new QPushButton(centralwidget);
        btn_notGate->setObjectName(QString::fromUtf8("btn_notGate"));
        btn_notGate->setGeometry(QRect(740, 330, 51, 41));
        btn_notGate->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-gate-not.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_notGate->setIcon(icon5);
        btn_notGate->setIconSize(QSize(40, 40));
        btn_andGate = new QPushButton(centralwidget);
        btn_andGate->setObjectName(QString::fromUtf8("btn_andGate"));
        btn_andGate->setGeometry(QRect(680, 430, 51, 41));
        btn_andGate->setAutoFillBackground(false);
        btn_andGate->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-gate-and.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_andGate->setIcon(icon6);
        btn_andGate->setIconSize(QSize(40, 40));
        btn_sourceGate = new QPushButton(centralwidget);
        btn_sourceGate->setObjectName(QString::fromUtf8("btn_sourceGate"));
        btn_sourceGate->setGeometry(QRect(680, 380, 51, 41));
        btn_sourceGate->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-gate-output.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_sourceGate->setIcon(icon7);
        btn_sourceGate->setIconSize(QSize(40, 40));
        btn_DeleteLink = new QPushButton(centralwidget);
        btn_DeleteLink->setObjectName(QString::fromUtf8("btn_DeleteLink"));
        btn_DeleteLink->setGeometry(QRect(740, 150, 51, 41));
        btn_DeleteLink->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-link-delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_DeleteLink->setIcon(icon8);
        btn_DeleteLink->setIconSize(QSize(32, 32));
        btn_click = new QPushButton(centralwidget);
        btn_click->setObjectName(QString::fromUtf8("btn_click"));
        btn_click->setGeometry(QRect(680, 100, 51, 41));
        btn_click->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-tool.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_click->setIcon(icon9);
        btn_click->setIconSize(QSize(32, 32));
        line = new QFrame(centralwidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(680, 80, 111, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(centralwidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(680, 240, 111, 16));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        line_3 = new QFrame(centralwidget);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setGeometry(QRect(680, 310, 111, 16));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        line_4 = new QFrame(centralwidget);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setGeometry(QRect(680, 470, 111, 20));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);
        line_5 = new QFrame(centralwidget);
        line_5->setObjectName(QString::fromUtf8("line_5"));
        line_5->setGeometry(QRect(680, 580, 111, 20));
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);
        line_6 = new QFrame(centralwidget);
        line_6->setObjectName(QString::fromUtf8("line_6"));
        line_6->setGeometry(QRect(680, 20, 111, 20));
        line_6->setFrameShape(QFrame::HLine);
        line_6->setFrameShadow(QFrame::Sunken);
        btn_Save = new QPushButton(centralwidget);
        btn_Save->setObjectName(QString::fromUtf8("btn_Save"));
        btn_Save->setGeometry(QRect(680, 260, 51, 41));
        btn_Save->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-file-down.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_Save->setIcon(icon10);
        btn_Save->setIconSize(QSize(32, 32));
        btn_load = new QPushButton(centralwidget);
        btn_load->setObjectName(QString::fromUtf8("btn_load"));
        btn_load->setGeometry(QRect(740, 260, 51, 41));
        btn_load->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-file-up.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_load->setIcon(icon11);
        btn_load->setIconSize(QSize(32, 32));
        btn_recieverGate = new QPushButton(centralwidget);
        btn_recieverGate->setObjectName(QString::fromUtf8("btn_recieverGate"));
        btn_recieverGate->setGeometry(QRect(740, 380, 51, 41));
        btn_recieverGate->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-gate-input.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_recieverGate->setIcon(icon12);
        btn_recieverGate->setIconSize(QSize(40, 40));
        btn_gateCollection = new QPushButton(centralwidget);
        btn_gateCollection->setObjectName(QString::fromUtf8("btn_gateCollection"));
        btn_gateCollection->setGeometry(QRect(740, 430, 51, 41));
        btn_gateCollection->setAutoFillBackground(false);
        btn_gateCollection->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-gate-collection.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_gateCollection->setIcon(icon13);
        btn_gateCollection->setIconSize(QSize(37, 37));
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
        btn_newPage->setText(QString());
        btn_orGate->setText(QString());
        btn_notGate->setText(QString());
        btn_andGate->setText(QString());
        btn_sourceGate->setText(QString());
        btn_DeleteLink->setText(QString());
        btn_click->setText(QString());
        btn_Save->setText(QString());
        btn_load->setText(QString());
        btn_recieverGate->setText(QString());
        btn_gateCollection->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class DLG_Home: public Ui_DLG_Home {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLG_HOME_H
