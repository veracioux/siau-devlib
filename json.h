/** @file json.h */
#ifndef JSON_H
#define JSON_H

#include "devlib_global.h"

#include "data.h"
#include "device.h"
#include "function.h"
#include "valuespec.h"

#include <QJsonArray>
#include <QJsonObject>

namespace Devlib
{

// THE MOST IMPORTANT OBJECTS
/**
 * Parse the contents of *factory_device.json* and *user_device.json* and
 * return a `Device` object.
 *
 * If the parameter`factoryFile` is an empty string, a device with default
 * values will be returned.
 *
 * @throws std::logic_error If the file cannot be parsed into a device.
 */
Device DEVLIB_EXPORT jsonParseDevice(const QString& factoryFile);
// TODO LATER Add parsing for user_device.json
/**
 * Parse a device data object and return a `Data` object.
 *
 * @throws std::logic_error If `data` cannot be parsed into a valid `Data`
 * object.
 */
Data DEVLIB_EXPORT* jsonParseData(const QJsonObject& data);
/**
 * Parse a JSON object `func` and return a `SingleFunction`.
 *
 * @throws std::logic_error If `func` cannot be parsed into a valid
 * `SingleFunction` object.
 */
SingleFunction DEVLIB_EXPORT* jsonParseFunction(const QJsonObject& func);
/**
 * Parse a JSON object `func` and return a `MultiFunction`.
 *
 * @throws std::logic_error If `func` contains invalid `SingleFunction` objects.
 */
MultiFunction DEVLIB_EXPORT* jsonParseFunction(const QJsonArray& func);

// HELPER OBJECTS
/**
 * Parse the JSON object `cond` and return a `Condition` object.
 *
 * @throws std::logic_error If `cond` cannot be parsed into a valid `Condition`.
 */
Condition DEVLIB_EXPORT jsonParseCondition(const QString& cond);
/**
 * Parse the JSON object `valueSpec` and return a `ValueSpec` object.
 *
 * @param valueSpec The data or function object containing the attributes
 * `valueType`, `valueRange` and `unit`. The `ValueSpec` object is created
 * as `ValueSpec(valueType, valueRange, unit)`. Some of these can be omitted,
 * which will implicitly set them to their default value (confer the
 * device representation specification).
 *
 * @throws std::logic_error If `valueSpec` does not contain a valid `ValueSpec`.
 */
ValueSpec DEVLIB_EXPORT jsonParseValueSpec(const QJsonObject& obj);

}

#endif // JSON_H
