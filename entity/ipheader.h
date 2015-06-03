#ifndef IPHEADER_H
#define IPHEADER_H

// includes from standard memory
#include <memory>
#include <cstdint>

// includes from QT
#include <QString>
#include <QStringList>
#include <QAbstractTableModel>

// includes from current project
#include "entity_global.h"
#include "util.h"
#include "enum_protocoltype.h"
#include "networkinclude.h"

#define IP_HL(ip)			(((ip)->version) & 0x0f)
#define IP_V(ip)			(((ip)->version) >> 4)

/* reserved fragment flag */
#define IP_OFFSET_RF 		0x8000

/* dont fragment flag */
#define IP_OFFSET_DF 		0x4000

/* more fragments flag */
#define IP_OFFSET_MF 		0x2000

/* mask for fragmenting bits */
#define IP_OFFSET_MASK 		0x1fff

/* IP header */
typedef struct ip_header {
        /* version << 4 | header length >> 2 */
        uint8_t 	version;
        /* type of service */
        uint8_t 	type_of_service;
        /* total length */
        uint16_t 	length;
        /* identification */
        uint16_t 	id;
        /* flags & offset field */
        uint16_t 	offset;
        /* time to live */
        uint8_t     ttl;
        /* protocol */
        uint8_t     protocol;
        /* checksum */
        uint16_t    checksum;
        /* adresa destinatarului si al trmitatorului */
        struct in_addr ip_src, ip_dst;
}ip_header;

// pointer definition
class ENTITYSHARED_EXPORT IpHeader;
typedef std::shared_ptr<IpHeader> IpHeaderPtr;

class ENTITYSHARED_EXPORT IpHeader : public QAbstractTableModel
{
    Q_OBJECT
public:
    IpHeader(QObject *parent = 0);
    virtual ~IpHeader();

    uint32_t getSizeIp() const;
    void setSizeIp(const uint32_t &value);

    QString getVersion() const;
    void setVersion(const QString &value);
    void setVersion(const uint8_t &value);

    QString getTypeOfService() const;
    void setTypeOfService(const QString &value);
    void setTypeOfService(const uint8_t &value);

    QString getLength() const;
    void setLength(const QString &value);
    void setLength(const uint16_t &value);

    QString getId() const;
    void setId(const QString &value);
    void setId(const uint16_t &value);

    QString getOffsetIp() const;
    void setOffsetIp(const QString &value);
    void setOffsetIp(const uint16_t &value);

    QString getTtl() const;
    void setTtl(const QString &value);
    void setTtl(const uint8_t &value);

    ProtocolType getProtocol() const;
    QString getProtocolName() const;
    uint8_t getProtocolValue() const;
    void setProtocol(const uint8_t &value);

    QString getChecksumIp() const;
    void setChecksumIp(const QString &value);
    void setChecksumIp(const uint16_t &value);

    QString getIpSource() const;
    void setIpSource(const QString &value);

    QString getIpDest() const;
    void setIpDest(const QString &value);

    // QAbstractItemModel interface
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

private:
    uint32_t sizeIp;
    QString version;
    QString typeOfService;
    QString length;
    QString id;
    QString offsetIp;
    QString ttl;
    ProtocolType protocol;
    QString checksumIp;
    QString ipSource;
    QString ipDest;



};

#endif // IPHEADER_H
