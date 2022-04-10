#include "GrouperWithRules.h"
///\todo transform this into a decision tree?

GrouperWithRules::GrouperWithRules(Environment* environment, Vector2<float> pos, 
        GrouperHQ* hq, Vector2<float> baseMvDirection, 
        float speed , float radius, 
        float startLife) : GrouperBasePheromones(environment, pos, hq, baseMvDirection, speed, radius, startLife), 
        rules({new rule1(this), new rule2(this), new rule3(this), new rule4(this), new rule5(this), new rule6(this)})
{

}


GrouperWithRules::rule1::rule1(GrouperBasePheromones* grouper) : AbstractGrouperRule(grouper)
{}

GrouperWithRules::rule2::rule2(GrouperBasePheromones* grouper) : AbstractGrouperRule(grouper)
{}
GrouperWithRules::rule3::rule3(GrouperBasePheromones* grouper) : AbstractGrouperRule(grouper)
{}
GrouperWithRules::rule4::rule4(GrouperBasePheromones* grouper) : AbstractGrouperRule(grouper)
{}
GrouperWithRules::rule5::rule5(GrouperBasePheromones* grouper) : AbstractGrouperRule(grouper)
{}
GrouperWithRules::rule6::rule6(GrouperBasePheromones* grouper) : AbstractGrouperRule(grouper)
{}
bool GrouperWithRules::rule1::condition() const
{
    return (!target->isCarryingFood()) && (! target->perceive<Food>().empty()) ;
}

void GrouperWithRules::rule1::action() const
{
    std::vector<Food*> foodPileOnSameCell = target->perceive<Food>();
    for(Food* f : foodPileOnSameCell)
    {
        target->collectFood(*f);
        if(target->isFull())
            break;
    }
}

bool GrouperWithRules::rule2::condition() const
{
    return (!target->isCarryingFood()) && (! target->perceive<Food>(target->getMvDirection(),target->viewAngle, target->viewDistance ).empty()) ;
}

void GrouperWithRules::rule2::action() const
{
    std::vector<Food*> foodPileNearby = target->perceive<Food>(target->getMvDirection(), target->viewAngle, target->viewDistance);
    target->pointTo(*foodPileNearby[0]);
}

bool GrouperWithRules::rule3::condition() const
{
    return (!target->isCarryingFood()) && (target->choosePheromone() != nullptr);
}

void GrouperWithRules::rule3::action() const
{
    target->pointTo(target->choosePheromone()->getPosition());
}

bool GrouperWithRules::rule4::condition() const
{
    return (!target->isCarryingFood()) && (target->choosePheromone() == nullptr);
}

void GrouperWithRules::rule4::action() const
{
    target->randomRotation();
}

bool GrouperWithRules::rule5::condition() const
{
    std::vector<GrouperHQ*> hqList = target->perceive<GrouperHQ>();
    return target->isCarryingFood() && (std::count(hqList.begin(), hqList.end(), target->getHQ()) != 0);
}

void GrouperWithRules::rule5::action() const
{
    target->depositFood();
    target->uTurn();
}

bool GrouperWithRules::rule6::condition() const
{
    std::vector<GrouperHQ*> hqList = target->perceive<GrouperHQ>();
    return target->isCarryingFood() && (std::count(hqList.begin(), hqList.end(), target->getHQ()) == 0);
}

void GrouperWithRules::rule6::action() const
{
    //turn then search for pheromones   
    //if there are pheromones, follow them, else go to the HQ directly
    target->pointTo(*target->getHQ());
    Pheromones* pheromone = target->choosePheromone();
    if(pheromone!=nullptr)
        target->pointTo(*pheromone);
}


void GrouperWithRules::update()
{
    if(rules.condition()) // condition is probably optional here
        rules.action();
    putPheromones();
    GrouperBasePheromones::update();
}