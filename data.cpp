#include "data.h"

#include <limits>

/*******************
 * class ValueSpec *
 *******************/

bool ValueSpec::isValidIdentifier(const QString &type)
{
    // TODO implement: just check if type contains a valid C++ identifier.
    return true;
}

bool ValueSpec::isValidSpec(const QString &type, const QList<QString> range)
{
    if (type == "void" || !ValueSpec::isValidIdentifier(type))
        return false;
    // For number types, range can be empty (no limits)
    // or an array of two values (an interval)
    if ((type == "float" || type == "int")
        && (range.size() != 0 && range.size() != 2))
        return false;

    if (type == "float")
    {
        // Can the values be converted to float?
        bool conversionOk;
        range[0].toFloat(&conversionOk);
        if (!conversionOk) return false;
        range[1].toFloat(&conversionOk);
        if (!conversionOk) return false;
    }
    else if (type == "int")
    {
        // Can the values be converted to float?
        bool conversionOk;
        range[0].toInt(&conversionOk);
        if (!conversionOk) return false;
        range[1].toInt(&conversionOk);
        if (!conversionOk) return false;
    }
    return true;
}

/**************
 * class Data *
 **************/

// GETTERS

QString Data::getName() const
{
    return name;
}

QString Data::getFriendlyName() const
{
    return friendlyName;
}

ValueSpec &Data::getValueSpec()
{
    return valueSpec;
}

ValueSpec Data::getValueSpec() const
{
    return valueSpec;
}

// SETTERS

void Data::setName(QString name)
{
    this->name = name;
}

void Data::setFriendlyName(QString name)
{
    this->name = name;
}

void Data::setValueSpec(const ValueSpec &spec)
{
    valueSpec = spec;
}

// PRIVATE

/* TODO use in Function instead
float Value::getMinFloat() const
{
    assertType("float");
    if (valueRange.empty())
        return std::numeric_limits<float>::min();
    float val = valueRange[0].toFloat();
    return val;
}

float Value::getMaxFloat() const
{
    assertType("float");
    if (valueRange.empty())
        return std::numeric_limits<float>::max();
    float val = valueRange[1].toFloat();
    return val;
}
*/
/*
void Data::assertType(const QString &type) const
{
    if ((*this)["valueType"] != type)
        throw std::logic_error("Value must be of type" + type.toStdString());
}
*/
