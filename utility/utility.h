#ifndef UTILITY_H
#define UTILITY_H

#include "utility_global.h"

#include "stringutil.h"

class UTILITYSHARED_EXPORT Utility
{

public:
    Utility();
    virtual ~Utility();

    static char* qStringToCharP(QString input);

private:
    StringUtil stringUtil;
};

#endif // UTILITY_H
