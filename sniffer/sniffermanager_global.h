#ifndef SNIFFERMANAGER_GLOBAL
#define SNIFFERMANAGER_GLOBAL

#include <QtCore/qglobal.h>

#if defined(SNIFFER_LIBRARY)
#  define SNIFFERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define SNIFFERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // SNIFFERMANAGER_GLOBAL
