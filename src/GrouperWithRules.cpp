#include "GrouperWithRules.h"
#include "Pheromones.h"

// Rule 1
const PersonalisableStaticRule GrouperWithRules::grabFood(
    [](void *target) -> bool
    { GrouperWithRules* grouper = (GrouperWithRules*) target;
        return ( !grouper->isCarryingFood()) && (!grouper->perceive<Food>().empty()); 
    },
    [](void *target) -> void
    {
        GrouperWithRules* grouper = (GrouperWithRules*) target;
        std::vector<Food *> foodPileOnSameCell = grouper->perceive<Food>();
        for (Food *f : foodPileOnSameCell)
        {
            grouper->collectFood(*f);
            if (grouper->isFull())
                break;
        }
    });
// Rule 2
const PersonalisableStaticRule GrouperWithRules::goToFood(
    [](void *target) -> bool
    { 
        GrouperWithRules* grouper = (GrouperWithRules*) target;
        return (!grouper->isCarryingFood()) && (!grouper->perceive<Food>(grouper->getMvDirection(), grouper->viewAngle, grouper->viewDistance).empty()); 
    },
    [](void *target) -> void
    {
        GrouperWithRules* grouper = (GrouperWithRules*) target;

        std::vector<Food *> foodPileNearby = grouper->perceive<Food>(grouper->getMvDirection(), grouper->viewAngle, grouper->viewDistance);
        grouper->pointTo(*foodPileNearby[0]);
    });
// Rule 3
const PersonalisableStaticRule GrouperWithRules::followPheromones(
    [](void *target) -> bool
    { 
        GrouperWithRules* grouper = (GrouperWithRules*) target;
        return (!grouper->isCarryingFood()) && (grouper->choosePheromone() != nullptr); 
    },
    [](void *target) -> void
    {
        GrouperWithRules* grouper = (GrouperWithRules*) target;
        grouper->pointTo(grouper->choosePheromone()->getPosition());
    });
// Rule 4
const PersonalisableStaticRule GrouperWithRules::moveRandomly(
    [](void *target) -> bool
    { 
        GrouperWithRules* grouper = (GrouperWithRules*) target;
        return (!grouper->isCarryingFood()) && (grouper->choosePheromone() == nullptr);
         },
    [](void *target) -> void
    {
        GrouperWithRules* grouper = (GrouperWithRules*) target;
        grouper->randomRotation();
    });
// Rule 5
const PersonalisableStaticRule GrouperWithRules::depositFoodIfPossible(
    [](void *target) -> bool
    {
        GrouperWithRules* grouper = (GrouperWithRules*) target;
        std::vector<GrouperHQ *> hqList = grouper->perceive<GrouperHQ>();
        return grouper->isCarryingFood() && (std::count(hqList.begin(), hqList.end(), grouper->getHQ()) != 0);
    },
    [](void *target) -> void
    {
        GrouperWithRules* grouper = (GrouperWithRules*) target;
        grouper->depositFood();
        grouper->uTurn();
    });
// Rule 6
const PersonalisableStaticRule GrouperWithRules::goBackToBase(
    [](void *target) -> bool
    {
        GrouperWithRules* grouper = (GrouperWithRules*) target;
        std::vector<GrouperHQ *> hqList = grouper->perceive<GrouperHQ>();
        return grouper->isCarryingFood() && (std::count(hqList.begin(), hqList.end(), grouper->getHQ()) == 0);
    },
    [](void *target) -> void
    {
        GrouperWithRules* grouper = (GrouperWithRules*) target;
        // turn then search for pheromones
        // if there are pheromones, follow them, else go to the HQ directly
        grouper->pointTo(*grouper->getHQ());
        Pheromones *pheromone = grouper->choosePheromone();
        if (pheromone != nullptr)
            grouper->pointTo(*pheromone);
    });
StaticOrRule GrouperWithRules::rules({&grabFood, &goToFood, &followPheromones, &moveRandomly, &depositFoodIfPossible, &goBackToBase});

GrouperWithRules::GrouperWithRules(Environment *environment, Vector2<float> pos,
                                   GrouperHQ *hq, Vector2<float> baseMvDirection,
                                   float speed, float radius,
                                   float startLife) : GrouperBase(environment, pos, hq, baseMvDirection, speed, radius, startLife),
                                                      PheromonesTeamHandler(this)
{
}

void GrouperWithRules::update()
{
    if (getRule().condition(this)) // condition is probably optional here
        getRule().action(this);
    smartPutPheromones();
    GrouperBase::update();
}

void GrouperWithRules::smartPutPheromones() const
{
    if (isCarryingFood())
        putPheromones(PHEROMONE_AMOUNT_FULL);
    else
        putPheromones(PHEROMONE_AMOUNT_EMPTY);
}

const AbstractStaticRule& GrouperWithRules::getRule() const
{
    return rules;
}