#ifndef _Camera_H
#define _Camera_H
#include "ThreeDObj.h"
#include "eigen3/Eigen/Geometry"


namespace ThreeD
{

class Camera : public ThreeDObj
{
private:
///\brief Plan where the images are projected, defined by a normal,
    Eigen::Hyperplane<float, 3> plane;

///\brief width of the plan 
    float width;
///\brief Height of the plan
    float height;
public:
///\param position Position of the camera
///\param plan Plan where images are projected, defined by a normal, Must define a base
///\param width width of the surface where things are projected
///\param height height of the surface where things are projected
    Camera(Vector3f position,  Eigen::Hyperplane<float, 3> plane, float width, float height);

///\return The plan where imaegs are projected
    const Eigen::Hyperplane<float, 3>& getPlane() const;
///\return width of the surface where things are projected
    float getWidth() const;
///\return height of the surface where things are projected
    float getHeight() const;
///\return The normal of the plan
    Vector3f getNormal() const;

///\return an empty vector
    virtual std::vector<Vector3f> getPoints() const;
};
}

#endif