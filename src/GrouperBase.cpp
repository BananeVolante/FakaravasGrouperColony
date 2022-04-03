#include "GrouperBase.h"
#include "Renderer.h"
const float GrouperBase::viewAngle = MathUtils::piDiv2;

GrouperBase::GrouperBase(Environment* environment, Vector2<float> 
    pos, GrouperHQ* hq,Vector2<float> baseMvDirection, float speed, float radius,float startLife) :
        Agent(environment, pos, radius), HQ(hq),  speed(speed), mvDirection(baseMvDirection), 
        foodAmountTransported(0), lifeLeft(startLife)
{
    if(lifeLeft>lifeLeft_UPPER_BOUND || lifeLeft<lifeLeft_LOWER_BOUND)
        throw new std::invalid_argument("maxLife is not between" + std::to_string(lifeLeft_LOWER_BOUND) + 
        " and " + std::to_string(lifeLeft_UPPER_BOUND));


}

void GrouperBase::update()
{
    
}

void GrouperBase::draw()
{
    Renderer::getInstance()->drawCircle(LocalizedEntity::getPosition(), LocalizedEntity::getRadius(), 
        (foodAmountTransported==0)? Renderer::Color(255,255,255) : Renderer::Color(128,255,128));
}