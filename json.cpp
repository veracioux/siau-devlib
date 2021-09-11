#include "json.h"
#include "valuespec.h"
#include <QFileInfo>
#include <QIODevice>
#include <QJsonDocument>
#include <iostream>

using namespace std;

QList<QString> _parseValueRangee(const QJsonValue &valueRange, const ValueSpec &spec) {
    QList<QString> range;
    foreach (const QJsonValue &val, valueRange.toArray()) {
        if (((spec.isInt() || spec.isFloat()) && !val.isDouble()) ||
                (spec.isCustomEnum() && !val.isString()) ||
                val.isArray() || val.isObject()) {
            throw std::runtime_error("valueRange has invalid JSON type");
        }
        range.append(val.toVariant().toString());
    }
    return range;
}

ValueSpec jsonParseValueSpec(const QJsonObject &obj) {
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

    spec.setValueType(valueType.toString());
    spec.setUnit(obj["unit"].toString());
    spec.setValueRange(_parseValueRangee(valueRange, spec));
    return spec;
}

Data *jsonParseData(const QJsonObject &data) {
    Data *result = new Data;
    QJsonValue name = data["name"],
        friendlyName = data["friendly"];

    if (!name.isString())
        throw std::runtime_error("Attribute 'name' must be a string");
    if (!friendlyName.isString())
        throw std::runtime_error("Attribute 'friendly' must be a string");
    ValueSpec valueSpec = jsonParseValueSpec(data);

    result->setName(name.toString());
    result->setFriendlyName(friendlyName.toString());
    result->setValueSpec(valueSpec);
    return result;
}

SingleFunction *jsonParseFunction(const QJsonObject &func) {
    SingleFunction *result = new SingleFunction;
    QJsonValue name = func["name"],
            friendlyName = func["friendly"];

    if (!name.isString())
        throw std::runtime_error("Attribute 'name' must be a string");
    if (!friendlyName.isString())
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

Condition jsonParseCondition(const QString &cond) {
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

QJsonObject jsonObjectFromFile(const QString &path) {
    QFile file(path);
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QJsonDocument document = QJsonDocument::fromJson(file.readAll());
    file.close();
    return document.object();
}

QList<Data *> _parseDataArray(const QJsonArray &jsonArray)
{
    QList<Data*> result;
    result.reserve(jsonArray.size());

    foreach (const QJsonValue &val, jsonArray) {
        if (!val.isObject())
            throw std::runtime_error("Members of 'data' array must be JSON objects");
        result.append(jsonParseData(val.toObject()));
    }
    return result;
}

QList<Function*> _parseFunctionsArray(const QJsonArray &jsonArray)
{
    QList<Function*> result;
    result.reserve(jsonArray.size());

    foreach (const QJsonValue &val, jsonArray) {
        if (!val.isObject())
            throw std::runtime_error("Members of 'function' array must be JSON objects");
        result.append(jsonParseFunction(val.toObject()));
    }
    return result;
}

Device jsonParseDevice(const QString &factoryFile)
{
    if (!QFileInfo(factoryFile).isFile())
        throw std::runtime_error("Specified JSON file does not exist");

    QFile file(factoryFile);
    Device device;
    QList<Data *> datas;
    QList<Function *> functions;

    QJsonObject jsonObject = jsonObjectFromFile(factoryFile);

    // Read all attributes of the device JSON object
    foreach (const QString &attr, jsonObject.keys()) {
        QJsonValue val = jsonObject[attr];
        if (val.isString())
            try {
                device[attr] = val.toString();
            }  catch (std::exception &e) {
                goto unknown_attribute;
            }
        else if (val.isArray() && attr == "data")
            device.setData(_parseDataArray(val.toArray()));
        else if (val.isArray() && attr == "functions")
            device.setFunctions(_parseFunctionsArray(val.toArray()));
        else
            goto unknown_attribute;
    }

    return device;

unknown_attribute:
    throw std::runtime_error("Unknown device attribute: ");
}

int main() { return 0; }
