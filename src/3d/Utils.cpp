#include "Utils.h"

using namespace Eigen;


std::vector<Vector3f> Fakarava3d::processFaceNormals(const std::vector<Mesh::point>& points, const std::vector<Mesh::triangle>& triangles)
{
    std::vector<Vector3f> normals;

    for(Mesh::triangle t : triangles)
    {
        Vector3f v1 = points[std::get<1>(t)] - points[std::get<0>(t)];
        Vector3f v2 = points[std::get<2>(t)] - points[std::get<0>(t)];

        normals.push_back(v1.cross(v2));
    }
    return normals;
}

bool Fakarava3d::normalsInSameDirection(const Vector3f& v1, const Vector3f& v2)
{
    return v1.dot(v2) >=0;
}