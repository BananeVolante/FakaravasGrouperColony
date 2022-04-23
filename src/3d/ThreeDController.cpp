#include "ThreeDController.h"
#include "Vector2.h"

using namespace Fakarava3d;
using namespace Eigen;

ThreeDController::ThreeDController(point3D position, float width, float height
                    , float focal, float screenWidth, float screenHeight) : 
                    camera(Vector3f(position.x, position.y, position.z), Matrix3f::Identity(), 
                    width, height, focal, screenWidth, screenHeight)
{

}

Vector2<float> ThreeDController::project(const Vector3f& point)
{
    Vector2f tmp = camera.project(point);
    return {tmp[0], tmp[1]};
}

std::vector<Vector2<float>> ThreeDController::project(const std::vector<Vector3f>& points)
{
    std::vector<Vector2<float>> projectedPoints;
    for(const Vector3f& originalPoint : points)
    {
        projectedPoints.push_back(project(originalPoint));
    }
    return projectedPoints;
}



Camera& ThreeDController::getCamera()
{
    return camera;
}