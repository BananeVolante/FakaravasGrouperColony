#ifndef _AbstractPheromonesHandler_H
#define _AbstractPheromonesHandler_H
//#include "Pheromones.h"
//#include "GrouperBase.h"


class Pheromones;
class GrouperBase;

///\brief Abstract class that define the functions that a class needs to handle pheromones
class AbstractPheromonesHandler
{
private:
    ///\brief to be able to define function before adding the class to a grouper class, an internal pointer to the concerned grouper is required
    GrouperBase* grouper;
protected: 
    ///\param grouper the grouper that will use the class. Typically, once the class is inherited in a grouper class, this will be initialised with 'this'
    AbstractPheromonesHandler(GrouperBase* grouper) : grouper(grouper){};
    ///\brief If there are pheromones where the grouper is, increase the amount of pheromones of this pile by amount, if not, create a pile with amount pheromones
    ///\brief the amount of pheromones to add/create the pile with
    virtual void putPheromones(float amount) const = 0;
    ///\brief Select one Pheromone among all the "compatible" pheromones near the grouper
    ///\remark This function have been designer to be as much versatile as possible, it could be used to 
    /// select a pheromone from a certain team for example
    virtual Pheromones* choosePheromone() const = 0;
    ///\return the grouper that uses this handler
    inline GrouperBase* getGrouper() const {return grouper;}
};


#endif