/** @file function.h */
#ifndef FUNCTION_H
#define FUNCTION_H

#include "data.h"
#include "devlib_global.h"

#include <QString>

namespace Devlib
{

/**
 * A condition to enable a device function.
 *
 * It is always of the format (*value of dataName*) = *value*.
 *
 * This class is meant to be used by the GUI/logic module.
 * It not of interest for device programmers.
 */
struct DEVLIB_EXPORT Condition
{
    QString dataName;
    QString value;
};

/**
 * A function that a device can perform.
 */
class DEVLIB_EXPORT Function
{
public:
    virtual bool isSingleFunction() const = 0;
    virtual bool isMultiFunction() const;
};

/**
 * An atomic function that is not made up of any subfunctions.
 */
class DEVLIB_EXPORT SingleFunction : public Function
{
    QString name, friendlyName;
    /**
     * Defines the properties of the value that can be
     * supplied to this function.
     */
    ValueSpec valueSpec;
    /** Condition that makes this function available for use. */
    Condition condition;

public:
    SingleFunction();
    virtual ~SingleFunction() = default;
    SingleFunction(const QString& name,
                   const QString& friendlyName,
                   const ValueSpec& valueSpec,
                   const Condition& condition = {});

    // GETTERS
    QString getName() const;
    QString getFriendlyName() const;
    ValueSpec getValueSpec() const;
    Condition getCondition() const;

    bool isSingleFunction() const override;

    // SETTERS
    void setName(const QString& name);
    void setFriendlyName(const QString& friendly);
    void setValueSpec(const ValueSpec& spec);
    void setCondition(const Condition& condition);
};

/**
 * A function that is wholly made up of other subfunctions.
 */
class DEVLIB_EXPORT MultiFunction : public Function
{
    QList<SingleFunction*> subfunctions;

public:
    MultiFunction(const QList<SingleFunction>& subfunctions);
    virtual ~MultiFunction() = default;

    // GETTERS
    QList<SingleFunction*>& getSubfunctions();
    QList<const SingleFunction*> getSubfunctions() const;

    bool isSingleFunction() const override;

    // SETTERS
    void setSubfunctions(const QList<SingleFunction*>& subfunctions);
};

}

#endif // FUNCTION_H
