#include "ThreeDObj.h"

using namespace Fakarava3d;

ThreeDObj::ThreeDObj(const Vector3f& position, const Vector3f& scale) : position(position), scale(Matrix3f::Identity())
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

ThreeDObj::MeshData::MeshData(std::vector<Vector3f> points, std::vector<std::pair<size_t, size_t>>  lines, 
            std::vector<std::tuple<size_t, size_t, size_t>> triangles) : 
            points(points), lines(lines), triangles(triangles)
{
    
}


ThreeDObj::MeshData::MeshData() 
{}


ThreeDObj::MeshData::MeshData(std::vector<Vector3f> points, std::vector<std::pair<size_t, size_t>>  lines) : 
            points(points), lines(lines)
{
    
}
