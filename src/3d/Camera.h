#ifndef _Camera_H
#define _Camera_H
#include "ThreeDObj.h"
#include "eigen3/Eigen/Geometry"


namespace Fakarava3d
{
    using namespace Fakarava3d;
///\brief a not orthographic camera
///\remark this camera always point toward (0,0,0)
class Camera : public ThreeDObj
{
private:
///\brief width of the plan projected
    float width;
///\brief Height of the plan projected
    float height;

///\brief focal length of the camera
    float focal;

public:
///\param position Position of the camera
///\param rotMat Rotation of the camera
///\param width width of the surface where things are projected
///\param height height of the surface where things are projected
    Camera(Eigen::Vector3f position,  Eigen::Matrix3f rotMat, float width, float height, float focal, float screenWidth, float screenHeight);


///\return width of the surface where things are projected
    float getWidth() const;
///\return height of the surface where things are projected
    float getHeight() const;

///\return the focal
    float getFocal() const;

    Vector3f getNormal() const;

///\brief set the rotation matrix
    virtual void setRotation(const Eigen::Matrix3f& newMatrix);
///\brief set the position
///\remark contrary to its parent function, this function is not virtual, this is intended(but might not do what i want to do)
    void setPosition(const Eigen::Vector3f& newPosition);


///\brief apply a rotation to the camera
    void rotate(const Eigen::AngleAxisf& rotation);
};
}

#endif