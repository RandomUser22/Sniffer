#define HAVE_REMOTE

#include "networkinterfacemanager.h"

#include <winsock2.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdint>

#pragma comment(lib, "iphlpapi.lib")


/* From tcptraceroute, convert a numeric IP address to a string */
#define IPTOSBUFFERS    12
char *iptos(u_long in)
{
    static char output[IPTOSBUFFERS][3*4+3+1];
    static short which;
    u_char *p;

    p = (u_char *)&in;
    which = (which + 1 == IPTOSBUFFERS ? 0 : which + 1);
    _snprintf_s(output[which], sizeof(output[which]), sizeof(output[which]),"%d.%d.%d.%d", p[0], p[1], p[2], p[3]);
    return output[which];
}

char* ip6tos(struct sockaddr *sockaddr, char *address, int addrlen)
{
    socklen_t sockaddrlen;

#ifdef WIN32
    sockaddrlen = sizeof(struct sockaddr_in6);
#else
    sockaddrlen = sizeof(struct sockaddr_storage);
#endif


    if(getnameinfo(sockaddr,
                   sockaddrlen,
                   address,
                   addrlen,
                   NULL,
                   0,
                   NI_NUMERICHOST) != 0) address = NULL;

    return address;
}

// implementation of the method for windows machines
QList<NetworkInterfacePtr> NetworkInterfaceManager::getListOfSniffingInterfacess()
{
    // what we will return at the end of the method
    QList<NetworkInterfacePtr> toReturn;

    // temporary object used to store information
    // about a certain interface
    NetworkInterfacePtr adaptName;

    pcap_if_t *alldevs;

    pcap_addr_t *a;
    char ip6str[128];

    // error buffer
    char errbuf[PCAP_ERRBUF_SIZE];

    // clear the buffer before displaying
    memset(&errbuf[0], 0, sizeof(errbuf));

    int res = pcap_findalldevs_ex(PCAP_SRC_IF_STRING,
                                  NULL /* auth is not needed */,
                                  &alldevs,
                                  errbuf);

    // Retrieve the device list from the local machine
    if (res == -1)
    {
        // if the operation was not successful,
        // then throw an exception
        std::string exceptionText("Error finding interfaces: ");
        exceptionText.append(errbuf);
        throw PcapException(exceptionText.c_str());
    }
    else
    {
        // Save the list
        for(pcap_if_t* d= alldevs; d != NULL; d= d->next)
        {
            // create a new network interface object
            adaptName.reset(new NetworkInterface());

            // adding the device name
            adaptName->setPcapName(QString(d->name));

            // adding the device description if it has one
            if(d->description) {
                adaptName->setPcapDescription(
                            QString(d->description));
            } else {
                adaptName->setPcapDescription(
                            QString(""));
            }

            // Loopback Address
            adaptName->setPcapLoopback((d->flags & PCAP_IF_LOOPBACK)?true:false);

            /* IP addresses */
            for(a=d->addresses;a;a=a->next) {
                adaptName->getPcapAddress()
                        ->setAddressFamilyNumber(a->addr->sa_family);

                switch(a->addr->sa_family)
                {
                case AF_INET:
                    adaptName->getPcapAddress()->setAddressFamilyName("AF_INET");
                    if (a->addr)
                    {
                        QString temp(iptos(((struct sockaddr_in *)a->addr)->sin_addr.s_addr));
                        temp = temp.split('%').at(0);
                        adaptName->getPcapAddress()->setAddress(temp);
                    }
                    if (a->netmask)
                        adaptName->getPcapAddress()->setNetmask(QString(iptos(((struct sockaddr_in *)a->netmask)->sin_addr.s_addr)));
                    if (a->broadaddr)
                        adaptName->getPcapAddress()->setBroadcastAddress(QString(iptos(((struct sockaddr_in *)a->broadaddr)->sin_addr.s_addr)));
                    if (a->dstaddr)
                        adaptName->getPcapAddress()->setDestinationAddress(QString(iptos(((struct sockaddr_in *)a->dstaddr)->sin_addr.s_addr)));
                    break;
                case AF_INET6:
                    adaptName->getPcapAddress()->setAddressFamilyName("AF_INET6");
                    if (a->addr)
                        adaptName->getPcapAddress()->setAddress(QString(ip6tos(a->addr, ip6str, sizeof(ip6str))).split('%').at(0));
                    break;
                default:
                    adaptName->getPcapAddress()->setAddressFamilyName("Unknown");
                    break;
                }
            }


            // get aditional information
            // these variables are passed as parameters
            // to the GetAdaptersInfo function
            IP_ADAPTER_INFO  *pAdapterInfo;
            ULONG             ulOutBufLen;

            // also create a DWORD variable called dwRetVal
            // (for error checking)
            DWORD            dwRetVal;

            // allocate memory for the structures
            pAdapterInfo = (IP_ADAPTER_INFO *)
                    malloc( sizeof(IP_ADAPTER_INFO) );
            ulOutBufLen = sizeof(IP_ADAPTER_INFO);

            // Make an initial call to GetAdaptersInfo to get
            // the size needed into the ulOutBufLen variable.
            // Note  This call to the function is meant to fail,
            // and is used to ensure that the ulOutBufLen variable
            // specifies a size sufficient for holding
            // all the information returned to pAdapterInfo.
            // This is a common programming model for data structures
            // and functions of this type.
            if (GetAdaptersInfo(
                        pAdapterInfo,
                        &ulOutBufLen) != ERROR_SUCCESS) {
                free (pAdapterInfo);
                pAdapterInfo = (IP_ADAPTER_INFO *)
                        malloc ( ulOutBufLen );
            }

            // Make a second call to GetAdaptersInfo,
            // passing pAdapterInfo and ulOutBufLen as parameters
            // and doing general error checking.
            // Return its value to the DWORD variable dwRetVal
            // (for more extensive error checking).

            dwRetVal = GetAdaptersInfo( pAdapterInfo, &ulOutBufLen);

            if (dwRetVal != ERROR_SUCCESS) {
                qDebug("GetAdaptersInfo call failed with %d\n", dwRetVal);
            }

            // If the call was successful,
            // access some of the data in the pAdapterInfo structure.
            PIP_ADAPTER_INFO pAdapter = pAdapterInfo;

            QString devName = adaptName->getPcapName();
            QStringList tempList = devName.split("_");
            devName = tempList.at(1);

            while (pAdapter){

                if(devName == QString(pAdapter->AdapterName))
                {
                    adaptName->setName(QString(pAdapter->AdapterName));
                    adaptName->setDescription(QString(pAdapter->Description));
                    switch (pAdapter->Type) {
                    case MIB_IF_TYPE_OTHER:
                        adaptName->setAdapterType(entity::adapter_type_other);
                        break;
                    case MIB_IF_TYPE_ETHERNET:
                        adaptName->setAdapterType(entity::adapter_type_ethernet);
                        break;
                    case MIB_IF_TYPE_TOKENRING:
                        adaptName->setAdapterType(entity::adapter_type_tokenring);
                        break;
                    case MIB_IF_TYPE_FDDI:
                        adaptName->setAdapterType(entity::adapter_type_fddi);
                        break;
                    case MIB_IF_TYPE_PPP:
                        adaptName->setAdapterType(entity::adapter_type_ppp);
                        break;
                    case MIB_IF_TYPE_LOOPBACK:
                        adaptName->setAdapterType(entity::adapter_type_loopback);
                        break;
                    case MIB_IF_TYPE_SLIP:
                        adaptName->setAdapterType(entity::adapter_type_slip);
                        break;
                    case IF_TYPE_IEEE80211:
                        adaptName->setAdapterType(entity::adapter_type_ieee80211);
                        break;
                    default:
                        adaptName->setAdapterType(entity::adapter_type_unknown);
                        break;
                    }
                    std::stringstream ss;
                    char buffer[20];
                    for (unsigned int i = 0; i < pAdapter->AddressLength; i++) {
                        if (i == (pAdapter->AddressLength - 1)){
                            sprintf_s(buffer, "%.2X\n",(int)pAdapter->Address[i]);
                        }
                        else {
                            sprintf_s(buffer, "%.2X-",(int)pAdapter->Address[i]);
                        }
                        ss << buffer;
                    }
                    adaptName->setAdapterAddress(QString(ss.str().c_str()));
                    adaptName->setIpAddress(QString(pAdapter->IpAddressList.IpAddress.String));
                    adaptName->setIpMask(QString(pAdapter->IpAddressList.IpMask.String));
                    adaptName->setGateway(QString(pAdapter->GatewayList.IpAddress.String));
                    if (pAdapter->DhcpEnabled) {
                        adaptName->setDhcpEnabled(true);
                        adaptName->setDhcpServer(QString(pAdapter->DhcpServer.IpAddress.String));
                    }
                }
                pAdapter = pAdapter->Next;
            }


            // Free any memory allocated for the pAdapterInfo structure.
            if (pAdapterInfo)
                free(pAdapterInfo);

            // add to the list of interfaces
            toReturn.push_back(adaptName);
        }
    }

    if(alldevs)
    {
        // free the list
        pcap_freealldevs(alldevs);
    }
    return toReturn;
}

