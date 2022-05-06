#ifndef _utils_H
#define _utils_H
#include <vector>
#include <eigen3/Eigen/Dense>
#include "Mesh.h"

namespace Fakarava3d
{
        ///\brief process the normals for faces
        ///\param points vector of points
        ///\param triangles vector of triangles
        ///\return vector linking normals to faces. The normal of index "i" is the normal of the face of index "i"
        std::vector<Vector3f> processFaceNormals(const std::vector<Mesh::point>& points, const std::vector<Mesh::triangle>& triangles);
        
        ///\brief return true if the normals are "globally" in the same direction (not just colinear)
        /// -> which means that the dot product between the 2 vectors is positive
        ///\param v1 first vector
        ///\param v2 second vector
        ///\return true if the dot product is positive
        bool normalsInSameDirection(const Vector3f& v1, const Vector3f& v2);


        ///\brief process the normal of a single face
        ///\param point the array with all the points that are used
        ///\param triangle the triangle(using points index) 
        ///\return the normal of triangle
        Vector3f processFaceNormal(const std::vector<Mesh::point>& points, const Mesh::triangle& triangle);

        ///\brief process the normal of a triangle
        ///\param triangle the triangle formed by the 3 points
        ///\return the normal of the triangle
        Vector3f processFaceNormal(const std::array<Vector3f, 3>& triangle);


        ///\brief determine if a point is out of screen
        ///\param point the point first 2 coordinates are screen coordinates, third is depth
        ///\param the dimensions of the screen. first elem is x, second is y
        ///\return true if the point is out of screen
        bool outOfScreen(const Eigen::Vector3f& point, const Eigen::Vector2f& screenDimensions);



}

#endif