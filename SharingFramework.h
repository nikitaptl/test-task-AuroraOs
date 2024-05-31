#ifndef SHARINGFRAMEWORK_H
#define SHARINGFRAMEWORK_H

#include <QStringList>
#include <QtDBus>
#include <QDebug>
#include <iostream>

class SharingFramework : public QDBusAbstractAdaptor {
    Q_OBJECT
    Q_PROPERTY(QStringList formatList READ formatList WRITE registerFormats NOTIFY formatsChanged)
    Q_CLASSINFO("D-Bus Interface", "service.Test")

public:
    explicit SharingFramework(QObject *parent, QString nameService, QString pathService);
    QStringList formatList() const;

public slots:
    void registerFormats(QStringList stringList);

signals:
    void formatsChanged(QStringList stringList);

public:
    QStringList m_formatList;
    QString m_nameService, m_pathService;
};

#endif // SHARINGFRAMEWORK_H

