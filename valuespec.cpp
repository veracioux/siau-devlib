#include "valuespec.h"
#include "util.h"

#include <limits>

using namespace Devlib;

// PRIVATE HELPER FUNCTIONS

void throwIncompatible(const QString& type, const QStringList& range)
{
    throw std::domain_error(QStringLiteral("Incompatible value type and range\n"
                                           "Value type: %1\n"
                                           "Value range: [%2]")
                              .arg(type)
                              .arg(range.join(", "))
                              .toStdString());
}

// CONSTRUCTOR
ValueSpec::ValueSpec(const QString& type,
                     const QStringList range,
                     const QString& unit)
{
    if (!isValidSpec(type, range))
        throwIncompatible(type, range);
    setSpec(type, range, unit);
}

// STATIC

bool ValueSpec::isValidType(const QString& type)
{
    return validIdentifiers().exactMatch(type);
}

bool ValueSpec::isValidSpec(const QString& type, const QStringList& range)
{
    if (!ValueSpec::isValidType(type))
        return false;
    // For number types, range can be empty (no limits)
    // or an array of two values (an interval)
    if ((type == "float" || type == "int") &&
        (!range.isEmpty() && range.size() != 2))
        return false;

    if (type == "float") {
        if (range.isEmpty())
            return true;
        // Can the values be converted to float?
        bool conversionOk;
        range[0].toFloat(&conversionOk);
        if (!conversionOk)
            return false;
        range[1].toFloat(&conversionOk);
        if (!conversionOk)
            return false;
    } else if (type == "int") {
        if (range.isEmpty())
            return true;
        // Can the values be converted to float?
        bool conversionOk;
        range[0].toInt(&conversionOk);
        if (!conversionOk)
            return false;
        range[1].toInt(&conversionOk);
        if (!conversionOk)
            return false;
    } else if (type == "void" || type == "bool") {
        return range.isEmpty();
    } else { // custom enum
        if (range.isEmpty())
            return false;
        for (const QString& val : range)
            if (!isValidType(val))
                return false;
    }
    return true;
}

// GETTERS

QString ValueSpec::getValueType() const
{
    return type;
}

QStringList ValueSpec::getValueRange() const
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
        return 0.0 / 0.0; // NaN
    else
        return range[0].toFloat();
}

float ValueSpec::getMaxFloat() const
{
    if (!isFloat())
        throw std::logic_error("The ValueSpec type is not float");
    if (range.empty())
        return 0.0 / 0.0; // NaN
    else
        return range[1].toFloat();
}

int ValueSpec::getMinInt() const
{
    if (!isInt())
        throw std::logic_error("The ValueSpec type is not int");
    if (range.empty())
        return std::numeric_limits<int>::min();
    else
        return range[0].toInt();
}

int ValueSpec::getMaxInt() const
{
    if (!isInt())
        throw std::logic_error("The ValueSpec type is not int");
    if (range.empty())
        return std::numeric_limits<int>::max();
    else
        return range[1].toInt();
}

// SETTERS

void ValueSpec::setValueType(const QString& type)
{
    if (isValidSpec(type, range))
        this->type = type;
    else
        throwIncompatible(type, range);
}

void ValueSpec::setValueRange(const QStringList& range)
{
    if (isValidSpec(type, range))
        this->range = range;
    else
        throwIncompatible(type, range);
}

void ValueSpec::setSpec(const QString& type, const QStringList& range)
{
    if (!isValidSpec(type, range))
        throwIncompatible(type, range);
    this->type = type;
    this->range = range;
}

void ValueSpec::setSpec(const QString& type,
                        const QStringList& range,
                        const QString& unit)
{
    setSpec(type, range);
    this->unit = unit;
}

void ValueSpec::setUnit(const QString& unit)
{
    this->unit = unit;
}
