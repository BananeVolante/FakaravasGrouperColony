#ifndef _Grouper_H
#define _Grouper_H
#include "GrouperBasePheromones.h"

///\brief the normal grouper, that collects and deposit food, deposit pheromones, follow pheromoens and everything
class Grouper : public GrouperBasePheromones
{
private:

public:

    Grouper(Environment* environment, Vector2<float> pos, 
        GrouperHQ* hq, Vector2<float> baseMvDirection, 
        float speed = GrouperBase::speed_DEFAULT, float radius = LocalizedEntity::defaultRadius(), 
        float startLife = MathUtils::random(GrouperBase::lifeLeft_LOWER_BOUND, GrouperBase::lifeLeft_UPPER_BOUND) );
    ///\copydoc Agent::update()
    virtual void update();

};

#endif