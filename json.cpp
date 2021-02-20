#include "json.h"

Device jsonParseDevice(const QString &factoryFile, const QString &userFile)
{
    Device device;
    if (factoryFile == "") // No factory_device.json specified
        return device;
    return {}; // TODO
}

Data jsonParseValue(const QJsonObject &val)
{
    return {}; // TODO
}

Condition jsonParseCondition(const QJsonObject &val)
{
    return {}; // TODO
}

Function jsonParseFunction(const QJsonObject &func)
{
    return {}; // TODO
}
