#ifndef _Mesh_H
#define _Mesh_H
#include "ThreeDObj.h"

#include <eigen3/Eigen/Dense>
#include <vector>

namespace Fakarava3d
{
    using Eigen::Vector3f;
    using namespace Fakarava3d;
    ///\brief contains all the data that defines a mesh, such as points, lines, triangles(not supported)
    ///can be moved, scales, rotated
    class Mesh : public ThreeDObj
    {
    private:
        ///\brief the points of the mesh, the order is important
        std::vector<Vector3f> points;
        ///\brief the lines of the mesh. each entry define a line that starts at points[line.first] and ends at points[line.second]
        std::vector<std::pair<size_t, size_t>> lines;
        ///\brief the triangles of the mesh. each entry define a triangle
        /// between points[std::get<0>(triangle)], points[std::get<1>(triangle)] and points[std::get<2>(triangle)]
        ///\remark This entry will probably stay empty, drawing a triangle means caring about depth, and i'm not sure if i have the time
        std::vector<std::tuple<size_t, size_t, size_t>> triangles;

    public:
        ///\brief creates a Mesh with points, lines and triangles
        ///\param points points of the mesh
        ///\param lines lines of the mesh(the values refer to indexes in points)
        ///\param triangles triangles of the mesh(the valeus refer to indexes in points)
        Mesh(std::vector<Eigen::Vector3f> points, std::vector<std::pair<size_t, size_t>> lines,
             std::vector<std::tuple<size_t, size_t, size_t>> triangles);

        ///\brief creates a mesh data with no triangles(since i can't display them)
        ///\param points points of the mesh
        ///\param lines lines of the mesh(the values refer to indexes in points)
        Mesh(std::vector<Eigen::Vector3f> points, std::vector<std::pair<size_t, size_t>> lines);

        ///\brief creates a Mesh with no points, triangles or lines
        Mesh();

        ///\brief return an modiable reference to the lines
        std::vector<std::pair<size_t, size_t>> &getLines();

        ///\brief return a modifiable reference to the triangles
        std::vector<std::tuple<size_t, size_t, size_t>> &getTriangles();

        ///\brief return a modifiable reference to the points
        std::vector<Vector3f> &getLocalPoints();

        ///\brief return a vector containing the points in world coordinates
        std::vector<Vector3f> getWorldPoints();
    };
}

#endif
