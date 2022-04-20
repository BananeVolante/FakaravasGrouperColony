#ifndef _GrouperWithRules_H
#define _GrouperWithRules_H
#include "StaticRules.h"
#include "GrouperBase.h"
#include "PheromonesHandler.h"
#include "PheromonesTeamHandler.h"
#include <map>

///\brief class similar to Grouper, but that uses rule class to determine its actions
class GrouperWithRules : public GrouperBase, public PheromonesTeamHandler
{
private:
    ///\brief rules followed by all groupers
    static StaticOrRule rules;
    
    ///\brief amount of pheromones placed when the grouper isn't carrying food
    static constexpr float PHEROMONE_AMOUNT_EMPTY = 10;
    ///\brief amount of pheromones placed when the grouper is carrying food
    static constexpr float PHEROMONE_AMOUNT_FULL = 100;

public:
    ///\copydoc GrouperBasePheromones::GrouperBasePheromones()
    GrouperWithRules(Environment *environment, Vector2<float> pos,
                     GrouperHQ *hq, Vector2<float> baseMvDirection,
                     float speed = GrouperBase::speed_DEFAULT, float radius = LocalizedEntity::defaultRadius(),
                     float startLife = MathUtils::random(GrouperBase::lifeLeft_LOWER_BOUND, GrouperBase::lifeLeft_UPPER_BOUND));
    ///\copydoc Agent::update()
    virtual void update();

protected:
    ///\brief place PHEROMONE_AMOUNT_EMPTY if the grouper isn't carrying food, and PHEROMONE_AMOUNT_EMPTY if he is
    void smartPutPheromones() const;

    ///\brief get the current rule that makes the grouper work
    ///\remark can be redefined in child class to change the rules
    virtual const AbstractStaticRule& getRule() const;

    //rules used by groupers
    static const PersonalisableStaticRule grabFood;
    static const PersonalisableStaticRule goToFood;
    static const PersonalisableStaticRule followPheromones;
    static const PersonalisableStaticRule moveRandomly;
    static const PersonalisableStaticRule depositFoodIfPossible;
    static const PersonalisableStaticRule goBackToBase;

};

#endif