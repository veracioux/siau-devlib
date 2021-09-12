#include "util.h"

/**
 * @brief Return a regex matching the allowed names for identifiers.
 *
 * An identifier is valid if it is a valid C++ identifier. This regex will also
 * match against reserved C++ keywords.
 */
QRegExp Devlib::validIdentifiers()
{
    return QRegExp("[_a-zA-Z][_a-zA-Z0-9]*");
}
