#ifndef NETWORKINTERFACE_H
#define NETWORKINTERFACE_H

#define HAVE_REMOTE

#include <pcap.h>
#ifdef _WIN32
#include <winsock2.h>
#elif __unix__
#include <arpa/inet.h>
#endif


/**
    @brief Dimensiunea maxima a unui frame de Ethernet
 */
#define FRAME_MAX_SIZE 		1518

/**
    @brief Header-ul unui frame de Ethernet este de 14 bytes
    @detail Incepande de la Adresa MAC a destinatarului pana la
            inceputul payload-ului se afla un un numar exact de
            bytes pentru fiecare frame
*/
#define HEADER_FRAME_SIZE 	14

/**
    @brief Adresa MAC dintr-un frame este de 9 bytes
*/
#define MAC_ADDRESS_SIZE	6

/**
    @brief
*/
/* reserved fragment flag */
#define IP_OFFSET_RF 		0x8000

/* dont fragment flag */
#define IP_OFFSET_DF 		0x4000

/* more fragments flag */
#define IP_OFFSET_MF 		0x2000

/* mask for fragmenting bits */
#define IP_OFFSET_MASK 		0x1fff

#define IP_HL(ip)			(((ip)->version) & 0x0f)
#define IP_V(ip)			(((ip)->version) >> 4)

/**
    @brief
*/
#define TH_OFF(th)      	(((th)->offset & 0xf0) >> 4)
#define TH_FIN  			0x01
#define TH_SYN  			0x02
#define TH_RST  			0x04
#define TH_PUSH 			0x08
#define TH_ACK  			0x10
#define TH_URG  			0x20
#define TH_ECE  			0x40
#define TH_CWR  			0x80
#define TH_FLAGS        	(TH_FIN|TH_SYN|TH_RST|TH_ACK|TH_URG|TH_ECE|TH_CWR)

/**
    @brief
*/
#define MAX_NR_OF_PACKETS	10

/* Ethernet header */
typedef struct ethernet_header {
        /* destination host address */
        unsigned char  mac_dest  [MAC_ADDRESS_SIZE];
        /* source host address */
        unsigned char  mac_source[MAC_ADDRESS_SIZE];
        /* IP? ARP? RARP? etc */
        unsigned short frame_type;
}ethernet_header;

/* IP header */
typedef struct ip_header {
        /* version << 4 | header length >> 2 */
        unsigned char 	version;
        /* type of service */
        unsigned char 	type_of_service;
        /* total length */
        unsigned short 	length;
        /* identification */
        unsigned short 	id;
        /* flags & offset field */
        unsigned short 	offset;
        /* time to live */
        unsigned char  ttl;
        /* protocol */
        unsigned char  protocol;
        /* checksum */
        unsigned short checksum;
        /* adresa destinatarului si al trmitatorului */
        struct in_addr ip_src, ip_dst;
}ip_header;

/* TCP header */
typedef struct tcp_packet {
        /* source port */
        unsigned short 	source_port;
        /* destination port */
        unsigned short 	destination_port;
        /* sequence number */
        unsigned int 	sequence_number;
        /* acknowledgement number */
        unsigned int 	ack;
        /* data offset, rsvd */
        unsigned char   offset;
        /* flag-uri */
        unsigned char  	flags;
        /* window size */
        unsigned short 	window;
        /* checksum */
        unsigned short 	checksum;
        /* urgent pointer */
        unsigned short 	urgent_pointer;

}tcp_packet;

/* Complete frame */
typedef struct complete_frame
{
    //
    ethernet_header ethernet;
    //
    ip_header ip;
    //
    tcp_packet tcp;
    //
    char* data;

}complete_frame;


#endif // NETWORKINTERFACE_H
