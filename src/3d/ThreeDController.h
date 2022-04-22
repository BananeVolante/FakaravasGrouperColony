#ifndef _ThreeDController_H
#define _ThreeDController_H
#include "Vector2.h"
#include "ThreeDObj.h"
#include "Camera.h"

namespace Fakarava3d
{
    using namespace Fakarava3d;
class ThreeDController
{
private:
///\brief The camera currently used by this controller
    Camera* cam;

public:
    ThreeDController(Camera* cam);
    Vector2<float> project(const Vector3f& point);

};
    
} 



#endif