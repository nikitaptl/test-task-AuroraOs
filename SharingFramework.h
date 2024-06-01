#include <QStringList>
#include <QtDBus/QDBusAbstractAdaptor>
#include <QDebug>

#ifndef SHARINGFRAMEWORK_H
#define SHARINGFRAMEWORK_H

class SharingFramework : public QDBusAbstractAdaptor {
    Q_OBJECT
    Q_PROPERTY(QStringList formatList READ formatList WRITE registerFormats NOTIFY formatsChanged)
    Q_CLASSINFO("D-Bus Interface", "service.Test")

public:
    explicit SharingFramework(QObject *parent, QString nameService, QString pathService);
    QStringList formatList() const;

public slots:
    void registerFormats(QStringList formatList);
    void addFormat(QString format);
    void registerLaunchDBus(QString name, QString exec);

signals:
    void formatsChanged(QStringList formatList);
    void launchRegistered();

private:
    QStringList m_formatList;
    QString m_nameService, m_pathService;
};

#endif // SHARINGFRAMEWORK_H


