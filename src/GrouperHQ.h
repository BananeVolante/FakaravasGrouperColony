#ifndef _GrouperHQ_H
#define _GrouperHQ_H
#include "Agent.h"
#include "Scoreable.h"


#define GROUPERHQ_DEFAULT_RADIUS 10

///\brief Class representing the central base of a category of agents
class GrouperHQ : public Agent, public Scoreable
{
private :

    static constexpr float GROUPER_COST = 15; 

    ///\brief Amount of food currently stored in this HQ
    float amountOfFood;

    ///\brief Total amount of food collected
    float totalAmountOfFood;

    ///\brief name of the HQ
    std::string name;

public : 
    /**
     *\brief standard constructor for a grouperHQ
     * \param environment environment where the grouperHQ is located
     * \param pos position where the grouperHQ is located
     */
    

    GrouperHQ(Environment *environment, Vector2<float> pos, std::string name);

    ///\copydoc Agent::update()
    virtual void update();

    ///\copydoc Agent::draw()
    virtual void draw();

    ///\brief add food to this HQ's stock
    ///\param amount amount of food to deposit
    void depositFood(float amount);

    ///\return return the amount of food stocked
    float getAmount() const;
    
    ///\copydoc Scoreable::getScore
    float getScore() const;

    ///\copydoc Scoreable::getName
    const std::string& getName() const;
};


#endif