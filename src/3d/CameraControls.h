#ifndef _CameraControls_H
#define _CameraControls_H
#include "Camera.h"
#include "SDL2/SDL_events.h"

///\brief class to control the camera more easily
///\remark not in the fakarava3d package, since it relies on sdl2's events
class CameraControls
{

private:
    Fakarava3d::Camera &camera;
    float rotationSpeed;
    float movementSpeed;

public:
///\param cam camera controlled by this class
///\param rotSpeed speed at which the rotation "happens?" 
///\param movSpeed speed at which the camera moves
    CameraControls(Fakarava3d::Camera& cam, float rotSpeed = 0.001, float movSpeed = 0.001);

///\brief change the rotation speed
///\param rotSpeed new speed
    void setRotSpeed(float rotSpeed);
///\brief change the movement speed
///\param movSpeed new speed
    void setMovSpeed(float movSpeed);

///\brief rotate the camera
///\param axis the rotation is done around this axis
///\param if true, rotate the camera by rotSpeed, if false, by -rotSpeed
    void rotate(const Eigen::Vector3f &axis, bool positiveDirection);
///\brief move the camera
///\param axis the rotation is done on this axis
///\param positive true, move the camera by movSpeed, if false, by -movSpeed
    void move(const Eigen::Vector3f &axis, bool positiveDirection);
///\brief rotate the camera
///\param axis the rotation is done around this axis
///\param amount rotation angle in radiant
    void rotate(const Eigen::Vector3f &axis, float amount);

///\brief move the camera by a specified amount
///\param axis the movement is done on this axis
///\param amount units moved
    void move(const Eigen::Vector3f &axis, float amount);


    
///\brief handle the controls for the camera
///\param keycode code of the key
void handleControls(SDL_Keycode keycode);

};

#endif