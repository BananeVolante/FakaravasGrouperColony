#include "GrouperFactory.h"
#include "GrouperWithRules.h"

GrouperFactory* GrouperFactory::instance = nullptr;

GrouperFactory* GrouperFactory::getInstance()
{
    if(instance == nullptr)
        instance = new GrouperFactory();
    return instance;
        
}

void GrouperFactory::spawnGrouper(GrouperHQ* hq)
{
    new GrouperWithRules(hq->getEnvironment(), hq->getPosition(), hq, Vector2<float>::random());
}