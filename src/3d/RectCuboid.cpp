#include "RectCuboid.h"
#include <iostream>
using namespace Fakarava3d;

RectCuboid::RectCuboid(Vector3f hwlDimensions, Vector3f position) : Mesh()
{
    setScale(hwlDimensions);
    setPosition(position);   

    std::vector<Vector3f>& points = getLocalPoints();

    points.push_back(Vector3f(.5, .5, .5));
    points.push_back(Vector3f(.5, .5, -.5));
    points.push_back(Vector3f(-.5, .5, .5));
    points.push_back(Vector3f(-.5, .5, -.5));
    points.push_back(Vector3f(.5, -.5, .5));
    points.push_back(Vector3f(.5, -.5, -.5));
    points.push_back(Vector3f(-.5, -.5, .5));
    points.push_back(Vector3f(-.5, -.5, -.5));

    std::vector<Mesh::line>& lines = getLines();
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

}
