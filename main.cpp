#include <QCoreApplication>
#include "SharingFramework.h"

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    QObject parent;
    SharingFramework frame(&parent, "service.Test", "/service/Test");

    return app.exec();
}
