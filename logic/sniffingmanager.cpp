#include "sniffingmanager.h"

// redeclaration of static members
SniffingManagerPtr SniffingManager::instance;

SniffingManager::SniffingManager()
    :handle(),
      stopSingnaled(false),
      mutex()
{

}

SniffingManager::~SniffingManager()
{

}

// static instance set and remove
SniffingManagerPtr SniffingManager::getInstance()
{
    if(!instance)
    {
        instance = SniffingManagerPtr(new SniffingManager());
    }
    return instance;
}

void SniffingManager::removeInstance()
{
    if(instance)
    {
        instance.reset();
    }
}
