#ifndef _Camera_H
#define _Camera_H
#include "ThreeDObj.h"
#include "eigen3/Eigen/Geometry"


namespace Fakarava3d
{
    using namespace Fakarava3d;
class Camera : public ThreeDObj
{
private:
///\brief width of the plan projected
    float width;
///\brief Height of the plan projected
    float height;

///\brief focal length of the camera
    float focal;

///\brief The camera matrix (K in the stanford document), that contains all intrinsic parametrs = the parameters that define the camera
    Eigen::Matrix3f cameraMatrix;

///\brief The extrisinc parameters matrix, that contains the rotation and position of the camera
    Eigen::Matrix<float, 3, 4> extrisincParam;

///\brief the matrix that turns 3d world coordinates into 2d screen coordinates
///\remark This matrix is supposed to be reprocessed every time a change is made to the extrisinc parameters
    Eigen::Matrix<float, 3, 4> M;


///\brief update the extrisinc parameters matrix, and reprocess the M matrix
    void updateExtrisincParam();

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

///\brief set the rotation matrix
    virtual void setRotation(const Eigen::Matrix3f& newMatrix);
///\brief set the position
///\remark contrary to its parent function, this function is not virtual, this is intended(but might not do what i want to do)
    void setPosition(const Eigen::Vector3f& newPosition);

///\return The projection of a point onto the screen
    Eigen::Vector2f project(const Eigen::Vector3f& p) const;


///\brief apply a rotation to the camera
    void rotate(const Eigen::AngleAxisf& rotation);
};
}

#endif