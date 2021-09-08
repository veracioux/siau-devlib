/** @file value.h */
#ifndef VALUESPEC_H
#define VALUESPEC_H

#include "devlib_global.h"

#include <QString>
#include <QList>

/**
 * Value specification. A tuple of (valueType, valueRange, unit).
 *
 * This class contains the definition of a value type, along with its
 * range of possible values and unit of measurement.
 *
 */
class DEVLIB_EXPORT ValueSpec
{
    QString type = QStringLiteral("void"), unit;
    QList<QString> range;

private:
    /**
     * Helper method that throws an exception signalling that
     * type and unit are incompatible
     */
    void throwIncompatible();

public:

    // CONSTRUCTORS
    /** Default constructor */
    ValueSpec() = default;
    /**
     * Create a value spec.
     * @param type The value type.
     * @param range The range of possible values.
     * @param unit [optional] The unit of measurement
     *
     * @throws std::logic_error If the parameters do not make a valid
     * `ValueSpec`.
     */
    ValueSpec(const QString &type, const QList<QString> range,
              const QString &unit = "");

    // STATIC
    /** Test if `type` is a valid C++ identifier. */
    static bool isValidType(const QString &type);
    /**
     * Test if the pair (`type`, `range`) can be used to create a
     * valid `ValueSpec`.
     */
    static bool isValidSpec(const QString &type, const QList<QString> range);

    // GETTERS
    QString getValueType() const;
    QList<QString> getValueRange() const;
    QString getUnit() const;

    bool isFloat() const;
    bool isInt() const;
    bool isBool() const;
    bool isVoid() const;
    bool isCustomEnum() const;

    /**
     * Return the minimum value of this `ValueSpec` if it is of type float.
     *
     * @throws std::logic_error If this `ValueSpec` is not of type float.
     */
    float getMinFloat() const;
    /**
     * Return the maximum value of this `ValueSpec` if it is of type `float`.
     *
     * @throws std::logic_error If this `ValueSpec` is not of type `float`.
     */
    float getMaxFloat() const;
    /**
     * Return the minimum value of this `ValueSpec` if it is of type `int`.
     *
     * @throws std::logic_error If this `ValueSpec` is not of type `int`.
     */
    int getMinInt() const;
    /**
     * Return the maximum value of this `ValueSpec` if it is of type `int`.
     *
     * @throws std::logic_error If this `ValueSpec` is not of type `int`.
     */
    int getMaxInt() const;

    // Add to/from byte array method or similar?

    // SETTERS
    /**
     * @brief setValueType
     *
     * @throws std::logic_error If `type` is not compatible with the value
     * range of this object.
     */
    void setValueType(const QString &type);
    /**
     * @brief setValueRange
     *
     * @throws std::logic_error If `range` is not compatible with the value
     * type of this object.
     */
    void setValueRange(const QList<QString> &range);
    void setSpec(const QString &type, const QList<QString> &range);
    void setSpec(const QString &type, const QList<QString> &range,
                 const QString &unit);
    void setUnit(const QString &unit);

    friend class Data;
};

#endif // VALUESPEC_H
