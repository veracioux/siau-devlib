#ifndef FUNCTION_H
#define FUNCTION_H

#include "devlib_global.h"

#include <QString>
#include <QMap>

class DEVLIB_EXPORT Condition
{
    QMap<QString, QString> attr = {
        {"valueName", ""},
        {"value", ""},
    };
public:
    QString &operator[](const QString &key);
};

/**
 * @brief Abstract class that represents a function that a
 * device can perform.
 */
class DEVLIB_EXPORT Function
{
};

/**
 * @brief An atomic function that is not made up of any subfunctions.
 */
class DEVLIB_EXPORT PrimitiveFunction : public Function
{
    QMap<QString, QString> attr = {
        {"name", ""},
        {"friendly", ""},
        {"valueType", "float"}
    };
    Condition condition;

public:
    QString &operator[](const QString &key);
};

/**
 * @brief A function that is wholly made up of other subfunctions.
 */
class DEVLIB_EXPORT CompositeFunction : public Function
{
    QList<Function> subfunctions;
};

#endif // FUNCTION_H
