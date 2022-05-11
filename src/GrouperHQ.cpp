#include "GrouperHQ.h"
#include "Renderer.h"
#include "GrouperFactory.h"


GrouperHQ::GrouperHQ(Environment *environment, Vector2<float> pos, std::string name) : Agent(environment, pos, GROUPERHQ_DEFAULT_RADIUS), amountOfFood(0),totalAmountOfFood(0) ,name(name)
{

}



void GrouperHQ::draw()
{
    Renderer::getInstance()->drawCircle(getPosition(), GROUPERHQ_DEFAULT_RADIUS, Renderer::Color(0,0,255));
    Renderer::getInstance()->drawString(getPosition()+Vector2<float>(-15,15), getName());
    Renderer::getInstance()->drawString(getPosition()+Vector2<float>(-15,25), std::to_string((getScore())));
}


void GrouperHQ::update()
{
    ///disabled because of a conflict with 3d grouper, no time to fix it
    /*if(getAmount() > GROUPER_COST)
    {
        amountOfFood -= GROUPER_COST;
        GrouperFactory::getInstance()->spawnGrouper(this);
    }*/
}


void GrouperHQ::depositFood(float amount)
{
    if(amount <0)
        throw new std::invalid_argument("amount of food cannot be negative");
    amountOfFood += amount;
    totalAmountOfFood += amount;
}

float GrouperHQ::getAmount() const
{
    return amountOfFood;
}

float GrouperHQ::getScore() const
{
    return totalAmountOfFood;
}

const std::string& GrouperHQ::getName() const
{
    return name;
}
