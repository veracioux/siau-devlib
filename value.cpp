#include "value.h"

#include <limits>

// PRIVATE HELPER FUNCTIONS

void ValueSpec::throwIncompatible()
{
    throw std::logic_error("The value type and range are incompatible");
}

// CONSTRUCTOR
ValueSpec::ValueSpec(const QString &type, const QList<QString> range,
                     const QString &unit)
{
    if (!isValidSpec(type, range))
        throwIncompatible();
    setSpec(type, range, unit);
}

// STATIC

bool ValueSpec::isValidIdentifier(const QString &type)
{
    // TODO implement
    // Just check if type contains a valid C++ identifier.
    return true;
}

bool ValueSpec::isValidSpec(const QString &type,
                            const QList<QString> range)
{
    if (!ValueSpec::isValidIdentifier(type))
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
    else if (type == "void")
        return range.empty();
    return true;
}

// GETTERS

QString ValueSpec::getValueType() const
{
    return type;
}

QList<QString> ValueSpec::getValueRange() const
{
    return range;
}

QString ValueSpec::getUnit() const
{
    return unit;
}
/*****/
bool ValueSpec::isFloat() const
{
    return type == "float";
}

bool ValueSpec::isInt() const
{
    return type == "int";
}

bool ValueSpec::isBool() const
{
    return type == "bool";
}

bool ValueSpec::isVoid() const
{
    return type == "void";
}

bool ValueSpec::isCustomEnum() const
{
    return !isFloat() && !isInt() && !isBool() && !isVoid();
}
/*****/
float ValueSpec::getMinFloat() const
{
    if (!isFloat())
        throw std::logic_error("The ValueSpec type is not float");
    if (range.empty())
        return -1e6;
    else
        return range[0].toFloat();
}

float ValueSpec::getMaxFloat() const
{
    if (!isFloat())
        throw std::logic_error("The ValueSpec type is not float");
    if (range.empty())
        return 1e6;
    else
        return range[1].toFloat();
}

float ValueSpec::getMinInt() const
{
    if (!isInt())
        throw std::logic_error("The ValueSpec type is not int");
    if (range.empty())
        return -1e6;
    else
        return range[0].toInt();
}

float ValueSpec::getMaxInt() const
{
    if (!isInt())
        throw std::logic_error("The ValueSpec type is not int");
    if (range.empty())
        return 1e6;
    else
        return range[1].toInt();
}

// SETTERS

void ValueSpec::setValueType(const QString &type)
{
    if (isValidSpec(type, range))
        this->type = type;
    else
        throwIncompatible();
}

void ValueSpec::setValueRange(const QList<QString> &range)
{
    if (isValidSpec(type, range))
        this->range = range;
    else
        throwIncompatible();
}

void ValueSpec::setSpec(const QString &type, const QList<QString> &range)
{
    if (isValidSpec(type, range))
    {
        this->type = type;
        this->range = range;
    }
    else
        throwIncompatible();
}

void ValueSpec::setSpec(const QString &type, const QList<QString> &range,
                        const QString &unit)
{
    setSpec(type, range);
    this->unit = unit;
}

void ValueSpec::setUnit(const QString &unit)
{

}
