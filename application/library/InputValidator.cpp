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
Response InputValidator::validateFilePath(const QString& filePath, const QStringList& formatList) {
    QRegularExpression regex("\\.([^.]+)$");
    QRegularExpressionMatch match = regex.match(filePath);
    if (!match.hasMatch()) {
        return Response{false, "The format of this file is not supported"};
    }
    QString format = match.captured(1);

    QStringList formatsWithoutDot;
    for (const QString& formatInList : formatList) {
        formatsWithoutDot << formatInList.mid(1);
    }

    if (!formatsWithoutDot.contains(format, Qt::CaseInsensitive)) {
        return Response{false, "The format of this file is not supported"};
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
