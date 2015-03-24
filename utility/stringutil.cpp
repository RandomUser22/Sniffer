#include "stringutil.h"

StringUtil::StringUtil()
{
}

StringUtil::~StringUtil()
{
}

char* StringUtil::qStringToCharP(QString input)
{
    char* toReturn;

    QByteArray ba = input.toLocal8Bit();
    toReturn = ba.data();

    return toReturn;
}
