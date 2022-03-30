#ifndef _GrouperHQ_H
#define _GrouperHQ_H
#include "Agent.h"


#define GROUPERHQ_DEFAULT_RADIUS 10

///\brief Class representing the central base of a category of agents
class GrouperHQ : Agent
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

    virtual void draw();
    

};


#endif