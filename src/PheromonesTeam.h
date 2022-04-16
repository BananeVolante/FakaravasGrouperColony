#ifndef _PheromonesTeam_H
#define _PheromonesTeam_H
#include "Pheromones.h"
#include "GrouperHQ.h"

///\brief Pheromones that mark the team(hq) that placed them
class PheromonesTeam : public Pheromones
{
private: 
    ///\brief the team of the pheromone
    const GrouperHQ* const team;
public: 
    /** \param environment environment where the pheromone is placed
     * \param pos Position where the pheromone is placed 
     * \param pheromonesAmount Amount of pheromones on the pile
     * \param team whose team this pheromone belong to
     * \param 
     * 
     * */
    PheromonesTeam(Environment *environment, Vector2<float> pos, float pheromonesAmount, GrouperHQ* team) :
        Pheromones(environment, pos, pheromonesAmount), team(team)
        {}

    const GrouperHQ* const getTeam() const
    {return team;}

};


#endif