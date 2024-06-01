#include "SharingFramework.h"
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusConnectionInterface>
#include <QFile>

extern SharingFramework::SharingFramework(QObject *parent, QString nameService, QString pathService) : QDBusAbstractAdaptor(parent) {
    m_nameService = nameService;
    m_pathService = pathService;
    QDBusConnection dbusConnection = QDBusConnection::sessionBus();
    if(!dbusConnection.interface()->isServiceRegistered(nameService)) {
        dbusConnection.registerObject(pathService, parent);
        dbusConnection.registerService(nameService);
        qDebug() << "New service is started";
    }
    else {
        qDebug() << "Service already exists";
    }
}

QStringList SharingFramework::formatList() const {
    return m_formatList;
}

void SharingFramework::registerFormats(QStringList stringList) {
    if(m_formatList == stringList) {
        return;
    }
    m_formatList = stringList;
    emit formatsChanged(stringList);
}

void SharingFramework::addFormat(QString format) {
    if(m_formatList.contains(format)) {
        qDebug() << "This format is already registered";
    }
    m_formatList.append(format);
}

void SharingFramework::registerLaunchDBus(QString name, QString pathExec) {
    QString filePath = "/usr/share/dbus-1/services/my_service.service";
    QFile serviceFile(filePath);

    if(!serviceFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qCritical() << "Failed to open .service file";
        return;
    }

    QTextStream out(&serviceFile);
    out << "[D-BUS Service]" << Qt::endl;
    out << "Name=" << name << Qt::endl;
    out << "Exec=" << pathExec << Qt::endl;
    serviceFile.close();

    qDebug() << "Service file created successfully";
}
