#ifndef _InstanciableMesh_H
#define _InstanciableMesh_H

#include "LocalMesh.h"
#include <eigen3/Eigen/Dense>
namespace Fakarava3d
{
    ///\brief a class ade to reuse the same meshData but edit its position, size, rotation
    class InstanciableMesh : public ThreeDObj, public AbstractMesh
    {
    private:
        ///\brief a pointer to the mesh data used
        LocalMesh *baseMesh;

    public:

        ///\param baseMesh the mesh used by this instance
        InstanciableMesh(LocalMesh* baseMesh);

        ///\return the data of the mesh used
        LocalMesh *getBaseMesh() const;

        ///\return a modifiable reference to points in model coordinates
        std::vector<point> &getLocalPoints();
        ///\return a const ref to points in model coordinates
        const std::vector<point> &getLocalPoints() const;
        ///\return the lines that compose the mesh
        std::vector<line> &getLines();
        ///\return a const ref to the lines that compose the mesh
        const std::vector<line> &getLines() const;
        ///\return a ref to the triangles that compose the mesh
        std::vector<triangle> &getTriangles();
        ///\return a const ref to the triangles that compose the mesh
        const std::vector<triangle> &getTriangles() const;
        ///\return the points of the mesh used as a base converted to world coordinates using the data of this class
        std::vector<point> getWorldPoints() const;
    };

}

#endif