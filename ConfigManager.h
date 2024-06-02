#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include "Validator.h"
#include <QDir>
#include <QSet>
#include <QSettings>
#include <QObject>

const QString CONFIG_FORMATS = "General/SupportedFileTypes";

class ConfigManager : public QObject {
    Q_OBJECT
public:
    explicit ConfigManager(const QString& filePath = "formats.conf", QObject *parent = nullptr);

    void createConfiguration(const QStringList& formatList);
    Response registerFormats(const QStringList& formatList);
    Response addFormat(const QString& format);
    Response deleteFormat(const QString& format);
    Response loadConfiguration(QStringList& formatList);
    bool isConfCreated() const;

signals:
    void messageSignal(const QString& message);

private:
    QString m_filePath;
    QSet<QString> m_formatList;
    QSettings m_settings;
    InputValidator validator;
    bool m_isConfCreated = false;
};

#endif // CONFIGMANAGER_H
