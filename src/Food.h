#ifndef _Food_H
#define _Food_H
#include "Agent.h"
class Food : public Agent
{
    public: 
    //Constructor, destructor
    /**
     * \brief Normal Constructor
     * \param environment the environment where the food is
     * \param pos the starting position of the food
     * \param foodAmount the quantity of food stored
     */ 
     Food(Environment *environment, Vector2<float> pos, float foodAmount);


};


#endif