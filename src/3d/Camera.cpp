#include "Camera.h"

using namespace ThreeD;
using namespace Eigen;

Camera::Camera(Vector3f position,  Hyperplane<float, 3> plane, float width, float height) : ThreeDObj(position), plane(plane), width(width), height(height)
{}

const Hyperplane<float, 3>& Camera::getPlane() const
{
    return plane;
}

Vector3f Camera::getNormal() const
{
    return plane.normal();
}

std::vector<Vector3f> Camera::getPoints() const
{
    return std::vector<Vector3f>();
}

float Camera::getWidth() const
{return width;}

float Camera::getHeight() const
{return height;}

