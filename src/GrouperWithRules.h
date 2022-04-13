#ifndef _GrouperWithRules_H
#define _GrouperWithRules_H
#include "StaticRules.h"
#include "GrouperBasePheromones.h"


///\brief class similar to Grouper, but that uses rule class to determine its actions
class GrouperWithRules : public GrouperBasePheromones
{
private:
///\brief rules followed by all groupers
static StaticOrRule<GrouperWithRules> rules;

public:
///\copydoc GrouperBasePheromones::GrouperBasePheromones()
    GrouperWithRules(Environment* environment, Vector2<float> pos, 
        GrouperHQ* hq, Vector2<float> baseMvDirection, 
        float speed = GrouperBase::speed_DEFAULT, float radius = LocalizedEntity::defaultRadius(), 
        float startLife = MathUtils::random(GrouperBase::lifeLeft_LOWER_BOUND, GrouperBase::lifeLeft_UPPER_BOUND) );
///\copydoc Agent::update()
    virtual void update();
    

};  

#endif