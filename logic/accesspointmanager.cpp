#include "accesspointmanager.h"

// redeclaration of static members
AccessPointManagerPtr AccessPointManager::instance;


AccessPointManager::AccessPointManager(QObject *parent) :
    QObject(parent)
{

}

AccessPointManager::~AccessPointManager()
{

}

// static instance and remove
AccessPointManagerPtr AccessPointManager::getInstance()
{
    if(!instance)
    {
        instance = AccessPointManagerPtr(new AccessPointManager());
    }
    return instance;
}
void AccessPointManager::removeInstance()
{
    if(instance)
    {
        instance.reset();
    }
}
