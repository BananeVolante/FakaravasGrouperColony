#include "SillyGrouper.h"
#include "Timer.h"

SillyGrouper::SillyGrouper(Environment* environment, Vector2<float> pos, 
        GrouperHQ* hq, float speed, float radius, float startLife) 
        : GrouperBase(environment, pos, hq, Vector2<float>::random(), speed, radius, startLife)
    {}

#include "SDL2/SDL.h"
void SillyGrouper::update()
{
    //action order is : search for things to do -> rotate -> move
    //The Grouper cannot grab AND deposit food during the same tick

    //randomly search for food
    //If the grouper can still carry food, search for food
    if(!isFull()) 
        {
        //search food, THEN rotate

        //get liost of all foodPile
        std::vector<Food*> nearFoodPiles =  perceive<Food>();
        for(Food* f : nearFoodPiles)
        {
            collectFood(*f);
            if(isFull()) //useless to continue if the Grouper can't take more food
                break;
        }

        float randomBound = MathUtils::pi/10 *Timer::dt();
        float randomedNumber = MathUtils::random(-randomBound, randomBound) ;
        
        rotate(randomedNumber);

    }
    else // if the Grouper have to deposit food to an HQ
    {
        //same as before, search for things to do, THEN rotate
        std::vector<GrouperHQ*> hqList = perceive<GrouperHQ>();
        //If the HQ have been found in the list of nearby HQ, deposit food
        if (std::count(hqList.begin(), hqList.end(), getHQ()) != 0 )
            depositFood();
        //point even if the hq is already nearby
        pointTo(*getHQ());

    }

    GrouperBase::update();
}