#include "Utils.h"

using namespace Eigen;


std::vector<Vector3f> Fakarava3d::processFaceNormals(const std::vector<Mesh::point>& points, const std::set<Mesh::triangle>& triangles)
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

Vector3f Fakarava3d::processFaceNormal(const std::vector<Mesh::point>& points, const Mesh::triangle& triangle)
{
        Vector3f v1 = points[std::get<1>(triangle)] - points[std::get<0>(triangle)];
        Vector3f v2 = points[std::get<2>(triangle)] - points[std::get<0>(triangle)];

        return v1.cross(v2);
}

bool Fakarava3d::normalsInSameDirection(const Vector3f& v1, const Vector3f& v2)
{
    return v1.dot(v2) >=0;
}