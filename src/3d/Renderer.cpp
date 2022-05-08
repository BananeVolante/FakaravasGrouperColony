#include "Renderer.h"
#include "Utils.h"
#include <iostream>


using namespace Fakarava3d;
using namespace Eigen;

Renderer::Renderer(Camera& camera, float screenSizeX, float screenSizeY) : camera(camera), screenSize(screenSizeX, screenSizeY)
{

}


void Renderer::inPlaceProject(std::vector<Mesh::point>& points) const
{
    for(Mesh::point& point : points)
    {
        inPlaceProject(point);
    }
}

void Renderer::inPlaceProject(Mesh::point& point) const
{
    point = M * Vector4f(point[0], point[1], point[2], 1);
    //switch the first and second coordinates to euclidian coordinates
    point[0] /= point[2];
    point[1] /= point[2];
}

Renderer::triangleList Renderer::triangleIndexToTriangle(const std::vector<Mesh::point>& points, const std::vector<Mesh::triangle>& triangles) const
{
    triangleList tList;
    for(const Mesh::triangle& t : triangles)
    {
        tList.push_back({points[std::get<0>(t)], points[std::get<1>(t)], points[std::get<2>(t)]});
    }
    return tList;
}

const Eigen::Vector2f& Renderer::getScreenSize() const
{
    return screenSize;
}

void Renderer::setScreenSize(const Eigen::Vector2f& newVec)
{
    screenSize = newVec;
    rebuildIntrasincParameters();
}

void Renderer::queueRender(const Mesh* mesh)
{
    renderQueue.push(mesh);
}


std::list<std::array<Vector3f,3>> Renderer::render(const Mesh& mesh) const
{
    std::vector<Mesh::point> worldPoints = mesh.getWorldPoints();
    inPlaceProject(worldPoints);

    triangleList tList = triangleIndexToTriangle(worldPoints, mesh.getTriangles());
    removeBackFaces(tList);
    //removeOutOfScreenFaces(tList);
    return tList;
}

std::list<std::array<Vector3f, 3>> Renderer::render()
{
    rebuildExtrasincParameters();
    rebuildIntrasincParameters();
    rebuildM();


    std::list<std::array<Vector3f, 3>> tList;
    const Mesh* mesh;
    while (! renderQueue.empty())
    {
        mesh = renderQueue.front();
        renderQueue.pop();
        //add the the rendered triangles to the list of triangles to render
        tList.splice(tList.end(), render(*mesh));
    }
    return tList; 
}

void Renderer::removeBackFaces(Renderer::triangleList& triangles) const
{
    Vector3f camNormal = camera.getNormal();
    triangles.remove_if([&camNormal](std::array<Vector3f, 3> triangle)->bool
    {
        return normalsInSameDirection(processFaceNormal(triangle), camNormal);
    });
}

void Renderer::removeOutOfScreenFaces(Renderer::triangleList& triangles) const
{
    const Vector2f& screenDimensions = getScreenSize();
    triangles.remove_if([&screenDimensions](std::array<Vector3f, 3> triangle)->bool
    {
        //if all 3 points are out of screen
        return (outOfScreen(triangle[0], screenDimensions) &&
                outOfScreen(triangle[1], screenDimensions) &&
                outOfScreen(triangle[2], screenDimensions)); 
    });
}

std::list<Eigen::Vector2f> Renderer::rasterize(const triangleList& triangles)
{
    std::list<Eigen::Vector2f> pixelList;

    for(const triangle& t : triangles)
    {
        //process bounding box
        float xMax = std::max({t[0][0], t[1][0], t[2][0]});
        float xMin = std::min({t[0][0], t[1][0], t[2][0]});
        float yMax = std::max({t[0][1], t[1][1], t[2][1]});
        float yMin = std::min({t[0][1], t[1][1], t[2][1]});


        //update it with the screen boundings
        const Vector2f& screenS = getScreenSize(); 

        xMax = std::min(screenS[0], xMax);
        xMin = std::max(.0f, xMin);
        yMax = std::min(screenS[1], yMax);
        yMin = std::max(.0f, yMin);

        //and finally calculate which pixels are in the triangle
        //we cas from float to int, so we take more than needed
        // apparently this can be optimised thanks to the fact that the edge function is linear
        Vector2f currentPoint;
        for(int x = xMin; x<xMax+1; x++)
        {
            for(int y = yMin; y<yMax+1; y++)
            {
                currentPoint << x, y;
                if(edgeFunction(t[0], t[1], currentPoint)>0 && edgeFunction(t[1], t[2], currentPoint)>0
                     && edgeFunction(t[2], t[0], currentPoint)>0)
                {
                    pixelList.push_back(currentPoint);
                }
            }
        }
                


    }
    return pixelList;
}



void Renderer::rebuildIntrasincParameters()
{
    const Vector2f& screenDim = getScreenSize();
    float k = screenDim[0]/camera.getWidth(); 
    float l = -screenDim[1]/camera.getHeight(); 
    float alpha = camera.getFocal()*k; 
    float beta = camera.getFocal()*l; 
    float cx = screenDim[0]/2;
    float cy = screenDim[1]/2;
    cameraMatrix << alpha, 0, cx, 0, beta, cy, 0, 0, 1;
}

void Renderer::rebuildExtrasincParameters()
{
    const Matrix3f& rotationMatrix = camera.getRotation();
    extrisincParam <<rotationMatrix(0,0), rotationMatrix(0,1), 
        rotationMatrix(0,2), -camera.getPosition()[0], rotationMatrix(1,0), 
        rotationMatrix(1,1), rotationMatrix(1,2), -camera.getPosition()[1], 
        rotationMatrix(2,0), rotationMatrix(2,1), rotationMatrix(2,2), -camera.getPosition()[2];
}

void Renderer::rebuildM()
{
    M = cameraMatrix*extrisincParam;
}
