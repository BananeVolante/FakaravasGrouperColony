#ifndef _ThreeDGrouper_H
#define _ThreeDGrouper_H
#include "GrouperWithRules.h"
#include "3d/InstanciableMesh.h"

class ThreeDGrouper : public GrouperWithRules
{
    private: 
        Fakarava3d::InstanciableMesh mesh;

    public: 
        ///\copydoc GrouperBasePheromones::GrouperBasePheromones()
    ThreeDGrouper(Environment *environment, Vector2<float> pos,
                     GrouperHQ *hq, Vector2<float> baseMvDirection,
                     float speed = GrouperBase::speed_DEFAULT, float radius = LocalizedEntity::defaultRadius(),
                     float startLife = MathUtils::random(GrouperBase::lifeLeft_LOWER_BOUND, GrouperBase::lifeLeft_UPPER_BOUND));
    ///\brief normal update + update the coordinates of the mesh
    virtual void update();

    ///\brief draw using the 3d system
    virtual void draw();

    Fakarava3d::InstanciableMesh& getMesh();

    virtual void putPheromones(float amount) const;


};



#endif