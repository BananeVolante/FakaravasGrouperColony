#include "ThreeDObj.h"

using namespace Fakarava3d;

ThreeDObj::ThreeDObj(const Vector3f& position, const Vector3f& scale, const Matrix3f& rotation) : position(position), scale(Matrix3f::Identity()), rotation(rotation)
{
    setScale(scale);
}

const Vector3f& ThreeDObj::getPosition() const
{
    return position;
}

void ThreeDObj::setPosition(const Vector3f &newPos)
{
    position = newPos;
}

const Matrix3f &ThreeDObj::getScaleMat() const
{
    return scale;
}
void ThreeDObj::setScaleMat(const Matrix3f &mat)
{
    scale = mat;
}
void ThreeDObj::setScale(const Vector3f &xyzScales)
{
    scale(0, 0) = xyzScales[0];
    scale(1, 1) = xyzScales[1];
    scale(2, 2) = xyzScales[2];
}
Vector3f ThreeDObj::getScale() const
{
    return {scale(0, 0), scale(1, 1), scale(2, 2)};
}


const Matrix3f& ThreeDObj::getRotation() const
{
    return rotation;
}

void ThreeDObj::setRotation(const Matrix3f& mat)
{
    rotation = mat;
}
