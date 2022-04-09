#include "GrouperBasePheromones.h"
#include "Pheromones.h"

GrouperBasePheromones::GrouperBasePheromones(Environment* environment, Vector2<float> pos, 
        GrouperHQ* hq, Vector2<float> baseMvDirection, 
        float speed , float radius, 
        float startLife) : GrouperBase(environment, pos, hq, baseMvDirection, speed, radius, startLife)
{

}

std::vector<Pheromones*> GrouperBasePheromones::perceivePheromones() const
{
    return LocalizedEntity::perceive<Pheromones>(getMvDirection(), viewAngle, PHEROMONES_SENSE_DISTANCE);
}


void GrouperBasePheromones::putPheromones(float amount) const
{
    //check for nearby pheromones pile
    //if there are piles, add amount to ALL piles
    //else create a new pile

    std::vector<Pheromones*> pheromonesPiles =  perceive<Pheromones>();
    if(pheromonesPiles.empty())
        new Pheromones(getEnvironment(), getPosition(), amount);
    else
    {
        for(Pheromones *f : pheromonesPiles)
            f->addQuantity(amount);
        
    }
}

Pheromones* GrouperBasePheromones::choosePheromone() const
{
    //get nearby pheromones
    std::vector<Pheromones*> nearbyPheromones = perceivePheromones();
    
    size_t listSize = nearbyPheromones.size();
    if(listSize == 0) // if there are no pheromone,s useless to continue
        return nullptr;
    std::vector<float> weights(listSize);
    for (size_t i = 0; i < listSize; i++) // create a vector with the weights of all pheromones
        weights[i] = nearbyPheromones[i]->getQuantity();

    return nearbyPheromones[MathUtils::randomChoose(weights)];//choose one pheromone and returns it
}

