#include "LocalMesh.h"

using namespace Fakarava3d;

LocalMesh::LocalMesh() 
{}

std::vector<std::pair<size_t, size_t>>&  LocalMesh::getLines()
{
    return lines;
}

std::vector<std::tuple<size_t, size_t, size_t>>& LocalMesh::getTriangles()
{
    return triangles;
}


const std::vector<std::pair<size_t, size_t>>&  LocalMesh::getLines() const
{
    return lines;
}

const std::vector<std::tuple<size_t, size_t, size_t>>& LocalMesh::getTriangles() const
{
    return triangles;
}

std::vector<AbstractMesh::point> LocalMesh::getWorldPoints() const

{
    return {};
}


std::vector<Vector3f>& LocalMesh::getLocalPoints()
{
    return points;
}

const std::vector<Vector3f>& LocalMesh::getLocalPoints() const
{
    return points;
}
