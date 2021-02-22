#include "device.h"

// GETTERS

QString Device::getName() const
{
    return name;
}

QString Device::getVendorId() const
{
    return vendorId;
}

QString Device::getDeviceId() const
{
    return deviceId;
}

QList<Data> &Device::getData()
{
    return values;
}

QList<Data> Device::getData() const
{
    return values;
}

QList<Function> &Device::getFunctions()
{
    return functions;
}

QList<Function> Device::getFunctions() const
{
    return functions;
}

// SETTERS

void Device::setName(const QString &name)
{
    this->name = name;
}

void Device::setVendorId(const QString &id)
{
    this->vendorId = id;
}

void Device::setDeviceId(const QString &id)
{
    this->deviceId = id;
}

void Device::setData(const QList<Data> &data)
{
    this->data = data;
}

void Device::setFunctions(const QList<Function> &functions)
{
    this->functions = functions;
}
