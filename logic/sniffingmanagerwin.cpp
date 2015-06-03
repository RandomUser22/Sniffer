#define HAVE_REMOTE

#include <QDebug>
#include "sniffingmanager.h"

void SniffingManager::startSniffing(
        NetworkInterfacePtr inter,
        uint32_t nrOfPacketsToCapture)
{
    if(inter)
    {
        stopSingnaled = false;
        QString deviceName = inter->getPcapName();
        bool canCapture = true;
        uint32_t count = 0;

        PacketPtr output;

        // generic per-packet information - see pcap.h
        struct pcap_pkthdr *header;

        // data from the packet
        const u_char *pkt_data;

        // error buffer
        char errbuf[PCAP_ERRBUF_SIZE];

        // clear the buffer before displaying
        memset(&errbuf[0], 0, sizeof(errbuf));

        // obtain a handle for our current device we are tring to sniff
        handle = pcap_open(deviceName.toLocal8Bit().data(),     // device
                           65536,                             // snaplen
                           PCAP_OPENFLAG_PROMISCUOUS,       // flags
                           1000,                              // read timeout
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

            while(canCapture)
            {
                res = pcap_next_ex( handle, &header, &pkt_data);
                if(res > 0)
                {
                    output.reset(new Packet());

                    count++;
                    // if the legth of the packet if greater than 0
                    // then save the data and show it on the screen

                    // add the size of the payload
                    output->setSizeOfPacket(header->len);

                    // add the payload
                    output->setRawData(pkt_data);

                    // signal the capturing of a package
                    emit packageCaptured(output);
                }
                else if(res == 0)
                {
                    continue;
                }

                mutex.lock();
                if(((nrOfPacketsToCapture != 0) &&
                    (count >= nrOfPacketsToCapture)) ||
                        stopSingnaled)
                {
                    canCapture = false;
                    stopSingnaled = false;
                }
                mutex.unlock();
            }
        }
    }
}

void SniffingManager::stopSniffing()
{
    mutex.lock();
    stopSingnaled = true;
    mutex.unlock();
}
