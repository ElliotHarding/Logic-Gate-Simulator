#include "dlg_load.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DLG_Load loadScreen;
    loadScreen.show();

    return a.exec();
}
