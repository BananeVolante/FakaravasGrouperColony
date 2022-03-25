#ifndef _Food_H
#define _Food_H
#include "Agent.h"

///\brief A stack of food in an environment
class Food : public Agent
{
private:
    ///\brief current amount of food available in this heap of food
    float currentFoodAmount;
    /// \brief has the food amount changed since last update?
    bool foodChanged;

public:
    // Constructor, destructor
    /**
     * \brief Normal Constructor
     * \param environment the environment where the food is
     * \param pos the starting position of the food
     * \param foodAmount the quantity of food stored
     */
    Food(Environment *environment, Vector2<float> pos, float foodAmount);

    /**
     * \brief returns the current amount of food
     *\return the current amount of food
     */
    float getFoodQuantity() const;

    /** \brief Collect food from the pile, if quantity > amount of food available, collect what's left
     * \param quantity the maximum amount of food to collect
     * \return the amount of food collected, which is min(quantity asked, quantity available)
     */
    float collectFood(float quantity);

    ///\copydoc Agent::update()
    virtual void update();

    ///\copydoc Agent::draw()
    virtual void draw();
};

#endif