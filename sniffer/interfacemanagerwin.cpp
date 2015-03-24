#include "interfacemanager.h"

#include <QDebug>

#include <iphlpapi.h>
#include <stdio.h>
#include <stdlib.h>

#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))

#define WORKING_BUFFER_SIZE 15000
#define MAX_TRIES 3

#pragma comment(lib, "iphlpapi.lib")

InterfaceManager::InterfaceManager()
{

}

InterfaceManager::~InterfaceManager()
{

}

QList<QStringList> InterfaceManager::getListOfInterfacess()
{
    {

        /* Declare and initialize variables */

        int argc = 2;
        char *argv[] = { "4" , "A" };

        DWORD dwSize = 0;
        DWORD dwRetVal = 0;

        unsigned int i = 0;

        // Set the flags to pass to GetAdaptersAddresses
        ULONG flags = GAA_FLAG_INCLUDE_PREFIX;

        // default to unspecified address family (both)
        ULONG family = AF_UNSPEC;

        LPVOID lpMsgBuf = NULL;

        PIP_ADAPTER_ADDRESSES pAddresses = NULL;
        ULONG outBufLen = 0;
        ULONG Iterations = 0;

        PIP_ADAPTER_ADDRESSES pCurrAddresses = NULL;
        PIP_ADAPTER_UNICAST_ADDRESS pUnicast = NULL;
        PIP_ADAPTER_ANYCAST_ADDRESS pAnycast = NULL;
        PIP_ADAPTER_MULTICAST_ADDRESS pMulticast = NULL;
        IP_ADAPTER_DNS_SERVER_ADDRESS *pDnServer = NULL;
        IP_ADAPTER_PREFIX *pPrefix = NULL;

        if (argc != 2) {
            qDebug(" Usage: getadapteraddresses family\n");
            qDebug("        getadapteraddresses 4 (for IPv4)\n");
            qDebug("        getadapteraddresses 6 (for IPv6)\n");
            qDebug("        getadapteraddresses A (for both IPv4 and IPv6)\n");
            exit(1);
        }

        if (atoi(argv[1]) == 4)
            family = AF_INET;
        else if (atoi(argv[1]) == 6)
            family = AF_INET6;

        qDebug("Calling GetAdaptersAddresses function with family = ");
        if (family == AF_INET)
            qDebug("AF_INET\n");
        if (family == AF_INET6)
            qDebug("AF_INET6\n");
        if (family == AF_UNSPEC)
            qDebug("AF_UNSPEC\n\n");

        // Allocate a 15 KB buffer to start with.
        outBufLen = WORKING_BUFFER_SIZE;

        do {

            pAddresses = (IP_ADAPTER_ADDRESSES *) MALLOC(outBufLen);
            if (pAddresses == NULL) {
                printf
                    ("Memory allocation failed for IP_ADAPTER_ADDRESSES struct\n");
                exit(1);
            }

            dwRetVal =
                GetAdaptersAddresses(family, flags, NULL, pAddresses, &outBufLen);

            if (dwRetVal == ERROR_BUFFER_OVERFLOW) {
                FREE(pAddresses);
                pAddresses = NULL;
            } else {
                break;
            }

            Iterations++;

        } while ((dwRetVal == ERROR_BUFFER_OVERFLOW) && (Iterations < MAX_TRIES));

        if (dwRetVal == NO_ERROR) {
            // If successful, output some information from the data we received
            pCurrAddresses = pAddresses;
            while (pCurrAddresses) {
                qDebug("\tLength of the IP_ADAPTER_ADDRESS struct: %ld\n",
                       pCurrAddresses->Length);
                qDebug("\tIfIndex (IPv4 interface): %u\n", pCurrAddresses->IfIndex);
                qDebug("\tAdapter name: %s\n", pCurrAddresses->AdapterName);

                qDebug("\tAdapter descr:");
                qDebug(QString::fromWCharArray(pCurrAddresses->Description).toLatin1());

                pUnicast = pCurrAddresses->FirstUnicastAddress;
                if (pUnicast != NULL) {
                    for (i = 0; pUnicast != NULL; i++)
                        pUnicast = pUnicast->Next;
                    qDebug("\tNumber of Unicast Addresses: %d\n", i);
                } else
                    qDebug("\tNo Unicast Addresses\n");

                pAnycast = pCurrAddresses->FirstAnycastAddress;
                if (pAnycast) {
                    for (i = 0; pAnycast != NULL; i++)
                        pAnycast = pAnycast->Next;
                    qDebug("\tNumber of Anycast Addresses: %d\n", i);
                } else
                    qDebug("\tNo Anycast Addresses\n");

                pMulticast = pCurrAddresses->FirstMulticastAddress;
                if (pMulticast) {
                    for (i = 0; pMulticast != NULL; i++)
                        pMulticast = pMulticast->Next;
                    qDebug("\tNumber of Multicast Addresses: %d\n", i);
                } else
                    qDebug("\tNo Multicast Addresses\n");

                pDnServer = pCurrAddresses->FirstDnsServerAddress;
                if (pDnServer) {
                    for (i = 0; pDnServer != NULL; i++)
                        pDnServer = pDnServer->Next;
                    qDebug("\tNumber of DNS Server Addresses: %d\n", i);
                } else
                    qDebug("\tNo DNS Server Addresses\n");

                qDebug("\tDNS Suffix: %wS\n", pCurrAddresses->DnsSuffix);
                qDebug("\tDescription: %wS\n", pCurrAddresses->Description);
                qDebug("\tFriendly name: %wS\n", pCurrAddresses->FriendlyName);

                if (pCurrAddresses->PhysicalAddressLength != 0) {
                    qDebug("\tPhysical address: ");
                    for (i = 0; i < (int) pCurrAddresses->PhysicalAddressLength;
                         i++) {
                        if (i == (pCurrAddresses->PhysicalAddressLength - 1))
                            qDebug("%.2X\n",
                                   (int) pCurrAddresses->PhysicalAddress[i]);
                        else
                            qDebug("%.2X-",
                                   (int) pCurrAddresses->PhysicalAddress[i]);
                    }
                }
                qDebug("\tFlags: %ld\n", pCurrAddresses->Flags);
                qDebug("\tMtu: %lu\n", pCurrAddresses->Mtu);
                qDebug("\tIfType: %ld\n", pCurrAddresses->IfType);
                qDebug("\tOperStatus: %ld\n", pCurrAddresses->OperStatus);
                qDebug("\tIpv6IfIndex (IPv6 interface): %u\n",
                       pCurrAddresses->Ipv6IfIndex);
                qDebug("\tZoneIndices (hex): ");
                for (i = 0; i < 16; i++)
                    qDebug("%lx ", pCurrAddresses->ZoneIndices[i]);
                qDebug("\n");

                qDebug("\tTransmit link speed: %I64u\n", pCurrAddresses->TransmitLinkSpeed);
                qDebug("\tReceive link speed: %I64u\n", pCurrAddresses->ReceiveLinkSpeed);

                pPrefix = pCurrAddresses->FirstPrefix;
                if (pPrefix) {
                    for (i = 0; pPrefix != NULL; i++)
                        pPrefix = pPrefix->Next;
                    qDebug("\tNumber of IP Adapter Prefix entries: %d\n", i);
                } else
                    qDebug("\tNumber of IP Adapter Prefix entries: 0\n");

                qDebug("\n");

                pCurrAddresses = pCurrAddresses->Next;
            }
        } else {
            qDebug("Call to GetAdaptersAddresses failed with error: %d\n",
                   dwRetVal);
            if (dwRetVal == ERROR_NO_DATA)
                qDebug("\tNo addresses were found for the requested parameters\n");
            else {

                if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
                        FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                        NULL, dwRetVal, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                        // Default language
                        (LPTSTR) & lpMsgBuf, 0, NULL)) {
                    qDebug("\tError: %s", lpMsgBuf);
                    LocalFree(lpMsgBuf);
                    if (pAddresses)
                        FREE(pAddresses);
                    exit(1);
                }
            }
        }

        if (pAddresses) {
            FREE(pAddresses);
        }

    }
    QList<QStringList> toReturn;
    QStringList temp;

    pcap_if_t *alldevs;
    pcap_if_t *d;

    char errbuf[PCAP_ERRBUF_SIZE];

    /* Retrieve the device list from the local machine */
    if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL /* auth is not needed */, &alldevs, errbuf) == -1)
    {
        fprintf(stderr,"Eroare la cautarea de interfete: %s\n", errbuf);
    }
    else
    {
        QString devName;
        QStringList detailAdapterNetwork;

        // Save the list
        for(d= alldevs; d != NULL; d= d->next)
        {
            // adding the device name
            devName = QString(d->name);
            temp << devName;

            // adding the device description if it has one
            if(d->description) {
                temp << QString(d->description);
            } else {
                temp << QString("");
            }

            // adding the actual description from the GetAdaptersInfo()
            detailAdapterNetwork = getAdaptersInfo(devName);
            if(detailAdapterNetwork.size() >= 2) {
                temp << detailAdapterNetwork.at(2);
            } else {
                temp << QString("");
            }

            toReturn << temp;
            temp.clear();
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

QStringList InterfaceManager::getAdaptersInfo(QString adaptName)
{
    QStringList toReturn;

//    PIP_ADAPTER_INFO pAdapterInfo;
//    PIP_ADAPTER_INFO pAdapter = NULL;
//    DWORD dwRetVal = 0;

//    ULONG ulOutBufLen = sizeof (IP_ADAPTER_INFO);
//    pAdapterInfo = (IP_ADAPTER_INFO *) MALLOC(sizeof (IP_ADAPTER_INFO));
//    if (pAdapterInfo == NULL)
//    {
//        qDebug("Error allocating memory needed to call GetAdaptersinfo\n");
//    }
//    else
//    {
//        // Make an initial call to GetAdaptersInfo to get
//        // the necessary size into the ulOutBufLen variable
//        if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) ==
//                ERROR_BUFFER_OVERFLOW)
//        {
//            FREE(pAdapterInfo);
//            pAdapterInfo = (IP_ADAPTER_INFO *) MALLOC(ulOutBufLen);
//            if (pAdapterInfo == NULL)
//            {
//                qDebug("Error allocating memory needed to call GetAdaptersinfo\n");
//            }
//            else
//            {
//                if ((dwRetVal = GetAdaptersInfo(pAdapterInfo, &ulOutBufLen)) ==
//                        NO_ERROR)
//                {
//                    pAdapter = pAdapterInfo;
//                    while (pAdapter)
//                    {
//                        toReturn << QString(pAdapter->ComboIndex);
//                        toReturn << QString(pAdapter->AdapterName);
//                        toReturn << QString(pAdapter->Description);
//                        toReturn << getAdapterType(pAdapter->Type);

//                        pAdapter = pAdapter->Next;
//                    }
//                }
//                else
//                {
//                    qDebug("GetAdaptersInfo failed with error: %d\n", dwRetVal);
//                }
//                if (pAdapterInfo)
//                    FREE(pAdapterInfo);
//            }
//        }
//    }
    return toReturn;
}

QString InterfaceManager::getAdapterType(UINT type)
{
    QString toReturn;
    switch (type) {
        case MIB_IF_TYPE_OTHER:
            toReturn = QString("Other\n");
            break;
        case MIB_IF_TYPE_ETHERNET:
            toReturn = QString("Ethernet\n");
            break;
        case MIB_IF_TYPE_TOKENRING:
            toReturn = QString("Token Ring\n");
            break;
        case MIB_IF_TYPE_FDDI:
            toReturn = QString("FDDI\n");
            break;
        case MIB_IF_TYPE_PPP:
            toReturn = QString("PPP\n");
            break;
        case MIB_IF_TYPE_LOOPBACK:
            toReturn = QString("Lookback\n");
            break;
        case MIB_IF_TYPE_SLIP:
            toReturn = QString("Slip\n");
            break;
        case IF_TYPE_IEEE80211:
            toReturn = QString("WIFI\n");
            break;
        default:
            toReturn = QString("Unknown type %1\n").arg(QString::number(type));
            break;
    }

    return toReturn;
}
/*
int printAdaptersInfo()
{
    qDebug() << "Start printAdaptersInfo";

    // Declare and initialize variables

// It is possible for an adapter to have multiple
// IPv4 addresses, gateways, and secondary WINS servers
// assigned to the adapter.
//
// Note that this sample code only prints out the
// first entry for the IP address/mask, and gateway, and
// the primary and secondary WINS server for each adapter.

    PIP_ADAPTER_INFO pAdapterInfo;
    PIP_ADAPTER_INFO pAdapter = NULL;
    DWORD dwRetVal = 0;
    UINT i;

// variables used to print DHCP time info
    struct tm newtime;
    char buffer[32];
    errno_t error;

    ULONG ulOutBufLen = sizeof (IP_ADAPTER_INFO);
    pAdapterInfo = (IP_ADAPTER_INFO *) MALLOC(sizeof (IP_ADAPTER_INFO));
    if (pAdapterInfo == NULL) {
        qDebug("Error allocating memory needed to call GetAdaptersinfo\n");
        return 1;
    }
// Make an initial call to GetAdaptersInfo to get
// the necessary size into the ulOutBufLen variable
    if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW) {
        FREE(pAdapterInfo);
        pAdapterInfo = (IP_ADAPTER_INFO *) MALLOC(ulOutBufLen);
        if (pAdapterInfo == NULL) {
            qDebug("Error allocating memory needed to call GetAdaptersinfo\n");
            return 1;
        }
    }

    if ((dwRetVal = GetAdaptersInfo(pAdapterInfo, &ulOutBufLen)) == NO_ERROR) {
        pAdapter = pAdapterInfo;
        while (pAdapter) {
            qDebug("\tComboIndex: \t%d\n", pAdapter->ComboIndex);
            qDebug("\tAdapter Name: \t%s\n", pAdapter->AdapterName);
            qDebug("\tAdapter Desc: \t%s\n", pAdapter->Description);
            qDebug("\tAdapter Addr: \t");
            for (i = 0; i < pAdapter->AddressLength; i++) {
                if (i == (pAdapter->AddressLength - 1))
                    qDebug("%.2X\n", (int) pAdapter->Address[i]);
                else
                    qDebug("%.2X-", (int) pAdapter->Address[i]);
            }
            qDebug("\tIndex: \t%d\n", pAdapter->Index);
            qDebug("\tType: \t");
            switch (pAdapter->Type) {
            case MIB_IF_TYPE_OTHER:
                qDebug("Other\n");
                break;
            case MIB_IF_TYPE_ETHERNET:
                qDebug("Ethernet\n");
                break;
            case MIB_IF_TYPE_TOKENRING:
                qDebug("Token Ring\n");
                break;
            case MIB_IF_TYPE_FDDI:
                qDebug("FDDI\n");
                break;
            case MIB_IF_TYPE_PPP:
                qDebug("PPP\n");
                break;
            case MIB_IF_TYPE_LOOPBACK:
                qDebug("Lookback\n");
                break;
            case MIB_IF_TYPE_SLIP:
                qDebug("Slip\n");
                break;
            case IF_TYPE_IEEE80211:
                qDebug("WIFI\n");
                break;
            default:
                qDebug("Unknown type %ld\n", pAdapter->Type);
                break;
            }

            qDebug("\tIP Address: \t%s\n",
                   pAdapter->IpAddressList.IpAddress.String);
            qDebug("\tIP Mask: \t%s\n", pAdapter->IpAddressList.IpMask.String);

            qDebug("\tGateway: \t%s\n", pAdapter->GatewayList.IpAddress.String);
            qDebug("\t***\n");

            if (pAdapter->DhcpEnabled) {
                qDebug("\tDHCP Enabled: Yes\n");
                qDebug("\t  DHCP Server: \t%s\n",
                       pAdapter->DhcpServer.IpAddress.String);

                qDebug("\t  Lease Obtained: ");
                // Display local time
                error = _localtime32_s(&newtime, (__time32_t*) &pAdapter->LeaseObtained);
                if (error)
                    qDebug("Invalid Argument to _localtime32_s\n");
                else {
                    // Convert to an ASCII representation
                    error = asctime_s(buffer, 32, &newtime);
                    if (error)
                        qDebug("Invalid Argument to asctime_s\n");
                    else
                        // asctime_s returns the string terminated by \n\0
                        qDebug("%s", buffer);
                }

                qDebug("\t  Lease Expires:  ");
                error = _localtime32_s(&newtime, (__time32_t*) &pAdapter->LeaseExpires);
                if (error)
                    qDebug("Invalid Argument to _localtime32_s\n");
                else {
                    // Convert to an ASCII representation
                    error = asctime_s(buffer, 32, &newtime);
                    if (error)
                        qDebug("Invalid Argument to asctime_s\n");
                    else
                        // asctime_s returns the string terminated by \n\0
                        qDebug("%s", buffer);
                }
            } else
                qDebug("\tDHCP Enabled: No\n");

            if (pAdapter->HaveWins) {
                qDebug("\tHave Wins: Yes\n");
                qDebug("\t  Primary Wins Server:    %s\n",
                       pAdapter->PrimaryWinsServer.IpAddress.String);
                qDebug("\t  Secondary Wins Server:  %s\n",
                       pAdapter->SecondaryWinsServer.IpAddress.String);
            } else
                qDebug("\tHave Wins: No\n");
            pAdapter = pAdapter->Next;
            qDebug("\n");
        }
    } else {
        qDebug("GetAdaptersInfo failed with error: %d\n", dwRetVal);

    }
    if (pAdapterInfo)
        FREE(pAdapterInfo);

    qDebug() << "end printAdaptersInfo";
}
*/
