#include "SharingFramework.h"
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusConnectionInterface>
#include <QFile>

SharingFramework::SharingFramework(QObject *parent, QString nameService,
                                   QString pathService, QString pathExecutable) :
    QDBusAbstractAdaptor(parent), m_nameService(nameService),
    m_pathService(pathService), m_pathExecutable(pathExecutable)
{
    QDir dir(pathExecutable);
    dir.cdUp();
    configManager.setPath(dir.absolutePath());

    QDBusConnection dbusConnection = QDBusConnection::sessionBus();
    if(dbusConnection.interface()->isServiceRegistered(nameService)) {
        writeMessage("The service has already been launched");
        exit(1);
    }
    dbusConnection.registerObject(pathService, parent);
    dbusConnection.registerService(nameService);
    writeMessage("New service is registered!");
    configManager.loadConfiguration(m_formatList);
    connect(&configManager, &ConfigManager::messageSignal, this, &SharingFramework::writeMessage);
}

QStringList SharingFramework::formatList() const {
    return m_formatList;
}

QString SharingFramework::registerFormats(QStringList formatList) {
    if(const auto& [is_successful, message] = configManager.registerFormats(formatList); !is_successful) {
        writeMessage(message);
        return message;
    }
    return "The formats were successfully registered";
}

QString SharingFramework::addFormat(QString format) {
    if(const auto& [is_successful, message] = configManager.addFormat(format); !is_successful) {
        writeMessage(message);
        return message;
    }
    return "The new format has been successfully added";
}

QString SharingFramework::deleteFormat(QString format) {
    if(const auto& [is_successful, message] = configManager.deleteFormat(format); !is_successful) {
        writeMessage(message);
        return message;
    }
    return "The format has been successfully deleted";
}

QStringList SharingFramework::GetSupportedFileTypes() {
    if(const auto& [is_successful, message] = configManager.loadConfiguration(m_formatList); !is_successful) {
        writeMessage(message);
        return QStringList{message};
    }
    return m_formatList;
}

void SharingFramework::writeMessage(const QString& message) {
    qDebug() << message;
}

QString SharingFramework::createServiceFile() {
    return createServiceFile(QStringList{m_nameService, m_pathExecutable});
}

QString SharingFramework::createServiceFile(QStringList args) {
    if(args.size() != 2) {
        writeMessage("Incorrect number of arguments. Enter the name of the service and the path to the executable file");
        return "Incorrect number of arguments. Enter the name of the service and the path to the executable file";
    }
    QString name = args[0];
    QString pathExec = args[1];
    QDir dir(m_pathExecutable);
    dir.cdUp();
    QFile serviceFile(dir.absolutePath() + "/" + name + ".service");

    if(!serviceFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qCritical() << "Failed to open .service file";
        writeMessage("Failed to open .service file");
    }

    QTextStream out(&serviceFile);
    out << "[D-BUS Service]" << Qt::endl;
    out << "Name=" << name << Qt::endl;
    out << "Exec=" << pathExec << Qt::endl;
    serviceFile.close();

    QString message = "Now you can use command \"sudo mv " + name +
                      ".service" + " /usr/share/dbus-1/services\" to register the launch of the program in the system ";
    writeMessage(".service file created successfully");
    writeMessage(message);
    return ".service file created successfully. " + message;
}

QString SharingFramework::openFile(QString path) {
    if(const auto& [is_successful, message] = configManager.loadConfiguration(m_formatList); !is_successful) {
        writeMessage(message);
        return message;
    }
    if(const auto& [is_successful, message] = validator.validateFilePath(path, m_formatList); !is_successful) {
        writeMessage(message);
        return message;
    }
    m_path = path;
    writeMessage("The application has successfully received the file for processing");
    emit newFile(path);
    return "The application has successfully received the file for processing";
}

void SharingFramework::stop() {
    exit(1);
}
