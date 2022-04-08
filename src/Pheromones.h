#ifndef _Pheromones_H
#define _Pheromones_H
#include "Agent.h"

///\brief grouper's pheromones, that are used to mark paths that lead to food
class Pheromones : public Agent
{
private:
///\brief speed at which the amount of pheromones decay
    static constexpr float DECAY_SPEED = 0.01;


///\brief amount of pheromones in this pile of pheromones
    float pheromonesAmount;


public:
/** \brief normal constructor for pheromones
* \copydoc Agent::Agent()   
* \param pheromonesAmount amount of pheromons stored in the pile when it's created
*
*/
Pheromones(Environment *environment, Vector2<float> pos, float pheromonesAmount, float radius = Environment::LocalizedEntity::defaultRadius());

///\copydoc Agent::update()
virtual void update();
///\copydoc Agent::draw()
virtual void draw();  


///\returns amount of pheromones in this pile
float getQuantity() const;

///\brief add a certain amount of pheromones to this pile
///\param amount amount of pheromones to add
void addQuantity(float amount);

};

#endif