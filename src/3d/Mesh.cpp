#include "Mesh.h"
using namespace Fakarava3d;

Mesh::Mesh() : LocalMesh()
{
    
}

Mesh::Mesh(const LocalMesh& baseMesh) : LocalMesh(baseMesh) // no need to redfine the copy cstr
{

}


std::vector<Vector3f> Mesh::getWorldPoints() const
{
    std::vector<Vector3f> worldPoints;
    worldPoints.reserve(getLocalPoints().size()); // thx to this, worldPoints is resized only once
    for(const Vector3f& vec : getLocalPoints())
    {
        worldPoints.push_back((getRotation() * getScaleMat() * vec) + getPosition() ); 
    }
    return worldPoints;
}
