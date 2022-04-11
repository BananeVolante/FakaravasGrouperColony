#ifndef _SillyGrouper_H
#define _SillyGrouper_H
#include "GrouperBase.h"

///\brief a grouper that randomly search for food and go back to base once it found it
class SillyGrouper: public GrouperBase
{
public: 

///\brief copydoc GrouperBase::GrouperBase()
    SillyGrouper(Environment* environment, Vector2<float> pos, 
        GrouperHQ* hq, float speed = GrouperBase::speed_DEFAULT, float radius = LocalizedEntity::defaultRadius(), 
        float startLife = MathUtils::random(GrouperBase::lifeLeft_LOWER_BOUND, GrouperBase::lifeLeft_UPPER_BOUND) );

///\brief copydoc Agent::update()
    virtual void update();
    
};


#endif