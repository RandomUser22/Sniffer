#ifndef SUBPACKET_H
#define SUBPACKET_H

// includes from standard memory
#include <memory>
#include <cstdint>

// includes from QT
#include <QString>

// includes from current project
#include "entity_global.h"

// pointer definition
class ENTITYSHARED_EXPORT SubPacket;
typedef std::shared_ptr<SubPacket> SubPacketPtr;

class ENTITYSHARED_EXPORT SubPacket
{
public:
    SubPacket();
    virtual ~SubPacket();
};

#endif // SUBPACKET_H
