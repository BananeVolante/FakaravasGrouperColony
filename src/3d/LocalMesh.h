#ifndef _Mesh_Data_H
#define _Mesh_Data_H
#include "ThreeDObj.h"
#include "AbstractMesh.h"

#include <eigen3/Eigen/Dense>
#include <vector>

namespace Fakarava3d
{
    using Eigen::Vector3f;
    using namespace Fakarava3d;
    ///\brief A mesh cannot be moved, rotated, scaled or anything
    ///made to be encapsulated or intherited
    class LocalMesh : public AbstractMesh
    {
    private:
        ///\brief the points of the mesh, the order is important
        std::vector<point> points;
        ///\brief the lines of the mesh. each entry define a line that starts at points[line.first] and ends at points[line.second]
        std::vector<line> lines;
        ///\brief the triangles of the mesh. each entry define a triangle
        /// between points[std::get<0>(triangle)], points[std::get<1>(triangle)] and points[std::get<2>(triangle)]
        std::vector<triangle> triangles;

    public:
        ///\brief creates a Mesh with no points, triangles or lines
        LocalMesh();

    ///\return a modifiable reference to points in model coordinates
    std::vector<point>& getLocalPoints();
    ///\return a const ref to points in model coordinates
    const std::vector<point>& getLocalPoints() const;
    ///\return the lines that compose the mesh
    std::vector<line>& getLines();
    ///\return a const ref to the lines that compose the mesh
    const std::vector<line>& getLines() const;
    ///\return a ref to the triangles that compose the mesh
    std::vector<triangle>& getTriangles();
    ///\return a const ref to the triangles that compose the mesh
    const std::vector<triangle>& getTriangles() const;
    ///\return the points that compose the mesh converted to world coordinates
    ///\remark does not return a reference because the world coordinates points are most likely processed every time this is called
    virtual std::vector<point> getWorldPoints() const; 

      
    };
}

#endif