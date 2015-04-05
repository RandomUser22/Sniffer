#ifndef PACKET_H
#define PACKET_H

#include "entity_global.h"

// includes from QT
#include <QByteArray>

class ENTITYSHARED_EXPORT Packet;

// define the pointer definition
typedef std::shared_ptr<Packet> PacketPtr;

class ENTITYSHARED_EXPORT Packet
{
public:
    /**
        @brief Constructor for class Packet
     */
    Packet();

    /**
        @brief Destructor for class Packet
     */
    virtual ~Packet();

    // getters
    unsigned int getSizeOfPacket();
    QByteArray getData();

    // setters
    void setSizeOfPacket(unsigned int input);
    void setData(QByteArray input);
    void setData(const unsigned char* input);

private:
    /**
        @brief
     */
    unsigned int sizeOfPacket;

    /**
        @brief
     */
    QByteArray data;
};

#endif // PACKET_H
