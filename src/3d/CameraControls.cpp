#include "CameraControls.h"
namespace Fakarava3d
{
    CameraControls::CameraControls(Camera &cam, float rotSpeed, float movSpeed) : camera(cam), rotationSpeed(rotSpeed), movementSpeed(movSpeed)
    {
        
    }
    
    void CameraControls::setRotSpeed(float rotSpeed)
    {
        rotationSpeed = rotSpeed;
    }
    
    void CameraControls::setMovSpeed(float movSpeed)
    {
        movementSpeed = movSpeed;
    }
    
    void CameraControls::rotate(const Eigen::Vector3f& axis, bool positiveDirection)
    {
        rotate(axis, rotationSpeed * (positiveDirection ? 1 : -1));
    }
    
    void CameraControls::move(const Eigen::Vector3f& axis, bool positiveDirection)
    {
        move(axis, movementSpeed * (positiveDirection ? 1 : -1));
    }
    
    void CameraControls::rotate(const Eigen::Vector3f& axis, float amount)
    {
        camera.rotate(AngleAxisf(amount, axis));
    }
    
    void CameraControls::move(const Eigen::Vector3f& axis, float amount)
    {
        camera.setPosition(camera.getPosition() + amount*axis);
    }


}