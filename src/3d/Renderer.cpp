#include "Renderer.h"
#include "Utils.h"
#include <iostream>


using namespace Fakarava3d;
using namespace Eigen;

Renderer::Renderer(Camera& camera, float screenSizeX, float screenSizeY) : camera(camera), screenSize(screenSizeX, screenSizeY)
{
    //M will be rebuilt 2 times, but it's a constructor not supposed to be called every frame
    rebuildExtrasincParameters();
    rebuildIntrasincParameters();
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
    rebuildM();
}

void Renderer::rebuildExtrasincParameters()
{
    const Matrix3f& rotationMatrix = camera.getRotation();
    extrisincParam <<rotationMatrix(0,0), rotationMatrix(0,1), 
        rotationMatrix(0,2), -camera.getPosition()[0], rotationMatrix(1,0), 
        rotationMatrix(1,1), rotationMatrix(1,2), -camera.getPosition()[1], 
        rotationMatrix(2,0), rotationMatrix(2,1), rotationMatrix(2,2), -camera.getPosition()[2];
    rebuildM();
}

void Renderer::rebuildM()
{
    M = cameraMatrix*extrisincParam;
}
