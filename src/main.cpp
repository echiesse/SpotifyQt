#include "mainwindow.h"
#include <QApplication>
#include "Config.h"

Config config("config.cfg");
Config appState("app.data");

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
