#ifndef SNIFFERMANAGER_H
#define SNIFFERMANAGER_H

// includes from standard library
#include <stdio.h>

// includes from QT
#include <QStringList>

// global header
#include "sniffer_global.h"

// includes from project
#include "stringutil.h"
#include "pcapexception.h"
#include "packet.h"
#include "NetworkInterface.h"

// declare the class
class SNIFFERSHARED_EXPORT SnifferManager;

// define the pointer definition for SnifferManager class
typedef std::shared_ptr<SnifferManager> SnifferManagerPtr;

class SNIFFERSHARED_EXPORT SnifferManager : public QObject
{
    Q_OBJECT

public:
    /**
        @brief Method used to get the sone instance of SnifferManager class
     */
    static SnifferManagerPtr getInstance();

    /**
        @brief Method used to remove the sole object of SnifferManager
     */
    static void removeInstance();

    /**
        @brief Destructor for Sniffer Manager
     */
    virtual ~SnifferManager();

    /**
        @brief Method used to begin the pachet capturing process
     */
    void startSniffing();

    /**
        @brief Method used to set the device insterface to sniff on
     */
    void setInterfaceToSniffOn(QString device);

signals:
    /**
        @brief Signal for notifying when a package has been captured
     */
    void packageCaptured(unsigned int pckCount, PacketPtr package);

private:
    /**
        @brief Constructor for SnifferManager class
     */
    SnifferManager();

    /**
        @brief Copy constrctor for SnifferManager class
     */
    SnifferManager(SnifferManager const&);

    /**
        @brief Overwriten method for the '=' operator
     */
    void operator=(SnifferManager const&);

    /**
        @brief
     */
    static void callbackPacketReceived(u_char *args,
                                const struct pcap_pkthdr *header,
                                const u_char *packet);
    /**
        @brief
     */
    QString interpretPayload(int size,
                             const unsigned char *payload);

    /**
        @brief
     */
    QString formatPayload(const unsigned char *payload,
                          int len,
                          int offset);

    /**
        @brief Single instance
     */
    static SnifferManagerPtr instance;

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

    /**
        @brief
    */
    bpf_u_int32 mask;

    /**
        @brief
    */
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
    static unsigned int count;
};

#endif // SNIFFERMANAGER_H
