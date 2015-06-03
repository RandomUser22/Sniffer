#ifndef PCAPEXCEPTION_H
#define PCAPEXCEPTION_H

// includes from standard library
#include <string>
#include <exception>

#include "exception_global.h"

// pointer definition
class EXCEPTIONSHARED_EXPORT PcapException;
typedef std::shared_ptr<PcapException> PcapExceptionPtr;

class EXCEPTIONSHARED_EXPORT PcapException : std::exception
{
public:
    PcapException(const char* why);
    virtual ~PcapException() throw();

    // redefinition of the what() method from std::exception
    virtual const char* what() const throw();

private:
    std::string reason;
};

#endif // PCAPEXCEPTION_H
