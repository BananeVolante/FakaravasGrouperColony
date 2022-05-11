#include "ThreeDFood.h"
#include "3d/RessourceHandler.h"
#include "3d/ThreeDController.h"


ThreeDFood::ThreeDFood(Environment *environment, Vector2<float> pos, float foodAmount) : Food(environment, pos, foodAmount), mesh(Fakarava3d::RessourceHandler::getInstance()->get("food"))
{
    
}

void ThreeDFood::update()
{
    Food::update();
    getMesh().setPosition(Eigen::Vector3f(getPosition()[0], getPosition()[1], 0));
    getMesh().setScale(Eigen::Vector3f::Ones()* getRadius());
}

void ThreeDFood::draw()
{
    Fakarava3d::ThreeDController::getInstance()->drawMesh(mesh);
}

Fakarava3d::InstanciableMesh& ThreeDFood::getMesh()
{
    return mesh;
}
