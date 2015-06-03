// includes from QT
#include <QApplication>

// includes from other modules
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // display the main window
    MainWindow w;
    w.show();

    return a.exec();
}
