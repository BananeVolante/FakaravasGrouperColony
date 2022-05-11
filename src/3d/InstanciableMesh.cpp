#include "InstanciableMesh.h"
using namespace Fakarava3d; 
InstanciableMesh::InstanciableMesh(LocalMesh* baseMesh) : baseMesh(baseMesh)
{
    
}


LocalMesh* InstanciableMesh::getBaseMesh() const
{
    return baseMesh;
}

std::vector<AbstractMesh::point>& InstanciableMesh::getLocalPoints()
{
    return baseMesh->getLocalPoints();
}

const std::vector<AbstractMesh::point>& InstanciableMesh::getLocalPoints() const
{
    return baseMesh->getLocalPoints();
}

std::vector<AbstractMesh::line>& InstanciableMesh::getLines()
{
    return baseMesh->getLines();
}

const std::vector<AbstractMesh::line>& InstanciableMesh::getLines() const 
{
    return baseMesh->getLines();
}

std::vector<AbstractMesh::triangle>& InstanciableMesh::getTriangles()
{
    return baseMesh->getTriangles();
}

const std::vector<AbstractMesh::triangle>& InstanciableMesh::getTriangles() const
{
    return baseMesh->getTriangles();
}



std::vector<Eigen::Vector3f> InstanciableMesh::getWorldPoints() const
{
    std::vector<Vector3f> worldPoints;
    worldPoints.reserve(getBaseMesh()->getLocalPoints().size());
    for(const Vector3f& vec : getBaseMesh()->getLocalPoints())
    {
        worldPoints.push_back((getRotation()*getScaleMat()*vec) + getPosition());
    }
    return worldPoints;
}
