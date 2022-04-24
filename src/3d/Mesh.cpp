#include "Mesh.h"



using namespace Fakarava3d;

Mesh::Mesh(std::vector<Vector3f> points, std::vector<std::pair<size_t, size_t>>  lines, 
            std::vector<std::tuple<size_t, size_t, size_t>> triangles) : 
            points(points), lines(lines), triangles(triangles)
{
    
}


Mesh::Mesh() 
{}


Mesh::Mesh(std::vector<Vector3f> points, std::vector<std::pair<size_t, size_t>>  lines) : ThreeDObj(),
            points(points), lines(lines)
{
    
}


std::vector<std::pair<size_t, size_t>>&  Mesh::getLines()
{
    return lines;
}

std::vector<std::tuple<size_t, size_t, size_t>>& Mesh::getTriangles()
{
    return triangles;
}

std::vector<Vector3f>& Mesh::getLocalPoints()
{
    return points;
}

std::vector<Vector3f> Mesh::getWorldPoints()
{
    std::vector<Vector3f> worldPoints;
    for(Vector3f& vec : getLocalPoints())
    {
        worldPoints.push_back((getRotation() * getScaleMat() * vec) + getPosition() ); 
    }
    return worldPoints;
}
