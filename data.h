/** @file value.h */
#ifndef VALUE_H
#define VALUE_H

#include "devlib_global.h"

#include <QList>
#include <QString>
#include <QMap>

/**
 * Value specification. A tuple of (valueType, valueRange, unit).
 */
class DEVLIB_EXPORT ValueSpec
{
    QString type, unit;
    QList<QString> range;

public:
    // STATIC
    static bool isValidIdentifier(const QString &type);
    static bool isValidSpec(const QString &type, const QList<QString> range);

    friend class Data;
};

/**
 * A value that can be received from a device.
 */
class DEVLIB_EXPORT Data
{
    QString name, friendlyName, unit;
    ValueSpec valueSpec;

public:
    // CONSTRUCTORS
    /** The default constructor, does nothing. */
    Data() = default;

    // GETTERS
    QString getName() const;
    QString getFriendlyName() const;
    ValueSpec &getValueSpec();
    ValueSpec getValueSpec() const;

    // SETTERS
    void setName(QString name);
    void setFriendlyName(QString name);
    void setValueSpec(const ValueSpec &spec);

private:
    /* TODO find a use or remove
    /**
     * Helper function - assert that valueType is equal to `type`.
     * @throws std::logic_error On assertion failure.
    void assertType(const QString &type) const;
    */
};

#endif // VALUE_H
