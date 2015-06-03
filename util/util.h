#ifndef UTIL_H
#define UTIL_H

// includes from standard library
#include <memory>
#include <cstdint>

// includes from QT
#include <QByteArray>
#include <QString>

// includes from project
#include "util_global.h"

// pointer definition
class UTILSHARED_EXPORT Util;
typedef std::shared_ptr<Util> UtilPtr;

class UTILSHARED_EXPORT Util
{

public:
    Util();
    virtual ~Util();

    static QByteArray getHexRepresentationFromUInt16(const uint16_t &input);
    static QByteArray getHexRepresentationFromUInt32(const uint32_t &input);
    static QString getStringFromUInt8Array(const uint8_t *str,
                                          const uint32_t size);
    static uint32_t changeEndianness(uint32_t value);

};

#endif // UTIL_H
