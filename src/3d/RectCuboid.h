#ifndef _Cube_H
#define _Cube_H
#include "ThreeDObj.h"

namespace ThreeD
{
///\brief Class that represents a rectangular cuboid
class RectCuboid : public ThreeDObj
{
private:
    float height;
    float width;
    float length;
public:
///\param hwlDimensions Dimensions of the cuboid, coordinates are represented like that {height, width, length}
///\param position position of the center of the cuboid
RectCuboid(Vector3f hwlDimensions, Vector3f position);
///\return coordinates of the vertices situated at the corners of the coboid
virtual std::vector<Vector3f> getPoints() const;

};
}


#endif