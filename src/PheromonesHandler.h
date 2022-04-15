#ifndef _PheromonesHandler_H
#define _PheromonesHandler_H
#include "AbstractPheromonesHandler.h"

///\brief class made to handle "normal" pheromones
class PheromonesHandler : public AbstractPheromonesHandler
{
private: 
    ///\brief distance at which the grouper can smell pheromones
    static constexpr float PHEROMONES_SENSE_DISTANCE = 8;
    ///\brief angle at which the groupers can smell pheromones
    static const float PHEROMONES_SENSE_ANGLE; //pi/3 , using pi/2 made them sometimes block 

protected: 
    ///\param grouper grouper concerned by this handler
    PheromonesHandler(GrouperBase* grouper);
    ///\copydoc AbstractPheromonesHandler::putPheromones
    virtual void putPheromones(float amount) const;
    ///\copydoc AbstractPheromonesHandler::choosePheromones
    virtual Pheromones* choosePheromone() const;
};

#endif