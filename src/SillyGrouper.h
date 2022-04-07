#ifndef _SillyGrouper_H
#define _SillyGrouper_H
#include "GrouperBase.h"


class SillyGrouper: public GrouperBase
{
public: 

    SillyGrouper(Environment* environment, Vector2<float> pos, 
        GrouperHQ* hq, float speed = GrouperBase::speed_DEFAULT, float radius = LocalizedEntity::defaultRadius(), 
        float startLife = MathUtils::random(GrouperBase::lifeLeft_LOWER_BOUND, GrouperBase::lifeLeft_UPPER_BOUND) );

    virtual void update();
    
};


#endif