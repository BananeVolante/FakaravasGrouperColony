#include "ThreeDController.h"
#include "Vector2.h"

using namespace ThreeD;
using namespace Eigen;

ThreeDController::ThreeDController(Camera* cam) : cam(cam)
{

}


Vector2<float> ThreeDController::project(const Vector3f& point)
{
    //Vector3f v = cam->getPlane().projection(point);
    //return Vector2<float>(-v.x(), v.y());
}