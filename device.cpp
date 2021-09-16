#include "device.h"

using namespace Devlib;

// GETTERS

Device::~Device()
{
    qDeleteAll(functions);
    qDeleteAll(data);
}

QString Device::getName() const
{
    return (*this)["name"];
}

QString Device::getVendorId() const
{
    return (*this)["vendorId"];
}

QString Device::getModel() const
{
    return (*this)["model"];
}

QString Device::getSerialNo() const
{
    return (*this)["serialNo"];
}

QList<Data*>& Device::getData()
{
    return data;
}

QList<const Data *> Device::getData() const
{
    return QList<const Data*>(data.begin(), data.end());
}

QList<Function*>& Device::getFunctions()
{
    return functions;
}

QList<const Function*> Device::getFunctions() const
{
    return QList<const Function*>(functions.begin(), functions.end());
}

QString& Device::operator[](const QString& attr)
{
    if (!values.contains(attr))
        throw std::logic_error(
          QStringLiteral("Device does not have '%1' a string attribute")
            .arg(attr)
            .toStdString());
    return values[attr];
}

QStringList Device::textualAttributeNames()
{
    return Device().values.keys();
}

QString Device::operator[](const QString& attr) const // TODO test
{
    return const_cast<Device*>(this)->operator[](attr);
}

// SETTERS

void Device::setName(const QString& name)
{
    (*this)["name"] = name;
}

void Device::setVendorId(const QString& id)
{
    (*this)["vendorId"] = id;
}

void Device::setModel(const QString& id)
{
    (*this)["model"] = id;
}

void Device::setSerialNo(const QString& serialNo)
{
    (*this)["serialNo"] = serialNo;
}

void Device::setData(const QList<Data*>& data)
{
    this->data = data;
}

void Device::setFunctions(const QList<Function*>& functions)
{
    this->functions = functions;
}
