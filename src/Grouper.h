#ifndef _Grouper_H
#define _Grouper_H
#include "GrouperBasePheromones.h"

///\brief the normal grouper, that collects and deposit food, deposit pheromones, follow pheromoens and everything
class Grouper : public GrouperBasePheromones
{
    // FOR NOW, WE SUPPOSE THAT THE RANGE AT WHICH GROUPERS CAN DETECT FOOD IS THE RANGE AT WHICH THEY CAN COLLECT IT
private:
    ///\brief amount of pheromones placed when the grouper isn't carrying food
    static constexpr float PHEROMONE_AMOUNT_EMPTY = 10;
    ///\brief amount of pheromones placed when the grouper is carrying food
    static constexpr float PHEROMONE_AMOUNT_FULL = 1000;

    ///\brief place pheromones, with the amount changing whether the gouper is carrying food or not
    void putPheromones() const;
public:

    Grouper(Environment* environment, Vector2<float> pos, 
        GrouperHQ* hq, Vector2<float> baseMvDirection, 
        float speed = GrouperBase::speed_DEFAULT, float radius = LocalizedEntity::defaultRadius(), 
        float startLife = MathUtils::random(GrouperBase::lifeLeft_LOWER_BOUND, GrouperBase::lifeLeft_UPPER_BOUND) );
    ///\copydoc Agent::update()
    virtual void update();

};

#endif