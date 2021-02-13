#ifndef DEVICE_H
#define DEVICE_H

#include "devlib_global.h"
#include "value.h"
#include "function.h"

#include <QString>
#include <QMap>
#include <QList>

struct DEVLIB_EXPORT Device
{
    QString name, vendorId, deviceId;
    QMap<QString, QString> attr = {
        {"name", ""},
        {"vendorId", ""},
        {"deviceId", ""},
    };
    QList<Value> values;
    QList<Function> functions;
};

#endif // DEVICE_H
