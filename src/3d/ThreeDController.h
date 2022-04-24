#ifndef _ThreeDController_H
#define _ThreeDController_H
#include "Vector2.h"
#include "ThreeDObj.h"
#include "Camera.h"

namespace Fakarava3d
{
    using namespace Fakarava3d;
    ///\brief class made to separate as much as possible fakarava3d from the rest of the program
    class ThreeDController
    {
    public:
    ///\brief just 3 points together to separate eigen from the rest of the program
        typedef struct point3D
        {
            float x,y,z;
            float arr[3];
        } point3D;

    private:
    ///\brief The camera currently used by this controller
        Camera camera;

    public:
    ///\param position position of the camera
    ///\param width of the plan where images are prohected
    ///\param height of the plan where images are projected
    ///\param focal focal of the camera
    ///\param screenWidth width of the screen where 2d points are drawn
    ///\param screenHeight height of the screen 2d points are drawn
        ThreeDController(point3D position, float width, float height
                        , float focal, float screenWidth, float screenHeight);

        ///\brief convert a 3d point into a 2d point
        Vector2<float> project(const Vector3f& point);

        ///\brief same as project, take a vector of points
        std::vector<Vector2<float>> project(const std::vector<Vector3f>& points);

        ///\return a reference to the camera
        Camera& getCamera();
    };
    
} 



#endif