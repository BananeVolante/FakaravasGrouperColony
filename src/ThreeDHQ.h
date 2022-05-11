#ifndef _ThreeDHQ_H
#define _ThreeDHQ_H
#include "GrouperHQ.h"
#include "3d/InstanciableMesh.h"
class ThreeDHQ : public GrouperHQ
{
    private: 
        Fakarava3d::InstanciableMesh mesh;
    public: 
    ThreeDHQ(Environment *environment, Vector2<float> pos, std::string name);

    ///\brief normal update + update 3d coordinates
    virtual void update();

    ///\brief draw in 3d
    virtual void draw();

    Fakarava3d::InstanciableMesh& getMesh();
};


#endif