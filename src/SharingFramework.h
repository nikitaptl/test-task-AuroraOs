#ifndef SHARINGFRAMEWORK_H
#define SHARINGFRAMEWORK_H

#include <QDBusAbstractAdaptor>
#include <QString>
#include <QStringList>
#include "ConfigManager.h"
#include "Validator.h"
#include "ServiceException.h"

class SharingFramework : public QDBusAbstractAdaptor {
    Q_OBJECT
public:
    SharingFramework(QObject *parent, QString nameService, QString pathService, QString pathExecutable);
    QStringList formatList() const;
    QString registerFormats(QStringList formatList);
    QString addFormat(QString format);
    QString deleteFormat(QString format);
    QStringList GetSupportedFileTypes();
    QString createServiceFile();
    QString createServiceFile(QStringList args);
    QString openFile(QString path);
    void stop();

signals:
    void newFile(QString path);
    void stopRequested();

private:
    void writeMessage(const QString& message);

    QString m_nameService;
    QString m_pathService;
    QString m_pathExecutable;
    QString m_path;
    QStringList m_formatList;
    ConfigManager configManager;
    InputValidator validator;
};

#endif // SHARINGFRAMEWORK_H
