#include "ThreeDController.h"
#include "Vector2.h"

#include <iostream>
#include "Utils.h"

using namespace Fakarava3d;
using namespace Eigen;

ThreeDController::ThreeDController(point3D position, float width, float height, float focal, float screenWidth, float screenHeight,
                                   drawPointFunction drawPoint, drawLineFunction drawLine, drawTriangleFunction drawTriangle, drawPixelFunction drawPixel) : camera(Vector3f(position.x, position.y, position.z), Matrix3f::Identity(),
                                                                                                                                       width, height, focal, screenWidth, screenHeight),
                                                                                                                                drawLine(drawLine), drawPoint(drawPoint), drawTriangle(drawTriangle), drawPixel(drawPixel),
                                                                                                                                rend(camera, screenWidth, screenHeight)
{
}

Vector2<float> ThreeDController::project(const Vector3f &point) const
{
    Vector2f tmp = camera.project(point);
    return {tmp[0], tmp[1]};
}

std::vector<Vector2<float>> ThreeDController::project(const std::vector<Vector3f> &points) const
{
    std::vector<Vector2<float>> projectedPoints;
    for (const Vector3f &originalPoint : points)
    {
        projectedPoints.push_back(project(originalPoint));
    }
    return projectedPoints;
}

Camera &ThreeDController::getCamera()
{
    return camera;
}

void ThreeDController::drawMesh(const Mesh &mesh, char drawFlags)
{

    rend.queueRender(&mesh);
}

void ThreeDController::flushDrawings()
{
    std::list<Vector2f> pixels = rend.rasterize(rend.render());
    for(const Vector2f& pixel : pixels )
    {
        drawPixel(Vector2<float>(pixel[0], pixel[1]), {128, 128, 255, 64});
    }
    /*for(std::array<Eigen::Vector3f, 3>& triangle : rend.render())
    {
        drawTriangle(
            Vector2<float>(triangle[0][0], triangle[0][1]),
            Vector2<float>(triangle[1][0], triangle[1][1]),
            Vector2<float>(triangle[2][0], triangle[2][1]),
            rgba({128, 128, 255, 64})
        );
    }*/
}

