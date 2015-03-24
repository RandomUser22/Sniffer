#include "interfacemanager.h"

InterfaceManager::InterfaceManager()
{

}

InterfaceManager::~InterfaceManager()
{

}

QList<QStringList> InterfaceManager::getListOfInterfacess()
{
    QList<QStringList> toReturn;
    QStringList temp;

    pcap_if_t *alldevs;
    pcap_if_t *d;

    char errbuf[PCAP_ERRBUF_SIZE];

    // Find the device's that can be listended to
    if (pcap_findalldevs(&alldevs, errbuf) != 0)
    {
        fprintf(stderr,"Eroare la cautarea de interfete: %s\n", errbuf);
    }
    else
    {
        // Save the list
        for(d= alldevs; d != NULL; d= d->next)
        {
            temp << QString(d->name);
            toReturn.push_back(temp);
        }
    }

    if(alldevs)
    {
        // free the list
        pcap_freealldevs(alldevs);
    }

    return toReturn;
}

QList<QStringList> InterfaceManager::getDetailsOfInterface(QString inter)
{
    (void)inter;

    QList<QStringList> toReturn;
    return toReturn;
}
