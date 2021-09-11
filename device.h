/** @file device.h */
#ifndef DEVICE_H
#define DEVICE_H

#include "data.h"
#include "devlib_global.h"
#include "function.h"

#include <QList>
#include <QMap>
#include <QString>

class DEVLIB_EXPORT Device {
    QMap<QString, QString> values = {
        {"name", ""},
        {"vendorId", ""},
        {"model", ""},
        {"serialNo", ""},
        {"deviceType", ""}
    };
    QList<Data *> data;
    QList<Function *> functions;

  public:
    virtual ~Device();
    // GETTERS
    QString getName() const;
    QString getVendorId() const;
    QString getModel() const;
    QString getSerialNo() const;
    QList<Data *> &getData();
    QList<Function *> &getFunctions();

    // SETTERS
    QString &operator[](const QString &attr); // TODO test
    QString operator[](const QString &attr) const; // TODO test
    void setName(const QString &name);
    void setVendorId(const QString &id);
    void setModel(const QString &id);
    void setSerialNo(const QString &serialNo);
    void setData(const QList<Data *> &data);
    void setFunctions(const QList<Function *> &functions);
};

#endif // DEVICE_H
