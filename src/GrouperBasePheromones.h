#ifndef _GrouperBasePheromones_H
#define _GrouperBasePheromones_H
#include "GrouperBase.h"
#include "Pheromones.h"
#include "PheromonesTeam.h"

///\deprecated Use classes of the AbstractPheromonesHandler family instead of this one
class GrouperBasePheromones : public GrouperBase 
{
private:
    ///\brief distance at which the grouper can smell pheromones
    static constexpr float PHEROMONES_SENSE_DISTANCE = 8;
    ///\brief angle at which the groupers can smell pheromones
    static const float PHEROMONES_SENSE_ANGLE; //pi/3 , using pi/2 made them sometimes block 

protected:
    ///\copybrief LocalizedEntity::perceive()
    ///\Only perceive pheromones, with the distance PHEROMONES_SENSE_DISTANCE
    std::vector<PheromonesTeam*> perceivePheromones() const;

    ///\brief amount of pheromones placed when the grouper isn't carrying food
    static constexpr float PHEROMONE_AMOUNT_EMPTY = 10;
    ///\brief amount of pheromones placed when the grouper is carrying food
    static constexpr float PHEROMONE_AMOUNT_FULL = 1000;

    ///\brief place pheromones, with the amount changing whether the gouper is carrying food or not
    void putPheromones() const;

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
    PheromonesTeam* choosePheromone() const;
};


#endif