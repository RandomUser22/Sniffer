#ifndef ENUM_WLANCONNECTION
#define ENUM_WLANCONNECTION

enum WlanConnectionType
{
    WlanConnectionType_not_ready                = 0,
    WlanConnectionType_connected                = 1,
    WlanConnectionType_ad_hoc_network_formed    = 2,
    WlanConnectionType_disconecting             = 3,
    WlanConnectionType_disconected              = 4,
    WlanConnectionType_associating              = 5,
    WlanConnectionType_discovering              = 6,
    WlanConnectionType_authenticateing          = 7,
    WlanConnectionType_unknown                  = 8,
};

#endif // ENUM_WLANCONNECTION

