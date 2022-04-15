#include "GrouperWithRules.h"
#include "Pheromones.h"

StaticOrRule<GrouperWithRules> GrouperWithRules::rules = StaticOrRule<GrouperWithRules>(
    {
        //Rule 1
        new PersonalisableStaticRule<GrouperWithRules>(
        [](GrouperWithRules* target) ->bool {return (!target->isCarryingFood()) && (! target->perceive<Food>().empty()) ;},
        [](GrouperWithRules* target) -> void
        {
            std::vector<Food*> foodPileOnSameCell = target->perceive<Food>();
            for(Food* f : foodPileOnSameCell)
            {
                target->collectFood(*f);
                if(target->isFull())
                    break;
            }
        }),
        //Rule 2
        new PersonalisableStaticRule<GrouperWithRules>(
        [](GrouperWithRules* target) ->bool {return (!target->isCarryingFood()) && (! target->perceive<Food>(target->getMvDirection(),target->viewAngle, target->viewDistance ).empty()) ;},
        [](GrouperWithRules* target) -> void
        {
            std::vector<Food*> foodPileNearby = target->perceive<Food>(target->getMvDirection(), target->viewAngle, target->viewDistance);
            target->pointTo(*foodPileNearby[0]);
        }),
        //Rule 3
        new PersonalisableStaticRule<GrouperWithRules>(
        [](GrouperWithRules* target) ->bool {    return (!target->isCarryingFood()) && (target->choosePheromone() != nullptr);},
        [](GrouperWithRules* target) -> void
        {
            target->pointTo(target->choosePheromone()->getPosition());
        }),
        //Rule 4
        new PersonalisableStaticRule<GrouperWithRules>(
        [](GrouperWithRules* target) ->bool {    return (!target->isCarryingFood()) && (target->choosePheromone() == nullptr);},
        [](GrouperWithRules* target) -> void
        {
            target->randomRotation();
        }),
        //Rule 5
        new PersonalisableStaticRule<GrouperWithRules>(
        [](GrouperWithRules* target) ->bool 
        {   
            std::vector<GrouperHQ*> hqList = target->perceive<GrouperHQ>();
            return target->isCarryingFood() && (std::count(hqList.begin(), hqList.end(), target->getHQ()) != 0);
        },
        [](GrouperWithRules* target) -> void
        {
            target->depositFood();
            target->uTurn();
        }),
        //Rule 6
        new PersonalisableStaticRule<GrouperWithRules>(
        [](GrouperWithRules* target) ->bool 
        {
            std::vector<GrouperHQ*> hqList = target->perceive<GrouperHQ>();
            return target->isCarryingFood() && (std::count(hqList.begin(), hqList.end(), target->getHQ()) == 0);
        },
        [](GrouperWithRules* target) -> void
        {
            //turn then search for pheromones   
            //if there are pheromones, follow them, else go to the HQ directly
            target->pointTo(*target->getHQ());
            Pheromones* pheromone = target->choosePheromone();
            if(pheromone!=nullptr)
                target->pointTo(*pheromone);
        })
    });


GrouperWithRules::GrouperWithRules(Environment* environment, Vector2<float> pos, 
        GrouperHQ* hq, Vector2<float> baseMvDirection, 
        float speed , float radius, 
        float startLife) : GrouperBase(environment, pos, hq, baseMvDirection, speed, radius, startLife), PheromonesHandler(this)
{
}

void GrouperWithRules::update()
{
    if(rules.condition(this)) // condition is probably optional here
        rules.action(this);
    smartPutPheromones();
    GrouperBase::update();
}


void GrouperWithRules::smartPutPheromones() const
{
    if(isCarryingFood())
        putPheromones(PHEROMONE_AMOUNT_FULL);
    else
        putPheromones(PHEROMONE_AMOUNT_EMPTY);
}