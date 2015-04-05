#ifndef SNIFFINGINTERFACE_H
#define SNIFFINGINTERFACE_H

#include <QString>

#include "entity_global.h"

class ENTITYSHARED_EXPORT SniffingInterface;

// define the pointer definition
typedef std::shared_ptr<SniffingInterface> SniffingInterfacePtr;

class ENTITYSHARED_EXPORT SniffingInterface
{
public:
    /**
        @brief Constructor for class SniffingInterface
     */
    SniffingInterface();

    /**
        @brief Destructor for class SniffingInterface
     */
    virtual ~SniffingInterface();

    // getters
    QString getPcapName();
    QString getPcapDescription();
    QString getName();
    QString getDescription();
    QString getType();
    QString getIpAddress();
    QString getIpMask();

    // setters
    void setPcapName(QString input);
    void setPcapDescription(QString input);
    void setName(QString input);
    void setDescription(QString input);
    void setType(QString input);
    void setIpAddress(QString input);
    void setIpMask(QString input);

private:
    /**
        @brief
     */
    QString pcapName;

    /**
        @brief
     */
    QString pcapDescription;

    /**
        @brief
     */
    QString name;

    /**
        @brief
     */
    QString description;

    /**
        @brief
     */
    QString type;

    /**
        @brief
     */
    QString ipAddress;

    /**
        @brief
     */
    QString ipMask;

};

#endif // SNIFFINGINTERFACE_H
