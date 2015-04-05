#include "pcapexception.h"

PcapException::PcapException(const char* why)
    :reason(why)
{

}

PcapException::~PcapException() throw()
{

}

const char* PcapException::what() const throw()
{
    return reason.c_str();
}
