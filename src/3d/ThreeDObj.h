#ifndef _ThreeDObj_H
#define _ThreeDObj_H
#include <eigen3/Eigen/Dense>
#include <vector>



namespace Fakarava3d
{
        using Eigen::Matrix3f;
        using Eigen::Vector3f;
        using namespace Fakarava3d;
///\brief Class that represents an object in a 3d space
class ThreeDObj
{
public: 

    

private: 
    ///\brief Position of the object
    Vector3f position;

    ///\brief scale of the object
    Matrix3f scale;

    ///\brief rotation of the object
    Matrix3f rotation;
public: 
    ///\param position Position of the object in 3d
    ThreeDObj(const Vector3f& position = Vector3f::Zero(), const Vector3f& scale = Vector3f::Ones(), const Matrix3f& rotation = Matrix3f::Identity());

    ///\return the position of the object
    const Vector3f& getPosition() const;


    ///\brief change the position of the object
    ///\param newPos new position
    virtual void setPosition(const Vector3f& newPos);


    ///\return the scale matrix
    const Matrix3f& getScaleMat() const;

    ///\brief change the scale matrix
    ////\param mat the new scale matrix
    virtual void setScaleMat(const Matrix3f& mat);

    ///\brief change the scalle of the object
    ///\param xyzScales vector with the x, y and z scales, in this order
    virtual void setScale(const Vector3f& xyzScales);

    ///\return the scale of the object, with x, y and z in this order
    Vector3f getScale() const;

    ///\return a constant reference to the rotation matrix
    const Matrix3f& getRotation() const;

    ///\brief change the rotation matrix 
    ///\param mat the nexw rotation matrix to use
    virtual void setRotation(const Matrix3f& mat);

    ///\brief rotate the model
    ///\param rotation to add to the current rotation
    void rotate(const Eigen::AngleAxisf& rotation);


};

}


#endif