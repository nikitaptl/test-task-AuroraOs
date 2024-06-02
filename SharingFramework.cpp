#include "SharingFramework.h"
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusConnectionInterface>
#include <QFile>

SharingFramework::SharingFramework(QObject *parent, QString nameService, QString pathService) : QDBusAbstractAdaptor(parent) {
    m_nameService = nameService;
    m_pathService = pathService;
    QDBusConnection dbusConnection = QDBusConnection::sessionBus();

    if(dbusConnection.interface()->isServiceRegistered(nameService)) {
        qDebug() << "The service has already been launched";
        exit(1);
    }
    dbusConnection.registerObject(pathService, parent);
    dbusConnection.registerService(nameService);
    qDebug() << "New service is registered!";
    configManager.loadConfiguration(m_formatList);
    connect(&configManager, &ConfigManager::messageSignal, this, &SharingFramework::writeMessage);
}

QStringList SharingFramework::formatList() const {
    return m_formatList;
}

QString SharingFramework::registerFormats(QStringList formatList) {
    Response response = configManager.registerFormats(formatList);
    if (!response.is_successful) {
        qDebug() << response.message;
    }
    return "The formats were successfully registered";
}

QString SharingFramework::addFormat(QString format) {
    Response response = configManager.addFormat(format);
    if (!response.is_successful) {
        qDebug() << response.message;
        return response.message;
    }
    return "The new format has been successfully added";
}

QString SharingFramework::deleteFormat(QString format) {
    Response response = configManager.deleteFormat(format);
    if (!response.is_successful) {
        qDebug() << response.message;
        return response.message;
    }
    return "The format has been successfully deleted";
}

QStringList SharingFramework::GetSupportedFileTypes() {
    configManager.loadConfiguration(m_formatList);
    return m_formatList;
}

void SharingFramework::writeMessage(const QString& message) {
    qDebug() << message;
}

QString SharingFramework::registerLaunchDBus(QStringList args) {
    if(args.size() != 2) {
        return "Incorrect number of arguments";
    }
    QString name = args[0];
    QString pathExec = args[1];
    QFile serviceFile(name + ".service");

    if(!serviceFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qCritical() << "Failed to open .service file";
        return "Failed to open .service file";
    }

    QTextStream out(&serviceFile);
    out << "[D-BUS Service]" << Qt::endl;
    out << "Name=" << name << Qt::endl;
    out << "Exec=" << pathExec << Qt::endl;
    serviceFile.close();

    qDebug() << "Service file created successfully";
    return "Service file created successfully";
}
