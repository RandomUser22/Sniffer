#include "packet.h"

Packet::Packet()
    :sizeOfPacket(0),
      rawData(),
      ethernetHeader(EthernetHeaderPtr(new EthernetHeader())),
      ipHeader(IpHeaderPtr(new IpHeader())),
      validIpHeader(false),
      payload()
{

}

Packet::~Packet()
{

}
EthernetHeaderPtr Packet::getEthernetHeader() const
{
    return ethernetHeader;
}
uint32_t Packet::getSizeOfPacket() const
{
    return sizeOfPacket;
}

void Packet::setSizeOfPacket(const uint32_t &value)
{
    sizeOfPacket = value;
}

void Packet::setRawData(const uint8_t *input)
{
    const struct ethernet_header *ethernet;
    const struct ip_header *ip;
    const struct tcp_packet *tcp;

    int size_ip;
    int size_tcp;
    int size_payload;

    // define ethernet header
    ethernet = (struct ethernet_header*)input;
    ethernetHeader->setMacDestination(ethernet->mac_dest);
    ethernetHeader->setMacSource(ethernet->mac_source);
    ethernetHeader->setFrameType(ethernet->frame_type);

    // define IP header
    ip = (struct ip_header*)(input + ETHERNET_HEADER_SIZE);
    size_ip = IP_HL(ip)*4;
    ipHeader->setSizeIp(size_ip);
    if (size_ip < 20) {
        validIpHeader = false;
    }
    else
    {
        validIpHeader = true;
        ipHeader->setVersion(ip->version);
        ipHeader->setTypeOfService(ip->type_of_service);
        ipHeader->setLength(ip->length);
        ipHeader->setId(ip->id);
        ipHeader->setOffsetIp(ip->offset);
        ipHeader->setTtl(ip->ttl);
        ipHeader->setProtocol(ip->protocol);
        ipHeader->setChecksumIp(ip->checksum);
        ipHeader->setIpSource(inet_ntoa(ip->ip_src));
        ipHeader->setIpDest(inet_ntoa(ip->ip_dst));
    }

    /* determine protocol */
    switch(ip->protocol) {
    case IPPROTO_TCP:
        qDebug("   Protocol: TCP\n");
        payload.reset(new TcpPayload);
        break;
    case IPPROTO_UDP:
        qDebug("   Protocol: UDP\n");
        payload.reset(new UdpPayload);
        break;
    case IPPROTO_ICMP:
        qDebug("   Protocol: ICMP\n");
        payload.reset(new IcmpPayload);
        break;
    case IPPROTO_IP:
        qDebug("   Protocol: IP\n");
        break;
    default:
        qDebug("   Protocol: unknown\n");
        break;
    }

    QByteArray data = QByteArray::fromRawData(reinterpret_cast<const char*>(input + ETHERNET_HEADER_SIZE + size_ip), sizeof(input + ETHERNET_HEADER_SIZE + size_ip));
    if(payload)
    {
        payload->setRawData(data);
    }

}
IpHeaderPtr Packet::getIpHeader() const
{
    return ipHeader;
}
PayloadPtr Packet::getPayload() const
{
    return payload;
}








