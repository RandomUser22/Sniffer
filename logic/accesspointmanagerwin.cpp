# include "accesspointmanager.h"

#include <windows.h>
#include <wlanapi.h>
#include <objbase.h>
#include <wtypes.h>

#include <stdio.h>
#include <stdlib.h>

// Need to link with Wlanapi.lib and Ole32.lib
#pragma comment(lib, "wlanapi.lib")
#pragma comment(lib, "ole32.lib")

HANDLE hClient = NULL;

WlanInterfacePtr AccessPointManager::getDetailedAccessPointInformation(NetworkInterfacePtr value)
{
    // declere the return list
    WlanInterfacePtr toReturn;

    // Declare and initialize variables.
    DWORD dwMaxClient = 2;
    DWORD dwCurVersion = 0;
    DWORD dwResult = 0;
    int iRet = 0;

    WCHAR GuidString[39] = {0};

    /* variables used for WlanEnumInterfaces  */
    PWLAN_INTERFACE_INFO_LIST pIfList = NULL;
    PWLAN_INTERFACE_INFO pIfInfo = NULL;

    PWLAN_AVAILABLE_NETWORK_LIST pBssList = NULL;
    PWLAN_AVAILABLE_NETWORK pBssEntry = NULL;

    int32_t iRSSI = 0;

    if(hClient == NULL)
    {
        dwResult = WlanOpenHandle(dwMaxClient, NULL, &dwCurVersion, &hClient);
        if (dwResult != ERROR_SUCCESS) {
            qDebug("WlanOpenHandle failed with error: %u\n", dwResult);
            // TODO: add exception handling
        }
    }


    dwResult = WlanEnumInterfaces(hClient, NULL, &pIfList);
    if (dwResult != ERROR_SUCCESS) {
        qDebug("WlanEnumInterfaces failed with error: %u\n", dwResult);
        // TODO: add exception handling
    }
    else
    {
        QString tempQstring;

        for (unsigned i = 0; i < (unsigned int) pIfList->dwNumberOfItems; i++)
        {
            pIfInfo = (WLAN_INTERFACE_INFO *) &pIfList->InterfaceInfo[i];
            tempQstring = QString::fromWCharArray(pIfInfo->strInterfaceDescription);

            if(!(tempQstring.compare(value->getDescription())))
            {
                toReturn = WlanInterfacePtr(new WlanInterface());
                toReturn->setAdapterAddress(value->getAdapterAddress());
                toReturn->setAdapterType(value->getAdapterType());
                toReturn->setDescription(value->getDescription());
                toReturn->setDhcpEnabled(value->getDhcpEnabled());
                toReturn->setDhcpServer(value->getDhcpServer());
                toReturn->setGateway(value->getGateway());
                toReturn->setIpAddress(value->getIpAddress());
                toReturn->setIpMask(value->getIpMask());
                toReturn->setName(value->getName());
                toReturn->setPcapDescription(value->getDescription());
                toReturn->setPcapLoopback(value->getPcapLoopback());
                toReturn->setPcapName(value->getPcapName());
                toReturn->setPcapAddress(value->getPcapAddress());

                pIfInfo = (WLAN_INTERFACE_INFO *) &pIfList->InterfaceInfo[i];

                iRet = StringFromGUID2(pIfInfo->InterfaceGuid, (LPOLESTR) &GuidString,
                                       sizeof(GuidString)/sizeof(*GuidString));
                if (iRet == 0)
                    qDebug("StringFromGUID2 failed\n");
                else
                {
                    // set the GUID
                    tempQstring = QString::fromWCharArray(GuidString, 39);
                    toReturn->setGuid(tempQstring);
                }
                tempQstring = QString::fromWCharArray(pIfInfo->strInterfaceDescription);
                toReturn->setWlanDescription(tempQstring);

                switch (pIfInfo->isState)
                {
                case wlan_interface_state_not_ready:
                    toReturn->setConnectionType(WlanConnectionType_not_ready);
                    break;
                case wlan_interface_state_connected:
                    toReturn->setConnectionType(WlanConnectionType_connected);
                    break;
                case wlan_interface_state_ad_hoc_network_formed:
                    toReturn->setConnectionType(WlanConnectionType_ad_hoc_network_formed);
                    break;
                case wlan_interface_state_disconnecting:
                    toReturn->setConnectionType(WlanConnectionType_disconecting);
                    break;
                case wlan_interface_state_disconnected:
                    toReturn->setConnectionType(WlanConnectionType_disconected);
                    break;
                case wlan_interface_state_associating:
                    toReturn->setConnectionType(WlanConnectionType_associating);
                    break;
                case wlan_interface_state_discovering:
                    toReturn->setConnectionType(WlanConnectionType_discovering);
                    break;
                case wlan_interface_state_authenticating:
                    toReturn->setConnectionType(WlanConnectionType_authenticateing);
                    break;
                default:
                    toReturn->setConnectionType(WlanConnectionType_unknown);
                    break;
                }

                dwResult = WlanGetAvailableNetworkList(hClient,
                                                       &pIfInfo->InterfaceGuid,
                                                       0,
                                                       NULL,
                                                       &pBssList);
                if (dwResult != ERROR_SUCCESS)
                {
                    qDebug("WlanGetAvailableNetworkList failed with error: %u\n",
                           dwResult);
                    // TODO: exception handling
                }
                else
                {
                    // declare a pointer for an available network
                    WlanAvailableConnectionPtr newAvailableNetwork;

                    for (unsigned int j = 0; j < pBssList->dwNumberOfItems; j++)
                    {
                        newAvailableNetwork = WlanAvailableConnectionPtr(new WlanAvailableConnection());

                        pBssEntry =
                                (WLAN_AVAILABLE_NETWORK *) & pBssList->Network[j];
                        tempQstring.clear();

                        for (unsigned int k = 0; k < pBssEntry->dot11Ssid.uSSIDLength; k++) {
                            tempQstring.append(QChar((int)pBssEntry->dot11Ssid.ucSSID[k]));
                        }
                        newAvailableNetwork->setSsid(tempQstring);

                        tempQstring.clear();
                        tempQstring = QString::fromWCharArray(pBssEntry->strProfileName);
                        newAvailableNetwork->setProfileName(tempQstring);

                        switch (pBssEntry->dot11BssType) {
                        case dot11_BSS_type_infrastructure   :
                            newAvailableNetwork->setBbsType(wlan_bss_type_infrastructure);
                            break;
                        case dot11_BSS_type_independent:
                            newAvailableNetwork->setBbsType(wlan_bss_type_independent);
                            break;
                        case dot11_BSS_type_any:
                            newAvailableNetwork->setBbsType(wlan_bss_type_any);
                            break;
                        default:
                            newAvailableNetwork->setBbsType(wlan_bss_type_unknown);
                            break;
                        }
                        newAvailableNetwork->setNrOfBssIds(pBssEntry->uNumberOfBssids);

                        if (pBssEntry->bNetworkConnectable)
                            newAvailableNetwork->setConnectable(true);
                        else {
                            newAvailableNetwork->setConnectable(false);
                            std::stringstream sstr;
                            sstr << pBssEntry->wlanNotConnectableReason;
                            std::string str = sstr.str();
                            newAvailableNetwork->setConnectableReason(QString::fromStdString(str));
                        }
                        newAvailableNetwork->setNrOfPhySupported(pBssEntry->uNumberOfPhyTypes);

                        // calculate the signal quality
                        if (pBssEntry->wlanSignalQuality == 0)
                            iRSSI = -100;
                        else if (pBssEntry->wlanSignalQuality == 100)
                            iRSSI = -50;
                        else
                            iRSSI = -100 + (pBssEntry->wlanSignalQuality/2);
                        newAvailableNetwork->setSignalQuality(pBssEntry->wlanSignalQuality);
                        qDebug(" --->[%d][%d]  -- %d ",i, j, newAvailableNetwork->getSignalQuality());
                        newAvailableNetwork->setIrssi(iRSSI);

                        if (pBssEntry->bSecurityEnabled)
                            newAvailableNetwork->setSecurity(true);
                        else
                            newAvailableNetwork->setSecurity(false);
                        toReturn->addWlanConnction(newAvailableNetwork);
                    }
                }

            }

        }

        //                    // TODO:
        ////                    qDebug("  Default AuthAlgorithm[%u]: ", j);
        ////                    switch (pBssEntry->dot11DefaultAuthAlgorithm) {
        ////                    case DOT11_AUTH_ALGO_80211_OPEN:
        ////                        qDebug("802.11 Open (%u)\n", pBssEntry->dot11DefaultAuthAlgorithm);
        ////                        break;
        ////                    case DOT11_AUTH_ALGO_80211_SHARED_KEY:
        ////                        qDebug("802.11 Shared (%u)\n", pBssEntry->dot11DefaultAuthAlgorithm);
        ////                        break;
        ////                    case DOT11_AUTH_ALGO_WPA:
        ////                        qDebug("WPA (%u)\n", pBssEntry->dot11DefaultAuthAlgorithm);
        ////                        break;
        ////                    case DOT11_AUTH_ALGO_WPA_PSK:
        ////                        qDebug("WPA-PSK (%u)\n", pBssEntry->dot11DefaultAuthAlgorithm);
        ////                        break;
        ////                    case DOT11_AUTH_ALGO_WPA_NONE:
        ////                        qDebug("WPA-None (%u)\n", pBssEntry->dot11DefaultAuthAlgorithm);
        ////                        break;
        ////                    case DOT11_AUTH_ALGO_RSNA:
        ////                        qDebug("RSNA (%u)\n", pBssEntry->dot11DefaultAuthAlgorithm);
        ////                        break;
        ////                    case DOT11_AUTH_ALGO_RSNA_PSK:
        ////                        qDebug("RSNA with PSK(%u)\n", pBssEntry->dot11DefaultAuthAlgorithm);
        ////                        break;
        ////                    default:
        ////                        qDebug("Other (%lu)\n", pBssEntry->dot11DefaultAuthAlgorithm);
        ////                        break;
        ////                    }

        ////                    qDebug("  Default CipherAlgorithm[%u]: ", j);
        ////                    switch (pBssEntry->dot11DefaultCipherAlgorithm) {
        ////                    case DOT11_CIPHER_ALGO_NONE:
        ////                        qDebug("None (0x%x)\n", pBssEntry->dot11DefaultCipherAlgorithm);
        ////                        break;
        ////                    case DOT11_CIPHER_ALGO_WEP40:
        ////                        qDebug("WEP-40 (0x%x)\n", pBssEntry->dot11DefaultCipherAlgorithm);
        ////                        break;
        ////                    case DOT11_CIPHER_ALGO_TKIP:
        ////                        qDebug("TKIP (0x%x)\n", pBssEntry->dot11DefaultCipherAlgorithm);
        ////                        break;
        ////                    case DOT11_CIPHER_ALGO_CCMP:
        ////                        qDebug("CCMP (0x%x)\n", pBssEntry->dot11DefaultCipherAlgorithm);
        ////                        break;
        ////                    case DOT11_CIPHER_ALGO_WEP104:
        ////                        qDebug("WEP-104 (0x%x)\n", pBssEntry->dot11DefaultCipherAlgorithm);
        ////                        break;
        ////                    case DOT11_CIPHER_ALGO_WEP:
        ////                        qDebug("WEP (0x%x)\n", pBssEntry->dot11DefaultCipherAlgorithm);
        ////                        break;
        ////                    default:
        ////                        qDebug("Other (0x%x)\n", pBssEntry->dot11DefaultCipherAlgorithm);
        ////                        break;
        ////                    }

        ////                    qDebug("  Flags[%u]:\t 0x%x", j, pBssEntry->dwFlags);
        ////                    if (pBssEntry->dwFlags) {
        ////                        if (pBssEntry->dwFlags & WLAN_AVAILABLE_NETWORK_CONNECTED)
        ////                            qDebug(" - Currently connected");
        ////                        if (pBssEntry->dwFlags & WLAN_AVAILABLE_NETWORK_CONNECTED)
        ////                            qDebug(" - Has profile");
        ////                    }



    }
    if (pBssList != NULL) {
        WlanFreeMemory(pBssList);
        pBssList = NULL;
    }

    if (pIfList != NULL) {
        WlanFreeMemory(pIfList);
        pIfList = NULL;
    }


    return toReturn;
}

void AccessPointManager::getSignalStrenght(WlanInterfacePtr inter)
{
    HANDLE hClient = NULL;
    DWORD dwMaxClient = 2;      //
    DWORD dwCurVersion = 0;
    DWORD dwResult = 0;
    DWORD dwRetVal = 0;
    int iRet = 0;

    WCHAR GuidString[39] = { 0 };

    unsigned int i, k;

//    // variables used for WlanEnumInterfaces

//    PWLAN_INTERFACE_INFO_LIST pIfList = NULL;
//    PWLAN_INTERFACE_INFO pIfInfo = NULL;

//    // variables used for WlanQueryInterfaces for opcode = wlan_intf_opcode_current_connection
//    PWLAN_CONNECTION_ATTRIBUTES pConnectInfo = NULL;
//    DWORD connectInfoSize = sizeof(WLAN_CONNECTION_ATTRIBUTES);
//    WLAN_OPCODE_VALUE_TYPE opCode = wlan_opcode_value_type_invalid;

//    dwResult = WlanOpenHandle(dwMaxClient, NULL, &dwCurVersion, &hClient);
//    if (dwResult == ERROR_SUCCESS) {

//        dwResult = WlanEnumInterfaces(hClient, NULL, &pIfList);
//        if (dwResult == ERROR_SUCCESS)
//        {
//            if (pIfInfo->isState == wlan_interface_state_connected) {
//                dwResult = WlanQueryInterface(hClient,
//                                              &pIfInfo->InterfaceGuid,
//                                              wlan_intf_opcode_current_connection,
//                                              NULL,
//                                              &connectInfoSize,
//                                              (PVOID *) &pConnectInfo,
//                                              &opCode);
//            }
//        }


//    }
}
