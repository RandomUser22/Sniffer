#ifndef WLANAVAILABLECONNECTION_H
#define WLANAVAILABLECONNECTION_H

// includes from standard library
#include <memory>
#include <cstdint>

// includes from QT
#include <QString>

// includes from current project
#include "entity_global.h"
#include "enum_wlanbsstype.h"

// pointer definition
class ENTITYSHARED_EXPORT WlanAvailableConnection;
typedef std::shared_ptr<WlanAvailableConnection> WlanAvailableConnectionPtr;

class ENTITYSHARED_EXPORT WlanAvailableConnection
{
public:
    WlanAvailableConnection();
    virtual ~WlanAvailableConnection();

    QString getProfileName() const;
    void setProfileName(const QString &value);

    QString getSsid() const;
    void setSsid(const QString &value);

    WlanBssType getBbsType() const;
    QString getBbsTypeName() const;
    void setBbsType(const WlanBssType &value);

    uint32_t getNrOfBssIds() const;
    QString getNrOfBssIdsString() const;
    void setNrOfBssIds(const uint32_t &value);

    bool getConnectable() const;
    void setConnectable(bool value);

    QString getConnectableReason() const;
    void setConnectableReason(const QString &value);

    uint32_t getNrOfPhySupported() const;
    QString getNrOfPhySupportedString() const;
    void setNrOfPhySupported(const uint32_t &value);

    uint32_t getSignalQuality() const;
    QString getSignalQualityString() const;
    void setSignalQuality(const uint32_t &value);

    int32_t getIrssi() const;
    QString getIrssiString() const;
    void setIrssi(const int32_t &value);

    bool getSecurity() const;
    void setSecurity(bool value);

    QString getAuthAlgorithm() const;
    void setAuthAlgorithm(const QString &value);

    QString getCipherAlgorithm() const;
    void setCipherAlgorithm(const QString &value);

    bool getCurrentlyConnected() const;
    void setCurrentlyConnected(bool value);

    bool getProfile() const;
    void setProfile(bool value);

    static uint32_t getNumberOfProperties();

private:
    QString profileName;
    QString ssid;
    WlanBssType bbsType;
    uint32_t nrOfBssIds;
    bool connectable;
    QString connectableReason;
    uint32_t nrOfPhySupported;
    uint32_t signalQuality;
    int32_t irssi;
    bool security;
    QString authAlgorithm;
    QString cipherAlgorithm;
    bool currentlyConnected;
    bool profile;
};

#endif // WLANAVAILABLECONNECTION_H
