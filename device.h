/** @file device.h */
#ifndef DEVICE_H
#define DEVICE_H

#include "devlib_global.h"
#include "data.h"
#include "function.h"

#include <QString>
#include <QMap>
#include <QList>

class DEVLIB_EXPORT Device
{
    QString name, vendorId, model, serialNo;
    QList<Data*> data;
    QList<Function*> functions;

public:

    // GETTERS
    QString getName() const;
    QString getVendorId() const;
    QString getModel() const;
    QString getSerialNo() const;
    QList<Data*> &getData();
    QList<Function*> &getFunctions();

    // SETTERS
    void setName(const QString &name);
    void setVendorId(const QString &id);
    void setModel(const QString &id);
    void setData(const QList<Data*> &data);
    void setFunctions(const QList<Function*> &functions);
};

#endif // DEVICE_H
