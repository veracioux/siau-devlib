#include "function.h"

QString &Condition::operator[](const QString &key)
{
    if (!attr.contains(key))
        throw std::logic_error("Specified attribute does not exist");
    else
        return attr[key];
}

QString &PrimitiveFunction::operator[](const QString &key)
{
    if (!attr.contains(key))
        throw std::logic_error("Specified attribute does not exist");
    else
        return attr[key];
}
