#include "json.h"
#include "valuespec.h"
#include <QIODevice>
#include <QFileInfo>
#include <QJsonDocument>
#include <iostream>

using namespace std;

bool fileExists(QString path) {
    QFileInfo check_file(path);

    return check_file.exists() && check_file.isFile();
}

ValueSpec jsonParseValueSpec(const QJsonObject &obj) {
    ValueSpec valueSpec;

    valueSpec.setValueType(obj["valueType"].toString());

    valueSpec.setUnit(obj["unit"].toString());

    QJsonValue jsonRange = obj["valueRange"];
    if (!jsonRange.isUndefined() && !jsonRange.isArray())
        throw std::logic_error("Invalid value range");
    QList<QString> range;

    foreach (const QJsonValue &val, jsonRange.toArray()) {
        range.append(val.toVariant().toString());
    }

    valueSpec.setValueRange(range);
    return valueSpec;
}

Data *jsonParseData(const QJsonObject &data) {
    Data *result = new Data;
    QString name = "";
    QString friendlyName = "";
    ValueSpec valueSpec = jsonParseValueSpec(data);
    if (!data["name"].isNull())
        name = data["name"].toString();
    if (!data["friendly"].isNull())
        friendlyName = data["friendly"].toString();

    result->setName(name);
    result->setFriendlyName(friendlyName);
    result->setValueSpec(valueSpec);
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

SingleFunction *jsonParseFunction(const QJsonObject &func) {
    SingleFunction *function = new SingleFunction;
    QString name = "";
    QString friendlyName = "";
    ValueSpec valueSpec = jsonParseValueSpec(func);
    Condition condition; // TODO = jsonParseCondition(func["if"]);
    if (!func["name"].isNull())
        name = func["name"].toString();
    if (!func["friendly"].isNull())
        friendlyName = func["friendly"].toString();

    if (!func["if"].isNull())
        jsonParseCondition(func["if"].toString());

    function->setName(name);
    function->setFriendlyName(friendlyName);
    function->setValueSpec(valueSpec);
    function->setCondition(condition);

    return function;
}

Device jsonParseDevice(const QString &factoryFile) {
    Device device;
    QList<Data*> datas;
    QList<Function*> functions;
    if (factoryFile == "") // No factory_device.json specified
        return device;
    QString rawData;
    QFile file(factoryFile);

    if (fileExists(factoryFile)) {
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        rawData = file.readAll();
        file.close();

        QJsonDocument document = QJsonDocument::fromJson(rawData.toUtf8());

        QJsonObject jsonObject = document.object();
        QString name = "";
        QString vendorId = "";
        QString model = "";
        QString deviceType = "";
        QString desc = "";
        if (!jsonObject["name"].isNull())
            name = jsonObject["name"].toString();
        if (!jsonObject["vendorId"].isNull())
            vendorId = jsonObject["vendorId"].toString();
        if (!jsonObject["deviceId"].isNull())
            model = jsonObject["deviceId"].toString();
        if (!jsonObject["deviceType"].isNull())
            deviceType = jsonObject["deviceType"].toString();
        if (!jsonObject["desc"].isNull())
            desc = jsonObject["desc"].toString();

        foreach (const QJsonValue &value, jsonObject["data"].toArray()) {

            QJsonObject object = value.toObject();

            datas.append(jsonParseData(object));
        }

        foreach (const QJsonValue &value, jsonObject["functions"].toArray()) {

            QJsonObject object = value.toObject();

            functions.append(jsonParseFunction(object));
        }
        device.setName(name);
        device.setVendorId(vendorId);
        device.setModel(model);
        device.setData(datas);
        device.setFunctions(functions);
        return device;

    } else {
        qWarning() << "There is no any file in this path!";
    }
    return device;
}

int main() { return 0; }
