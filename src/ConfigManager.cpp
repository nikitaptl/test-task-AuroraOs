#include "ConfigManager.h"

ConfigManager::ConfigManager(const QString& filePath, QObject *parent) :
    QObject(parent),
    m_filePath(filePath + "/formats.conf"),
    m_settings(new QSettings(m_filePath, QSettings::IniFormat)) {
}

Response ConfigManager::loadConfiguration(QStringList& formatList) {
    if (!m_settings->contains(CONFIG_FORMATS) && QFile(m_filePath).exists()) {
        emit messageSignal("The configuration file is missing CONFIG_FORMATS key");
    }

    formatList = m_settings->value(CONFIG_FORMATS).toString().split(",");
    if(!formatList.empty()) {
        m_formatList = validator.listToSet(formatList);
        return Response();
    }
    emit messageSignal("The configuration file has not been created yet. Wait for registration");
    return Response{false, "The configuration file has not been created yet"};
}

Response ConfigManager::registerFormats(const QStringList& formatList) {
    m_formatList = validator.listToSet(formatList);
    Response response;
    if (auto [is_successful, message] = validator.validateFormatList(m_formatList); !is_successful) {
        emit messageSignal(message);
        response.message = "WARNING: one of the registered formats "
                           "does not meet the requirements for naming formats";
    }
    m_settings->clear();
    m_settings->setValue(CONFIG_FORMATS, validator.setToList(m_formatList).join(","));
    if (m_settings->status() == QSettings::NoError) {
        return response;
    }
    emit messageSignal("Failed to write configuration");
    return Response{false, "Failed to write configuration"};
}

Response ConfigManager::addFormat(const QString& format) {
    Response response;
    if (auto [is_successful, message] = validator.validateFormat(format); !is_successful) {
        emit messageSignal(message);
        response.message = "WARNING: " + format
                           + " does not meet the requirements for naming formats";
    }

    if (m_formatList.contains(format)) {
        emit messageSignal("Format already exists");
        return Response{false, "Format already exists"};
    }

    m_formatList.insert(format);
    m_settings->setValue(CONFIG_FORMATS, validator.setToList(m_formatList).join(","));
    if (m_settings->status() == QSettings::NoError) {
        return Response();
    }
    emit messageSignal("Failed to write configuration");
    return Response{false, "Failed to write configuration"};
}

Response ConfigManager::deleteFormat(const QString& format) {
    if (!m_formatList.contains(format)) {
        emit messageSignal("Format not found");
        return Response{false, "Format not found"};
    }
    m_formatList.remove(format);
    m_settings->setValue(CONFIG_FORMATS, validator.setToList(m_formatList).join(","));
    if (m_settings->status() == QSettings::NoError) {
        return Response();
    }
    emit messageSignal("Failed to write configuration");
    return Response{false, "Failed to write configuration"};
}

void ConfigManager::setPath(const QString& path) {
    m_filePath = path + "/formats.conf";
    m_settings.reset(new QSettings(m_filePath, QSettings::IniFormat));
}

