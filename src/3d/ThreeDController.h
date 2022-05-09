#ifndef _ThreeDController_H
#define _ThreeDController_H
#include "Vector2.h"
#include "ThreeDObj.h"
#include "Camera.h"
#include "Mesh.h"
#include "3d/Renderer.h"

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
            float x, y, z;
            float arr[3];
        } point3D;

        typedef struct rgba
        {
            unsigned char r,g,b,a;
        } rgba;

    typedef std::function<void(const Vector2<float>& startPoint, const Vector2<float>& endPoint, const rgba& color)> drawLineFunction;
    //typedef void  (*drawLineFunction)(const Vector2<float>& startPoint, const Vector2<float>& endPoint, const rgba& color);
    typedef std::function<void(const Vector2<float>& point, float size, const rgba& color)> drawPointFunction;
  //  typedef void (*drawPointFunction)(const Vector2<float>& point, float size, const rgba& color);
    typedef std::function<void(const Vector2<float>& firstPoint,const Vector2<float>& secondPoint,const Vector2<float>& thirdPoint, const rgba& color)> drawTriangleFunction;
    //typedef void (*drawTriangleFunction)(const Vector2<float>& firstPoint,const Vector2<float>& secondPoint,const Vector2<float>& thirdPoint, const rgba& color);

    typedef std::function<void(const Vector2<float>& position, const rgba& color)> drawPixelFunction;


    ///\brief flag to indicate if the back side of faces must be drawn
    static constexpr char DRAW_FLAG_FACE_BACK = 0b0001000;

    

    private:
        ///\brief The camera currently used by this controller
        Camera camera;

        drawLineFunction drawLine;
        drawPointFunction drawPoint;
        drawTriangleFunction drawTriangle;
        drawPixelFunction drawPixel;
        Fakarava3d::Renderer rend;


    public:
        ///\param position position of the camera
        ///\param width of the plan where images are prohected
        ///\param height of the plan where images are projected
        ///\param focal focal of the camera
        ///\param screenWidth width of the screen where 2d points are drawn
        ///\param screenHeight height of the screen 2d points are drawn
        ThreeDController(point3D position, float width, float height, float focal, float screenWidth, float screenHeight,
            drawPointFunction drawPoint, drawLineFunction drawLine, drawTriangleFunction drawTriangle, drawPixelFunction drawPixel);


        ///\return a reference to the camera
        Camera &getCamera();


        ///\brief project and draw a mesh
        ///\param mesh mesh to project and draw
        ///\param drawFlags used to modify the rendering process, no longer used for now
        void drawMesh(const Mesh& mesh, char drawFlags = 0);

        ///\brief draw all meshes on screen
        void flushDrawings();
    };

}

#endif