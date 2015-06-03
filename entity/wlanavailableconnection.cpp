#include "wlanavailableconnection.h"

WlanAvailableConnection::WlanAvailableConnection() :
    profileName(""),
    ssid(""),
    bbsType(wlan_bss_type_unknown),
    nrOfBssIds(0),
    connectable(false),
    connectableReason(""),
    nrOfPhySupported(0),
    signalQuality(0),
    irssi(0),
    security(false),
    authAlgorithm(""),
    cipherAlgorithm(""),
    currentlyConnected(false),
    profile(false)
{

}

WlanAvailableConnection::~WlanAvailableConnection()
{

}
QString WlanAvailableConnection::getProfileName() const
{
    return profileName;
}

void WlanAvailableConnection::setProfileName(const QString &value)
{
    profileName = value;
}
QString WlanAvailableConnection::getSsid() const
{
    return ssid;
}

void WlanAvailableConnection::setSsid(const QString &value)
{
    ssid = value;
}
WlanBssType WlanAvailableConnection::getBbsType() const
{
    return bbsType;
}

QString WlanAvailableConnection::getBbsTypeName() const
{
    QString toReturn = "";
    switch (bbsType) {
    case wlan_bss_type_infrastructure:
        toReturn = "infrastructure";
        break;
    case wlan_bss_type_independent:
        toReturn = "independent";
        break;
    case wlan_bss_type_any:
        toReturn = "any";
        break;
    case wlan_bss_type_unknown:
    default:
        toReturn = "unknown";
        break;
    }
    return toReturn;
}

void WlanAvailableConnection::setBbsType(const WlanBssType &value)
{
    bbsType = value;
}
uint32_t WlanAvailableConnection::getNrOfBssIds() const
{
    return nrOfBssIds;
}

QString WlanAvailableConnection::getNrOfBssIdsString() const
{
    return QString::number(nrOfBssIds);
}

void WlanAvailableConnection::setNrOfBssIds(const uint32_t &value)
{
    nrOfBssIds = value;
}
bool WlanAvailableConnection::getConnectable() const
{
    return connectable;
}

void WlanAvailableConnection::setConnectable(bool value)
{
    connectable = value;
}
QString WlanAvailableConnection::getConnectableReason() const
{
    return connectableReason;
}

void WlanAvailableConnection::setConnectableReason(const QString &value)
{
    connectableReason = value;
}
uint32_t WlanAvailableConnection::getNrOfPhySupported() const
{
    return nrOfPhySupported;
}

QString WlanAvailableConnection::getNrOfPhySupportedString() const
{
    return QString::number(nrOfPhySupported);
}

void WlanAvailableConnection::setNrOfPhySupported(const uint32_t &value)
{
    nrOfPhySupported = value;
}
uint32_t WlanAvailableConnection::getSignalQuality() const
{
    return signalQuality;
}

QString WlanAvailableConnection::getSignalQualityString() const
{
    return QString::number(signalQuality);
}

void WlanAvailableConnection::setSignalQuality(const uint32_t &value)
{
    signalQuality = value;
}
int32_t WlanAvailableConnection::getIrssi() const
{
    return irssi;
}

QString WlanAvailableConnection::getIrssiString() const
{
    return QString::number(irssi);
}

void WlanAvailableConnection::setIrssi(const int32_t &value)
{
    irssi = value;
}
bool WlanAvailableConnection::getSecurity() const
{
    return security;
}

void WlanAvailableConnection::setSecurity(bool value)
{
    security = value;
}
QString WlanAvailableConnection::getAuthAlgorithm() const
{
    return authAlgorithm;
}

void WlanAvailableConnection::setAuthAlgorithm(const QString &value)
{
    authAlgorithm = value;
}
QString WlanAvailableConnection::getCipherAlgorithm() const
{
    return cipherAlgorithm;
}

void WlanAvailableConnection::setCipherAlgorithm(const QString &value)
{
    cipherAlgorithm = value;
}
bool WlanAvailableConnection::getCurrentlyConnected() const
{
    return currentlyConnected;
}

void WlanAvailableConnection::setCurrentlyConnected(bool value)
{
    currentlyConnected = value;
}
bool WlanAvailableConnection::getProfile() const
{
    return profile;
}

void WlanAvailableConnection::setProfile(bool value)
{
    profile = value;
}

uint32_t WlanAvailableConnection::getNumberOfProperties()
{
    return 14;
}















