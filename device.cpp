#include "device.h"

// GETTERS

Device::~Device()
{
    qDeleteAll(functions);
    qDeleteAll(data);
}

QString Device::getName() const
{
    return name;
}

QString Device::getVendorId() const
{
    return vendorId;
}

QString Device::getModel() const
{
    return model;
}

QString Device::getSerialNo() const
{
    return serialNo;
}


QList<Data*> &Device::getData()
{
    return data;
}

QList<Function*> &Device::getFunctions()
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

void Device::setModel(const QString &id)
{
    this->model = id;
}

void Device::setSerialNo(const QString &serialNo) {
    this->serialNo = serialNo;
}

void Device::setData(const QList<Data*> &data)
{
    this->data = data;
}

void Device::setFunctions(const QList<Function*> &functions)
{
    this->functions = functions;
}
