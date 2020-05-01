#include "mainwindow.h"
#include "dlg_home.h"
#include "dlg_load.h"
#include <QApplication>
#include "Tests/unit_tests.h"

int main(int argc, char *argv[])
{
    UnitTests* ut = new UnitTests();
    QTest::qExec(ut);

    QApplication a(argc, argv);

    DLG_Load loadScreen;
    loadScreen.show();

    return a.exec();
}

int winmain()
{
    UnitTests* ut = new UnitTests();
    QTest::qExec(ut);

}

/*
INT WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    PSTR lpCmdLine, INT nCmdShow)
{
    return 0;
}
 */
