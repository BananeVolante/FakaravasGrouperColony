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

    std::set<Mesh::line>& lines = getLines();
    lines.insert({0,1});
    lines.insert({0,2});
    lines.insert({0,4});
    lines.insert({1,3});
    lines.insert({1,5});
    lines.insert({2,3});
    lines.insert({2,6});
    lines.insert({3,7});
    lines.insert({4,5});
    lines.insert({4,6});
    lines.insert({5,7});
    lines.insert({6,7});

}
