#ifndef _GrouperBasePheromones_H
#define _GrouperBasePheromones_H
#include "GrouperBase.h"
#include "Pheromones.h"


class GrouperBasePheromones : public GrouperBase 
{
private:
    ///\brief distance at which the grouper can smell pheromones
    static constexpr float PHEROMONES_SENSE_DISTANCE = 8;

protected:
    ///\copybrief LocalizedEntity::perceive()
    ///\Only perceive pheromones, with the distance PHEROMONES_SENSE_DISTANCE
    std::vector<Pheromones*> perceivePheromones() const;

public:

///\brief normal constructor for GrouperBasePheromones
///\copydoc GrouperBase::GrouperBase()
    GrouperBasePheromones(Environment* environment, Vector2<float> pos, 
        GrouperHQ* hq, Vector2<float> baseMvDirection, 
        float speed = GrouperBase::speed_DEFAULT, float radius = LocalizedEntity::defaultRadius(), 
        float startLife = MathUtils::random(GrouperBase::lifeLeft_LOWER_BOUND, GrouperBase::lifeLeft_UPPER_BOUND) );

    ///\brief if a pheromones pile is nearby, add pheromones to it, else, create  new pile
    ///\param amount amount of pheromones to place
    void putPheromones(float amount) const;

    ///\brief sense nearby pheromones and return one. probability depends on the amount
    ///\return a random pheromon nearby
    Pheromones* choosePheromone() const;
};


#endif