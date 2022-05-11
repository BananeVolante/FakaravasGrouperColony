#include "Camera.h"
#include <iostream>

using namespace Fakarava3d;
using namespace Eigen;

Camera::Camera(Vector3f position,  Matrix3f rotMat, float width, float height, float focal, float screenWidth, float screenHeight) : ThreeDObj(position, {1,1,1}, rotMat), width(width), height(height), focal(focal)
{
}


float Camera::getWidth() const
{return width;}

float Camera::getHeight() const
{return height;}



void Camera::setRotation(const Matrix3f& newMat)
{
    ThreeDObj::setRotation(newMat);
}

void Camera::setPosition(const Vector3f& newPos)
{
    ThreeDObj::setPosition(newPos);
}

void Camera::rotate(const AngleAxisf& rotation)
{
    setRotation(rotation.toRotationMatrix() * getRotation());
}


float Camera::getFocal() const
{
    return focal;
}

Vector3f Camera::getNormal() const
{
    return getRotation()* Vector3f(0,0,-1) ;
}
