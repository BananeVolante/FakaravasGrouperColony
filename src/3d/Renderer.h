#ifndef _Fakarava3dRenderer_H
#define _Fakarava3dRenderer_H
#include "Camera.h"
#include "AbstractMesh.h"
#include <list>
#include <queue>

namespace Fakarava3d
{
    using namespace Fakarava3d;

    class Renderer
    {
    public:


    typedef std::array<Vector3f,3> triangle;
    typedef std::list<triangle> triangleList;

    private:

    ///\brief the camera used by this renderer
        Camera& camera;
    ///\brief dimensions of the screen
        Eigen::Vector2f screenSize;

    ///\brief The camera matrix (K in the stanford document), that contains all intrinsic parametrs = the parameters that define the camera
        Eigen::Matrix3f cameraMatrix;

    ///\brief The extrisinc parameters matrix, that contains the rotation and position of the camera
        Eigen::Matrix<float, 3, 4> extrisincParam;

    ///\brief the matrix that turns 3d world coordinates into 2d screen coordinates
    ///\remark This matrix is supposed to be reprocessed every time a change is made to the extrisinc parameters
        Eigen::Matrix<float, 3, 4> M;

    ///\brief container withh all the meshes that must be drawn
    std::queue<const AbstractMesh*> renderQueue;

        
    public:
        ///\param camera the camero(that have a position, rotation, focal, projection area) used by this renderer
        ///\param screenSizeX the width of the screen
        ///\param screenSizeY the height of the screen
        Renderer(Camera& camera, float screenSizeX, float screenSizeY);

        ///\return the current screen size. first elem is width, second elem is height
        const Eigen::Vector2f& getScreenSize() const;
        ///\brief change the screen szie and update the different matrixes
        ///\param newVec the new vector. 
        void setScreenSize(const Eigen::Vector2f& newVec);

        ///\brief add a mesh to render when render is called
        ///\param mesh mesh to add to the queue
        void queueRender(const AbstractMesh* mesh);

        ///get world points of the model
        /// project thos points
        /// convert the point vector + index triangles to coordinates triangles
        //remove useless triangles
        ///\brief turn a mesh into trangle screen coordinates 
        ///\param mesh the mesh to render
        ///\return a list with all the triangles
        std::list<std::array<Vector3f,3>> render(const AbstractMesh& mesh) const;

        ///\brief update the matrixes and take all the meshes that have been queued for render and turn them to triangles
        ///\return a list with all the triangles to draw
        ///\bug triangles overlap at the edges, drawing lines between them when there is transparency
        std::list<std::array<Vector3f, 3>> render();


        ///\brief project the points onto the screen by erasing the previous points
        ///\param points the points to project
        void inPlaceProject(std::vector<AbstractMesh::point>& points) const;

            ///\brief project the points onto the screen by erasing the previous points
        ///\param points the points to project
        void inPlaceProject(AbstractMesh::point& point) const;

        ///\brief take a vector of point and a vector of index triangles(triangles made with the indexes of the points)
        ///\param points vector containing the points
        ///\param triangles vector containing the index triangles
        ///\return a list of triangles that uses points directly
        /// the last one is its depth
        triangleList triangleIndexToTriangle(const std::vector<AbstractMesh::point>& points, const std::vector<AbstractMesh::triangle>& triangles) const;

        ///\brief removes the triangles that are not facing the camera
        ///\param triangles the list of triangles to modify
        void removeBackFaces(Renderer::triangleList& triangles) const;

        ///\brief removes the triangles that are out of screen
        ///\param triangles the list of triangles to modify
        void removeOutOfScreenFaces(Renderer::triangleList& triangles) const;

        ///\brief turn triangles into pixels
        ///\param triangles the triangles to transform
        ///\return a list of pixels
        ///\remark Completely annihilates FPS, so for now this class only returns triangles
        std::list<Eigen::Vector2f> rasterize(const triangleList& triangles);


    private: 
        ///\brief reprocess the extrasinc parameters matrix 
        void rebuildExtrasincParameters();
        ///\brief reprocess the intrasinc parameters matrix 
        void rebuildIntrasincParameters();
        ///\brief reprocess M
        void rebuildM();

    };
}

#endif