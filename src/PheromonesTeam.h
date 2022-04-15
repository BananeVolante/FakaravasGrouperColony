#ifndef _PheromonesTeam_H
#define _PheromonesTeam_H
#include "Pheromones.h"
#include "GrouperHQ.h"


class PheromonesTeam : public Pheromones
{
private: 
    const GrouperHQ* const team;
public: 
    PheromonesTeam(Environment *environment, Vector2<float> pos, float pheromonesAmount, GrouperHQ* team,float radius = Environment::LocalizedEntity::defaultRadius()) :
        Pheromones(environment, pos, pheromonesAmount, radius), team(team)
        {}

    const GrouperHQ* const getTeam() const
    {return team;}

};


#endif