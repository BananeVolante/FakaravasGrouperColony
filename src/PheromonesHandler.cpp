#include "PheromonesHandler.h"
#include "MathUtils.h"
#include "GrouperBase.h"
#include "Pheromones.h"

const float PheromonesHandler::PHEROMONES_SENSE_ANGLE = MathUtils::pi /3;

PheromonesHandler::PheromonesHandler(GrouperBase* grouper) : AbstractPheromonesHandler(grouper)
{}

Pheromones* PheromonesHandler::choosePheromone() const
{
    std::vector<Pheromones*> nearbyPheromones = getGrouper()->perceive<Pheromones>(getGrouper()->getMvDirection(),PHEROMONES_SENSE_ANGLE, PHEROMONES_SENSE_DISTANCE);

     size_t listSize = nearbyPheromones.size();
    if(listSize == 0) // if there are no pheromone,s useless to continue
        return nullptr;
    std::vector<float> weights(listSize);
    for (size_t i = 0; i < listSize; i++) // create a vector with the weights of all pheromones
        weights[i] = nearbyPheromones[i]->getQuantity();

    return nearbyPheromones[MathUtils::randomChoose(weights)];//choose one pheromone and returns it

}


void PheromonesHandler::putPheromones(float amount) const
{
    //check for nearby pheromones pile
    //if there are piles, add amount to ALL piles
    //else create a new pile
    std::vector<Pheromones*> pheromonesPiles =  getGrouper()->perceive<Pheromones>();
    if(pheromonesPiles.empty())
        new Pheromones(getGrouper()->getEnvironment(), getGrouper()->getPosition(), amount);
    else
    {
        for(Pheromones *f : pheromonesPiles)
            f->addQuantity(amount);
        
    }
}