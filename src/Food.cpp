#include "Food.h"
#include "MathUtils.h"

Food::Food(Environment *environment, Vector2<float> pos, float foodAmount) : 
    Agent(environment, pos, MathUtils::circleRadius(foodAmount)), currentFoodAmount(foodAmount), foodChanged(false)
{

}

float Food::getFoodQuantity() const
{
    return currentFoodAmount;
}

float Food::collectFood(float quantity)
{
    float amountToCollect = fmin(quantity, currentFoodAmount);
    currentFoodAmount-= amountToCollect;
    foodChanged = foodChanged || (amountToCollect!=0); //true if already true or if a non null amount of food have been collected
    return amountToCollect;
}


void Food::update()
{
    if(currentFoodAmount == 0)
        status = destroy;
    else if (foodChanged)
    {
        setRadius(MathUtils::circleRadius(currentFoodAmount));
    }

    foodChanged = false;//reset it
}