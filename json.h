/** @file json.h */
#ifndef JSON_H
#define JSON_H

#include "devlib_global.h"

#include "device.h"
#include "function.h"
#include "data.h"

#include <QJsonObject>

/**
 * Parse the contents of 'factory_device.json' and 'user_device.json' and
 * return a `Device` object.
 *
 * The file user_device is optional. If it is unspecified or empty, the
 * corresponding attributes of the returned object will have their default
 * values.
 */
Device DEVLIB_EXPORT jsonParseDevice(const QString &factoryFile,
                                     const QString &userFile = "");
Data DEVLIB_EXPORT jsonParseValue(const QJsonObject &val);
Condition DEVLIB_EXPORT jsonParseCondition(const QJsonObject &val);
Function DEVLIB_EXPORT jsonParseFunction(const QJsonObject &func);

#endif // JSON_H
