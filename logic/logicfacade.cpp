#include "logicfacade.h"

// redeclaration of static members
LogicFacadePtr LogicFacade::instance;

LogicFacade::LogicFacade() :
    networkInterfaceManager(NetworkInterfaceManager::getInstance()),
    sniffingManager(SniffingManager::getInstance()),
    accessPointManager(AccessPointManager::getInstance())
{
    qRegisterMetaType<PacketPtr>("PacketPtr");
    connect(sniffingManager.get(), SIGNAL(packageCaptured(PacketPtr)),
            this, SLOT(onPackageCaptured(PacketPtr)));

    connect(accessPointManager.get(), SIGNAL(signalStrChanged(uint32_t)),
            this, SLOT(onSignalStrenghtChanged(uint32_t)));
}

LogicFacade::~LogicFacade()
{

}

// static instance set and remove
LogicFacadePtr LogicFacade::getInstance()
{
    if(!instance)
    {
        instance = LogicFacadePtr(new LogicFacade());
    }
    return instance;
}

void LogicFacade::removeInstance()
{
    if(instance)
    {
        instance.reset();
    }
}

QList<NetworkInterfacePtr> LogicFacade::getListOfNetworkInterfacess()
{
    QList<NetworkInterfacePtr> tempList;
    try
    {
        tempList = networkInterfaceManager->getListOfSniffingInterfacess();
    }
    catch(PcapException& e)
    {
        // just throw the exception up
        throw e;
    }
    return tempList;
}

void LogicFacade::startSniffing(NetworkInterfacePtr inter,
                                uint32_t nrOfPacketsToSniff)
{
    try
    {
        sniffingManager->startSniffing(inter, nrOfPacketsToSniff);
    }
    catch(PcapException& e)
    {
        // just throw the exception up
        throw e;
    }
}

void LogicFacade::stopSniffing()
{
    sniffingManager->stopSniffing();
}

WlanInterfacePtr LogicFacade::getDetailedAccessPointInformation(NetworkInterfacePtr value)
{
    return accessPointManager->getDetailedAccessPointInformation(value);
}

void LogicFacade::getSignalStrenght(WlanInterfacePtr inter)
{
    accessPointManager->getSignalStrenght(inter);
}

void LogicFacade::onPackageCaptured(PacketPtr capturedPacket)
{
    emit packageSniffed(capturedPacket);
}

void LogicFacade::onSignalStrenghtChanged(uint32_t value)
{
//    emit signalStrenghtChanged(value);
}
