#include "GrouperHQ.h"
#include "Renderer.h"



GrouperHQ::GrouperHQ(Environment *environment, Vector2<float> pos) : Agent(environment, pos, GROUPERHQ_DEFAULT_RADIUS), amountOfFood(0)
{

}



void GrouperHQ::draw()
{
    Renderer::getInstance()->drawCircle(getPosition(), GROUPERHQ_DEFAULT_RADIUS, Renderer::Color(0,0,255));
}


void GrouperHQ::update()
{
    
}


void GrouperHQ::depositFood(float amount)
{
    if(amount <0)
        throw new std::invalid_argument("amount of food cannot be negative");
    amountOfFood += amount;
}