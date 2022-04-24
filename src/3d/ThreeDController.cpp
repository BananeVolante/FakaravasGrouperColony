#include "ThreeDController.h"
#include "Vector2.h"

using namespace Fakarava3d;
using namespace Eigen;

ThreeDController::ThreeDController(point3D position, float width, float height
                    , float focal, float screenWidth, float screenHeight,
                    drawPointFunction drawPoint, drawLineFunction drawLine, drawTriangleFunction drawTriangle) : 
                    camera(Vector3f(position.x, position.y, position.z), Matrix3f::Identity(), 
                    width, height, focal, screenWidth, screenHeight), drawLine(drawLine), drawPoint(drawPoint), drawTriangle(drawTriangle)
{

}

Vector2<float> ThreeDController::project(const Vector3f& point) const
{
    Vector2f tmp = camera.project(point);
    return {tmp[0], tmp[1]};
}

std::vector<Vector2<float>> ThreeDController::project(const std::vector<Vector3f>& points) const
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


void ThreeDController::drawMesh(const Mesh& mesh) const
{
    std::vector<Vector2<float>> projectedPoints = project(mesh.getWorldPoints());
    for(const Vector2<float>& point : projectedPoints)
        drawPoint(point, 1, {0,0,255,255});
    for(const auto& line : mesh.getLines())
        drawLine(line.first, line.second, {255,255,255,255});
    for(const auto& triangle : mesh.getTriangles())
        drawTriangle(std::get<0>(triangle),std::get<1>(triangle), std::get<2>(triangle), {255,255,0,255});

}