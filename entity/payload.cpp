#include "payload.h"

Payload::Payload(QObject *parent) :
    QAbstractTableModel(parent),
    size(0)
{

}

Payload::~Payload()
{

}
uint32_t Payload::getSize() const
{
    return size;
}

void Payload::setSize(const uint32_t &value)
{
    size = value;
}


