#include "networkinterfacemanager.h"

// redeclaration of static members
NetworkInterfaceManagerPtr NetworkInterfaceManager::instance;

NetworkInterfaceManager::NetworkInterfaceManager()
{

}

NetworkInterfaceManager::~NetworkInterfaceManager()
{

}

// static instance set and remove
NetworkInterfaceManagerPtr NetworkInterfaceManager::getInstance()
{
    if(!instance)
    {
        instance = NetworkInterfaceManagerPtr(new NetworkInterfaceManager());
    }
    return instance;
}

void NetworkInterfaceManager::removeInstance()
{
    if(instance)
    {
        instance.reset();
    }
}
