#ifndef _AbstractMesh_H
#define _AbstractMesh_H
#include <eigen3/Eigen/Dense>
#include <vector>
namespace Fakarava3d
{
class AbstractMesh
{
    public: 
        typedef Eigen::Vector3f point;
        typedef std::pair<size_t, size_t> line;
        typedef std::tuple<size_t, size_t, size_t> triangle;

    ///\return a modifiable reference to points in model coordinates
    virtual std::vector<point>& getLocalPoints() = 0;
    ///\return a const ref to points in model coordinates
    virtual const std::vector<point>& getLocalPoints() const = 0;
    ///\return the lines that compose the mesh
    virtual std::vector<line>& getLines() = 0;
    ///\return a const ref to the lines that compose the mesh
    virtual const std::vector<line>& getLines() const = 0;
    ///\return a ref to the triangles that compose the mesh
    virtual std::vector<triangle>& getTriangles() = 0;
    ///\return a const ref to the triangles that compose the mesh
    virtual const std::vector<triangle>& getTriangles() const = 0;
    ///\return the points that compose the mesh converted to world coordinates
    ///\remark does not return a reference because the world coordinates points are most likely processed every time this is called
    virtual std::vector<point> getWorldPoints() const = 0; 

    
};
}

#endif