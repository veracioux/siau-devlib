#include "function.h"

/************
 * Function *
 ************/

bool Function::isMultiFunction() const
{
    return !isSingleFunction();
}

/******************
 * SingleFunction *
 ******************/

// CONSTRUCTORS

SingleFunction::SingleFunction()
{
}

SingleFunction::SingleFunction(const QString &name, const QString &friendlyName,
                               const ValueSpec &valueSpec, const Condition &condition)
    : name(name), friendlyName(friendlyName), valueSpec(valueSpec), condition(condition)
{
}

// GETTERS

QString SingleFunction::getName() const
{
    return name;
}

QString SingleFunction::getFriendlyName() const
{
    return friendlyName;
}

ValueSpec SingleFunction::getValueSpec() const
{
    return valueSpec;
}

Condition SingleFunction::getCondition() const
{
    return condition;
}

bool SingleFunction::isSingleFunction() const
{
    return true;
}

// SETTERS

void SingleFunction::setName(const QString &name)
{
    this->name = name;
}

void SingleFunction::setFriendlyName(const QString &friendly)
{
    this->friendlyName = friendly;
}

void SingleFunction::setValueSpec(const ValueSpec &spec)
{
    this->valueSpec = spec;
}

void SingleFunction::setCondition(const Condition &condition)
{
    this->condition = condition;
}

/*****************
 * MultiFunction *
 *****************/

bool MultiFunction::isSingleFunction() const
{
    return false;
}

void MultiFunction::setSubfunctions(const QList<SingleFunction*> &subfunctions)
{
    this->subfunctions = subfunctions;
}
