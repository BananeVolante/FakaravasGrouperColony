#ifndef _ThreeDPheromone_H
#define _ThreeDPheromone_H
#include "PheromonesTeam.h"
#include "3d/InstanciableMesh.h"

class ThreeDPheromone : public PheromonesTeam
{
    private: 
    Fakarava3d::InstanciableMesh mesh;

    public : 
    ThreeDPheromone(Environment *environment, Vector2<float> pos, float pheromonesAmount, GrouperHQ* team);


    virtual void draw();

    Fakarava3d::InstanciableMesh& getMesh();


};


#endif