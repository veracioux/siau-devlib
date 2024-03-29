#include "json.h"
#include "valuespec.h"
#include <QFileInfo>
#include <QIODevice>
#include <QJsonDocument>
#include <iostream>

using namespace std;

namespace Devlib
{

QStringList _parseValueRange(const QJsonValue& valueRange, const QString& valueType)
{
    QList<QString> range;
    ValueSpec dummySpec;
    // Bypass error checking
    dummySpec.type = valueType;
    foreach (const QJsonValue& val, valueRange.toArray()) {
        if (((dummySpec.isInt() || dummySpec.isFloat()) && !val.isDouble()) ||
            (dummySpec.isCustomEnum() && !val.isString()) || val.isArray() ||
            val.isObject()) {
            throw std::runtime_error("valueRange has invalid JSON type");
        }
        range.append(val.toVariant().toString());
    }
    return range;
}

ValueSpec jsonParseValueSpec(const QJsonObject& obj)
{
    ValueSpec spec;

    QJsonValue valueType = obj["valueType"];
    QJsonValue valueRange = obj["valueRange"];
    QJsonValue unit = obj["unit"];

    if (!(valueType.isString() || valueType.isUndefined()))
        throw std::runtime_error("valueType has invalid JSON type");
    if (!(valueRange.isArray() || valueRange.isUndefined()))
        throw std::runtime_error("valueRange has invalid JSON type");
    if (!(unit.isString() || unit.isUndefined()))
        throw std::runtime_error("unit has invalid JSON type");

    if (valueType.isUndefined())
        valueType = "void";

    spec.setSpec(valueType.toString(), _parseValueRange(valueRange, valueType.toString()));
    spec.setUnit(obj["unit"].toString());
    return spec;
}

Data* jsonParseData(const QJsonObject& data)
{
    Data* result = new Data;
    QJsonValue name = data["name"], friendlyName = data["friendly"];

    if (!name.isString())
        throw std::runtime_error("Attribute 'name' must be a string");
    if (!friendlyName.isUndefined() && !friendlyName.isString())
        throw std::runtime_error("Attribute 'friendly' must be a string");
    ValueSpec valueSpec = jsonParseValueSpec(data);

    result->setName(name.toString());
    result->setFriendlyName(friendlyName.toString());
    result->setValueSpec(valueSpec);
    return result;
}

SingleFunction* jsonParseFunction(const QJsonObject& func)
{
    SingleFunction* result = new SingleFunction;
    QJsonValue name = func["name"], friendlyName = func["friendly"];

    if (!name.isString())
        throw std::runtime_error("Attribute 'name' must be a string");
    if (!friendlyName.isUndefined() && !friendlyName.isString())
        throw std::runtime_error("Attribute 'friendly' must be a string");

    ValueSpec valueSpec = jsonParseValueSpec(func);
    Condition condition;

    // TODO jsonParseCondition(func["if"].toString());

    result->setName(name.toString());
    result->setFriendlyName(friendlyName.toString());
    result->setValueSpec(valueSpec);
    // TODO result->setCondition(condition);

    return result;
}

MultiFunction* jsonParseFunction(const QJsonArray& func)
{
    QList<SingleFunction*> sfun;
    sfun.reserve(func.size());
    for (const auto &val : func) {
        if (!val.isObject())
            throw std::runtime_error("Subfunctions of a multi function must be JSON objects");
        sfun.append(jsonParseFunction(val.toObject()));
    }
    return new MultiFunction(sfun);
}

Condition jsonParseCondition(const QString& cond)
{
    Condition condition;
    QString name = "";
    QString value = "";
    int index = cond.indexOf('=');
    name = cond.mid(0, index);
    value = cond.mid(index + 1);

    // condition.setName(name);
    // condition.setValue(value);
    return condition;
}

QJsonObject jsonObjectFromFile(const QString& path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        throw std::runtime_error(QStringLiteral("Could not open file '%1'")
                                 .arg(path).toStdString());

    QJsonDocument document = QJsonDocument::fromJson(file.readAll());
    file.close();
    return document.object();
}

QList<Data*> _parseDataArray(const QJsonArray& jsonArray)
{
    QList<Data*> result;
    result.reserve(jsonArray.size());

    foreach (const QJsonValue& val, jsonArray) {
        if (!val.isObject())
            throw std::runtime_error(
              "Members of 'data' array must be JSON objects");
        result.append(jsonParseData(val.toObject()));
    }
    return result;
}

QList<Function*> _parseFunctionsArray(const QJsonArray& jsonArray)
{
    QList<Function*> result;
    result.reserve(jsonArray.size());

    foreach (const QJsonValue& val, jsonArray) {
        if (val.isObject())     // single function
            result.append(jsonParseFunction(val.toObject()));
        else if (val.isArray()) // multi function
            result.append(jsonParseFunction(val.toArray()));
        else
            throw std::runtime_error(
              "Members of 'function' array must be JSON objects or function arrays");
    }
    return result;
}

// helper
void throwInvalidAttribute(const QString &attr)
{
    throw std::runtime_error(QStringLiteral("Attribute '%1' is invalid")
                             .arg(attr).toStdString());
}

Device jsonParseDevice(const QString& factoryFile)
{
    if (!QFileInfo(factoryFile).isFile())
        throw std::runtime_error("Specified JSON file does not exist");

    QFile file(factoryFile);
    Device device;

    QJsonObject jsonObject = jsonObjectFromFile(factoryFile);

    // Read all attributes of the device JSON object
    foreach (const QString& attr, jsonObject.keys()) {
        QJsonValue val = jsonObject[attr];
        if (val.isString())
            try {
                device.setAttribute(attr, val.toString());
            } catch (std::exception& e) {
                throwInvalidAttribute(attr);
            }
        else if (val.isArray() && attr == "data")
            device.setData(_parseDataArray(val.toArray()));
        else if (val.isArray() && attr == "functions")
            device.setFunctions(_parseFunctionsArray(val.toArray()));
        else
            throwInvalidAttribute(attr);
    }

    return device;

}

}
