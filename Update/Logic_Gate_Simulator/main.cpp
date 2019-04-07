#include "mainwindow.h"
#include "dlg_home.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    DLG_Home home;
    home.show();

    return a.exec();
}
