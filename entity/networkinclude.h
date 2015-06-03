#ifndef NETWORKINCLUDE_H
#define NETWORKINCLUDE_H

#ifdef _WIN32
#include <winsock2.h>
#elif __unix__
#include <arpa/inet.h>
#endif

#endif // NETWORKINCLUDE_H

