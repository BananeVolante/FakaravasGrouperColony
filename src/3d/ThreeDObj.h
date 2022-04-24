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


    virtual void setPosition(const Vector3f& newPos);


    const Matrix3f& getScaleMat() const;

    virtual void setScaleMat(const Matrix3f& mat);

    virtual void setScale(const Vector3f& xyzScales);

    Vector3f getScale() const;

    const Matrix3f& getRotation() const;

    virtual void setRotation(const Matrix3f& mat);

};

}


#endif