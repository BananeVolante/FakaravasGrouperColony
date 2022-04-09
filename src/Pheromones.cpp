#include "Pheromones.h"
#include "Timer.h"
#include "Renderer.h"


Pheromones::Pheromones(Environment *environment, Vector2<float> pos, float pheromonesAmount, float radius)
    : Agent(environment, pos, radius), pheromonesAmount(pheromonesAmount)
{   
}


void Pheromones::update()
{
    //std::string msg("Pheromones updated, started at " + std::to_string(pheromonesAmount));
    pheromonesAmount -= Timer::dt()*DECAY_SPEED*pheromonesAmount;
    if(pheromonesAmount<0.01)
        status = destroy;
    //msg += std::string(" ended at " + std::to_string(pheromonesAmount));
   // SDL_Log(msg.c_str());
}

void Pheromones::draw()
{
    Renderer::getInstance()->drawCircle(getPosition(), getRadius()*5, Renderer::Color(0,128,128,std::min<float>(pheromonesAmount, 255)));
}


float Pheromones::getQuantity() const
{
    return pheromonesAmount;
}

void Pheromones::addQuantity(float amount)
{
    pheromonesAmount+= amount;
}