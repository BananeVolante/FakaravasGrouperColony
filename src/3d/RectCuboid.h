#ifndef _Cube_H
#define _Cube_H
#include "ThreeDObj.h"

namespace Fakarava3d
{
    using namespace Fakarava3d;
///\brief Class that represents a rectangular cuboid
class RectCuboid : public Fakarava3d::ThreeDObj
{
public:
///\param hwlDimensions Dimensions of the cuboid, coordinates are represented like that {height, width, length}
///\param position position of the center of the cuboid
RectCuboid(Vector3f hwlDimensions, Vector3f position);
///\return coordinates of the vertices situated at the corners of the coboid
virtual MeshData getMesh() const;

};
}


#endif