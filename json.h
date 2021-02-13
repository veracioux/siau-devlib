#ifndef JSON_H
#define JSON_H

#include "devlib_global.h"

#include "device.h"
#include "function.h"
#include "value.h"

#include <QJsonObject>

/**
 * @brief Parse the contents of 'factory_device.json' and 'user_device.json'
 * and return a `Device` object.
 *
 * The file user_device is optional. If it is unspecified or empty, the
 * corresponding attributes returned object will have their default values.
 */
DEVLIB_EXPORT Device jsonParseDevice(const QString &factoryFile, const QString &userFile = "");
DEVLIB_EXPORT Value jsonParseValue(const QJsonObject &val);
DEVLIB_EXPORT Condition jsonParseCondition(const QJsonObject &val);
DEVLIB_EXPORT Function jsonParseFunction(const QJsonObject &func);

#endif // JSON_H
