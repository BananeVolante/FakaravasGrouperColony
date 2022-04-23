#ifndef _ThreeDController_H
#define _ThreeDController_H
#include "Vector2.h"
#include "ThreeDObj.h"
#include "Camera.h"

namespace Fakarava3d
{
    using namespace Fakarava3d;
    class ThreeDController
    {
    public:
        typedef struct point3D
        {
            float x,y,z;
            float arr[3];
        } point3D;

    private:
    ///\brief The camera currently used by this controller
        Camera camera;

    public:
        ThreeDController(point3D position, float width, float height
                        , float focal, float screenWidth, float screenHeight);
        Vector2<float> project(const Vector3f& point);

        std::vector<Vector2<float>> project(const std::vector<Vector3f>& points);

        Camera& getCamera();
    };
    
} 



#endif