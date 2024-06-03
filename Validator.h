#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <QString>
#include <QRegularExpression>

struct Response {
    bool is_successful = true;
    QString message;
};

class InputValidator {
public:
    InputValidator();
    Response validateFormat(const QString& formatName);
    Response validateFormatList(const QSet<QString>& formatList);
    Response validateFilePath(const QString& filePath, const QStringList& formatList);
    QSet<QString> listToSet(const QStringList& list);
    QStringList setToList(const QSet<QString>& set);
private:
    QRegularExpression regexFormat;
};

#endif // VALIDATOR_H
