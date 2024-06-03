#include <QCoreApplication>
#include "SharingFramework.h"

const QString execPath = "/home/nikita_ptl/Qt/test-task-AuroraOs/build/Default_bro-Debug";

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    QObject parent;
    SharingFramework frame(&parent, "application.Timer", "/application/Timer", argv[0]);
    return app.exec();
}
