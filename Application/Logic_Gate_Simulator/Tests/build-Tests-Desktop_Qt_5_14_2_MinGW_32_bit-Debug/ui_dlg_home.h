/********************************************************************************
** Form generated from reading UI file 'dlg_home.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLG_HOME_H
#define UI_DLG_HOME_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DLG_Home
{
public:
    QAction *actionNew_page;
    QAction *actionNewPage;
    QAction *actionSave;
    QAction *actionLoad;
    QAction *actionPan;
    QAction *actionDrag;
    QAction *actionEdit;
    QAction *actionDelete;
    QAction *actionLink;
    QAction *actionDelete_Link;
    QAction *actionZoom;
    QAction *actionZoom_2;
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionNew_circuit_from_truth_table_task;
    QAction *actionNew_truth_table_from_circuit_task;
    QAction *actionCircuit_from_truth_table_task;
    QAction *actionTruth_table_from_circuit_task;
    QAction *actionView_Tasks;
    QWidget *centralwidget;
    QTabWidget *PlayField;
    QWidget *widget;
    QWidget *tab;
    QWidget *tab2;
    QPushButton *btn_Drag;
    QPushButton *btn_Delete;
    QPushButton *btn_DeleteLink;
    QPushButton *btn_click;
    QPushButton *btn_zoomIn;
    QPushButton *btn_zoomOut;
    QPushButton *btn_newPage;
    QPushButton *btn_Pan;
    QPushButton *btn_undo;
    QPushButton *btn_redo;
    QWidget *layout_Dlg_GateInfo;
    QWidget *widget_2;
    QPushButton *btn_load;
    QFrame *line_3;
    QFrame *line_5;
    QFrame *line_6;
    QFrame *line_8;
    QPushButton *btn_Save;
    QPushButton *btn_tasks;
    QWidget *widget_4;
    QComboBox *comboBox;
    QWidget *layout_GateWidget;
    QWidget *layout_ZoomSlider;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuNew_task;
    QMenu *menuTools;
    QMenu *menuEdit;

    void setupUi(QMainWindow *DLG_Home)
    {
        if (DLG_Home->objectName().isEmpty())
            DLG_Home->setObjectName(QString::fromUtf8("DLG_Home"));
        DLG_Home->setWindowModality(Qt::NonModal);
        DLG_Home->resize(1000, 560);
        DLG_Home->setMinimumSize(QSize(1000, 560));
        DLG_Home->setMaximumSize(QSize(1000, 560));
        DLG_Home->setBaseSize(QSize(1000, 560));
        DLG_Home->setContextMenuPolicy(Qt::NoContextMenu);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-application.png"), QSize(), QIcon::Normal, QIcon::Off);
        DLG_Home->setWindowIcon(icon);
        DLG_Home->setStyleSheet(QString::fromUtf8(""));
        DLG_Home->setDocumentMode(false);
        DLG_Home->setTabShape(QTabWidget::Rounded);
        DLG_Home->setDockNestingEnabled(false);
        DLG_Home->setUnifiedTitleAndToolBarOnMac(false);
        actionNew_page = new QAction(DLG_Home);
        actionNew_page->setObjectName(QString::fromUtf8("actionNew_page"));
        actionNewPage = new QAction(DLG_Home);
        actionNewPage->setObjectName(QString::fromUtf8("actionNewPage"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-new-page.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNewPage->setIcon(icon1);
        actionSave = new QAction(DLG_Home);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionSave->setCheckable(false);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-file-up.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon2);
        actionLoad = new QAction(DLG_Home);
        actionLoad->setObjectName(QString::fromUtf8("actionLoad"));
        actionLoad->setIcon(icon2);
        actionPan = new QAction(DLG_Home);
        actionPan->setObjectName(QString::fromUtf8("actionPan"));
        actionDrag = new QAction(DLG_Home);
        actionDrag->setObjectName(QString::fromUtf8("actionDrag"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-drag.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDrag->setIcon(icon3);
        actionEdit = new QAction(DLG_Home);
        actionEdit->setObjectName(QString::fromUtf8("actionEdit"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-tool.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionEdit->setIcon(icon4);
        actionDelete = new QAction(DLG_Home);
        actionDelete->setObjectName(QString::fromUtf8("actionDelete"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-bin.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDelete->setIcon(icon5);
        actionLink = new QAction(DLG_Home);
        actionLink->setObjectName(QString::fromUtf8("actionLink"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-link-basic.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLink->setIcon(icon6);
        actionDelete_Link = new QAction(DLG_Home);
        actionDelete_Link->setObjectName(QString::fromUtf8("actionDelete_Link"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-link-delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDelete_Link->setIcon(icon7);
        actionZoom = new QAction(DLG_Home);
        actionZoom->setObjectName(QString::fromUtf8("actionZoom"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-zoom-in.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoom->setIcon(icon8);
        actionZoom_2 = new QAction(DLG_Home);
        actionZoom_2->setObjectName(QString::fromUtf8("actionZoom_2"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-zoom-out.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoom_2->setIcon(icon9);
        actionUndo = new QAction(DLG_Home);
        actionUndo->setObjectName(QString::fromUtf8("actionUndo"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-undo.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionUndo->setIcon(icon10);
        actionRedo = new QAction(DLG_Home);
        actionRedo->setObjectName(QString::fromUtf8("actionRedo"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-redo.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRedo->setIcon(icon11);
        actionNew_circuit_from_truth_table_task = new QAction(DLG_Home);
        actionNew_circuit_from_truth_table_task->setObjectName(QString::fromUtf8("actionNew_circuit_from_truth_table_task"));
        actionNew_truth_table_from_circuit_task = new QAction(DLG_Home);
        actionNew_truth_table_from_circuit_task->setObjectName(QString::fromUtf8("actionNew_truth_table_from_circuit_task"));
        actionCircuit_from_truth_table_task = new QAction(DLG_Home);
        actionCircuit_from_truth_table_task->setObjectName(QString::fromUtf8("actionCircuit_from_truth_table_task"));
        actionTruth_table_from_circuit_task = new QAction(DLG_Home);
        actionTruth_table_from_circuit_task->setObjectName(QString::fromUtf8("actionTruth_table_from_circuit_task"));
        actionView_Tasks = new QAction(DLG_Home);
        actionView_Tasks->setObjectName(QString::fromUtf8("actionView_Tasks"));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-tasks.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionView_Tasks->setIcon(icon12);
        centralwidget = new QWidget(DLG_Home);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        PlayField = new QTabWidget(centralwidget);
        PlayField->setObjectName(QString::fromUtf8("PlayField"));
        PlayField->setGeometry(QRect(160, 37, 805, 488));
        QFont font;
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        font.setStrikeOut(false);
        PlayField->setFont(font);
        PlayField->setMouseTracking(true);
        PlayField->setFocusPolicy(Qt::NoFocus);
        PlayField->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border:none;"));
        PlayField->setTabPosition(QTabWidget::North);
        PlayField->setTabShape(QTabWidget::Rounded);
        PlayField->setIconSize(QSize(5, 5));
        PlayField->setElideMode(Qt::ElideNone);
        PlayField->setUsesScrollButtons(true);
        PlayField->setDocumentMode(false);
        PlayField->setTabsClosable(true);
        PlayField->setMovable(false);
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
        btn_Drag->setGeometry(QRect(966, 110, 32, 32));
        btn_Drag->setStyleSheet(QString::fromUtf8(""));
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-pan.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_Drag->setIcon(icon13);
        btn_Drag->setIconSize(QSize(32, 32));
        btn_Drag->setAutoDefault(false);
        btn_Drag->setFlat(true);
        btn_Delete = new QPushButton(centralwidget);
        btn_Delete->setObjectName(QString::fromUtf8("btn_Delete"));
        btn_Delete->setGeometry(QRect(966, 230, 32, 32));
        btn_Delete->setStyleSheet(QString::fromUtf8(""));
        btn_Delete->setIcon(icon5);
        btn_Delete->setIconSize(QSize(32, 32));
        btn_Delete->setFlat(true);
        btn_DeleteLink = new QPushButton(centralwidget);
        btn_DeleteLink->setObjectName(QString::fromUtf8("btn_DeleteLink"));
        btn_DeleteLink->setGeometry(QRect(966, 270, 32, 32));
        btn_DeleteLink->setStyleSheet(QString::fromUtf8(""));
        btn_DeleteLink->setIcon(icon7);
        btn_DeleteLink->setIconSize(QSize(32, 32));
        btn_DeleteLink->setFlat(true);
        btn_click = new QPushButton(centralwidget);
        btn_click->setObjectName(QString::fromUtf8("btn_click"));
        btn_click->setGeometry(QRect(966, 190, 32, 32));
        btn_click->setStyleSheet(QString::fromUtf8(""));
        btn_click->setIcon(icon4);
        btn_click->setIconSize(QSize(30, 30));
        btn_click->setFlat(true);
        btn_zoomIn = new QPushButton(centralwidget);
        btn_zoomIn->setObjectName(QString::fromUtf8("btn_zoomIn"));
        btn_zoomIn->setGeometry(QRect(966, 35, 32, 32));
        btn_zoomIn->setStyleSheet(QString::fromUtf8(""));
        btn_zoomIn->setIcon(icon8);
        btn_zoomIn->setIconSize(QSize(30, 30));
        btn_zoomIn->setCheckable(false);
        btn_zoomIn->setFlat(true);
        btn_zoomOut = new QPushButton(centralwidget);
        btn_zoomOut->setObjectName(QString::fromUtf8("btn_zoomOut"));
        btn_zoomOut->setGeometry(QRect(966, 70, 32, 32));
        btn_zoomOut->setStyleSheet(QString::fromUtf8(""));
        btn_zoomOut->setIcon(icon9);
        btn_zoomOut->setIconSize(QSize(30, 30));
        btn_zoomOut->setFlat(true);
        btn_newPage = new QPushButton(centralwidget);
        btn_newPage->setObjectName(QString::fromUtf8("btn_newPage"));
        btn_newPage->setGeometry(QRect(170, 3, 24, 24));
        btn_newPage->setStyleSheet(QString::fromUtf8(""));
        btn_newPage->setIcon(icon1);
        btn_newPage->setIconSize(QSize(22, 22));
        btn_newPage->setFlat(true);
        btn_Pan = new QPushButton(centralwidget);
        btn_Pan->setObjectName(QString::fromUtf8("btn_Pan"));
        btn_Pan->setGeometry(QRect(966, 150, 32, 32));
        btn_Pan->setStyleSheet(QString::fromUtf8(""));
        btn_Pan->setIcon(icon3);
        btn_Pan->setIconSize(QSize(32, 32));
        btn_Pan->setFlat(true);
        btn_undo = new QPushButton(centralwidget);
        btn_undo->setObjectName(QString::fromUtf8("btn_undo"));
        btn_undo->setGeometry(QRect(300, 4, 24, 24));
        btn_undo->setAutoFillBackground(false);
        btn_undo->setStyleSheet(QString::fromUtf8(""));
        btn_undo->setIcon(icon10);
        btn_undo->setIconSize(QSize(24, 24));
        btn_undo->setFlat(true);
        btn_redo = new QPushButton(centralwidget);
        btn_redo->setObjectName(QString::fromUtf8("btn_redo"));
        btn_redo->setGeometry(QRect(270, 4, 24, 24));
        btn_redo->setStyleSheet(QString::fromUtf8(""));
        btn_redo->setIcon(icon11);
        btn_redo->setIconSize(QSize(24, 24));
        btn_redo->setFlat(true);
        layout_Dlg_GateInfo = new QWidget(centralwidget);
        layout_Dlg_GateInfo->setObjectName(QString::fromUtf8("layout_Dlg_GateInfo"));
        layout_Dlg_GateInfo->setGeometry(QRect(9, 350, 140, 175));
        layout_Dlg_GateInfo->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        widget_2 = new QWidget(centralwidget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setGeometry(QRect(160, 0, 841, 31));
        widget_2->setAutoFillBackground(false);
        widget_2->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 85, 85);"));
        btn_load = new QPushButton(widget_2);
        btn_load->setObjectName(QString::fromUtf8("btn_load"));
        btn_load->setGeometry(QRect(70, 3, 24, 24));
        btn_load->setLayoutDirection(Qt::LeftToRight);
        btn_load->setStyleSheet(QString::fromUtf8(""));
        btn_load->setIcon(icon2);
        btn_load->setIconSize(QSize(24, 24));
        btn_load->setFlat(true);
        line_3 = new QFrame(widget_2);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setGeometry(QRect(92, 5, 20, 21));
        line_3->setAutoFillBackground(false);
        line_3->setStyleSheet(QString::fromUtf8("color:rgb(255, 255, 255);"));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);
        line_5 = new QFrame(widget_2);
        line_5->setObjectName(QString::fromUtf8("line_5"));
        line_5->setGeometry(QRect(-9, 5, 20, 21));
        line_5->setAutoFillBackground(false);
        line_5->setStyleSheet(QString::fromUtf8("color:rgb(255, 255, 255);"));
        line_5->setFrameShape(QFrame::VLine);
        line_5->setFrameShadow(QFrame::Sunken);
        line_6 = new QFrame(widget_2);
        line_6->setObjectName(QString::fromUtf8("line_6"));
        line_6->setGeometry(QRect(160, 5, 20, 21));
        line_6->setAutoFillBackground(false);
        line_6->setStyleSheet(QString::fromUtf8("color:rgb(255, 255, 255);"));
        line_6->setFrameShape(QFrame::VLine);
        line_6->setFrameShadow(QFrame::Sunken);
        line_8 = new QFrame(widget_2);
        line_8->setObjectName(QString::fromUtf8("line_8"));
        line_8->setGeometry(QRect(680, 5, 20, 21));
        line_8->setContextMenuPolicy(Qt::NoContextMenu);
        line_8->setAutoFillBackground(false);
        line_8->setStyleSheet(QString::fromUtf8("color:rgb(255, 255, 255);"));
        line_8->setFrameShape(QFrame::VLine);
        line_8->setFrameShadow(QFrame::Sunken);
        btn_Save = new QPushButton(widget_2);
        btn_Save->setObjectName(QString::fromUtf8("btn_Save"));
        btn_Save->setGeometry(QRect(40, 3, 24, 24));
        btn_Save->setStyleSheet(QString::fromUtf8(""));
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/Resources/Button Icons/icon-file-down.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_Save->setIcon(icon14);
        btn_Save->setIconSize(QSize(24, 24));
        btn_Save->setFlat(true);
        btn_tasks = new QPushButton(widget_2);
        btn_tasks->setObjectName(QString::fromUtf8("btn_tasks"));
        btn_tasks->setGeometry(QRect(175, 3, 24, 24));
        btn_tasks->setAutoFillBackground(false);
        btn_tasks->setStyleSheet(QString::fromUtf8(""));
        btn_tasks->setIcon(icon12);
        btn_tasks->setIconSize(QSize(24, 24));
        btn_tasks->setFlat(true);
        widget_4 = new QWidget(centralwidget);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        widget_4->setGeometry(QRect(0, 31, 1001, 510));
        widget_4->setAutoFillBackground(false);
        widget_4->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 85, 85);"));
        comboBox = new QComboBox(centralwidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(0, 0, 160, 31));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy);
        comboBox->setFont(font);
        comboBox->setFocusPolicy(Qt::NoFocus);
        comboBox->setContextMenuPolicy(Qt::NoContextMenu);
        comboBox->setAutoFillBackground(false);
        comboBox->setStyleSheet(QString::fromUtf8("QComboBox {\n"
"	background-color: rgb(85, 85, 85);\n"
"	border:none;\n"
"    color: black;\n"
"    font: 15px;\n"
"    padding: 5px 5px 5px 20px; /* This (useless) line resolves a bug with the font color */\n"
"}\n"
"\n"
"QComboBox:focus {\n"
"    color: black;\n"
"}\n"
"\n"
"QComboBox::drop-down \n"
"{\n"
"    border: 0px; /* This seems to replace the whole arrow of the combo box */\n"
"}\n"
"\n"
"Define a new custom arrow icon for the combo box \n"
"QComboBox::down-arrow {\n"
"    image: url(Resources/empty.png);\n"
"    width: 14px;\n"
"    height: 14px;\n"
"}"));
        comboBox->setEditable(false);
        comboBox->setIconSize(QSize(16, 60));
        layout_GateWidget = new QWidget(centralwidget);
        layout_GateWidget->setObjectName(QString::fromUtf8("layout_GateWidget"));
        layout_GateWidget->setGeometry(QRect(9, 39, 140, 301));
        layout_GateWidget->setMouseTracking(true);
        layout_GateWidget->setStyleSheet(QString::fromUtf8("background-color:rgb(255, 255, 255);"));
        layout_ZoomSlider = new QWidget(centralwidget);
        layout_ZoomSlider->setObjectName(QString::fromUtf8("layout_ZoomSlider"));
        layout_ZoomSlider->setGeometry(QRect(850, 0, 151, 31));
        layout_ZoomSlider->setAutoFillBackground(false);
        DLG_Home->setCentralWidget(centralwidget);
        widget_2->raise();
        widget_4->raise();
        btn_Drag->raise();
        btn_Delete->raise();
        btn_DeleteLink->raise();
        btn_click->raise();
        btn_zoomIn->raise();
        btn_zoomOut->raise();
        btn_newPage->raise();
        btn_Pan->raise();
        btn_undo->raise();
        btn_redo->raise();
        layout_Dlg_GateInfo->raise();
        PlayField->raise();
        comboBox->raise();
        layout_GateWidget->raise();
        layout_ZoomSlider->raise();
        menuBar = new QMenuBar(DLG_Home);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1000, 21));
        menuBar->setStyleSheet(QString::fromUtf8("background-color: rgb(120, 120, 120);"));
        menuBar->setDefaultUp(false);
        menuBar->setNativeMenuBar(true);
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuNew_task = new QMenu(menuFile);
        menuNew_task->setObjectName(QString::fromUtf8("menuNew_task"));
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QString::fromUtf8("menuTools"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        DLG_Home->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuTools->menuAction());
        menuFile->addAction(actionNewPage);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionLoad);
        menuFile->addAction(menuNew_task->menuAction());
        menuFile->addAction(actionView_Tasks);
        menuNew_task->addAction(actionCircuit_from_truth_table_task);
        menuNew_task->addAction(actionTruth_table_from_circuit_task);
        menuTools->addAction(actionPan);
        menuTools->addAction(actionDrag);
        menuTools->addAction(actionEdit);
        menuTools->addAction(actionDelete);
        menuTools->addAction(actionLink);
        menuTools->addAction(actionDelete_Link);
        menuTools->addAction(actionZoom);
        menuTools->addAction(actionZoom_2);
        menuEdit->addAction(actionUndo);
        menuEdit->addAction(actionRedo);

        retranslateUi(DLG_Home);

        PlayField->setCurrentIndex(0);
        btn_Drag->setDefault(false);


        QMetaObject::connectSlotsByName(DLG_Home);
    } // setupUi

    void retranslateUi(QMainWindow *DLG_Home)
    {
        DLG_Home->setWindowTitle(QString());
        actionNew_page->setText(QCoreApplication::translate("DLG_Home", "New page", nullptr));
        actionNewPage->setText(QCoreApplication::translate("DLG_Home", "New page", nullptr));
        actionSave->setText(QCoreApplication::translate("DLG_Home", "Save", nullptr));
        actionLoad->setText(QCoreApplication::translate("DLG_Home", "Load", nullptr));
        actionPan->setText(QCoreApplication::translate("DLG_Home", "Pan", nullptr));
        actionDrag->setText(QCoreApplication::translate("DLG_Home", "Drag", nullptr));
        actionEdit->setText(QCoreApplication::translate("DLG_Home", "Edit", nullptr));
        actionDelete->setText(QCoreApplication::translate("DLG_Home", "Delete", nullptr));
        actionLink->setText(QCoreApplication::translate("DLG_Home", "Link", nullptr));
        actionDelete_Link->setText(QCoreApplication::translate("DLG_Home", "Delete Link", nullptr));
        actionZoom->setText(QCoreApplication::translate("DLG_Home", "Zoom +", nullptr));
        actionZoom_2->setText(QCoreApplication::translate("DLG_Home", "Zoom -", nullptr));
        actionUndo->setText(QCoreApplication::translate("DLG_Home", "Undo", nullptr));
        actionRedo->setText(QCoreApplication::translate("DLG_Home", "Redo", nullptr));
        actionNew_circuit_from_truth_table_task->setText(QCoreApplication::translate("DLG_Home", "New Circuit from truth table task", nullptr));
        actionNew_truth_table_from_circuit_task->setText(QCoreApplication::translate("DLG_Home", "New ", nullptr));
        actionCircuit_from_truth_table_task->setText(QCoreApplication::translate("DLG_Home", "Circuit from truth table task", nullptr));
        actionTruth_table_from_circuit_task->setText(QCoreApplication::translate("DLG_Home", "Truth table from circuit task", nullptr));
        actionView_Tasks->setText(QCoreApplication::translate("DLG_Home", "View Tasks", nullptr));
        PlayField->setTabText(PlayField->indexOf(widget), QCoreApplication::translate("DLG_Home", "Page", nullptr));
        PlayField->setTabText(PlayField->indexOf(tab), QCoreApplication::translate("DLG_Home", "Page 1", nullptr));
        PlayField->setTabText(PlayField->indexOf(tab2), QCoreApplication::translate("DLG_Home", "Page 2", nullptr));
        btn_Drag->setText(QString());
        btn_Delete->setText(QString());
        btn_DeleteLink->setText(QString());
        btn_click->setText(QString());
        btn_zoomIn->setText(QString());
        btn_zoomOut->setText(QString());
        btn_newPage->setText(QString());
        btn_Pan->setText(QString());
        btn_undo->setText(QString());
        btn_redo->setText(QString());
        btn_load->setText(QString());
        btn_Save->setText(QString());
        btn_tasks->setText(QString());
        comboBox->setItemText(0, QCoreApplication::translate("DLG_Home", "All", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("DLG_Home", "Standard", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("DLG_Home", "Custom", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("DLG_Home", "Input", nullptr));
        comboBox->setItemText(4, QCoreApplication::translate("DLG_Home", "Advanced", nullptr));

        menuFile->setTitle(QCoreApplication::translate("DLG_Home", "File", nullptr));
        menuNew_task->setTitle(QCoreApplication::translate("DLG_Home", "New task", nullptr));
        menuTools->setTitle(QCoreApplication::translate("DLG_Home", "Tools", nullptr));
        menuEdit->setTitle(QCoreApplication::translate("DLG_Home", "Edit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DLG_Home: public Ui_DLG_Home {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLG_HOME_H
