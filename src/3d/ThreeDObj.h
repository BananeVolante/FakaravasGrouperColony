#ifndef _ThreeDObj_H
#define _ThreeDObj_H
#include <eigen3/Eigen/Dense>
#include <vector>

using Eigen::Matrix3f;
using Eigen::Vector3f;

namespace Fakarava3d
{
        using namespace Fakarava3d;
///\brief Class that represents an object in a 3d space
class ThreeDObj
{
public: 

    ///\brief contains all the data that defines a Mesh
    struct MeshData
    {
        ///\brief creates a MeshData with points, lines and triangles
        ///\param points points of the mesh
        ///\param lines lines of the mesh(the values refer to indexes in points)
        ///\param triangles triangles of the mesh(the valeus refer to indexes in points)
        MeshData(std::vector<Vector3f> points, std::vector<std::pair<size_t, size_t>>  lines, 
                std::vector<std::tuple<size_t, size_t, size_t>> triangles);

        ///\brief creates a mesh data with no triangles(since i can't display them)
        ///\param points points of the mesh
        ///\param lines lines of the mesh(the values refer to indexes in points)
        MeshData(std::vector<Vector3f> points, std::vector<std::pair<size_t, size_t>>  lines); 
        
        ///\brief creates a meshData with no points, triangles or lines
        MeshData();
        ///\brief the points of the mesh, the order is important
        std::vector<Vector3f> points;
        ///\brief the lines of the mesh. each entry define a line that starts at points[line.first] and ends at points[line.second]
        std::vector<std::pair<size_t, size_t>>  lines;
        ///\brief the triangles of the mesh. each entry define a triangle
        ///between points[std::get<0>(triangle)], points[std::get<1>(triangle)] and points[std::get<2>(triangle)]
        ///\remark This entry will probably stay empty, drawing a triangle means caring about depth, and i'm not sure if i have the time
        std::vector<std::tuple<size_t, size_t, size_t>> triangles;
    };

private: 
    ///\brief Position of the object
    Vector3f position;

    ///\brief scale of the object
    Matrix3f scale;
public: 
    ///\param position Position of the object in 3d
    ThreeDObj(const Vector3f& position, const Vector3f& scale);

    ///\return the position of the object
    const Vector3f& getPosition() const;


    virtual void setPosition(const Vector3f& newPos);


    const Matrix3f& getScaleMat() const;

    void setScaleMat(const Matrix3f& mat);

    void setScale(const Vector3f& xyzScales);

    Vector3f getScale() const;


    #warning "recheck return value"
    ///\return all the points that constitute the object
    virtual MeshData getMesh() const = 0;




};

}


#endif