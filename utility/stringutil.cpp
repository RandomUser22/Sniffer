#include "stringutil.h"

StringUtil::StringUtil()
{
}

StringUtil::~StringUtil()
{
}

char* StringUtil::qStringToCharP(QString input)
{
    return input.toLocal8Bit().data();
}
