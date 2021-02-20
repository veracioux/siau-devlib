/** @file function.h */
#ifndef FUNCTION_H
#define FUNCTION_H

#include "devlib_global.h"
#include "data.h"

#include <QString>
#include <QMap>

class DEVLIB_EXPORT Condition
{
    QString valueName;
    QString value;
public:
};

/**
 * A function that a device can perform.
 */
class DEVLIB_EXPORT Function
{
};

/**
 * An atomic function that is not made up of any subfunctions.
 */
class DEVLIB_EXPORT SingleFunction : public Function
{
    /** List of string attributes */
    QMap<QString, QString> attr = {
        {"name", ""},
        {"friendly", ""},
    };
    ValueSpec valueSpec;
    /** Condition that makes this function available for use. */
    Condition condition;
};

/**
 * A function that is wholly made up of other subfunctions.
 */
class DEVLIB_EXPORT MultiFunction : public Function
{
    QList<Function> subfunctions;
};

#endif // FUNCTION_H
