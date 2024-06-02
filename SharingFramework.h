#include <QStringList>
#include <QtDBus/QDBusAbstractAdaptor>
#include <QDebug>
#include <QSettings>
#include "ConfigManager.h"

#ifndef SHARINGFRAMEWORK_H
#define SHARINGFRAMEWORK_H

class SharingFramework : public QDBusAbstractAdaptor {
    Q_OBJECT
    Q_PROPERTY(QStringList formatList READ formatList WRITE registerFormats NOTIFY formatsChanged)
    Q_CLASSINFO("D-Bus Interface", "dbus.application")

public:
    explicit SharingFramework(QObject *parent, QString nameService, QString pathService);
    QStringList formatList() const;

public slots:
    QString registerFormats(QStringList formatList);
    QString addFormat(QString format);
    QString deleteFormat(QString format);
    QStringList GetSupportedFileTypes();
    void writeMessage(const QString& message);
    QString registerLaunchDBus(QStringList args);
    // QString openFile(const QStringList &args);

signals:
    void formatsChanged(QStringList formatList);
    void launchRegistered();

private:
    QString m_nameService, m_pathService;
    QStringList m_formatList;
    ConfigManager configManager;
};

#endif // SHARINGFRAMEWORK_H
