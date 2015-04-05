#include "sniffinginterface.h"

SniffingInterface::SniffingInterface() :
    pcapName(),
    pcapDescription(),
    name(),
    description(),
    type(),
    ipAddress(),
    ipMask()
{

}

SniffingInterface::~SniffingInterface()
{

}

QString SniffingInterface::getPcapName(){
    return pcapName;
}

QString SniffingInterface::getPcapDescription(){
    return pcapDescription;
}

QString SniffingInterface::getName(){
    return name;
}

QString SniffingInterface::getDescription(){
    return description;
}

QString SniffingInterface::getType(){
    return type;
}

QString SniffingInterface::getIpAddress(){
    return ipAddress;
}

QString SniffingInterface::getIpMask(){
    return ipMask;
}

void SniffingInterface::setPcapName(QString input){
    pcapName = input;
}

void SniffingInterface::setPcapDescription(QString input){
    pcapDescription = input;
}

void SniffingInterface::setName(QString input){
    name = input;
}

void SniffingInterface::setDescription(QString input){
    description = input;
}

void SniffingInterface::setType(QString input){
    type = input;
}

void SniffingInterface::setIpAddress(QString input){
    ipAddress = input;
}

void SniffingInterface::setIpMask(QString input){
    ipMask = input;
}
