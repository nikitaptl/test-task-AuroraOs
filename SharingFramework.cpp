#include "SharingFramework.h"
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusConnectionInterface>

SharingFramework::SharingFramework(QObject *parent, QString nameService, QString pathService) : QDBusAbstractAdaptor(parent) {
    m_nameService = nameService;
    m_pathService = pathService;
    QDBusConnection dbusConnection = QDBusConnection::sessionBus();
    if(!dbusConnection.interface()->isServiceRegistered(nameService)) {
        dbusConnection.registerObject(pathService, parent);
        dbusConnection.registerService(nameService);
        qDebug() << "New service is created!";
    }
    else {
        qDebug() << "Service already exists";
    }
}

void SharingFramework::registerFormats(QStringList stringList) {
    if(m_formatList == stringList) {
        return;
    }
    m_formatList = stringList;
    emit formatsChanged(stringList);
}

QStringList SharingFramework::formatList() const {
    return m_formatList;
}


