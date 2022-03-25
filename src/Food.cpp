#include "Food.h"
#include "MathUtils.h"

Food::Food(Environment *environment, Vector2<float> pos, float foodAmount) : 
    Agent(environment, pos, MathUtils::circleRadius(foodAmount))
{

}
