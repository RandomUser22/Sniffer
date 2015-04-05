#include "sniffermanager.h"
#include <iostream>

SnifferManagerPtr SnifferManager::instance;
unsigned int SnifferManager::count = 0;

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
    filter_exp((char*)"ip")
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

}

void SnifferManager::startSniffing()
{
    // generic per-packet information - see pcap.h
    struct pcap_pkthdr *header;

    // data from the packet
    const u_char *pkt_data;

    // the output string to be sent once capturing is done
    PacketPtr output = PacketPtr(new Packet());

    // obtain a handle for our current device we are tring to sniff
    handle = pcap_open(device.toLocal8Bit().data(),     // device
                       100,                             // snaplen
                       PCAP_OPENFLAG_PROMISCUOUS,       // flags
                       20,                              // read timeout
                       NULL,                            // remote authentication
                       errbuf);                         // error buffer

    // check if the operation was successful
    if (handle == NULL)
    {
        // if the operation was not successful, then throw an exception
        std::string exceptionText("Error opening source: ");
        exceptionText.append(errbuf);
        throw PcapException(exceptionText.c_str());
    }
    else
    {
        // the result from capturing
        int res = 0;
        do
        {
            res = pcap_next_ex( handle, &header, &pkt_data);
            if(res > 0)
            {
                count++;

                // if the legth of the packet if greater than 0
                // then save the data and show it on the screen

                // add the size of the payload
                output->setSizeOfPacket(header->len);

                // add the payload
                output->setData(pkt_data);

                emit packageCaptured(count, output);

            }
            else if(res == 0)
            {
                //count++;

                // continue the sniffing
                // if the packet contains no data
                continue;
            }
//            else
//            {
//                fprintf(stderr, "Error reading the packets: %s\n", pcap_geterr(handle));
//            }
        }while(count < 10);
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

