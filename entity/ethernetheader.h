#ifndef ETHERNETHEADER_H
#define ETHERNETHEADER_H

// includes from standard memory
#include <memory>
#include <cstdint>

// includes from QT
#include <QString>
#include <QAbstractTableModel>

// includes from current project
#include "entity_global.h"
#include "util.h"

#define MAC_ADDRESS_SIZE        6
#define ETHERNET_HEADER_SIZE 	14

/* Ethernet header */
typedef struct ethernet_header {
        /* destination host address */
        uint8_t     mac_dest  [MAC_ADDRESS_SIZE];
        /* source host address */
        uint8_t     mac_source[MAC_ADDRESS_SIZE];
        /* IP? ARP? RARP? etc */
        uint16_t    frame_type;
}ethernet_header;

// pointer definition
class ENTITYSHARED_EXPORT EthernetHeader;
typedef std::shared_ptr<EthernetHeader> EthernetHeaderPtr;

class ENTITYSHARED_EXPORT EthernetHeader : public QAbstractTableModel
{
    Q_OBJECT
public:
    EthernetHeader(QObject *parent = 0);
    virtual ~EthernetHeader();

    QString getMacDestination() const;
    void setMacDestination(const QString &value);
    void setMacDestination(const uint8_t *value);

    QString getMacSource() const;
    void setMacSource(const QString &value);
    void setMacSource(const uint8_t *value);

    QString getFrameType() const;
    void setFrameType(const QString &value);
    void setFrameType(const uint16_t &value);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

private:
    void beautifyMacAddress(QString& input);

    QString macDestination;
    QString macSource;
    QString frameType;

    // QAbstractItemModel interface

};


#endif // ETHERNETHEADER_H
