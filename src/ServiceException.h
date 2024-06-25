#ifndef SERVICEEXCEPTION_H
#define SERVICEEXCEPTION_H

#include <QException>
#include <QString>

class ServiceException : public QException {
public:
    void raise() const override { throw *this; }
    ServiceException *clone() const override { return new ServiceException(*this); }
    ServiceException(const QString& message) : msg(message) {}
    const char *what() const noexcept override { return msg.toLocal8Bit().constData(); }
private:
    QString msg;
};

#endif // SERVICEEXCEPTION_H
