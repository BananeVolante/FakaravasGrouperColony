#include "ThreeDPheromone.h"
#include "3d/RessourceHandler.h"
#include "3d/ThreeDController.h"
#include "iostream"

ThreeDPheromone::ThreeDPheromone(Environment *environment, Vector2<float> pos, float pheromonesAmount, GrouperHQ* team) : PheromonesTeam(environment, pos, pheromonesAmount, team), mesh(Fakarava3d::RessourceHandler::getInstance()->get("pheromone"))
{
    getMesh().setPosition(Eigen::Vector3f(pos[0], pos[1], 0));
    getMesh().setScale(Eigen::Vector3f(0.3, 0.3, 0.3));

}


void ThreeDPheromone::draw()
{
    if(getQuantity() > 100)
        Fakarava3d::ThreeDController::getInstance()->drawMesh(mesh); 
}

Fakarava3d::InstanciableMesh& ThreeDPheromone::getMesh()
{
    return mesh;
}

