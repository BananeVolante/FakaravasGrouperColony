#ifndef _ThreeDFood_H
#define _ThreeDFood_H
#include "Food.h"
#include "3d/InstanciableMesh.h"

class ThreeDFood : public Food
{
    private: 
    Fakarava3d::InstanciableMesh mesh;
    public: 

    ThreeDFood(Environment *environment, Vector2<float> pos, float foodAmount);


    ///\brief normal update + update positions
    virtual void update();

    ///\brief draw the element in 3d
    virtual void draw();

    Fakarava3d::InstanciableMesh& getMesh();


};

#endif