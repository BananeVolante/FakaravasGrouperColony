#include "ThreeDGrouper.h"
#include "3d/RessourceHandler.h"
#include "3d/ThreeDController.h"
#include "ThreeDPheromone.h"
#include "math.h"

ThreeDGrouper::ThreeDGrouper(Environment *environment, Vector2<float> pos,
                     GrouperHQ *hq, Vector2<float> baseMvDirection,
                     float speed, float radius,
                     float startLife) : GrouperWithRules(environment, pos, hq, baseMvDirection, speed, radius, startLife), mesh(Fakarava3d::RessourceHandler::getInstance()->get("lowPolyGrouper"))
{
 mesh.setRotation(Eigen::AngleAxisf(MathUtils::piDiv2, Eigen::Vector3f::UnitY()).toRotationMatrix());   
}

void ThreeDGrouper::update()
{
    GrouperWithRules::update();
    getMesh().setPosition(Eigen::Vector3f(getPosition()[0], getPosition()[1], isCarryingFood() ? -5 : 0));
    //e trouve pas les bonnes rotations a appliquer getMesh().setRotation((Eigen::AngleAxisf(atan2(getMvDirection()[0], getMvDirection()[1]), Eigen::Vector3f::UnitZ()) * Eigen::AngleAxisf(MathUtils::piDiv2, Eigen::Vector3f::UnitY())).toRotationMatrix());
}

void ThreeDGrouper::draw()
{
    Fakarava3d::ThreeDController::getInstance()->drawMesh(getMesh());
}

Fakarava3d::InstanciableMesh& ThreeDGrouper::getMesh()
{
    return mesh;
}

void ThreeDGrouper::putPheromones(float amount) const
{
    //GrouperWithRules::putPheromones(amount);
    
    //check for nearby pheromones pile
    //if there are piles, add amount to ALL piles
    //else create a new pile
    std::vector<ThreeDPheromone*> pheromonesPiles =  getGrouper()->perceive<ThreeDPheromone>();
    if(pheromonesPiles.empty())
        new ThreeDPheromone(getGrouper()->getEnvironment(), getGrouper()->getPosition(), amount, getGrouper()->getHQ());
    else
    {
        for(ThreeDPheromone *f : pheromonesPiles)
            f->addQuantity(amount);
        
    }
}
