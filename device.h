/** @file device.h */
#ifndef DEVICE_H
#define DEVICE_H

#include "data.h"
#include "devlib_global.h"
#include "function.h"

#include <QList>
#include <QMap>
#include <QString>

namespace Devlib
{

class DEVLIB_EXPORT Device
{
    QMap<QString, QString> attributes = { { "name", "" },
                                      { "vendorId", "" },
                                      { "model", "" },
                                      { "deviceType", "" },
                                      { "desc", ""}};
    QList<Data*> data;
    QList<Function*> functions;

public:

    virtual ~Device();
    // GETTERS
    QString getName() const;
    QString getVendorId() const;
    QString getModel() const;
    QString getDescription() const;
    QList<Data*>& getData();
    QList<const Data*> getData() const;
    QList<Function*>& getFunctions();
    QList<const Function*> getFunctions() const;
    QString operator[](const QString& attr) const;
    QMap<QString, QString> getAttributes() const;

    static QStringList textualAttributeNames();

    // SETTERS
    void setAttribute(const QString& attr, const QString& value);
    void setName(const QString& name);
    void setVendorId(const QString& id);
    void setModel(const QString& id);
    void setDescription(const QString& serialNo);
    void setData(const QList<Data*>& data);
    void setFunctions(const QList<Function*>& functions);

private:
    void assertTextAttributeExists(const QString &attr) const;
};

}

#endif // DEVICE_H
