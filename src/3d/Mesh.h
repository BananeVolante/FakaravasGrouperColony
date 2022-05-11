#ifndef _Mesh_H
#define _Mesh_H
#include "ThreeDObj.h"
#include "LocalMesh.h"

#include <eigen3/Eigen/Dense>
#include <vector>

namespace Fakarava3d
{
    using Eigen::Vector3f;
    using namespace Fakarava3d;
    ///\brief contains all the data that defines a mesh, such as points, lines, triangles
    ///can be moved, scaled, rotated
    class Mesh : public ThreeDObj, public LocalMesh
    {
        public:

        Mesh();
        ///\brief init this mesh with the baseMesh in param
        ///\param baseMesh the mesh to use as a reference
        Mesh(const LocalMesh& baseMesh);
        
        ///\brief return a vector containing the points in world coordinates
        ///\remark this function calculate the world points, it does not simply return data already present, so call this only once per frame
        std::vector<AbstractMesh::point> getWorldPoints() const;
    };
}

#endif
