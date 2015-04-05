#include "packet.h"

Packet::Packet() :
    sizeOfPacket(0),
    data()
{

}

Packet::~Packet()
{

}

// getters
unsigned int Packet::getSizeOfPacket(){
    return sizeOfPacket;
}

QByteArray Packet::getData(){
    return data;
}

// setters
void Packet::setSizeOfPacket(unsigned int input){
    sizeOfPacket = input;
}

void Packet::setData(QByteArray input){
    data = input;
}

void Packet::setData(const unsigned char* input){
    data = QByteArray(reinterpret_cast<const char*>(input));
}
