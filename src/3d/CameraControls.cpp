#include "CameraControls.h"

    CameraControls::CameraControls(Fakarava3d::Camera &cam, float rotSpeed, float movSpeed) : camera(cam), rotationSpeed(rotSpeed), movementSpeed(movSpeed)
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
        camera.rotate(Eigen::AngleAxisf(amount, axis));
    }
    
    void CameraControls::move(const Eigen::Vector3f& axis, float amount)
    {
        camera.setPosition(camera.getPosition() + amount *axis);
    }


///\brief handle the controls for the camera
///\param keycode code of the key
void CameraControls::handleControls(SDL_Keycode keycode)
{
	if(keycode == SDLK_UP)
		move(Eigen::Vector3f::UnitY() , true);
	if(keycode == SDLK_DOWN)
		move(Eigen::Vector3f::UnitY(), false);

	if(keycode == SDLK_LEFT)
		move(Eigen::Vector3f::UnitX(), false);
	if(keycode == SDLK_RIGHT)
		move(Eigen::Vector3f::UnitX(), true);

    if(keycode == SDLK_KP_PLUS)
		move(Eigen::Vector3f::UnitZ(), true);
	if(keycode == SDLK_KP_MINUS)
		move(Eigen::Vector3f::UnitZ(), false);

	if(keycode == SDLK_KP_8)
		rotate(Eigen::Vector3f::UnitX(), true);
	if(keycode == SDLK_KP_2)
		rotate(Eigen::Vector3f::UnitX(), false);

    if(keycode == SDLK_KP_4)
		rotate(Eigen::Vector3f::UnitY(), true);
	if(keycode == SDLK_KP_6)
		rotate(Eigen::Vector3f::UnitY(), false);
	
}