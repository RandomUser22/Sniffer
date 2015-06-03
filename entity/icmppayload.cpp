#include "icmppayload.h"

IcmpPayload::IcmpPayload():
    Payload(),
    typeOfMessage(""),
    code(""),
    checksum(""),
    indentifier(""),
    sequenceNumber("")
{

}

IcmpPayload::~IcmpPayload()
{

}
QString IcmpPayload::getTypeOfMessage() const
{
    return typeOfMessage;
}

void IcmpPayload::setTypeOfMessage(const QString &value)
{
    typeOfMessage = value;
}
QString IcmpPayload::getCode() const
{
    return code;
}

void IcmpPayload::setCode(const QString &value)
{
    code = value;
}
QString IcmpPayload::getChecksum() const
{
    return checksum;
}

void IcmpPayload::setChecksum(const QString &value)
{
    checksum = value;
}
QString IcmpPayload::getIndentifier() const
{
    return indentifier;
}

void IcmpPayload::setIndentifier(const QString &value)
{
    indentifier = value;
}
QString IcmpPayload::getSequenceNumber() const
{
    return sequenceNumber;
}

void IcmpPayload::setSequenceNumber(const QString &value)
{
    sequenceNumber = value;
}

void IcmpPayload::setRawData(const QByteArray &data)
{

}

int IcmpPayload::rowCount(const QModelIndex &parent) const
{
    return 9;
}

int IcmpPayload::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant IcmpPayload::data(const QModelIndex &index, int role) const
{
    return QVariant();
}






