#include "sniffermanager.h"
#include <iostream>

SnifferManagerPtr SnifferManager::instance;
int SnifferManager::count;

SnifferManagerPtr SnifferManager::getInstance()
{
    // check to see if the instance is pointing to a valid object
    if(!instance)
    {
        // if not then create one
        instance = SnifferManagerPtr(new SnifferManager());
    }
    // return the single instance
    return instance;
}

void SnifferManager::removeInstance()
{
    // check to see if the instance exists
    if(instance)
    {
        // if it exists then delete it
        instance.reset();
    }
}

SnifferManager::SnifferManager():
    device(),
    handle(NULL),
    mask(0),
    net(0),
    filter_exp((char*)"ip"),
    count(0)
{

}

SnifferManager::~SnifferManager()
{
    free(handle);
}

void SnifferManager::callbackPacketReceived(u_char *args,
                            const struct pcap_pkthdr *header,
                            const u_char *packet)
{
    QStringList packageReceived;

    /* declare pointers to packet headers */
    const ethernet_header *ethernet;  /* The ethernet header [1] */
    const ip_header *ip;              /* The IP header */
    const tcp_packet *tcp;            /* The TCP header */
    const unsigned char *payload;              /* Packet payload */

    int size_ip;
    int size_tcp;
    int size_payload;

    /* define ethernet header */
    ethernet = (ethernet_header*)(packet);

    /* define/compute ip header offset */
    ip = (ip_header*)(packet + HEADER_FRAME_SIZE);
    size_ip = IP_HL(ip)*4;

    if (size_ip >= 20)
    {
        /* determine protocol */
        switch(ip->protocol)
        {
            case IPPROTO_TCP:
                break;
            case IPPROTO_UDP:
                return;
            case IPPROTO_ICMP:
                return;
            case IPPROTO_IP:
                return;
            default:
                return;
        }

        /*
         *  OK, this packet is TCP.
         */

        /* define/compute tcp header offset */
        tcp = (tcp_packet*)(packet + HEADER_FRAME_SIZE + size_ip);

        size_tcp = TH_OFF(tcp)*4;
        if (size_tcp >= 20)
        {
            /* define/compute tcp payload (segment) offset */
            payload = (u_char *)(packet + HEADER_FRAME_SIZE +
                                 size_ip +
                                 size_tcp);

            /* compute tcp payload (segment) size */
            size_payload = ntohs(ip->length) -
                    (size_ip + size_tcp);

            /*
             * Print payload data; it might be binary, so don't just
             * treat it as a string.
             */
            if (size_payload > 0)
            {
                count++;
                QString tempString;
                tempString.setNum(count);
                packageReceived << tempString;
                tempString.clear();
                tempString.setNum(size_payload);
                packageReceived << tempString;
                packageReceived << instance->
                                   interpretPayload(size_payload,
                                                    payload);

                emit instance->packageCaptured(packageReceived);
            }
        }
    }
}

void SnifferManager::startSniffing()
{
    qDebug("2");
    if(this->device != NULL)
    {
        /* get network number and mask associated with capture device */
        if (pcap_lookupnet(Utility::qStringToCharP(device),
                           &net, &mask, errbuf) == -1)
        {
            fprintf(stderr,
                    "Couldn't get netmask for device %s: %s\n",
                Utility::qStringToCharP(device), errbuf);
            net = 0;
            mask = 0;
        }

        /* open capture device */
        this->handle =
                pcap_open_live(Utility::qStringToCharP(device),
                                    FRAME_MAX_SIZE, 1, 1000,
                               errbuf);
        if (this->handle == NULL)
        {
            fprintf(stderr, "Couldn't open device %s: %s\n",
                Utility::qStringToCharP(device), errbuf);
        }
        else
        {
            /* make sure we're capturing on an Ethernet device [2] */
            if (pcap_datalink(this->handle) != DLT_EN10MB) {
                fprintf(stderr, "%s is not an Ethernet\n",
                        Utility::qStringToCharP(device));
            }

            /* compile the filter expression */
            if (pcap_compile(this->handle,
                             &fp, filter_exp, 0, net) == -1) {
                fprintf(stderr,
                        "Couldn't parse filter %s: %s\n",
                    filter_exp, pcap_geterr(this->handle));
            }
            else
            {
                /* apply the compiled filter */
                if (pcap_setfilter(this->handle, &fp) == -1) {
                    fprintf(stderr, "Couldn't install filter %s: %s\n",
                        filter_exp, pcap_geterr(this->handle));
                }
                else
                {
                    /* now we can set our callback function */
                    pcap_loop(this->handle,
                              MAX_NR_OF_PACKETS,
                              SnifferManager::callbackPacketReceived, NULL);
                }
            }

        }
    }
}

void SnifferManager::setInterfaceToSniffOn(QString device)
{
    this->device = device;
}

QString SnifferManager::interpretPayload(int size,
                         const unsigned char *payload)
{
    int auxSize = size;
    const unsigned char *auxPa = payload;

    int lineWidth = 16;
    int lineLen;
    int offset = 0;

    QString s;

    if(size > 0)
    {
          // data is on multiple lines
          if(size > lineWidth)
          {
                while(1)
                {
                    lineLen = lineWidth % auxSize;

                    s.append(this->formatPayload(auxPa, lineLen, offset));

                    auxSize = auxSize - lineLen;

                    auxPa = auxPa + lineLen;

                    offset = offset + lineWidth;

                    if(auxSize <= lineWidth)
                    {
                        s.append(this->formatPayload(auxPa, auxSize, offset));
                        break;
                    }
                }
          }
          // data is on one line
          else
          {
                s.append(this->formatPayload(auxPa, size, offset));
          }
    }

    return s;
}

QString SnifferManager::formatPayload(
        const unsigned char *payload,
                      int len,
                      int offset)
{
    QString s;
    int i;
    int gap;
    const unsigned char *ch;

    ch = payload;

    s.sprintf("%05d   ", offset);

    for(i = 0; i< len; i++)
    {
        s.sprintf("%02x ", *ch);
        ch++;

        if (i == 7)
             s.sprintf(" ");
    }
    /* print space to handle line less than 8 bytes */
    if (len < 8)
        s.sprintf(" ");

    /* fill hex gap with spaces if not full line */
    if (len < 16) {
        gap = 16 - len;
        for (i = 0; i < gap; i++) {
            s.sprintf("   ");
        }
    }
    s.sprintf("   ");

    return s;
}
