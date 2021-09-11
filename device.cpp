#include "device.h"

// GETTERS

Device::~Device() {
    qDeleteAll(functions);
    qDeleteAll(data);
}

QString Device::getName() const { return (*this)["name"]; }

QString Device::getVendorId() const { return (*this)["vendorId"]; }

QString Device::getModel() const { return (*this)["model"]; }

QString Device::getSerialNo() const { return (*this)["serialNo"]; }

QList<Data *> &Device::getData() { return data; }

QList<Function *> &Device::getFunctions() { return functions; }

QString &Device::operator[](const QString &attr)
{
    if (!values.contains(attr))
        throw std::logic_error(QStringLiteral("Device does not have '%1' a string attribute").arg(attr).toStdString());
    return values[attr];
}

QString Device::operator[](const QString &attr) const // TODO test
{
    return const_cast<Device*>(this)->operator[](attr);
}

// SETTERS

void Device::setName(const QString &name) { (*this)["name"] = name; }

void Device::setVendorId(const QString &id) { (*this)["vendorId"] = id; }

void Device::setModel(const QString &id) { (*this)["model"] = id; }

void Device::setSerialNo(const QString &serialNo) { (*this)["serialNo"] = serialNo; }

void Device::setData(const QList<Data *> &data) { this->data = data; }

void Device::setFunctions(const QList<Function *> &functions) {
    this->functions = functions;
}
