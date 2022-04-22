#include "RectCuboid.h"
#include <iostream>
using Fakarava3d::RectCuboid;

RectCuboid::RectCuboid(Vector3f hwlDimensions, Vector3f position) : ThreeDObj(position),
    height(hwlDimensions.x()), width(hwlDimensions.y()), length(hwlDimensions.z())
{

}

std::vector<Vector3f> RectCuboid::getPoints() const
{
    //this function by alternating positive and negative values for x y and z
    //every iteration, x chaneg value
    //every 2 iterations, y change values,...
    //gives something like that 1 1 1 , -1 1 1 , 1 -1 1, -1 -1 1, ...

    std::vector<Vector3f> points;
    // 3 elements devant chacun prendre 2 valeurs -> 2³ possibilités
    float x = 0.5;
    float y = 0.5;
    float z = 0.5;
    for (size_t i = 1; i<=2*2*2 ; i++)
    {
        points.push_back(getPosition() + Vector3f(x*height, y*width, z*length));

        x*=-1;
        y*= (i%(2)==0 ? -1 : 1);
        z*= (i%(2*2)==0 ? -1 : 1);
    }   
    return points;
}
