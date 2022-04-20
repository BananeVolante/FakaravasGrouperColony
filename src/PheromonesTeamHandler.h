#ifndef _PheromonesTeamHandler_H
#define _PheromonesTeamHandler_H
#include "AbstractPheromonesHandler.h"
#include "PheromonesTeam.h"

class PheromonesTeamHandler : protected AbstractPheromonesHandler
{
private: 
    ///\brief distance at which the grouper can smell pheromones
    static constexpr float PHEROMONES_SENSE_DISTANCE = 8;
    ///\brief angle at which the groupers can smell pheromones
    static const float PHEROMONES_SENSE_ANGLE; //pi/3 , using pi/2 made them sometimes block 
protected:
 
    PheromonesTeamHandler(GrouperBase* grouper);

    virtual void putPheromones(float amount) const;

    virtual PheromonesTeam* choosePheromone() const;

    PheromonesTeam* choosePheromone(GrouperHQ* team, bool searchForAlly = true) const;
};
#endif