#include "data.h"

using namespace Devlib;

// CONSTRUCTORS

Data::Data(const QString& name,
           const QString& friendlyName,
           const ValueSpec& valueSpec)
{
    setValueSpec(valueSpec);
    this->name = name;
    this->friendlyName = friendlyName;
}

// GETTERS

QString Data::getName() const
{
    return name;
}

QString Data::getFriendlyName() const
{
    return friendlyName;
}

ValueSpec& Data::getValueSpec()
{
    return valueSpec;
}

ValueSpec Data::getValueSpec() const
{
    return valueSpec;
}

// SETTERS

void Data::setName(const QString& name)
{
    this->name = name;
}

void Data::setFriendlyName(const QString& name)
{
    this->friendlyName = name;
}

void Data::setValueSpec(const ValueSpec& spec)
{
    if (spec.isVoid())
        throw std::logic_error(
          "Value specification for a data object cannot be of type 'void'");
    valueSpec = spec;
}
