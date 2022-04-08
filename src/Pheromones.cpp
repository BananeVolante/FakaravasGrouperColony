#include "Pheromones.h"
#include "Timer.h"
#include "Renderer.h"


Pheromones::Pheromones(Environment *environment, Vector2<float> pos, float pheromonesAmount, float radius)
    : Agent(environment, pos, radius), pheromonesAmount(pheromonesAmount)
{   
}


void Pheromones::update()
{

    pheromonesAmount *= Timer::dt()*DECAY_SPEED;
}

void Pheromones::draw()
{
    Renderer::getInstance()->drawCircle(getPosition(), getRadius(), Renderer::Color(0,128,128,std::min<float>(pheromonesAmount, 255)));
}


float Pheromones::getQuantity() const
{
    return pheromonesAmount;
}

void Pheromones::addQuantity(float amount)
{
    pheromonesAmount+= amount;
}