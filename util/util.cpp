#include "util.h"


Util::Util()
{
}

Util::~Util()
{
}
QString Util::getStringFromUInt8Array(const uint8_t *str,
                                      const uint32_t size)
{
    QString s;
    QString result = "";

    // qstring in reverse order
    for (uint32_t i = 0; i < size; i++){
        s = QString("%1").arg(str[i],2,16,QChar('0'));
        result.append(s);
    }
    return result;
}

QByteArray Util::getHexRepresentationFromUInt16(const uint16_t &input)
{
    QByteArray aux;
    char lowerByte = input;
    char upperByte = input >> 8;
    aux.append(lowerByte);
    aux.append(upperByte);
    return aux.toHex();
}

QByteArray Util::getHexRepresentationFromUInt32(const uint32_t &input)
{
    QByteArray aux;
    aux.append(QString::number(changeEndianness(input)));
    return aux.toHex();
}

uint32_t Util::changeEndianness(uint32_t value)
{
    uint32_t result = 0;
    result |= (value & 0x000000FF) << 24;
    result |= (value & 0x0000FF00) << 8;
    result |= (value & 0x00FF0000) >> 8;
    result |= (value & 0xFF000000) >> 24;
    return result;
}


