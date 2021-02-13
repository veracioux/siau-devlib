#ifndef VALUE_H
#define VALUE_H

#include "devlib_global.h"

#include <QList>
#include <QString>
#include <QMap>

class DEVLIB_EXPORT Value
{
    QMap<QString, QString> attr = {
        {"name", ""},
        {"friendly", ""},
        {"valueType", ""}
    };
    QList<QString> valueRange;
};

#endif // VALUE_H
