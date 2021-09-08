/** @file data.h */
#ifndef DATA_H
#define DATA_H

#include "devlib_global.h"

#include "valuespec.h"

#include <QList>
#include <QString>

/**
 * A value that can be received from a device.
 */
class DEVLIB_EXPORT Data
{
    QString name, friendlyName;
    ValueSpec valueSpec;

public:
    Data() = default;
    Data(const QString &name, const QString &friendlyName, const ValueSpec &valueSpec);

    // GETTERS
    QString getName() const;
    QString getFriendlyName() const;
    ValueSpec &getValueSpec();
    ValueSpec getValueSpec() const;

    // SETTERS
    void setName(const QString &name);
    void setFriendlyName(const QString &name);
    void setValueSpec(const ValueSpec &spec);

private:
};

#endif // DATA_H
