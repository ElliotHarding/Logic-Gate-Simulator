#include "mainwindow.h"
#include "Dialogs/dlg_home.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DLG_Home home;
    home.show();

    return a.exec();
}
