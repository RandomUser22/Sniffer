#ifndef PCAPEXCEPTION_H
#define PCAPEXCEPTION_H

#include <string>
#include <exception>

#include "entity_global.h"

// declare the class
class ENTITYSHARED_EXPORT PcapException;

// define the pointer definition
typedef std::shared_ptr<PcapException> PcapExceptionPtr;

class ENTITYSHARED_EXPORT PcapException : std::exception
{
public:
    /**
        @brief Exception constructor
     */
    PcapException(const char* why);

    /**
        @brief Exception destructor
     */
    virtual ~PcapException() throw();

    /**
        @brief Redefinition of the what() method
               from std::exception
     */
    virtual const char* what() const throw();

private:
    /**
        @brief The reason for the exception
     */
    std::string reason;
};

#endif // PCAPEXCEPTION_H
