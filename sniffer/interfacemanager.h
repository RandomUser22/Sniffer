#ifndef INTERFACEMANAGER_H
#define INTERFACEMANAGER_H

// includes from QT
#include <QStringList>

// global header
#include "sniffer_global.h"

// includes from project
#include "pcapexception.h"
#include "sniffinginterface.h"
#include "NetworkInterface.h"

// declare the class
class SNIFFERSHARED_EXPORT InterfaceManager;

// define the pointer definition for SnifferManager class
typedef std::shared_ptr<InterfaceManager> InterfaceManagerPtr;

// interfata utilizata pentru a ne intoarce lista de interfete prin care putem snifui pachete
class SNIFFERSHARED_EXPORT InterfaceManager
{
public:
    /**
        @brief Constructor for class InterfaceManager
     */
    InterfaceManager();

    /**
        @brief Destructor for class InterfaceManager
     */
    virtual ~InterfaceManager();

    /**
        @brief Method used to get the name and description of the list of interfeces we can sniff on
     */
    static QList<SniffingInterfacePtr> getListOfInterfacess();

private:
    /**
        @brief
     */
    static void getAdaptersInfo(SniffingInterfacePtr& adaptName);

    /**
        @brief
     */
    static QString getAdapterType(UINT type);
};

#endif // INTERFACEMANAGER_H
