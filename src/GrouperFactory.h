#ifndef _GrouperFactory_H
#define _GrouperFactory_H
#include "GrouperHQ.h"

class GrouperFactory
{
private:
    static GrouperFactory* instance;
public:
    static GrouperFactory* getInstance();
    void spawnGrouper(GrouperHQ* hq);
};



#endif