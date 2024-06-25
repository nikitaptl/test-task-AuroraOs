#include "mainwindow.h"
#include <QApplication>
#include <QtDBus/QDBusConnection>
#include "library/SharingFramework.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    SharingFramework sharingFramework(&w, "txt.Handler", "/txt/Handler", "/home/nikita_ptl/Qt/test-task-AuroraOs/application");
    QObject::connect(&sharingFramework, &SharingFramework::newFile, &w, &MainWindow::handleNewFile);

    w.show();
    return a.exec();
}
