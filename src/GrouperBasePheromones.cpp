#include "GrouperBasePheromones.h"
#include "Pheromones.h"
#include "iostream"

const float GrouperBasePheromones::PHEROMONES_SENSE_ANGLE = MathUtils::pi /3;


GrouperBasePheromones::GrouperBasePheromones(Environment* environment, Vector2<float> pos, 
        GrouperHQ* hq, Vector2<float> baseMvDirection, 
        float speed , float radius, 
        float startLife) : GrouperBase(environment, pos, hq, baseMvDirection, speed, radius, startLife)
{
    std::cerr << " Deprecated : Use classes of the AbstractPheromonesHandler family instead of this one" << std::endl; 
}

std::vector<PheromonesTeam*> GrouperBasePheromones::perceivePheromones() const
{
    return LocalizedEntity::perceive<PheromonesTeam>(getMvDirection(), PHEROMONES_SENSE_ANGLE, PHEROMONES_SENSE_DISTANCE);
}


void GrouperBasePheromones::putPheromones(float amount) const
{
    //check for nearby pheromones pile
    //if there are piles, add amount to ALL piles
    //else create a new pile

    std::vector<PheromonesTeam*> pheromonesPiles =  perceive<PheromonesTeam>();
    if(pheromonesPiles.empty())
        new PheromonesTeam(getEnvironment(), getPosition(), amount, getHQ());
    else
    {
        for(PheromonesTeam *f : pheromonesPiles)
            f->addQuantity(amount);
        
    }
}

PheromonesTeam* GrouperBasePheromones::choosePheromone() const
{
    //get nearby pheromones
    std::vector<PheromonesTeam*> nearbyPheromones = perceivePheromones();
    
    size_t listSize = nearbyPheromones.size();
    if(listSize == 0) // if there are no pheromone,s useless to continue
        return nullptr;
    std::vector<float> weights(listSize);
    for (size_t i = 0; i < listSize; i++) // create a vector with the weights of all pheromones
        weights[i] = nearbyPheromones[i]->getQuantity();

    return nearbyPheromones[MathUtils::randomChoose(weights)];//choose one pheromone and returns it
}

void GrouperBasePheromones::putPheromones() const
{
    if(isCarryingFood())
        putPheromones(PHEROMONE_AMOUNT_FULL);
    else
        putPheromones(PHEROMONE_AMOUNT_EMPTY);
}
