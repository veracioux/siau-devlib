#include "device.h"
#include "util.h"

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

QString Device::getDescription() const
{
    return (*this)["desc"];
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

// helpers
void assertNameValid(const QString& name)
{
    if (!validIdentifiers().exactMatch(name))
        throw std::logic_error("Device name must be a valid C++ identifier");
}

void Device::setAttribute(const QString& attr, const QString& value)
{
    assertTextAttributeExists(attr);
    if (attr == "name")
        assertNameValid(attr);
    attributes[attr] = value;
}

QStringList Device::textualAttributeNames()
{
    return Device().attributes.keys();
}

QString Device::operator[](const QString& attr) const
{
    assertTextAttributeExists(attr);
    return attributes[attr];
}

QMap<QString, QString> Devlib::Device::getAttributes() const
{
    return attributes;
}

// SETTERS

void Device::setName(const QString& value)
{
    setAttribute("name", value);
}

void Device::setVendorId(const QString& value)
{
    setAttribute("vendorId", value);
}

void Device::setModel(const QString& value)
{
    setAttribute("model", value);
}

void Device::setDescription(const QString& value)
{
    setAttribute("desc", value);
}

void Device::setData(const QList<Data*>& data)
{
    this->data = data;
}

void Device::setFunctions(const QList<Function*>& functions)
{
    this->functions = functions;
}

void Device::assertTextAttributeExists(const QString& attr) const
{
    if (!attributes.contains(attr))
        throw std::logic_error(
          QStringLiteral("Device does not have '%1' as a text attribute")
            .arg(attr)
            .toStdString());
}
