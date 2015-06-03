#ifndef ENUM_ADAPTERTYPE
#define ENUM_ADAPTERTYPE

namespace entity
{

enum AdapterType
{
    adapter_type_other          = 1,
    adapter_type_ethernet       = 2,
    adapter_type_tokenring      = 3,
    adapter_type_fddi           = 4,
    adapter_type_ppp            = 5,
    adapter_type_loopback       = 6,
    adapter_type_slip           = 7,
    adapter_type_ieee80211      = 8,
    adapter_type_unknown        = 0,
};

}

#endif // ENUM_ADAPTERTYPE

