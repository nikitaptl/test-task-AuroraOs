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
    explicit SharingFramework(QObject *parent, QString nameService,
                              QString pathService, QString pathExecutable);
    QStringList formatList() const;
    QString path() const;

public slots:
    QString registerFormats(QStringList formatList);
    QString addFormat(QString format);
    QString deleteFormat(QString format);
    QStringList GetSupportedFileTypes();
    QString createServiceFile();
    QString createServiceFile(QStringList args);
    QString openFile(QString path);
    void stop();

private slots:
    void writeMessage(const QString& message);

signals:
    void formatsChanged(QStringList formatList);
    void newFile(QString path);

private:
    QString m_pathExecutable, m_nameService, m_pathService;
    QStringList m_formatList;
    ConfigManager configManager;
    QString m_path;
    InputValidator validator;
};

#endif // SHARINGFRAMEWORK_H

