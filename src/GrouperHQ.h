#ifndef _GrouperHQ_H
#define _GrouperHQ_H
#include "Agent.h"


#define GROUPERHQ_DEFAULT_RADIUS 10

///\brief Class representing the central base of a category of agents
class GrouperHQ : public Agent
{
private :

    ///\brief Amount of food currently stored in this HQ
    float amountOfFood;

public : 
    /**
     *\brief standard constructor for a grouperHQ
     * \param environment environment where the grouperHQ is located
     * \param pos position where the grouperHQ is located
     */
    

    GrouperHQ(Environment *environment, Vector2<float> pos);

    ///\copydoc Agent::update()
    virtual void update();

    ///\copydoc Agent::draw()
    virtual void draw();

    ///\brief add food to this HQ's stock
    ///\param amount amount of food to deposit
    void depositFood(float amount);

    ///\return return the amount of food stocked
    float getAmount() const;
    

};


#endif