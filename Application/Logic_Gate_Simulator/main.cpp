#include "mainwindow.h"
#include "dlg_home.h"
#include "dlg_load.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DLG_Load loadScreen;
    loadScreen.show();

    return a.exec();
}

/*
int winmain()
{
}


INT WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    PSTR lpCmdLine, INT nCmdShow)
{
    return 0;
}
 */
