/** @file devlib_global.h */
#ifndef DEVLIB_GLOBAL_H
#define DEVLIB_GLOBAL_H

#include <QtCore/QtGlobal>

#if defined(DEVLIB_LIBRARY)
#    define DEVLIB_EXPORT Q_DECL_EXPORT
#else
#    define DEVLIB_EXPORT Q_DECL_IMPORT
#endif

#endif // DEVLIB_GLOBAL_H
