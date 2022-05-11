#include "ThreeDHQ.h"
#include "3d/ThreeDController.h"
#include "3d/RessourceHandler.h"

void ThreeDHQ::update()
{
    GrouperHQ::update();

    getMesh().setPosition(Eigen::Vector3f(getPosition()[0], getPosition()[1], 0));
    getMesh().rotate(Eigen::AngleAxisf(0.03, Eigen::Vector3f::UnitY()));
}

void ThreeDHQ::draw()
{
    Fakarava3d::ThreeDController::getInstance()->drawMesh(mesh);
}

Fakarava3d::InstanciableMesh& ThreeDHQ::getMesh()
{
    return mesh;
}

ThreeDHQ::ThreeDHQ(Environment *environment, Vector2<float> pos, std::string name) : GrouperHQ(environment, pos, name), mesh(Fakarava3d::RessourceHandler::getInstance()->get("HQ"))
{
    mesh.setScale(Eigen::Vector3f::Ones()* getRadius());
}
