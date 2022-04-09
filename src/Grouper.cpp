#include "Grouper.h"
#include "Renderer.h"

Grouper::Grouper(Environment* environment, Vector2<float> pos, 
        GrouperHQ* hq, Vector2<float> baseMvDirection, 
        float speed , float radius, 
        float startLife) : GrouperBasePheromones(environment, pos, hq, baseMvDirection, speed, radius, startLife)
{

}


void Grouper::update()
{
    
    if(!isCarryingFood())
    {
        std::vector<Food*> foodPileOnSameCell = perceive<Food>();
        std::vector<Food*> foodPileNearby = perceive<Food>(getMvDirection(), viewAngle, viewDistance);
        //if the grouper is on top of food
        if(foodPileOnSameCell.size() !=0)
        {
            for(Food* f : foodPileOnSameCell)
            {
                collectFood(*f);
                if(isFull())
                    break;
            }
        }//if the grouper is not on top of a food pile, search for a nearby food pile
        else if(foodPileNearby.size() != 0)
        {
            //go to the first one
            pointTo(*foodPileNearby[0]);
        }else // if there is no food pile nearby, search for pheromones
        {
            Pheromones* pheromone = choosePheromone();
            if(pheromone != nullptr) // if there are pheromones nearby, follow them
            {
                pointTo(pheromone->getPosition());
            } else  // else move randomly
            {
                randomRotation();
            }
        }
        
    }else 
    {
        //for now, if the grouper have food, we consider that he must deposit
        //if the grouper is on the HQ, deposit food
        //same as before, search for things to do, THEN rotate
        std::vector<GrouperHQ*> hqList = perceive<GrouperHQ>();
        //If the HQ have been found in the list of nearby HQ, deposit food, then make a u turn
        if (std::count(hqList.begin(), hqList.end(), getHQ()) != 0 )
        {
            depositFood();
            uTurn();
        }else //go back to the HQ
        {
            //turn then search for pheromones   
            //if there are pheromones, follow them, else go to the HQ directly
            pointTo(*getHQ());
            Pheromones* pheromone = choosePheromone();
            if(pheromone!=nullptr)
                pointTo(*pheromone);
                
        }
    }

    
    putPheromones();

    GrouperBasePheromones::update();
}

void Grouper::putPheromones() const
{
    if(isCarryingFood())
        GrouperBasePheromones::putPheromones(PHEROMONE_AMOUNT_FULL);
    else
        GrouperBasePheromones::putPheromones(PHEROMONE_AMOUNT_EMPTY);
}
