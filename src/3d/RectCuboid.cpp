#include "RectCuboid.h"
#include <iostream>
using namespace Fakarava3d;

RectCuboid::RectCuboid(Vector3f hwlDimensions, Vector3f position) : ThreeDObj(position, hwlDimensions)
{

}

ThreeDObj::MeshData RectCuboid::getMesh() const
{
    //this function DOES NOT WORK by alternating positive and negative values for x y and z
    //every iteration, x chaneg value
    //every 2 iterations, y change values,...
    //gives something like that 1 1 1 , -1 1 1 , 1 -1 1, -1 -1 1, ...
    // Or just do it stupidly, it will be easier to make lines like that*
    // 

    std::vector<Vector3f> points;

    points.push_back(Vector3f(.5, .5, .5));
    points.push_back(Vector3f(.5, .5, -.5));
    points.push_back(Vector3f(-.5, .5, .5));
    points.push_back(Vector3f(-.5, .5, -.5));
    points.push_back(Vector3f(.5, -.5, .5));
    points.push_back(Vector3f(.5, -.5, -.5));
    points.push_back(Vector3f(-.5, -.5, .5));
    points.push_back(Vector3f(-.5, -.5, -.5));


    // rotate the cuboid and switch to world coordinates
    for(Vector3f& p : points)
    {
        p = getScaleMat() * p + getPosition();
    }
    
    std::vector<std::pair<size_t, size_t>> lines;
    lines.push_back({0,1});
    lines.push_back({0,2});
    lines.push_back({0,4});
    lines.push_back({1,3});
    lines.push_back({1,5});
    lines.push_back({2,3});
    lines.push_back({2,6});
    lines.push_back({3,7});
    lines.push_back({4,5});
    lines.push_back({4,6});
    lines.push_back({5,7});
    lines.push_back({6,7});

    std::vector<std::tuple<size_t, size_t, size_t>> triangles;


    return MeshData(points, lines, triangles);
}
