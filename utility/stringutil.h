#ifndef STRINGUTIL_H
#define STRINGUTIL_H

#include "utility_global.h"

#include <QString>

class UTILITYSHARED_EXPORT StringUtil
{
public:
    StringUtil();
    virtual ~StringUtil();

    static char* qStringToCharP(QString input);
};

#endif // STRINGUTIL_H
