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


const std::vector<std::pair<size_t, size_t>>&  Mesh::getLines() const
{
    return lines;
}

const std::vector<std::tuple<size_t, size_t, size_t>>& Mesh::getTriangles() const
{
    return triangles;
}


std::vector<Vector3f>& Mesh::getLocalPoints()
{
    return points;
}

const std::vector<Vector3f>& Mesh::getLocalPoints() const
{
    return points;
}

std::vector<Vector3f> Mesh::getWorldPoints() const
{
    std::vector<Vector3f> worldPoints;
    worldPoints.reserve(getLocalPoints().size());
    for(const Vector3f& vec : getLocalPoints())
    {
        worldPoints.push_back((getRotation() * getScaleMat() * vec) + getPosition() ); 
    }
    return worldPoints;
}
