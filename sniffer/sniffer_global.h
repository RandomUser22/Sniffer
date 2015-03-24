#ifndef SNIFFER_GLOBAL_H
#define SNIFFER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SNIFFER_LIBRARY)
#  define SNIFFERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define SNIFFERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // SNIFFER_GLOBAL_H
