#include "json.h"

Device jsonParseDevice(const QString &factoryFile)
{
    Device device;
    if (factoryFile == "") // No factory_device.json specified
        return device;
    return {}; // TODO implement
}

Data jsonParseData(const QJsonObject &data)
{
    return {}; // TODO implement
}

SingleFunction jsonParseFunction(const QJsonObject &func)
{
   // TODO implement
}

MultiFunction jsonParseFunction(const QJsonArray &func)
{
   // TODO implement
}

Condition jsonParseCondition(const QJsonObject &cond)
{
   // TODO implement
}

ValueSpec jsonParseValueSpec(const QJsonObject &obj)
{
   // TODO implement
}
