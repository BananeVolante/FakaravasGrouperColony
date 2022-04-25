#ifndef _CameraControls_H
#define _CameraControls_H
#include "Camera.h"

namespace Fakarava3d
{
    using namespace Eigen;
    class CameraControls
    {

    private:
        Camera &camera;
        float rotationSpeed;
        float movementSpeed;

    public:
        CameraControls(Camera &cam, float rotSpeed = 0.001, float movSpeed = 0.001);

        void setRotSpeed(float rotSpeed);
        void setMovSpeed(float movSpeed);

        void rotate(const Eigen::Vector3f& axis, bool positiveDirection);
        void move(const Eigen::Vector3f& axis,bool positiveDirection);
        
        void rotate(const Eigen::Vector3f& axis, float amount);
        void move(const Eigen::Vector3f& axis, float amount);

    };

}

#endif