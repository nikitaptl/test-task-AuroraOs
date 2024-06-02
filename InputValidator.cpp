#include "Validator.h"
#include <QSet>

InputValidator::InputValidator() : regexFormat("^\\.[a-zA-Z0-9]+$") {
}

Response InputValidator::validateFormat(const QString& formatName) {
    if(!regexFormat.match(formatName).hasMatch()) {
        QString errorMessage = "Format name \"" + formatName + "\" does not match the format naming requirements";
        return Response{false, errorMessage};
    }
    return Response();
}

Response InputValidator::validateFormatList(const QSet<QString>& formatList) {
    for (const QString &formatName : formatList) {
        if(!regexFormat.match(formatName).hasMatch()) {
            QString errorMessage = "Format name \"" + formatName + "\" does not match the format naming requirements";
            return Response{false, errorMessage};
        }
    }
    return Response();
}

QSet<QString> InputValidator::listToSet(const QStringList& list) {
    QSet<QString> uniqueSet;
    for (const QString &str : list) {
        uniqueSet.insert(str);
    }
    return uniqueSet;
}

QStringList InputValidator::setToList(const QSet<QString>& set) {
    QStringList list;
    for (const QString& str : set) {
        list << str;
    }
    return list;
}
