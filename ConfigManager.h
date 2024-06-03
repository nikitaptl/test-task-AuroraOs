#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include "Validator.h"
#include <QDir>
#include <QSet>
#include <QSettings>
#include <QObject>
#include <QScopedPointer>

const QString CONFIG_FORMATS = "General/SupportedFileTypes";

class ConfigManager : public QObject {
    Q_OBJECT
public:
    explicit ConfigManager(const QString& filePath = QDir::currentPath(), QObject *parent = nullptr);

    void createConfiguration(const QStringList& formatList);
    Response registerFormats(const QStringList& formatList);
    Response addFormat(const QString& format);
    Response deleteFormat(const QString& format);
    Response loadConfiguration(QStringList& formatList);
    void setPath(const QString& format);

signals:
    void messageSignal(const QString& message);

public:
    QString m_filePath;
    QSet<QString> m_formatList;
    QScopedPointer<QSettings> m_settings;
    InputValidator validator;
};

#endif // CONFIGMANAGER_H

