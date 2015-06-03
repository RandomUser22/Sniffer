#ifndef PAYLOAD_H
#define PAYLOAD_H

// includes from standard library
#include <cstdint>
#include <memory>

// includes from QT
#include <QByteArray>
#include <QAbstractTableModel>

// includes from project
#include "entity_global.h"
#include "networkinclude.h"
#include "util.h"

// pointer definition
class ENTITYSHARED_EXPORT Payload;
typedef std::shared_ptr<Payload> PayloadPtr;

class ENTITYSHARED_EXPORT Payload : public QAbstractTableModel
{
    Q_OBJECT
public:
    Payload(QObject *parent = 0);
    virtual ~Payload();

    uint32_t getSize() const;
    virtual void setRawData(const QByteArray& data) = 0;

    // QAbstractItemModel interface
    int rowCount(const QModelIndex &parent) const = 0;
    int columnCount(const QModelIndex &parent) const = 0;
    QVariant data(const QModelIndex &index, int role) const = 0;

protected:
    void setSize(const uint32_t &value);

private:
    uint32_t size;

};

#endif // PAYLOAD_H
