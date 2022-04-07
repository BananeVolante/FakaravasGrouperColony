#include "GrouperBase.h"
#include "Renderer.h"
#include "Timer.h"
const float GrouperBase::viewAngle = MathUtils::piDiv2;

GrouperBase::GrouperBase(Environment* environment, Vector2<float> 
    pos, GrouperHQ* hq,Vector2<float> baseMvDirection, float speed, float radius,float startLife) :
        Agent(environment, pos, radius), HQ(hq),  speed(speed), mvDirection(baseMvDirection.normalized()), 
        foodAmountTransported(0), lifeLeft(startLife)
{
    if(lifeLeft>lifeLeft_UPPER_BOUND || lifeLeft<lifeLeft_LOWER_BOUND)
        throw new std::invalid_argument("maxLife is not between" + std::to_string(lifeLeft_LOWER_BOUND) + 
        " and " + std::to_string(lifeLeft_UPPER_BOUND));
    if(hq == nullptr)
        throw new std::invalid_argument("hq cannot be null");
}

void GrouperBase::update()
{
    //update the life left to live
    lifeLeft-= Timer::dt();
    if(lifeLeft <=0)
        status = destroy;
    //move
    move();
}

void GrouperBase::draw()
{
    Renderer::getInstance()->drawCircle(LocalizedEntity::getPosition(), LocalizedEntity::getRadius(), 
        (foodAmountTransported==0)? Renderer::Color(255,255,255) : Renderer::Color(128,255,128));
}

GrouperHQ*const GrouperBase::getHQ() const
{
    return HQ;
}

void GrouperBase::move()
{
    LocalizedEntity::translate(mvDirection*speed*Timer::dt());
}

void GrouperBase::rotate(float angle)
{
    mvDirection = mvDirection.rotate(angle);
}

void GrouperBase::uTurn()
{
    mvDirection = mvDirection*-1;
}

void GrouperBase::pointTo(Vector2<float> point)
{
    mvDirection = (point-LocalizedEntity::getPosition()).normalized();
}

void GrouperBase::pointTo(const LocalizedEntity& entity )
{
    pointTo(entity.getPosition());
}

void GrouperBase::depositFood()
{
   // if(getPosition() != HQ->getPosition())
     //   throw new GrouperBase::badPositionException("The grouper must be on top of the hq to deposit food");

    HQ->depositFood(foodAmountTransported);
    foodAmountTransported = 0 ;
}


void GrouperBase::collectFood(Food& foodPile)
{
   // if(getPosition() != foodPile.getPosition())
     //   throw new GrouperBase::badPositionException("the grouper must be near the foodpile to collect food from it");
    float foodCollectable = maxFoodAmountTransported-foodAmountTransported;
    foodAmountTransported +=  foodPile.collectFood(foodCollectable);
}   



bool GrouperBase::isFull()
{
    return foodAmountTransported >= maxFoodAmountTransported; 
}