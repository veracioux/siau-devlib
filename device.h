/** @file device.h */
#ifndef DEVICE_H
#define DEVICE_H

#include "devlib_global.h"
#include "data.h"
#include "function.h"

#include <QString>
#include <QMap>
#include <QList>

class DEVLIB_EXPORT Device
{
    QString name, vendorId, deviceId;
    QList<Data> values;
    QList<Function> functions;
};

#endif // DEVICE_H
