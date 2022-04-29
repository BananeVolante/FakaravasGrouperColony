#ifndef _Cube_H
#define _Cube_H
#include "ThreeDObj.h"
#include "Mesh.h"

namespace Fakarava3d
{
    using namespace Fakarava3d;
///\brief Class that represents a rectangular cuboid
class RectCuboid : public Mesh
{
public:
///\param hwlDimensions Dimensions of the cuboid, coordinates are represented like that {height, width, length}
///\param position position of the center of the cuboid
RectCuboid(Vector3f hwlDimensions, Vector3f position);


};
}


#endif