#ifndef _ThreeDObj_H
#define _ThreeDObj_H
#include <eigen3/Eigen/Dense>
#include <vector>

using Eigen::Matrix3f;
using Eigen::Vector3f;

namespace ThreeD
{
///\brief Class that represents an object in a 3d space
class ThreeDObj
{
private: 
    ///\brief Position of the object
    Vector3f position;
public: 
    ///\param position Position of the object in 3d
    ThreeDObj(Vector3f position) : position(position)
    {}
    ///\return the position of the object
    const Vector3f& getPosition() const
    {return position;}

    virtual void setPosition(const Vector3f& newPos)
    {position = newPos;}
    #warning "recheck return value"
    ///\return all the points that constitute the object
    virtual std::vector<Vector3f> getPoints() const = 0;

};

}


#endif