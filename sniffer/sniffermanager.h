#ifndef SNIFFERMANAGER_H
#define SNIFFERMANAGER_H

#include "sniffer_global.h"

#include <stdio.h>
#include <QStringList>

#include "utility.h"
#include "NetworkInterface.h"

class SNIFFERSHARED_EXPORT SnifferManager : public QObject
{
    Q_OBJECT

public:
    // fiin o clasa singleton, va avea o methode de
    // returnarea instantei actuale si nu se vor putea creea
    // alte instante
    static SnifferManager* getInstance();
    static void removeInstance();

    virtual ~SnifferManager();

    void startSniffing();
    void setInterfaceToSniffOn(QString device);

signals:
    void packageCaptured(QStringList payload);

private:
    SnifferManager();
    SnifferManager(SnifferManager const&);
    void operator=(SnifferManager const&);

    static void callbackPacketReceived(u_char *args,
                                const struct pcap_pkthdr *header,
                                const u_char *packet);
    QString interpretPayload(int size,
                             const unsigned char *payload);
    QString formatPayload(const unsigned char *payload,
                          int len,
                          int offset);

    /**
        @brief Single instance
     */
    static SnifferManager* instance;

    /**
        @brief The interface on which the sniffing is done
    */
    QString device;

    /**
        @brief Packet capture handler
    */
    pcap_t *handle;

    /**
        @brief Error string buffer
    */
    char errbuf[PCAP_ERRBUF_SIZE];

    bpf_u_int32 mask;

    bpf_u_int32 net;

    /**
        @brief Compiled filter program (expression)
    */
    struct bpf_program fp;

    /**
        @brief Filter expresion
    */
    char* filter_exp;

    /**
        @brief packet counter
    */
    static int count;

};

#endif // SNIFFERMANAGER_H
