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

Vector3f Fakarava3d::processFaceNormal(const std::array<Vector3f, 3>& triangle)
{
    return (triangle[1] - triangle[0]).cross(triangle[2]-triangle[0]);
}


bool Fakarava3d::outOfScreen(const Vector3f& point, const Eigen::Vector2f& screenDimensions)
{
    if(point[0]<0 || point[0]>screenDimensions[0] || point[1]<0 || point[1]>screenDimensions[1])
        return true;
    return false;
    /*if(point[0]>=0 && point[0]<=screenDimensions[0] && point[1]>=0 && point[1]<=screenDimensions[1])
        return false;
    return true;*/
}

float Fakarava3d::edgeFunction(const Vector3f& v0, const Vector3f& v1, const Vector2f& point)
{
    return (point[0] - v0[0]) * (v1[1] - v0[1]) - (point[1] - v0[1]) * (v1[0] - v0[0]);    
}

